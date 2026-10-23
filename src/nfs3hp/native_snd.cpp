#include "native_snd.h"

/* EA's SND library in nfs3.exe, native: the voices the game plays its sounds
 * on, their volume, pan and pitch, the 100 Hz tick that moves their envelopes,
 * and the platform layer under them that sets the mixer's channels.  The
 * mixer itself is native_mixer.cpp's, eacsnd native_sound.cpp's.
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (SND_NATIVES), and the generated code calls it by name; tools/game_checks
 * holds each against the game's code.  The names are EA's where the game's
 * messages give them.
 *
 * The voices, 16 of 0x60 bytes at 0xa09b3c:
 *   +0 the handle the game holds (-1: a voice another one leads), +0xc the
 *   state (0 free, 1 playing, 2 ending with its group), +0xe the priority,
 *   +0xf the pan, +0x10 the pitch, +0x12 the pitch with the envelopes,
 *   +0x14 the tick it was taken or freed at, +0x18/+0x1c/+0x20 the volume's
 *   step, target and value (16.16), +0x24/+0x28/+0x2c the envelope's step,
 *   value (16.16) and ticks left, +0x30 the voice's volume, +0x31 what the
 *   mixer gets, +0x32 the patch's pan, +0x33 the pitch bend, +0x34/+0x35 the
 *   envelope's segments and the one it is in, +0x37 the pan's spread,
 *   +0x3a the voice that ends a group, +0x3b the group (0 none), +0x3c..+0x3f
 *   two LFOs' lengths and places, +0x40/+0x42 their depths, +0x44 the voice
 *   that leads, +0x45 the pan asked for, +0x48 the envelope, +0x4c a volume
 *   curve, +0x50 a pan curve, +0x54 the bend's curve, +0x58/+0x5c the LFOs.
 * The platform's view of the same voices, 16 of 0x10 at 0x9ef658: +0 the
 * sample rate, +2 bits, +3 channels, +4 the compression, +5 how it is played
 * (0 the mixer, 1 the mixer with Dolby surround, 2 the mixer, 3 eacsnd's 3D
 * buffers, which the port never has), +6 whether a pan was set, +8/+9 the
 * surround's two levels, +0xa the 3D position, +0xc an id.
 * The mixer's channels, 16 of 0xde4 at 0x9fbcb4 (native_mixer.cpp's).
 *
 * Each does what the game's code does: the same memory written in the same
 * order, the game's functions called with the same registers and stack, the
 * stack where the code had it (a pointer into a frame is compared), the
 * registers its callers count on as the code leaves them, eax its result, and
 * the return address -- and what a stdcall ret takes -- popped. */
namespace nfs3hp
{
namespace snd
{

namespace
{

// The file and function names, lines and texts of the errors.
constexpr reg32 kAllocFile = 0x54e128, kFreeChanName = 0x54e138, kFreeChanText = 0x54e148;
constexpr reg32 kServerFile = 0x54e314, kEnterName = 0x54e324, kEnterText = 0x54e334;
constexpr reg32 kAddClientName = 0x54e38c, kAddClientText = 0x54e3a8;
constexpr reg32 kRemoveClientName = 0x54e3d8, kRemoveClientText = 0x54e3f4;
constexpr reg32 kVolFile = 0x54e5a8, kVolName = 0x54e5b4, kVolText = 0x54e5bc;
constexpr reg32 kDetuneFile = 0x54ea0c, kDetuneName = 0x54ea1c, kDetuneText = 0x54ea30;
constexpr reg32 k3dPosFile = 0x54ea64, k3dPosName = 0x54ea74, k3dPosText = 0x54ea88;
constexpr reg32 kPanFile = 0x54eac0, kPanName = 0x54eacc, kPanText = 0x54ead4;
constexpr reg32 kDriverFile = 0x549b10, kStopName = 0x54a060, kStopText = 0x54a06c;
constexpr reg32 kAutovolFile = 0x54b278, kAutovolName = 0x54b288, kAutovolText = 0x54b294;
constexpr reg32 kSvolFile = 0x54b2c0, kSvolName = 0x54b2cc, kSvolText = 0x54b2d4;
constexpr reg32 kBendFile = 0x54b2fc, kBendName = 0x54b308, kBendText = 0x54b318;
constexpr reg32 kSpanFile = 0x54b358, kSpanName = 0x54b364, kSpanText = 0x54b36c;
constexpr reg32 kSetdefFile = 0x54b390, kSetdefName = 0x54b3a0, kSetdefText = 0x54b3b0;
constexpr reg32 kPlayFile = 0x54b3dc, kPlayName = 0x54b3e8, kPlayText = 0x54b3f0;

}  // namespace

/* 0x4ffc9c: the voice a handle is on (its low five bits), or -8 when that
 * voice is free or holds another sound. */
void voiceOf(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax;
    reg32 result = 0xfffffff8;
    const reg32 index = handle & 0x1f;
    if (i32(handle) >= 0 && index < kVoiceCount && byte(app, voice(index) + 0xc) != 0
        && handle == at(app, voice(index)))
        result = index;
    kept.ret(cpu, result);
}

/* 0x4ffb64 (iSNDfreechan): the voice in eax freed, the tick it was freed at
 * kept.  A voice of a group ends the group's sound only when it is the last
 * of it playing, or the one marked to end it (+0x3a) is ending already. */
void iSNDfreechan(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax;
    const reg32 v = voice(index);
    const reg32 group = byte(app, v + 0x3b);
    if (group == 0)
    {
        if (byte(app, v + 0xc) == 0 && !fail(app, cpu, kept.frame(6), kAllocFile, kFreeChanName, 0x12a, {kFreeChanText, index}))
            return;
        putByte(app, v + 0xc, 0);
        put(app, v + 0x14, at(app, kTicks));
        kept.ret(cpu, at(app, kTicks));
        return;
    }
    reg32 count = 0, last = 0xffffffff;
    for (reg32 i = 0; i < kVoiceCount; ++i)
    {
        const reg32 w = voice(i);
        if (byte(app, w + 0x3b) == group && s32(app, w) >= 0 && byte(app, w + 0xc) != 0)
        {
            ++count;
            if (byte(app, w + 0x3a) != 0)
                last = i;
        }
    }
    if (count != 1)
    {
        const reg32 l = last * kVoiceSize;
        if (byte(app, l + kVoices + 0xc) == 2 && index != last && count == 2)
        {
            putByte(app, v + 0xc, 0);
            put(app, v + 0x14, at(app, kTicks));
            putByte(app, l + kVoices + 0xc, 0);
            put(app, l + kVoices + 0x14, at(app, kTicks));
            kept.ret(cpu, l);
            return;
        }
        if (byte(app, l + kVoices + 0xc) == 1 && index == last)
        {
            putByte(app, l + kVoices + 0xc, 2);
            kept.ret(cpu, l);
            return;
        }
    }
    putByte(app, v + 0xc, 0);
    put(app, v + 0x14, at(app, kTicks));
    kept.ret(cpu, at(app, kTicks));
}

/* 0x4ff840: whether voice eax is among the first edx allocVoices picked. */
void voicePicked(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 result = 0;
    for (i32 i = 0; i < i32(cpu.edx); ++i)
        if (reg32(sbyte(app, kPicked + i)) == cpu.eax)
            result = 1;
    kept.ret(cpu, result);
}

namespace
{

/* voicePicked as the code calls it. */
bool picked(App* app, CPU& cpu, reg32 index, reg32 count, bool& result)
{
    if (!callWith(app, cpu, 0x4ff840, index, count))
        return false;
    result = cpu.eax != 0;
    return true;
}

}  // namespace

/* 0x4ff86c (iSNDallocchan): edx voices of the mask in eax, at priority bl:
 * free ones first, the longest free, then playing ones of the lowest
 * priority below 0x66, the oldest first -- their sounds stopped.  The handle
 * (the new high bits with the first voice) is written to [ecx] and kept on the
 * first voice; the others are marked as led by it.  The first voice, or -9. */
void iSNDallocchan(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 mask = cpu.eax, wanted = cpu.edx, priority = cpu.ebx, out = cpu.ecx;
    cpu.esp = kept.frame(3, 0x24);
    const i32 count = i32(wanted);
    reg32 found = 0;
    for (i32 i = 1; i <= count; ++i)
        putByte(app, kPicked - 1 + i, 0xff);
    put(app, kHandleSerial, at(app, kHandleSerial) + 0x20);
    if (s32(app, kHandleSerial) < 0)
        put(app, kHandleSerial, 0);
    const i32 used = sbyte(app, kVoicesUsed);
    for (i32 k = 0; k < count; ++k)
    {
        reg32 best = 0xffffffff, bestTime = 0xffffffff;
        for (i32 v = 0; v < used; ++v)
        {
            const reg32 w = voice(reg32(v));
            if (!(mask & (1u << (v & 31))) || byte(app, w + 0xc) != 0)
                continue;
            bool taken;
            if (!picked(app, cpu, reg32(v), found, taken))
                return;
            if (taken || bestTime <= at(app, w + 0x14))
                continue;
            bestTime = at(app, w + 0x14);
            best = reg32(v);
        }
        if (i32(best) >= 0)
        {
            ++found;
            putByte(app, kPicked - 1 + found, reg8(best));
        }
    }
    for (i32 k = i32(found); k < count; ++k)
    {
        reg32 lowest = 0x66, best = 0xffffffff, bestTime = 0xffffffff;
        for (i32 v = 0; v < used; ++v)
        {
            const reg32 w = voice(reg32(v));
            if (!(mask & (1u << (v & 31))))
                continue;
            bool taken;
            if (!picked(app, cpu, reg32(v), found, taken))
                return;
            if (taken)
                continue;
            const reg32 p = byte(app, w + 0xe);
            if (i32(p) < i32(lowest))
            {
                lowest = p;
                bestTime = at(app, w + 0x14);
                best = reg32(v);
            }
            else if (p == lowest && at(app, w + 0x14) < bestTime)
            {
                bestTime = at(app, w + 0x14);
                best = reg32(v);
            }
        }
        if (i32(best) >= 0)
        {
            ++found;
            putByte(app, kPicked - 1 + found, reg8(best));
            if (i32(found) >= count)
                break;
        }
    }
    if (found != wanted)
    {
        kept.ret(cpu, 0xfffffff7);
        return;
    }
    const reg32 first = reg32(sbyte(app, kPicked));
    put(app, out, at(app, kHandleSerial) | first);
    for (i32 j = 0; j < i32(found); ++j)
    {
        const reg32 w = voice(reg32(sbyte(app, kPicked + j)));
        reg32 handle = at(app, w);
        if (byte(app, w + 0xc) == 1)
        {
            if (i32(handle) < 0)
                handle = at(app, voice(reg32(sbyte(app, w + 0x44))));
            if (!callWith(app, cpu, 0x4e9670, handle) || !callWith(app, cpu, 0x4e8fd0, handle))
                return;
            if (cpu.eax != 1)
            {
                for (i32 b = j - 1; b >= 0; --b)
                    putByte(app, voice(reg32(sbyte(app, kPicked + b))) + 0xc, 0);
                kept.ret(cpu, 0xfffffff7);
                return;
            }
        }
        putByte(app, w + 0xc, 1);
        put(app, w + 0x14, at(app, kTicks));
        putByte(app, w + 0xe, reg8(priority));
    }
    put(app, voice(first), at(app, out));
    for (reg32 e = 1; i32(e) < i32(found); ++e)
    {
        putByte(app, voice(reg32(sbyte(app, kPicked))) + 3 + e, byte(app, kPicked + e));
        const reg32 w = voice(reg32(sbyte(app, kPicked + e)));
        put(app, w, 0xffffffff);
        putByte(app, w + 0x44, byte(app, kPicked));
    }
    kept.ret(cpu, first);
}

/* 0x500e20 (iSNDenteraudio): into the library's lock; an error first when a
 * DirectDraw surface is locked, outside the tick. */
void iSNDenteraudio(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (!call(app, cpu, kSurfaceLocked))
        return;
    if (cpu.eax != 0 && byte(app, kInTick) == 0 && !fail(app, cpu, kept.frame(4), kServerFile, kEnterName, 0x114, {kEnterText}))
        return;
    if (!call(app, cpu, at(app, kEnterCriticalSection), {at(app, kLock)}))
        return;
    putByte(app, kEntered, reg8(byte(app, kEntered) + 1));
    kept.ret(cpu, cpu.eax);
}

/* 0x500e7c: out of the library's lock. */
void iSNDleaveaudio(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    putByte(app, kEntered, reg8(byte(app, kEntered) - 1));
    if (!call(app, cpu, at(app, kLeaveCriticalSection), {at(app, kLock)}))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x500e94 (iSNDserveradd100hzclient): eax among the tick's clients. */
void iSNDserveradd100hzclient(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 client = cpu.eax;
    if (sbyte(app, kClientCount) >= 6
        && !fail(app, cpu, kept.frame(4), kServerFile, kAddClientName, 0x149, {kAddClientText}))
        return;
    const reg32 n = reg32(sbyte(app, kClientCount));
    put(app, kClients + 4 * n, client);
    putByte(app, kClientCount, reg8(byte(app, kClientCount) + 1));
    kept.ret(cpu, n);
}

/* 0x500ef0 (iSNDserverremove100hzclient): eax no longer a client, those after
 * it moved down. */
void iSNDserverremove100hzclient(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 client = cpu.eax;
    for (i32 i = 0; i < sbyte(app, kClientCount); ++i)
        if (at(app, kClients + 4 * i) == client)
        {
            putByte(app, kClientCount, reg8(byte(app, kClientCount) - 1));
            for (; i < sbyte(app, kClientCount); ++i)
                put(app, kClients + 4 * i, at(app, kClients + 4 * i + 4));
            kept.ret(cpu, reg32(i));
            return;
        }
    if (!fail(app, cpu, kept.frame(3), kServerFile, kRemoveClientName, 0x165, {kRemoveClientText}))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e0d88: EA's random number, the sum of a 192-bit state with carries, the
 * state then counted up by one. */
void eaRandom(App* app, CPU& cpu)
{
    constexpr reg32 kState = 0x5644e0;  // six dwords, the lowest at +0x14
    std::uint64_t sum = std::uint64_t(at(app, kState + 0x14)) + at(app, kState + 0x10);
    put(app, kState + 0x10, reg32(sum));
    for (const reg32 at4 : {0xcu, 0x8u, 0x4u})
    {
        sum = std::uint64_t(reg32(sum)) + at(app, kState + at4) + (sum >> 32);
        put(app, kState + at4, reg32(sum));
    }
    reg32 eax = reg32(reg32(sum) + at(app, kState) + reg32(sum >> 32));
    bool carry = true;
    for (const reg32 at4 : {0x14u, 0x10u, 0xcu, 0x8u, 0x4u})
    {
        put(app, kState + at4, at(app, kState + at4) + 1);
        if (at(app, kState + at4) != 0)
        {
            carry = false;
            break;
        }
    }
    if (carry)
        ++eax;
    put(app, kState, eax);
    cpu.eax = eax;
    cpu.esp += 4;
}

/* 0x5224e0: a random offset of up to eax either way (eax clamped to 0x10000,
 * none for less than 0). */
void randomOffset(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    i32 range = i32(cpu.eax);
    if (range > 0x10000)
        range = 0x10000;
    else if (range < 0)
        range = 0;
    if (!call(app, cpu, 0x4e0d88))
        return;
    const i32 r = i32(cpu.eax & 0x7fff) - 0x4000;
    kept.ret(cpu, reg32(mul(r, range) >> 14));
}

/* 0x52b230: edx bytes at eax, big-endian; 1 to 3 of them signed. */
void readBigEndian(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 n = cpu.edx;
    reg32 value = 0, p = cpu.eax;
    for (reg32 left = n - 1; left != 0xffffffff; --left)
        value = (value << 8) + byte(app, p++);
    if (n == 1 && i32(value) > 0x7f)
        value -= 0x100;
    else if (n == 2 && i32(value) > 0x7fff)
        value -= 0x10000;
    else if (n == 3 && i32(value) > 0x7fffff)
        value -= 0x1000000;
    kept.ret(cpu, value);
    cpu.edx = 0xffffffff;
}

/* 0x5229d0: the next tag of a patch's: [eax] the place, read on; [edx] the
 * tag; for a tag with data, [ebx] its first up to 4 bytes as a number and
 * [ecx] where they are.  0xfc pads; 0xff ends (0); 0xfd and 0xfe have no
 * data.  A length of 0xff is followed by a 4-byte one. */
void nextTag(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 place = cpu.eax, tag = cpu.edx, number = cpu.ebx, data = cpu.ecx;
    reg32 p = at(app, place);
    while (byte(app, p) == 0xfc)
        put(app, place, ++p);
    const reg32 t = byte(app, p);
    put(app, tag, t);
    if (t == 0xff)
    {
        kept.ret(cpu, 0);
        return;
    }
    reg32 q = at(app, place) + 1;
    put(app, place, q);
    if (t == 0xfd || t == 0xfe)
    {
        kept.ret(cpu, 1);
        return;
    }
    reg32 length = byte(app, q);
    if (length == 0xff)
    {
        put(app, place, q + 1);
        if (!callWith(app, cpu, 0x52b230, q + 1, 4))
            return;
        length = cpu.eax;
        put(app, place, at(app, place) + 3);
    }
    put(app, place, at(app, place) + 1);
    if (i32(length) >= 0 && i32(length) <= 4)
    {
        if (!callWith(app, cpu, 0x52b230, at(app, place), length))
            return;
        put(app, number, cpu.eax);
        put(app, data, at(app, place));
    }
    put(app, place, at(app, place) + length);
    kept.ret(cpu, 1);
    cpu.ecx = length;
    cpu.edx = at(app, place);
}

/* 0x5222f0: volume edx panned by eax (0..127, 64 the middle) into [ebx]
 * left and [ecx] right, the far side scaled down. */
void panSplit(App* app, CPU& cpu)
{
    const i32 pan = i32(cpu.eax), volume = i32(cpu.edx);
    put(app, cpu.ebx, reg32(volume));
    put(app, cpu.ecx, reg32(volume));
    if (pan < 0x40)
    {
        cpu.eax = reg32(mul(pan, volume) >> 6);
        put(app, cpu.ecx, cpu.eax);
    }
    else if (pan > 0x40)
    {
        cpu.ecx = reg32(0x7f - pan);
        cpu.eax = reg32(mul(0x7f - pan, volume) >> 6);
        put(app, cpu.ebx, cpu.eax);
    }
    cpu.esp += 4;
}

/* 0x52b1c0: volume edx at angle eax (the circle in 0x10000ths) into [ebx]
 * and [ecx], each at most 0x7f: the volume times 1 - sin and 1 + sin, from
 * the quarter table at 0x5672ac. */
void panLaw(App* app, CPU& cpu)
{
    const reg32 volume = cpu.edx, left = cpu.ebx, right = cpu.ecx;
    reg32 a = reg32(i32(cpu.eax) >> 6);
    const reg32 negative = (a & 0x200) ? 0xffffffff : 0;
    const reg32 mirrored = (a & 0x100) ? 0xffffffff : 0;
    const reg32 index = ((a ^ mirrored) & 0xff) - mirrored;
    const reg32 sine = (at(app, 0x5672ac + index * 4) ^ negative) - negative;
    const reg32 l = (reg32(0x10000) - sine) * volume >> 16;
    put(app, left, l);
    if (i32(l) > 0x7f)
        put(app, left, 0x7f);
    const reg32 r = volume * (sine + 0x10000) >> 16;
    put(app, right, r);
    if (i32(r) > 0x7f)
        put(app, right, 0x7f);
    cpu.eax = l;
    cpu.ecx = reg32(0x10000) - sine;
    cpu.edx = sine + 0x10000;
    cpu.esp += 4;
}

/* 0x5224b0: panLaw, both sides made positive. */
void panLawPositive(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 left = cpu.ebx, right = cpu.ecx;
    if (!call(app, cpu, 0x52b1c0))
        return;
    reg32 eax = cpu.eax;
    const reg32 ecx = cpu.ecx;
    const reg32 l = at(app, left), r = at(app, right);
    if (i32(l) < 0)
        put(app, left, eax = 0u - l);
    if (i32(r) < 0)
        put(app, right, eax = 0u - r);
    kept.ret(cpu, eax);
    cpu.ecx = ecx;
    cpu.edx = l;
    cpu.ebx = r;
}

/* 0x522320 (stdcall, 8): panLaw for a voice played in Dolby surround: from
 * the surround's two levels on the stack, the side that is turned around. */
void panSurround(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 angle = cpu.eax, left = cpu.ebx, right = cpu.ecx;
    const i32 a = s32(app, kept.esp + 4), b = s32(app, kept.esp + 8);
    cpu.esp = kept.frame(3, 4);
    put(app, cpu.esp, angle);
    if (!call(app, cpu, 0x52b1c0))
        return;
    reg32 q;
    if (a >= 0 && b >= 0)
        q = b <= a ? 1 : 2;
    else if (a < 0 && b < 0)
        q = b <= a ? 2 : 1;
    else
    {
        const i32 ma = a <= 0 ? -a : a, mb = b <= 0 ? -b : b;
        q = ma <= mb ? 3 : 4;
    }
    reg32 side = 0, ecx;
    const bool front = !(i32(angle) < 0x4000 || i32(angle) >= 0xc000);
    if (front)
    {
        ecx = s32(app, left) >= s32(app, right) ? 4 : 3;
        if (i32(q) <= 2)
            side = ecx == 3 && q == 2 ? 1 : 2;
    }
    else
    {
        ecx = s32(app, left) >= s32(app, right) ? 1 : 2;
        if (i32(q) >= 3)
            side = ecx == 2 && q == 3 ? 1 : 2;
    }
    reg32 eax = q, ebx = (a >= 0 && b >= 0) || (a < 0 && b < 0) ? kept.ebx : reg32(a);
    if (a < 0)
        put(app, left, eax = 0u - at(app, left));
    if (b < 0)
    {
        ebx = at(app, right);
        put(app, right, eax = 0u - ebx);
    }
    if (side == 1)
        put(app, left, eax = 0u - at(app, left));
    else if (side == 2)
        put(app, right, eax = 0u - at(app, right));
    kept.ret(cpu, eax, 8);
    cpu.ecx = ecx;
    cpu.edx = side;
    cpu.ebx = ebx;
}

/* 0x500654: a channel's (eax) second volume, its effect send: the mean of its
 * two targets times the send's level (+3), to its second volume function. */
void setSendVolume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 c = cpu.eax;
    if (byte(app, c + 3) == 0)
    {
        putByte(app, c + 8, 0);
        kept.ret(cpu, c);
        return;
    }
    putByte(app, c + 8, reg8((sbyte(app, c + 4) + sbyte(app, c + 5)) >> 1));
    putByte(app, c + 8, reg8(mul(sbyte(app, c + 3), sbyte(app, c + 8)) >> 7));
    const reg32 level = reg32(sbyte(app, c + 8));
    if (!call(app, cpu, at(app, c + 0xddc), {c + 0xdc4, level, level}))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x5006a4: channel eax's volume to edx left, ebx right, ramped a step a
 * frame from where it is; and its send. */
void setMixVolume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const i32 left = i32(cpu.edx), right = i32(cpu.ebx);
    const reg32 c = channel(cpu.eax);
    putByte(app, c + 4, reg8(left));
    putByte(app, c + 5, reg8(right));
    putByte(app, c + 6, sbyte(app, c + 1) < left ? 1 : 0xff);
    const i32 now = sbyte(app, c + 2);
    putByte(app, c + 7, now < right ? 1 : 0xff);
    if (!callWith(app, cpu, 0x500654, c, reg32(now), reg32(right), kept.ecx))
        return;
    kept.ret(cpu, 0);
    cpu.edx = reg32(now);
}

/* 0x52b500: channel eax's send level to dl, and its send set. */
void setSendLevel(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 c = channel(cpu.eax);
    putByte(app, c + 3, cpu.dl);
    cpu.eax = c;
    if (!call(app, cpu, 0x500654))
        return;
    kept.ret(cpu, cpu.eax);
    cpu.edx = kept.edx;
}

/* 0x523310: voice eax's send level to ebx, but for a 3D voice. */
void setVoiceSend(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 index = cpu.eax, level = cpu.ebx;
    if (byte(app, platform(index) + 5) != 3 && !callWith(app, cpu, 0x52b500, index, level, level, kept.ecx))
        return;
    kept.ret(cpu, 0);
    cpu.edx = level;
}

/* 0x5014a0: what voice eax plays at (+0x31): its volume times the voice's,
 * the patch's and the master's, through its LFO and volume curve. */
void updateVoiceVolume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 v = voice(cpu.eax);
    i32 a = mul(shalf(app, v + 0x22), sbyte(app, v + 0x30));
    a = mul(a, shalf(app, v + 0x2a));
    a = mul(sbyte(app, kMasterVolume), a);
    reg32 eax = reg32(quotient(a, 0x1f417f));
    putByte(app, v + 0x31, reg8(eax));
    const reg32 lfo = at(app, v + 0x58);
    if (lfo != 0)
    {
        const i32 e = mul(sbyte(app, lfo + byte(app, v + 0x3e)), sbyte(app, v + 0x31));
        eax = reg32(quotient(e, 0x7f));
        putByte(app, v + 0x31, reg8(eax));
    }
    const reg32 curve = at(app, v + 0x4c);
    if (curve != 0)
    {
        const reg32 i = reg32(sbyte(app, v + 0x31));
        eax = (i & 0xffffff00) | byte(app, curve + i);
        putByte(app, v + 0x31, reg8(eax));
    }
    kept.ret(cpu, eax);
}

/* 0x501540 (iSNDvol): voice eax to volume edx on its channel, panned as it
 * is (with surround or not); eacsnd's for a 3D voice. */
void iSNDvol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax, volume = cpu.edx;
    const reg32 p = platform(index);
    const reg32 frame = kept.frame(5, 8);
    cpu.esp = frame;
    const reg32 method = byte(app, p + 5);
    if (method == 3)
    {
        cpu.eax = volume;
        cpu.edx = (volume & 0xffffff00) | method;
        if (!call(app, cpu, at(app, kDirectVol), {index, volume}))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (method == 0 || method == 2)
    {
        if (byte(app, p + 6) != 0)
        {
            if (!callWith(app, cpu, 0x5222f0, reg32(sbyte(app, voice(index) + 0xf)), volume, frame, frame + 4))
                return;
        }
        else if (!callWith(app, cpu, 0x5224b0, half(app, p + 0xa), volume, frame, frame + 4))
            return;
    }
    else if (method == 1)
    {
        reg32 angle = kept.ebp;
        if (byte(app, p + 6) != 0)
            angle = reg32((sbyte(app, voice(index) + 0xf) - 0x40) << 8);
        if (!callWith(app, cpu, 0x522320, angle, volume, frame, frame + 4,
                      {reg32(sbyte(app, p + 8)), reg32(sbyte(app, p + 9))}))
            return;
        putByte(app, p + 8, byte(app, frame));
        putByte(app, p + 9, byte(app, frame + 4));
    }
    else if (!fail(app, cpu, frame, kVolFile, kVolName, 0x30, {kVolText}))
        return;
    if (!callWith(app, cpu, 0x5006a4, index, at(app, frame), at(app, frame + 4)))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x502cb0: voice eax's pitch with its bend (through its curve) and its LFO. */
void updateVoicePitch(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 v = voice(cpu.eax);
    i32 pitch = shalf(app, v + 0x10);
    if (half(app, v + 0x42) != 0)
    {
        const reg32 curve = at(app, v + 0x54);
        const i32 e = curve != 0 ? sbyte(app, curve + byte(app, v + 0x33)) : i32(byte(app, v + 0x33));
        pitch += mul(e - 0x40, shalf(app, v + 0x42)) >> 6;
    }
    const reg32 lfo = at(app, v + 0x5c);
    if (lfo != 0)
        pitch += mul(sbyte(app, lfo + byte(app, v + 0x3f)) - 0x40, shalf(app, v + 0x40)) >> 6;
    putHalf(app, v + 0x12, reg16(pitch));
    kept.ret(cpu, v);
}

/* 0x522e90: 2 to the power eax/4096 as a float, on the x87's stack: the
 * table at 0x56adec holds it for each bit. */
void pitchFactor(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    x86::FPU& fpu = cpu.fpu;
    const reg32 table = 0x56adec;
    float f = 1.0f;
    i32 n = i32(cpu.eax);
    const bool down = n <= 0;
    if (down)
        n = mul(n, -1);
    reg32 bit = 1, k = 0;
    while (i32(bit) <= n)
    {
        if (bit & reg32(n))
        {
            const x86::Float t = x86::Float(app->getMemory<float>(table + k));
            f = float(down ? fpu.div(x86::Float(f), t) : fpu.mul(x86::Float(f), t));
        }
        bit += bit;
        k += 4;
    }
    fpu.push(x86::Float(f));
    kept.ret(cpu, reg32(n));
}

namespace
{

/* fild of a dword, the operations on st(0) as the x87 does them. */
void fild(CPU& cpu, i32 value) { cpu.fpu.push(x86::Float(value)); }

i32 fistp(CPU& cpu)
{
    const i32 value = cpu.fpu.toInteger<i32>(cpu.fpu.st(0));
    cpu.fpu.pop();
    return value;
}

}  // namespace

/* 0x522f10: the mixer's step for a sample of rate eax at pitch ebx, the mixer
 * at rate edx: rate * 2^(pitch/4096) / mix rate * [0x551af4], truncated. */
void mixStep(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const i32 rate = i32(cpu.eax), mixRate = i32(cpu.edx);
    cpu.esp = kept.frame(1, 8);
    cpu.eax = cpu.ebx;
    if (!call(app, cpu, 0x522e90))
        return;
    x86::FPU& fpu = cpu.fpu;
    fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(rate));
    fpu.st(0) = fpu.div(fpu.st(0), x86::Float(mixRate));
    fpu.st(0) = fpu.mul(fpu.st(0), x86::Float(app->getMemory<float>(0x551af4)));
    if (!call(app, cpu, kChop))
        return;
    const i32 step = fistp(cpu);
    kept.ret(cpu, reg32(step));
    cpu.edx = reg32(mixRate);
}

/* 0x522f50: channel eax's step to edx (at most 0x80000), through its
 * resampler's set function. */
void setMixStep(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 c = channel(cpu.eax);
    const reg32 step = cpu.edx > 0x80000 ? 0x80000 : cpu.edx;
    cpu.eax = c;
    cpu.edx = c + 0xd64;
    cpu.ecx = step;
    if (!call(app, cpu, at(app, c + 0xdb0), {c + 0xd64, step}))
        return;
    kept.ret(cpu, cpu.eax);
    cpu.edx = c + 0xd64;
}

/* 0x502d30 (iSNDplatformdetune): voice eax to pitch edx: its channel's step,
 * or eacsnd's rate for a 3D voice. */
void iSNDplatformdetune(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax, pitch = cpu.edx;
    const reg32 p = platform(index);
    const reg32 frame = kept.frame(3, 4);
    cpu.esp = frame;
    const reg32 method = byte(app, p + 5);
    if (method <= 2)
    {
        if (!callWith(app, cpu, 0x522f10, half(app, p), half(app, kMixRate), pitch, index))
            return;
        if (!callWith(app, cpu, 0x522f50, index, cpu.eax, pitch, index))
            return;
        kept.ret(cpu, 0);
        return;
    }
    if (method == 3)
    {
        if (!callWith(app, cpu, 0x522e90, pitch, p, pitch, index))
            return;
        put(app, frame, half(app, p));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), x86::Float(i32(half(app, p))));
        if (!call(app, cpu, kChop))
            return;
        const reg32 rate = reg32(fistp(cpu));
        put(app, frame, rate);
        cpu.eax = half(app, p);
        cpu.esi = rate;
        cpu.ecx = index;
        if (!call(app, cpu, at(app, kDirectRate), {index, rate}))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (!fail(app, cpu, frame, kDetuneFile, kDetuneName, 0x22, {kDetuneText}))
        return;
    kept.ret(cpu, 0xfffffff9);
}

/* 0x502df0 (iSNDplatform3dpos): voice eax to position dx, elevation ebx: its
 * channel's volumes panned by it (with surround or not), or eacsnd's. */
void iSNDplatform3dpos(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax, position = cpu.edx, elevation = cpu.ebx;
    const reg32 p = platform(index);
    const reg32 frame = kept.frame(3, 8);
    cpu.esp = frame;
    putByte(app, p + 6, 0);
    const reg32 method = byte(app, p + 5);
    putHalf(app, p + 0xa, reg16(position));
    const reg32 volume = reg32(sbyte(app, voice(index) + 0x31));
    if (method == 3)
    {
        cpu.eax = position;
        cpu.edx = elevation;
        if (!call(app, cpu, at(app, kDirectPos3d), {index, position, elevation}))
            return;
        kept.ret(cpu, cpu.eax);
        return;
    }
    if (method == 1)
    {
        if (!callWith(app, cpu, 0x522320, position, volume, frame, frame + 4,
                      {reg32(sbyte(app, p + 8)), reg32(sbyte(app, p + 9))}))
            return;
        putByte(app, p + 8, byte(app, frame));
        putByte(app, p + 9, byte(app, frame + 4));
    }
    else if (method == 0 || method == 2)
    {
        if (!callWith(app, cpu, 0x5224b0, position, volume, frame, frame + 4))
            return;
    }
    else if (!fail(app, cpu, frame, k3dPosFile, k3dPosName, 0x29, {k3dPosText}))
        return;
    if (!callWith(app, cpu, 0x5006a4, index, at(app, frame), at(app, frame + 4)))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x502ef0 (iSNDpan): voice eax to pan edx (0..127): its channel's volumes
 * split by it (with surround or not), or eacsnd's for a 3D voice. */
void iSNDpan(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax, pan = cpu.edx;
    const reg32 p = platform(index);
    const reg32 frame = kept.frame(5, 8);
    cpu.esp = frame;
    const reg32 method = byte(app, p + 5);
    putByte(app, p + 6, 1);
    const reg32 volume = reg32(sbyte(app, voice(index) + 0x31));
    if (method == 0 || method == 2)
    {
        if (!callWith(app, cpu, 0x5222f0, pan, volume, frame, frame + 4))
            return;
    }
    else
    {
        const reg32 angle = (pan - 0x40) << 8;
        if (method == 3)
        {
            cpu.eax = (index & 0xffff00ff) | method << 8;
            if (!call(app, cpu, at(app, kDirectPos3d), {index, angle, 0}))
                return;
            kept.ret(cpu, cpu.eax);
            return;
        }
        if (method == 1)
        {
            if (!callWith(app, cpu, 0x522320, angle, volume, frame, frame + 4,
                          {reg32(sbyte(app, p + 8)), reg32(sbyte(app, p + 9))}))
                return;
            putByte(app, p + 8, byte(app, frame));
            putByte(app, p + 9, byte(app, frame + 4));
        }
        else if (!fail(app, cpu, frame, kPanFile, kPanName, 0x2e, {kPanText}))
            return;
    }
    if (!callWith(app, cpu, 0x5006a4, index, at(app, frame), at(app, frame + 4)))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x500604 (iSNDmixstop): channel eax silenced at once -- its volume to 0 and
 * ramped there over a block -- freed, and the voice freed. */
void iSNDmixstop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(5);
    const reg32 index = cpu.eax;
    const reg32 c = channel(index);
    if (!callWith(app, cpu, 0x5006a4, index, 0, 0))
        return;
    if (!callWith(app, cpu, kRamp, c, 0x100, 0, cpu.ecx))
        return;
    if (!call(app, cpu, at(app, kEmms)))
        return;
    putByte(app, c, 0);
    cpu.eax = index;
    if (!call(app, cpu, at(app, kChannelEnded)))
        return;
    kept.ret(cpu, 0);
}

/* 0x4e25c0 (iSNDstop): voice eax stopped, on its channel or eacsnd's. */
void iSNDstop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 index = cpu.eax;
    const reg32 method = byte(app, platform(index) + 5);
    if (method <= 2)
    {
        if (!call(app, cpu, 0x500604))
            return;
    }
    else if (method == 3)
    {
        if (!call(app, cpu, at(app, kDirectStopBuf), {index}))
            return;
    }
    else
    {
        if (!fail(app, cpu, kept.frame(3), kDriverFile, kStopName, 0x3a3, {kStopText}))
            return;
        cpu.eax = 0xfffffff9;
    }
    kept.ret(cpu, cpu.eax);
}

/* 0x4e257c: the ret ending the driver's restore -- the tick calls it for
 * nothing. */
void soundIdle(App*, CPU& cpu)
{
    cpu.esp += 4;
}

/* 0x500c80: the library's 100 Hz tick: its clients (the streams), then each
 * playing voice's LFOs, volume ramp and envelope moved on, its pitch and
 * volume set again where they changed; a voice whose volume or envelope ran
 * out stopped.  ebp is left as the code leaves it -- the volume moved to, the
 * ramp's target, an envelope segment's ticks -- for iSNDvol takes a Dolby
 * voice's pan from it where none was set. */
void soundTick(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(6);
    putByte(app, kInTick, reg8(byte(app, kInTick) + 1));
    put(app, kTicks, at(app, kTicks) + 1);
    if (!call(app, cpu, 0x4e257c))
        return;
    for (i32 i = 0; i < sbyte(app, kClientCount); ++i)
        if (!callWith(app, cpu, at(app, kClients + 4 * i), reg32(4 * i), cpu.edx, reg32(i), cpu.ecx))
            return;
    reg32 ebp = kept.ebp;
    for (reg32 index = 0; index < kVoiceCount; ++index)
    {
        const reg32 v = voice(index);
        if (byte(app, v + 0xc) != 1 || s32(app, v) < 0)
            continue;
        cpu.ebp = ebp;
        if (at(app, v + 0x5c) != 0)
        {
            const reg8 place = reg8(byte(app, v + 0x3f) + 1);
            putByte(app, v + 0x3f, place);
            if (place >= byte(app, v + 0x3d))
                putByte(app, v + 0x3f, 0);
            if (!callWith(app, cpu, 0x502cb0, index, 1, v, v)
                || !callWith(app, cpu, 0x502d30, index, reg32(shalf(app, v + 0x12)), v, v))
                return;
        }
        bool changed = false;
        if (at(app, v + 0x58) != 0)
        {
            const reg8 place = reg8(byte(app, v + 0x3e) + 1);
            putByte(app, v + 0x3e, place);
            changed = true;
            if (place >= byte(app, v + 0x3c))
                putByte(app, v + 0x3e, 0);
        }
        bool stop = false;
        const i32 step = s32(app, v + 0x18);
        if (step != 0)
        {
            const i32 value = i32(at(app, v + 0x20) + reg32(step));
            changed = true;
            put(app, v + 0x20, reg32(value));
            const i32 target = s32(app, v + 0x1c);
            ebp = step < 0 ? reg32(target) : reg32(value);
            if (step < 0 ? value <= target : value >= target)
            {
                put(app, v + 0x18, 0);
                put(app, v + 0x20, reg32(target));
            }
            stop = s32(app, v + 0x20) < 0;
        }
        if (!stop)
        {
            const reg32 envelopeStep = at(app, v + 0x24);
            if (envelopeStep != 0)
            {
                put(app, v + 0x28, at(app, v + 0x28) + envelopeStep);
                changed = true;
            }
            if (at(app, v + 0x2c) == 0)
            {
                const reg8 segment = reg8(byte(app, v + 0x35) + 1);
                putByte(app, v + 0x35, segment);
                if (i8(segment) >= i8(byte(app, v + 0x34)))
                    stop = true;
                else
                {
                    const reg32 e = at(app, v + 0x48) + reg32(sbyte(app, v + 0x35)) * 8;
                    put(app, v + 0x2c, at(app, e));
                    if (s32(app, e) < 0)
                        put(app, v + 0x2c, 0x7fffffff);
                    const i32 to = i32((at(app, e + 4) << 16) - at(app, v + 0x28));
                    ebp = at(app, v + 0x2c);
                    put(app, v + 0x24, reg32(quotient(to, i32(ebp))));
                }
            }
            if (!stop)
            {
                put(app, v + 0x2c, at(app, v + 0x2c) - 1);
                if (changed)
                {
                    cpu.ebp = ebp;
                    if (!callWith(app, cpu, 0x5014a0, index, cpu.edx, v, v))
                        return;
                    if (s32(app, v) >= 0
                        && !callWith(app, cpu, 0x501540, index, reg32(sbyte(app, v + 0x31)), v, v))
                        return;
                }
                continue;
            }
        }
        cpu.ebp = ebp;
        if (!callWith(app, cpu, 0x4e9670, at(app, v), cpu.edx, v, v))
            return;
    }
    putByte(app, kInTick, reg8(byte(app, kInTick) - 1));
    kept.ret(cpu, cpu.eax);
}

namespace
{

bool enter(App* app, CPU& cpu) { return call(app, cpu, 0x500e20); }
bool leave(App* app, CPU& cpu) { return call(app, cpu, 0x500e7c); }

/* voiceOf as the code calls it. */
bool find(App* app, CPU& cpu, reg32 handle, i32& index)
{
    if (!callWith(app, cpu, 0x4ffc9c, handle))
        return false;
    index = i32(cpu.eax);
    return true;
}

/* Whether voice w plays a sound of group `group`. */
bool inGroup(App* app, reg32 w, reg32 group)
{
    return byte(app, w + 0x3b) == group && byte(app, w + 0xc) == 1 && s32(app, w) >= 0;
}

}  // namespace

/* 0x4e9670 (SNDstop): the sound of handle eax stopped -- its voice, or every
 * voice of its group.  0, -8 for no such sound, -10 before SNDinit. */
void SNDstop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(4);
    const reg32 handle = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index))
        return;
    reg32 result = 0;
    if (index < 0)
        result = 0xfffffff8;
    else
    {
        const reg32 group = byte(app, voice(reg32(index)) + 0x3b);
        if (group == 0)
        {
            if (!callWith(app, cpu, 0x4e25c0, reg32(index)))
                return;
        }
        else
            for (reg32 j = 0; j < kVoiceCount; ++j)
                if (inGroup(app, voice(j), group) && !callWith(app, cpu, 0x4e25c0, j))
                    return;
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e8fd0 (SNDstatus): 0 while the sound of handle eax plays, 1 when it
 * no longer does, -10 before SNDinit. */
void SNDstatus(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 handle = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index) || !leave(app, cpu))
        return;
    kept.ret(cpu, index < 0 ? 1 : 0);
}

/* 0x4e9010 (SNDstopall): every voice's sound stopped. */
void SNDstopall(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    for (reg32 i = 0; i < kVoiceCount; ++i)
        if (!callWith(app, cpu, 0x4e9670, at(app, voice(i)), i * kVoiceSize + kVoiceSize))
            return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e9420 (SNDautovol): the sound of handle eax (its group's voices) to
 * volume ebx over edx ticks (at least 1); its result in edx too. */
void SNDautovol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(4);
    const reg32 handle = cpu.eax;
    i32 ticks = i32(cpu.edx);
    const i32 target = i32(cpu.ebx);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        cpu.edx = cpu.eax;
        return;
    }
    if ((target > 0x7f || target < -1)
        && !fail(app, cpu, kept.frame(4), kAutovolFile, kAutovolName, 0x40, {kAutovolText, reg32(target)}))
        return;
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index))
        return;
    if (index < 0)
    {
        if (!leave(app, cpu))
            return;
        kept.ret(cpu, 0xfffffff8);
        cpu.edx = cpu.eax;
        return;
    }
    const reg32 v = voice(reg32(index));
    if (ticks <= 0)
        ticks = 1;
    const reg32 group = byte(app, v + 0x3b);
    const reg32 to = reg32(target) << 16;
    for (reg32 j = 0; j < kVoiceCount; ++j)
    {
        const reg32 w = voice(j);
        if (group == 0 ? w != v : !inGroup(app, w, group))
            continue;
        put(app, w + 0x1c, to);
        put(app, w + 0x18, reg32(quotient(i32(to - at(app, w + 0x20)), ticks)));
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, 0);
    cpu.edx = 0;
    // A lone voice's way leaves ebx shifted.
    if (group == 0)
        cpu.ebx = to;
}

/* 0x4e9540: the sound of handle eax (its group's voices) to volume edx at
 * once, in the library's lock; -8 for no such sound. */
void setSoundVolume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 volume = cpu.edx;
    i32 index;
    if (!find(app, cpu, cpu.eax, index))
        return;
    if (index < 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const reg32 v = voice(reg32(index));
    const reg32 to = volume << 16;
    if (to == at(app, v + 0x20))
    {
        kept.ret(cpu, 0);
        return;
    }
    const reg32 group = byte(app, v + 0x3b);
    cpu.esp -= 4;
    for (reg32 j = 0; j < kVoiceCount; ++j)
    {
        const reg32 w = voice(j);
        if (group == 0 ? w != v : !inGroup(app, w, group))
            continue;
        put(app, w + 0x20, to);
        put(app, w + 0x18, 0);
        if (!callWith(app, cpu, 0x5014a0, j) || !callWith(app, cpu, 0x501540, j, reg32(sbyte(app, w + 0x31))))
            return;
    }
    kept.ret(cpu, 0);
}

/* 0x4e95fc (SNDvol): setSoundVolume, the volume checked (0..127); its
 * result in edx too. */
void SNDvol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 handle = cpu.eax, volume = cpu.edx;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (i32(volume) > 0x7f || i32(volume) < 0)
    {
        if (!fail(app, cpu, kept.frame(4), kSvolFile, kSvolName, 0x7b, {kSvolText, volume}))
            return;
    }
    if (!enter(app, cpu) || !callWith(app, cpu, 0x4e9540, handle, volume))
        return;
    const reg32 result = cpu.eax;
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
    cpu.edx = result;
}

/* 0x4e9710: the sound of handle eax (its group's voices) to bend edx, where
 * the bend moves its pitch. */
void setSoundBend(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bend = cpu.edx;
    cpu.esp = kept.frame(4, 4);
    put(app, cpu.esp, bend);
    i32 index;
    if (!find(app, cpu, cpu.eax, index))
        return;
    if (index < 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const reg32 v = voice(reg32(index));
    const reg32 group = byte(app, v + 0x3b);
    for (reg32 j = 0; j < kVoiceCount; ++j)
    {
        const reg32 w = voice(j);
        if (group == 0 ? w != v : !inGroup(app, w, group))
            continue;
        if (byte(app, w + 0x33) == bend || half(app, w + 0x42) == 0)
            continue;
        putByte(app, w + 0x33, reg8(bend));
        if (!callWith(app, cpu, 0x502cb0, j) || !callWith(app, cpu, 0x502d30, j, reg32(shalf(app, w + 0x12))))
            return;
    }
    kept.ret(cpu, 0);
}

/* 0x4e97e4 (SNDpitchbend): setSoundBend, the bend checked (0..127). */
void SNDpitchbend(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 handle = cpu.eax, bend = cpu.edx;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (i32(bend) < 0 || i32(bend) > 0x7f)
    {
        // The registers the code pushes around the call, which the text's %i reads.
        put(app, kept.frame(2), kept.edi);
        put(app, kept.frame(3), kept.esi);
        put(app, kept.frame(4), kept.ebx);
        if (!fail(app, cpu, kept.frame(4), kBendFile, kBendName, 0x78, {kBendText}))
            return;
    }
    if (!enter(app, cpu) || !callWith(app, cpu, 0x4e9710, handle, bend))
        return;
    const reg32 result = cpu.eax;
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e9850: the sound of handle eax (its group's voices) to 3D position dx,
 * elevation ebx (clamped to -0x4000..0x3fff). */
void SNDpos3d(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    const reg32 position = cpu.edx & 0xffff;
    i32 elevation = i32(cpu.ebx);
    if (elevation > 0x3fff)
        elevation = 0x3fff;
    else if (elevation < -0x4000)
        elevation = -0x4000;
    cpu.esp = kept.frame(3, 4);
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index))
        return;
    reg32 result = 0;
    if (index < 0)
        result = 0xfffffff8;
    else
    {
        cpu.esp -= 4;
        const reg32 v = voice(reg32(index));
        const reg32 group = byte(app, v + 0x3b);
        for (reg32 j = 0; j < kVoiceCount; ++j)
        {
            const reg32 w = voice(j);
            if (group == 0 ? w != v : !inGroup(app, w, group))
                continue;
            if (!callWith(app, cpu, 0x502df0, j, position, reg32(elevation)))
                return;
        }
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e9950 (SNDpan): the sound of handle eax (its group's voices) to pan edx
 * (0..127): spread about the middle by each voice's spread, moved by the
 * patch's pan, through a pan curve. */
void SNDpan(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 handle = cpu.eax;
    const i32 pan = i32(cpu.edx);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    cpu.esp = kept.frame(5, 8);
    if ((pan > 0x7f || pan < 0) && !fail(app, cpu, kept.frame(5, 8), kSpanFile, kSpanName, 0x47, {kSpanText, reg32(pan)}))
        return;
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index))
        return;
    reg32 result = 0;
    if (index < 0)
        result = 0xfffffff8;
    else if (sbyte(app, voice(reg32(index)) + 0x45) != pan)
    {
        const reg32 v = voice(reg32(index));
        putByte(app, v + 0x45, reg8(pan));
        const i32 offset = pan - 0x40;
        const reg32 group = byte(app, v + 0x3b);
        for (reg32 j = 0; j < kVoiceCount; ++j)
        {
            const reg32 w = voice(j);
            if (group == 0 ? w != v : !inGroup(app, w, group))
                continue;
            i32 p = pan;
            if (byte(app, w + 0x37) != 1)
                p = mul(sbyte(app, w + 0x37), offset) + 0x40;
            p += sbyte(app, w + 0x32) - 0x40;
            if (p > 0x7f)
                p = 0x7f;
            else if (p < 0)
                p = 0;
            const reg32 curve = at(app, w + 0x50);
            if (curve != 0)
                p = sbyte(app, curve + reg32(p));
            putByte(app, w + 0xf, reg8(p));
            if (!callWith(app, cpu, 0x502ef0, j, reg32(p)))
                return;
        }
    }
    if (!leave(app, cpu))
        return;
    kept.ret(cpu, result);
}

/* 0x4e9b20 (SNDplaysetdef): a play's options at eax to their defaults. */
void SNDplaysetdef(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 options = cpu.eax;
    if (options == 0 && !fail(app, cpu, kept.frame(4), kSetdefFile, kSetdefName, 0x37, {kSetdefText}))
        return;
    put(app, options, 0xffffffff);
    const reg8 bytes[] = {0xff, 0x3c, 0x7f, 0x40, 0x7f, 0x40, 0x7f, 0};
    for (reg32 i = 0; i < 8; ++i)
        putByte(app, options + 4 + i, bytes[i]);
    putHalf(app, options + 0xc, 0);
    putHalf(app, options + 0xe, 0);
    kept.ret(cpu, 0);
}

/* 0x4e9bf8: the patch a play's options name (+0 the patch, +4 the bank)
 * played; -8 for none. */
void playOptions(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 options = cpu.eax;
    const reg32 bank = reg32(sbyte(app, options + 4));
    if (!callWith(app, cpu, 0x502570, bank))
        return;
    reg32 result = 0xfffffff8;
    if (i32(cpu.eax) >= 0)
    {
        const reg32 b = at(app, kBanks + bank * 12);
        const reg32 patch = at(app, options);
        if (i32(patch) >= 0 && i32(half(app, b + 6)) > i32(patch))
        {
            const reg32 pointer = at(app, b + patch * 4 + (byte(app, b + 4) == 4 ? 0x14 : 0xc));
            if (!callWith(app, cpu, 0x501de8, pointer, options))
                return;
            result = cpu.eax;
        }
    }
    kept.ret(cpu, result);
}

/* 0x4e9ba0 (SNDplay): playOptions; -10 before SNDinit. */
void SNDplay(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    const reg32 options = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (options == 0 && !fail(app, cpu, kept.frame(4), kPlayFile, kPlayName, 0x9f, {kPlayText}))
        return;
    if (!callWith(app, cpu, 0x4e9bf8, options, 0))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x501670: what the sound of handle eax plays at (+0x31), -8 for none. */
void soundVolume(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    const reg32 handle = cpu.eax;
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    i32 index;
    if (!enter(app, cpu) || !find(app, cpu, handle, index) || !leave(app, cpu))
        return;
    kept.ret(cpu, index < 0 ? 0xfffffff8 : reg32(sbyte(app, voice(reg32(index)) + 0x31)));
}

/* 0x501938: a new group's number: one past the last that no playing voice
 * has, never 0. */
void newGroup(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg8 group = byte(app, kGroupSerial);
    bool taken = true;
    while (taken)
    {
        if (++group == 0)
            ++group;
        taken = false;
        for (reg32 i = 0; i < kVoiceCount && !taken; ++i)
            taken = byte(app, voice(i) + 0xc) != 0 && byte(app, voice(i) + 0x3b) == group;
    }
    putByte(app, kGroupSerial, group);
    kept.ret(cpu, group);
}

}  // namespace snd
}  // namespace nfs3hp
