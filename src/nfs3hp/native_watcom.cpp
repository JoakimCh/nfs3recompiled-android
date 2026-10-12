#include "native_guest.h"
#include "native_watcom_heap.h"
#include <algorithm>
#include <bitset>
#include <cstring>
#include <utility>

/* The Watcom C runtime the game was linked with, in C++: the functions of it
 * the port has natively, where their code was -- disassemble_nfs3hp.py binds
 * each address to the function of that name here (GAME_NATIVES), and the
 * generated code calls it by name.  The names are Open Watcom's (bld/clib,
 * bld/mathlib), the runtime's own descendant, which says what each does;
 * src/nfs3hp/watcom.md maps all of the runtime in nfs3.exe, what is native
 * and what is not yet.  tools/game_checks generates the game's code for them
 * afresh and holds each one against it.
 *
 * They take their arguments in registers, as Watcom's runtime does -- eax,
 * edx, ebx, ecx -- and keep every other register, as it does; the registers
 * an argument came in are the caller's no longer, and are left as they are
 * here.  What they read and write of the runtime's own state -- the
 * per-thread data, the character table, the heap -- is where the runtime
 * keeps it, in guest memory, as the code that is still generated expects. */

namespace nfs3hp
{
namespace watcom
{

namespace
{

using guest::at;
using guest::byte;
using guest::call;
using guest::put;
using guest::putByte;

/* The runtime's per-thread data: [__GetThreadPtr]() -- the pointer the
 * runtime swaps for its own when a second thread starts. */
constexpr x86::reg32 kGetThreadPtr = 0x567764;
constexpr x86::reg32 kThreadData = 0x9f642c;  // the single thread's, what GetThreadPtr hands back
constexpr x86::reg32 kRandomSeed = 0xc;        // rand's, in the thread's data
constexpr x86::reg32 kNextToken = 0x10;        // strtok's
/* _IsTable: a byte of flags for each character, EOF first. */
constexpr x86::reg32 kIsTable = 0x564ef0;
constexpr x86::reg8 kSpace = 0x02;
constexpr x86::reg8 kDigit = 0x20;

/* The thread's data, as the runtime asks for it; false when the game
 * stopped. */
bool threadData(win32::WinApplication* app, x86::CPU& cpu, x86::reg32& data)
{
    if (!call(app, cpu, at(app, kGetThreadPtr)))
        return false;
    data = cpu.eax;
    return true;
}

void returns(x86::CPU& cpu, x86::reg32 result)
{
    cpu.eax = result;
    cpu.esp += 4;
}

/* The registers but eax, as a function had them when it was called. */
struct Kept
{
    x86::reg32 ebx, ecx, edx, esi, edi, ebp;
    explicit Kept(const x86::CPU& cpu)
        : ebx(cpu.ebx), ecx(cpu.ecx), edx(cpu.edx), esi(cpu.esi), edi(cpu.edi), ebp(cpu.ebp)
    {
    }
    void back(x86::CPU& cpu) const
    {
        cpu.ebx = ebx;
        cpu.ecx = ecx;
        cpu.edx = edx;
        cpu.esi = esi;
        cpu.edi = edi;
        cpu.ebp = ebp;
    }
};

}  // namespace

/* __CHP (mathlib/a/fchop87.asm, 0x4dfd56): st(0) rounded toward zero -- the
 * game's step from a float to an integer, before every fistp -- by frndint
 * under the caller's control word with truncation in it.  Nothing else
 * changes: the registers, the control word, the status word. */
namespace
{

void chop(x86::CPU& cpu)
{
    const auto rc = cpu.fpu.control.rc;
    cpu.fpu.control.rc = 3;
    cpu.fpu.st(0) = cpu.fpu.rndint(cpu.fpu.st(0));
    cpu.fpu.control.rc = rc;
}

}  // namespace

void CHP(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    chop(cpu);
    cpu.esp += 4;
}

/* __GetThreadPtr (0x4ff0ec): the single thread's data, until a second thread
 * starts and the runtime points kGetThreadPtr at its own. */
void GetThreadPtr(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, at(app, kThreadData));
}

/* __NullAccessRtn (0x4ff0f4): what the runtime's locks are -- the streams',
 * the heap's -- while there is one thread: nothing. */
void NullAccess(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    cpu.esp += 4;
}

/* memset (clib/memory/c/memset.c, 0x4e0640): eax the buffer, edx the byte,
 * ebx how many; the buffer back. */
void memset(win32::WinApplication* app, x86::CPU& cpu)
{
    if (cpu.ebx != 0)
        std::memset(&app->getMemory<x86::reg8>(cpu.eax), int(cpu.edx & 0xff), cpu.ebx);
    returns(cpu, cpu.eax);
}

/* __STOSD (clib/cgsupp/a/__stos.asm, 0x4ff4f7): ecx dwords of edx from eax
 * on -- one by one to a 32-byte boundary, then four at a time, then up to
 * three; eax left past them, and ecx 0, but 1 after three at the end (the
 * last of them is not counted down). */
void STOSD(win32::WinApplication* app, x86::CPU& cpu)
{
    for (; cpu.ecx != 0 && (cpu.eax & 0x1f) != 0; --cpu.ecx, cpu.eax += 4)
        put(app, cpu.eax, cpu.edx);
    const x86::reg32 tail = cpu.ecx & 3;
    for (; cpu.ecx != 0; --cpu.ecx, cpu.eax += 4)
        put(app, cpu.eax, cpu.edx);
    cpu.ecx = tail == 3 ? 1 : 0;
    cpu.esp += 4;
}

/* __STOSB (clib/cgsupp/a/__stos.asm, 0x4ff4c0): ecx bytes of the pattern in
 * edx from eax on -- byte by byte up to a dword boundary, the pattern turned
 * a byte for each, then dwords (__STOSD), then up to three bytes more: dl,
 * dh, dl.  eax is left past the dwords, edx as turned, ecx 0 -- or 1 after
 * three bytes at the end, as __STOSD. */
void STOSB(win32::WinApplication* app, x86::CPU& cpu)
{
    for (; cpu.ecx != 0 && (cpu.eax & 3) != 0; --cpu.ecx, ++cpu.eax)
    {
        putByte(app, cpu.eax, x86::reg8(cpu.edx));
        cpu.edx = cpu.edx >> 8 | cpu.edx << 24;
    }
    const x86::reg32 tail = cpu.ecx & 3;
    for (cpu.ecx >>= 2; cpu.ecx != 0; --cpu.ecx, cpu.eax += 4)
        put(app, cpu.eax, cpu.edx);
    const x86::reg8 bytes[] = {x86::reg8(cpu.edx), x86::reg8(cpu.edx >> 8), x86::reg8(cpu.edx)};
    for (x86::reg32 i = 0; i < tail; ++i)
        putByte(app, cpu.eax + i, bytes[i]);
    cpu.ecx = tail == 3 ? 1 : 0;
    cpu.esp += 4;
}

/* strcmp (clib/string/a/cmp386.asm, 0x4ee310): eax and edx, the strings;
 * -1, 0 or 1 as the first byte that differs, unsigned, is below or above. */
void strcmp(win32::WinApplication* app, x86::CPU& cpu)
{
    for (x86::reg32 a = cpu.eax, b = cpu.edx;; ++a, ++b)
    {
        const x86::reg8 c = byte(app, a), d = byte(app, b);
        if (c != d)
            return returns(cpu, c < d ? 0xffffffff : 1);
        if (c == 0)
            return returns(cpu, 0);
    }
}

/* strncmp (clib/string/c/strncmp.c, 0x4eb390): eax and edx, the strings, ebx
 * the most to compare; the first difference of unsigned bytes, or 0. */
void strncmp(win32::WinApplication* app, x86::CPU& cpu)
{
    for (x86::reg32 a = cpu.eax, b = cpu.edx, n = cpu.ebx; n != 0; ++a, ++b, --n)
    {
        const x86::reg8 c = byte(app, a), d = byte(app, b);
        if (c != d)
            return returns(cpu, x86::reg32(c) - x86::reg32(d));
        if (c == 0)
            break;
    }
    returns(cpu, 0);
}

/* _stricmp (clib/string/c/stricmp.c, 0x4e9ec0): strcmp's difference, unsigned,
 * with A to Z taken as a to z and nothing else folded. */
void stricmp(win32::WinApplication* app, x86::CPU& cpu)
{
    const auto lower = [](x86::reg8 c) { return x86::reg8(c >= 'A' && c <= 'Z' ? c + 0x20 : c); };
    for (x86::reg32 a = cpu.eax, b = cpu.edx;; ++a, ++b)
    {
        const x86::reg8 c = lower(byte(app, a)), d = lower(byte(app, b));
        if (c != d || d == 0)
            return returns(cpu, x86::reg32(c) - x86::reg32(d));
    }
}

/* strncpy (clib/string/c/strncpy.c, 0x4e0e30): eax the buffer, edx the
 * string, ebx how many bytes: the string, then zeros to make up the count. */
void strncpy(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 to = cpu.eax, from = cpu.edx, n = cpu.ebx;
    for (; n != 0 && byte(app, from) != 0; --n)
        putByte(app, to++, byte(app, from++));
    for (; n != 0; --n)
        putByte(app, to++, 0);
    returns(cpu, cpu.eax);
}

/* strncat (clib/string/c/strncat.c, 0x4eedf0): eax the string, edx what to add,
 * ebx at most how much of it; always ended. */
void strncat(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 to = cpu.eax;
    while (byte(app, to) != 0)
        ++to;
    for (x86::reg32 from = cpu.edx, n = cpu.ebx; n != 0; --n, ++to, ++from)
    {
        const x86::reg8 c = byte(app, from);
        putByte(app, to, c);
        if (c == 0)
            break;
    }
    putByte(app, to, 0);
    returns(cpu, cpu.eax);
}

/* strrchr (clib/string/c/strrchr.c, 0x4ee2f0): eax the string, dl the byte;
 * where it is last, the end included, or 0. */
void strrchr(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg8 wanted = x86::reg8(cpu.edx);
    x86::reg32 found = 0;
    for (x86::reg32 at = cpu.eax;; ++at)
    {
        const x86::reg8 c = byte(app, at);
        if (c == wanted)
            found = at;
        if (c == 0)
            break;
    }
    returns(cpu, found);
}

/* strstr (clib/string/c/strstr.c, 0x4e0820): eax the string, edx what to look
 * for; where it first is, or 0 -- the string itself for an empty one. */
void strstr(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 text = cpu.eax, wanted = cpu.edx;
    x86::reg32 length = 0;
    while (byte(app, wanted + length) != 0)
        ++length;
    for (x86::reg32 at = text;; ++at)
    {
        x86::reg32 same = 0;
        while (same < length && byte(app, at + same) == byte(app, wanted + same))
            ++same;
        if (same == length)
            return returns(cpu, at);
        if (byte(app, at) == 0)
            return returns(cpu, 0);
    }
}

/* __setbits (clib/string/c/setbits.c, 0x50c540): eax 32 bytes, made the set
 * of the bytes of the string at edx -- a bit each, the low bit first. */
void setbits(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 vector = cpu.eax;
    std::memset(&app->getMemory<x86::reg8>(vector), 0, 0x20);
    for (x86::reg32 at = cpu.edx; byte(app, at) != 0; ++at)
    {
        const x86::reg8 c = byte(app, at);
        putByte(app, vector + (c >> 3), x86::reg8(byte(app, vector + (c >> 3)) | 1 << (c & 7)));
    }
    cpu.esp += 4;
}

/* strtok (clib/string/c/strtok.c, 0x4eff60): eax the string -- 0 to go on
 * where the last call stopped, kept in the thread's data -- edx the bytes
 * that part the tokens; the next token, ended, or 0 when there is none. */
void strtok(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 text = cpu.eax;
    const x86::reg32 parts = cpu.edx;
    x86::reg32 data = 0;
    if (text == 0)
    {
        if (!threadData(app, cpu, data))
            return;
        text = at(app, data + kNextToken);
        if (text == 0)
            return returns(cpu, 0);
    }
    std::bitset<256> parting;
    for (x86::reg32 at = parts; byte(app, at) != 0; ++at)
        parting.set(byte(app, at));
    while (byte(app, text) != 0 && parting.test(byte(app, text)))
        ++text;
    if (byte(app, text) == 0)
        return returns(cpu, 0);
    for (x86::reg32 at = text; byte(app, at) != 0; ++at)
        if (parting.test(byte(app, at)))
        {
            putByte(app, at, 0);
            if (!threadData(app, cpu, data))
                return;
            put(app, data + kNextToken, at + 1);
            return returns(cpu, text);
        }
    if (!threadData(app, cpu, data))
        return;
    put(app, data + kNextToken, 0);
    returns(cpu, text);
}

/* _strupr (clib/string/c/strupr.c, 0x4f8020): a to z of the string at eax made
 * A to Z, in place; the string back. */
void strupr(win32::WinApplication* app, x86::CPU& cpu)
{
    for (x86::reg32 at = cpu.eax; byte(app, at) != 0; ++at)
        if (byte(app, at) >= 'a' && byte(app, at) <= 'z')
            putByte(app, at, x86::reg8(byte(app, at) - 0x20));
    returns(cpu, cpu.eax);
}

/* toupper and tolower (clib/char/c, 0x4eede0 and 0x4f0ae0): eax a character,
 * moved between a-z and A-Z; anything else as it is. */
void toupper(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    const x86::sreg32 c = x86::sreg32(cpu.eax);
    returns(cpu, c >= 'a' && c <= 'z' ? cpu.eax - 0x20 : cpu.eax);
}

void tolower(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    const x86::sreg32 c = x86::sreg32(cpu.eax);
    returns(cpu, c >= 'A' && c <= 'Z' ? cpu.eax + 0x20 : cpu.eax);
}

/* atoi and atol (clib/convert/c, 0x4f0430 and 0x4f0490, the same code): the
 * number at eax, past white space, a sign and then digits as _IsTable has
 * them, in 32 bits as it wraps.  The table is looked up at the character
 * plus one in a byte: 0xff at EOF's place. */
void atoi(win32::WinApplication* app, x86::CPU& cpu)
{
    const auto is = [&](x86::reg8 c, x86::reg8 what) {
        return (byte(app, kIsTable + x86::reg8(c + 1)) & what) != 0;
    };
    x86::reg32 at = cpu.eax;
    while (is(byte(app, at), kSpace))
        ++at;
    const x86::reg8 sign = byte(app, at);
    if (sign == '+' || sign == '-')
        ++at;
    x86::reg32 value = 0;
    for (; is(byte(app, at), kDigit); ++at)
        value = value * 10 + byte(app, at) - '0';
    returns(cpu, sign == '-' ? 0 - value : value);
}

void atol(win32::WinApplication* app, x86::CPU& cpu)
{
    atoi(app, cpu);
}

namespace
{

/* Where rand keeps its seed: 0 if the thread has no data.  False when the
 * game stopped. */
bool seedAt(win32::WinApplication* app, x86::CPU& cpu, x86::reg32& seed)
{
    if (!threadData(app, cpu, seed))
        return false;
    seed += kRandomSeed;
    return true;
}

}  // namespace

/* initrandnext (clib/math/c/rand.c, 0x4eb1f0): where rand keeps its seed. */
void initrandnext(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 seed;
    if (seedAt(app, cpu, seed))
        returns(cpu, seed);
}

/* rand (clib/math/c/rand.c, 0x4eb1fc): the seed taken on, x 1103515245 +
 * 12345, and bits 16 to 30 of it. */
void rand(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 seed;
    if (!seedAt(app, cpu, seed))
        return;
    if (seed == 0)
        return returns(cpu, 0);
    const x86::reg32 next = at(app, seed) * 0x41c64e6d + 0x3039;
    put(app, seed, next);
    returns(cpu, next >> 16 & 0x7fff);
}

/* srand (clib/math/c/rand.c, 0x4eb220): eax the seed. */
void srand(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 value = cpu.eax;
    x86::reg32 seed;
    if (!seedAt(app, cpu, seed))
        return;
    if (seed != 0)
        put(app, seed, value);
    returns(cpu, seed);
}

/* ---- Search and sort (clib/search/c): each comparison is the caller's
 * function called as the runtime calls it -- the same elements in the same
 * order, and esp where the runtime's frame has it, for qsort's pivot lies in
 * that frame. ---- */

namespace
{

/* The caller's function on a and b -- in eax and edx, Watcom's registers --
 * called with esp at `esp`; its result.  False when the game stopped in it. */
bool compare(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 esp, x86::reg32 function, x86::reg32 a,
             x86::reg32 b, x86::sreg32& result)
{
    cpu.esp = esp;
    cpu.eax = a;
    cpu.edx = b;
    if (!call(app, cpu, function))
        return false;
    result = x86::sreg32(cpu.eax);
    return true;
}

/* byteswap's exchange of `size` bytes at p and q: a dword at a time, then a
 * byte -- q read, then p, p written, then q, as its xchg and stos do; what
 * it leaves in eax, the last of p's it moved, given `eax` before. */
x86::reg32 exchange(win32::WinApplication* app, x86::reg32 p, x86::reg32 q, x86::reg32 size, x86::reg32 eax)
{
    for (x86::reg32 i = size >> 2; i != 0; --i, p += 4, q += 4)
    {
        const x86::reg32 fromQ = at(app, q);
        eax = at(app, p);
        put(app, p, fromQ);
        put(app, q, eax);
    }
    for (x86::reg32 i = size & 3; i != 0; --i, ++p, ++q)
    {
        const x86::reg8 fromQ = byte(app, q);
        eax = (eax & 0xffffff00) | byte(app, p);
        putByte(app, p, fromQ);
        putByte(app, q, x86::reg8(eax));
    }
    return eax;
}

/* med3's choice of a, b and c, the median by the caller's function, for a
 * med3 whose return address is at `entry`: its five pushes below that. */
bool median(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 function, x86::reg32 a,
            x86::reg32 b, x86::reg32 c, x86::reg32& chosen)
{
    const x86::reg32 esp = entry - 0x14;  // esi, edi, es, fs, gs
    x86::sreg32 r;
    if (!compare(app, cpu, esp, function, a, b, r))
        return false;
    const bool aAbove = r > 0;
    if (!compare(app, cpu, esp, function, a, c, r))
        return false;
    if (aAbove ? r <= 0 : r >= 0)
    {
        chosen = a;
        return true;
    }
    if (!compare(app, cpu, esp, function, b, c, r))
        return false;
    chosen = (r <= 0) == aAbove ? c : b;
    return true;
}

}  // namespace

/* med3 (clib/search/c/qsort.c, 0x4ee480): the median of the elements at eax,
 * edx and ebx by the function at ecx. */
void med3(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 chosen;
    if (!median(app, cpu, entry, cpu.ecx, cpu.eax, cpu.edx, cpu.ebx, chosen))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, chosen);
}

/* byteswap (clib/search/c/qsortrtn.c, 0x4ee4d0): ecx bytes at esi and edi
 * exchanged -- its own convention, esi and edi left past them, ecx and edx
 * 0. */
void byteswap(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = exchange(app, cpu.esi, cpu.edi, cpu.ecx, cpu.eax);
    cpu.esi += cpu.ecx;
    cpu.edi += cpu.ecx;
    cpu.ecx = 0;
    cpu.edx = 0;
    cpu.esp += 4;
}

/* qsort (clib/search/c/qsortrtn.c, 0x4ee4f8): edx elements of ebx bytes at
 * eax sorted by the function at ecx.  Fewer than 16 by a shell sort, steps of
 * 3 and 1; more by quicksort, the pivot the median of 3 from 30 on, of 9 from
 * 43 on, the elements equal to it gathered at both ends and swapped to the
 * middle, the larger part kept for later.  An array of dwords, aligned, has
 * its pivot copied into the frame and the function handed that. */
void qsort(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 base = cpu.eax;
    x86::reg32 n = cpu.edx;
    const x86::reg32 size = cpu.ebx;
    const x86::reg32 function = cpu.ecx;
    const x86::reg32 frame = entry - 0x168;  // esi, edi, es, fs, gs, ebp, and 0x150 of its own
    const x86::reg32 pivotCopy = frame + 0x100;
    const int swaptype = ((base | size) & 3) != 0 ? 2 : size > 4 ? 1 : 0;
    auto swap = [&](x86::reg32 p, x86::reg32 q) {
        if (swaptype != 0)
        {
            exchange(app, p, q, size, 0);
        }
        else
        {
            const x86::reg32 t = at(app, p);
            put(app, p, at(app, q));
            put(app, q, t);
        }
    };
    x86::reg32 laterBase[32], laterCount[32];  // the larger parts, for later: the runtime's 32
    unsigned later = 0;
    x86::sreg32 r;
    for (;;)
    {
        if (n > 1 && n < 16)
        {
            const x86::reg32 end = base + n * size;
            for (x86::reg32 shell = 3 * size; x86::sreg32(shell) > 0; shell -= 2 * size)
                for (x86::reg32 p1 = base + shell; p1 < end; p1 += shell)
                    for (x86::reg32 p2 = p1; p2 > base; p2 -= shell)
                    {
                        if (!compare(app, cpu, frame, function, p2 - shell, p2, r))
                            return;
                        if (r <= 0)
                            break;
                        swap(p2, p2 - shell);
                    }
        }
        else if (n >= 16)
        {
            x86::reg32 mid = base + (n >> 1) * size;
            if (n > 29)
            {
                x86::reg32 p1 = base;
                x86::reg32 p2 = base + (n - 1) * size;
                if (n > 42)
                {
                    const x86::reg32 s = (n >> 3) * size;
                    if (!median(app, cpu, frame - 4, function, p1, p1 + s, p1 + 2 * s, p1)
                        || !median(app, cpu, frame - 4, function, mid - s, mid, mid + s, mid)
                        || !median(app, cpu, frame - 4, function, p2 - 2 * s, p2 - s, p2, p2))
                        return;
                }
                if (!median(app, cpu, frame - 4, function, p1, mid, p2, mid))
                    return;
            }
            x86::reg32 pivot = base;
            if (swaptype != 0)
            {
                swap(base, mid);
            }
            else
            {
                pivot = pivotCopy;
                put(app, pivotCopy, at(app, mid));
            }
            x86::reg32 pa = base, pb = base;
            x86::reg32 pc = base + (n - 1) * size, pd = pc;
            x86::reg32 count = n;
            for (;;)
            {
                for (; count != 0; pb += size, --count)
                {
                    if (!compare(app, cpu, frame, function, pb, pivot, r))
                        return;
                    if (r > 0)
                        break;
                    if (r == 0)
                    {
                        swap(pa, pb);
                        pa += size;
                    }
                }
                for (; count != 0; pc -= size, --count)
                {
                    if (!compare(app, cpu, frame, function, pc, pivot, r))
                        return;
                    if (r < 0)
                        break;
                    if (r == 0)
                    {
                        swap(pc, pd);
                        pd -= size;
                    }
                }
                if (count == 0)
                    break;
                swap(pb, pc);
                pb += size;
                if (--count == 0)
                    break;
                pc -= size;
                --count;
            }
            // The equal ones from both ends into the middle.
            const x86::reg32 pn = base + n * size;
            x86::reg32 moved = x86::sreg32(pa - base) < x86::sreg32(pb - pa) ? pa - base : pb - pa;
            if (moved != 0)
                exchange(app, base, pb - moved, moved, 0);
            moved = std::min(pd - pc, pn - pd - size);
            if (moved != 0)
                exchange(app, pb, pn - moved, moved, 0);
            // The smaller part now, the larger later.
            const x86::reg32 below = pb - pa, above = pd - pc;
            if (above >= below)
            {
                laterBase[later] = pn - above;
                laterCount[later] = above / size;
                n = below / size;
                ++later;
                continue;
            }
            if (below > size)
            {
                laterBase[later] = base;
                laterCount[later] = below / size;
                n = above / size;
                base = pn - above;
                ++later;
                continue;
            }
        }
        if (later == 0)
            break;
        --later;
        base = laterBase[later];
        n = laterCount[later];
    }
    kept.back(cpu);
    cpu.esp = entry + 4;
}

/* bsearch (clib/search/c/bsearch.c, 0x4fb300): the element of edx's ebx, ecx
 * bytes each, that the function on the stack finds equal to the key at eax,
 * halving from both ends; or 0. */
void bsearch(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 key = cpu.eax, base = cpu.edx, count = cpu.ebx, size = cpu.ecx;
    const x86::reg32 function = at(app, entry + 4);
    const x86::reg32 frame = entry - 0x1c;  // esi, edi, es, fs, gs, ebp, and the function
    x86::reg32 found = 0;
    if (count != 0)
    {
        x86::reg32 low = base, high = base + (count - 1) * size;
        x86::sreg32 r = 1;
        while (low < high)
        {
            const x86::reg32 mid = low + (high - low) / size / 2 * size;
            if (!compare(app, cpu, frame, function, key, mid, r))
                return;
            if (r == 0)
            {
                found = mid;
                break;
            }
            if (r < 0)
                high = mid;
            else
                low = mid + size;
        }
        if (r != 0 && low == high)
        {
            if (!compare(app, cpu, frame, function, key, high, r))
                return;
            found = r == 0 ? high : 0;
        }
    }
    kept.back(cpu);
    cpu.eax = found;
    cpu.esp = entry + 8;
}

/* ---- errno (clib/startup/c/seterrno.c, doserrno.c; clib/_dos/c/dosret.c):
 * the thread's, errno at +4 and _doserrno at +8.  Those that set it leave
 * eax with the thread's data, as theirs do; those that turn a Windows error
 * into it, -1. ---- */

namespace
{

constexpr x86::reg32 kErrno = 4, kDosErrno = 8;  // in the thread's data
/* __set_errno_dos's errno for each of Windows' errors up to 19, a signed
 * byte each; the rest take 19's. */
constexpr x86::reg32 kErrnoOfError = 0x567888;
/* Watcom's errno values. */
constexpr x86::reg32 kENOENT = 1, kENOMEM = 5, kEEXIST = 7, kEINVAL = 9, kERANGE = 14;

/* The Windows functions they call: their slots. */
constexpr x86::reg32 kCreateDirectoryA = 0x534490, kDeleteFileA = 0x5344b0, kFindFirstFileA = 0x5344cc;
constexpr x86::reg32 kGetCurrentDirectoryA = 0x534500, kGetDiskFreeSpaceA = 0x534514;
constexpr x86::reg32 kGetFileAttributesA = 0x534520, kGetLastError = 0x534534, kRemoveDirectoryA = 0x5345b4;
constexpr x86::reg32 kSetCurrentDirectoryA = 0x5345d4, kSetFileAttributesA = 0x5345ec;

/* A word of the thread's data set; false when the game stopped. */
bool setThreadWord(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 offset, x86::reg32 value)
{
    x86::reg32 data;
    if (!threadData(app, cpu, data))
        return false;
    put(app, data + offset, value);
    return true;
}

/* __set_errno_dos's: _doserrno the error, errno what it stands for. */
bool setErrnoDos(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 error)
{
    if (!setThreadWord(app, cpu, kDosErrno, error))
        return false;
    x86::reg32 value;
    if (error == 0x7b)  // ERROR_INVALID_NAME
        value = kENOENT;
    else if (error == 0xce)  // ERROR_FILENAME_EXCED_RANGE
        value = kEINVAL;
    else if (error == 0xb7)  // ERROR_ALREADY_EXISTS
        value = kEEXIST;
    else
        value = x86::reg32(x86::sreg32(x86::sreg8(byte(app, kErrnoOfError + std::min<x86::reg32>(error, 0x13)))));
    return setThreadWord(app, cpu, kErrno, value);
}

/* __set_errno_nt's: GetLastError's error, as __set_errno_dos has it. */
bool setErrnoNt(win32::WinApplication* app, x86::CPU& cpu)
{
    return call(app, cpu, at(app, kGetLastError)) && setErrnoDos(app, cpu, cpu.eax);
}

/* What the runtime makes of a Windows function's BOOL: 0, or errno from
 * GetLastError and -1. */
bool windowsResult(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 succeeded, x86::reg32& result)
{
    result = succeeded != 0 ? 0 : 0xffffffff;
    return succeeded != 0 || setErrnoNt(app, cpu);
}

}  // namespace

/* __set_errno (0x502880): errno eax. */
void set_errno(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setThreadWord(app, cpu, kErrno, cpu.eax))
        return;
    const x86::reg32 data = cpu.eax;
    kept.back(cpu);
    returns(cpu, data);
}

/* __set_ERANGE (0x5028a4): errno ERANGE. */
void set_ERANGE(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setThreadWord(app, cpu, kErrno, kERANGE))
        return;
    const x86::reg32 data = cpu.eax;
    kept.back(cpu);
    returns(cpu, data);
}

/* __set_doserrno (0x5028c8): _doserrno eax. */
void set_doserrno(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setThreadWord(app, cpu, kDosErrno, cpu.eax))
        return;
    const x86::reg32 data = cpu.eax;
    kept.back(cpu);
    returns(cpu, data);
}

/* __set_errno_dos (0x500f8c): errno for the Windows error in eax; -1. */
void set_errno_dos(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setErrnoDos(app, cpu, cpu.eax))
        return;
    kept.back(cpu);
    returns(cpu, 0xffffffff);
}

/* __set_errno_nt (0x500ff4): errno for GetLastError's; -1. */
void set_errno_nt(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setErrnoNt(app, cpu))
        return;
    kept.back(cpu);
    returns(cpu, 0xffffffff);
}

/* ---- Files and directories: each a Windows function on the path at eax,
 * 0 or -1 and errno.  Those that hand Windows a buffer of their own have it
 * where their frame has it, esp below it. ---- */

namespace
{

/* A function of one call to Windows on the path, BOOL its result. */
void pathCall(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 slot, std::initializer_list<x86::reg32> arguments)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!call(app, cpu, at(app, slot), arguments) || !windowsResult(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __fixed_GetFileAttributesA's: the file's attributes by FindFirstFileA --
 * the handle left open, as it leaves it -- or -1, for a path with * or ? in
 * it too; for a call whose return address is at `entry`. */
bool fileAttributes(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 path,
                    x86::reg32& attributes)
{
    attributes = 0xffffffff;
    for (x86::reg32 c = path; byte(app, c) != 0; ++c)
        if (byte(app, c) == '*' || byte(app, c) == '?')
            return true;
    const x86::reg32 found = entry - 0x150;  // ebx, ecx, edx, esi; WIN32_FIND_DATA
    cpu.esp = found;
    if (!call(app, cpu, at(app, kFindFirstFileA), {path, found}))
        return false;
    if (cpu.eax != 0xffffffff)
        attributes = at(app, found);
    return true;
}

}  // namespace

/* unlink (clib/handleio/c/unlnkwnt.c, 0x4e28a0): DeleteFileA. */
void unlink(win32::WinApplication* app, x86::CPU& cpu)
{
    pathCall(app, cpu, kDeleteFileA, {cpu.eax});
}

/* remove (clib/file/c/remove.c, 0x4ee2e0): unlink. */
void remove(win32::WinApplication* app, x86::CPU& cpu)
{
    unlink(app, cpu);
}

/* mkdir (clib/direct/c/mkdirwnt.c, 0x4eb1d0): CreateDirectoryA, no security
 * attributes. */
void mkdir(win32::WinApplication* app, x86::CPU& cpu)
{
    pathCall(app, cpu, kCreateDirectoryA, {cpu.eax, 0});
}

/* rmdir (clib/direct/c/rmdirwnt.c, 0x4ee400): RemoveDirectoryA. */
void rmdir(win32::WinApplication* app, x86::CPU& cpu)
{
    pathCall(app, cpu, kRemoveDirectoryA, {cpu.eax});
}

/* chdir (clib/direct/c/chdirwnt.c, 0x4f0260): SetCurrentDirectoryA. */
void chdir(win32::WinApplication* app, x86::CPU& cpu)
{
    pathCall(app, cpu, kSetCurrentDirectoryA, {cpu.eax});
}

/* chmod (clib/file/c/chmodwnt.c, 0x4ee3c0): the file read-only unless edx
 * has S_IWRITE (0x80), its other attributes as __fixed_GetFileAttributesA
 * finds them. */
void chmod(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 path = cpu.eax, mode = cpu.edx;
    x86::reg32 attributes, result;
    if (!fileAttributes(app, cpu, entry - 0xc, path, attributes))  // ebx, ecx, and the call
        return;
    cpu.esp = entry;
    if (attributes == 0xffffffff)
    {
        result = 0xffffffff;
        if (!setErrnoNt(app, cpu))
            return;
    }
    else
    {
        attributes = (attributes & ~x86::reg32(1)) | ((mode & 0x80) != 0 ? 0 : 1);  // FILE_ATTRIBUTE_READONLY
        if (!call(app, cpu, at(app, kSetFileAttributesA), {path, attributes})
            || !windowsResult(app, cpu, cpu.eax, result))
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

/* access (clib/file/c/accsswnt.c, 0x4f05f0): 0 if the file is there, and
 * not read-only if edx asks for writing (2). */
void access(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    const x86::reg32 mode = cpu.edx;
    if (!call(app, cpu, at(app, kGetFileAttributesA), {cpu.eax}))
        return;
    const x86::reg32 attributes = cpu.eax;
    x86::reg32 result = 0;
    if (attributes == 0xffffffff)
    {
        result = 0xffffffff;
        if (!setErrnoNt(app, cpu))
            return;
    }
    else if ((mode & 2) != 0 && (attributes & 1) != 0)
    {
        result = 0xffffffff;
        if (!setErrnoDos(app, cpu, 5))  // ERROR_ACCESS_DENIED
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

void nmalloc(win32::WinApplication* app, x86::CPU& cpu);
void nfree(win32::WinApplication* app, x86::CPU& cpu);
void sopen(win32::WinApplication* app, x86::CPU& cpu);

/* getcwd (clib/direct/c/gtcwdwnt.c, 0x4f0730): the current directory into
 * eax's edx bytes -- or, for no buffer, into a block _nmalloc gives of edx
 * bytes or as many as it takes -- or 0: errno ERANGE when it does not fit,
 * ENOMEM when there is no block.  What it copies is as long as
 * GetCurrentDirectoryA says, from its MAX_PATH bytes and on into the
 * registers it pushed -- here too. */
void getcwd(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 buffer = cpu.eax;
    const x86::reg32 size = cpu.edx;
    put(app, entry - 4, cpu.ebx);
    put(app, entry - 8, cpu.ecx);
    put(app, entry - 0xc, cpu.esi);
    put(app, entry - 0x10, cpu.edi);
    const x86::reg32 local = entry - 0x114;  // MAX_PATH bytes below them
    cpu.esp = local;
    if (!call(app, cpu, at(app, kGetCurrentDirectoryA), {0x104, local}))
        return;
    const x86::reg32 length = cpu.eax;
    x86::reg32 result = 0;
    if (length == 0)
    {
        if (!setErrnoNt(app, cpu))
            return;
    }
    else
    {
        bool fits = true;
        if (buffer == 0)
        {
            cpu.eax = std::max(size, length + 1);
            if (!call(app, cpu, nmalloc))
                return;
            buffer = cpu.eax;
            if (buffer == 0)
            {
                fits = false;
                if (!setThreadWord(app, cpu, kErrno, kENOMEM))
                    return;
            }
        }
        else if (length > size)
        {
            fits = false;
            if (!setThreadWord(app, cpu, kErrno, kERANGE))
                return;
        }
        if (fits)
        {
            for (x86::reg32 i = 0; i < length + 1; ++i)
                putByte(app, buffer + i, byte(app, local + i));
            result = buffer;
        }
    }
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* _getdiskfree (clib/direct/c/diskfree.c, 0x4f07d0): GetDiskFreeSpaceA's of
 * drive eax -- 1 A:, 0 the current one -- into edx's diskfree_t: total and
 * free clusters, sectors a cluster, bytes a sector; 0, or -1. */
void getdiskfree(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 drive = cpu.eax, info = cpu.edx;
    const x86::reg32 local = entry - 0x1c;  // ebx, ecx; the root and four dwords
    x86::reg32 root = 0;
    if (drive != 0)
    {
        putByte(app, local, x86::reg8(drive + 0x40));
        putByte(app, local + 1, ':');
        putByte(app, local + 2, '\\');
        putByte(app, local + 3, 0);
        root = local;
    }
    cpu.esp = local;
    x86::reg32 result;
    if (!call(app, cpu, at(app, kGetDiskFreeSpaceA), {root, local + 0x10, local + 0xc, local + 8, local + 4})
        || !windowsResult(app, cpu, cpu.eax, result))
        return;
    if (result == 0)
    {
        put(app, info, at(app, local + 4));
        put(app, info + 4, at(app, local + 8));
        put(app, info + 8, at(app, local + 0x10));
        put(app, info + 0xc, at(app, local + 0xc));
    }
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* __fixed_GetFileAttributesA (0x509640): GetFileAttributesA by way of
 * FindFirstFileA, which wildcards would fool: -1 for them. */
void fixed_GetFileAttributesA(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 attributes;
    if (!fileAttributes(app, cpu, entry, cpu.eax, attributes))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, attributes);
}

/* ---- The runtime's handles (clib/handleio/c): a handle is an index into
 * __OSHandles, Windows' HANDLE for it, and __io_mode, its mode; each taken
 * and given back under the file's lock, _AccessFileH and _ReleaseFileH,
 * __NullAccessRtn while there is one thread.  A handle up to __NFiles is
 * good -- __NFiles too, the runtime's own slip, kept. ---- */

namespace
{

constexpr x86::reg32 kOsHandles = 0x56acbc;  // __OSHandles: where the HANDLEs are
constexpr x86::reg32 kFileCount = 0x56ad94;  // __NFiles
constexpr x86::reg32 kIoModes = 0x56ade8;    // __io_mode: where the modes are
constexpr x86::reg32 kAccessFile = 0x567768, kReleaseFile = 0x56776c;  // the file's lock, eax the handle
/* The default windowing's hooks: none in the game. */
constexpr x86::reg32 kIsWindowedHandle = 0x5677b0, kWindowsStdin = 0x5677d8, kWindowsStdout = 0x5677dc;
constexpr x86::reg32 kGetFileType = 0x53452c, kReadFile = 0x5345b0, kSetFilePointer = 0x5345f0;
constexpr x86::reg32 kWriteFile = 0x534640;
constexpr x86::reg32 kEBADF = 4, kENOSPC = 12;
/* A mode's bits. */
constexpr x86::reg32 kAppend = 0x80, kIsTty = 0x2000, kInitialized = 0x4000, kExtended = 0x8000;

bool goodHandle(win32::WinApplication* app, x86::reg32 handle)
{
    return x86::sreg32(handle) >= 0 && handle <= at(app, kFileCount);
}

x86::reg32 osHandle(win32::WinApplication* app, x86::reg32 handle)
{
    return at(app, at(app, kOsHandles) + 4 * handle);
}

/* The file's lock taken or given back. */
bool fileLock(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 slot, x86::reg32 handle)
{
    cpu.eax = handle;
    return call(app, cpu, at(app, slot));
}

/* The default windowing's window for the handle, if it has one and `hook`
 * is set: _WindowsIsWindowedHandle's. */
bool windowOf(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 hook, x86::reg32 handle, x86::reg32& window)
{
    window = 0;
    if (at(app, hook) == 0)
        return true;
    cpu.eax = handle;
    if (!call(app, cpu, at(app, kIsWindowedHandle)))
        return false;
    window = cpu.eax;
    return true;
}

/* isatty's: 1 for a window's handle or a character device's, under the lock. */
bool isTty(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32& result)
{
    x86::reg32 window;
    if (!fileLock(app, cpu, kAccessFile, handle) || !windowOf(app, cpu, kIsWindowedHandle, handle, window))
        return false;
    result = 1;
    if (window == 0)
    {
        if (!call(app, cpu, at(app, kGetFileType), {osHandle(app, handle)}))
            return false;
        result = cpu.eax == 2 ? 1 : 0;  // FILE_TYPE_CHAR
    }
    return fileLock(app, cpu, kReleaseFile, handle);
}

/* __GetIOMode's: 0 past __NFiles; for the first three, isatty asked the
 * first time and the answer kept in the mode. */
bool ioMode(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32& mode)
{
    mode = 0;
    if (handle >= at(app, kFileCount))
        return true;
    if (x86::sreg32(handle) < 3 && !(byte(app, at(app, kIoModes) + 4 * handle + 1) & (kInitialized >> 8)))
    {
        const x86::reg32 flags = at(app, kIoModes) + 4 * handle + 1;
        putByte(app, flags, byte(app, flags) | (kInitialized >> 8));
        x86::reg32 tty;
        if (!isTty(app, cpu, handle, tty))
            return false;
        if (tty != 0)
        {
            const x86::reg32 again = at(app, kIoModes) + 4 * handle + 1;
            putByte(app, again, byte(app, again) | (kIsTty >> 8));
        }
    }
    mode = at(app, at(app, kIoModes) + 4 * handle);
    return true;
}

/* __SetIOMode's: a mode set, initialized unless 0. */
void setIoMode(win32::WinApplication* app, x86::reg32 handle, x86::reg32 mode)
{
    put(app, at(app, kIoModes) + 4 * handle, mode != 0 ? mode | kInitialized : 0);
}

/* What a handle's function makes of a bad one: errno EBADF, -1. */
bool badHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32& result)
{
    result = 0xffffffff;
    return setThreadWord(app, cpu, kErrno, kEBADF);
}

}  // namespace

/* __GetIOMode (clib/handleio/c/iomode.c, 0x522de0): eax's mode. */
void GetIOMode(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 mode;
    if (!ioMode(app, cpu, cpu.eax, mode))
        return;
    kept.back(cpu);
    returns(cpu, mode);
}

/* __SetIOMode (clib/handleio/c/iomode.c, 0x522e38): eax's mode edx; eax
 * left 4 times the handle, as its code leaves it. */
void SetIOMode(win32::WinApplication* app, x86::CPU& cpu)
{
    setIoMode(app, cpu.eax, cpu.edx);
    returns(cpu, cpu.eax << 2);
}

/* isatty (clib/environ/c/isattwnt.c, 0x523560): whether eax is a
 * character device's, or a window's. */
void isatty(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!isTty(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* lseek (clib/handleio/c/lseek.c, 0x5028e0): SetFilePointer on eax, edx bytes
 * from where ebx says; a move forward marks the mode extended unless it is
 * appending.  The new place, or -1. */
void lseek(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    const x86::reg32 handle = cpu.eax, offset = cpu.edx, whence = cpu.ebx;
    x86::reg32 result;
    if (!goodHandle(app, handle))
    {
        if (!badHandle(app, cpu, result))
            return;
    }
    else
    {
        x86::reg32 mode;
        if (!fileLock(app, cpu, kAccessFile, handle) || !ioMode(app, cpu, handle, mode))
            return;
        if (x86::sreg32(offset) > 0 && !(mode & kAppend))
            setIoMode(app, handle, mode | kExtended);
        if (!call(app, cpu, at(app, kSetFilePointer), {osHandle(app, handle), offset, 0, whence}))
            return;
        result = cpu.eax;
        if (!fileLock(app, cpu, kReleaseFile, handle) || (result == 0xffffffff && !setErrnoNt(app, cpu)))
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

/* _tell (clib/handleio/c/tell.c, 0x502960): eax's place, or -1. */
void tell(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    const x86::reg32 handle = cpu.eax;
    x86::reg32 result;
    if (!goodHandle(app, handle))
    {
        if (!badHandle(app, cpu, result))
            return;
    }
    else
    {
        const x86::reg32 os = osHandle(app, handle);  // before the lock, as its code reads it
        if (!fileLock(app, cpu, kAccessFile, handle) || !call(app, cpu, at(app, kSetFilePointer), {os, 0, 0, 1}))
            return;
        result = cpu.eax;
        if (!fileLock(app, cpu, kReleaseFile, handle) || (result == 0xffffffff && !setErrnoNt(app, cpu)))
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

namespace
{

/* __qread's and __qwrite's way to a window's: the hook on it, eax the window,
 * edx the buffer, ebx the length; how many it took. */
bool windowTransfer(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 hook, x86::reg32 handle,
                    x86::reg32 window, x86::reg32 buffer, x86::reg32 length, x86::reg32& result)
{
    cpu.eax = window;
    cpu.edx = buffer;
    cpu.ebx = length;
    if (!call(app, cpu, at(app, hook)))
        return false;
    result = cpu.eax;
    return fileLock(app, cpu, kReleaseFile, handle);
}

bool readHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32 buffer, x86::reg32 length,
          x86::reg32 local, x86::reg32& result)
{
    if (!goodHandle(app, handle))
        return badHandle(app, cpu, result);
    x86::reg32 window;
    if (!fileLock(app, cpu, kAccessFile, handle) || !windowOf(app, cpu, kWindowsStdin, handle, window))
        return false;
    if (window != 0)
        return windowTransfer(app, cpu, kWindowsStdin, handle, window, buffer, length, result);
    if (!call(app, cpu, at(app, kReadFile), {osHandle(app, handle), buffer, length, local, 0}))
        return false;
    const bool done = cpu.eax != 0;
    result = done ? at(app, local) : 0xffffffff;
    return fileLock(app, cpu, kReleaseFile, handle) && (done || setErrnoNt(app, cpu));
}

bool writeHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32 buffer, x86::reg32 length,
           x86::reg32 local, x86::reg32& result)
{
    if (!goodHandle(app, handle))
        return badHandle(app, cpu, result);
    const x86::reg32 os = osHandle(app, handle);  // before the lock, as its code reads it
    x86::reg32 mode, window;
    if (!fileLock(app, cpu, kAccessFile, handle) || !ioMode(app, cpu, handle, mode))
        return false;
    if (mode & kAppend)
    {
        if (!call(app, cpu, at(app, kSetFilePointer), {os, 0, 0, 2}))
            return false;
        if (cpu.eax == 0xffffffff)
        {
            result = 0xffffffff;
            return fileLock(app, cpu, kReleaseFile, handle) && setErrnoNt(app, cpu);
        }
    }
    if (!windowOf(app, cpu, kWindowsStdout, handle, window))
        return false;
    if (window != 0)
        return windowTransfer(app, cpu, kWindowsStdout, handle, window, buffer, length, result);
    if (!call(app, cpu, at(app, kWriteFile), {os, buffer, length, local, 0}))
        return false;
    if (cpu.eax == 0)
    {
        result = 0xffffffff;
        return fileLock(app, cpu, kReleaseFile, handle) && setErrnoNt(app, cpu);
    }
    result = at(app, local);
    return (result == length || setThreadWord(app, cpu, kErrno, kENOSPC))
           && fileLock(app, cpu, kReleaseFile, handle);
}

}  // namespace

/* __qread (clib/handleio/c/qread.c, 0x502a50): ebx bytes from eax into edx --
 * a window's by _WindowsStdin, else by ReadFile; how many, or -1. */
void qread(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    cpu.esp = entry - 0xc;  // ecx, esi; how many were read
    x86::reg32 result;
    if (!readHandle(app, cpu, cpu.eax, cpu.edx, cpu.ebx, entry - 0xc, result))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* __qwrite (clib/handleio/c/qwrit.c, 0x5096c0): ebx bytes from edx to eax --
 * at the end, if it is appending; a window's by _WindowsStdout, else by
 * WriteFile, errno ENOSPC for fewer.  How many, or -1. */
void qwrite(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    cpu.esp = entry - 0x14;  // ecx, esi, edi, ebp; how many were written
    x86::reg32 result;
    if (!writeHandle(app, cpu, cpu.eax, cpu.edx, cpu.ebx, entry - 0x14, result))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* ---- Time (clib/time/c): a struct tm in guest memory is nine ints -- sec,
 * min, hour, mday, mon, year since 1900, wday, yday, isdst.  The time zone
 * is the runtime's, __tzset's: still the game's code, called where the
 * runtime calls it.  The structs these keep on their stacks are where their
 * frames have them. ---- */

namespace
{

constexpr x86::reg32 kTzset = 0x515c2c;        // __tzset: the zone from TZ, or from Windows
constexpr x86::reg32 kTimezone = 0x568b94;     // timezone: seconds west of UTC
constexpr x86::reg32 kDstAdjust = 0x568b9c;    // __dst_adjust: seconds daylight saving takes off
constexpr x86::reg32 kDstName = 0x568b90;      // tzname[1]: no daylight saving while it is ""
constexpr x86::reg32 kDstStart = 0x568a40, kDstEnd = 0x568a64;  // its rules, a struct tm each
constexpr x86::reg32 kDaysInYear = 0x552148, kDaysInLeapYear = 0x552162;  // __diyr, __dilyr: shorts
constexpr x86::reg32 kGetLocalTime = 0x534538;
constexpr x86::reg32 kDaysTo1970 = 0x63df;     // from 1 January 1900
constexpr x86::reg32 kDay = 86400;
enum TmField : x86::reg32
{
    kSec = 0, kMin = 4, kHour = 8, kMday = 0xc, kMon = 0x10, kYear = 0x14, kWday = 0x18, kYday = 0x1c,
    kIsdst = 0x20,
};

x86::sreg32 field(win32::WinApplication* app, x86::reg32 tm, TmField f)
{
    return x86::sreg32(at(app, tm + f));
}

/* __diyr's or __dilyr's entry, a short; the index as the runtime's code
 * scales it. */
x86::sreg32 daysBefore(win32::WinApplication* app, x86::reg32 table, x86::reg32 month)
{
    return x86::sreg16(app->getMemory<x86::reg16>(table + 2 * month));
}

/* __leapyear (clib/time/c/leapyear.c). */
bool leapYear(x86::reg32 year)
{
    if (year & 3)
        return false;
    return year % 100 != 0 || year % 400 == 0;
}

x86::reg32 yearTable(x86::reg32 year)
{
    return leapYear(year + 1900) ? kDaysInLeapYear : kDaysInYear;
}

/* __brktime (clib/time/c/gmtime.c): `seconds` seconds `zone` west into day
 * `days` broken down into the struct tm, all but isdst.  Its years are
 * found by 366 a year, then a year's length at a time -- the first year's
 * length each time, as its code does. */
x86::reg32 breakTime(win32::WinApplication* app, x86::reg32 days, x86::reg32 seconds, x86::reg32 zone, x86::reg32 tm)
{
    if (seconds < 0xa8c0 && x86::sreg32(zone) > 0)
    {
        seconds = seconds + kDay - zone;
        days += seconds / kDay - 1;
    }
    else
    {
        seconds -= zone;
        days += seconds / kDay;
    }
    x86::reg32 rest = seconds % kDay;
    put(app, tm + kHour, rest / 3600);
    rest %= 3600;
    put(app, tm + kMin, rest / 60);
    put(app, tm + kSec, rest % 60);
    x86::reg32 year = days / 366;
    x86::reg32 day = days - 365 * year;
    if (year != 0)
        day -= (year - 1) >> 2;
    const x86::reg32 length = (leapYear(year + 1900) ? 1 : 0) + 365;
    while (day >= length)
    {
        day -= length;
        ++year;
    }
    put(app, tm + kYear, year);
    put(app, tm + kYday, day);
    const x86::reg32 table = yearTable(year);
    x86::reg32 month = day / 31;
    if (day >= x86::reg32(daysBefore(app, table, month + 1)))
        ++month;
    put(app, tm + kMon, month);
    put(app, tm + kMday, day - daysBefore(app, table, month) + 1);
    put(app, tm + kWday, (days + 1) % 7);
    return tm;
}

/* time_less (clib/time/c/timeutil.c): whether a's time of day is before b's. */
bool timeLess(win32::WinApplication* app, x86::reg32 a, x86::reg32 b)
{
    if (field(app, a, kHour) != field(app, b, kHour))
        return field(app, a, kHour) < field(app, b, kHour);
    if (field(app, a, kMin) != field(app, b, kMin))
        return field(app, a, kMin) < field(app, b, kMin);
    return field(app, a, kSec) < field(app, b, kSec);
}

bool makeTime(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 tm, x86::reg32& result);

/* calc_yday (clib/time/c/timeutil.c): the day of `year` a daylight saving
 * rule falls on -- Jn, n or Mm.w.d, as its isdst says; mktime asked for the
 * weekday the month begins on, with a struct tm of its frame. */
bool ruleDay(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 rule, x86::reg32 year,
             x86::sreg32& result)
{
    const x86::sreg32 kind = field(app, rule, kIsdst);
    if (kind != 0)
    {
        result = x86::sreg32(at(app, rule + kYday) - (kind == 1 ? 1 : 0));
        return true;
    }
    const x86::reg32 month = at(app, rule + kMon);
    const x86::reg32 table = yearTable(year);
    const x86::sreg32 monthDays = daysBefore(app, table, month + 1) - daysBefore(app, table, month);
    const x86::reg32 first = entry - 0x38;  // ebx, ecx, esi, edi, ebp; the struct tm
    put(app, first + kSec, 0);
    put(app, first + kMin, 0);
    put(app, first + kHour, 0);
    put(app, first + kMday, 1);
    put(app, first + kMon, month);
    put(app, first + kYear, year);
    put(app, first + kIsdst, 0);
    x86::reg32 ignored;
    if (!makeTime(app, cpu, first - 4, first, ignored))
        return false;
    // The rule's fields are anything: its sums wrap as the x86's do.
    const x86::reg32 firstWday = x86::reg32(x86::sreg32(at(app, rule + kWday) - at(app, first + kWday) + 7) % 7);
    const x86::reg32 week = at(app, rule + kMday);
    x86::reg32 nth = week - 1;
    if (week == 5 && x86::sreg32(firstWday + 1 + 28) > monthDays)
        nth = week - 2;
    result = x86::sreg32(7 * nth + at(app, first + kYday) + firstWday);
    return true;
}

/* check_order (clib/time/c/timeutil.c): whether daylight saving starts after
 * it ends in `year` -- the southern hemisphere. */
bool rulesReversed(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 start, x86::reg32 end,
                   x86::reg32 year, bool& result)
{
    if (field(app, start, kIsdst) == 0 && field(app, end, kIsdst) == 0
        && field(app, start, kMon) != field(app, end, kMon))
    {
        result = field(app, start, kMon) > field(app, end, kMon);
        return true;
    }
    const x86::reg32 esp = entry - 0xc;  // ecx, esi, edi
    x86::sreg32 startDay, endDay;
    if (!ruleDay(app, cpu, esp - 4, start, year, startDay) || !ruleDay(app, cpu, esp - 4, end, year, endDay))
        return false;
    result = startDay > endDay;
    return true;
}

/* __isindst's test of one rule (clib/time/c/timeutil.c): whether the day is
 * past the rule's day, and whether it is that day, its time to be compared. */
void ruleDayPassed(win32::WinApplication* app, x86::reg32 tm, x86::reg32 rule, x86::sreg32 monthDays, bool start,
                   bool& dst, bool& timeCheck)
{
    timeCheck = false;
    if (field(app, rule, kIsdst) == 0)
    {
        const x86::sreg32 month = field(app, tm, kMon), ruleMonth = field(app, rule, kMon);
        if (month > ruleMonth)
        {
            dst = start;
            return;
        }
        if (month != ruleMonth)
            return;
        if (!start)
            dst = false;
        // The rule's fields are anything: its sums wrap as the x86's do.
        const x86::reg32 mday = at(app, tm + kMday), wday = at(app, tm + kWday), ruleWday = at(app, rule + kWday);
        const x86::sreg32 n1 = x86::sreg32(mday - x86::reg32(x86::sreg32(wday + 7 - ruleWday) % 7));
        const x86::sreg32 n2 = x86::sreg32(mday - 1 - x86::reg32(x86::sreg32(wday + 6 - ruleWday) % 7));
        const x86::reg32 week = at(app, rule + kMday);
        const bool lastWeek = week == 5;
        const x86::sreg32 limit = lastWeek ? monthDays - 7 : x86::sreg32(7 * (week - 1) + 1);
        const bool n1Past = lastWeek ? n1 > limit : n1 >= limit;
        const bool n2Past = lastWeek ? n2 > limit : n2 >= limit;
        if (start)
        {
            if (n1Past)
            {
                dst = true;
                timeCheck = !n2Past;
            }
        }
        else if (!n1Past)
        {
            dst = true;
        }
        else
        {
            timeCheck = !n2Past;
        }
        return;
    }
    x86::reg32 n1 = at(app, rule + kYday);
    if (field(app, rule, kIsdst) == 1)
    {
        if (leapYear(at(app, tm + kYear) + 1900) && x86::sreg32(n1) > daysBefore(app, kDaysInYear, 2))
            ++n1;
        --n1;
    }
    if (field(app, tm, kYday) >= x86::sreg32(n1))
    {
        dst = start;
        timeCheck = at(app, tm + kYday) == n1;
    }
}

/* __isindst (clib/time/c/timeutil.c): whether the struct tm is in daylight
 * saving, by the zone's rules, into its isdst; none while tzname[1] is "". */
bool inDst(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 tm, x86::reg32& result)
{
    bool dst = false;
    if (byte(app, at(app, kDstName)) != 0)
    {
        bool south;
        if (!rulesReversed(app, cpu, entry - 0x34 - 4, kDstStart, kDstEnd, at(app, tm + kYear), south))
            return false;  // ebx, ecx, edx, esi, edi, ebp, and 0x1c of its own
        const x86::reg32 start = south ? kDstEnd : kDstStart, end = south ? kDstStart : kDstEnd;
        const x86::reg32 table = yearTable(at(app, tm + kYear));
        const x86::reg32 month = at(app, tm + kMon);
        const x86::sreg32 monthDays = daysBefore(app, table, month + 1) - daysBefore(app, table, month);
        bool timeCheck;
        ruleDayPassed(app, tm, start, monthDays, true, dst, timeCheck);
        if (timeCheck)
            dst = !timeLess(app, tm, start);
        if (dst)
        {
            ruleDayPassed(app, tm, end, monthDays, false, dst, timeCheck);
            if (timeCheck)
                dst = timeLess(app, tm, end);
        }
        if (south)
            dst = !dst;
    }
    result = dst ? 1 : 0;
    put(app, tm + kIsdst, result);
    return true;
}

/* mktime (clib/time/c/mktime.c): the struct tm made a time_t, and put right
 * -- months past 11, seconds past 59 and the like -- by __brktime; isdst
 * found by __isindst if it is negative; -1 before 1970, or for a year too
 * far back to count. */
bool makeTime(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 tm, x86::reg32& result)
{
    // Its sums wrap as the x86's do: the fields are anything.
    const x86::reg32 esp = entry - 0x1c;  // ebx, ecx, edx, esi, edi, ebp, and a dword
    result = 0xffffffff;
    x86::sreg32 month = field(app, tm, kMon) % 12;
    if (field(app, tm, kYear) < x86::sreg32(0xf4fb7ea1))
        return true;
    x86::reg32 year = at(app, tm + kYear) + x86::reg32(field(app, tm, kMon) / 12);
    while (month < 0)
    {
        month += 12;
        --year;
    }
    if (x86::sreg32(year) < 0)
        return true;
    const x86::reg32 table = yearTable(year);
    x86::reg32 days = x86::reg32(x86::sreg32(year + 3) / 4) + 365 * year
                      - x86::reg32(x86::sreg32(year + 0x63) / 100) + x86::reg32(x86::sreg32(year + 0x12b) / 400);
    days = x86::reg32(daysBefore(app, table, month)) + days + at(app, tm + kMday) - 1;
    x86::reg32 seconds = at(app, tm + kSec) + 60 * (at(app, tm + kMin) + 60 * at(app, tm + kHour));
    while (x86::sreg32(seconds) < 0)
    {
        seconds += kDay;
        --days;
    }
    breakTime(app, days, seconds, 0, tm);
    cpu.esp = esp;
    if (!call(app, cpu, kTzset))
        return false;
    seconds += at(app, kTimezone);
    if (field(app, tm, kIsdst) < 0)
    {
        x86::reg32 ignored;
        if (!inDst(app, cpu, esp - 4, tm, ignored))
            return false;
    }
    if (field(app, tm, kIsdst) > 0)
        seconds -= at(app, kDstAdjust);
    while (x86::sreg32(seconds) < 0)
    {
        --days;
        seconds += kDay;
    }
    if (x86::sreg32(days) < x86::sreg32(kDaysTo1970 - 1))
        return true;
    if (days == kDaysTo1970 - 1)
    {
        seconds -= kDay;
        if (x86::sreg32(at(app, kTimezone)) > 0 && x86::sreg32(seconds) >= 0)
            result = seconds;
        return true;
    }
    result = seconds + (days - kDaysTo1970) * kDay;
    return true;
}

/* __getctime (clib/time/c/gtctmwnt.c): GetLocalTime's into the struct tm,
 * isdst -1; its milliseconds. */
bool currentTime(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 tm, x86::reg32& result)
{
    const x86::reg32 local = entry - 0x1c;  // ebx, ecx, edx; a SYSTEMTIME
    cpu.esp = local;
    if (!call(app, cpu, at(app, kGetLocalTime), {local}))
        return false;
    auto word16 = [app, local](x86::reg32 offset) { return x86::reg32(app->getMemory<x86::reg16>(local + offset)); };
    put(app, tm + kYear, word16(0) - 1900);
    put(app, tm + kMon, word16(2) - 1);
    put(app, tm + kMday, word16(6));
    put(app, tm + kHour, word16(8));
    put(app, tm + kMin, word16(0xa));
    put(app, tm + kIsdst, 0xffffffff);
    put(app, tm + kSec, word16(0xc));
    result = word16(0xe);
    return true;
}

/* _localtime's (clib/time/c/localtim.c): *timer broken down in the zone,
 * again with daylight saving's hour if it is in it. */
bool localTime(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry, x86::reg32 timer, x86::reg32 tm)
{
    cpu.esp = entry - 0x10;  // ebx, ecx, esi, edi
    if (!call(app, cpu, kTzset))
        return false;
    const x86::reg32 seconds = at(app, timer);
    breakTime(app, kDaysTo1970, seconds, at(app, kTimezone), tm);
    x86::reg32 dst;
    if (!inDst(app, cpu, entry - 0x14, tm, dst))
        return false;
    if (dst != 0)
        breakTime(app, kDaysTo1970, seconds, at(app, kTimezone) - at(app, kDstAdjust), tm);
    return true;
}

}  // namespace

/* __leapyear (clib/time/c/leapyear.c, 0x5160f0): whether year eax is a leap
 * year. */
void leapyear(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    returns(cpu, leapYear(cpu.eax) ? 1 : 0);
}

/* __brktime (clib/time/c/gmtime.c, 0x515fa0): edx seconds ebx west into day
 * eax since 1900 broken down into the struct tm at ecx; that. */
void brktime(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, breakTime(app, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx));
}

/* time_less (clib/time/c/timeutil.c, 0x51652c): whether the struct tm at
 * eax's time of day is before edx's. */
void time_less(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, timeLess(app, cpu.eax, cpu.edx) ? 1 : 0);
}

/* calc_yday (clib/time/c/timeutil.c, 0x51612c): the day of year edx the rule
 * at eax falls on. */
void calc_yday(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::sreg32 day;
    if (!ruleDay(app, cpu, entry, cpu.eax, cpu.edx, day))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, day);
}

/* check_order (clib/time/c/timeutil.c, 0x516224): whether the rule at eax
 * falls after edx's in year ebx. */
void check_order(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    bool reversed;
    if (!rulesReversed(app, cpu, entry, cpu.eax, cpu.edx, cpu.ebx, reversed))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, reversed ? 1 : 0);
}

/* __isindst (clib/time/c/timeutil.c, 0x516270): the struct tm at eax's isdst
 * by the zone's rules; that. */
void isindst(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 dst;
    if (!inDst(app, cpu, entry, cpu.eax, dst))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, dst);
}

/* mktime (clib/time/c/mktime.c, 0x50eba0): the struct tm at eax made a
 * time_t, and put right. */
void mktime(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 result;
    if (!makeTime(app, cpu, entry, cpu.eax, result))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* __getctime (clib/time/c/gtctmwnt.c, 0x50eb30): the local time into the
 * struct tm at eax; its milliseconds. */
void getctime(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    x86::reg32 milliseconds;
    if (!currentTime(app, cpu, entry, cpu.eax, milliseconds))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, milliseconds);
}

/* time (clib/time/c/time.c, 0x4f22b0): now, a second on from half of one,
 * as a time_t -- into eax's too, if there is one. */
void time(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 timer = cpu.eax;
    const x86::reg32 tm = entry - 0x2c;  // ebx, edx; the struct tm
    x86::reg32 milliseconds, result;
    if (!currentTime(app, cpu, tm - 4, tm, milliseconds))
        return;
    if (x86::sreg32(milliseconds) >= 500)
        put(app, tm + kSec, at(app, tm + kSec) + 1);
    if (!makeTime(app, cpu, tm - 4, tm, result))
        return;
    if (timer != 0)
        put(app, timer, result);
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, result);
}

/* _localtime (clib/time/c/localtim.c, 0x4f8040): *eax broken down into the
 * struct tm at edx; that. */
void localtime_(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 tm = cpu.edx;
    if (!localTime(app, cpu, entry, cpu.eax, tm))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, tm);
}

/* localtime (clib/time/c/localtim.c, 0x4f8094): *eax broken down into the
 * thread's struct tm; that. */
void localtime(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const Kept kept(cpu);
    const x86::reg32 timer = cpu.eax;
    x86::reg32 data;
    cpu.esp = entry - 8;  // ebx, edx
    if (!threadData(app, cpu, data))
        return;
    const x86::reg32 tm = data + 0x14;
    if (!localTime(app, cpu, entry - 0xc, timer, tm))
        return;
    kept.back(cpu);
    cpu.esp = entry;
    returns(cpu, tm);
}

/* ---- The x87's maths (mathlib): each of its instructions the same
 * operation of the port's x87 as the generated code has for it, in the same
 * order -- its constants too, fldpi's and fldl2e's doubles -- so that the
 * results are its to the bit in either FPU, and the register stack, the
 * control word and the status word are left as its code leaves them; eax
 * too, where fnstsw and sahf leave a byte of the status word in it.  A math
 * error goes to __math87_err, and on to __reporterror, still the game's
 * code: its struct exception, _matherr, errno.  On a Pentium with the FDIV
 * bug (__chipbug's bit 0) IF@DATAN2 goes to __fpatan_wrap, the game's code
 * too. ---- */

namespace
{

constexpr x86::reg32 kChipBug = 0x567858;      // __chipbug
constexpr x86::reg32 kFpatanWrap = 0x4ff624;   // __fpatan_wrap
constexpr x86::reg32 kReportError = 0x5243a7;  // __reporterror
constexpr x86::reg32 k8087 = 0x5644c0;         // _8087: whether there is an x87
constexpr x86::reg32 kMinusOne = 0x54c970;     // floor's -1.0
constexpr x86::reg32 kExpMax = 0x56716c, kExpMin = 0x567174;  // exp's limits, doubles
constexpr x86::reg32 kHalfPi = 0x56719c;       // IF@DACOS's pi/2, 80 bits
constexpr x86::reg32 kEDOM = 13;
constexpr double kLog2e = 1.4426950408889634;  // fldl2e, as the port loads it
constexpr double kPi = 3.1415926535897932;     // fldpi
/* sahf's carry and zero: C0 and C3. */
constexpr x86::reg16 kC0 = 0x100, kC3 = 0x4000;

x86::Float loadDouble(win32::WinApplication* app, x86::reg32 address)
{
    return x86::Float(app->getMemory<double>(address));
}

void storeDouble(win32::WinApplication* app, x86::reg32 address, const x86::Float& value)
{
    app->getMemory<double>(address) = double(value);
}

void pushFloat(x86::CPU& cpu, const x86::Float& value)
{
    cpu.fpu.count += 1;
    cpu.fpu.st(0) = value;
}

void setAh(x86::CPU& cpu, x86::reg16 status)
{
    cpu.eax = (cpu.eax & 0xffff00ff) | (status & 0xff00);
}

/* modf's: the double at `argument` into its integer part, at `whole`, and
 * its fraction on the stack. */
void splitDouble(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 argument, x86::reg32 whole)
{
    const x86::Float value = loadDouble(app, argument);
    cpu.fpu.count += 2;
    cpu.fpu.st(0) = value;
    cpu.fpu.st(1) = value;
    chop(cpu);
    const x86::Float fraction = cpu.fpu.sub(cpu.fpu.st(1), cpu.fpu.st(0));
    storeDouble(app, whole, cpu.fpu.st(0));
    cpu.fpu.count -= 1;
    cpu.fpu.st(0) = fraction;
}

/* floor's: the double at `argument` rounded down, by modf, its integer part
 * at `whole`. */
void roundDown(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 argument, x86::reg32 whole)
{
    splitDouble(app, cpu, argument, whole);
    cpu.fpu.compare(0.0, cpu.fpu.st(0));
    cpu.fpu.count -= 1;
    if (!(cpu.fpu.status.word & (kC0 | kC3)))
        storeDouble(app, whole, cpu.fpu.add(loadDouble(app, whole), loadDouble(app, kMinusOne)));
    pushFloat(cpu, loadDouble(app, whole));
}

bool mathError(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry);

/* __@DSQRT's: st(0)'s root; a negative one, or none, __math87_err's, al the
 * caller's function -- st(1) dropped too unless it is sqrt's (3).  al 0, or
 * 1. */
bool squareRoot(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry)
{
    put(app, entry - 4, cpu.ebp);
    cpu.fpu.compare(cpu.fpu.st(0), 0.0);
    const x86::reg16 status = cpu.fpu.status.word;
    const x86::reg32 slot = entry - 0xc;  // fnstsw's word, which xchg gives ax for
    app->getMemory<x86::reg16>(slot) = x86::reg16(cpu.eax);
    if (!(status & kC0))
    {
        cpu.fpu.st(0) = cpu.fpu.sqrt(cpu.fpu.st(0));
        cpu.eax = (cpu.eax & 0xffff0000) | (status & 0xff00);
        return true;
    }
    const x86::reg32 argument = entry - 0x14;
    storeDouble(app, argument, cpu.fpu.st(0));
    cpu.fpu.count -= 1;
    cpu.eax = at(app, slot);
    if (x86::reg8(cpu.eax) != 3)
    {
        storeDouble(app, argument, cpu.fpu.st(0));
        cpu.fpu.count -= 1;
    }
    put(app, entry - 8, cpu.edx);
    cpu.esp = argument;
    if (!mathError(app, cpu, argument - 4))
        return false;
    cpu.eax = (cpu.eax & 0xffffff00) | 1;
    return true;
}

/* IF@DATAN2's: atan2 of st(1) by st(0), fpatan's. */
bool arcTangent(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry)
{
    std::swap(cpu.fpu.st(0), cpu.fpu.st(1));
    if (byte(app, kChipBug) & 1)
    {
        cpu.esp = entry;
        return call(app, cpu, kFpatanWrap);
    }
    const x86::Float angle = cpu.fpu.atan(cpu.fpu.st(0), cpu.fpu.st(1));
    cpu.fpu.count -= 1;
    cpu.fpu.st(0) = angle;
    return true;
}

/* __math87_err's: the double at entry + 4 and the function at entry + 0xc,
 * its byte, made __reporterror's flags -- or, for exp's underflow, 0 -- and
 * what it gives back pushed. */
bool mathError(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry)
{
    const x86::reg32 argument = entry + 4;
    const x86::reg32 result = entry - 0x1c;  // ebp, eax, ebx, ecx, edx; a double
    const x86::reg32 eax = cpu.eax, ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    const x86::reg8 function = byte(app, entry + 0xc);
    x86::reg32 flags = 0;
    bool underflow = false;
    if (function >= 1 && function <= 3)
    {
        flags = 0x2000 | (function | 0x40);
    }
    else
    {
        if (function == 4)
        {
            cpu.fpu.compare(0.0, loadDouble(app, argument));
            underflow = !(cpu.fpu.status.word & (kC0 | kC3));
        }
        if (!underflow)
        {
            flags = 0x8100 | function;
            if (function == 6)
            {
                cpu.fpu.compare(0.0, loadDouble(app, argument));
                if (!(cpu.fpu.status.word & (kC0 | kC3)))
                    flags = 0x1100 | function;
            }
        }
    }
    if (underflow)
    {
        put(app, result, 0);
        put(app, result + 4, 0);
    }
    else
    {
        cpu.eax = flags;
        cpu.edx = argument;
        cpu.esp = result;
        if (!call(app, cpu, kReportError))
            return false;
        storeDouble(app, result, cpu.fpu.st(0));
        cpu.fpu.count -= 1;
    }
    pushFloat(cpu, loadDouble(app, result));
    cpu.eax = eax;
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
    cpu.esp = entry + 0x10;
    return true;
}

/* IF@DEXP's: e to st(0), al 4, exp's: by fldl2e, frndint, f2xm1 and fscale;
 * past the largest double __math87_err's, below the smallest 0.  al 0, or 1;
 * ah fnstsw's last. */
bool exponential(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 entry)
{
    cpu.eax = (cpu.eax & 0xffffff00) | 4;
    put(app, entry - 4, cpu.ebp);
    cpu.fpu.compare(cpu.fpu.st(0), loadDouble(app, kExpMax));
    setAh(cpu, cpu.fpu.status.word);
    if (!(cpu.fpu.status.word & (kC0 | kC3)))
    {
        const x86::reg32 argument = entry - 0x14;
        storeDouble(app, argument, cpu.fpu.st(0));
        put(app, entry - 0xc, cpu.eax);
        put(app, entry - 8, cpu.edx);
        cpu.fpu.count -= 1;
        cpu.esp = argument;
        if (!mathError(app, cpu, argument - 4))
            return false;
        cpu.eax = (cpu.eax & 0xffffff00) | 1;
        return true;
    }
    cpu.fpu.compare(cpu.fpu.st(0), loadDouble(app, kExpMin));
    setAh(cpu, cpu.fpu.status.word);
    if (cpu.fpu.status.word & (kC0 | kC3))
    {
        pushFloat(cpu, 0.0);
    }
    else
    {
        const x86::Float scaled = cpu.fpu.mul(cpu.fpu.st(0), kLog2e);
        const x86::Float whole = cpu.fpu.rndint(scaled);
        const x86::Float fraction = cpu.fpu.sub(scaled, whole);
        const x86::Float power = cpu.fpu.add(cpu.fpu.f2xm1(fraction), 1.0);
        cpu.fpu.count += 1;
        cpu.fpu.st(0) = cpu.fpu.scale(power, whole);
        cpu.fpu.st(1) = whole;
    }
    const x86::Float result = cpu.fpu.st(0);
    cpu.fpu.count -= 1;
    cpu.fpu.st(0) = result;
    cpu.eax &= 0xffffff00;
    return true;
}

}  // namespace

/* IF@DATAN2 (mathlib/a/atan87.asm, 0x4e06d9): atan2 of st(1) by st(0), into
 * st(0). */
void IF_DATAN2(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    if (!arcTangent(app, cpu, entry))
        return;
    cpu.esp = entry + 4;
}

/* floor (mathlib/c/floor.c, 0x4f1c30): the double on the stack rounded
 * down, onto the x87's; stdcall. */
void floor(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    roundDown(app, cpu, entry + 4, entry - 0x18);  // ebp, eax, ebx, edx; the integer part
    cpu.esp = entry + 0xc;
}

/* ceil (mathlib/c/ceil.c, 0x4f2d78): -floor(-x). */
void ceil(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const x86::reg32 negated = entry - 0x10;  // ebp, eax; floor's argument
    storeDouble(app, negated, -loadDouble(app, entry + 4));
    roundDown(app, cpu, negated, negated - 4 - 0x18);
    cpu.fpu.st(0) = -cpu.fpu.st(0);
    cpu.esp = entry + 0xc;
}

/* modf (0x50ea4e): the double on the stack into its integer part, at the
 * pointer after it, and its fraction, onto the x87's; stdcall. */
void modf(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    splitDouble(app, cpu, entry + 4, at(app, entry + 0xc));
    cpu.esp = entry + 0x10;
}

/* _control87 (clib/fpu/c/cntrl87.c, 0x4f7c90): the control word's bits of
 * edx made eax's, if there is an x87 (_8087); the control word, or 0. */
void control87(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 word = 0;
    if (byte(app, k8087) != 0)
    {
        word = cpu.fpu.control.word;
        const x86::reg32 mask = cpu.edx;
        if (mask != 0)
        {
            word = (~mask & word) | (mask & cpu.eax);
            cpu.fpu.setControl(x86::reg16(word));
            word = (word & 0xffff0000) | cpu.fpu.control.word;
        }
    }
    returns(cpu, word & 0xffff);
}

/* IF@DEXP (0x4f80b4): e to st(0), into st(0). */
void IF_DEXP(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    if (!exponential(app, cpu, entry))
        return;
    cpu.esp = entry + 4;
}

/* exp (mathlib/a/exp87.asm, 0x4f8116): e to the double on the stack, onto
 * the x87's; stdcall. */
void exp(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    pushFloat(cpu, loadDouble(app, entry + 4));
    if (!exponential(app, cpu, entry - 4))
        return;
    cpu.esp = entry + 0xc;
}

/* IF@DACOS (mathlib/a/acos87.asm, 0x4f9482): acos of st(0) -- atan2 of
 * sqrt(1 - x*x) by x, from pi/2; 0 or pi for 1 and -1 -- into st(0). */
void IF_DACOS(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    const x86::reg32 saved = entry - 4;  // push ax: the port's code takes a dword for it
    app->getMemory<x86::reg16>(saved) = x86::reg16(cpu.eax);
    cpu.esp = saved;
    const x86::Float x = cpu.fpu.st(0);
    const x86::Float rest = cpu.fpu.sub(1.0, cpu.fpu.mul(x, x));
    cpu.fpu.compare(rest, 0.0);
    cpu.eax = (cpu.eax & 0xffff0000) | cpu.fpu.status.word;
    pushFloat(cpu, rest);
    if (cpu.fpu.status.word & kC3)
    {
        cpu.fpu.compare(cpu.fpu.st(0), cpu.fpu.st(1));
        cpu.eax = (cpu.eax & 0xffff0000) | cpu.fpu.status.word;
        cpu.fpu.count -= 2;
        pushFloat(cpu, cpu.fpu.status.word & (kC0 | kC3) ? x86::Float(0.0) : x86::Float(kPi));
    }
    else
    {
        cpu.eax = (cpu.eax & 0xffffff00) | 1;
        if (!squareRoot(app, cpu, saved - 4))
            return;
        cpu.esp = saved;
        if (x86::reg8(cpu.eax) == 0)
        {
            std::swap(cpu.fpu.st(0), cpu.fpu.st(1));
            if (!arcTangent(app, cpu, saved - 4))
                return;
            cpu.esp = saved;
            const x86::Float halfPi = x86::Float(app->getMemory<x86::IEEEf80>(kHalfPi));
            cpu.fpu.st(0) = cpu.fpu.sub(halfPi, cpu.fpu.st(0));
        }
    }
    cpu.eax = (cpu.eax & 0xffff0000) | app->getMemory<x86::reg16>(saved);
    cpu.esp = entry + 4;
}

/* __@DSQRT (mathlib, 0x51a1ba): st(0)'s root, al the caller's function; al
 * 0, or 1 for a math error. */
void DSQRT(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 entry = cpu.esp;
    if (!squareRoot(app, cpu, entry))
        return;
    cpu.esp = entry + 4;
}

/* __math87_err (0x51655c): a math error -- the argument, a double, and the
 * function, a byte of the dword after it, on the stack -- reported; what
 * _matherr or the runtime gives back onto the x87's.  Takes its arguments
 * off. */
void math87_err(win32::WinApplication* app, x86::CPU& cpu)
{
    mathError(app, cpu, cpu.esp);
}

/* __set_EDOM (0x502890): errno EDOM. */
void set_EDOM(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!setThreadWord(app, cpu, kErrno, kEDOM))
        return;
    const x86::reg32 data = cpu.eax;
    kept.back(cpu);
    returns(cpu, data);
}

/* ---- Streams (clib/streamio/c): a FILE is the runtime's, in guest memory
 * -- _ptr, _cnt, _link, _flag, _handle, _bufsize, _ungotten, _tmpfchar --
 * and its __stream_link has the buffer, the orientation and the extended
 * flags; __OpenStreams lists the links.  Each function takes the file's
 * lock where its code does, the handle in eax, and goes down to the
 * handles' functions (__qread, __qwrite, lseek, _tell, isatty) and the
 * heap's where its code does, with esp where its frame has it: __qread and
 * __qwrite hand Windows a dword of their own frames.  The flags' bits each
 * changes are the ones its code changes. ---- */

namespace
{

constexpr x86::reg32 kPtr = 0, kCnt = 4, kLink = 8, kFlag = 0xc, kFileHandle = 0x10, kBufsize = 0x14;
constexpr x86::reg32 kUngotten = 0x18;
constexpr x86::reg32 kLinkNext = 0, kLinkStream = 4, kLinkBase = 8, kOrientation = 0xc, kExtFlags = 0x10;
constexpr x86::reg32 kOpenStreams = 0x9f38a0;                      // __OpenStreams: their links
constexpr x86::reg32 kAccessIob = 0x567778, kReleaseIob = 0x56777c;  // the streams' lock
constexpr x86::reg32 kFlushFileBuffers = 0x5344d4;
constexpr x86::reg32 kGetche = 0x522e60;  // the console's getche: still the game's
/* _flag's bits. */
constexpr x86::reg32 kReading = 0x1, kWriting = 0x2, kUnget = 0x4, kBigBuf = 0x8, kAtEof = 0x10, kError = 0x20;
constexpr x86::reg32 kBinary = 0x40;  // and _APPEND a mode's kAppend
constexpr x86::reg32 kFullBuf = 0x100, kLineBuf = 0x200, kNoBuf = 0x400, kBuffering = 0x700;
constexpr x86::reg32 kDirty = 0x1000, kTty = 0x2000;
constexpr x86::reg32 kCommit = 1;  // the link's extended flags

/* A function's frame as its code makes it -- the registers it pushes, its
 * locals -- esp that far down while it calls what it calls. */
class Frame
{
public:
    Frame(x86::CPU& cpu, x86::reg32 size) : cpu_(cpu), entry_(cpu.esp) { cpu.esp = entry_ - size; }
    ~Frame() { cpu_.esp = entry_; }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    x86::CPU& cpu_;
    const x86::reg32 entry_;
};

/* One of these called from another as its code calls it: the return
 * address's slot below the caller's frame. */
template <typename Function>
bool nested(x86::CPU& cpu, Function function)
{
    const Frame slot(cpu, 4);
    return function();
}

x86::reg32 linkOf(win32::WinApplication* app, x86::reg32 fp)
{
    return at(app, fp + kLink);
}

x86::reg32 bufferOf(win32::WinApplication* app, x86::reg32 fp)
{
    return at(app, linkOf(app, fp) + kLinkBase);
}

x86::reg32 flags(win32::WinApplication* app, x86::reg32 fp)
{
    return at(app, fp + kFlag);
}

void setFlags(win32::WinApplication* app, x86::reg32 fp, x86::reg32 set, x86::reg32 clear = 0)
{
    put(app, fp + kFlag, (flags(app, fp) & ~clear) | set);
}

bool streamLock(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 slot, x86::reg32 fp)
{
    return fileLock(app, cpu, slot, at(app, fp + kFileHandle));
}

/* The buffer emptied: _cnt 0, _ptr its start, read first. */
x86::reg32 emptyBuffer(win32::WinApplication* app, x86::reg32 fp)
{
    const x86::reg32 base = bufferOf(app, fp);
    put(app, fp + kCnt, 0);
    put(app, fp + kPtr, base);
    return base;
}

/* fsync's (clib/handleio/c/fsync.c): FlushFileBuffers under the lock; 0, or
 * -1. */
bool syncHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32& result)
{
    const Frame frame(cpu, 0x10);  // ebx, ecx, edx, esi
    if (!goodHandle(app, handle))
        return badHandle(app, cpu, result);
    result = 0;
    if (!fileLock(app, cpu, kAccessFile, handle)
        || !call(app, cpu, at(app, kFlushFileBuffers), {osHandle(app, handle)}))
        return false;
    if (cpu.eax == 0)
    {
        result = 0xffffffff;
        if (!setErrnoNt(app, cpu))
            return false;
    }
    return fileLock(app, cpu, kReleaseFile, handle);
}

/* __chktty's: a tty's stream marked one, and line-buffered unless it is
 * buffered some way already; eax as its code leaves it. */
bool checkTty(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp)
{
    const Frame frame(cpu, 0xc);  // ebx, ecx, edx
    cpu.eax = fp;
    if (flags(app, fp) & kTty)
        return true;
    cpu.eax = at(app, fp + kFileHandle);
    if (!call(app, cpu, isatty))
        return false;
    if (cpu.eax != 0)
    {
        setFlags(app, fp, kTty);
        if (!(flags(app, fp) & kBuffering))
            setFlags(app, fp, kLineBuf);
    }
    return true;
}

/* __ioalloc's: a buffer from _nmalloc -- _bufsize's, or 0x86 bytes
 * line-buffered, 1 unbuffered, 4K -- or, for none, _ungotten, unbuffered. */
bool allocateBuffer(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp)
{
    const Frame frame(cpu, 0xc);  // ebx, ecx, edx
    if (!nested(cpu, [&] { return checkTty(app, cpu, fp); }))
        return false;
    if (at(app, fp + kBufsize) == 0)
    {
        const x86::reg32 f = flags(app, fp);
        put(app, fp + kBufsize, f & kLineBuf ? 0x86 : f & kNoBuf ? 1 : 0x1000);
    }
    cpu.eax = at(app, fp + kBufsize);
    if (!call(app, cpu, nmalloc))
        return false;
    put(app, linkOf(app, fp) + kLinkBase, cpu.eax);
    if (bufferOf(app, fp) == 0)
    {
        setFlags(app, fp, kNoBuf, kBuffering);
        put(app, linkOf(app, fp) + kLinkBase, fp + kUngotten);
        put(app, fp + kBufsize, 1);
    }
    else
    {
        setFlags(app, fp, kBigBuf);
    }
    cpu.eax = emptyBuffer(app, fp);
    return true;
}

/* __flush's: a written buffer to __qwrite, all of it -- ENOSPC for none
 * taken; a read one's unread part seeked back over, unless it is a tty's;
 * the buffer emptied, and committed if the link says so.  0, or -1. */
bool flushStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x18);  // ebx, ecx, edx, esi, edi, ebp
    result = 0;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    if (flags(app, fp) & kDirty)
    {
        setFlags(app, fp, 0, kDirty);
        x86::reg32 from = bufferOf(app, fp);
        if ((flags(app, fp) & kWriting) && from != 0)
        {
            for (x86::reg32 left = at(app, fp + kCnt); left != 0 && result == 0;)
            {
                cpu.eax = at(app, fp + kFileHandle);
                cpu.edx = from;
                cpu.ebx = left;
                if (!call(app, cpu, qwrite))
                    return false;
                const x86::reg32 written = cpu.eax;
                if (written == 0xffffffff)
                {
                    setFlags(app, fp, kError);
                    result = written;
                }
                else if (written == 0)
                {
                    if (!setThreadWord(app, cpu, kErrno, kENOSPC))
                        return false;
                    setFlags(app, fp, kError);
                    result = 0xffffffff;
                }
                from += written;
                left -= written;
            }
        }
    }
    else if (bufferOf(app, fp) != 0)
    {
        setFlags(app, fp, 0, kAtEof);
        if (!(flags(app, fp) & kTty))
        {
            x86::reg32 place = 0;
            if (at(app, fp + kCnt) != 0)
            {
                cpu.eax = at(app, fp + kFileHandle);
                cpu.edx = 0 - at(app, fp + kCnt);
                cpu.ebx = 1;  // SEEK_CUR
                if (!call(app, cpu, lseek))
                    return false;
                place = cpu.eax;
            }
            if (place == 0xffffffff)
            {
                setFlags(app, fp, kError);
                result = place;
            }
        }
    }
    emptyBuffer(app, fp);
    if (result == 0 && (at(app, linkOf(app, fp) + kExtFlags) & kCommit))
    {
        x86::reg32 synced;
        if (!nested(cpu, [&] { return syncHandle(app, cpu, at(app, fp + kFileHandle), synced); }))
            return false;
        if (synced == 0xffffffff)
            result = synced;
    }
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* fputc's: c into the buffer -- '\n' after a '\r' in text -- flushed when
 * it fills, or for a line or a character as the stream is buffered; a
 * stream of wide characters takes none, one not open for writing is EBADF.
 * The character, or -1. */
bool putChar(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 c, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x14);  // ebx, ecx, esi, edi, ebp
    result = 0xffffffff;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    const x86::reg32 link = linkOf(app, fp);
    const x86::reg32 orientation = at(app, link + kOrientation);
    if (orientation != 1)
    {
        if (orientation != 0)
            return streamLock(app, cpu, kReleaseFile, fp);
        put(app, link + kOrientation, 1);
    }
    if (!(flags(app, fp) & kWriting))
    {
        if (!setThreadWord(app, cpu, kErrno, kEBADF))
            return false;
        setFlags(app, fp, kError);
        return streamLock(app, cpu, kReleaseFile, fp);
    }
    if (bufferOf(app, fp) == 0 && !nested(cpu, [&] { return allocateBuffer(app, cpu, fp); }))
        return false;
    auto put1 = [&](x86::reg8 byte_) {
        setFlags(app, fp, kDirty);
        putByte(app, at(app, fp + kPtr), byte_);
        put(app, fp + kPtr, at(app, fp + kPtr) + 1);
        put(app, fp + kCnt, at(app, fp + kCnt) + 1);
    };
    x86::reg32 flushOn = kNoBuf;
    if (c == '\n')
    {
        flushOn = kNoBuf | kLineBuf;
        if (!(flags(app, fp) & kBinary))
        {
            put1('\r');
            if (at(app, fp + kCnt) == at(app, fp + kBufsize))
            {
                x86::reg32 flushed;
                if (!nested(cpu, [&] { return flushStream(app, cpu, fp, flushed); }))
                    return false;
                if (flushed != 0)
                    return streamLock(app, cpu, kReleaseFile, fp);
            }
        }
    }
    put1(x86::reg8(c));
    if ((flags(app, fp) & flushOn) || at(app, fp + kCnt) == at(app, fp + kBufsize))
    {
        x86::reg32 flushed;
        if (!nested(cpu, [&] { return flushStream(app, cpu, fp, flushed); }))
            return false;
        if (flushed != 0)
            return streamLock(app, cpu, kReleaseFile, fp);
    }
    result = c & 0xff;
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* fputs's: the string by fputc, an unbuffered stream line-buffered while
 * it goes and flushed after; how many, or -1. */
bool putString(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 string, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x14);  // ebx, ecx, esi, edi, ebp
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    if (bufferOf(app, fp) == 0 && !nested(cpu, [&] { return allocateBuffer(app, cpu, fp); }))
        return false;
    const bool unbuffered = flags(app, fp) & kNoBuf;
    if (unbuffered)
        setFlags(app, fp, kLineBuf, kLineBuf | kNoBuf);
    result = 0;
    x86::reg32 at_ = string;
    for (; byte(app, at_) != 0; ++at_)
    {
        x86::reg32 put_;
        if (!nested(cpu, [&] { return putChar(app, cpu, byte(app, at_), fp, put_); }))
            return false;
        if (put_ == 0xffffffff)
        {
            result = put_;
            break;
        }
    }
    if (unbuffered)
    {
        setFlags(app, fp, kNoBuf, kLineBuf | kNoBuf);
        if (result == 0 && !nested(cpu, [&] { return flushStream(app, cpu, fp, result); }))
            return false;
    }
    if (result == 0)
        result = at_ - string;
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* __flushall's: every open stream with a bit of `mask` counted, and flushed
 * if it is dirty, under the streams' lock -- given back with eax as the walk
 * leaves it: the mask, the last stream, or what flushing it gave. */
bool flushAll(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 mask, x86::reg32& count)
{
    const Frame frame(cpu, 0xc);  // ebx, ecx, edx
    cpu.eax = mask;
    if (!call(app, cpu, at(app, kAccessIob)))
        return false;
    count = 0;
    x86::reg32 eax = mask;
    for (x86::reg32 link = at(app, kOpenStreams); link != 0; link = at(app, link + kLinkNext))
    {
        const x86::reg32 fp = eax = at(app, link + kLinkStream);
        if (!(flags(app, fp) & mask))
            continue;
        ++count;
        if ((flags(app, fp) & kDirty) && !nested(cpu, [&] { return flushStream(app, cpu, fp, eax); }))
            return false;
    }
    cpu.eax = eax;
    return call(app, cpu, at(app, kReleaseIob));
}

/* fwrite's: n of size bytes -- binary, into the buffer, or straight to
 * __qwrite in whole 512s when the buffer is empty and they fill it; text,
 * by fputc, an unbuffered stream fully buffered while it goes -- until an
 * error; the stream's EOF and error as they were, and its new error.  How
 * many whole ones. */
bool writeStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 buffer, x86::reg32 size, x86::reg32 n,
                 x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x20);  // esi, edi, ebp; five dwords
    result = 0;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    if (!(flags(app, fp) & kWriting))
    {
        if (!setThreadWord(app, cpu, kErrno, kEBADF))
            return false;
        setFlags(app, fp, kError);
        return streamLock(app, cpu, kReleaseFile, fp);
    }
    const x86::reg32 total = n * size;
    if (total == 0)
        return streamLock(app, cpu, kReleaseFile, fp);
    if (bufferOf(app, fp) == 0 && !nested(cpu, [&] { return allocateBuffer(app, cpu, fp); }))
        return false;
    const x86::reg32 kept = flags(app, fp) & (kAtEof | kError);
    setFlags(app, fp, 0, kAtEof | kError);
    x86::reg32 written = 0;
    if (flags(app, fp) & kBinary)
    {
        for (x86::reg32 left = total;;)
        {
            x86::reg32 step;
            if (at(app, fp + kCnt) == 0 && left >= at(app, fp + kBufsize))
            {
                x86::reg32 direct = left & 0xfffffe00;
                if (direct == 0)
                    direct = left;
                cpu.eax = at(app, fp + kFileHandle);
                cpu.edx = buffer;
                cpu.ebx = direct;
                if (!call(app, cpu, qwrite))
                    return false;
                step = cpu.eax;
                if (step == 0)
                {
                    x86::reg32 data;
                    if (!threadData(app, cpu, data))
                        return false;
                    put(app, data + kErrno, kENOSPC);
                }
                if (step == 0 || step == 0xffffffff)
                    setFlags(app, fp, kError);
            }
            else
            {
                // rep movsd, then rep movsb: by dwords where they overlap.
                step = std::min(at(app, fp + kBufsize) - at(app, fp + kCnt), left);
                const x86::reg32 to = at(app, fp + kPtr);
                x86::reg32 i = 0;
                for (; i < (step & ~3u); i += 4)
                    put(app, to + i, at(app, buffer + i));
                for (; i < step; ++i)
                    putByte(app, to + i, byte(app, buffer + i));
                put(app, fp + kCnt, at(app, fp + kCnt) + step);
                put(app, fp + kPtr, at(app, fp + kPtr) + step);
                setFlags(app, fp, kDirty);
                if (at(app, fp + kCnt) == at(app, fp + kBufsize) || (flags(app, fp) & kNoBuf))
                {
                    x86::reg32 ignored;
                    if (!nested(cpu, [&] { return flushStream(app, cpu, fp, ignored); }))
                        return false;
                }
            }
            buffer += step;
            written += step;
            left -= step;
            if (left == 0 || (flags(app, fp) & kError))
                break;
        }
    }
    else
    {
        const bool unbuffered = flags(app, fp) & kNoBuf;
        if (unbuffered)
            setFlags(app, fp, kFullBuf, kFullBuf | kNoBuf);
        const x86::reg32 link = linkOf(app, fp);
        const x86::reg32 orientation = at(app, link + kOrientation);
        put(app, link + kOrientation, 1);
        for (;;)
        {
            x86::reg32 ignored;
            if (!nested(cpu, [&] { return putChar(app, cpu, byte(app, buffer++), fp, ignored); }))
                return false;
            if (flags(app, fp) & (kAtEof | kError))
                break;
            if (++written == total)
                break;
        }
        put(app, linkOf(app, fp) + kOrientation, orientation);
        if (unbuffered)
        {
            setFlags(app, fp, kNoBuf, kFullBuf | kNoBuf);
            x86::reg32 ignored;
            if (!nested(cpu, [&] { return flushStream(app, cpu, fp, ignored); }))
                return false;
        }
    }
    if (flags(app, fp) & kError)
        written = 0;
    setFlags(app, fp, kept);
    if (!streamLock(app, cpu, kReleaseFile, fp))
        return false;
    result = written / size;
    return true;
}

/* __update_buffer's (clib/streamio/c/fseek.c): a seek `diff` from where the
 * stream is, within what is buffered -- back to the buffer's start, on to
 * what is left in it -- done there, the end of the file cleared, and 0; 1
 * for one outside it. */
x86::reg32 updateBuffer(win32::WinApplication* app, x86::reg32 diff, x86::reg32 fp)
{
    if (x86::sreg32(diff) > x86::sreg32(at(app, fp + kCnt))
        || x86::sreg32(diff) < x86::sreg32(bufferOf(app, fp) - at(app, fp + kPtr)))
        return 1;
    const x86::reg32 ptr = at(app, fp + kPtr) + diff, cnt = at(app, fp + kCnt) - diff;
    setFlags(app, fp, 0, kAtEof);
    put(app, fp + kPtr, ptr);
    put(app, fp + kCnt, cnt);
    return 0;
}

/* __reset_buffer's: the end of the file cleared and the buffer emptied. */
void resetBuffer(win32::WinApplication* app, x86::reg32 fp)
{
    setFlags(app, fp, 0, kAtEof);
    emptyBuffer(app, fp);
}

/* __fill_buffer's (clib/streamio/c/fgetc.c): the buffer filled by __qread
 * -- a byte for an unbuffered stream -- from where it starts, the ttys'
 * streams flushed first if this is a tty's line by line or unbuffered; an
 * unbuffered tty's handle 0 by the console's getche.  How many are in it:
 * none at the end of the file, none and an error for one. */
bool fillBuffer(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& count)
{
    const Frame frame(cpu, 0x10);  // ebx, ecx, edx, esi
    if (bufferOf(app, fp) == 0 && !nested(cpu, [&] { return allocateBuffer(app, cpu, fp); }))
        return false;
    if ((flags(app, fp) & kTty) && (flags(app, fp) & (kLineBuf | kNoBuf)))
    {
        x86::reg32 ignored;
        if (!nested(cpu, [&] { return flushAll(app, cpu, kTty, ignored); }))
            return false;
    }
    setFlags(app, fp, 0, kUnget);
    put(app, fp + kPtr, bufferOf(app, fp));
    if ((flags(app, fp) & (kTty | kNoBuf)) == (kTty | kNoBuf) && at(app, fp + kFileHandle) == 0)
    {
        put(app, fp + kCnt, 0);
        if (!call(app, cpu, kGetche))
            return false;
        if (cpu.eax != 0xffffffff)
        {
            putByte(app, at(app, fp + kPtr), x86::reg8(cpu.eax));
            put(app, fp + kCnt, 1);
        }
    }
    else
    {
        cpu.ebx = flags(app, fp) & kNoBuf ? 1 : at(app, fp + kBufsize);
        cpu.edx = at(app, fp + kPtr);
        cpu.eax = at(app, fp + kFileHandle);
        if (!call(app, cpu, qread))
            return false;
        put(app, fp + kCnt, cpu.eax);
    }
    const x86::sreg32 cnt = x86::sreg32(at(app, fp + kCnt));
    if (cnt == 0)
    {
        setFlags(app, fp, kAtEof);
    }
    else if (cnt < 0)
    {
        put(app, fp + kCnt, 0);
        setFlags(app, fp, kError);
    }
    count = at(app, fp + kCnt);
    return true;
}

/* __filbuf's: the buffer filled, and its first byte taken; -1 for none. */
bool fillAndTake(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& c)
{
    const Frame frame(cpu, 0xc);  // ebx, ecx, edx
    x86::reg32 count;
    if (!nested(cpu, [&] { return fillBuffer(app, cpu, fp, count); }))
        return false;
    c = 0xffffffff;
    if (count != 0)
    {
        const x86::reg32 cnt = at(app, fp + kCnt) - 1, ptr = at(app, fp + kPtr) + 1;
        put(app, fp + kCnt, cnt);
        put(app, fp + kPtr, ptr);
        c = byte(app, ptr - 1);
    }
    return true;
}

/* A byte of the buffer, as fgetc takes one: _cnt down, and the buffer
 * filled when that leaves it below 0. */
bool takeChar(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& c)
{
    const x86::reg32 cnt = at(app, fp + kCnt) - 1;
    put(app, fp + kCnt, cnt);
    if (x86::sreg32(cnt) < 0)
        return nested(cpu, [&] { return fillAndTake(app, cpu, fp, c); });
    const x86::reg32 ptr = at(app, fp + kPtr);
    c = byte(app, ptr);
    put(app, fp + kPtr, ptr + 1);
    return true;
}

/* fgetc's: a byte of the stream -- in text a '\r' dropped for the byte
 * after it, ^Z its end -- or -1; a stream of wide characters gives none,
 * one not open for reading is EBADF. */
bool getChar(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x14);  // ebx, ecx, edx, esi, ebp
    result = 0xffffffff;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    const x86::reg32 link = linkOf(app, fp);
    const x86::reg32 orientation = at(app, link + kOrientation);
    if (orientation != 1)
    {
        if (orientation != 0)
            return streamLock(app, cpu, kReleaseFile, fp);
        put(app, link + kOrientation, 1);
    }
    x86::reg32 c = 0xffffffff;
    if (!(flags(app, fp) & kReading))
    {
        if (!setThreadWord(app, cpu, kErrno, kEBADF))
            return false;
        setFlags(app, fp, kError);
    }
    else if (!takeChar(app, cpu, fp, c))
    {
        return false;
    }
    if (!(flags(app, fp) & kBinary))
    {
        if (c == '\r' && !takeChar(app, cpu, fp, c))
            return false;
        if (c == 0x1a)
        {
            setFlags(app, fp, kAtEof);
            c = 0xffffffff;
        }
    }
    result = c;
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* fread's: n of size bytes -- binary, what the buffer has, then straight
 * from __qread in whole 512s (unless the stream is unbuffered) while as many
 * as the buffer holds are left, through the buffer otherwise; text, by the
 * byte, each '\r' dropped for the byte after it, up to a ^Z, its end -- until
 * the end of the file or an error.  How many whole ones. */
bool readStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 buffer, x86::reg32 size, x86::reg32 n,
                x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x1c);  // esi, edi, ebp; four dwords
    result = 0;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    if (!(flags(app, fp) & kReading))
    {
        if (!setThreadWord(app, cpu, kErrno, kEBADF))
            return false;
        setFlags(app, fp, kError);
        return streamLock(app, cpu, kReleaseFile, fp);
    }
    const x86::reg32 total = n * size;
    if (total == 0)
        return streamLock(app, cpu, kReleaseFile, fp);
    if (bufferOf(app, fp) == 0 && !nested(cpu, [&] { return allocateBuffer(app, cpu, fp); }))
        return false;
    x86::reg32 read = 0;
    if (flags(app, fp) & kBinary)
    {
        for (x86::reg32 left = total;;)
        {
            const x86::reg32 cnt = at(app, fp + kCnt);
            if (cnt != 0)
            {
                // rep movsd, then rep movsb: by dwords where they overlap.
                const x86::reg32 step = std::min(cnt, left);
                const x86::reg32 from = at(app, fp + kPtr);
                x86::reg32 i = 0;
                for (; i < (step & ~3u); i += 4)
                    put(app, buffer + i, at(app, from + i));
                for (; i < step; ++i)
                    putByte(app, buffer + i, byte(app, from + i));
                const x86::reg32 ptr = at(app, fp + kPtr) + step, rest = at(app, fp + kCnt) - step;
                buffer += step;
                read += step;
                left -= step;
                put(app, fp + kPtr, ptr);
                put(app, fp + kCnt, rest);
            }
            if (left == 0)
                break;
            if (left >= at(app, fp + kBufsize) || (flags(app, fp) & kNoBuf))
            {
                const x86::reg32 base = bufferOf(app, fp);
                put(app, fp + kCnt, 0);
                x86::reg32 asked = left;
                const bool unbuffered = flags(app, fp) & kNoBuf;
                put(app, fp + kPtr, base);
                if (!unbuffered && asked > 0x200)
                    asked &= 0xfffffe00;
                cpu.ebx = asked;
                cpu.edx = buffer;
                cpu.eax = at(app, fp + kFileHandle);
                if (!call(app, cpu, qread))
                    return false;
                if (cpu.eax == 0xffffffff)
                {
                    setFlags(app, fp, kError);
                    break;
                }
                if (cpu.eax == 0)
                {
                    setFlags(app, fp, kAtEof);
                    break;
                }
                buffer += cpu.eax;
                left -= cpu.eax;
                read += cpu.eax;
            }
            else
            {
                x86::reg32 count;
                if (!nested(cpu, [&] { return fillBuffer(app, cpu, fp, count); }))
                    return false;
                if (count == 0)
                    break;
            }
        }
    }
    else
    {
        // Each byte as fgetc's code takes one, but for filling the buffer
        // only once it is empty.
        auto take = [&](x86::reg32& c) {
            if (at(app, fp + kCnt) == 0)
            {
                x86::reg32 count;
                if (!nested(cpu, [&] { return fillBuffer(app, cpu, fp, count); }))
                    return false;
                if (count == 0)
                    return c = 0xffffffff, true;
            }
            const x86::reg32 cnt = at(app, fp + kCnt) - 1, ptr = at(app, fp + kPtr);
            put(app, fp + kCnt, cnt);
            put(app, fp + kPtr, ptr + 1);
            c = byte(app, ptr);
            return true;
        };
        for (const x86::reg32 end = buffer + total; buffer != end;)
        {
            x86::reg32 c;
            if (!take(c))
                return false;
            if (c == '\r' && !take(c))
                return false;
            if (c == 0xffffffff)
                break;
            if (c == 0x1a)
            {
                setFlags(app, fp, kAtEof);
                break;
            }
            putByte(app, buffer++, x86::reg8(c));
            ++read;
        }
    }
    if (!streamLock(app, cpu, kReleaseFile, fp))
        return false;
    result = read / size;
    return true;
}

/* fgets's: bytes by fgetc into the buffer, up to n - 1 of them and a '\n',
 * and a 0 after; none for the end of the file before any, or an error.  The
 * stream's end and error as they were, and new ones.  fgetc's last result is
 * kept in a dword of its frame, whatever was there for none. */
bool getString(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 buffer, x86::reg32 n, x86::reg32 fp,
               x86::reg32& result)
{
    const Frame frame(cpu, 0x14);  // ecx, esi, edi, ebp; a dword
    x86::reg32 c = at(app, cpu.esp);
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    const x86::reg32 kept = flags(app, fp) & (kAtEof | kError);
    setFlags(app, fp, 0, kAtEof | kError);
    x86::reg32 to = buffer;
    for (x86::reg32 left = n - 1; x86::sreg32(left) > 0; --left)
    {
        if (!nested(cpu, [&] { return getChar(app, cpu, fp, c); }))
            return false;
        if (c == 0xffffffff)
            break;
        putByte(app, to++, x86::reg8(c));
        if (x86::reg8(c) == '\n')
            break;
    }
    result = buffer;
    if (c == 0xffffffff && (to == buffer || (flags(app, fp) & kError)))
        result = 0;
    else
        putByte(app, to, 0);
    setFlags(app, fp, kept);
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* fseek's: a stream open for writing, or with a byte put back, flushed and
 * its buffer given up, then lseek -- for SEEK_CUR from where the stream is,
 * not the handle; one for reading moved within its buffer where it can be,
 * by lseek and the buffer emptied otherwise.  0, or -1, EINVAL for a
 * whence that is none, and for a flush that failed on a SEEK_SET before 0. */
bool seekStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32 offset, x86::reg32 whence,
                x86::reg32& result)
{
    const Frame frame(cpu, 0xc);  // ecx, esi, edi
    result = 0xffffffff;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    auto invalid = [&] {
        return setThreadWord(app, cpu, kErrno, kEINVAL) && streamLock(app, cpu, kReleaseFile, fp);
    };
    auto seek = [&](x86::reg32 to, bool reset) {
        cpu.ebx = whence;
        cpu.edx = to;
        cpu.eax = at(app, fp + kFileHandle);
        if (!call(app, cpu, lseek))
            return false;
        if (cpu.eax == 0xffffffff)
            return streamLock(app, cpu, kReleaseFile, fp);
        if (reset)
            resetBuffer(app, fp);
        result = 0;
        return streamLock(app, cpu, kReleaseFile, fp);
    };
    const x86::reg32 f = flags(app, fp);
    if (f & (kWriting | kUnget))
    {
        if (flags(app, fp) & kDirty)
        {
            x86::reg32 flushed;
            if (!nested(cpu, [&] { return flushStream(app, cpu, fp, flushed); }))
                return false;
            if (flushed != 0)
            {
                if (whence == 0 && x86::sreg32(offset) < 0)
                    return invalid();
                return streamLock(app, cpu, kReleaseFile, fp);
            }
        }
        else
        {
            if (whence == 1)
                offset -= at(app, fp + kCnt);
            emptyBuffer(app, fp);
        }
        setFlags(app, fp, 0, kUnget | kAtEof);
        return seek(offset, false);
    }
    if (whence == 1)
    {
        const x86::reg32 cnt = at(app, fp + kCnt);
        if (updateBuffer(app, offset, fp) == 0)
            return result = 0, streamLock(app, cpu, kReleaseFile, fp);
        return seek(offset - cnt, true);
    }
    if (whence == 0)
    {
        cpu.eax = at(app, fp + kFileHandle);
        if (!call(app, cpu, tell))
            return false;
        if (updateBuffer(app, offset - (cpu.eax - at(app, fp + kCnt)), fp) == 0)
            return result = 0, streamLock(app, cpu, kReleaseFile, fp);
        return seek(offset, true);
    }
    if (whence == 2)
    {
        const x86::reg32 link = linkOf(app, fp);
        setFlags(app, fp, 0, kAtEof);
        put(app, fp + kPtr, at(app, link + kLinkBase));
        put(app, fp + kCnt, 0);
        return seek(offset, false);
    }
    return invalid();
}

/* ftell's: where the stream is -- _tell's place, less what is left to read
 * of the buffer, or more what is written to it; a stream appended to and
 * dirty flushed first. */
bool tellStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0x10);  // ebx, ecx, edx, esi
    if ((flags(app, fp) & kAppend) && (flags(app, fp) & kDirty))
    {
        x86::reg32 ignored;
        if (!nested(cpu, [&] { return flushStream(app, cpu, fp, ignored); }))
            return false;
    }
    cpu.eax = at(app, fp + kFileHandle);
    if (!call(app, cpu, tell))
        return false;
    result = cpu.eax;
    if (result == 0xffffffff)
        return true;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    const x86::reg32 cnt = at(app, fp + kCnt);
    if (cnt != 0)
        result = flags(app, fp) & kDirty ? result + cnt : result - cnt;
    return streamLock(app, cpu, kReleaseFile, fp);
}

/* ---- Opening and closing: a FILE of __iob's or the heap's, its link on
 * __OpenStreams, and a handle -- __OSHandles' first free, Windows' HANDLE in
 * it -- by CreateFileA; and back. ---- */

constexpr x86::reg32 kClosedStreams = 0x9f38a4;               // the links of streams closed, to be used again
constexpr x86::reg32 kIobEnd = 0x567160;                      // past __iob's 20
constexpr x86::reg32 kIobStart = 0x566f58, kFileSize = 0x1a, kLinkSize = 0x1d;
constexpr x86::reg32 kDynamic = 0x4000, kTmpFile = 0x800;     // _flag's: the heap's FILE; tmpfile's
constexpr x86::reg32 kTmpfChar = 0x14;                        // the link's: a temporary file's number
constexpr x86::reg32 kHandleCount = 0x56acc0;                 // __NHandles: how many __OSHandles has
constexpr x86::reg32 kFakeHandle = 0x56acc4;                  // __NTGetFakeHandle's last
constexpr x86::reg32 kAccessHandles = 0x567798, kReleaseHandles = 0x56779c;  // their lock
constexpr x86::reg32 kAllocHandle = 0x567770, kFreeHandle = 0x567774;        // what calls __allocPOSIXHandle and __freePOSIXHandle
/* The default windowing's other hooks, none in the game. */
constexpr x86::reg32 kRemoveWindowedHandle = 0x5677b4, kNewWindow = 0x5677b8, kDestroyWindow = 0x5677bc;
constexpr x86::reg32 kCommitMode = 0x568260;  // _commode
constexpr x86::reg32 kFileMode = 0x567164;    // _fmode: O_TEXT, or O_BINARY
constexpr x86::reg32 kUmask = 0x56ae60;
constexpr x86::reg32 kConsole = 0x54f6f0;     // "con"
constexpr x86::reg32 kRealloc = 0x5185c0;     // _nrealloc: still the game's
constexpr x86::reg32 kMkTmpFile = 0x4ee168;   // __MkTmpFile: still the game's
constexpr x86::reg32 kCloseHandle = 0x534488, kCreateEventA = 0x534494, kCreateFileA = 0x534498;
constexpr x86::reg32 kEMFILE = 11;
/* open's flags. */
constexpr x86::reg32 kOpenAppend = 0x10, kOpenCreate = 0x20, kOpenTruncate = 0x40, kOpenText = 0x100;
constexpr x86::reg32 kOpenNoInherit = 0x80, kOpenBinary = 0x200, kOpenExclusive = 0x400;

x86::reg32 freeStream(win32::WinApplication* app, x86::reg32 fp);

/* __GetNTAccessAttr's: CreateFileA's access and attributes for a read and
 * write mode. */
void accessAttributes(win32::WinApplication* app, x86::reg32 rwmode, x86::reg32 access, x86::reg32 attributes)
{
    put(app, access, rwmode == 2 ? 0xc0000000 : rwmode == 1 ? 0x40000000 : 0x80000000);
    put(app, attributes, rwmode == 2 || rwmode == 1 ? 0x80 : 1);
}

/* __GetNTShareAttr's: CreateFileA's sharing for SH_COMPAT -- reading, and
 * writing too for a file opened to read -- SH_DENYRW, SH_DENYWR, SH_DENYRD,
 * SH_DENYNO; none written for another.  The sharing bits. */
x86::reg32 shareAttributes(win32::WinApplication* app, x86::reg32 mode, x86::reg32 share)
{
    const x86::reg32 sharing = mode & 0x70;
    switch (sharing)
    {
    case 0x00: put(app, share, (mode & 7) == 0 ? 3 : 1); break;
    case 0x10: put(app, share, 0); break;
    case 0x20: put(app, share, 1); break;
    case 0x30: put(app, share, 2); break;
    case 0x40: put(app, share, 3); break;
    }
    return sharing;
}

/* The one of 0x51e2b0: 1 when __OSHandles is as long as __NFiles and has no
 * slot free, 0 otherwise. */
x86::reg32 handlesFull(win32::WinApplication* app)
{
    const x86::reg32 count = at(app, kHandleCount), table = at(app, kOsHandles);
    if (count < at(app, kFileCount))
        return 0;
    if (x86::sreg32(count) <= 0)
        return 1;
    x86::reg32 offset = 0;
    do
    {
        if (at(app, table + offset) == 0)
            return 0;
        offset += 4;
    } while (x86::sreg32(offset) < x86::sreg32(count << 2));
    return 1;
}

/* __NTGetFakeHandle's: an event's HANDLE, or one past 0x80000000 of the
 * runtime's own. */
bool fakeHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32& handle)
{
    const Frame frame(cpu, 8);  // ecx, edx
    if (!call(app, cpu, at(app, kCreateEventA), {0, 0, 0, 0}))
        return false;
    handle = cpu.eax;
    if (handle == 0)
        put(app, kFakeHandle, handle = at(app, kFakeHandle) + 1);
    return true;
}

/* __allocPOSIXHandle's: the HANDLE into __OSHandles' first free slot, or
 * one more at its end, by _nrealloc, under the handles' lock -- given back
 * with eax the slot's offset, or the table.  Its handle. */
bool allocHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 os, x86::reg32& handle)
{
    const Frame frame(cpu, 0x10);  // ebx, ecx, edx, esi
    cpu.eax = os;
    if (!call(app, cpu, at(app, kAccessHandles)))
        return false;
    const x86::reg32 count = at(app, kHandleCount);
    if (x86::sreg32(count) > 0)
    {
        x86::reg32 offset = 0;
        handle = 0;
        do
        {
            const x86::reg32 slot = at(app, kOsHandles) + offset;
            if (at(app, slot) == 0)
            {
                put(app, slot, os);
                cpu.eax = offset;
                return call(app, cpu, at(app, kReleaseHandles));
            }
            offset += 4;
            ++handle;
        } while (x86::sreg32(offset) < x86::sreg32(count << 2));
    }
    cpu.edx = (at(app, kHandleCount) + 1) << 2;
    cpu.eax = at(app, kOsHandles);
    if (!call(app, cpu, kRealloc))
        return false;
    const x86::reg32 last = at(app, kHandleCount);
    put(app, kOsHandles, cpu.eax);
    put(app, cpu.eax + 4 * last, os);
    put(app, kHandleCount, last + 1);
    if (!call(app, cpu, at(app, kReleaseHandles)))
        return false;
    handle = at(app, kHandleCount) - 1;
    return true;
}

/* __freePOSIXHandle's: a handle's slot free again, but 0's, under the
 * handles' lock; eax as its code leaves it. */
bool freeHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle)
{
    const Frame frame(cpu, 4);  // edx
    cpu.eax = handle;
    if (!call(app, cpu, at(app, kAccessHandles)))
        return false;
    if (x86::sreg32(handle) > 0 && x86::sreg32(handle) < x86::sreg32(at(app, kHandleCount)))
    {
        cpu.eax = handle << 2;
        put(app, at(app, kOsHandles) + cpu.eax, 0);
    }
    return call(app, cpu, at(app, kReleaseHandles));
}

/* __close's: a window's handle's window gone, by the default windowing's
 * hooks, or Windows' HANDLE closed -- EBADF and -1 for one CloseHandle
 * refuses -- and the handle's mode 0.  0, or -1. */
bool closeHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 handle, x86::reg32& result)
{
    const Frame frame(cpu, 0x18);  // ebx, ecx, edx, esi, edi, ebp
    if (!goodHandle(app, handle))
        return badHandle(app, cpu, result);
    result = 0;
    const x86::reg32 destroy = at(app, kDestroyWindow), os = osHandle(app, handle);
    x86::reg32 window = 0;
    if (destroy != 0)
    {
        cpu.eax = handle;
        if (!call(app, cpu, at(app, kIsWindowedHandle)))
            return false;
        window = cpu.eax;
        if (window != 0)
        {
            cpu.eax = handle;
            if (!call(app, cpu, at(app, kRemoveWindowedHandle)))
                return false;
            cpu.eax = window;
            if (!call(app, cpu, at(app, kDestroyWindow)))
                return false;
        }
    }
    if (window == 0)
    {
        if (!call(app, cpu, at(app, kCloseHandle), {os}))
            return false;
        if (cpu.eax == 0)
        {
            result = 0xffffffff;
            return setThreadWord(app, cpu, kErrno, kEBADF);
        }
    }
    cpu.eax = handle;
    cpu.edx = 0;
    return call(app, cpu, SetIOMode);
}

/* __sopen's (clib/handleio/c/openwnt.c): name opened by CreateFileA as the
 * flags say -- created, truncated, exclusively; once more with no security
 * and the second disposition for one to create it could not open -- its
 * permissions from the va_list less the umask; a handle of __OSHandles for
 * it and its mode: read, write, append, binary as the flags or _fmode say,
 * a tty's.  "con" a window of the default windowing's, if it has any.  The
 * handle, or -1 and errno.  Its frame's eight dwords are CreateFileA's
 * SECURITY_ATTRIBUTES, sharing, access, attributes and dispositions, and
 * the flags, read back from there -- the sharing as the frame had it, for
 * one that is none of the five, which __GetNTShareAttr does not write. */
bool openHandle(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 name, x86::reg32 oflag, x86::reg32 shflag,
                x86::reg32 args, x86::reg32& result)
{
    const Frame frame(cpu, 0x2c);  // esi, edi, ebp; eight dwords
    const x86::reg32 local = cpu.esp;
    const x86::reg32 security = local, share = local + 0xc, access = local + 0x10, attributes = local + 0x14;
    const x86::reg32 retry = local + 0x18, flags = local + 0x1c;
    put(app, flags, oflag);
    result = 0xffffffff;
    if (handlesFull(app) != 0)
        return setThreadWord(app, cpu, kErrno, kEMFILE);
    const x86::reg32 rwmode = oflag & 7;
    accessAttributes(app, rwmode, access, attributes);
    shareAttributes(app, shflag | rwmode, share);
    x86::reg32 fileAttributes = 0x80;
    put(app, security + 4, 0);
    put(app, security, 0xc);
    put(app, security + 8, byte(app, flags) & kOpenNoInherit ? 0 : 1);
    x86::reg32 handle, mode = 0;
    bool window = false;
    if (at(app, kNewWindow) != 0)
    {
        cpu.edx = kConsole;
        cpu.eax = name;
        if (!call(app, cpu, stricmp))
            return false;
        if (cpu.eax == 0)
        {
            x86::reg32 fake;
            if (!nested(cpu, [&] { return fakeHandle(app, cpu, fake); }))
                return false;
            cpu.eax = fake;
            if (!call(app, cpu, at(app, kAllocHandle)))
                return false;
            cpu.ebx = 0;
            cpu.edx = 0x2000;
            cpu.ecx = cpu.eax;
            if (!call(app, cpu, at(app, kNewWindow), {0, cpu.eax, 0xffffffff}))
                return false;
            handle = cpu.ecx;
            mode = cpu.edx;
            window = true;
        }
    }
    if (!window)
    {
        x86::reg32 disposition;
        if (byte(app, flags) & kOpenCreate)
        {
            const x86::reg32 va = at(app, args) + 4;
            put(app, args, va);
            put(app, attributes, at(app, va - 4));
            put(app, args, 0);
            put(app, attributes, at(app, attributes) & ~at(app, kUmask));
            if ((byte(app, attributes + 1) & 1) && !(byte(app, attributes) & 0x80))
                fileAttributes = 1;  // FILE_ATTRIBUTE_READONLY
            if (byte(app, flags + 1) & (kOpenExclusive >> 8))
            {
                put(app, retry, 1);  // CREATE_NEW
                disposition = 1;
            }
            else if (byte(app, flags) & kOpenTruncate)
            {
                put(app, retry, 2);  // CREATE_ALWAYS
                disposition = 1;
            }
            else
            {
                put(app, retry, 4);  // OPEN_ALWAYS
                disposition = 3;     // OPEN_EXISTING
            }
        }
        else
        {
            disposition = byte(app, flags) & kOpenTruncate ? 5 : 3;  // TRUNCATE_EXISTING, OPEN_EXISTING
        }
        if (!call(app, cpu, at(app, kCreateFileA),
                  {name, at(app, access), at(app, share), security, disposition, fileAttributes, 0}))
            return false;
        x86::reg32 os = cpu.eax;
        if (os == 0xffffffff && (byte(app, flags) & kOpenCreate))
        {
            if (!call(app, cpu, at(app, kCreateFileA),
                      {name, at(app, access), at(app, share), 0, at(app, retry), fileAttributes, 0}))
                return false;
            os = cpu.eax;
        }
        if (os == 0xffffffff)
            return setErrnoNt(app, cpu);
        cpu.eax = os;
        if (!call(app, cpu, at(app, kAllocHandle)))
            return false;
        handle = cpu.eax;
        if (handle >= at(app, kFileCount))
        {
            if (!call(app, cpu, at(app, kCloseHandle), {os}))
                return false;
            return setThreadWord(app, cpu, kErrno, kENOMEM);
        }
        cpu.eax = handle;
        if (!call(app, cpu, isatty))
            return false;
        if (cpu.eax != 0)
            mode = kIsTty;
    }
    if (rwmode == 2)
        mode |= 3;
    else if (rwmode == 0)
        mode |= 1;
    else if (rwmode == 1)
        mode |= 2;
    if (byte(app, flags) & kOpenAppend)
        mode |= kAppend;
    const x86::reg8 kind = byte(app, flags + 1);
    if (kind & ((kOpenText | kOpenBinary) >> 8) ? (kind & (kOpenBinary >> 8)) != 0 : at(app, kFileMode) == kOpenBinary)
        mode |= kBinary;
    cpu.eax = handle;
    cpu.edx = mode;
    if (!call(app, cpu, SetIOMode))
        return false;
    result = handle;
    return true;
}

/* __open_flags' (clib/streamio/c/fopen.c): a mode string's flags -- 'r',
 * 'w' or 'a' first, then '+', 't' or 'b', 'c' or 'n' each once, anything
 * else let be; one twice ends it there -- binary by _fmode for neither 't'
 * nor 'b'; the extended flags committed as _commode says, or as 'c' and 'n'
 * say.  0 and EINVAL for another first. */
bool openFlags(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 mode, x86::reg32 extflags, x86::reg32& result)
{
    const Frame frame(cpu, 0x18);  // ebx, ecx, esi, edi, ebp; a dword
    if (extflags != 0)
        put(app, extflags, at(app, kCommitMode) == 1 ? 1 : 0);
    x86::reg32 flags;
    switch (byte(app, mode))
    {
    case 'r': flags = kReading; break;
    case 'w': flags = kWriting; break;
    case 'a': flags = kWriting | kAppend; break;
    default:
        result = 0;
        return setThreadWord(app, cpu, kErrno, kEINVAL);
    }
    bool good = true, plus = false, kind = false, commit = false;
    for (x86::reg32 at_ = mode + 1; byte(app, at_) != 0 && good; ++at_)
    {
        switch (byte(app, at_))
        {
        case '+':
            good = !plus;
            if (good)
                flags |= kReading | kWriting, plus = true;
            break;
        case 't':
        case 'b':
            good = !kind;
            if (good && byte(app, at_) == 'b')
                flags |= kBinary;
            kind = true;
            break;
        case 'c':
        case 'n':
            good = !commit;
            if (good)
                putByte(app, extflags, byte(app, at_) == 'c' ? byte(app, extflags) | kCommit : byte(app, extflags) & ~kCommit);
            commit = true;
            break;
        }
    }
    if (!kind && at(app, kFileMode) == kOpenBinary)
        flags |= kBinary;
    result = flags;
    return true;
}

/* __doopen's (clib/streamio/c/fopen.c): the stream's flags, its handle by
 * _sopen -- read, or written, created and truncated or appended to, as the
 * mode's first says, text or binary, 0600 -- its buffer and orientation
 * none, its extended flags; an appended one seeked to its end, a tty's
 * marked.  The stream, or 0, given back, for a handle refused. */
bool doOpen(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 name, x86::reg8 first, x86::reg32 flags,
            x86::reg32 extflags, x86::reg32 shflag, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 0xc);  // esi, edi, ebp
    putByte(app, fp + kFlag, byte(app, fp + kFlag) & ~(kReading | kWriting));
    put(app, fp + kFlag, at(app, fp + kFlag) | flags);
    cpu.eax = first;
    if (!call(app, cpu, tolower))
        return false;
    x86::reg32 oflag = flags & kBinary ? kOpenBinary : kOpenText, permission = 0;
    if (x86::reg8(cpu.eax) == 'r')
    {
        oflag |= flags & kWriting ? 2 : 0;
    }
    else
    {
        oflag |= (flags & kReading ? 2 : 1) | kOpenCreate | (flags & kAppend ? kOpenAppend : kOpenTruncate);
        permission = 0x180;
    }
    if (!call(app, cpu, sopen, {name, oflag, shflag, permission}))
        return false;
    put(app, fp + kFileHandle, cpu.eax);
    result = 0;
    if (at(app, fp + kFileHandle) == 0xffffffff)
    {
        freeStream(app, fp);
        return true;
    }
    put(app, fp + kCnt, 0);
    const x86::reg32 link = linkOf(app, fp);
    put(app, fp + kBufsize, 0);
    put(app, link + kOrientation, 0);
    put(app, linkOf(app, fp) + kExtFlags, extflags);
    put(app, linkOf(app, fp) + 0x15, 0);
    put(app, linkOf(app, fp) + kLinkBase, 0);
    if (flags & kAppend)
    {
        x86::reg32 ignored;
        cpu.ebx = 2;
        cpu.edx = 0;
        if (!nested(cpu, [&] { return seekStream(app, cpu, fp, 0, 2, ignored); }))
            return false;
    }
    if (!nested(cpu, [&] { return checkTty(app, cpu, fp); }))
        return false;
    result = fp;
    return true;
}

/* __allocfp's (clib/streamio/c/allocfp.c): a stream for fopen, under the
 * streams' lock -- the last closed's again; or one of __iob's 20 not in use,
 * a link from the heap for it; or a FILE and its link from the heap -- its
 * FILE cleared, in use, its link first on __OpenStreams; 0 and ENOMEM for
 * none.  The lock is given back with eax as its code leaves it. */
bool allocateStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32& fp)
{
    const Frame frame(cpu, 0x14);  // ebx, ecx, edx, esi, edi
    if (!call(app, cpu, at(app, kAccessIob)))
        return false;
    x86::reg32 link = at(app, kClosedStreams), flag;
    if (link != 0)
    {
        fp = at(app, link + kLinkStream);
        flag = (at(app, fp + kFlag) & (kDynamic | kReading | kWriting)) | kReading | kWriting;
        put(app, kClosedStreams, at(app, link + kLinkNext));
    }
    else
    {
        fp = 0;
        for (x86::reg32 iob = kIobStart; iob < kIobEnd; iob += kFileSize)
            if (!(byte(app, iob + kFlag) & (kReading | kWriting)))
            {
                fp = iob;
                break;
            }
        cpu.eax = fp != 0 ? kLinkSize : kLinkSize + kFileSize;
        if (!call(app, cpu, nmalloc))
            return false;
        link = cpu.eax;
        flag = fp != 0 ? kReading | kWriting : kDynamic | kReading | kWriting;
        if (link == 0)
        {
            fp = 0;
            return setThreadWord(app, cpu, kErrno, kENOMEM) && call(app, cpu, at(app, kReleaseIob));
        }
        if (fp == 0)
            fp = link + kLinkSize;
    }
    cpu.ebx = kFileSize;
    cpu.eax = fp;
    cpu.edx = 0;
    if (!call(app, cpu, memset))
        return false;
    put(app, fp + kFlag, flag);
    put(app, link + kLinkStream, fp);
    const x86::reg32 head = at(app, kOpenStreams);
    put(app, fp + kLink, link);
    put(app, kOpenStreams, link);
    put(app, link + kLinkNext, head);
    cpu.eax = head;
    return call(app, cpu, at(app, kReleaseIob));
}

/* __freefp's: the stream's link off __OpenStreams and first on the closed
 * ones', its FILE marked in use still; the link, or 0 for a stream not
 * open. */
x86::reg32 freeStream(win32::WinApplication* app, x86::reg32 fp)
{
    for (x86::reg32 before = kOpenStreams, link = at(app, before); link != 0; before = link, link = at(app, link))
    {
        const x86::reg32 stream = at(app, link + kLinkStream);
        if (stream != fp)
            continue;
        putByte(app, fp + kFlag, byte(app, stream + kFlag) | kReading | kWriting);
        put(app, before, at(app, link + kLinkNext));
        const x86::reg32 closed = at(app, kClosedStreams);
        put(app, kClosedStreams, link);
        put(app, link + kLinkNext, closed);
        return link;
    }
    return 0;
}

/* __doclose's (clib/streamio/c/fclose.c): a stream given up -- flushed, the
 * handle where the stream is, closed if asked, the heap's buffer freed, a
 * temporary file removed by the name __MkTmpFile makes it in its frame --
 * and the handle's slot freed.  0, or what flushing and closing gave; -1
 * for a FILE not in use. */
bool doClose(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32 handleToo, x86::reg32& result)
{
    const Frame frame(cpu, 0x128);  // ebx, ecx, esi, edi, ebp; a path
    const x86::reg32 path = cpu.esp;
    result = 0xffffffff;
    if (at(app, fp + kFlag) == 0)
        return true;
    result = 0;
    if ((flags(app, fp) & kDirty) && !nested(cpu, [&] { return flushStream(app, cpu, fp, result); }))
        return false;
    if (!streamLock(app, cpu, kAccessFile, fp))
        return false;
    x86::reg32 place;
    if (!nested(cpu, [&] { return tellStream(app, cpu, fp, place); }))
        return false;
    if (place != 0xffffffff)
    {
        cpu.edx = place;
        cpu.ebx = 0;
        cpu.eax = at(app, fp + kFileHandle);
        if (!call(app, cpu, lseek))
            return false;
    }
    if (handleToo != 0)
    {
        x86::reg32 closed;
        if (!nested(cpu, [&] { return closeHandle(app, cpu, at(app, fp + kFileHandle), closed); }))
            return false;
        result |= closed;
    }
    if (byte(app, fp + kFlag) & kBigBuf)
    {
        cpu.eax = bufferOf(app, fp);
        if (!call(app, cpu, nfree))
            return false;
        put(app, linkOf(app, fp) + kLinkBase, 0);
    }
    if (flags(app, fp) & kTmpFile)
    {
        cpu.edx = byte(app, linkOf(app, fp) + kTmpfChar);
        cpu.eax = path;
        if (!call(app, cpu, kMkTmpFile))
            return false;
        cpu.eax = path;
        if (!call(app, cpu, remove))
            return false;
    }
    if (!streamLock(app, cpu, kReleaseFile, fp))
        return false;
    cpu.eax = at(app, fp + kFileHandle);
    return handleToo == 0 || call(app, cpu, at(app, kFreeHandle));
}

/* __shutdown_stream's: __doclose's, and __freefp. */
bool shutdownStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32 handleToo,
                    x86::reg32& result)
{
    const Frame frame(cpu, 4);  // ebx
    if (!nested(cpu, [&] { return doClose(app, cpu, fp, handleToo, result); }))
        return false;
    freeStream(app, fp);
    return true;
}

/* fclose's: a stream on __OpenStreams shut down, its handle closed; -1 for
 * one not there.  The streams' lock given back with eax its link, or 0. */
bool closeStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 fp, x86::reg32& result)
{
    const Frame frame(cpu, 8);  // ebx, edx
    cpu.eax = fp;
    if (!call(app, cpu, at(app, kAccessIob)))
        return false;
    x86::reg32 link = at(app, kOpenStreams);
    while (link != 0 && at(app, link + kLinkStream) != fp)
        link = at(app, link + kLinkNext);
    cpu.eax = link;
    if (!call(app, cpu, at(app, kReleaseIob)))
        return false;
    result = 0xffffffff;
    return link == 0 || nested(cpu, [&] { return shutdownStream(app, cpu, fp, 1, result); });
}

/* _fsopen's (clib/streamio/c/fopen.c): the mode's flags, a stream, and
 * __doopen, its extended flags a dword of the frame; 0 for a mode that is
 * none or no stream. */
bool openStream(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 name, x86::reg32 mode, x86::reg32 shflag,
                x86::reg32& result)
{
    const Frame frame(cpu, 0x10);  // ecx, esi, edi; a dword
    const x86::reg32 extflags = cpu.esp;
    x86::reg32 flags, fp;
    if (!nested(cpu, [&] { return openFlags(app, cpu, mode, extflags, flags); }))
        return false;
    result = 0;
    if (flags == 0)
        return true;
    cpu.eax = 0;
    if (!nested(cpu, [&] { return allocateStream(app, cpu, fp); }))
        return false;
    if (fp == 0)
        return true;
    const Frame arguments(cpu, 8);  // shflag and the stream, __doopen's on the stack
    return nested(cpu, [&] {
        return doOpen(app, cpu, name, byte(app, mode), flags, at(app, extflags), shflag, fp, result);
    });
}

}  // namespace

/* fsync (clib/handleio/c/fsync.c, 0x522d80): handle eax's buffers to the
 * disk; 0, or -1. */
void fsync(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!syncHandle(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __chktty (clib/streamio/c/chktty.c, 0x509380): the stream at eax marked a
 * tty's, if it is one. */
void chktty(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!checkTty(app, cpu, cpu.eax))
        return;
    const x86::reg32 eax = cpu.eax;
    kept.back(cpu);
    returns(cpu, eax);
}

/* __ioalloc (clib/streamio/c/ioalloc.c, 0x5029c0): a buffer for the stream at
 * eax. */
void ioalloc(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!allocateBuffer(app, cpu, cpu.eax))
        return;
    const x86::reg32 eax = cpu.eax;
    kept.back(cpu);
    returns(cpu, eax);
}

/* __flush (clib/streamio/c/flush.c, 0x502760): the stream at eax's buffer
 * written, or given back; 0, or -1. */
void flush(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!flushStream(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fputc (clib/streamio/c/fputc.c, 0x5097b0): eax's character to the stream
 * at edx. */
void fputc(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!putChar(app, cpu, cpu.eax, cpu.edx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fputs (clib/streamio/c/fputs.c, 0x4f7d80): the string at eax to the stream
 * at edx. */
void fputs(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!putString(app, cpu, cpu.eax, cpu.edx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fwrite (clib/streamio/c/fwrite.c, 0x4eebd0): ebx of edx bytes from eax to
 * the stream at ecx. */
void fwrite(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!writeStream(app, cpu, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __flushall (clib/streamio/c/flushall.c, 0x515858): the open streams with
 * a bit of eax flushed; how many. */
void flushall_(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 count;
    if (!flushAll(app, cpu, cpu.eax, count))
        return;
    kept.back(cpu);
    returns(cpu, count);
}

/* flushall (clib/streamio/c/flushall.c, 0x515850): all of them. */
void flushall(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 count;
    if (!flushAll(app, cpu, 0xffffffff, count))
        return;
    kept.back(cpu);
    returns(cpu, count);
}

/* fflush (clib/streamio/c/fflush.c, 0x4f7d70): the stream at eax flushed --
 * or, for none, all of them, and 0. */
void fflush(win32::WinApplication* app, x86::CPU& cpu)
{
    if (cpu.eax != 0)
        return flush(app, cpu);
    const Kept kept(cpu);
    x86::reg32 count;
    if (!nested(cpu, [&] { return flushAll(app, cpu, 0xffffffff, count); }))
        return;
    kept.back(cpu);
    returns(cpu, 0);
}

/* __update_buffer (clib/streamio/c/fseek.c, 0x4e9030): a seek of eax from
 * where the stream at edx is, within its buffer: 0, or 1 for one outside. */
void update_buffer(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, updateBuffer(app, cpu.eax, cpu.edx));
}

/* __reset_buffer (clib/streamio/c/fseek.c, 0x4e9070): the stream at eax's
 * buffer emptied; eax left the stream. */
void reset_buffer(win32::WinApplication* app, x86::CPU& cpu)
{
    resetBuffer(app, cpu.eax);
    returns(cpu, cpu.eax);
}

/* __fill_buffer (clib/streamio/c/fgetc.c, 0x502be8): the stream at eax's
 * buffer filled; how many are in it. */
void fill_buffer(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 count;
    if (!fillBuffer(app, cpu, cpu.eax, count))
        return;
    kept.back(cpu);
    returns(cpu, count);
}

/* __filbuf (clib/streamio/c/fgetc.c, 0x502bb8): the stream at eax's buffer
 * filled, and its first byte; -1 for none. */
void filbuf(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 c;
    if (!fillAndTake(app, cpu, cpu.eax, c))
        return;
    kept.back(cpu);
    returns(cpu, c);
}

/* fgetc (clib/streamio/c/fgetc.c, 0x502af0): a byte of the stream at eax,
 * or -1. */
void fgetc(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!getChar(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fread (clib/streamio/c/fread.c, 0x4e9200): ebx of edx bytes into eax from
 * the stream at ecx. */
void fread(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!readStream(app, cpu, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fgets (clib/streamio/c/fgets.c, 0x4f0570): a line of the stream at ebx
 * into eax, edx bytes at most with its 0; eax, or 0. */
void fgets(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!getString(app, cpu, cpu.eax, cpu.edx, cpu.ebx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fseek (clib/streamio/c/fseek.c, 0x4e9088): the stream at eax to edx, from
 * ebx's whence; 0, or -1. */
void fseek(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!seekStream(app, cpu, cpu.eax, cpu.edx, cpu.ebx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* ftell (clib/streamio/c/ftell.c, 0x4ee420): where the stream at eax is, or
 * -1. */
void ftell(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!tellStream(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __GetNTAccessAttr (clib/streamio/c/ntfio.c, 0x5234d0): CreateFileA's
 * access to edx's dword and attributes to ebx's for eax's read and write
 * mode. */
void GetNTAccessAttr(win32::WinApplication* app, x86::CPU& cpu)
{
    accessAttributes(app, cpu.eax, cpu.edx, cpu.ebx);
    returns(cpu, cpu.eax);
}

/* __GetNTShareAttr (clib/streamio/c/ntfio.c, 0x523504): CreateFileA's
 * sharing to edx's dword for eax's sharing and mode; eax left the sharing
 * bits. */
void GetNTShareAttr(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, shareAttributes(app, cpu.eax, cpu.edx));
}

/* 0x51e2b0, _sopen's: whether __OSHandles has no slot free. */
void handlesFull(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, handlesFull(app));
}

/* __NTGetFakeHandle (clib/handleio/c/hdlman.c, 0x51e4f0): a HANDLE for a
 * handle with none. */
void NTGetFakeHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 handle;
    if (!fakeHandle(app, cpu, handle))
        return;
    kept.back(cpu);
    returns(cpu, handle);
}

/* __allocPOSIXHandle (clib/handleio/c/hdlman.c, 0x51e304): a handle for the
 * HANDLE at eax. */
void allocPOSIXHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 handle;
    if (!allocHandle(app, cpu, cpu.eax, handle))
        return;
    kept.back(cpu);
    returns(cpu, handle);
}

/* __freePOSIXHandle (clib/handleio/c/hdlman.c, 0x51e45c): handle eax's slot
 * free. */
void freePOSIXHandle(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!freeHandle(app, cpu, cpu.eax))
        return;
    const x86::reg32 eax = cpu.eax;
    kept.back(cpu);
    returns(cpu, eax);
}

/* __close (clib/handleio/c/_clsewnt.c, 0x5095b0): handle eax closed; 0, or
 * -1. */
void close(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!closeHandle(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __sopen (clib/handleio/c/openwnt.c, 0x50901c): eax opened with edx's
 * flags and ebx's sharing, the permissions from the va_list at ecx. */
void sopen_(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!openHandle(app, cpu, cpu.eax, cpu.edx, cpu.ebx, cpu.ecx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* _sopen (clib/handleio/c/openwnt.c, 0x508ff4): cdecl (name, flags,
 * sharing, ...); __sopen's, with a va_list of its frame for the rest. */
void sopen(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    const x86::reg32 entry = cpu.esp;
    x86::reg32 result;
    {
        const Frame frame(cpu, 0x10);  // ebx, ecx, edx; the va_list
        const x86::reg32 args = cpu.esp;
        put(app, args, entry + 0x10);
        if (!nested(cpu, [&] {
                return openHandle(app, cpu, at(app, entry + 4), at(app, entry + 8), at(app, entry + 0xc), args, result);
            }))
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

/* __open_flags (clib/streamio/c/fopen.c, 0x4edd80): the mode string at eax's
 * flags, its extended ones to edx's dword. */
void open_flags(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!openFlags(app, cpu, cpu.eax, cpu.edx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __doopen (clib/streamio/c/fopen.c, 0x4edebc): eax opened as dl's mode
 * says, with ebx's flags and ecx's extended ones, into the stream on the
 * stack after its sharing; takes them off. */
void doopen(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    const x86::reg32 entry = cpu.esp;
    x86::reg32 result;
    if (!doOpen(app, cpu, cpu.eax, x86::reg8(cpu.edx), cpu.ebx, cpu.ecx, at(app, entry + 4), at(app, entry + 8),
                result))
        return;
    kept.back(cpu);
    returns(cpu, result);
    cpu.esp += 8;
}

/* __allocfp (clib/streamio/c/allocfp.c, 0x509250): a stream, or 0. */
void allocfp(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 fp;
    if (!allocateStream(app, cpu, fp))
        return;
    kept.back(cpu);
    returns(cpu, fp);
}

/* __freefp (clib/streamio/c/allocfp.c, 0x509314): the stream at eax off the
 * open ones; its link, or 0. */
void freefp(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, freeStream(app, cpu.eax));
}

/* __doclose (clib/streamio/c/fclose.c, 0x4ee214): the stream at eax given
 * up, its handle closed too if edx says so. */
void doclose(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!doClose(app, cpu, cpu.eax, cpu.edx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __shutdown_stream (clib/streamio/c/fclose.c, 0x4ee144): the stream at eax
 * given up and freed. */
void shutdown_stream(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!shutdownStream(app, cpu, cpu.eax, cpu.edx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fclose (clib/streamio/c/fclose.c, 0x4ee100): the stream at eax closed; 0,
 * or -1. */
void fclose(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!closeStream(app, cpu, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* _fsopen (clib/streamio/c/fopen.c, 0x4edfa4): eax opened as the mode at edx
 * says, with ebx's sharing; the stream, or 0. */
void fsopen(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!openStream(app, cpu, cpu.eax, cpu.edx, cpu.ebx, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* fopen (clib/streamio/c/fopen.c, 0x4edfe8): _fsopen's, sharing as it may. */
void fopen(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    {
        const Frame frame(cpu, 4);  // ebx
        if (!nested(cpu, [&] { return openStream(app, cpu, cpu.eax, cpu.edx, 0, result); }))
            return;
    }
    kept.back(cpu);
    returns(cpu, result);
}

/* ---- The heap (native_watcom_heap.cpp has it; these are the game's calls
 * into it, each keeping the registers its code kept: all but eax, but for
 * what __MemAllocator and __MemFree are handed). ---- */

/* _nmalloc (clib/heap/c/nmalloc.c, 0x4f7900): eax bytes; the block, or 0. */
void nmalloc(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!watcomheap::allocate(app, cpu, kGameHeap, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* _nfree (clib/heap/c/nfree.c, 0x4f79f0): the block at eax given back. */
void nfree(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!watcomheap::free(app, cpu, kGameHeap, cpu.eax))
        return;
    const x86::reg32 eax = cpu.eax;
    kept.back(cpu);
    returns(cpu, eax);
}

/* __MemAllocator (clib/heap/c/mem.c, 0x515300): eax bytes from the miniheap at
 * ebx (edx the segment, nothing on a flat heap); the block, or 0. */
void MemAllocator(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, watcomheap::allocateIn(app, cpu.ebx, cpu.eax));
}

/* __MemFree (clib/heap/c/mem.c, 0x5153b0): the block at eax given back to the
 * miniheap at ebx. */
void MemFree(win32::WinApplication* app, x86::CPU& cpu)
{
    watcomheap::freeIn(app, cpu.ebx, cpu.eax);
    cpu.esp += 4;
}

/* __LinkUpNewNHeap (clib/heap/c/grownear.c, 0x5154e0): the new miniheap at eax
 * into the list; its first block. */
void LinkUpNewNHeap(win32::WinApplication* app, x86::CPU& cpu)
{
    returns(cpu, watcomheap::link(app, kGameHeap, cpu.eax));
}

/* __AdjustAmount (clib/heap/c/grownear.c, 0x515628): the amount at eax made
 * what a miniheap for it takes, in place; 1, or 0. */
void AdjustAmount(win32::WinApplication* app, x86::CPU& cpu)
{
    x86::reg32 amount = at(app, cpu.eax);
    const bool adjusted = watcomheap::adjust(app, kGameHeap, amount);
    put(app, cpu.eax, amount);
    returns(cpu, adjusted ? 1 : 0);
}

/* __CreateNewNHeap (clib/heap/c/grownear.c, 0x515558): a miniheap with room
 * for eax bytes; 1, or 0. */
void CreateNewNHeap(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!watcomheap::create(app, cpu, kGameHeap, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __ExpandDGROUP (clib/heap/c/grownear.c, 0x515614): the empty miniheaps given
 * back, then a new one with room for eax bytes; 1, or 0. */
void ExpandDGROUP(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!watcomheap::expand(app, cpu, kGameHeap, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* __nmemneed (clib/heap/c/nmemneed.c, 0x515680): whether the caller could give
 * memory back for eax bytes more -- no. */
void nmemneed(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    returns(cpu, 0);
}

/* _nheapshrink (clib/heap/c/nheapmin.c, 0x5241c0): every empty miniheap given
 * back to the system; 0. */
void nheapshrink(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    if (!watcomheap::shrink(app, cpu, kGameHeap))
        return;
    kept.back(cpu);
    returns(cpu, 0);
}

/* __ReturnMemToSystem (clib/heap/c/nheapmin.c, 0x5241fc): the miniheap at eax
 * to VirtualFree, and the rovers off it; 0, or -1. */
void ReturnMemToSystem(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!watcomheap::giveBack(app, cpu, kGameHeap, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

/* 0x52425c, _nheapshrink's step (clib/heap/c/nheapmin.c, __UnlinkNHeap after
 * __ReturnMemToSystem): the miniheap at eax given back and, if it went, taken
 * off the list; 0, or -1. */
void ReleaseNHeap(win32::WinApplication* app, x86::CPU& cpu)
{
    const Kept kept(cpu);
    x86::reg32 result;
    if (!watcomheap::release(app, cpu, kGameHeap, cpu.eax, result))
        return;
    kept.back(cpu);
    returns(cpu, result);
}

}  // namespace watcom
}  // namespace nfs3hp
