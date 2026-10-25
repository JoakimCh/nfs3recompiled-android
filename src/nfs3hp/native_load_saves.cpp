#include "native_guest.h"

/* The files the game saves and loads, and EA's formats under its loaders.
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (LOAD_SAVES_NATIVES), and the generated code calls it by name.
 * tools/game_checks holds each against its generated code.
 *
 * Replays: the race just run is replay.rp3, 0x296f8 bytes -- config.dat's
 * 0x20f0 (the race's settings) copied to its head at 0x7a3e50, its version
 * (2) at 0x7a56b0, whether the frames' log follows (0x7a5f40, the race's
 * [0x55d000] being 1) and the seed at 0x7a5f44, checksummed (0x478010,
 * 0x4781b0) and written whole, the log appended through stdio (0x477ac0).
 * Loading reads it back the same way (0x477b00 the log) and checks it
 * (0x478090, 0x478100).  A replay kept is a copy of it under a name of the
 * player's in the replays' folder ([0x7a2f34], "<name>.rp3"; a ghost,
 * ghost.gst, likewise ".gst"); one picked from the list is copied back over
 * replay.rp3 and loaded.  The list (a menu's record: +0x48 how many, at most
 * 200, +0x4c the one chosen, +0x70 its block -- 8 bytes an entry, the name's
 * address and a byte, then the names) is the folder's "*.rp3", the last race
 * first.  The replays' screen shows a replay's track, laps, kind of race and
 * car (the replay's +0x196c, +0x1974, +0x1878, its player's +0x19b4 car at
 * +0x1a00 + 0x6c each) in four lines of 0x78 at 0x558d0c.
 *
 * records.dat: the records' table, 0x4197c bytes ([0x559408]; its first word
 * 0x10, the version), loaded or made empty, and saved back.
 *
 * config.dat (in [0x7a3034]): the game's settings, 0x20f0 bytes at 0x6fbb40
 * (its first word its length), loaded at the start -- made afresh with the
 * defaults when it is missing, of another length, older than nfs3.exe, or
 * another version ([0x6fbc10] against [0x7a3a58]) -- and saved as the menus
 * leave it, unless the game runs from a demo's command line ([0x55eb2e] 0x20)
 * or a replay is shown.  The language, [0x6fbb4c], is read from its name
 * at 0x7a2634.
 *
 * EA's library under them: cmn\locatbig.c's BIG archives, of two kinds --
 * 0xc0fb (a 16-bit header's length at 2, each entry a 24-bit offset and size
 * and its name) and "BIGF" (the header's length at 0xc, each entry a 32-bit
 * offset and size and its name from 0x10), big-endian both -- an entry looked
 * up by its name (case aside) or by its index; cmn\savefile.c's savefileadr,
 * a block written to a file whole; and the fixed-point sine and cosine
 * (0x10000 a turn, 16.16 results) from the quarter wave at 0x5672ac.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, a string's length as repne scasb
 * leaves it, copies as the code makes them (movsd and movsb, two bytes a turn
 * to a string's end).  The kind of race's switch goes by the targets
 * nfs3.exe's table at 0x446050 holds.  Windows' functions are called through
 * their imports' slots; every function of the game's that is not this
 * file's, and those of this file's that the checks stand in for for other
 * files' natives (savefileadr, the file's age compared), by address. */
namespace nfs3hp
{
namespace load
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

// Where an Error is from: the file, the function, the line; a file not
// opened (or an entry not found) ends the game, when set.
constexpr reg32 kWhereFile = 0x552190, kWhereFunction = 0x552194, kWhereLine = 0x552198;
constexpr reg32 kErrorsFatal = 0x56440c;
// The game's strings.
constexpr reg32 kReplayName = 0x538bb4, kPercentS = 0x538bc0, kLapsFormat = 0x538bc4, kNoName = 0x538be8;
constexpr reg32 kGhostExtension = 0x538bec, kKeptFormat = 0x538bf0, kGhostName = 0x538bf8;
constexpr reg32 kReplayExtension = 0x538c14, kAllOfKind = 0x538c98, kRecordsFormat = 0x539578;
constexpr reg32 kRecordsBlockName = 0x539588, kLanguageNames = 0x53afd8, kConfigBlockName = 0x53b008;
constexpr reg32 kConfigFormat = 0x53b00c, kRaceReplayName = 0x540168, kReadWrite = 0x540174;
constexpr reg32 kLocatbigC = 0x54b5a4, kTypeOfBigFileName = 0x54b5b4, kNoBigFile = 0x54b5c4;
constexpr reg32 kNotBigFile = 0x54b5f4, kLocateBigEntryName = 0x54b620, kEntryNotFound = 0x54b630;
constexpr reg32 kIndexNotFound = 0x54b658, kSavefileC = 0x54c240, kSavefileadrName = 0x54c250;
constexpr reg32 kOpenFailed = 0x54c25c, kWriteFailed = 0x54c288;
// The replays' screen's four lines; the replays' and the saves' folders.
constexpr reg32 kReplayTrackLine = 0x558d0c, kReplayLapsLine = 0x558d84, kReplayKindLine = 0x558dfc;
constexpr reg32 kReplayCarLine = 0x558e74, kReplayFolder = 0x7a2f34, kSaveFolder = 0x7a3034;
constexpr reg32 kRecordsFolder = 0x7a2fb4;
// The replay's fields, its length; the replay of the race in memory.
constexpr reg32 kReplayKind = 0x1878, kReplayTrack = 0x196c, kReplayLaps = 0x1974, kReplayPlayer = 0x19b4;
constexpr reg32 kReplayCars = 0x1a00, kReplayBytes = 0x296f8, kRaceReplay = 0x7a3e50;
constexpr reg32 kRaceReplayVersion = 0x7a56b0, kRaceReplayLogged = 0x7a5f40, kRaceReplaySeed = 0x7a5f44;
// The replays' list: its entries at most, the block's length, where its
// names end.
constexpr reg32 kListEntries = 0xc8, kListBytes = 0x7b70, kListNamesEnd = 0x7538;
// The records' table, its length, its two parts.
constexpr reg32 kRecords = 0x559408, kRecordsFirst = 0x55940c, kRecordsSecond = 0x559410;
constexpr reg32 kRecordsBytes = 0x4197c, kRecordsVersion = 0x10;
// config.dat in memory, its length; the language and its name; whether the
// settings were made afresh; the version's word and the game's.
constexpr reg32 kConfig = 0x6fbb40, kConfigBytes = 0x20f0, kLanguage = 0x6fbb4c, kLanguageName = 0x7a2634;
constexpr reg32 kConfigMadeAfresh = 0x67900c, kConfigVersion = 0x6fbc10, kGameVersion = 0x7a3a58;
// The camera's views chosen and the race's numbers for them.
constexpr reg32 kViewsChosen = 0x6fbba8, kViews = 0x6fbbc0, kViewNumbers = 0x55629c;
// The command line's flags (0x20 a demo's, 0x10 another), the race's game
// mode, a replay shown, the network's player alone queued, the controllers.
constexpr reg32 kCommandFlags = 0x55eb2e, kGameMode = 0x6fd3b0, kReplayShown = 0x6fd3a0;
constexpr reg32 kOwnOnly = 0x6fd50c, kControllersKnown = 0x55b038;
// The default FILETIME (0x472160, among the code), the sine's quarter wave.
constexpr reg32 kNoTime = 0x472160, kQuarterWave = 0x5672ac;
// Windows' functions, by their imports' slots.
constexpr reg32 kCompareFileTime = 0x53448c, kGetFileTime = 0x534528, kGetModuleFileNameA = 0x534544;
constexpr reg32 kLclose = 0x534644, kLopen = 0x534648;
// The game's functions, by address.
constexpr reg32 kError = 0x401010, kIs3DSoundAvailable = 0x40faf0, kNewCarList = 0x438ad0;
constexpr reg32 kCarName = 0x439250, kCarListFirst = 0x439990, kRoomToSave = 0x4516a0;
constexpr reg32 kFileOlder = 0x472940, kLoadControllers = 0x472b60, kWriteReplayLog = 0x477ac0;
constexpr reg32 kReadReplayLog = 0x477b00, kReplaySum = 0x478010, kReplayValid = 0x478090;
constexpr reg32 kReplayChecked = 0x478100, kReplaySeal = 0x4781b0, kSetControlsMenu = 0x485880;
constexpr reg32 kDefaultControls = 0x4904f0, kRandomNumber = 0x4b56d0, kPickDetail = 0x4b62a0;
constexpr reg32 kLoadRaceReplay = 0x4bcb00, kScreenWidth = 0x4cef00, kNetworkActive = 0x4cf040;
constexpr reg32 kScreenDepth = 0x4cf160, kLanguageText = 0x4d1850, kSprintf = 0x4df690;
constexpr reg32 kMemset = 0x4e0640, kFillZero = 0x4e070c, kSeedRandom = 0x4e0dee, kFileExists = 0x4e0e60;
constexpr reg32 kLoadFile = 0x4e0ec0, kLoadFileQuietly = 0x4e0fe0, kMemBlockSize = 0x4e15d0;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kUnlink = 0x4e28a0, kOpenHandle = 0x4e28d0;
constexpr reg32 kOpenHandleToWrite = 0x4e2ae0, kCloseHandle = 0x4e2da0, kReadHandle = 0x4e2de0;
constexpr reg32 kWriteHandle = 0x4e2e20, kGetDirectory = 0x4e33a0, kRunSystemTasks = 0x4e7630;
constexpr reg32 kStricmp = 0x4e9ec0, kFopen = 0x4edfe8, kFclose = 0x4ee100;
constexpr reg32 kStrcmp = 0x4ee310, kChmod = 0x4ee3c0, kSavefileadr = 0x4eeae0, kChdir = 0x4f0260;
constexpr reg32 kFindNext = 0x4f0280, kFindFirst = 0x4f0330;

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

/* Where an Error is from, as the code sets it. */
void where(win32::WinApplication* app, reg32 file, reg32 function, reg32 line)
{
    put(app, kWhereFile, file);
    put(app, kWhereFunction, function);
    put(app, kWhereLine, line);
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

/* rep movsd: ecx dwords from esi to edi, both past them, ecx 0. */
void copyDwords(win32::WinApplication* app, x86::CPU& cpu)
{
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.edi += 4;
        cpu.esi += 4;
    }
}

/* push edi; mov eax, ecx; shr ecx, 2; rep movsd; mov cl, al; and cl, 3;
 * rep movsb; pop edi: ecx bytes from esi to edi, esi past them, edi as it
 * was, eax the count, ecx 0. */
void copyBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    cpu.eax = cpu.ecx;
    cpu.ecx >>= 2;
    copyDwords(app, cpu);
    cpu.cl = cpu.al;
    cpu.cl &= 3;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        putByte(app, cpu.edi, byte(app, cpu.esi));
        ++cpu.edi;
        ++cpu.esi;
    }
    cpu.edi = pop(app, cpu);
}

/* mov ecx, n; mov eax, [at]; bswap eax; neg ecx; lea ecx, [ecx*8 + 0x20];
 * shr eax, cl: the big-endian number of n bytes at `at` in eax, ecx the
 * shift. */
void bigEndian(win32::WinApplication* app, x86::CPU& cpu, reg32 address, reg32 bytes)
{
    const reg32 word = at(app, address);
    cpu.eax = word >> 24 | (word >> 8 & 0xff00) | (word << 8 & 0xff0000) | word << 24;
    cpu.ecx = 0x20 - 8 * bytes;
    cpu.eax >>= cpu.cl & 0x1f;
}

/* mov dl, '.'; then a byte a turn to the string's '.' or end; sub esi, esi
 * at its end (no '.'); mov byte ptr [esi], 0: the name at esi cut at its
 * '.' -- and without one, byte 0 of the guest's memory cleared, as the code
 * does. */
void cutAtDot(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.dl = '.';
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
    putByte(app, cpu.esi, 0);
}

/* cwde: ax sign-extended into eax. */
void cwde(x86::CPU& cpu)
{
    cpu.eax = reg32(sreg32(x86::sreg16(cpu.ax)));
}

}  // namespace

void readReplayInfo(win32::WinApplication* app, x86::CPU& cpu);
void saveGhostAs(win32::WinApplication* app, x86::CPU& cpu);
void loadKeptReplay(win32::WinApplication* app, x86::CPU& cpu);
void saveReplayAs(win32::WinApplication* app, x86::CPU& cpu);
void listReplays(win32::WinApplication* app, x86::CPU& cpu);
void loadRecords(win32::WinApplication* app, x86::CPU& cpu);
void saveRecords(win32::WinApplication* app, x86::CPU& cpu);
void languageStub(win32::WinApplication* app, x86::CPU& cpu);
void setLanguage(win32::WinApplication* app, x86::CPU& cpu);
void setCameraViews(win32::WinApplication* app, x86::CPU& cpu);
void defaultConfig(win32::WinApplication* app, x86::CPU& cpu);
void saveConfig(win32::WinApplication* app, x86::CPU& cpu);
void fileWriteTime(win32::WinApplication* app, x86::CPU& cpu);
void fileOlder(win32::WinApplication* app, x86::CPU& cpu);
void loadConfig(win32::WinApplication* app, x86::CPU& cpu);
void saveRaceReplay(win32::WinApplication* app, x86::CPU& cpu);
void readRaceReplay(win32::WinApplication* app, x86::CPU& cpu);
void typeOfBigFile(win32::WinApplication* app, x86::CPU& cpu);
void bigHeaderLength(win32::WinApplication* app, x86::CPU& cpu);
void findBigEntry(win32::WinApplication* app, x86::CPU& cpu);
void locateBigEntry(win32::WinApplication* app, x86::CPU& cpu);
void savefileadr(win32::WinApplication* app, x86::CPU& cpu);
void savefileadrQuietly(win32::WinApplication* app, x86::CPU& cpu);
void fixedSine(win32::WinApplication* app, x86::CPU& cpu);
void fixedCosine(win32::WinApplication* app, x86::CPU& cpu);

/* 0x446060: what the replays' screen shows of the replay named eax (an empty
 * name made replay.rp3 first): loaded whole, and if its track (0 to 8) and
 * kind of race are known and it checks out, its track's name, its laps, its
 * kind of race and its player's car's name printed into the screen's four
 * lines (0x558d0c on); then freed. */
void readReplayInfo(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const auto leave = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.ecx = cpu.eax;
    if (byte(app, cpu.eax) == 0)
    {
        cpu.esi = kReplayName;
        cpu.edi = cpu.ecx;
        copyString(app, cpu);
    }
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFileExists))
        return;
    if (cpu.eax == 0)
        return leave();
    cpu.edx = 0x10;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kLoadFileQuietly))
        return;
    cpu.edx = cpu.eax;
    if (cpu.eax == 0)
        return leave();
    cpu.ecx = 0xffffffff;
    cpu.esi = at(app, cpu.eax + kReplayTrack);
    cpu.eax = at(app, cpu.eax + kReplayKind);
    // The switch's table at 0x446050: 0x4460d2, 0x4460d9, 0x4460e0, 0x4460e7.
    switch (cpu.eax)
    {
    case 0:
        cpu.ecx = 0xd5;
        break;
    case 1:
        cpu.ecx = 0xd6;
        break;
    case 2:
        cpu.ecx = 0xd7;
        break;
    case 3:
        cpu.ecx = 0xdc;
        break;
    default:
        break;
    }
    if (sreg32(cpu.esi) <= 8 && sreg32(cpu.esi) >= 0 && sreg32(cpu.ecx) > 0)
    {
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kReplayValid))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = cpu.edx;
            if (!byAddress(app, cpu, kReplayChecked))
                return;
            if (cpu.eax != 0)
            {
                cpu.ebx = at(app, cpu.edx + kReplayPlayer);
                cpu.eax = cpu.ebx * 4;
                cpu.eax -= cpu.ebx;
                cpu.eax <<= 2;
                cpu.ebx = cpu.eax;
                cpu.eax <<= 3;
                cpu.eax += cpu.ebx;
                cpu.ebx = at(app, cpu.edx + cpu.eax + kReplayCars);
                cpu.eax = cpu.esi + 0x66;
                if (!byAddress(app, cpu, kLanguageText))
                    return;
                push(app, cpu, cpu.eax);
                push(app, cpu, kPercentS);
                push(app, cpu, kReplayTrackLine);
                if (!byAddress(app, cpu, kSprintf))
                    return;
                cpu.esp += 0xc;
                cpu.eax = 5;
                if (!byAddress(app, cpu, kLanguageText))
                    return;
                push(app, cpu, cpu.eax);
                cpu.esi = at(app, cpu.edx + kReplayLaps);
                push(app, cpu, cpu.esi);
                push(app, cpu, kLapsFormat);
                push(app, cpu, kReplayLapsLine);
                if (!byAddress(app, cpu, kSprintf))
                    return;
                cpu.esp += 0x10;
                cpu.eax = cpu.ecx;
                if (!byAddress(app, cpu, kLanguageText))
                    return;
                push(app, cpu, cpu.eax);
                push(app, cpu, kPercentS);
                push(app, cpu, kReplayKindLine);
                if (!byAddress(app, cpu, kSprintf))
                    return;
                cpu.esp += 0xc;
                cpu.eax = cpu.ebx;
                if (!byAddress(app, cpu, kCarName))
                    return;
                push(app, cpu, cpu.eax);
                push(app, cpu, kPercentS);
                push(app, cpu, kReplayCarLine);
                if (!byAddress(app, cpu, kSprintf))
                    return;
                cpu.esp += 0xc;
            }
        }
    }
    cpu.eax = cpu.edx;
    if (!byAddress(app, cpu, kFree))
        return;
    leave();
}

namespace
{

/* The replays' keeping: the file `from` (fileExists, loadFile) written as
 * "<the replays' folder><name eax>.<extension>" (savefileadr) and freed; 1
 * if it was there, else what fileExists or loadFile gave. */
void keepAs(win32::WinApplication* app, x86::CPU& cpu, reg32 extension, reg32 from)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x100;
    const reg32 ebp = cpu.ebp;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    push(app, cpu, extension);
    push(app, cpu, cpu.eax);
    push(app, cpu, kReplayFolder);
    push(app, cpu, kKeptFormat);
    cpu.eax = ebp - 0x100;
    push(app, cpu, cpu.eax);
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esp += 0x14;
    cpu.eax = from;
    if (!byAddress(app, cpu, kFileExists))
        return;
    if (cpu.eax == 0)
        return leave();
    cpu.edx = 0x10;
    cpu.eax = from;
    if (!byAddress(app, cpu, kLoadFile))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
        return leave();
    if (!byAddress(app, cpu, kMemBlockSize))
        return;
    cpu.ebx = cpu.eax;
    cpu.edx = cpu.ecx;
    cpu.eax = ebp - 0x100;
    if (!byAddress(app, cpu, kSavefileadr))
        return;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFree))
        return;
    cpu.eax = 1;
    leave();
}

}  // namespace

/* 0x446780: the ghost (ghost.gst) kept as "<name eax>.gst" in the replays'
 * folder (keepAs).  Called through the menus' table at 0x447a30. */
void saveGhostAs(win32::WinApplication* app, x86::CPU& cpu)
{
    keepAs(app, cpu, kGhostExtension, kGhostName);
}

/* 0x446990: a replay picked from the list made the race's replay and loaded:
 * an empty name eax is the last race's (replay.rp3 itself); another file's
 * loaded whole, replay.rp3 deleted and written anew from it (savefileadr).
 * Then config.dat saved and the replay loaded (0x4bcb00).  1 if it was. */
void loadKeptReplay(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const auto leave = [&] {
        cpu.eax = cpu.esi;
        cpu.ebp = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.dl = byte(app, cpu.eax);
    cpu.esi = 0;
    if (cpu.dl == 0)
    {
        if (!direct(app, cpu, saveConfig))
            return;
        if (!byAddress(app, cpu, kLoadRaceReplay))
            return;
        if (cpu.eax != 0)
            cpu.esi = 1;
        return leave();
    }
    cpu.edx = 0x10;
    if (!byAddress(app, cpu, kLoadFileQuietly))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
        return leave();
    cpu.eax = kReplayName;
    if (!byAddress(app, cpu, kUnlink))
        return;
    cpu.eax = cpu.ecx;
    cpu.edx = cpu.ecx;
    if (!byAddress(app, cpu, kMemBlockSize))
        return;
    cpu.ebx = cpu.eax;
    cpu.eax = kReplayName;
    if (!byAddress(app, cpu, kSavefileadr))
        return;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFree))
        return;
    if (cpu.edx == 0)
        return leave();
    if (!direct(app, cpu, saveConfig))
        return;
    if (!byAddress(app, cpu, kLoadRaceReplay))
        return;
    if (cpu.eax != 0)
        cpu.esi = 1;
    leave();
}

/* 0x446a10: the last race's replay (replay.rp3) kept as "<name eax>.rp3" in
 * the replays' folder (keepAs).  Called through the menus' table at
 * 0x447a30. */
void saveReplayAs(win32::WinApplication* app, x86::CPU& cpu)
{
    keepAs(app, cpu, kReplayExtension, kReplayName);
}

/* 0x4475a0: the replays' list (the menu's record eax) made of the files of
 * extension edx in the replays' folder: its block made anew (200 entries of
 * 8 bytes, the names after them), the last race's first ("rp3" and
 * replay.rp3 there: the language's text 0x143), then each file found (its
 * name cut at its '.') while there is room; the count and the one chosen
 * kept within it.  The directory as it was after. */
void listReplays(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x220;
    const reg32 ebp = cpu.ebp;
    put(app, ebp - 4, cpu.eax);
    put(app, ebp - 0x10, cpu.edx);
    cpu.edx = at(app, cpu.eax + 0x70);
    if (cpu.edx != 0)
    {
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kFree))
            return;
        cpu.eax = at(app, ebp - 4);
        put(app, cpu.eax + 0x70, 0);
    }
    cpu.eax = at(app, ebp - 4);
    cpu.edx = kListBytes;
    cpu.ebx = 0;
    put(app, cpu.eax + 0x48, kListEntries);
    cpu.eax = kNoName;
    if (!byAddress(app, cpu, kAllocate))
        return;
    cpu.edx = at(app, ebp - 4);
    put(app, cpu.edx + 0x70, cpu.eax);
    cpu.eax = at(app, cpu.edx + 0x48);
    cpu.eax <<= 3;
    cpu.edx = at(app, cpu.edx + 0x70);
    cpu.eax += cpu.edx;
    cpu.ebx = cpu.eax + 8;
    cpu.ecx = 0;
    cpu.eax += kListNamesEnd;
    cpu.edx = kReplayExtension;
    put(app, ebp - 0x14, cpu.eax);
    cpu.eax = at(app, ebp - 0x10);
    put(app, ebp - 8, cpu.ecx);
    if (!byAddress(app, cpu, kStrcmp))
        return;
    if (cpu.eax == 0)
    {
        cpu.eax = kReplayName;
        if (!byAddress(app, cpu, kFileExists))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = 0x143;
            if (!byAddress(app, cpu, kLanguageText))
                return;
            cpu.edi = cpu.ebx;
            cpu.esi = cpu.eax;
            copyString(app, cpu);
            cpu.eax = at(app, ebp - 4);
            cpu.eax = at(app, cpu.eax + 0x70);
            put(app, cpu.eax, cpu.ebx);
            cpu.eax = at(app, ebp - 4);
            cpu.eax = at(app, cpu.eax + 0x70);
            putByte(app, cpu.eax + 4, 0);
            cpu.eax = 0x143;
            if (!byAddress(app, cpu, kLanguageText))
                return;
            cpu.edi = cpu.eax;
            cpu.esi = 1;
            stringLength(app, cpu);
            cpu.eax = cpu.ecx + cpu.esi;
            put(app, ebp - 8, cpu.esi);
            cpu.ebx += cpu.eax;
        }
    }
    cpu.eax = ebp - 0x220;
    if (!byAddress(app, cpu, kGetDirectory))
        return;
    cpu.eax = kReplayFolder;
    cpu.edi = at(app, ebp - 0x10);
    if (!byAddress(app, cpu, kChdir))
        return;
    push(app, cpu, cpu.edi);
    push(app, cpu, kAllOfKind);
    cpu.eax = ebp - 0x20;
    push(app, cpu, cpu.eax);
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esp += 0xc;
    cpu.eax = ebp - 0x20;
    if (!byAddress(app, cpu, kFindFirst))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.edx = at(app, ebp - 4);
        cpu.eax = at(app, ebp - 8);
        cpu.edx = at(app, cpu.edx + 0x70);
        put(app, cpu.edx + cpu.eax * 8, cpu.ebx);
        cpu.edx = at(app, ebp - 4);
        cpu.edx = at(app, cpu.edx + 0x70);
        cpu.esi = cpu.ecx;
        putByte(app, cpu.edx + cpu.eax * 8 + 4, 0);
        cpu.edi = cpu.ebx;
        cutAtDot(app, cpu);
        cpu.esi = cpu.ecx;
        copyString(app, cpu);
        cpu.edi = cpu.ecx;
        for (;;)
        {
            // 0x447715: the name's length, and the room it took.
            stringLength(app, cpu);
            cpu.eax = cpu.ecx + 1;
            cpu.ebx += cpu.eax;
            put(app, ebp - 8, at(app, ebp - 8) + 1);
            cpu.edx = at(app, ebp - 8);
            if (sreg32(cpu.edx) >= sreg32(kListEntries))
                break;
            if (!byAddress(app, cpu, kFindNext))
                return;
            put(app, ebp - 0xc, cpu.eax);
            if (cpu.eax == 0)
                break;
            cpu.eax = cpu.edx;
            cpu.edx = at(app, ebp - 4);
            cpu.edx = at(app, cpu.edx + 0x70);
            put(app, cpu.edx + cpu.eax * 8, cpu.ebx);
            cpu.edx = at(app, ebp - 4);
            cpu.edx = at(app, cpu.edx + 0x70);
            cpu.esi = at(app, ebp - 0xc);
            putByte(app, cpu.edx + cpu.eax * 8 + 4, 0);
            cpu.edi = at(app, ebp - 0xc);
            cutAtDot(app, cpu);
            stringLength(app, cpu);
            cpu.esi = at(app, ebp - 0x14);
            cpu.eax = cpu.ebx + cpu.ecx;
            if (cpu.eax >= cpu.esi)
                break;
            cpu.esi = at(app, ebp - 0xc);
            cpu.edi = cpu.ebx;
            copyString(app, cpu);
            cpu.edi = at(app, ebp - 0xc);
        }
    }
    // 0x4477ba: the count, and the one chosen within it.
    cpu.edx = at(app, ebp - 4);
    cpu.eax = at(app, ebp - 8);
    put(app, cpu.edx + 0x48, cpu.eax);
    if (cpu.eax != 0)
    {
        cpu.ecx = at(app, cpu.edx + 0x48);
        if (sreg32(cpu.ecx) <= sreg32(at(app, cpu.edx + 0x4c)))
        {
            cpu.eax = cpu.ecx - 1;
            put(app, cpu.edx + 0x4c, cpu.eax);
        }
        cpu.eax = at(app, ebp - 4);
        if (sreg32(at(app, cpu.eax + 0x4c)) < 0)
            put(app, cpu.eax + 0x4c, 0);
    }
    else
        put(app, cpu.edx + 0x4c, cpu.eax);
    cpu.eax = ebp - 0x220;
    if (!byAddress(app, cpu, kChdir))
        return;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x44f510: records.dat ("<[0x7a2fb4]>records.dat") loaded, if it is not
 * already ([0x559408]): kept if its first word is 0x10, else freed; none
 * there, a table made empty (0x4197c bytes, 0x10 first).  Its two parts'
 * addresses to 0x55940c (+0x16e0) and 0x559410 (+4). */
void loadRecords(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x100;
    const reg32 ebp = cpu.ebp;
    cpu.edx = at(app, kRecords);
    if (cpu.edx == 0)
    {
        push(app, cpu, kRecordsFolder);
        push(app, cpu, kRecordsFormat);
        cpu.eax = ebp - 0x100;
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, kSprintf))
            return;
        cpu.esp += 0xc;
        cpu.eax = ebp - 0x100;
        if (!byAddress(app, cpu, kFileExists))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = ebp - 0x100;
            if (!byAddress(app, cpu, kLoadFile))
                return;
            cpu.ecx = at(app, cpu.eax);
            put(app, kRecords, cpu.eax);
            if (cpu.ecx != kRecordsVersion)
            {
                cpu.ebx = 0;
                if (!byAddress(app, cpu, kFree))
                    return;
                put(app, kRecords, cpu.ebx);
            }
        }
        if (at(app, kRecords) == 0)
        {
            cpu.edx = kRecordsBytes;
            cpu.eax = kRecordsBlockName;
            cpu.ebx = 0;
            if (!byAddress(app, cpu, kAllocate))
                return;
            cpu.edx = kRecordsBytes;
            put(app, kRecords, cpu.eax);
            if (!byAddress(app, cpu, kFillZero))
                return;
            cpu.eax = at(app, kRecords);
            put(app, cpu.eax, kRecordsVersion);
        }
        cpu.eax = at(app, kRecords);
        cpu.edx = cpu.eax + 0x16e0;
        cpu.eax += 4;
        put(app, kRecordsFirst, cpu.edx);
        put(app, kRecordsSecond, cpu.eax);
    }
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x44f5f0: the records' table, if loaded, saved as records.dat (made
 * writable first, if it is there: chmod 0x180) and freed. */
void saveRecords(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x100;
    const reg32 ebp = cpu.ebp;
    if (at(app, kRecords) != 0)
    {
        push(app, cpu, kRecordsFolder);
        push(app, cpu, kRecordsFormat);
        cpu.eax = ebp - 0x100;
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, kSprintf))
            return;
        cpu.esp += 0xc;
        cpu.eax = ebp - 0x100;
        if (!byAddress(app, cpu, kFileExists))
            return;
        if (cpu.eax != 0)
        {
            cpu.edx = 0x180;
            cpu.eax = ebp - 0x100;
            if (!byAddress(app, cpu, kChmod))
                return;
        }
        cpu.ebx = kRecordsBytes;
        cpu.eax = ebp - 0x100;
        cpu.edx = at(app, kRecords);
        if (!byAddress(app, cpu, kSavefileadr))
            return;
        cpu.eax = at(app, kRecords);
        cpu.ecx = 0;
        if (!byAddress(app, cpu, kFree))
            return;
        put(app, kRecords, cpu.ecx);
    }
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472230: the language checked against the game's mode eax -- an empty
 * function, its body compiled away: it compares the language with 1 and 2
 * and eax with 1, and does nothing.  defaultConfig calls it. */
void languageStub(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472250: the language ([0x6fbb4c]) from its name at 0x7a2634 --
 * english, german, french, spanish, italian, swedish: 0 to 5 -- left as it
 * is for another name.  eax the last strcmp's. */
void setLanguage(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    for (reg32 language = 0; language < 6; ++language)
    {
        cpu.edx = kLanguageName;
        cpu.eax = kLanguageNames + 8 * language;
        if (!byAddress(app, cpu, kStrcmp))
            return;
        if (cpu.eax == 0)
            put(app, kLanguage, language == 0 ? cpu.eax : language);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472300: the camera's four views chosen (0x6fbba8 on) made the race's
 * view numbers (0x6fbbc0 on), each through the table of words at 0x55629e.
 * eax the last. */
void setCameraViews(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    for (reg32 i = 0; i < 16; i += 4)
    {
        cpu.eax = at(app, kViewsChosen + i);
        cpu.eax = at(app, cpu.eax * 2 + kViewNumbers);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        put(app, kViews + i, cpu.eax);
    }
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4723f0: config.dat's settings made afresh, its defaults: the record
 * cleared, its length first and the 8 bytes at 0x55e8b8 after it; the race
 * (one player, no replay, a random seed), the camera's views (setCameraViews),
 * the screen's size and depth, the two cars' lists (0x438ad0, 0x439990), the
 * language (setLanguage) and what it sets, the sound's volumes and 3D, the
 * game's options, the two players' controls (0x4904f0), and what a demo's
 * command line sets; the controls' menus told (0x485880).  With the port's
 * change of tools/apply_track_detail.py in it: View Distance starts Full. */
void defaultConfig(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ebx = kConfigBytes;
    cpu.eax = kConfig;
    cpu.edi = kConfig + 4;
    cpu.edx = 0;
    cpu.esi = 0x55e8b8;
    if (!byAddress(app, cpu, kMemset))
        return;
    cpu.ecx = 0;
    cpu.edx = kConfigBytes;
    cpu.ebx = 3;
    put(app, kConfig, cpu.edx);
    cpu.edx = 1;
    for (int i = 0; i < 2; ++i)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.edi += 4;
        cpu.esi += 4;
    }
    if (!byAddress(app, cpu, kRandomNumber))
        return;
    put(app, 0x6fd3b4, cpu.eax);
    for (const reg32 address : {0x6fd2ac, 0x6fd2a8, 0x6fd3a0, 0x6fd3b0, 0x6fd3b8})
        put(app, address, cpu.ecx);
    put(app, 0x6fbba8, cpu.edx);
    put(app, 0x6fbbb0, cpu.ebx);
    cpu.esi = 0;
    cpu.ecx = 2;
    cpu.eax = at(app, 0x6fd4aa);
    put(app, 0x6fbbb4, cpu.esi);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    put(app, 0x6fbbac, cpu.ecx);
    if (!byAddress(app, cpu, kScreenWidth))
        return;
    cwde(cpu);
    cpu.edi = cpu.edx;
    put(app, 0x6fd2b4, cpu.eax);
    if (!direct(app, cpu, setCameraViews))
        return;
    cpu.eax = 0;
    put(app, 0x6fd4b4, cpu.ecx);
    for (const reg32 address : {0x6fd4c0, 0x6fd4c4, 0x6fd4c8, 0x6fd4cc, 0x6fd4f0, 0x6fd474, 0x6fd488, 0x6fd47c,
                                0x6fd480, 0x6fd484, 0x6fd478, 0x6fd4ac, 0x6fd470})
        put(app, address, cpu.eax);
    cpu.eax = at(app, 0x6fd4b2);
    put(app, 0x6fd4ec, cpu.edx);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    put(app, 0x6fd48c, cpu.edx);
    if (!byAddress(app, cpu, kScreenDepth))
        return;
    cwde(cpu);
    cpu.edx = 0x13;
    put(app, 0x6fd4b0, cpu.eax);
    cpu.eax = 0x6fd2c0;
    if (!byAddress(app, cpu, kNewCarList))
        return;
    cpu.eax = 0x6fd2c0;
    cpu.edx = 0x13;
    if (!byAddress(app, cpu, kCarListFirst))
        return;
    put(app, 0x6fd2bc, cpu.eax);
    put(app, 0x6fd2d8, cpu.esi);
    cpu.eax = 0x6fd32c;
    put(app, 0x6fd2d4, cpu.edi);
    if (!byAddress(app, cpu, kNewCarList))
        return;
    cpu.eax = 0x6fd32c;
    cpu.edi = 0;
    if (!byAddress(app, cpu, kCarListFirst))
        return;
    put(app, 0x6fd328, cpu.eax);
    put(app, 0x6fd344, cpu.edi);
    cpu.eax = 1;
    put(app, 0x6fd4d4, cpu.ecx);
    put(app, 0x6fd4d0, cpu.ecx);
    put(app, 0x6fd4e8, cpu.edi);
    put(app, 0x6fd340, cpu.eax);
    if (!direct(app, cpu, setLanguage))
        return;
    // English's (0) six settings 1, another language's ebx.
    reg32 setting = cpu.ebx;
    if (at(app, kLanguage) == 0)
    {
        cpu.edi = 1;
        setting = cpu.edi;
    }
    for (const reg32 address : {0x6fbfb0, 0x6fc2f8, 0x6fbe0c, 0x6fc154, 0x6fc49c, 0x6fbc68})
        put(app, address, setting);
    cpu.edi = 0x64;
    cpu.ecx = 0x7f;
    cpu.esi = 1;
    cpu.eax = 2;
    put(app, 0x6fbbe8, cpu.edi);
    put(app, 0x6fbbf0, cpu.edi);
    cpu.edx = cpu.edi;
    put(app, 0x6fbbf4, cpu.edi);
    put(app, 0x6fbbfc, cpu.ecx);
    put(app, 0x6fbbf8, cpu.edi);
    put(app, 0x6fbbe0, cpu.esi);
    put(app, 0x6fbbd8, cpu.esi);
    cpu.edx ^= cpu.edi;
    put(app, 0x6fbbe4, cpu.eax);
    put(app, 0x6fbbec, cpu.edx);
    put(app, 0x6fbbdc, cpu.edx);
    if (!byAddress(app, cpu, kIs3DSoundAvailable))
        return;
    put(app, 0x6fbc00, cpu.eax != 0 ? 3 : cpu.eax);
    cpu.edi = 1;
    cpu.eax = 2;
    cpu.edx = 3;
    cpu.cl = 0x7f;
    cpu.ebx = 0;
    put(app, 0x6fbc04, cpu.edi);
    put(app, 0x6fbc08, cpu.eax);
    put(app, 0x6fbc0c, cpu.edx);
    put(app, 0x6fd504, cpu.edx);
    put(app, 0x6fd204, cpu.ebx);
    put(app, 0x6fd208, cpu.ebx);
    put(app, 0x6fd3a8, cpu.eax);
    put(app, 0x6fbc14, cpu.ebx);
    put(app, 0x6fbc28, 0);  // the port's (tools/apply_track_detail.py): View Distance Full, was Far (edi)
    put(app, 0x6fbc1c, cpu.ebx);
    cpu.esi = cpu.edi;
    put(app, 0x6fbc20, cpu.edi);
    put(app, 0x6fbc24, cpu.edi);
    put(app, 0x6fbc2c, cpu.ebx);
    put(app, 0x6fbc30, cpu.ebx);
    put(app, 0x6fbc34, cpu.edi);
    put(app, 0x6fbc3c, cpu.edi);
    put(app, 0x6fbb58, cpu.ebx);
    put(app, 0x6fbb5c, cpu.ebx);
    put(app, 0x6fd508, cpu.ebx);
    put(app, 0x6fd50c, cpu.ebx);
    putByte(app, 0x6fd30a, cpu.cl);
    cpu.edx = 0x280;
    cpu.ch = 0xf;
    cpu.eax = 0;
    cpu.esi ^= cpu.edi;
    cpu.edi = 0x6fd30c;
    put(app, 0x6fbc18, cpu.edx);
    put(app, 0x6fbc40, cpu.esi);
    putByte(app, 0x6fd373, cpu.ch);
    putByte(app, 0x6fd376, cpu.cl);
    cpu.ah ^= cpu.bh;
    cpu.ecx = 7;
    cpu.esi = 0x55d024;
    putByte(app, 0x6fd2fc, cpu.ah);
    cpu.edx = 0;
    putByte(app, 0x6fd374, cpu.ah);
    cpu.dl ^= cpu.bl;
    putByte(app, 0x6fd375, cpu.ah);
    putByte(app, 0x6fd368, cpu.dl);
    cpu.dh ^= cpu.bh;
    cpu.bl ^= cpu.bl;
    putByte(app, 0x6fd307, cpu.dh);
    putByte(app, 0x6fd308, cpu.bl);
    putByte(app, 0x6fd309, cpu.bl);
    copyDwords(app, cpu);
    cpu.ecx = 7;
    cpu.edi = 0x6fd378;
    cpu.esi = 0x55d024;
    copyDwords(app, cpu);
    cpu.esi = kConfigBlockName;
    cpu.edi = 0x6fbb60;
    copyString(app, cpu);
    cpu.eax = at(app, kGameMode);
    if (!direct(app, cpu, languageStub))
        return;
    cpu.eax = 0;
    cpu.ebx = 0x64;
    if (!byAddress(app, cpu, kDefaultControls))
        return;
    cpu.eax = 1;
    cpu.edi = 0x32;
    if (!byAddress(app, cpu, kDefaultControls))
        return;
    cpu.dh = byte(app, kCommandFlags);
    put(app, 0x6fd1f0, cpu.ebx);
    put(app, 0x6fd1f4, cpu.ebx);
    put(app, 0x6fd1f8, cpu.edi);
    cpu.eax = 0;
    put(app, 0x6fd200, cpu.ebx);
    put(app, 0x6fd1fc, cpu.eax);
    if (cpu.dh & 0x20)
    {
        put(app, 0x6fd470, cpu.eax);
        put(app, 0x6fd4e8, cpu.eax);
        cpu.eax = 1;
        cpu.ecx = 3;
        put(app, 0x6fd4b4, cpu.eax);
        cpu.edx = 2;
        cpu.eax = at(app, 0x6fd4b2);
        put(app, 0x6fd3b8, cpu.ecx);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        put(app, 0x6fd4ac, cpu.ecx);
        if (!byAddress(app, cpu, kScreenDepth))
            return;
        cwde(cpu);
        put(app, 0x6fd4d4, cpu.edx);
        put(app, 0x6fd4b0, cpu.eax);
    }
    else if (cpu.dh & 0x10)
    {
        cpu.ebx = 3;
        put(app, 0x6fd470, cpu.eax);
        put(app, 0x6fd3b8, cpu.eax);
        put(app, 0x6fd4ac, cpu.ebx);
    }
    if (!byAddress(app, cpu, kSetControlsMenu))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472820: config.dat saved -- a copy of the settings, its +0x1860 cleared,
 * written as "<[0x7a3034]>config.dat" (savefileadr) -- unless the game runs
 * from a demo's command line, a replay is shown, there is no room for it
 * (0x4516a0), or [0x55e88c] says not to. */
void saveConfig(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0xfc;
    const reg32 ebp = cpu.ebp;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if ((byte(app, kCommandFlags) & 0x20) != 0 || at(app, kReplayShown) != 0)
        return leave();
    cpu.eax = kConfigBytes;
    if (!byAddress(app, cpu, kRoomToSave))
        return;
    if (cpu.eax == 0 || at(app, 0x55e88c) != 0)
        return leave();
    cpu.edx = kConfigBytes;
    cpu.eax = kConfigBlockName;
    cpu.ecx = kConfigBytes;
    cpu.ebx = 0;
    cpu.esi = kConfig;
    if (!byAddress(app, cpu, kAllocate))
        return;
    cpu.edi = cpu.eax;
    copyBytes(app, cpu);
    push(app, cpu, kSaveFolder);
    cpu.eax = cpu.edi;
    push(app, cpu, kConfigFormat);
    put(app, cpu.eax + 0x1860, 0);
    cpu.eax = ebp - 0xfc;
    push(app, cpu, cpu.eax);
    cpu.ebx = kConfigBytes;
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esp += 0xc;
    cpu.edx = cpu.edi;
    cpu.eax = ebp - 0xfc;
    if (!byAddress(app, cpu, kSavefileadr))
        return;
    cpu.eax = cpu.edi;
    if (!byAddress(app, cpu, kFree))
        return;
    leave();
}

/* 0x4728e0: the last write time of the file named eax (_lopen, GetFileTime,
 * _lclose) into the 8 bytes at esi; 0 if it is not opened (_lopen's 0 --
 * its HFILE_ERROR, -1, taken as a file).  esi back in eax; esi itself left
 * past the frame's copy. */
void fileWriteTime(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x10;
    const reg32 ebp = cpu.ebp;
    const auto movsd = [&] {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.edi += 4;
        cpu.esi += 4;
    };
    cpu.ebx = cpu.esi;
    push(app, cpu, 0);
    cpu.edi = ebp - 0x10;
    cpu.esi = kNoTime;
    push(app, cpu, cpu.eax);
    movsd();
    movsd();
    if (!windows(app, cpu, kLopen))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax == 0)
    {
        cpu.edi = ebp - 8;
        cpu.esi = ebp - 0x10;
    }
    else
    {
        cpu.eax = ebp - 0x10;
        push(app, cpu, cpu.eax);
        push(app, cpu, 0);
        push(app, cpu, 0);
        push(app, cpu, cpu.esi);
        if (!windows(app, cpu, kGetFileTime))
            return;
        push(app, cpu, cpu.esi);
        cpu.edi = ebp - 8;
        cpu.esi = ebp - 0x10;
        if (!windows(app, cpu, kLclose))
            return;
    }
    movsd();
    movsd();
    cpu.esi = ebp - 8;
    cpu.edi = cpu.ebx;
    movsd();
    movsd();
    cpu.eax = cpu.ebx;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472940: 1 if the file named eax was written before the one named edx
 * (fileWriteTime, CompareFileTime's -1), else 0.  loadConfig asks it of
 * config.dat and nfs3.exe. */
void fileOlder(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x10;
    const reg32 ebp = cpu.ebp;
    cpu.esi = ebp - 0x10;
    if (!direct(app, cpu, fileWriteTime))
        return;
    cpu.esi = ebp - 8;
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, fileWriteTime))
        return;
    cpu.eax = ebp - 8;
    push(app, cpu, cpu.eax);
    cpu.eax = ebp - 0x10;
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kCompareFileTime))
        return;
    cpu.eax = cpu.eax == 0xffffffff ? 1 : 0;
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x472980: config.dat loaded at the start ("<[0x7a3034]>config.dat",
 * opened unless the game runs from a demo's command line): read into a block
 * and copied over the settings if it is 0x20f0 bytes and not older than
 * nfs3.exe, the sound's volume taken from it; else deleted (an old one) and
 * the settings made afresh (defaultConfig), [0x67900c] set -- as for another
 * version.  Then the race's mode for a demo, the random seed, the language,
 * the detail, and the controllers (0x472b60) if they are known. */
void loadConfig(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x208;
    const reg32 ebp = cpu.ebp;
    push(app, cpu, 0xf9);
    cpu.eax = ebp - 0x10c;
    push(app, cpu, cpu.eax);
    cpu.edx = 0;
    push(app, cpu, cpu.edx);
    put(app, ebp - 0xc, cpu.edx);
    put(app, ebp - 0x10, cpu.edx);
    if (!windows(app, cpu, kGetModuleFileNameA))
        return;
    push(app, cpu, kSaveFolder);
    push(app, cpu, kConfigFormat);
    cpu.eax = ebp - 0x208;
    push(app, cpu, cpu.eax);
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esp += 0xc;
    cpu.eax = 0;
    if (!byAddress(app, cpu, kRunSystemTasks))
        return;
    if ((byte(app, kCommandFlags) & 0x20) == 0)
    {
        cpu.eax = ebp - 0x208;
        if (!byAddress(app, cpu, kFileExists))
            return;
        if (cpu.eax != 0)
        {
            cpu.ecx = ebp - 8;
            cpu.ebx = ebp - 0x10;
            cpu.edx = ebp - 0xc;
            cpu.eax = ebp - 0x208;
            if (!byAddress(app, cpu, kOpenHandle))
                return;
        }
    }
    cpu.eax = 0;
    if (!byAddress(app, cpu, kRunSystemTasks))
        return;
    if (at(app, ebp - 0xc) == 0)
    {
        put(app, kConfigMadeAfresh, 1);
        if (!direct(app, cpu, defaultConfig))
            return;
    }
    else
    {
        cpu.edi = at(app, ebp - 8);
        bool fresh = true;
        if (cpu.edi == kConfigBytes)
        {
            cpu.edx = ebp - 0x10c;
            cpu.eax = ebp - 0x208;
            if (!byAddress(app, cpu, kFileOlder))
                return;
            fresh = cpu.eax != 0;
        }
        if (fresh)
        {
            put(app, kConfigMadeAfresh, 1);
            cpu.eax = at(app, ebp - 0xc);
            if (!byAddress(app, cpu, kCloseHandle))
                return;
            cpu.eax = ebp - 0x208;
            if (!byAddress(app, cpu, kUnlink))
                return;
            if (!direct(app, cpu, defaultConfig))
                return;
        }
        else
        {
            cpu.ebx = 0x10;
            cpu.edx = at(app, ebp - 8);
            put(app, kConfigMadeAfresh, cpu.eax);
            cpu.eax = kConfigBlockName;
            cpu.ecx = cpu.edi;
            if (!byAddress(app, cpu, kAllocate))
                return;
            cpu.ebx = at(app, ebp - 8);
            put(app, ebp - 4, cpu.eax);
            cpu.edx = cpu.eax;
            cpu.eax = at(app, ebp - 0xc);
            cpu.edi = kConfig;
            if (!byAddress(app, cpu, kReadHandle))
                return;
            cpu.eax = at(app, ebp - 0xc);
            cpu.esi = at(app, ebp - 4);
            if (!byAddress(app, cpu, kCloseHandle))
                return;
            copyBytes(app, cpu);
            cpu.eax = at(app, ebp - 4);
            if (!byAddress(app, cpu, kFree))
                return;
            cpu.eax = at(app, 0x6fbbf4);
            put(app, 0x552920, cpu.eax);
        }
    }
    // 0x472ab6: another length, or another version: made afresh too.
    if (at(app, kConfig) != kConfigBytes)
    {
        put(app, kConfigMadeAfresh, 1);
        if (!direct(app, cpu, defaultConfig))
            return;
    }
    cpu.esi = at(app, kGameVersion);
    if (cpu.esi != at(app, kConfigVersion))
        put(app, kConfigMadeAfresh, 1);
    cpu.dl = byte(app, kCommandFlags);
    if (cpu.dl & 0x20)
        put(app, 0x6fd3b8, 3);
    else if (cpu.dl & 0x10)
    {
        cpu.edx = 0;
        put(app, 0x6fd3b8, cpu.edx);
    }
    if (!byAddress(app, cpu, kRandomNumber))
        return;
    put(app, 0x6fd3b4, cpu.eax);
    if (!byAddress(app, cpu, kRandomNumber))
        return;
    putByte(app, 0x57126b, cpu.al);
    cpu.eax = at(app, 0x6fd3b4);
    cpu.ecx = 0;
    if (!byAddress(app, cpu, kSeedRandom))
        return;
    if (!direct(app, cpu, setLanguage))
        return;
    put(app, kOwnOnly, cpu.ecx);
    if (!byAddress(app, cpu, kPickDetail))
        return;
    cpu.ebx = at(app, kControllersKnown);
    put(app, 0x6fbb54, cpu.eax);
    if (cpu.ebx != 0)
    {
        if (!byAddress(app, cpu, kLoadControllers))
            return;
        put(app, kControllersKnown, cpu.ecx);
    }
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4bd1e0: the race just run saved as replay.rp3 -- if replays are on
 * ([0x6fd3ac]), the race not a network's with its own players only, and no
 * network game on (0x4cf040): config.dat's settings copied to its head, its
 * version, whether the frames' log follows and the seed set, checksummed
 * (0x478010, 0x4781b0) and written (savefileadr); the log appended
 * (0x477ac0) to the file opened "rb+". */
void saveRaceReplay(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x3c;
    const reg32 ebp = cpu.ebp;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (at(app, 0x6fd3ac) == 0)
        return leave();
    if (sreg32(at(app, kGameMode)) > 1 && at(app, kOwnOnly) != 0)
        return leave();
    if (!byAddress(app, cpu, kNetworkActive))
        return;
    if (cpu.eax != 0)
        return leave();
    push(app, cpu, kRaceReplayName);
    cpu.eax = ebp - 0x3c;
    push(app, cpu, cpu.eax);
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esi = at(app, 0x7cda58);
    cpu.esp += 8;
    if (cpu.esi == 0)
    {
        cpu.eax = at(app, 0x7d3684);
        put(app, 0x55fe40, cpu.eax);
    }
    cpu.ecx = kConfigBytes / 4;
    cpu.edi = kRaceReplay;
    cpu.esi = kConfig;
    copyDwords(app, cpu);
    cpu.edi = 2;
    cpu.eax = at(app, 0x55d000);
    put(app, kRaceReplayVersion, cpu.edi);
    if (cpu.eax != 1)
        cpu.eax = 0;
    put(app, kRaceReplayLogged, cpu.eax);
    cpu.eax = at(app, 0x55fe40);
    put(app, kRaceReplaySeed, cpu.eax);
    cpu.eax = kRaceReplay;
    cpu.ebx = kReplayBytes;
    if (!byAddress(app, cpu, kReplaySum))
        return;
    cpu.eax = kRaceReplay;
    cpu.edx = kRaceReplay;
    if (!byAddress(app, cpu, kReplaySeal))
        return;
    cpu.eax = ebp - 0x3c;
    if (!byAddress(app, cpu, kSavefileadr))
        return;
    if (at(app, 0x55d000) != 1)
        return leave();
    cpu.edx = kReadWrite;
    cpu.eax = ebp - 0x3c;
    if (!byAddress(app, cpu, kFopen))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
        return leave();
    cpu.edx = kReplayBytes;
    if (!byAddress(app, cpu, kWriteReplayLog))
        return;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFclose))
        return;
    leave();
}

/* 0x4bd2e0: replay.rp3 read into the race's replay (0x7a3e50) -- its frames'
 * log too (0x477b00) if it says one follows -- and checked (0x478090,
 * 0x478100): 1 if it was there and checks out, else 0 (and [0x7cda58]
 * cleared when it is not there). */
void readRaceReplay(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x5c;
    const reg32 ebp = cpu.ebp;
    const auto leave = [&] {
        cpu.eax = cpu.esi;
        cpu.esp = cpu.ebp;
        cpu.ebp = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    push(app, cpu, kRaceReplayName);
    cpu.eax = ebp - 0x5c;
    cpu.ecx = ebp - 8;
    cpu.ebx = ebp - 4;
    cpu.edx = 0;
    push(app, cpu, cpu.eax);
    put(app, ebp - 0xc, cpu.edx);
    put(app, ebp - 4, cpu.edx);
    if (!byAddress(app, cpu, kSprintf))
        return;
    cpu.esp += 8;
    cpu.edx = ebp - 0xc;
    cpu.eax = ebp - 0x5c;
    if (!byAddress(app, cpu, kOpenHandle))
        return;
    cpu.ebx = at(app, ebp - 0xc);
    cpu.esi = 1;
    if (cpu.ebx == 0)
    {
        put(app, 0x7cda58, cpu.ebx);
        cpu.esi = 0;
        return leave();
    }
    cpu.ebx = kReplayBytes;
    cpu.edx = kRaceReplay;
    cpu.eax = at(app, ebp - 0xc);
    if (!byAddress(app, cpu, kReadHandle))
        return;
    if (at(app, kRaceReplayLogged) != 0)
    {
        cpu.eax = at(app, ebp - 0xc);
        if (!byAddress(app, cpu, kReadReplayLog))
            return;
    }
    cpu.eax = at(app, ebp - 0xc);
    if (!byAddress(app, cpu, kCloseHandle))
        return;
    cpu.eax = kRaceReplay;
    if (!byAddress(app, cpu, kReplayValid))
        return;
    if (cpu.eax == 0)
        cpu.esi = 0;
    cpu.eax = kRaceReplay;
    if (!byAddress(app, cpu, kReplayChecked))
        return;
    if (cpu.eax == 0)
        cpu.esi = 0;
    leave();
}

/* 0x4e9f00, EA's typeofbigfile: the kind of BIG archive at eax -- 1 for
 * 0xc0fb, 2 for "BIGF", else 0; none at all, or not one, an Error while
 * [0x56440c] is set. */
void typeOfBigFile(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.eax = cpu.ebx;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edx = cpu.eax;
    cpu.ebx = 0;
    if (cpu.eax == 0 && at(app, kErrorsFatal) != 0)
    {
        cpu.esi = kLocatbigC;
        cpu.edi = kTypeOfBigFileName;
        cpu.ebp = 0x11;
        push(app, cpu, kNoBigFile);
        where(app, cpu.esi, cpu.edi, cpu.ebp);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 4;
    }
    bigEndian(app, cpu, cpu.edx, 2);
    if (cpu.eax == 0xc0fb)
    {
        cpu.ebx = 1;
        return leave();
    }
    bigEndian(app, cpu, cpu.edx, 4);
    if (cpu.eax == 0x42494746)
    {
        cpu.ebx = 2;
        return leave();
    }
    if (cpu.ebx != 0 || at(app, kErrorsFatal) == 0)
        return leave();
    cpu.ecx = kLocatbigC;
    push(app, cpu, cpu.edx);
    cpu.esi = kTypeOfBigFileName;
    cpu.edi = 0x21;
    push(app, cpu, kNotBigFile);
    where(app, cpu.ecx, cpu.esi, cpu.edi);
    if (!byAddress(app, cpu, kError))
        return;
    cpu.esp += 8;
    leave();
}

/* 0x4e9fe0: the length of the BIG archive eax's header -- 0xc0fb's 16-bit
 * one at 2 and its 4 bytes, BIGF's at 0xc -- or 0 if it is none. */
void bigHeaderLength(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    cpu.ecx = cpu.eax;
    if (!direct(app, cpu, typeOfBigFile))
        return;
    cpu.edx = 0;
    if (cpu.eax == 1)
    {
        bigEndian(app, cpu, cpu.ecx + 2, 2);
        cpu.edx = cpu.eax + 4;
    }
    else if (cpu.eax == 2)
    {
        bigEndian(app, cpu, cpu.ecx + 0xc, 4);
        cpu.edx = cpu.eax;
    }
    cpu.eax = cpu.edx;
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4ea040: the entry of the BIG archive eax named edx (case aside; the
 * names' first four letters looked at first), or with no name the ebx'th:
 * its offset to [ecx] and its size to [[esp+4]] (either pointer may be 0),
 * its name's address back -- or 0, and the two 0, if there is none.  ret 4.
 * locateBigEntry's, without its Errors. */
void findBigEntry(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0x10;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.esp = f + 0x10;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4 + 4;
    };
    const auto none = [&] {
        // 0x4ea070
        cpu.edi = at(app, f);
        if (cpu.edi != 0)
            put(app, cpu.edi, 0);
        cpu.ebp = at(app, f + 0x20);
        if (cpu.ebp != 0)
            put(app, cpu.ebp, 0);
        cpu.eax = 0;
        leave();
    };
    // The entry at ebx found: its offset and size, of `bytes` each, and its
    // name after them.
    const auto found = [&](reg32 bytes) {
        if (at(app, f) != 0)
        {
            bigEndian(app, cpu, cpu.ebx, bytes);
            cpu.ecx = at(app, f);
            put(app, cpu.ecx, cpu.eax);
        }
        cpu.esi = at(app, f + 0x20);
        if (cpu.esi != 0)
        {
            bigEndian(app, cpu, cpu.ebx + bytes, bytes);
            put(app, cpu.esi, cpu.eax);
        }
        cpu.eax = cpu.ebx + 2 * bytes;
        leave();
    };
    cpu.edi = cpu.eax;
    cpu.ebp = cpu.edx;
    put(app, f + 4, cpu.ebx);
    put(app, f, cpu.ecx);
    if (!direct(app, cpu, bigHeaderLength))
        return;
    cpu.edx = 0;
    cpu.ecx = cpu.edi;
    put(app, f + 0xc, cpu.edx);
    cpu.ecx += cpu.eax;
    cpu.eax = cpu.edi;
    put(app, f + 8, cpu.ecx);
    if (!direct(app, cpu, typeOfBigFile))
        return;
    if (cpu.eax < 1)
        return none();
    if (cpu.eax == 1)
    {
        cpu.ebx = cpu.edi + 6;
        if (cpu.ebx >= cpu.ecx)
            return none();
        for (;;)
        {
            // 0x4ea0a4
            if (cpu.ebp != 0)
            {
                // 0x4ea188: on to the first entry whose name's first four
                // letters are edx's, case aside -- or the archive's end.
                cpu.edx = at(app, f + 8);
                cpu.esi = cpu.ebp;
                cpu.edi = cpu.ebx;
                cpu.esi = at(app, cpu.esi);
                cpu.esi |= 0x20202020;
                while (sreg32(cpu.edi) < sreg32(cpu.edx))
                {
                    cpu.eax = at(app, cpu.edi + 6);
                    cpu.eax |= 0x20202020;
                    if (cpu.eax == cpu.esi)
                        break;
                    // The name's end, a dword at a time from its fifth byte.
                    cpu.eax = at(app, cpu.edi + 0xa);
                    cpu.edi += 0xe;
                    cpu.eax -= 0x1010101;
                    cpu.eax &= 0x80808080;
                    while (cpu.eax == 0)
                    {
                        cpu.eax = at(app, cpu.edi);
                        cpu.edi += 4;
                        cpu.eax -= 0x1010101;
                        cpu.eax &= 0x80808080;
                    }
                    cpu.al = byte(app, cpu.edi - 4);
                    cpu.edi -= 3;
                    if (cpu.al == 0)
                        continue;
                    cpu.al = byte(app, cpu.edi);
                    cpu.edi += 1;
                    if (cpu.al == 0)
                        continue;
                    cpu.al = byte(app, cpu.edi);
                    cpu.edi += 1;
                    if (cpu.al == 0)
                        continue;
                    cpu.al = byte(app, cpu.edi);
                    cpu.edi += 1;
                    if (cpu.al == 0)
                        continue;
                    break;
                }
                cpu.ebx = cpu.edi;
            }
            // 0x4ea0ac
            bool match;
            if (cpu.ebp != 0)
                match = false;
            else
                match = at(app, f + 0xc) == at(app, f + 4);
            if (!match && cpu.ebp != 0)
            {
                // 0x4ea208
                cpu.eax = cpu.ebx + 6;
                cpu.edx = cpu.ebp;
                if (!byAddress(app, cpu, kStricmp))
                    return;
                match = cpu.eax == 0;
            }
            if (match)
                return found(3);
            // 0x4ea21e: on to the next entry.
            cpu.edi = cpu.ebx + 6;
            stringLength(app, cpu);
            cpu.edi = at(app, f + 0xc);
            cpu.eax = at(app, f + 8);
            cpu.ebx += cpu.ecx;
            ++cpu.edi;
            cpu.ebx += 7;
            put(app, f + 0xc, cpu.edi);
            if (cpu.ebx >= cpu.eax)
                return none();
        }
    }
    if (cpu.eax != 2)
        return none();
    cpu.ebx = cpu.edi + 0x10;
    if (cpu.ebx >= cpu.ecx)
        return none();
    for (;;)
    {
        // 0x4ea124
        bool match;
        if (cpu.ebp != 0)
            match = false;
        else
            match = at(app, f + 0xc) == at(app, f + 4);
        if (!match && cpu.ebp != 0)
        {
            // 0x4ea24a
            cpu.eax = cpu.ebx + 8;
            cpu.edx = cpu.ebp;
            if (!byAddress(app, cpu, kStricmp))
                return;
            match = cpu.eax == 0;
        }
        if (match)
            return found(4);
        // 0x4ea260
        cpu.edi = cpu.ebx + 8;
        stringLength(app, cpu);
        cpu.edi = at(app, f + 0xc);
        cpu.eax = at(app, f + 8);
        cpu.ebx += cpu.ecx;
        ++cpu.edi;
        cpu.ebx += 9;
        put(app, f + 0xc, cpu.edi);
        if (cpu.ebx >= cpu.eax)
            return none();
    }
}

/* 0x4ea290, EA's locatebigentry: findBigEntry's (the archive eax, the name
 * edx or the index ebx, [ecx] and [[esp+4]] its offset and size), and an
 * Error for an entry not found while [0x56440c] is set.  ret 4. */
void locateBigEntry(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    const auto leave = [&] {
        cpu.eax = cpu.ecx;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.esp += 4 + 4;
    };
    cpu.esi = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.edx = at(app, cpu.esp + 0x10);
    push(app, cpu, cpu.edx);
    cpu.edx = cpu.esi;
    if (!direct(app, cpu, findBigEntry))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax != 0 || at(app, kErrorsFatal) == 0)
        return leave();
    if (cpu.esi != 0)
    {
        cpu.edx = kLocatbigC;
        push(app, cpu, cpu.esi);
        cpu.ebx = kLocateBigEntryName;
        cpu.edi = 0xef;
        push(app, cpu, kEntryNotFound);
        where(app, cpu.edx, cpu.ebx, cpu.edi);
    }
    else
    {
        cpu.esi = kLocatbigC;
        push(app, cpu, cpu.edi);
        cpu.ebp = kLocateBigEntryName;
        cpu.eax = 0xf1;
        push(app, cpu, kIndexNotFound);
        where(app, cpu.esi, cpu.ebp, cpu.eax);
    }
    if (!byAddress(app, cpu, kError))
        return;
    cpu.esp += 8;
    leave();
}

/* 0x4eeae0, EA's savefileadr: ebx bytes at edx written to the file named eax
 * (made anew: openhandlew, writehandle, closehandle); how many back, 0 if it
 * did not open -- either failure an Error while [0x56440c] is set. */
void savefileadr(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.esp -= 0xc;
    const reg32 f = cpu.esp;
    const auto leave = [&] {
        cpu.esp = f + 0xc;
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    cpu.ebp = cpu.ebx;
    cpu.ecx = f + 8;
    cpu.ebx = f + 4;
    cpu.edx = f;
    if (!byAddress(app, cpu, kOpenHandleToWrite))
        return;
    if (cpu.eax == 0)
    {
        if (at(app, kErrorsFatal) != 0)
        {
            cpu.edx = kSavefileC;
            push(app, cpu, cpu.esi);
            cpu.ecx = kSavefileadrName;
            cpu.ebx = 0x60;
            push(app, cpu, kOpenFailed);
            where(app, cpu.edx, cpu.ecx, cpu.ebx);
            if (!byAddress(app, cpu, kError))
                return;
            cpu.esp += 8;
        }
        cpu.eax = 0;
        return leave();
    }
    cpu.eax = at(app, f);
    cpu.ebx = cpu.ebp;
    cpu.edx = cpu.edi;
    if (!byAddress(app, cpu, kWriteHandle))
        return;
    cpu.edx = cpu.eax;
    cpu.ecx = cpu.eax;
    cpu.eax = at(app, f);
    if (!byAddress(app, cpu, kCloseHandle))
        return;
    if (cpu.edx == 0 && at(app, kErrorsFatal) != 0)
    {
        cpu.ebx = kSavefileC;
        push(app, cpu, cpu.esi);
        cpu.edi = kSavefileadrName;
        cpu.ebp = 0x6a;
        push(app, cpu, kWriteFailed);
        where(app, cpu.ebx, cpu.edi, cpu.ebp);
        if (!byAddress(app, cpu, kError))
            return;
        cpu.esp += 8;
    }
    cpu.eax = cpu.ecx;
    leave();
}

/* 0x4eebb0: savefileadr with its Errors off ([0x56440c] cleared about it). */
void savefileadrQuietly(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    cpu.esi = 0;
    cpu.ecx = at(app, kErrorsFatal);
    put(app, kErrorsFatal, cpu.esi);
    if (!byAddress(app, cpu, kSavefileadr))
        return;
    put(app, kErrorsFatal, cpu.ecx);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* The quarter wave's entry for the angle's 1024th in eax (sar eax, 6 done):
 * shl r8, 7; sbb edx, edx; add r8, r8; sbb ecx, ecx -- r8 the byte above
 * `byteOf`'s low one, its bit 1 the half (edx -1: negative), its bit 0 the
 * quarter (ecx -1: backwards) -- then xor eax, ecx; and eax, 0xff; sub eax,
 * ecx; the table's word; xor eax, edx; sub eax, edx.  The byte shifted
 * written back, as the code leaves it. */
void quarterWave(win32::WinApplication* app, x86::CPU& cpu, reg8& high)
{
    const reg8 shifted = reg8(high << 7);
    cpu.edx = (high >> 1 & 1) ? 0xffffffff : 0;
    high = reg8(shifted << 1);
    cpu.ecx = (shifted >> 7 & 1) ? 0xffffffff : 0;
    cpu.eax ^= cpu.ecx;
    cpu.eax &= 0xff;
    cpu.eax -= cpu.ecx;
    cpu.eax = at(app, cpu.eax * 4 + kQuarterWave);
    cpu.eax ^= cpu.edx;
    cpu.eax -= cpu.edx;
}

}  // namespace

/* 0x4f2380: the sine of the angle eax (0x10000 a turn), 16.16: the quarter
 * wave's entry for its 1024th, and the cosine's times the 64th left (by
 * 2 pi) added.  The race's and the menus' 3D call it. */
void fixedSine(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.esi = cpu.eax;
    cpu.esi &= 0x3f;
    cpu.esi = reg32(sreg32(cpu.esi) * 0x6487e);
    cpu.eax = reg32(sreg32(cpu.eax) >> 6);
    cpu.ebx = cpu.eax;
    quarterWave(app, cpu, cpu.ah);
    cpu.edi = cpu.eax;
    cpu.eax = cpu.ebx;
    cpu.ecx = cpu.eax + 0x100;
    quarterWave(app, cpu, cpu.ch);
    cpu.eax = reg32(sreg32(cpu.eax) >> 2);
    cpu.esi = reg32(sreg32(cpu.esi) >> 9);
    cpu.eax = reg32(sreg32(cpu.eax) * sreg32(cpu.esi));
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x15);
    cpu.eax += cpu.edi;
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4f23f0: the cosine of the angle eax, as fixedSine: the quarter wave's
 * entry a quarter on, and the sine's times the 64th left taken off. */
void fixedCosine(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    cpu.esi = cpu.eax;
    cpu.esi &= 0x3f;
    cpu.esi = reg32(sreg32(cpu.esi) * 0x6487e);
    cpu.eax = reg32(sreg32(cpu.eax) >> 6);
    cpu.ebx = cpu.eax;
    cpu.ecx = cpu.eax + 0x100;
    quarterWave(app, cpu, cpu.ch);
    cpu.edi = cpu.eax;
    cpu.eax = cpu.ebx;
    quarterWave(app, cpu, cpu.ah);
    cpu.eax = 0 - cpu.eax;
    cpu.eax = reg32(sreg32(cpu.eax) >> 2);
    cpu.esi = reg32(sreg32(cpu.esi) >> 9);
    cpu.eax = reg32(sreg32(cpu.eax) * sreg32(cpu.esi));
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x15);
    cpu.eax += cpu.edi;
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace load
}  // namespace nfs3hp
