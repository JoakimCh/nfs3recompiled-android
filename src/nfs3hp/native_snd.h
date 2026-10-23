#ifndef NFS3HP_NATIVE_SND_H
#define NFS3HP_NATIVE_SND_H

#include "native_guest.h"

#include <lib/thread.h>

#include <cstdint>
#include <initializer_list>

/* What native_snd*.cpp share: EA's SND library's state where nfs3.exe keeps
 * it, and the helpers its functions are written with (native_snd.cpp says
 * how). */
namespace nfs3hp
{
namespace snd
{

using guest::at;
using guest::byte;
using guest::call;
using guest::put;
using guest::putByte;
using x86::reg16;
using x86::reg32;
using x86::reg8;
using App = win32::WinApplication;
using CPU = x86::CPU;
using i32 = std::int32_t;
using i16 = std::int16_t;
using i8 = std::int8_t;

inline i32 s32(App* app, reg32 a) { return i32(at(app, a)); }
inline i32 sbyte(App* app, reg32 a) { return i8(byte(app, a)); }
inline reg16 half(App* app, reg32 a) { return app->getMemory<reg16>(a); }
inline i32 shalf(App* app, reg32 a) { return i16(half(app, a)); }
inline void putHalf(App* app, reg32 a, reg16 v) { app->getMemory<reg16>(a) = v; }

/* imul and idiv as the code has them: 32 bits, wrapping; a quotient towards 0. */
inline i32 mul(i32 a, i32 b) { return i32(reg32(a) * reg32(b)); }
inline i32 quotient(i32 a, i32 b) { return b == -1 ? i32(0u - reg32(a)) : a / b; }

/* What a function keeps for its caller: the registers as on entry, esp past
 * the return address and what its ret takes. */
struct Kept
{
    reg32 ebx, ecx, edx, esi, edi, ebp, esp;
    explicit Kept(const CPU& c) : ebx(c.ebx), ecx(c.ecx), edx(c.edx), esi(c.esi), edi(c.edi), ebp(c.ebp), esp(c.esp) {}
    void ret(CPU& c, reg32 eax, reg32 popped = 0) const
    {
        c.ebx = ebx;
        c.ecx = ecx;
        c.edx = edx;
        c.esi = esi;
        c.edi = edi;
        c.ebp = ebp;
        c.esp = esp + 4 + popped;
        c.eax = eax;
    }
    /* esp where the code has it after `pushes` registers and `locals` bytes. */
    reg32 frame(reg32 pushes, reg32 locals = 0) const { return esp - 4 * pushes - locals; }
};

/* The game's where-and-what of an error, then Error (0x401010) with
 * `arguments` pushed from `esp`, where the code has the stack. */
constexpr reg32 kWhere = 0x552190;
constexpr reg32 kError = 0x401010;
inline bool fail(App* app, CPU& cpu, reg32 esp, reg32 file, reg32 function, reg32 line,
          std::initializer_list<reg32> arguments)
{
    const reg32 before = cpu.esp;
    cpu.esp = esp;
    put(app, kWhere, file);
    put(app, kWhere + 4, function);
    put(app, kWhere + 8, line);
    if (!call(app, cpu, kError, arguments))
        return false;
    cpu.esp = before;
    return true;
}

/* A register call: the argument registers as given (those not given as they
 * are), `stack` pushed. */
inline bool callWith(App* app, CPU& cpu, reg32 target, reg32 eax)
{
    cpu.eax = eax;
    return call(app, cpu, target);
}

inline bool callWith(App* app, CPU& cpu, reg32 target, reg32 eax, reg32 edx)
{
    cpu.eax = eax;
    cpu.edx = edx;
    return call(app, cpu, target);
}

inline bool callWith(App* app, CPU& cpu, reg32 target, reg32 eax, reg32 edx, reg32 ebx)
{
    cpu.eax = eax;
    cpu.edx = edx;
    cpu.ebx = ebx;
    return call(app, cpu, target);
}

inline bool callWith(App* app, CPU& cpu, reg32 target, reg32 eax, reg32 edx, reg32 ebx, reg32 ecx,
              std::initializer_list<reg32> stack = {})
{
    cpu.eax = eax;
    cpu.edx = edx;
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    return call(app, cpu, target, stack);
}

// The registers a function pushed, to be popped on its way out (leave).
enum Pushed : unsigned
{
    kEbx = 1,
    kEcx = 2,
    kEdx = 4,
    kEsi = 8,
    kEdi = 16
};

/* The way out: the pushed registers (and ebp) popped, the others as they
 * are, esp past the return and `popped`. */
inline void leave(CPU& cpu, const Kept& kept, unsigned pushed, reg32 popped = 0)
{
    if (pushed & kEbx)
        cpu.ebx = kept.ebx;
    if (pushed & kEcx)
        cpu.ecx = kept.ecx;
    if (pushed & kEdx)
        cpu.edx = kept.edx;
    if (pushed & kEsi)
        cpu.esi = kept.esi;
    if (pushed & kEdi)
        cpu.edi = kept.edi;
    cpu.ebp = kept.ebp;
    cpu.esp = kept.esp + 4 + popped;
}

inline void setByte0(reg32& r, reg8 v) { r = (r & 0xffffff00) | v; }
inline void setByte1(reg32& r, reg8 v) { r = (r & 0xffff00ff) | (reg32(v) << 8); }

/* The code's signed shift towards 0 -- mov eax, edx; sar edx, 31; shl edx,
 * k; sbb eax, edx; sar eax, k -- of edx: eax the quotient, edx as it leaves it. */
inline void towardZero(CPU& cpu, unsigned k)
{
    const bool negative = i32(cpu.edx) < 0;
    cpu.eax = cpu.edx;
    cpu.edx = negative ? 0xffffffffu << k : 0;
    cpu.eax = reg32(i32(cpu.eax - cpu.edx - (negative ? 1 : 0)) >> k);
}

/* The code's cdq; idiv by: edx:eax divided, as x86 does. */
inline void idiv(CPU& cpu, reg32 by)
{
    const i32 n = i32(cpu.eax);
    cpu.eax = reg32(quotient(n, i32(by)));
    cpu.edx = by == 0xffffffff ? 0 : reg32(n % i32(by));
}

/* The code's 16.16 division of eax by `by` -- cdq; idiv; mov ecx, eax; xor
 * eax, eax; shrd eax, edx, 16; sar edx, 16; idiv; shl ecx, 16; add eax,
 * ecx -- with what it leaves in ecx and edx. */
inline void fixedDivide(CPU& cpu, reg32 by)
{
    idiv(cpu, by);
    cpu.ecx = cpu.eax;
    const std::int64_t n = std::int64_t(i32(cpu.edx)) * 0x10000;
    cpu.eax = reg32(n / i32(by));
    cpu.edx = reg32(n % i32(by));
    cpu.ecx <<= 16;
    cpu.eax += cpu.ecx;
}

/* The code's div by: edx:eax divided, unsigned. */
inline void udiv(CPU& cpu, reg32 by)
{
    const std::uint64_t n = (std::uint64_t(cpu.edx) << 32) | cpu.eax;
    cpu.eax = reg32(n / by);
    cpu.edx = reg32(n % by);
}

/* fcomp; fnstsw ax: st(0) compared with m, the x87's status word left in ax
 * as the code has it; true where sahf would set the flag -- CF (C0) for
 * `below`, ZF (C3) for `equal`. */
struct Compared
{
    bool below, equal;
};
inline Compared fcomp(CPU& cpu, const x86::Float& st0, const x86::Float& m)
{
    cpu.fpu.compare(st0, m);
    const reg16 status = cpu.fpu.status.word;
    cpu.eax = (cpu.eax & 0xffff0000) | status;
    return {(status & 0x100) != 0, (status & 0x4000) != 0};
}

/* The game's inlined strcpy of `from` to `to`, two bytes a turn: al left 0,
 * esi where the copy stopped reading (edi is pushed and popped around it). */
inline void copyString(App* app, CPU& cpu, reg32 to, reg32 from)
{
    cpu.esi = from;
    for (reg32 at = to;; at += 2)
    {
        reg8 c = byte(app, cpu.esi);
        putByte(app, at, c);
        if (c == 0)
            break;
        c = byte(app, cpu.esi + 1);
        cpu.esi += 2;
        putByte(app, at + 1, c);
        if (c == 0)
            break;
    }
    cpu.eax &= 0xffffff00;
}

/* The game's inlined strcat of `from` to `to`: its repne scasb (ecx past
 * the end), then copyString's loop. */
inline void appendString(App* app, CPU& cpu, reg32 to, reg32 from)
{
    reg32 end = to;
    while (byte(app, end) != 0)
        ++end;
    cpu.ecx = reg32(-2 - i32(end - to));
    copyString(app, cpu, end, from);
}

/* The game's sar-based halving towards 0 of eax; edx its sign. */
inline void halve(CPU& cpu)
{
    cpu.edx = reg32(i32(cpu.eax) >> 31);
    cpu.eax = reg32(i32(cpu.eax - cpu.edx) >> 1);
}

/* A pan (0..0xffff around) as stereo's (0..127), as the game's code makes it. */
inline reg32 stereoPan(reg32 pan)
{
    const reg32 a = i32(pan) > 0x3fff && i32(pan) < 0xc000 ? 0xbfff - pan : (pan + 0x4000) & 0xffff;
    return reg32(i32(a) >> 8);
}

// The library's state.
constexpr reg32 kVoices = 0xa09b3c, kVoiceSize = 0x60, kVoiceCount = 0x10;
constexpr reg32 kPlatform = 0x9ef658;
constexpr reg32 kChannels = 0x9fbcb4, kChannelSize = 0xde4;
constexpr reg32 kInited = 0xa09af4;         // byte: SNDinit done
constexpr reg32 kMasterVolume = 0xa09af5;   // byte, 0..127
constexpr reg32 kVoicesUsed = 0xa09af6;     // byte: the voices the game asked for
constexpr reg32 kInTick = 0xa09af7;         // byte: in the tick
constexpr reg32 kEntered = 0xa09af8;        // byte: in the library's lock
constexpr reg32 kClientCount = 0xa09af9;    // byte: the tick's clients
constexpr reg32 kTicks = 0xa09afc;
constexpr reg32 kLock = 0xa09b04;           // the critical section's address
constexpr reg32 kClients = 0xa09b0c;        // 6 functions the tick calls first
constexpr reg32 kGroupSerial = 0x5678b0;    // byte: the last group handed out
constexpr reg32 kHandleSerial = 0x56786c;   // a handle's high bits, 0x20 a time
constexpr reg32 kPicked = 0x9f6a54;         // bytes: the voices allocVoices picked
constexpr reg32 kMixRate = 0x9ef614;        // word: the mixer's rate; its high word a pitch's offset
constexpr reg32 kBanks = 0xa0a13c;          // 24 of 12 bytes: the bank, ..., +8 being loaded
constexpr reg32 kBusLevels = 0xa0a260;      // the effect bus's level, 0x10 a bus
constexpr reg32 kChannelEnded = 0x9f6b1c;   // what the mixer calls when a channel ends
constexpr reg32 kEmms = 0x9f6b24;
// The game's functions called here.
constexpr reg32 kSurfaceLocked = 0x4f9070;
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
constexpr reg32 kChop = 0x4dfd56;           // Watcom's __CHP: st(0) truncated
constexpr reg32 kRamp = 0x5004c8;           // the mixer's volume ramp (channel, frames)
// The eacsnd 3D functions the 3D voices go to.
constexpr reg32 kDirectPos3d = 0x9ef644, kDirectVol = 0x9ef648, kDirectRate = 0x9ef64c, kDirectStopBuf = 0x9ef650;

inline reg32 voice(reg32 index) { return kVoices + index * kVoiceSize; }
inline reg32 platform(reg32 index) { return kPlatform + (index << 4); }
inline reg32 channel(reg32 index) { return kChannels + index * kChannelSize; }

/* A loop's safepoint, as the generated code has one at each loop's head: the
 * guest's context handed over when another thread waits for it. */
inline void safepoint(App* app, CPU& cpu)
{
    if (app->contextWanted())
        app->yieldContext(cpu);
}

/* A busy wait's turn, as disassemble_nfs3hp.py's THREAD_SEGMENTS have it: the
 * context let go of and the thread's slice given up, so that the thread the
 * wait waits on runs. */
inline void giveWay(App* app, CPU& cpu)
{
    app->unlockContext(cpu);
    win32::Thread::sleep(0);
    app->lockContext(cpu);
}

}  // namespace snd
}  // namespace nfs3hp

#endif
