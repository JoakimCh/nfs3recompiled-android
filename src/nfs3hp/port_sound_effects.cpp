#include "port.h"

#include <cstdint>
#include <utility>

/* The game's sound effects, rewritten (port.h says how) -- what
 * its first, register-level native did: an effect of a bank played at
 * the effects' (or engine's, or speech's) volume, panned or placed as the
 * sound mode says; the race's sounds kept in slots; the master and the
 * music's volume; the effect bus; SND's angle of a vector.
 *
 * Each function's integer arithmetic is the game's to the bit (its
 * multiplications by 55 and 63, its shifts by 14, its divisions toward 0),
 * and it calls EA's SND library, which is not rewritten yet, with what the
 * game's code hands it -- from where on the stack the game's code has it,
 * for the records it points at. */
namespace nfs3hp
{
namespace port
{

namespace
{

// SND's options of a sound to play (SNDplaysetdef fills them, SNDplay takes
// them).
#pragma pack(push, 1)
struct PlayOptions
{
    int32_t effect;      // the sample in the bank
    uint8_t bank;        // the bank's handle (its low byte)
    uint8_t other5[2];
    uint8_t pan;         // stereo: 0..127, 0x40 the middle
    uint8_t volume;      // 0..127
    uint8_t pitch;       // 0x40 as recorded
    uint8_t otherA;
    uint8_t placed;      // 1: by its angle (3D or surround)
    uint16_t angle;      // 0..0xffff
    uint8_t otherE[2];
};
#pragma pack(pop)
static_assert(sizeof(PlayOptions) == 0x10, "SND's play options");

// One of the race's sound slots: the sound playing (-1 none) and its effect.
struct Slot
{
    int32_t sound;
    int32_t effect;
};

// A bank of the game's: its SND handle first.
struct Bank
{
    int32_t handle;
    int32_t other[2];
};

// The game's sound settings and state.
constexpr Var<int32_t> kEffectsOn{0x55290c}, kMenuSoundsOff{0x559234};
constexpr Var<int32_t> kEffectsVolume{0x6fbbf4}, kEngineVolume{0x6fbbf8}, kSpeechVolume{0x6fbbfc};
constexpr Var<int32_t> kSoundMode{0x6fbc00}, kSurround{0x5525a4}, kStereo{0x55292c}, kPlaying{0x552928};
constexpr Var<int32_t> kMusicVolume{0x6fbbf0}, kTechVersion{0x6fbbe4}, kTechVersion2{0x552854};
constexpr Var<int32_t> kPlayerCar{0x6fd4ac}, kGameMode{0x6fd3b8}, kCopRadioOn{0x6fd49c}, kSplitScreen{0x6fd3b0};
constexpr Var<uint8_t> kMusicUnmuted{0x552908}, kBusUsed{0x552930};
constexpr Table<int32_t> kCarMusicShare{0x5525d0};
constexpr Table<Bank> kBanks{0x571124};
constexpr Table<Slot> kSlots{0x570de8};
constexpr Table<uint8_t> kSlotBanks{0x552798, 4};

// The banks the code names by their place.
enum BankIndex : int32_t
{
    kMenuBank = 0,       // 0x571124
    kSceneryBank = 1,    // 0x571130
    kCarBank = 2,        // 0x57113c
    kCrashBank = 3,      // 0x571148
    kBank4 = 4,          // 0x571154
    kBank5 = 5,          // 0x571160
    kSpeechBank6 = 6,    // 0x57116c
    kSpeechBank7 = 7,    // 0x571178
    kBank9 = 9,          // 0x571190
    kSpeechBank10 = 10,  // 0x57119c
};

// EA's SND library, the game's own music and race sound, and the random.
constexpr reg32 kPlaySetDefault = 0x4e9b20, kPlay = 0x4e9ba0, kStop = 0x4e9670, kStopAll = 0x4e9010;
constexpr reg32 kMasterLevel = 0x4e73d0, kMusicLevel = 0x4e8b60, kFade = 0x4e9420, kVolume = 0x4e95fc;
constexpr reg32 kPitch = 0x4e97e4, kPlace = 0x4e9850, kPan = 0x4e9950, kBusInit = 0x4e9c70, kBusLevel = 0x4e9dfc;
constexpr reg32 kRandom = 0x4e0d88, kMusicStop = 0x4109d0, kRaceSoundInit = 0x4129c0;
constexpr reg32 kPlayEffect = 0x4182b0, kSlotStop = 0x416f60, kSlotPlay = 0x417080, kBusDown = 0x418790;

int32_t bankHandle(App* app, int32_t i) { return kBanks(app, i).handle; }

/* A level of 0..127 scaled by a setting as the game's code does it: the
 * setting times `factor`, times the level, over 2^14. */
int32_t scaled(int32_t setting, int32_t factor, int32_t level)
{
    const int32_t s = int32_t(uint32_t(setting) * uint32_t(factor));
    return int32_t(uint32_t(s) * uint32_t(level)) >> 14;
}

/* A pan (0..0xffff around) as stereo's (0..127), as the game's code makes it. */
uint8_t stereoPan(uint32_t pan)
{
    const uint32_t a = int32_t(pan) > 0x3fff && int32_t(pan) < 0xc000 ? 0xbfff - pan : (pan + 0x4000) & 0xffff;
    return uint8_t(int32_t(a) >> 8);
}

/* The options' place by the sound mode: 3D or surround by the angle (in
 * surround only with stereo on, else straight ahead), plain stereo by the
 * pan (the middle with stereo off). */
void place(App* app, PlayOptions& o, uint32_t pan)
{
    if (kSoundMode(app) == 2)
    {
        o.placed = 1;
        o.angle = uint16_t(pan);
    }
    else if (kSurround(app) != 0)
    {
        o.placed = 1;
        o.angle = kStereo(app) != 0 ? uint16_t(pan) : 0;
    }
    else
    {
        o.placed = 0;
        o.pan = kStereo(app) != 0 ? stereoPan(pan) : 0x40;
    }
}

/* The music's volume, less the car's own share for the tech version. */
int32_t musicVolume(App* app)
{
    if (kTechVersion(app) == 1 || kTechVersion2(app) == 1)
    {
        const int32_t v = kMusicVolume(app) - kCarMusicShare(app, kPlayerCar(app));
        return v < 0 ? 0 : v;
    }
    return kMusicVolume(app);
}

/* Whether bank `bank` is a speech bank for effect `effect` now. */
bool isSpeech(App* app, int32_t bank, int32_t effect)
{
    const auto is = [&](int32_t i) { return bank == bankHandle(app, i); };
    if (is(kSpeechBank7) || is(kSpeechBank6) || is(kSpeechBank10))
        return true;
    if (is(kBank5) && kGameMode(app) == 3 && effect >= 0x20 && effect < 0x29)
        return true;
    if (kGameMode(app) == 3)
        for (const int32_t i : {11, 14, 12, 13, 8, 15, 16, 17, 18, 19, 20, 21})
            if (is(i))
                return true;
    return is(kBank9) && kCopRadioOn(app) != 0;
}

/* SNDplay of `o`, filled from SND's defaults by `fill`, on the game's stack
 * at `at` (esp there): its handle, the effects playing one more. */
template <class Fill>
bool play(App* app, CPU& cpu, reg32 at, Fill fill, reg32& handle)
{
    if (!callGame(app, cpu, at, kPlaySetDefault, {at}))
        return false;
    PlayOptions o = load<PlayOptions>(app, at);
    fill(o);
    store(app, at, o);
    if (!callGame(app, cpu, at, kPlay, {at}, {}, handle))
        return false;
    kPlaying.set(app, kPlaying(app) + 1);
    return true;
}

}  // namespace

/* The effects -- each its adapter (the game's registers and stack in, the
 * result in eax out) around what it does. */

/* 0x4181d0: menu effect eax of the first bank at volume edx.  SNDplay's
 * handle (the effect itself, as the code leaves eax, with sounds off). */
void playMenuEffect(App* app, CPU& cpu)
{
    const Entry e(cpu);
    const int32_t effect = int32_t(e.eax), volume = int32_t(e.edx);
    reg32 handle = e.eax;
    if (kMenuSoundsOff(app) == 0 && kEffectsOn(app) != 0)
    {
        const auto fill = [&](PlayOptions& o) {
            o.bank = uint8_t(bankHandle(app, kMenuBank));
            o.volume = uint8_t(scaled(kEffectsVolume(app), 55, volume));
            o.effect = effect;
            o.pitch = 0x40;
            if (kSoundMode(app) == 2 || kSurround(app) != 0)
            {
                o.placed = 1;
                o.angle = 0;
            }
            else
            {
                o.placed = 0;
                o.pan = 0x40;
            }
        };
        if (!play(app, cpu, e.frame(4) - 0x10, fill, handle))
            return;
    }
    e.back(cpu, handle);
}

namespace
{

/* 0x4182b0's: effect `effect` of bank `bank` at `volume`, pan `pan`, pitch
 * `pitch` -- the volume scaled by its kind's (the engine's for bank 0's effect
 * 2, the speech's for the speech's banks, the effects' else).  -1 with the
 * effects off. */
bool playEffectOf(App* app, CPU& cpu, reg32 at, int32_t bank, int32_t effect, int32_t volume, uint32_t pan,
                  uint8_t pitch, reg32& handle)
{
    if (kEffectsOn(app) == 0)
    {
        handle = 0xffffffff;
        return true;
    }
    int32_t level;
    if (bank == 0 && effect == 2)
        level = int32_t(uint32_t(volume) * uint32_t(kEngineVolume(app))) / 0x7f;
    else if (isSpeech(app, bank, effect))
        level = scaled(kSpeechVolume(app), 0x7f, volume);
    else if ((bank == bankHandle(app, kBank4) && (effect == 6 || effect == 7))
             || (bank == bankHandle(app, kCarBank) && effect == 0xf))
        level = int32_t(uint32_t(volume) * uint32_t(kEffectsVolume(app))) / 0x7f;
    else
        level = scaled(kEffectsVolume(app), 55, volume);
    const auto fill = [&](PlayOptions& o) {
        o.bank = uint8_t(bank);
        o.effect = effect;
        o.volume = uint8_t(level);
        o.pitch = pitch;
        place(app, o, pan);
    };
    return play(app, cpu, at, fill, handle);
}

}  // namespace

/* 0x4182b0 (stdcall 4): effect edx of bank eax at volume ecx, pan ebx, pitch
 * the stack's word. */
void playEffect(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 handle;
    if (!playEffectOf(app, cpu, e.frame(3) - 0x14, int32_t(e.eax), int32_t(e.edx), int32_t(e.ecx), e.ebx,
                      uint8_t(e.arg(app, 0)), handle))
        return;
    e.back(cpu, handle, 4);
}

/* 0x418280: effect 5 of the car's bank at full volume, in the middle. */
void playCarEffectFive(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 handle;
    if (!callGame(app, cpu, e.frame(4), kPlayEffect, {reg32(bankHandle(app, kCarBank)), 5, 0, 0x7f}, {0x40}, handle))
        return;
    e.back(cpu, handle);
}

/* 0x4184f0 (stdcall 4): effect edx of bank eax at volume ecx scaled by the
 * speech's, pan ebx, pitch the stack's word.  -1 with the effects off. */
void playSpeechEffect(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 handle = 0xffffffff;
    if (kEffectsOn(app) != 0)
    {
        const auto fill = [&](PlayOptions& o) {
            o.bank = uint8_t(e.eax);
            o.effect = int32_t(e.edx);
            o.volume = uint8_t(scaled(kSpeechVolume(app), 0x7f, int32_t(e.ecx)));
            o.pitch = uint8_t(e.arg(app, 0));
            place(app, o, e.ebx);
        };
        if (!play(app, cpu, e.frame(2) - 0x14, fill, handle))
            return;
    }
    e.back(cpu, handle, 4);
}

/* 0x4185e0: a side's angle eax (0..127; edx above 0 for the right) as a pan
 * (0..0xffff). */
void panFromSide(App*, CPU& cpu)
{
    const Entry e(cpu);
    int32_t angle = int32_t(e.eax);
    if (int32_t(e.edx) <= 0)
        angle = 0x7f - angle + 0x80;
    int32_t pan = int32_t(uint32_t(angle) << 8) - 0x3ffe;
    if (pan < 0)
        pan += 0x10000;
    e.back(cpu, reg32(pan));
}

/* 0x418610: the master volume to nothing. */
void masterSilent(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!callGame(app, cpu, e.frame(1), kMasterLevel, {0}, {}, r))
        return;
    e.back(cpu, r);
}

/* 0x418620: the master volume back (0x78), the music's too when it is not
 * muted. */
void masterBack(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!callGame(app, cpu, e.frame(2), kMasterLevel, {0x78}, {}, r))
        return;
    if (kMusicUnmuted(app) != 0 && !callGame(app, cpu, e.frame(2), kMusicLevel, {reg32(musicVolume(app))}, {}, r))
        return;
    e.back(cpu, r);
}

namespace
{

/* Silence -- the music and every sound stopped -- then the master volume
 * brought up a step at a time below `to`, the bus down when it is used. */
bool silenceAndRaise(App* app, CPU& cpu, reg32 esp, int32_t to, reg32& r)
{
    if (!callGame(app, cpu, esp, kMasterLevel, {0}, {}, r) || !callGame(app, cpu, esp, kMusicStop, {}, {}, r)
        || !callGame(app, cpu, esp, kStopAll, {}, {}, r))
        return false;
    for (int32_t level = 0; level < to; ++level)
        if (!callGame(app, cpu, esp, kMasterLevel, {reg32(level)}, {}, r))
            return false;
    return kBusUsed(app) == 0 || callGame(app, cpu, esp, kBusDown, {}, {}, r);
}

}  // namespace

/* 0x4186a0: silence, then the master volume back up to 127. */
void silenceForMenus(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!silenceAndRaise(app, cpu, e.frame(2), 0x80, r))
        return;
    e.back(cpu, r);
}

/* 0x4186f0: silence, then the master volume back up to 0x77, and the race's
 * sounds reset. */
void silenceForRace(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!silenceAndRaise(app, cpu, e.frame(2), 0x78, r) || !callGame(app, cpu, e.frame(2), kRaceSoundInit, {}, {}, r))
        return;
    e.back(cpu, r);
}

/* 0x418740: the effect bus set to type 0x14, its level 0. */
void busInit(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!callGame(app, cpu, e.frame(4), kBusInit, {0, 0x7f, 0x14, 0xffffffff}, {0xffffffff})
        || !callGame(app, cpu, e.frame(4), kBusLevel, {0, 0}, {}, r))
        return;
    e.back(cpu, r);
}

/* 0x418770, 0x418790: the bus's level up (127) and down (0). */
void busUp(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!callGame(app, cpu, e.frame(2), kBusLevel, {0, 0x7f}, {}, r))
        return;
    e.back(cpu, r);
}

void busDown(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    if (!callGame(app, cpu, e.frame(2), kBusLevel, {0, 0}, {}, r))
        return;
    e.back(cpu, r);
}

/* 0x4187a0: the race's slots stopped: 4..11 and 14..36. */
void slotsStop(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r = e.eax;
    for (int32_t slot = 4; slot <= 0xb; ++slot)
        if (!callGame(app, cpu, e.frame(2), kSlotStop, {reg32(slot)}, {}, r))
            return;
    for (int32_t slot = 0xe; slot < 0x25; ++slot)
        if (!callGame(app, cpu, e.frame(2), kSlotStop, {reg32(slot)}, {}, r))
            return;
    e.back(cpu, r);
}

/* 0x4187e0: the music muted, or back at its volume. */
void musicMuteToggle(App* app, CPU& cpu)
{
    const Entry e(cpu);
    reg32 r;
    const bool unmuted = kMusicUnmuted(app) != 0;
    if (!callGame(app, cpu, e.frame(2), kMusicLevel, {unmuted ? 0 : reg32(musicVolume(app)), 0}, {}, r))
        return;
    // Muted, the code writes dl as the call leaves it (0 it set before).
    kMusicUnmuted.set(app, unmuted ? uint8_t(cpu.edx) : 1);
    e.back(cpu, r);
}

/* 0x416f60: slot eax's sound faded out (5 ticks) and the slot empty; the
 * effects playing, one less (that count back; else the slot as given). */
void slotStop(App* app, CPU& cpu)
{
    const Entry e(cpu);
    const int32_t slot = int32_t(e.eax);
    if (kEffectsOn(app) == 0 || slot == -1 || kSlots(app, slot).sound == -1)
        return e.back(cpu, e.eax);
    if (!callGame(app, cpu, e.frame(5), kFade, {reg32(kSlots(app, slot).sound), 5, 0xffffffff}))
        return;
    kSlots.set(app, slot, {-1, -1});
    const int32_t playing = kPlaying(app) - 1;
    kPlaying.set(app, playing);
    e.back(cpu, reg32(playing));
}

/* 0x416fc0 (stdcall 12): slot eax plays effect edx, pitch ecx times ebx
 * (16.16, toward 0), volume, pan and player the stack's words -- in the split
 * screen the player's side instead of the pan (the second player's slots 14
 * on) -- the horn (4) of the first car left out half the time by the random
 * (its quotient by 100 back then). */
void slotEffect(App* app, CPU& cpu)
{
    const Entry e(cpu);
    int32_t slot = int32_t(e.eax);
    const int32_t effect = int32_t(e.edx);
    const reg32 volume = e.arg(app, 0), player = e.arg(app, 2);
    reg32 pan = e.arg(app, 1);
    if (kSplitScreen(app) == 1)
    {
        pan = player != 0 ? 0xc000 : 0x3fff;
        if (player != 0)
            slot += 0xe;
    }
    const int32_t product = int32_t(uint32_t(e.ecx) * uint32_t(e.ebx));
    const int32_t pitch = int32_t(uint32_t(product) + (product < 0 ? 0xffffu : 0u)) >> 16;
    const reg32 esp = e.frame(3) - 4;
    if (kPlayerCar(app) == 0 && effect == 4)
    {
        app->getMemory<reg32>(esp) = 0x64;
        if (!callGame(app, cpu, esp, kRandom, {0, 0}))
            return;
        const uint64_t n = (uint64_t(cpu.edx) << 32) | cpu.eax;
        if (n % 0x64 > 0x32)
            return e.back(cpu, reg32(n / 0x64), 0xc);
    }
    reg32 r;
    if (!callGame(app, cpu, esp, kSlotPlay, {reg32(slot), reg32(effect), reg32(pitch), volume}, {pan}, r))
        return;
    e.back(cpu, r, 0xc);
}

/* 0x417080 (stdcall 4): slot eax plays effect edx at volume ecx, pitch ebx
 * (each kept to 0..127), pan the stack's word: started -- from the crashes'
 * bank for the crash slots, by the effect for some, else from the slot's own
 * bank -- the slot's old sound stopped; or, the slot playing that effect
 * already, its volume, pitch and place changed.  The last SND call's eax. */
void slotPlay(App* app, CPU& cpu)
{
    const Entry e(cpu);
    const int32_t slot = int32_t(e.eax);
    int32_t effect = int32_t(e.edx);
    const auto clamp = [](int32_t v) { return v < 0 ? 0 : v > 0x7f ? 0x7f : v; };
    const int32_t pitch = clamp(int32_t(e.ebx)), volume = clamp(int32_t(e.ecx));
    const reg32 pan = e.arg(app, 0);
    const reg32 esp = e.frame(3) - 8;
    int32_t bank;
    bool crash = false;
    for (const int32_t s : {0x12, 0x13, 0x1a, 0x20, 0x21, 0x24, 0x14, 0x15, 0x22, 0x23})
        crash = crash || slot == s;
    if (crash)
        bank = bankHandle(app, kCrashBank);
    else if (effect == 0)
        bank = bankHandle(app, kSceneryBank);
    else if (effect == 2)
        bank = bankHandle(app, kMenuBank);
    else if (effect == 0xa || effect == 0xb)
        bank = bankHandle(app, kCarBank);
    else if (effect == 0xc)
    {
        bank = bankHandle(app, kBank5);
        effect = 1;
    }
    else
        bank = bankHandle(app, kSlotBanks(app, slot));
    reg32 r;
    const auto start = [&](int32_t level, uint8_t pitchOf) {
        return callGame(app, cpu, esp, kPlayEffect, {reg32(bank), reg32(effect), pan, reg32(level)}, {pitchOf}, r);
    };
    if (slot == 0x1f || slot == 0x13 || slot == 0x21)
    {
        if (!start(volume, 0x40))
            return;
        kSlots.set(app, slot, {int32_t(r), effect});
        kPlaying.set(app, kPlaying(app) - 1);
        return e.back(cpu, r, 4);
    }
    const bool engine = slot >= 8 && slot <= 0xb;
    const Slot old = kSlots(app, slot);
    if (effect != old.effect)
    {
        if (old.sound != -1 && slot > 3)
        {
            if (!callGame(app, cpu, esp, kStop, {reg32(old.sound)}))
                return;
            kPlaying.set(app, kPlaying(app) - 1);
        }
        if (!start(engine ? 0 : volume, uint8_t(pitch)))
            return;
        kSlots.set(app, slot, {int32_t(r), effect});
        return e.back(cpu, r, 4);
    }
    int32_t level;
    if (engine)
        level = scaled(kEngineVolume(app), 63, volume);
    else if (slot == 0x10 || slot == 0x11)
        level = scaled(kEffectsVolume(app), 80, volume);
    else
        level = scaled(kEffectsVolume(app), 55, volume);
    const reg32 sound = reg32(old.sound);
    if (!callGame(app, cpu, esp, kVolume, {sound, reg32(level)}) || !callGame(app, cpu, esp, kPitch, {sound, reg32(pitch)}, {}, r))
        return;
    if (kSoundMode(app) == 2 && !callGame(app, cpu, esp, kPlace, {sound, pan, 0}, {}, r))
        return;
    if (kSurround(app) != 0)
    {
        if (!callGame(app, cpu, esp, kPlace, {sound, kStereo(app) != 0 ? pan : 0, 0}, {}, r))
            return;
        return e.back(cpu, r, 4);
    }
    if (!callGame(app, cpu, esp, kPan, {sound, kStereo(app) != 0 ? reg32(stereoPan(pan)) : 0x40}, {}, r))
        return;
    e.back(cpu, r, 4);
}

/* 0x4e8f28: the angle of the vector (eax, edx), 0x400 a turn: the smaller
 * over the larger looked up in the arctangents at 0x5678b8, then put in its
 * octant. */
void SNDangle(App* app, CPU& cpu)
{
    const Entry e(cpu);
    int32_t across = int32_t(e.edx), along = int32_t(e.eax);
    reg32 octant = 0;
    if (across < 0)
    {
        octant |= 8;
        across = int32_t(0u - uint32_t(across));
    }
    if (along < 0)
    {
        octant |= 0x10;
        along = int32_t(0u - uint32_t(along));
    }
    reg32 a;
    if (along == across)
        a = 0x80;
    else
    {
        if (along > across)
        {
            std::swap(along, across);
            octant |= 4;
        }
        const reg32 q = reg32((uint64_t(uint32_t(along)) << 32) / uint32_t(across));
        a = app->getMemory<uint8_t>(((q >> 24) + ((q >> 23) & 1)) + 0x5678b8);
    }
    switch (octant)
    {
    case 4: a = 0x100 - a; break;
    case 8: a = 0x200 - a; break;
    case 0xc: a += 0x100; break;
    case 0x10: a = 0u - a; break;
    case 0x14: a -= 0x100; break;
    case 0x18: a -= 0x200; break;
    case 0x1c: a = 0u - a - 0x100; break;
    default: break;
    }
    e.back(cpu, a);
}

}  // namespace port
}  // namespace nfs3hp
