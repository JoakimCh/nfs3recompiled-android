#include "native_snd.h"

/* EA's SND library, native (native_snd.cpp says how): what a sound is played
 * from.  A bank (SNDbankadd) holds patches; a patch is a stream of tags --
 * each a byte, its data's length and up to 4 bytes of it -- that set up
 * timbres (0xfe ends one), each played on voices of their own when the key
 * and velocity asked for are in its ranges; a timbre's sample (0xfd starts
 * its platform part) is played on a mixer's channel by iSNDplatformplay and
 * iSNDmixstart.  When a bank is added its patches' offsets become addresses
 * and each sample's place is written into its tags (iSNDresolvetaggedpatch).
 *
 * A timbre's settings, 0x98 bytes as iSNDplaytaggedpatch builds them on its
 * stack: dword i is tag i's number, and 0x98 bytes on its data's place --
 * +4/+8 the velocities and +0xc/+0x10 the keys it plays for, +0x14 the voices'
 * mask, +0x18 their priority, +0x1c the key it was sampled at, +0x20/+0x24
 * the envelope's ... , +0x2c how many voices, +0x30/+0x34 the pan and its
 * randomness, +0x38/+0x3c the volume and its, +0x40 the pitch, +0x44 its
 * randomness, +0x48.. curves, +0x64 the envelope, +0x70 its start, +0x74..
 * the LFOs, +0x90 whether the play's pitch counts, +0x94 the pan's spread. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kTagPatchFile = 0x54e638, kTimbreName = 0x54e648, kPatchName = 0x54e730;
constexpr reg32 kResolveName = 0x54e7ac;
constexpr reg32 kInfoFile = 0x54e890, kInfoName = 0x54e8a0;
constexpr reg32 kRemovePatFile = 0x54e910, kRemovePatName = 0x54e920;
constexpr reg32 kBankAllocFile = 0x54e960, kBankAllocName = 0x54e970;
constexpr reg32 kDownloadFile = 0x54e9b4, kDownloadName = 0x54e9c4;
constexpr reg32 kPlayPlatformFile = 0x55194c, kPlayPlatformName = 0x55195c;
constexpr reg32 kResolveFile = 0x551a10, kPlatformResolveName = 0x551a20;
constexpr reg32 kMixerFile = 0x54e184, kMixStartName = 0x54e1cc;
constexpr reg32 kPacketFile = 0x551bb0, kPacketName = 0x551bc0;
constexpr reg32 kCheckFile = 0x551c50, kCheckName = 0x551c60;
constexpr reg32 kRemoveFile = 0x54b10c, kRemoveName = 0x54b11c;
constexpr reg32 kAddFile = 0x54b198, kAddName = 0x54b1a4;
constexpr reg32 kHeaderSizeFile = 0x54b1d0, kHeaderSizeName = 0x54b1e0;
constexpr reg32 kHeaderCopyFile = 0x54b228, kHeaderCopyName = 0x54b238;
constexpr reg32 kPatPresentFile = 0x54dc24, kPatPresentName = 0x54dc34;
constexpr reg32 kMasterFile = 0x54ab28, kMasterName = 0x54ab38;

constexpr reg32 kPatchId = 0x5450;          // 'PT'
constexpr reg32 kBankId = 0x6c4b4e42;       // 'BNKl'
constexpr reg32 kNextTag = 0x5229d0;
constexpr reg32 kRandomOffset = 0x5224e0;
constexpr reg32 kRemoveAllBanks = 0x4e8c1c;
constexpr reg32 kBankHook = 0xa09b24;       // what SNDrestore calls for the banks
constexpr reg32 kMoveMemory = 0x4ea4f0;     // EA's memmove: eax to, edx from, ebx bytes
constexpr reg32 kDirectCreate3dBuf = 0x9ef638, kDirectRemoveBuf = 0x9ef63c, kDirectPlay3d = 0x9ef640;
// The mixer's functions for each format, set by iSNDmixinit: decoders' inits
// by format and compression (0x9f6a6c), volume inits, resampler inits.
constexpr reg32 kDecoderInits = 0x9f6a6c;

/* The tag reader as the code calls it, on the four words at `at`: the place,
 * the tag, the number, the data's place.  False when the game stopped. */
bool readTag(App* app, CPU& cpu, reg32 at, reg32& more)
{
    if (!callWith(app, cpu, kNextTag, at, at + 4, at + 8, at + 12))
        return false;
    more = cpu.eax;
    return true;
}

/* A patch's tags: past its 4-byte header, or 8 when bit 1 of byte 3 says. */
reg32 patchTags(App* app, reg32 patch)
{
    return patch + ((byte(app, patch + 3) & 2) ? 8 : 4);
}

}  // namespace

/* 0x5017c0: a timbre's settings that last the patch: one voice, the play's
 * pitch not counted, 0xf. */
void timbreDefaults(App* app, CPU& cpu)
{
    const reg32 t = cpu.eax;
    put(app, t, 1);
    put(app, t + 0x90, 0);
    put(app, t + 0x6c, 0xf);
    cpu.esp += 4;
}

/* 0x5017d8: a timbre's settings (eax) back to their defaults, its data's
 * places (edx, 0x98 bytes) cleared. */
void resetTimbre(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 t = cpu.eax, data = cpu.edx;
    for (reg32 i = 0; i < 0x98; i += 4)
        put(app, data + i, 0);
    const struct { reg32 at, value; } defaults[] = {
        {0x4, 0}, {0x8, 0x7f}, {0xc, 0}, {0x10, 0x7f}, {0x14, 0xffffffff}, {0x18, 0}, {0x1c, 0x3c},
        {0x20, 0xffffffff}, {0x24, 1}, {0x28, 0}, {0x2c, 1}, {0x30, 0x40}, {0x34, 0}, {0x38, 0x7f},
        {0x3c, 0}, {0x40, 0}, {0x44, 0}, {0x48, 0}, {0x4c, 0}, {0x54, 0}, {0x5c, 0}, {0x70, 0x7f},
        {0x74, 0}, {0x78, 0}, {0x7c, 0}, {0x80, 0}, {0x84, 0}, {0x8c, 0}, {0x88, 0}, {0x94, 1},
        {0x64, 0x5678a8}};
    for (const auto& d : defaults)
        put(app, t + d.at, d.value);
    kept.ret(cpu, data + 0x98);
    cpu.edx = data + 0x98;
}

/* 0x5018dc: a play's own settings (edx) added to a timbre's (eax): the
 * curves', the LFOs', the envelope's (when it has one). */
void addTimbreDeltas(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 t = cpu.eax, d = cpu.edx;
    for (const reg32 field : {0x48u, 0x54u, 0x5cu, 0x74u, 0x80u})
        put(app, t + field, at(app, t + field) + at(app, d + field));
    if (at(app, t + 0x64) != 0)
        put(app, t + 0x64, at(app, t + 0x64) + at(app, d + 0x64));
    kept.ret(cpu, t);
}

/* 0x501978 (iSNDplaytaggedtimbre, stdcall 0x10): timbre ecx played as the
 * play's options ebx ask (their pan, volume, bend, effect level), the tags'
 * place of its sample edx, its data's places [esp+4], key [esp+8], velocity
 * [esp+0xc] and pitch offset [esp+0x10]: voices taken, set up from the timbre
 * and the sample started.  The handle, or what failed. */
void iSNDplaytaggedtimbre(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 sample = cpu.edx, options = cpu.ebx, timbre = cpu.ecx;
    const reg32 frame = kept.frame(3, 0x1c);
    cpu.esp = frame;
    const reg32 deltas = at(app, kept.esp + 4), key = at(app, kept.esp + 8);
    const reg32 velocity = at(app, kept.esp + 12), pitch = at(app, kept.esp + 16);
    put(app, frame + 4, sample);
    i32 pan = sbyte(app, options + 7);
    const i32 volume = sbyte(app, options + 8);
    const i32 bend = sbyte(app, options + 9);
    const i32 effect = sbyte(app, options + 10);
    put(app, frame + 0x18, reg32(pan));
    put(app, frame + 0x10, reg32(volume));
    put(app, frame + 0xc, reg32(bend));
    put(app, frame + 8, reg32(effect));
    if (!callWith(app, cpu, 0x5018dc, timbre, deltas))
        return;
    if ((volume < 0 || volume > 0x7f)
        && !fail(app, cpu, frame, kTagPatchFile, kTimbreName, 0x9e, {0x54e660, reg32(volume)}))
        return;
    if ((pan < 0 || pan > 0x7f) && !fail(app, cpu, frame, kTagPatchFile, kTimbreName, 0xa6, {0x54e694, reg32(pan)}))
        return;
    if ((effect < 0 || effect > 0x7f)
        && !fail(app, cpu, frame, kTagPatchFile, kTimbreName, 0xad, {0x54e6c4, reg32(effect)}))
        return;
    i32 patchPan = s32(app, timbre + 0x30);
    const reg32 panRandom = at(app, timbre + 0x34);
    if (panRandom != 0)
    {
        if (!callWith(app, cpu, kRandomOffset, panRandom, reg32(patchPan)))
            return;
        patchPan += i32(cpu.eax);
    }
    if (patchPan > 0x7f)
        patchPan = 0x7f;
    else if (patchPan < 0)
        patchPan = 0;
    put(app, frame + 0x14, reg32(patchPan));
    if ((bend < 0 || bend > 0x7f) && !fail(app, cpu, frame, kTagPatchFile, kTimbreName, 0xc3, {0x54e6f8, reg32(bend)}))
        return;
    if (!callWith(app, cpu, 0x4ff86c, at(app, timbre + 0x14), at(app, timbre + 0x2c), at(app, timbre + 0x18), frame))
        return;
    const reg32 index = cpu.eax;
    if (i32(index) < 0)
    {
        kept.ret(cpu, index, 0x10);
        return;
    }
    const reg32 v = voice(index);
    putByte(app, v + 0x37, byte(app, timbre + 0x94));
    putHalf(app, v + 0x10, half(app, timbre + 0x40));
    putHalf(app, v + 0x10, reg16(half(app, v + 0x10) - reg16((half(app, timbre + 0x1c) - key) * 0x64)));
    if (at(app, timbre + 0x90) != 0)
        putHalf(app, v + 0x10, reg16(half(app, v + 0x10) + reg16(pitch)));
    const reg32 pitchRandom = at(app, timbre + 0x44);
    if (pitchRandom != 0)
    {
        if (!callWith(app, cpu, kRandomOffset, pitchRandom))
            return;
        putHalf(app, v + 0x10, reg16(half(app, v + 0x10) + reg16(cpu.eax)));
    }
    put(app, v + 0x4c, at(app, timbre + 0x48));
    put(app, v + 0x50, at(app, timbre + 0x54));
    put(app, v + 0x54, at(app, timbre + 0x5c));
    putByte(app, v + 0xd, byte(app, timbre));
    put(app, v + 0x20, reg32(volume) << 16);
    putByte(app, v + 0x45, reg8(pan));
    put(app, v + 0x18, 0);
    if (byte(app, v + 0x37) != 1)
        pan = mul(sbyte(app, v + 0x37), pan - 0x40) + 0x40;
    pan = patchPan + pan - 0x40;
    if (pan < 0)
        pan = 0;
    else if (pan > 0x7f)
        pan = 0x7f;
    const reg32 panCurve = at(app, v + 0x50);
    if (panCurve != 0)
        pan = sbyte(app, panCurve + reg32(pan));
    put(app, frame + 0x18, reg32(pan));
    i32 level = s32(app, timbre + 0x38);
    const reg32 volumeRandom = at(app, timbre + 0x3c);
    if (volumeRandom != 0)
    {
        if (!callWith(app, cpu, kRandomOffset, volumeRandom, reg32(level)))
            return;
        level += i32(cpu.eax);
    }
    if (level > 0x7f)
        level = 0x7f;
    else if (level < -0x80)
        level = -0x80;
    putByte(app, v + 0x30, reg8(quotient(mul(level, i32(velocity)), 0x7f)));
    putByte(app, v + 0x32, reg8(patchPan));
    putByte(app, v + 0xf, reg8(pan));
    putHalf(app, v + 0x42, reg16(half(app, timbre + 0x28) * 0x64));
    putByte(app, v + 0x33, reg8(bend));
    put(app, v + 0x48, at(app, timbre + 0x64));
    putByte(app, v + 0x35, 0);
    put(app, v + 0x28, at(app, timbre + 0x70) << 16);
    putByte(app, v + 0x34, byte(app, timbre + 0x24));
    putByte(app, v + 0x36, byte(app, timbre + 0x20));
    const reg32 envelope = at(app, v + 0x48);
    put(app, v + 0x2c, at(app, envelope));
    if (s32(app, envelope) < 0)
        put(app, v + 0x2c, 0x7fffffff);
    put(app, v + 0x24, reg32(quotient(i32((at(app, envelope + 4) << 16) - at(app, v + 0x28)), s32(app, v + 0x2c))));
    put(app, v + 0x58, at(app, timbre + 0x74));
    put(app, v + 0x5c, at(app, timbre + 0x80));
    putByte(app, v + 0x3c, byte(app, timbre + 0x78));
    putByte(app, v + 0x3d, byte(app, timbre + 0x84));
    putHalf(app, v + 0x40, half(app, timbre + 0x88));
    putByte(app, v + 0x3e, 0);
    if (at(app, timbre + 0x7c) != 0)
    {
        if (!call(app, cpu, 0x4e0d88))
            return;
        putByte(app, v + 0x3e, reg8(cpu.eax % at(app, timbre + 0x78)));
    }
    putByte(app, v + 0x3f, 0);
    if (at(app, timbre + 0x8c) != 0)
    {
        if (!call(app, cpu, 0x4e0d88))
            return;
        putByte(app, v + 0x3f, reg8(cpu.eax % at(app, timbre + 0x84)));
    }
    if (!callWith(app, cpu, 0x502cb0, index))
        return;
    putByte(app, v + 0xb, byte(app, timbre + 0x6c));
    putByte(app, v + 0x38, byte(app, timbre + 0x4c));
    putByte(app, v + 0x39, reg8(effect));
    putByte(app, v + 0xa, byte(app, options + 4));
    putHalf(app, v + 8, half(app, options));
    if (!callWith(app, cpu, 0x5014a0, index))
        return;
    const reg32 level0 = reg32(quotient(mul(sbyte(app, v + 0x39), mul(sbyte(app, v + 0x38), s32(app, 0xa0a260))), 0x3f01));
    if (!callWith(app, cpu, 0x522510, sample, at(app, timbre), index, at(app, frame + 0x18),
                  {reg32(sbyte(app, v + 0x31)), reg32(shalf(app, v + 0x12)), level0, half(app, options + 0xc),
                   reg32(shalf(app, options + 0xe)), byte(app, options + 0xb) == 0 ? 1u : 0u}))
        return;
    const reg32 result = cpu.eax;
    if (i32(result) < 0)
    {
        if (!callWith(app, cpu, 0x4ffb64, index))
            return;
        kept.ret(cpu, result, 0x10);
        return;
    }
    kept.ret(cpu, at(app, frame), 0x10);
}

/* 0x501de8 (iSNDplaytaggedpatch): patch eax played as the options at edx
 * ask: its timbres read from its tags, each played whose ranges hold the
 * play's key and velocity; several voices made a group, ended by the last.
 * The last handle, or what failed (each timbre played then stopped again). */
void iSNDplaytaggedpatch(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 patch = cpu.eax, options = cpu.edx;
    const reg32 f = kept.frame(5, 0x1a4);
    cpu.esp = f;
    put(app, f + 0x18c, patch);
    put(app, f + 0x184, options);
    put(app, f + 0x188, 0xfffffff7);
    put(app, f + 0x198, 0);
    put(app, f + 0x19c, 0);
    put(app, f + 0x194, 0);
    if (patch == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const i32 velocity = sbyte(app, options + 6), key = sbyte(app, options + 5);
    if ((velocity < 0 || velocity > 0x7f)
        && !fail(app, cpu, f, kTagPatchFile, kPatchName, 0x1a8, {0x54e744, reg32(velocity)}))
        return;
    if ((key < 0 || key > 0x7f) && !fail(app, cpu, f, kTagPatchFile, kPatchName, 0x1b0, {0x54e778, reg32(key)}))
        return;
    put(app, f + 0x170, patchTags(app, patch));
    if (!callWith(app, cpu, 0x5017c0, f, f + 0x98) || !callWith(app, cpu, 0x5017d8, f, f + 0x98))
        return;
    if (!call(app, cpu, 0x500e20) || !call(app, cpu, 0x501938))
        return;
    put(app, f + 0x180, cpu.eax);
    put(app, f + 0x1a0, at(app, f + 0x198) * 4);
    reg32 samplePlace = kept.ebp;
    // A timbre played: its handle kept, or false when the play failed.
    auto play = [&](bool& failed) {
        failed = false;
        if (!callWith(app, cpu, 0x501978, at(app, f + 0x18c), samplePlace, at(app, f + 0x184), f,
                      {f + 0x98, reg32(key), reg32(velocity), at(app, f + 0x194)}))
            return false;
        put(app, f + 0x188, cpu.eax);
        if (i32(cpu.eax) < 0)
        {
            failed = true;
            return true;
        }
        put(app, f + 0x130 + at(app, f + 0x1a0), cpu.eax);
        return true;
    };
    const auto inRange = [&] {
        return velocity >= s32(app, f + 4) && velocity <= s32(app, f + 8) && key >= s32(app, f + 0xc)
            && key <= s32(app, f + 0x10);
    };
    bool failed = false;
    for (;;)
    {
        reg32 more;
        if (!readTag(app, cpu, f + 0x170, more))
            return;
        put(app, f + 0x190, at(app, f + 0x198) + 1);
        if (more == 0)
            break;
        const reg32 tag = at(app, f + 0x174);
        if (tag == 0xfd)
            samplePlace = at(app, f + 0x170);
        else if (tag == 0xfe)
        {
            if (inRange())
            {
                if (!play(failed))
                    return;
                if (failed)
                    break;
                put(app, f + 0x1a0, at(app, f + 0x1a0) + 4);
                put(app, f + 0x198, at(app, f + 0x190));
            }
            if (!callWith(app, cpu, 0x5017d8, f, f + 0x98))
                return;
        }
        else if (i32(tag) < 0x26)
        {
            put(app, f + tag * 4, at(app, f + 0x178));
            put(app, f + 0x98 + tag * 4, at(app, f + 0x17c));
            if (tag == 0x24)
            {
                if (!callWith(app, cpu, kRandomOffset, at(app, f + 0x178)))
                    return;
                put(app, f + 0x194, cpu.eax);
            }
        }
    }
    if (!failed && inRange())
    {
        if (!play(failed))
            return;
        if (!failed)
            put(app, f + 0x198, at(app, f + 0x190));
    }
    const reg32 count = at(app, f + 0x198);
    if (failed || count == 0)
    {
        if (!call(app, cpu, 0x500e7c))
            return;
        for (i32 i = 0; i < i32(count); ++i)
            if (!callWith(app, cpu, 0x4e9670, at(app, f + 0x130 + 4 * i)))
                return;
        kept.ret(cpu, at(app, f + 0x188));
        return;
    }
    if (count == 1)
    {
        if (!callWith(app, cpu, 0x4ffc9c, at(app, f + 0x130)))
            return;
        if (i32(cpu.eax) >= 0)
        {
            const reg32 v = voice(cpu.eax);
            putByte(app, v + 0x3b, 0);
            putByte(app, v + 0x3a, 0);
        }
    }
    else
    {
        for (i32 i = 0; i < i32(count); ++i)
        {
            if (!callWith(app, cpu, 0x4ffc9c, at(app, f + 0x130 + 4 * i)))
                return;
            if (i32(cpu.eax) < 0)
                continue;
            const reg32 v = voice(cpu.eax);
            putByte(app, v + 0x3a, 0);
            put(app, f + 0x19c, v);
            putByte(app, v + 0x3b, byte(app, f + 0x180));
        }
        putByte(app, at(app, f + 0x19c) + 0x3a, 1);
    }
    if (!call(app, cpu, 0x500e7c))
        return;
    kept.ret(cpu, at(app, f + 0x188));
}

/* 0x5021ac (iSNDresolvetaggedpatch): a patch's (eax) samples made addresses
 * from bank edx: each 0xfd's tags through iSNDplatformresolve; the patch
 * marked resolved.  The last's result. */
void iSNDresolvetaggedpatch(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 patch = cpu.eax, base = cpu.edx, other = cpu.ebx;
    const reg32 f = kept.frame(4, 0x14);
    cpu.esp = f;
    put(app, f + 0x10, patch);
    reg32 result = 0xffffffff;
    if (half(app, patch) != kPatchId && !fail(app, cpu, f, kTagPatchFile, kResolveName, 0x254, {0x54e7c4}))
        return;
    if (byte(app, patch + 2) != 0 && !fail(app, cpu, f, kTagPatchFile, kResolveName, 0x267, {0x54e7f4}))
        return;
    if ((byte(app, patch + 3) & 1) && !fail(app, cpu, f, kTagPatchFile, kResolveName, 0x26f, {0x54e82c}))
        return;
    put(app, f, patchTags(app, patch));
    for (;;)
    {
        reg32 more;
        if (!readTag(app, cpu, f, more))
            return;
        if (more == 0)
            break;
        if (at(app, f + 4) == 0xfd)
        {
            if (!callWith(app, cpu, 0x522a80, at(app, f), base, other))
                return;
            result = cpu.eax;
        }
    }
    if (i32(result) >= 0)
        putByte(app, patch + 3, byte(app, patch + 3) | 1);
    kept.ret(cpu, result);
}

/* 0x5022d0: a patch's (eax) samples let go of -- eacsnd's 3D buffers among
 * them, into edx's list -- and the patch no longer resolved. */
void unresolveTaggedPatch(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 patch = cpu.eax, list = cpu.edx;
    const reg32 f = kept.frame(4, 0x10);
    cpu.esp = f;
    put(app, f, patchTags(app, patch));
    reg32 more;
    for (;;)
    {
        if (!readTag(app, cpu, f, more))
            return;
        if (more == 0)
            break;
        if (at(app, f + 4) == 0xfd && !callWith(app, cpu, 0x522d08, at(app, f), list))
            return;
    }
    putByte(app, patch + 3, byte(app, patch + 3) & 0xfe);
    kept.ret(cpu, more);
}

/* 0x502330 (iSNDextracthdrinfo): what a patch's (eax) tags say of its
 * sample, into edx: +0 tag 0x13, +1 0x1b (0xf), +2 bits, +3 compression, +4
 * the rate (22050), +6 channels, +8 its length. */
void iSNDextracthdrinfo(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 patch = cpu.eax, info = cpu.edx;
    const reg32 f = kept.frame(4, 0x10);
    cpu.esp = f;
    if (patch == 0 && !fail(app, cpu, f - 4, kInfoFile, kInfoName, 0x11, {0x54e8b4}))
        return;
    if (half(app, patch) != kPatchId && !fail(app, cpu, f, kInfoFile, kInfoName, 0x17, {0x54e8e4}))
        return;
    put(app, f, patchTags(app, patch));
    put(app, info + 8, 0);
    putByte(app, info, 0);
    putByte(app, info + 1, 0xf);
    putByte(app, info + 2, 0);
    putByte(app, info + 3, 0);
    putByte(app, info + 6, 0);
    putHalf(app, info + 4, 0x5622);
    reg32 more;
    for (;;)
    {
        if (!readTag(app, cpu, f, more))
            return;
        if (more == 0)
            break;
        const reg32 tag = at(app, f + 4), number = at(app, f + 8);
        switch (tag)
        {
        case 0x13: putByte(app, info, reg8(number)); break;
        case 0x1b: putByte(app, info + 1, reg8(number)); break;
        case 0x81: putByte(app, info + 2, reg8(number)); break;
        case 0x82: putByte(app, info + 6, reg8(number)); break;
        case 0x84: putHalf(app, info + 4, reg16(number)); break;
        case 0x83: putByte(app, info + 3, reg8(number)); break;
        case 0x85: put(app, info + 8, number); break;
        default: break;
        }
    }
    kept.ret(cpu, more);
}

/* 0x502570: whether bank eax is there to use: 0; -8 for none, -18 while it
 * is loaded. */
void bankUsable(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax;
    reg32 result = 0xfffffff8;
    if (i32(bank) >= 0 && i32(bank) < 0x18 && at(app, kBanks + bank * 12) != 0)
        result = byte(app, kBanks + bank * 12 + 8) != 0 ? 0xffffffee : 0;
    kept.ret(cpu, result);
}

/* 0x5024a0 (iSNDbankremovepat): patch edx of bank eax let go of (ebx the 3D
 * buffers' list) and gone from the bank. */
void iSNDbankremovepat(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax, index = cpu.edx, list = cpu.ebx;
    cpu.esp = kept.frame(4);
    const reg32 b = at(app, kBanks + bank * 12);
    const reg32 version4 = byte(app, b + 4) == 4 ? b : 0;
    if (!callWith(app, cpu, 0x502570, bank, list))
        return;
    if (cpu.eax != 0 || i32(index) < 0 || i32(index) >= i32(half(app, b + 6)))
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const reg32 slot = byte(app, b + 4) == 4 ? version4 + index * 4 + 0x14 : b + index * 4 + 0xc;
    const reg32 patch = at(app, slot);
    if (patch == 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    if (half(app, patch) != kPatchId && !fail(app, cpu, kept.frame(4), kRemovePatFile, kRemovePatName, 0x25, {0x54e934}))
        return;
    if (!callWith(app, cpu, 0x5022d0, patch, list))
        return;
    put(app, byte(app, b + 4) == 4 ? version4 + index * 4 + 0x14 : b + index * 4 + 0xc, 0);
    kept.ret(cpu, 0);
}

/* 0x5025b0 (iSNDbankalloc): the first free bank handle; -9 for none. */
void iSNDbankalloc(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    for (reg32 i = 0; i < 0x18; ++i)
        if (at(app, kBanks + i * 12) == 0)
        {
            kept.ret(cpu, i);
            return;
        }
    if (!fail(app, cpu, kept.frame(5), kBankAllocFile, kBankAllocName, 0x10, {0x54e980}))
        return;
    kept.ret(cpu, 0xfffffff7);
}

/* 0x502620 (iSNDdownloadbank): bank eax's patches made addresses (their
 * offsets from the bank's table) and resolved against edx.  7, or 8 when one
 * of them was not. */
void iSNDdownloadbank(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax, base = cpu.edx;
    const reg32 f = kept.frame(5, 0xc10);
    cpu.esp = f;
    put(app, f + 0xc04, base);
    put(app, f + 0xc00, 7);
    for (reg32 i = 0; i < 0xc00; i += 0xc)
        put(app, f + i, 0xffffffff);
    const reg32 version = byte(app, bank + 4);
    if (version != 4 && version != 2
        && !fail(app, cpu, f, kDownloadFile, kDownloadName, 0x1b, {0x54e9d8, version}))
        return;
    put(app, f + 0xc0c, bank + 0x14);
    put(app, f + 0xc08, bank + 0xc);
    for (reg32 i = 0, offset = 0; i32(i) < i32(half(app, bank + 6)); ++i, offset += 4)
    {
        const bool four = byte(app, bank + 4) == 4;
        const reg32 slot = bank + offset + (four ? 0x14 : 0xc);
        const reg32 p = at(app, slot);
        if (p == 0)
            continue;
        const reg32 patch = at(app, f + (four ? 0xc0c : 0xc08)) + offset + p;
        put(app, slot, patch);
        if (!callWith(app, cpu, 0x5021ac, patch, at(app, f + 0xc04), f, offset))
            return;
        if (cpu.eax != 7)
            put(app, f + 0xc00, 8);
    }
    kept.ret(cpu, at(app, f + 0xc00));
}

/* 0x522a80 (iSNDplatformresolve): a sample's tags (eax) read; its place in
 * the bank made an address (edx the bank) where tag 0x8a's data is; a 3D
 * sample's buffer made by eacsnd.  8. */
void iSNDplatformresolve(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 base = cpu.edx;
    const reg32 f = kept.frame(4, 0x3c);
    cpu.esp = f;
    put(app, f, cpu.eax);
    put(app, f + 0x10, base);
    reg32 bits = 0x10, compression = 0, buffer = 0;
    put(app, f + 0x1c, 0);
    put(app, f + 0x38, 0);
    put(app, f + 0x24, 0);
    put(app, f + 0x28, 0);
    put(app, f + 0x20, 0x5622);
    put(app, f + 0x2c, 1);
    put(app, f + 0x34, 0xffffffff);
    put(app, f + 0x30, 0xffffffff);
    for (;;)
    {
        reg32 more;
        if (!readTag(app, cpu, f, more))
            return;
        if (more == 0)
            break;
        const reg32 tag = at(app, f + 4), number = at(app, f + 8), data = at(app, f + 0xc);
        if (tag == 0x88)
            put(app, f + 0x1c, number);
        else if (tag == 0x8a)
            put(app, f + 0x38, data);
        else if (tag == 0x93)
            buffer = data;
        else if (tag == 0x85)
            put(app, f + 0x28, number);
        else if (tag == 0x81)
            bits = number;
        else if (tag == 0x82)
            put(app, f + 0x2c, number);
        else if (tag == 0x84)
            put(app, f + 0x20, number);
        else if (tag == 0x83)
            compression = number;
        else if (tag == 0x86)
            put(app, f + 0x34, number);
        else if (tag == 0x87)
            put(app, f + 0x30, number);
        else if (tag == 0x92)
        {
            put(app, f + 0x24, number);
            put(app, f + 0x18, data);
        }
        else if (tag == 0xfe)
            break;
    }
    put(app, at(app, f + 0x38), base + at(app, f + 0x1c));
    if (at(app, f + 0x24) == 2)
    {
        if (buffer == 0 && !fail(app, cpu, f, kResolveFile, kPlatformResolveName, 0x4e, {0x551a34}))
            return;
        if (compression == 7)
            put(app, f + 0x14, 3);
        else if (compression == 9)
            put(app, f + 0x14, 4);
        else if (compression == 0)
        {
            if (bits == 0x10)
                put(app, f + 0x14, 0);
            else if (bits == 8)
                put(app, f + 0x14, 2);
            else if (!fail(app, cpu, f, kResolveFile, kPlatformResolveName, 0x65, {0x551a90, bits}))
                return;
        }
        else if (!fail(app, cpu, f, kResolveFile, kPlatformResolveName, 0x6d, {0x551ac4, compression}))
            return;
        cpu.eax = at(app, f + 0x28);
        cpu.ebx = at(app, f + 0x2c);
        cpu.ecx = at(app, f + 0x14);
        cpu.edx = at(app, f + 0x20);
        if (!call(app, cpu, at(app, kDirectCreate3dBuf),
                  {at(app, f + 0x2c), at(app, f + 0x14), at(app, f + 0x20), at(app, f + 0x28), at(app, f + 0x34),
                   at(app, f + 0x30), at(app, at(app, f + 0x38))}))
            return;
        put(app, buffer, cpu.eax);
        if (cpu.eax != 0)
            putByte(app, at(app, f + 0x18), 3);
        kept.ret(cpu, 8);
        cpu.ebx = at(app, f + 0x2c);
        return;
    }
    kept.ret(cpu, 8);
    cpu.ebx = at(app, f + 0x1c);
}

/* 0x522d08: a sample's tags (eax): its 3D buffer, if eacsnd made one, let go
 * of.  0, or eacsnd's answer. */
void platformUnresolve(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(5, 0x10);
    cpu.esp = f;
    put(app, f, cpu.eax);
    reg32 buffer = kept.esi, method = 0, place = kept.ebp;
    for (;;)
    {
        reg32 more;
        if (!readTag(app, cpu, f, more))
            return;
        if (more == 0)
            break;
        const reg32 tag = at(app, f + 4);
        if (tag == 0x93)
            buffer = at(app, f + 0xc);
        else if (tag == 0x92)
        {
            method = at(app, f + 8);
            place = at(app, f);
        }
        else if (tag == 0xfe)
            break;
    }
    if (method != 3)
    {
        kept.ret(cpu, 0);
        return;
    }
    putByte(app, place, 2);
    if (!call(app, cpu, at(app, kDirectRemoveBuf), {at(app, buffer)}))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x5000b8 (iSNDmixstart, stdcall 0x24): channel eax started on a sample:
 * edx its format (1, 2, 4 or 8: bytes a frame), ebx its compression (0, 7 XA
 * mono, 9 XA stereo), ecx how it plays (0 a stream, 1 once or looped, 2 in
 * packets); on the stack the sample, its length, its loop's start and end,
 * the left and right volumes, the step, the priority (above 0x19 the better
 * resampler) and the send level.  Each step's function picked from the
 * mixer's tables for the format, its state set up.  0. */
void iSNDmixstart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.eax, format = cpu.edx, compression = cpu.ebx, mode = cpu.ecx;
    const reg32 f = kept.frame(3, 8);
    cpu.esp = f;
    put(app, f, index);
    const reg32 c = channel(index);
    auto arg = [&](reg32 i) { return at(app, kept.esp + 4 * i); };
    const bool better = i32(arg(8)) > 0x19;
    reg32 decoder = kept.edi, resampler = kept.ebp;
    if (format & 4)
    {
        put(app, f + 4, at(app, 0x9f6ae4));
        decoder = 8;
        resampler = at(app, better ? 0x9f6b04 : 0x9f6af4);
    }
    else if (format & 8)
    {
        decoder = 0xc;
        put(app, f + 4, at(app, 0x9f6ae8));
        resampler = at(app, i32(arg(8)) > 0x19 ? 0x9f6b08 : 0x9f6af8);
    }
    else if (format & 1)
    {
        put(app, f + 4, at(app, 0x9f6adc));
        decoder = 0;
        resampler = at(app, better ? 0x9f6afc : 0x9f6aec);
    }
    else if (format & 2)
    {
        decoder = 4;
        put(app, f + 4, at(app, 0x9f6ae0));
        resampler = at(app, better ? 0x9f6b00 : 0x9f6af0);
    }
    else if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x105, {0x54e1dc}))
        return;
    if (compression != 0)
    {
        if (compression == 7)
        {
            if (format & 4)
                decoder = 0x10;
            else if (format & 8)
                decoder = 0x14;
            else if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x11d, {0x54e208}))
                return;
        }
        else if (compression == 9)
        {
            if (format & 4)
                decoder = 0x18;
            else if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x12b, {0x54e208}))
                return;
        }
        else if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x142, {0x54e22c}))
            return;
    }
    if (mode == 1)
    {
        if (i32(arg(4)) > 0)
            decoder += 1;
    }
    else if (mode == 2)
        decoder += 2;
    else if (mode == 0)
        decoder += 3;
    else if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x15a, {0x54e25c}))
        return;
    const reg32 init = kDecoderInits + decoder * 4;
    if (at(app, init) == 0)
    {
        if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x178, {0x54e284}))
            return;
    }
    else if (!callWith(app, cpu, at(app, init), index, c + 0xc, arg(1), arg(2), {arg(3), arg(4), c + 0xda8, c + 0xdac}))
        return;
    if (at(app, f + 4) == 0)
    {
        if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x18a, {0x54e2a8}))
            return;
    }
    else if (!call(app, cpu, at(app, f + 4), {c + 0xd90, c + 0xdc0, c + 0xdbc})
             || !call(app, cpu, at(app, f + 4), {c + 0xdc4, c + 0xde0, c + 0xddc}))
        return;
    if (resampler == 0)
    {
        if (!fail(app, cpu, f, kMixerFile, kMixStartName, 0x197, {0x54e2d4}))
            return;
    }
    else if (!call(app, cpu, resampler, {c + 0xd64, c + 0xdb0, c + 0xdb4, c + 0xdb8}))
        return;
    reg32 step = arg(7);
    if (step > 0x80000)
        put(app, kept.esp + 28, step = 0x80000);
    if (!call(app, cpu, at(app, c + 0xdb0), {c + 0xd64, step}))
        return;
    putByte(app, c + 1, reg8(arg(5)));
    putByte(app, c + 2, reg8(arg(6)));
    putByte(app, c + 4, reg8(arg(5)));
    putByte(app, c + 5, reg8(arg(6)));
    putByte(app, c + 3, reg8(arg(9)));
    if (!callWith(app, cpu, 0x500654, c, arg(6)))
        return;
    if (!call(app, cpu, at(app, c + 0xdbc), {c + 0xd90, arg(5), arg(6)}))
        return;
    putByte(app, c, 1);
    kept.ret(cpu, 0, 0x24);
}

namespace
{

/* A sample's frame: 4 for 16 bits mono, 8 stereo, 1 and 2 for 8 bits; 0
 * and an error for another. */
reg32 frameFormat(reg32 bits, reg32 channels)
{
    if (bits == 0x10 && channels == 1)
        return 4;
    if (bits == 0x10 && channels == 2)
        return 8;
    if (bits == 8 && channels == 1)
        return 1;
    if (bits == 8 && channels == 2)
        return 2;
    return 0;
}

}  // namespace

/* 0x522510 (iSNDplatformplay, stdcall 0x18): a sample's tags (eax) played on
 * voice ebx's channel, as edx (2: as a stream) and the pan ecx say, at
 * volume [esp+4], pitch [esp+8], send level [esp+0xc], 3D position
 * [esp+0x10] and elevation [esp+0x14], [esp+0x18] whether its pan is the
 * pan's or the position's.  On eacsnd's 3D buffer for a 3D sample, else on
 * the mixer: iSNDmixstart's result. */
void iSNDplatformplay(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.ebx, mode = cpu.edx, pan = cpu.ecx;
    const reg32 f = kept.frame(3, 0x5c);
    cpu.esp = f;
    auto arg = [&](reg32 i) { return at(app, kept.esp + 4 * i); };
    put(app, f + 8, cpu.eax);
    put(app, f + 0x20, mode);
    put(app, f + 0x24, index);
    put(app, f + 0x18, pan);
    reg32 loopStart = 0xffffffff, loopEnd = 0xffffffff, priority = 0;
    put(app, f + 0x38, 0);
    put(app, f + 0x34, 0);
    put(app, f + 0x44, 0);
    put(app, f + 0x3c, 0x5622);
    put(app, f + 0x4c, 1);
    put(app, f + 0x40, 0);
    put(app, f + 0x50, 0);
    put(app, f + 0x48, 0x10);
    const reg32 p = platform(index);
    put(app, f + 0x2c, p);
    put(app, f + 0x30, 0);
    putByte(app, p + 6, reg8(arg(6)));
    putHalf(app, p + 0xa, reg16(arg(4)));
    for (;;)
    {
        if (!callWith(app, cpu, kNextTag, f + 8, f + 0x58, f + 0xc, f + 0x10))
            return;
        if (cpu.eax == 0)
            break;
        const reg32 tag = at(app, f + 0x58), number = at(app, f + 0xc), data = at(app, f + 0x10);
        if (tag == 0x8a)
            put(app, f + 0x38, data);
        else if (tag == 0x93)
            put(app, f + 0x34, data);
        else if (tag == 0x85)
            put(app, f + 0x44, number);
        else if (tag == 0x81)
            put(app, f + 0x48, number);
        else if (tag == 0x82)
            put(app, f + 0x4c, number);
        else if (tag == 0x84)
            put(app, f + 0x3c, number);
        else if (tag == 0x83)
            put(app, f + 0x40, number);
        else if (tag == 0x86)
            loopStart = number;
        else if (tag == 0x87)
        {
            loopEnd = number;
            put(app, f + 0x30, 1);
        }
        else if (tag == 0x91)
            priority = number;
        else if (tag == 0x92)
            put(app, f + 0x50, number);
        else if (tag == 0xfe)
            break;
    }
    if (mode == 2)
    {
        loopStart = 0xffffffff;
        put(app, f + 0x44, 0);
        loopEnd = 0xffffffff;
    }
    else
    {
        if (i32(loopStart) < -1)
            loopStart = 0xffffffff;
        if (i32(loopEnd) < -1)
            loopEnd = 0xffffffff;
    }
    putHalf(app, p, reg16(at(app, f + 0x3c)));
    putByte(app, p + 2, byte(app, f + 0x48));
    putByte(app, p + 3, byte(app, f + 0x4c));
    putByte(app, p + 4, byte(app, f + 0x40));
    put(app, p + 0xc, at(app, f + 0x44));
    const reg32 method = at(app, f + 0x50);
    bool mixer = true;
    if (method == 1)
    {
        if (at(app, f + 0x4c) != 1 && !fail(app, cpu, f, kPlayPlatformFile, kPlayPlatformName, 0x7c, {0x551970}))
            return;
        if (arg(6) != 0)
            put(app, kept.esp + 16, (pan - 0x40) << 8);
        if (!callWith(app, cpu, 0x522320, arg(4), arg(1), f + 0x14, f + 0x1c,
                      {reg32(sbyte(app, p + 8)), reg32(sbyte(app, p + 9))}))
            return;
        putByte(app, p + 8, byte(app, f + 0x14));
        putByte(app, p + 9, byte(app, f + 0x1c));
        mixer = false;
    }
    else if (method == 3)
    {
        if (arg(6) != 0)
        {
            put(app, kept.esp + 16, (pan - 0x40) << 8);
            put(app, kept.esp + 20, 0);
        }
        if (!callWith(app, cpu, 0x522e90, arg(2), p, cpu.ebx, arg(5)))
            return;
        put(app, f + 0x54, half(app, p));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), x86::Float(i32(half(app, p))));
        cpu.esp = f - 0xc;
        if (!call(app, cpu, kChop))
            return;
        const auto rate = cpu.fpu.toInteger<std::int64_t>(cpu.fpu.st(0));
        cpu.fpu.pop();
        put(app, f, reg32(rate));
        put(app, f + 4, reg32(std::uint64_t(rate) >> 32));
        cpu.esp = f;
        if (!call(app, cpu, at(app, kDirectPlay3d),
                  {at(app, at(app, f + 0x34)), index, at(app, f + 0x30), reg32(rate), arg(1), arg(4), arg(5)}))
            return;
        if (i32(cpu.eax) >= 0)
        {
            putByte(app, p + 5, byte(app, f + 0x50));
            kept.ret(cpu, 0, 0x18);
            return;
        }
        put(app, f + 0x50, 0);
    }
    else if (method != 0 && method != 2)
    {
        if (!fail(app, cpu, f, kPlayPlatformFile, kPlayPlatformName, 0xad, {0x5519ac}))
            return;
        mixer = false;
    }
    if (mixer)
    {
        if (arg(6) == 0)
        {
            if (!callWith(app, cpu, 0x5224b0, arg(4), arg(1), f + 0x14, f + 0x1c))
                return;
        }
        else if (!callWith(app, cpu, 0x5222f0, pan, arg(1), f + 0x14, f + 0x1c))
            return;
    }
    const reg32 frameBytes = frameFormat(at(app, f + 0x48), at(app, f + 0x4c));
    if (frameBytes != 0)
        put(app, f + 0x28, frameBytes);
    else if (!fail(app, cpu, f, kPlayPlatformFile, kPlayPlatformName, 0xbe, {0x5519e0}))
        return;
    if (!callWith(app, cpu, 0x522f10, at(app, f + 0x3c), half(app, kMixRate), arg(2)))
        return;
    const reg32 step = cpu.eax;
    i32 level = i32(priority) + shalf(app, kMixRate + 2);
    if (level > 0x64)
        level = 0x64;
    else if (level < 0)
        level = 0;
    putByte(app, p + 5, byte(app, f + 0x50));
    if (!callWith(app, cpu, 0x5000b8, index, at(app, f + 0x28), at(app, f + 0x40), at(app, f + 0x20),
                  {at(app, at(app, f + 0x38)), at(app, f + 0x44), loopStart, loopEnd, at(app, f + 0x14),
                   at(app, f + 0x1c), step, reg32(level), arg(3)}))
        return;
    kept.ret(cpu, cpu.eax, 0x18);
}

/* 0x523d94 (iSNDplatformpacketplay, stdcall 0x10): channel edx started on
 * packets (a stream's), the sample described at [esp+0x10] (its rate, its
 * representation), pan ebx, volume ecx, pitch [esp+4], send level [esp+8],
 * priority [esp+0xc].  iSNDmixstart's result, -15 or -7. */
void iSNDplatformpacketplay(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 index = cpu.edx, pan = cpu.ebx, volume = cpu.ecx;
    const reg32 f = kept.frame(3, 0xc);
    cpu.esp = f;
    auto arg = [&](reg32 i) { return at(app, kept.esp + 4 * i); };
    i32 priority = i32(arg(3));
    const reg32 sample = arg(4);
    put(app, f + 8, index);
    const reg32 p = platform(index);
    putByte(app, p + 6, 1);
    putHalf(app, p + 0xa, 0);
    put(app, p + 0xc, 0);
    putHalf(app, p, half(app, sample));
    putByte(app, p + 3, byte(app, sample + 2) & 3);
    const reg32 representation = half(app, sample + 2) & 0xfffc;
    if (representation == 0xc)
    {
        putByte(app, p + 2, 0x10);
        putByte(app, p + 4, 7);
    }
    else if (representation == 0x10)
    {
        putByte(app, p + 2, 0x10);
        putByte(app, p + 4, 9);
    }
    else if (representation == 8)
    {
        putByte(app, p + 2, 8);
        putByte(app, p + 4, 0);
    }
    else if (representation == 0)
    {
        putByte(app, p + 2, 0x10);
        putByte(app, p + 4, 0);
    }
    else
    {
        if (!fail(app, cpu, f, kPacketFile, kPacketName, 0x44, {0x551bd8}))
            return;
        kept.ret(cpu, 0xfffffff1, 0x10);
        return;
    }
    if (!callWith(app, cpu, 0x5222f0, pan, volume, f, f + 4))
        return;
    const reg32 frameBytes = frameFormat(byte(app, p + 2), byte(app, p + 3));
    if (frameBytes == 0)
    {
        if (!fail(app, cpu, f, kPacketFile, kPacketName, 0x59, {0x551c18}))
            return;
        kept.ret(cpu, 0xfffffff9, 0x10);
        return;
    }
    if (!callWith(app, cpu, 0x522f10, half(app, p), half(app, kMixRate), arg(1)))
        return;
    const reg32 step = cpu.eax;
    priority += shalf(app, kMixRate + 2);
    if (priority > 0x64)
        priority = 0x64;
    else if (priority < 0)
        priority = 0;
    putByte(app, p + 5, 0);
    if (!callWith(app, cpu, 0x5000b8, index, frameBytes, reg32(sbyte(app, p + 4)), 0,
                  {0, 0, 0xffffffff, 0xffffffff, at(app, f), at(app, f + 4), step, reg32(priority), arg(2)}))
        return;
    kept.ret(cpu, cpu.eax, 0x10);
}

/* 0x523f90 (iSNDcheckplayopts): a play's options at eax checked: key,
 * velocity, volume, bend, effect level, then the elevation of a 3D one or the
 * pan, each an error when out of range. */
void iSNDcheckplayopts(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 options = cpu.eax;
    const reg32 f = kept.frame(6);
    cpu.esp = f;
    const struct { reg32 at, line, text; } checks[] = {
        {5, 0xa, 0x551c74}, {6, 0xd, 0x551cac}, {8, 0x10, 0x551ce8}, {9, 0x13, 0x551d1c}, {0xa, 0x16, 0x551d54}};
    reg32 eax = options;
    for (const auto& c : checks)
        if (sbyte(app, options + c.at) < 0)
        {
            if (!fail(app, cpu, f, kCheckFile, kCheckName, c.line, {c.text, reg32(sbyte(app, options + c.at))}))
                return;
            eax = cpu.eax;
        }
    if (byte(app, options + 0xb) != 0)
    {
        const i32 elevation = shalf(app, options + 0xe);
        if ((elevation < -0x4000 || elevation > 0x3fff)
            && !fail(app, cpu, f, kCheckFile, kCheckName, 0x20, {0x551dc4, reg32(elevation)}))
            return;
        if (elevation < -0x4000 || elevation > 0x3fff)
            eax = cpu.eax;
    }
    else if (sbyte(app, options + 7) < 0)
    {
        if (!fail(app, cpu, f, kCheckFile, kCheckName, 0x1b, {0x551d90, reg32(sbyte(app, options + 7))}))
            return;
        eax = cpu.eax;
    }
    kept.ret(cpu, eax);
}

/* 0x4e8bd0: the first edx patches of bank eax let go of. */
void removeBankPatches(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax, count = cpu.edx;
    const reg32 f = kept.frame(4, 0xc00);
    cpu.esp = f;
    for (reg32 i = 0; i < 0xc00; i += 0xc)
        put(app, f + i, 0xffffffff);
    for (i32 i = 0; i < i32(count); ++i)
        if (!callWith(app, cpu, 0x5024a0, bank, reg32(i), f, reg32(i + 1)))
            return;
    kept.ret(cpu, 0);
}

/* 0x4e8c28 (SNDbankremove): bank eax gone (every bank for -1): its sounds
 * stopped, its patches let go of, its handle free. */
void SNDbankremove(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (bank == 0xffffffff)
    {
        for (reg32 i = 0; i < 0x18; ++i)
            if (!callWith(app, cpu, 0x4e8c28, i, 0, 0, i + 1))
                return;
        kept.ret(cpu, 0);
        return;
    }
    if (byte(app, kBanks + bank * 12 + 8) != 0
        && !fail(app, cpu, kept.frame(3), kRemoveFile, kRemoveName, 0x6f, {0x54b12c}))
        return;
    if (!callWith(app, cpu, 0x502570, bank))
        return;
    if (cpu.eax != 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const reg32 b = at(app, kBanks + bank * 12);
    for (reg32 i = 0; i < kVoiceCount; ++i)
        if (reg32(sbyte(app, voice(i) + 0xa)) == bank && !callWith(app, cpu, 0x4e9670, at(app, voice(i))))
            return;
    cpu.esp -= 4;
    if (!callWith(app, cpu, 0x4e8bd0, bank, half(app, b + 6)))
        return;
    put(app, kBanks + bank * 12, 0);
    putByte(app, kBanks + bank * 12 + 8, 0);
    kept.ret(cpu, 0);
}

/* 0x4e8c1c: every bank gone (what SNDrestore calls). */
void removeAllBanks(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    if (!callWith(app, cpu, 0x4e8c28, cpu.eax, 0))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e8d20 (SNDbankadd): the bank at edx added: a handle into [eax], its
 * patches made addresses.  iSNDdownloadbank's result. */
void SNDbankadd(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 out = cpu.eax, bank = cpu.edx;
    cpu.esp = kept.frame(3);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (at(app, bank) != kBankId && !fail(app, cpu, kept.frame(5), kAddFile, kAddName, 0x5b, {0x54b1b0}))
        return;
    if (!call(app, cpu, 0x5025b0))
        return;
    const reg32 handle = cpu.eax;
    put(app, out, handle);
    put(app, kBanks + handle * 12, bank);
    put(app, kBanks + handle * 12 + 4, bank);
    put(app, kBankHook, kRemoveAllBanks);
    if (!callWith(app, cpu, 0x502620, bank, bank))
        return;
    kept.ret(cpu, cpu.eax);
}

/* 0x4e8db0 (SNDbankheadersize): the size of bank eax's header. */
void SNDbankheadersize(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 bank = cpu.eax;
    cpu.esp = kept.frame(1);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (!callWith(app, cpu, 0x502570, bank))
        return;
    if (cpu.eax != 0 && !fail(app, cpu, kept.frame(4), kHeaderSizeFile, kHeaderSizeName, 0x47, {0x54b1f4}))
        return;
    kept.ret(cpu, at(app, at(app, kBanks + bank * 12) + 8));
}

/* 0x4e8e20 (SNDbankheadercopy): bank edx's header copied to eax, which the
 * bank is then: its patches' addresses moved with it. */
void SNDbankheadercopy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 to = cpu.eax, bank = cpu.edx;
    const reg32 f = kept.frame(4, 0xc);
    cpu.esp = f;
    put(app, f, bank);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    if (to == 0)
    {
        if (!fail(app, cpu, f, kHeaderCopyFile, kHeaderCopyName, 0x4c, {0x54b24c}))
            return;
        // As the code loads the where-and-what: in edx, ecx and ebx.
        cpu.edx = kHeaderCopyFile;
        cpu.ecx = kHeaderCopyName;
        cpu.ebx = 0x4c;
    }
    if (!callWith(app, cpu, 0x4e8db0, at(app, f)))
        return;
    const reg32 size = cpu.eax;
    if (i32(size) < 0)
    {
        kept.ret(cpu, size);
        return;
    }
    cpu.esp = f - 4;
    put(app, f + 4, to);
    put(app, f + 8, to);
    const reg32 entry = at(app, f) * 12;
    if (!callWith(app, cpu, 0x4ea4f0, at(app, kBanks + entry), to, size, entry))
        return;
    const reg32 from = at(app, kBanks + entry);
    for (reg32 i = 0, offset = 0; i32(i) < i32(half(app, from + 6)); ++i, offset += 4)
    {
        if (byte(app, from + 4) == 4)
        {
            const reg32 p = at(app, from + offset + 0x14);
            if (p != 0)
                put(app, to + offset + 0x14, p - from + to);
        }
        else
        {
            const reg32 p = at(app, from + offset + 0xc);
            if (p != 0)
                put(app, to + offset + 0xc, p - from + to);
        }
    }
    put(app, kBanks + at(app, f) * 12, to);
    kept.ret(cpu, 0);
}

/* 0x4fb1e0 (SNDbankpatpresent): whether bank eax has patch edx: 1 or 0. */
void SNDbankpatpresent(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    reg32 bank = cpu.eax;
    const reg32 patch = cpu.edx;
    cpu.esp = kept.frame(5);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    reg32 asked = 0;
    if (i32(bank) < 0)
        asked = 1;
    if (!callWith(app, cpu, 0x502570, asked))
        return;
    if (cpu.eax != 0)
    {
        kept.ret(cpu, 0xfffffff8);
        return;
    }
    const reg32 b = at(app, kBanks + bank * 12);
    if (i32(patch) < 0 && !fail(app, cpu, kept.frame(5), kPatPresentFile, kPatPresentName, 0x3b, {0x54dc48, patch}))
        return;
    if (i32(patch) >= i32(half(app, b + 6)))
    {
        kept.ret(cpu, 0);
        return;
    }
    const reg32 version = byte(app, b + 4);
    if (version != 2 && version != 4
        && !fail(app, cpu, kept.frame(5), kPatPresentFile, kPatPresentName, 0x47, {0x54dc78, version}))
        return;
    const reg32 slot = byte(app, b + 4) == 4 ? b + patch * 4 + 0x14 : b + patch * 4 + 0xc;
    kept.ret(cpu, at(app, slot) != 0 ? 1 : 0);
}

/* 0x4e73d0 (SNDmastervol): the master volume to eax (0..127), every playing
 * voice's set again. */
void SNDmastervol(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 volume = cpu.eax;
    cpu.esp = kept.frame(1);
    if (byte(app, kInited) == 0)
    {
        kept.ret(cpu, 0xfffffff6);
        return;
    }
    cpu.esp = kept.frame(3);
    if ((i32(volume) < 0 || i32(volume) > 0x7f)
        && !fail(app, cpu, kept.frame(4), kMasterFile, kMasterName, 0x51, {0x54ab48, volume}))
        return;
    if (!call(app, cpu, 0x500e20))
        return;
    putByte(app, kMasterVolume, reg8(volume));
    for (reg32 i = 0; i < kVoiceCount; ++i)
    {
        const reg32 v = voice(i);
        if (byte(app, v + 0xc) != 1 || s32(app, v) < 0)
            continue;
        if (!callWith(app, cpu, 0x5014a0, i) || !callWith(app, cpu, 0x501540, i, reg32(sbyte(app, v + 0x31))))
            return;
    }
    if (!call(app, cpu, 0x500e7c))
        return;
    kept.ret(cpu, 0);
}

}  // namespace snd
}  // namespace nfs3hp
