#include "native_snd.h"

/* The game's music, native (native_snd.h says how): the CD stream it plays
 * through, the tune for the menus ("show") and for a race (the track's rock or
 * tech version) started on Pathfinder with its map, faded in and out, and the
 * effects' banks loaded and freed.  The port's change to the race music
 * (tools/apply_music_stream.py's, before these were native) is here: the
 * track is played from its own file, not from a copy made at every race.
 *
 * The game's state: 0x6fbb54 set when there is no sound (no music either),
 * 0x552910 the music on, 0x552598 the music's CD stream, 0x570a50 the
 * Pathfinder map, 0x5525a0 the music playing, 0x55258c the menu tune
 * playing, 0x5525fc the menu tune picked, 0x552590 the race's own tune,
 * 0x552914 whether the menus' music plays, 0x552854 tech (1) or rock,
 * 0x5525f8 the race's tune, 0x5525a8 the tunes' names, 0x7a2a34 the audio
 * directory, 0x7a2734 the temp directory, 0x6fbbe4 the track, 0x6fbbe8 the
 * music's volume, 0x6fbbec the menu music asked for. */
namespace nfs3hp
{

// nfs3hp_main.cpp's: the track's index file as the game opens it, and its own
// stream file in place of the copy's.
void musicIndexOpened(win32::WinApplication* app, x86::reg32 path);
void musicStreamFile(win32::WinApplication* app, x86::reg32 path);

namespace snd
{

namespace
{

constexpr reg32 kNoSound = 0x6fbb54, kMusicOn = 0x552910, kMusicStream = 0x552598, kMusicMap = 0x570a50;
constexpr reg32 kMusicPlaying = 0x5525a0, kMenuTune = 0x55258c, kMenuPick = 0x5525fc, kOwnTune = 0x552590;
constexpr reg32 kMenuMusic = 0x552914, kTech = 0x552854, kRaceTune = 0x5525f8, kTuneNames = 0x5525a8;
constexpr reg32 kTrack = 0x6fbbe4, kMusicVolume = 0x6fbbe8, kMenuAsked = 0x6fbbec;
constexpr reg32 kAudioDir = 0x7a2a34, kTempDir = 0x7a2734;
constexpr reg32 kGameMode = 0x55eb2e;       // bytes: 0x10, 0x20 and [+1] 1 play rock always
constexpr reg32 kSprintf = 0x4df690, kRandom = 0x4e0d88, kLoad = 0x4e0ec0, kFree = 0x4e1890;
constexpr reg32 kFormatTwo = 0x536890;      // "%s%s"
constexpr reg32 kBankCopies = 0x57112c;          // 23 of 12 bytes: the bank's header copy; its handle at -8

bool sprintf(App* app, CPU& cpu, std::initializer_list<reg32> arguments)
{
    return call(app, cpu, kSprintf, arguments);
}

/* The string at `from` added to the one at `to`, as the code's repne scasb
 * and its copy loop do it: eax's low byte left 0, ecx past the end (esi and
 * edi are the callers' own, saved). */
void append(App* app, CPU& cpu, reg32 to, reg32 from)
{
    reg32 end = to;
    while (byte(app, end) != 0)
        ++end;
    cpu.ecx = reg32(-2 - i32(end - to));
    for (reg32 i = 0;; ++i)
    {
        const reg8 c = byte(app, from + i);
        putByte(app, end + i, c);
        if (c == 0)
            break;
    }
    cpu.eax &= 0xffffff00;
}

/* The rock or the tech version: rock while the game's mode says (0x10, 0x20,
 * or [+1] 1), else tech when it is to be. */
bool rock(App* app)
{
    return (byte(app, kGameMode) & 0x30) != 0 || (byte(app, kGameMode + 1) & 1) != 0;
}

}  // namespace

/* 0x40feb0: SND ended at the game's exit, with the sound or the music on. */
void soundExit(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(1);
    if ((at(app, 0x55290c) != 0 || at(app, kMusicOn) != 0) && !call(app, cpu, 0x4e26b4))
        return;
    const reg32 eax = cpu.eax, ebx = cpu.ebx, ecx = cpu.ecx, edx = cpu.edx;
    kept.ret(cpu, eax);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
    cpu.edx = edx;
}

/* 0x40fed0: the music's old copy (<temp>temp.mus) made writable and deleted. */
void deleteMusicCopy(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 name = kept.frame(3, 0x80);
    cpu.esp = name;
    cpu.ebp = kept.frame(3);
    if (!sprintf(app, cpu, {name, 0x536880, kTempDir}) || !callWith(app, cpu, 0x4e0e60, name))
        return;
    if (cpu.eax != 0)
    {
        if (!call(app, cpu, at(app, 0x5345ec), {name, 0x20}) || !callWith(app, cpu, 0x4e28a0, name))
            return;
    }
    const reg32 eax = cpu.eax, ebx = cpu.ebx;
    kept.ret(cpu, eax);
    cpu.ebx = ebx;
}

/* 0x40ffd0: the race's tune for the track: by its number, at random (of 5)
 * for the others. */
void raceTuneOf(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    const reg32 t = at(app, kTrack) - 3;
    static const reg32 tunes[] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8};
    if (t <= 9)
    {
        kept.ret(cpu, tunes[t]);
        return;
    }
    cpu.ecx = 5;
    cpu.edx = 0;
    if (!call(app, cpu, kRandom))
        return;
    udiv(cpu, cpu.ecx);
    cpu.eax = cpu.edx;
    leave(cpu, kept, kEcx | kEdx);
}

/* 0x410030: the race's music picked for track eax -- its tune, rock or tech
 * -- before the race.  The game then copied the track to <temp>temp.mus,
 * turning the loading bar; the port plays the track where it lies, so that
 * part is not done (nor the buffer it copied through taken). */
void raceMusicPrepare(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 track = cpu.eax;
    const reg32 f = kept.frame(6, 0x12c);
    cpu.esp = f;
    const reg32 frame = kept.frame(6) - 0x82;   // ebp as the code has it
    cpu.ebp = frame;
    const reg32 name = frame - 0xaa;
    put(app, frame + 0x72, 0);
    put(app, frame + 0x6e, 0);
    put(app, frame + 0x76, 0x80000);
    cpu.ecx = track;
    cpu.edx = 0x80000;
    cpu.ebx = 0;
    cpu.edi = at(app, kNoSound);
    auto done = [&] { kept.ret(cpu, cpu.eax); };
    if (cpu.edi != 0 || i32(track) >= 0xa)
        return done();
    if (!call(app, cpu, 0x4a33d0))
        return;
    if (at(app, 0x55e88c) != 0)
        return done();
    cpu.ebx = 0x10;
    cpu.eax = 0;  // the port: no buffer to copy through
    put(app, frame + 0x7a, 0);
    cpu.edx = at(app, kTrack);
    if (i32(cpu.edx) < 3)
    {
        cpu.ebx = at(app, kTuneNames + 4 * track);
        if (!sprintf(app, cpu, {name, kFormatTwo, kAudioDir, cpu.ebx}))
            return;
        cpu.eax = (cpu.eax & 0xffff00ff) | reg32(byte(app, kGameMode)) << 8;
        const reg32 t = at(app, kTrack);
        const bool tech = !rock(app) && (t == 1 || (t != 0 && at(app, kTech) == 1));
        append(app, cpu, name, tech ? 0x5368a4 : 0x536898);
    }
    else
    {
        if (!call(app, cpu, 0x40ffd0))
            return;
        const reg32 tune = cpu.eax;
        put(app, kRaceTune, tune);
        cpu.edx = at(app, kTuneNames + 4 * tune);
        if (!sprintf(app, cpu, {name, kFormatTwo, kAudioDir, cpu.edx}))
            return;
        cpu.ecx = at(app, kTrack);
        if (cpu.ecx == 0xb)
        {
            cpu.ecx = 0x64;
            cpu.edx = 0;
            if (!call(app, cpu, kRandom))
                return;
            udiv(cpu, cpu.ecx);
            cpu.eax = cpu.edx <= 0x32 ? 1 : 0;
            put(app, kTech, cpu.eax);
        }
        else if (byte(app, kTrack) & 1)
        {
            cpu.ebx = 0;
            put(app, kTech, 0);
        }
        else
            put(app, kTech, 1);
        cpu.ebx = (cpu.ebx & 0xffff00ff) | reg32(byte(app, kGameMode)) << 8;
        const reg32 t = at(app, kTrack);
        const bool tech = !rock(app) && (t == 1 || (t != 0 && at(app, kTech) == 1));
        append(app, cpu, name, tech ? 0x5368a4 : 0x536898);
    }
    done();
}

/* 0x410330: the music's CD stream made (300 KB of ring, 16 KB blocks), when
 * the music is on. */
void musicStreamMake(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (at(app, kNoSound) == 0 && at(app, kMusicOn) != 0)
    {
        if (!callWith(app, cpu, 0x4e4790, 0x4b000, 0x4000, 0))
            return;
        put(app, kMusicStream, cpu.eax);
    }
    kept.ret(cpu, cpu.eax);
}

/* 0x410370: the same, eax KB of ring. */
void musicStreamMakeOf(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (at(app, kNoSound) == 0 && at(app, kMusicOn) != 0)
    {
        if (!callWith(app, cpu, 0x4e4790, cpu.eax << 10, 0x4000, 0))
            return;
        put(app, kMusicStream, cpu.eax);
    }
    kept.ret(cpu, cpu.eax);
}

/* 0x4104f0: tune eax started at volume edx -- a menu's (0x16 the one picked,
 * 0x17 and 0x18 the sixth) or a race's (below 10: rock or tech, from its .lin
 * index when ebx says so, else its .map) -- on Pathfinder, faded in. */
void musicStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0x20c);
    cpu.esp = f;
    cpu.ebp = kept.frame(4) - 0x28a;
    reg32 tune = cpu.eax;
    const reg32 volume = cpu.edx, own = cpu.ebx;
    const reg32 name = f, path = f + 0x100;
    put(app, f + 0x208, tune);
    put(app, f + 0x200, volume);
    put(app, f + 0x204, 0x5dc);
    if (tune == 0x63)
    {
        tune = 0;
        cpu.esi = 0;
        put(app, f + 0x208, 0);
    }
    cpu.eax &= 0xffff00ff;
    cpu.edi = 0x63;
    putByte(app, kOwnTune, 0);
    cpu.eax = at(app, kNoSound);
    put(app, kMenuTune, 0x63);
    auto done = [&] {
        const reg32 eax = cpu.eax, ebx = cpu.ebx, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.ebx = ebx;
        cpu.edx = edx;
    };
    if (cpu.eax != 0 || at(app, kMusicOn) == 0)
        return done();
    cpu.ecx = tune;
    if (i32(tune) > 0x18)
        return done();
    if (own != 0 && i32(tune) < 0xa)
        putByte(app, kOwnTune, 1);
    if (own == 0)
        put(app, kMenuMusic, 1);
    if (at(app, kMenuAsked) == 0)
    {
        cpu.edi = 7;
        cpu.edx = 0;
        if (!call(app, cpu, kRandom))
            return;
        udiv(cpu, cpu.edi);
        cpu.edx += 1;
        putByte(app, kMenuPick, reg8(cpu.edx));
        if (reg8(cpu.edx) == 6)
            putByte(app, kMenuPick, 2);
    }
    else
    {
        cpu.eax = (cpu.eax & 0xffffff00) | byte(app, kMenuAsked);
        putByte(app, kMenuPick, byte(app, kMenuAsked));
    }
    cpu.ecx = (cpu.ecx & 0xffff00ff) | reg32(byte(app, kGameMode)) << 8;
    if (rock(app))
        putByte(app, kMenuPick, 1);
    cpu.edx = tune;
    if (tune == 0x18)
    {
        cpu.ecx = 6;
        if (!sprintf(app, cpu, {name, 0x5368c4, kAudioDir}))
            return;
        put(app, kMenuTune, cpu.ecx);
    }
    else if (tune == 0x16)
    {
        if (!sprintf(app, cpu, {name, 0x5368cc, kAudioDir, byte(app, kMenuPick)}))
            return;
        cpu.eax = byte(app, kMenuPick);
        put(app, kMenuTune, cpu.eax);
    }
    else if (tune == 0x17)
    {
        if (!sprintf(app, cpu, {name, 0x5368c4, kAudioDir}))
            return;
    }
    else
    {
        if (i32(tune) >= 0xa)
            return done();
        const reg32 pick = i32(at(app, kTrack)) >= 3 ? at(app, kRaceTune) : tune;
        if (!sprintf(app, cpu, {name, kFormatTwo, kAudioDir, at(app, kTuneNames + 4 * pick)}))
            return;
        cpu.edx = (cpu.edx & 0xffff00ff) | reg32(byte(app, kGameMode)) << 8;
        append(app, cpu, name, !rock(app) && at(app, kTech) == 1 ? 0x5368e0 : 0x5368d8);
    }
    const reg32 index = own != 0 && i32(tune) < 0xa ? 0x5368e8 : 0x5368f0;
    if (!sprintf(app, cpu, {path, kFormatTwo, name, index}))
        return;
    if (!callWith(app, cpu, kLoad, path, 0x10))
        return;
    put(app, kMusicMap, cpu.eax);
    if (!call(app, cpu, 0x4e6dc8))
        return;
    cpu.ebx = at(app, f + 0x204);
    if (!sprintf(app, cpu, {path, kFormatTwo, name, 0x5368f8}))
        return;
    if (!callWith(app, cpu, 0x4e73d0, 0, path)
        || !callWith(app, cpu, 0x4e6f0c, at(app, kMusicStream))
        || !callWith(app, cpu, 0x4e7470, 1, 0)
        || !callWith(app, cpu, 0x4e73d0, 0x7f, at(app, f + 0x200))
        || !callWith(app, cpu, 0x4e7470, 0x64))
        return;
    put(app, kMusicPlaying, 1);
    done();
}

/* 0x4107c0: a race's music started -- tune eax (the race's when ebx says
 * so), rock or tech, at volume edx less the car's own share for the tech --
 * from the track's own file, by the port's change. */
void raceMusicStart(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 f = kept.frame(4, 0x108);
    cpu.esp = f;
    cpu.ebp = kept.frame(4) - 0x186;
    reg32 tune = cpu.eax;
    const reg32 own = cpu.ebx, volume = cpu.edx;
    const reg32 name = f;
    put(app, f + 0x104, volume);
    put(app, f + 0x100, 0x5dc);
    if (tune == 0x63)
        tune = 0;
    cpu.eax = tune;
    cpu.edx &= 0xffffff00;
    cpu.ecx = at(app, kNoSound);
    putByte(app, kOwnTune, 0);
    auto done = [&] {
        const reg32 eax = cpu.eax, ebx = cpu.ebx, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.ebx = ebx;
        cpu.edx = edx;
    };
    if (cpu.ecx != 0 || at(app, kMusicOn) == 0 || i32(tune) >= 0xa)
        return done();
    reg32 pick;
    if (own != 0)
    {
        cpu.edx = (cpu.edx & 0xffff00ff) | 0x100;
        put(app, kMenuMusic, cpu.ecx);
        putByte(app, kOwnTune, 1);
        cpu.eax = at(app, kRaceTune);
        pick = cpu.eax;
        cpu.ecx = at(app, kTuneNames + 4 * pick);
    }
    else
    {
        put(app, kMenuMusic, 1);
        pick = tune;
        cpu.esi = at(app, kTuneNames + 4 * pick);
    }
    if (!sprintf(app, cpu, {name, kFormatTwo, kAudioDir, at(app, kTuneNames + 4 * pick)}))
        return;
    cpu.ecx = (cpu.ecx & 0xffffff00) | byte(app, kGameMode);
    const reg32 t = at(app, kTrack);
    const bool tech = !rock(app) && (t == 1 || (t != 0 && at(app, kTech) == 1));
    if (!rock(app))
        cpu.edi = t;
    append(app, cpu, name, tech ? 0x5368e0 : 0x5368d8);
    append(app, cpu, name, own != 0 ? 0x5368e8 : 0x5368f0);
    cpu.edx = 0x10;
    cpu.eax = name;
    musicIndexOpened(app, cpu.eax);
    if (!call(app, cpu, kLoad))
        return;
    put(app, kMusicMap, cpu.eax);
    if (!call(app, cpu, 0x4e6dc8))
        return;
    cpu.esi = 0x5368f8;
    cpu.edi = name;
    if (!sprintf(app, cpu, {name, 0x536900, kTempDir}))
        return;
    cpu.ebx = at(app, f + 0x100);
    cpu.edx = name;
    append(app, cpu, name, 0x5368f8);
    cpu.eax = at(app, kMusicStream);
    musicStreamFile(app, cpu.edx);
    if (!call(app, cpu, 0x4e6f0c) || !callWith(app, cpu, 0x4e7470, 1, 0))
        return;
    reg32 level = at(app, f + 0x104);
    if (at(app, kTrack) == 1 || at(app, kTech) == 1)
    {
        cpu.edx = at(app, 0x6fd4ac);
        cpu.esi = at(app, 0x5525d0 + 4 * cpu.edx);
        level = at(app, f + 0x104) - cpu.esi;
        if (i32(level) < 0)
            level = 0;
    }
    if (!callWith(app, cpu, 0x4e7470, 0x64, level))
        return;
    put(app, kMusicPlaying, 1);
    done();
}

/* 0x4103a0: the music after a change of setting eax (edx: the menus' tune
 * back): the menu's tune, or the race's for a track (3..12, rock or tech by
 * eax's evenness) -- restarted. */
void musicAfterSetting(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(4);
    const reg32 setting = cpu.eax;
    cpu.ecx = setting;
    auto menu = [&] {
        if (!call(app, cpu, 0x4109d0) || !callWith(app, cpu, 0x4104f0, 0x16, at(app, kMusicVolume), 0))
            return false;
        putByte(app, 0x552591, 1);
        return true;
    };
    auto done = [&] {
        const reg32 eax = cpu.eax, edx = cpu.edx;
        kept.ret(cpu, eax);
        cpu.edx = edx;
    };
    if (cpu.edx != 0)
    {
        if (!menu())
            return;
        return done();
    }
    cpu.edx = at(app, kTrack);
    if (i32(cpu.edx) < 3 || i32(cpu.edx) > 0xc)
    {
        if (byte(app, 0x552591) == 0)
        {
            if (!menu())
                return;
        }
        else
            putByte(app, 0x552591, 1);
        return done();
    }
    put(app, kTech, (i32(setting) % 2) != 0 ? 0 : 1);
    if (!call(app, cpu, 0x40ffd0))
        return;
    cpu.ebx = 1;
    put(app, kRaceTune, cpu.eax);
    if (!call(app, cpu, 0x4109d0) || !callWith(app, cpu, 0x4104f0, 0, at(app, 0x6fbbf0)))
        return;
    cpu.ebx &= 0xffffff00;
    putByte(app, 0x552591, 0);
    done();
}

/* 0x410460: the menus' tune 0x18 while there is no other asked for (6). */
void musicMenuSix(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(4);
    cpu.ebp = cpu.esp;
    cpu.edx = 1;
    cpu.ecx = at(app, kMenuAsked);
    put(app, 0x552594, cpu.edx);
    if (cpu.ecx != 6 && at(app, kMenuTune) != 6)
    {
        if (!call(app, cpu, 0x4109d0))
            return;
        cpu.eax = 0x18;
        cpu.edx = at(app, kMusicVolume);
        cpu.ebx = 0;
        if (!call(app, cpu, 0x4104f0))
            return;
    }
    leave(cpu, kept, kEbx | kEcx | kEdx);
}

/* 0x4109d0: the music stopped: faded out and waited for, the stream purged,
 * Pathfinder ended and its map freed. */
void musicStop(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(4);
    cpu.edx = at(app, kNoSound);
    if (cpu.edx == 0 && at(app, kMusicPlaying) != 0 && at(app, kMusicOn) != 0)
    {
        if (!callWith(app, cpu, 0x4e7470, 0x64))
            return;
        for (;;)
        {
            safepoint(app, cpu);
            if (!call(app, cpu, 0x4e74f0))
                return;
            if (i32(cpu.eax) <= 0)
                break;
            if (!callWith(app, cpu, 0x4e7630, 0))
                return;
        }
        cpu.esi = 0;
        if (!call(app, cpu, 0x4e7b28))
            return;
        put(app, kMusicPlaying, 0);
        if (!call(app, cpu, 0x4e7388))
            return;
        cpu.edi = at(app, kMusicMap);
        if (cpu.edi != 0)
        {
            if (!callWith(app, cpu, kFree, cpu.edi))
                return;
            put(app, kMusicMap, 0);
        }
    }
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx;
    kept.ret(cpu, cpu.eax);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
}

/* 0x410aa0: the music's stream ended: the streamer's restore, the stream
 * deleted. */
void musicStreamEnd(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(2);
    cpu.edx = at(app, kNoSound);
    if (cpu.edx == 0 && at(app, kMusicOn) != 0)
    {
        if (!call(app, cpu, 0x4e784c) || !callWith(app, cpu, 0x4e4b50, at(app, kMusicStream)))
            return;
        put(app, kMusicStream, cpu.edx);
    }
    const reg32 ebx = cpu.ebx, ecx = cpu.ecx;
    kept.ret(cpu, cpu.eax);
    cpu.ebx = ebx;
    cpu.ecx = ecx;
}

/* 0x410ad0: the 23 banks' header copies freed. */
void banksFree(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.ebp = cpu.esp = kept.frame(5);
    for (cpu.edx = 0; i32(cpu.edx) < 0x17; ++cpu.edx)
    {
        cpu.eax = cpu.edx * 3;
        cpu.ecx = cpu.eax * 4;
        cpu.ebx = at(app, cpu.ecx + kBankCopies);
        if (cpu.ebx == 0)
            continue;
        cpu.eax = cpu.ebx;
        cpu.esi = 0;
        if (!call(app, cpu, kFree))
            return;
        put(app, cpu.ecx + kBankCopies, cpu.esi);
    }
    leave(cpu, kept, kEbx | kEcx | kEdx | kEsi);
}

/* 0x410b20: every bank removed from SND, the first's copy freed. */
void banksRemove(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    cpu.esp = kept.frame(3);
    if (!callWith(app, cpu, 0x4e8c1c, 0xffffffff))
        return;
    const reg32 bank = at(app, kBankCopies);
    if (bank != 0)
    {
        cpu.ecx = 0;
        if (!callWith(app, cpu, kFree, bank))
            return;
        put(app, kBankCopies, 0);
    }
    const reg32 ebx = cpu.ebx;
    kept.ret(cpu, cpu.eax);
    cpu.ebx = ebx;
}

/* 0x410b50: bank file eax (".bnk" added) loaded into slot edx and added to
 * SND: kept whole, or (SND asks for it, 7) its header copied out and the file
 * freed. */
void bankLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const reg32 file = cpu.eax;
    const reg32 frame = kept.frame(4);
    const reg32 buffer = frame - 0x108;
    cpu.esp = buffer;
    cpu.ebp = frame;
    put(app, frame - 4, cpu.edx);
    if (at(app, 0x55290c) == 0)
    {
        const reg32 ebx = cpu.ebx, edx = cpu.edx;
        kept.ret(cpu, cpu.eax);
        cpu.ebx = ebx;
        cpu.edx = edx;
        return;
    }
    for (reg32 i = 0;; ++i)
    {
        const reg8 c = byte(app, file + i);
        putByte(app, buffer + i, c);
        if (c == 0)
            break;
    }
    cpu.edx = kept.ebx;
    append(app, cpu, buffer, 0x536908);
    if (!callWith(app, cpu, kLoad, buffer))
        return;
    const reg32 data = cpu.eax;
    cpu.ecx = data;
    cpu.edi = data;
    if (!callWith(app, cpu, 0x4e8d20, frame - 8, data))
        return;
    reg32 kept_ = data;
    if (cpu.eax == 7)
    {
        if (!callWith(app, cpu, 0x4e8db0, at(app, frame - 8)))
            return;
        if (!callWith(app, cpu, 0x4e1620, 0x53688c, cpu.eax))
            return;
        const reg32 copy = cpu.eax;
        cpu.ebx = copy;
        if (!callWith(app, cpu, 0x4e8e20, copy, at(app, frame - 8)))
            return;
        if (!callWith(app, cpu, kFree, data))
            return;
        kept_ = copy;
        cpu.edi = copy;
    }
    const reg32 slot = at(app, frame - 4) * 12;
    cpu.ebx = slot;
    put(app, kBankCopies + slot, kept_);
    cpu.eax = at(app, frame - 8);
    put(app, kBankCopies - 8 + slot, cpu.eax);
    const reg32 ebx = cpu.ebx, edx = cpu.edx;
    kept.ret(cpu, cpu.eax);
    cpu.ebx = ebx;
    cpu.edx = edx;
}

}  // namespace snd
}  // namespace nfs3hp
