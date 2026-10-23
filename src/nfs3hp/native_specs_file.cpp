#include <nfs3hp.h>
#include "native_thrash.h"

/* sub_4b22d0, the writer of the specs file's text, decompiled.
 *
 * The game describes a car in a text file: for each of the 80 entries of the
 * spec record a line with the entry's name and its position in the file
 * ("mass [kg](2)"), then the value -- a single number, or a list of them
 * separated by commas -- and an empty line.  The names come from the table of
 * pointers at 0x55eddc and the numbers in parentheses from the table at
 * 0x4af3b2, both read as the game keeps them; the values come out of the
 * record through the switch the compiler built at 0x4b24e7, one case per
 * entry, which this table replaces.  Each line is built in a buffer on the
 * guest's stack, copied to the heap under the tag "a line" (0x4b0790's
 * sprintf helpers do the formatting), and after the 80th the pieces are
 * joined into one string tagged "specs file" (0x4e1620 allocates, 0x4e1890
 * frees), its length left at the caller's dword and its pointer in eax -- or
 * eax null, with nothing written, when the record is null or a piece could
 * not be allocated.  The registers but eax and edx come out as the generated
 * code leaves them (the original pushes and pops ecx, esi, edi and ebp; ebx
 * is an argument and may be clobbered), the flags come out as the last
 * compare of each of its four ways out leaves them, and only the stack below
 * the returned esp is not written.
 *
 * NFS_NATIVES=original runs the generated transcription, which stays in
 * place as the fallback. */

namespace nfs3hp
{

namespace
{

constexpr x86::reg32 kSprintf = 0x4df690;    // cdecl: the buffer, the format, the arguments
constexpr x86::reg32 kMemset = 0x4e0640;     // eax the buffer, edx the byte, ebx how many
constexpr x86::reg32 kAlloc = 0x4e1620;      // eax the tag, edx the size, ebx the flags
constexpr x86::reg32 kFree = 0x4e1890;       // eax the block, edi as the original's calls keep it
constexpr x86::reg32 kFmtInt = 0x4b0790;     // sprintf(eax, "%d", edx), when eax is not null
constexpr x86::reg32 kFmtByte = 0x4b07c0;    // sprintf(eax, "%d", edx & 0xff)
constexpr x86::reg32 kFmtFloat = 0x4b0880;   // sprintf(eax, "%.6f", the float pushed), ret 4
constexpr x86::reg32 kFmtFixed = 0x4b08d0;   // sprintf(eax, "%.6f", edx / 65536.0)

constexpr x86::reg32 kNameTable = 0x55eddc;  // char*[80]: the entries' names
constexpr x86::reg32 kDescTable = 0x4af3b2;  // {u16, u16 id, u16, u16}[80]: the numbers in parentheses
constexpr x86::reg32 kFmtIntText = 0x53eab4; // "%d"
constexpr x86::reg32 kFmtParen = 0x53ead0;   // "(%d)"
constexpr x86::reg32 kComma = 0x53ead8;      // ","
constexpr x86::reg32 kTagLine = 0x53eadc;    // "a line"
constexpr x86::reg32 kTagSpecs = 0x53eae4;   // "specs file"
constexpr x86::reg32 kNewLine = 0x4b0698;    // "\r\n"

constexpr x86::reg32 kFieldCount = 80;       // 0x50 entries, and the loop's bound
constexpr x86::reg32 kLineSize = 0x7d0;      // 2000 bytes for a field's text
constexpr x86::reg32 kNumberSize = 0x64;     // 100 bytes for one formatted value
constexpr x86::reg32 kFrameSize = 0xa00;     // the buffers' room below the entry esp

/* The switch at 0x4b24e7: where each entry's value lives in the record and
 * how it prints.  The arrays' first element prints before the loop, the rest
 * comma by comma.  Entry 0's serial number arrives in ebx, not in the
 * record. */
enum class Kind : std::uint8_t
{
    Serial,        // the serial number, from ebx, as "%d"
    Int,           // the dword at the offset, as "%d"
    Float,         // the float at the offset, as "%.6f"
    Byte,          // the byte at the offset, as "%d"
    Fixed,         // the dword at the offset, as "%.6f" of sixteenths (edx / 65536.0)
    FloatFromInt,  // the dword at the offset, made a float, as "%.6f"
    IntArray,      // count dwords, stride 4, as "%d"
    FloatArray,    // count floats, stride 4, as "%.6f"
    ByteArray      // count bytes, stride 1, as "%d"
};

struct Field
{
    Kind kind;
    std::uint32_t offset;
    std::uint8_t count;
};

const Field kFields[kFieldCount] = {
    {Kind::Serial,      0x0,    1},  // Serial Number
    {Kind::Int,         0x0,    1},  // Car Classification
    {Kind::Float,       0x4,    1},  // mass [kg]
    {Kind::Int,         0x8,    1},  // number of gears (reverse + neutral + forward gears)
    {Kind::Int,         0xc,    1},  // number of gears (automatic, r, n, forward)
    {Kind::Int,         0x10,   1},  // gear shift delay (ticks)
    {Kind::IntArray,    0x14,   8},  // shift blip in rpm
    {Kind::IntArray,    0x34,   8},  // brake blip in rpm
    {Kind::FloatArray,  0x94,   8},  // velocity to rpm ratio
    {Kind::FloatArray,  0xb4,   8},  // velocity to rpm ratio, automatic
    {Kind::FloatArray,  0x54,   8},  // gear ratios
    {Kind::FloatArray,  0x74,   8},  // gear ratios, automatic
    {Kind::FloatArray,  0xd4,   8},  // gear efficiency
    {Kind::FloatArray,  0xf4,   8},  // gear efficiency, automatic
    {Kind::FloatArray,  0x114, 41},  // torque curve, in 256 rpm increments
    {Kind::Float,       0x1b8,  1},  // final gear
    {Kind::Float,       0x1bc,  1},  // final gear, automatic
    {Kind::Int,         0x1c0,  1},  // engine minimum rpm
    {Kind::Int,         0x1c4,  1},  // engine redline in rpm
    {Kind::Float,       0x1c8,  1},  // maximum velocity of car
    {Kind::Float,       0x1cc,  1},  // top speed cap
    {Kind::Float,       0x1d0,  1},  // front drive ratio
    {Kind::Byte,        0x1d4,  1},  // Uses Antilock Brake System
    {Kind::Float,       0x1d8,  1},  // maximum braking deceleration
    {Kind::Float,       0x1dc,  1},  // front bias brake ratio
    {Kind::ByteArray,   0x1e0,  8},  // gas increasing curve
    {Kind::ByteArray,   0x1e8,  8},  // gas decreasing curve
    {Kind::FloatArray,  0x1f0,  8},  // brake increasing curve
    {Kind::FloatArray,  0x210,  8},  // brake decreasing curve
    {Kind::Float,       0x230,  1},  // wheel base
    {Kind::Float,       0x234,  1},  // front grip bias
    {Kind::Int,         0x238,  1},  // power steering (boolean)
    {Kind::Float,       0x23c,  1},  // minimum steering acceleration
    {Kind::Float,       0x240,  1},  // turn in ramp
    {Kind::Float,       0x244,  1},  // turn out ramp
    {Kind::Float,       0x248,  1},  // lateral acceleration grip multiplier
    {Kind::Float,       0x24c,  1},  // aerodynamic downforce multiplier
    {Kind::Float,       0x250,  1},  // gas off factor
    {Kind::Float,       0x254,  1},  // g transfer factor
    {Kind::Float,       0x258,  1},  // turning circle radius
    {Kind::IntArray,    0x25c,  3},  // tire specs, front
    {Kind::IntArray,    0x268,  3},  // tire specs, rear
    {Kind::Float,       0x274,  1},  // tire wear
    {Kind::Float,       0x278,  1},  // Slide Multiplier
    {Kind::Float,       0x27c,  1},  // Spin Velocity Cap
    {Kind::Float,       0x280,  1},  // Slide Velocity Cap
    {Kind::FloatFromInt, 0x284, 1},  // Slide Assistance Factor
    {Kind::Int,         0x288,  1},  // Push Factor
    {Kind::Float,       0x28c,  1},  // Low Turn Factor
    {Kind::Float,       0x290,  1},  // High Turn Factor
    {Kind::Float,       0x294,  1},  // pitch roll factor
    {Kind::Float,       0x298,  1},  // road bumpiness factor
    {Kind::Int,         0x29c,  1},  // spoiler function type
    {Kind::Float,       0x2a0,  1},  // spoiler activation speed
    {Kind::Int,         0x2a4,  1},  // gradual turn cutoff
    {Kind::Int,         0x2a8,  1},  // medium turn cutoff
    {Kind::Int,         0x2ac,  1},  // sharp turn cutoff
    {Kind::Float,       0x2b0,  1},  // medium turn speed modifier
    {Kind::Float,       0x2b4,  1},  // sharp turn speed modifier
    {Kind::Float,       0x2b8,  1},  // extreme turn speed modifier
    {Kind::Int,         0x2bc,  1},  // subdivide level
    {Kind::Fixed,       0x2c0,  1},  // camera arm
    {Kind::Float,       0x2c4,  1},  // Body Damage
    {Kind::Float,       0x2c8,  1},  // Engine Damage
    {Kind::Float,       0x2cc,  1},  // Suspension Damage
    {Kind::Float,       0x2d0,  1},  // Engine Tuning
    {Kind::Float,       0x2d4,  1},  // Brake Balance
    {Kind::Float,       0x2d8,  1},  // Steering Speed
    {Kind::Float,       0x2dc,  1},  // Gear Rat Factor
    {Kind::Float,       0x2e0,  1},  // Suspension Stiffness
    {Kind::Float,       0x2e4,  1},  // Aero Factor
    {Kind::Float,       0x2e8,  1},  // Tire Factor
    {Kind::FloatArray,  0x2ec, 14},  // AI ACC0 acceleration table section
    {Kind::FloatArray,  0x324, 14},  // AI ACC1 acceleration table section
    {Kind::FloatArray,  0x35c, 14},  // AI ACC2 acceleration table section
    {Kind::FloatArray,  0x394, 14},  // AI ACC3 acceleration table section
    {Kind::FloatArray,  0x3cc, 14},  // AI ACC4 acceleration table section
    {Kind::FloatArray,  0x404, 14},  // AI ACC5 acceleration table section
    {Kind::FloatArray,  0x43c, 14},  // AI ACC6 acceleration table section
    {Kind::FloatArray,  0x474, 14},  // AI ACC7 acceleration table section
};

x86::reg32 dwordAt(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg32>(address);
}

std::uint8_t byteAt(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg8>(address);
}

float floatAt(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<float>(address);
}

/* The guest's calls: the return address pushed, the callee's own epilogue
 * popping it back, cpu.terminate saying the game stopped inside. */
bool callGuest(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 address)
{
    cpu.esp -= 4;
    app->dynamic_call(address, cpu);
    return !cpu.terminate;
}

bool guestMemset(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, x86::reg32 fill, x86::reg32 count)
{
    cpu.eax = dst;
    cpu.edx = fill;
    cpu.ebx = count;
    return callGuest(app, cpu, kMemset);
}

/* cdecl: the value, the format and the buffer pushed, 12 bytes cleaned. */
bool guestSprintf(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, x86::reg32 format, x86::reg32 value)
{
    cpu.esp -= 4;
    app->getMemory<x86::reg32>(cpu.esp) = value;
    cpu.esp -= 4;
    app->getMemory<x86::reg32>(cpu.esp) = format;
    cpu.esp -= 4;
    app->getMemory<x86::reg32>(cpu.esp) = dst;
    if (!callGuest(app, cpu, kSprintf))
        return false;
    cpu.esp += 12;
    return true;
}

bool fmtInt(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, x86::reg32 value)
{
    cpu.eax = dst;
    cpu.edx = value;
    return callGuest(app, cpu, kFmtInt);
}

bool fmtByte(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, std::uint8_t value)
{
    cpu.eax = dst;
    cpu.edx = value;
    return callGuest(app, cpu, kFmtByte);
}

/* "%.6f" of the float pushed; the callee's ret 4 takes the argument back. */
bool fmtFloat(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, float value)
{
    cpu.esp -= 4;
    app->getMemory<float>(cpu.esp) = value;
    cpu.eax = dst;
    return callGuest(app, cpu, kFmtFloat);
}

/* "%.6f" of a sixteenth: the dword as the 16.16 the original scales by
 * 1.52587890625e-05 (0x53eac8's constant). */
bool fmtFixed(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 dst, x86::reg32 value)
{
    cpu.eax = dst;
    cpu.edx = value;
    return callGuest(app, cpu, kFmtFixed);
}

bool allocLine(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 tag, x86::reg32 size, x86::reg32& block)
{
    cpu.eax = tag;
    cpu.edx = size;
    cpu.ebx = 0x10;  // the original's alignment flags at every call
    if (!callGuest(app, cpu, kAlloc))
        return false;
    block = cpu.eax;
    return true;
}

bool freeBlock(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 block, x86::reg32 edi)
{
    cpu.eax = block;
    cpu.edi = edi;
    return callGuest(app, cpu, kFree);
}

/* strcpy(dst + strlen(dst), src), the original's inlined appends. */
void appendText(win32::WinApplication* app, x86::reg32 dst, x86::reg32 src)
{
    x86::reg32 tail = dst;
    while (byteAt(app, tail) != 0)
        ++tail;
    for (;;)
    {
        const std::uint8_t c = byteAt(app, src);
        app->getMemory<x86::reg8>(tail) = c;
        if (c == 0)
            return;
        ++tail;
        ++src;
    }
}

x86::reg32 textLength(win32::WinApplication* app, x86::reg32 text)
{
    x86::reg32 length = 0;
    while (byteAt(app, text + length) != 0)
        ++length;
    return length;
}

/* One entry's value into `number` and onto the line; kFields[field] says
 * from where and how.  False when the game stopped inside a call. */
bool emitField(win32::WinApplication* app, x86::CPU& cpu, const Field& field, x86::reg32 record,
               x86::reg32 serial, x86::reg32 number, x86::reg32 line)
{
    const x86::reg32 first = record + field.offset;
    switch (field.kind)
    {
        case Kind::Serial:
            if (!fmtInt(app, cpu, number, serial))
                return false;
            break;
        case Kind::Int:
            if (!fmtInt(app, cpu, number, dwordAt(app, first)))
                return false;
            break;
        case Kind::Float:
            if (!fmtFloat(app, cpu, number, floatAt(app, first)))
                return false;
            break;
        case Kind::Byte:
            if (!fmtByte(app, cpu, number, byteAt(app, first)))
                return false;
            break;
        case Kind::Fixed:
            if (!fmtFixed(app, cpu, number, dwordAt(app, first)))
                return false;
            break;
        case Kind::FloatFromInt:
            if (!fmtFloat(app, cpu, number, float(x86::sreg32(dwordAt(app, first)))))
                return false;
            break;
        case Kind::IntArray:
        case Kind::FloatArray:
        case Kind::ByteArray:
        {
            const bool bytes = field.kind == Kind::ByteArray;
            const bool reals = field.kind == Kind::FloatArray;
            const x86::reg32 stride = bytes ? 1 : 4;
            for (std::uint32_t k = 0; k < field.count; ++k)
            {
                if (k != 0)
                {
                    appendText(app, line, kComma);
                    if (!guestMemset(app, cpu, number, 0, kNumberSize))
                        return false;
                }
                const x86::reg32 element = first + k * stride;
                bool ok;
                if (reals)
                    ok = fmtFloat(app, cpu, number, floatAt(app, element));
                else if (bytes)
                    ok = fmtByte(app, cpu, number, byteAt(app, element));
                else
                    ok = fmtInt(app, cpu, number, dwordAt(app, element));
                if (!ok)
                    return false;
                appendText(app, line, number);
            }
            return true;
        }
    }
    appendText(app, line, number);
    return true;
}

/* The flags of the last compare of the original's three whole ways out
 * (cmp edx, 0x50 with edx 0x50) and of the null record's xor: zero and equal,
 * no carry, no overflow. */
void flagsExit(x86::CPU& cpu)
{
    cpu.flags.cf = 0;
    cpu.flags.of = 0;
    cpu.set_szp(x86::reg32(0));
}

}  // namespace

bool specsFileLine(win32::WinApplication* app, x86::CPU& cpu)
{
    if (nativeOriginalRunning() || !nativesEnabled())
        return false;

    const x86::reg32 entryEsp = cpu.esp;
    const x86::reg32 record = cpu.eax;   // the car's spec record, or null
    const x86::reg32 outSize = cpu.edx;  // the caller's dword for the text's length
    const x86::reg32 serial = cpu.ebx;   // the record's serial number
    /* the original pushes and pops ecx, esi, edi and ebp; this body only
     * ever disturbs edi, for the free calls, and puts it back. */
    const x86::reg32 callerEdi = cpu.edi;

    if (record == 0)
    {
        /* the original: eax = edx; *edx = 0; eax ^= edx -- null, and the
         * xor's flags. */
        app->getMemory<x86::reg32>(outSize) = 0;
        cpu.eax = cpu.edx;
        cpu.eax ^= x86::reg32(x86::sreg32(cpu.edx));
        cpu.clear_co();
        cpu.set_szp(cpu.eax);
        cpu.edi = callerEdi;
        cpu.esp = entryEsp + 4;
        return true;
    }

    /* The line, the formatted value and the 80 heap blocks' pointers live on
     * the guest's stack, like the original's frame. */
    cpu.esp = entryEsp - kFrameSize;
    const x86::reg32 line = cpu.esp;
    const x86::reg32 number = line + kLineSize;
    const x86::reg32 slots = number + kNumberSize;

    if (!guestMemset(app, cpu, slots, 0, 0x140))
        return true;

    /* One pass of the original's loop: the name, its number in parentheses,
     * the newline, the value or values, the newline again, the heap copy. */
    for (x86::reg32 field = 0; field < kFieldCount; ++field)
    {
        if (!guestMemset(app, cpu, line, 0, kLineSize) || !guestMemset(app, cpu, number, 0, kNumberSize))
            return true;
        appendText(app, line, dwordAt(app, kNameTable + field * 4));
        cpu.eax = dwordAt(app, kDescTable + field * 8);
        cpu.eax = x86::reg32(x86::sreg32(cpu.eax) >> 16);  // sar, the id in the table's high word
        if (!guestSprintf(app, cpu, number, kFmtParen, cpu.eax))
            return true;
        appendText(app, line, number);
        appendText(app, line, kNewLine);
        if (!emitField(app, cpu, kFields[field], record, serial, number, line))
            return true;
        appendText(app, line, kNewLine);

        const x86::reg32 size = textLength(app, line) + 1;
        x86::reg32 block;
        if (!allocLine(app, cpu, kTagLine, size, block))
            return true;
        if (block == 0)
        {
            /* the original's way out when a field's copy failed: the pieces
             * freed, the length zeroed, null. */
            for (x86::reg32 piece = 0; piece < kFieldCount; ++piece)
            {
                const x86::reg32 held = dwordAt(app, slots + piece * 4);
                if (held != 0 && !freeBlock(app, cpu, held, 0))
                    return true;
                app->getMemory<x86::reg32>(slots + piece * 4) = 0;
            }
            app->getMemory<x86::reg32>(outSize) = 0;
            cpu.edx = kFieldCount;              // the free loop's counter at its last compare
            cpu.ebx = (kFieldCount - 1) * 4;    // its index into the slots
            cpu.eax = 0;
            cpu.clear_co();
            cpu.set_szp(cpu.eax);
            cpu.edi = callerEdi;
            cpu.esp = entryEsp + 4;
            return true;
        }
        app->getMemory<x86::reg32>(slots + field * 4) = block;
        if (!guestMemset(app, cpu, block, 0, size))
            return true;
        appendText(app, block, line);
        if (app->contextWanted())
            app->yieldContext(cpu);
    }

    /* The join: the pieces' lengths summed, one string tagged "specs file",
     * the pieces copied in and freed. */
    x86::reg32 total = 0;
    for (x86::reg32 piece = 0; piece < kFieldCount; ++piece)
        total += textLength(app, dwordAt(app, slots + piece * 4));
    app->getMemory<x86::reg32>(outSize) = total + 1;

    x86::reg32 joined;
    if (!allocLine(app, cpu, kTagSpecs, total + 1, joined))
        return true;
    if (joined == 0)
    {
        for (x86::reg32 piece = 0; piece < kFieldCount; ++piece)
        {
            const x86::reg32 held = dwordAt(app, slots + piece * 4);
            if (held != 0 && !freeBlock(app, cpu, held, held))
                return true;
            app->getMemory<x86::reg32>(slots + piece * 4) = 0;
        }
        cpu.edx = kFieldCount;              // the free loop's counter at its last compare
        cpu.ebx = (kFieldCount - 1) * 4;    // its index into the slots
        cpu.eax = 0;                        // the original reads back the failed allocation's null
        flagsExit(cpu);
        cpu.edi = callerEdi;
        cpu.esp = entryEsp + 4;
        return true;
    }
    if (!guestMemset(app, cpu, joined, 0, total + 1))
        return true;
    for (x86::reg32 piece = 0; piece < kFieldCount; ++piece)
        appendText(app, joined, dwordAt(app, slots + piece * 4));
    for (x86::reg32 piece = 0; piece < kFieldCount; ++piece)
    {
        const x86::reg32 held = dwordAt(app, slots + piece * 4);
        if (held != 0 && !freeBlock(app, cpu, held, held))
            return true;
        app->getMemory<x86::reg32>(slots + piece * 4) = 0;
    }

    /* the original's free loop leaves edx at 0x50 under the last compare,
     * ebx at its last index. */
    cpu.edx = kFieldCount;
    cpu.ebx = (kFieldCount - 1) * 4;
    {
        x86::reg32 tmp1 = cpu.edx;
        x86::reg32 tmp2 = x86::reg32(x86::sreg32(kFieldCount));
        x86::reg32 result = tmp1 - tmp2;
        cpu.flags.cf = tmp1 < tmp2;
        cpu.flags.of = 1 & (tmp1 >> 31);
        cpu.flags.of ^= 1 & (result >> 31);
        cpu.flags.of &= (1 & (tmp1 >> 31)) != (1 & (tmp2 >> 31));
        cpu.set_szp(result);
    }
    cpu.eax = joined;
    cpu.edi = callerEdi;
    cpu.esp = entryEsp + 4;
    return true;
}

}  // namespace nfs3hp
