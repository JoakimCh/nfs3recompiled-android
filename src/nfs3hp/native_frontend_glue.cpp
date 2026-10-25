#include "native_guest.h"

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <utility>

/* What the main menu calls of the game's own: a race started or the game
 * left, the HUD's art, the attract mode's movies, the lists' keys.
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (FRONTEND_GLUE_NATIVES), and the generated code calls it by name.
 * tools/game_checks holds each against its generated code.
 *
 * The menus' widgets.  An item of a screen (188 bytes, the table at
 * 0x604ee0) is a button or a list or a slider: its x and y words at 6 and 8,
 * its codelink at 0x10, its nextmenu at 0x40; a button's listname at 0x58 and
 * its handler at 0x64; a list's name at 0x64, whether it is open (0x40), its
 * box (y, x, width, height words from 0x1a), the line chosen (0x56), the
 * lines shown at once (0x58, 0x5a) and the first and last shown (0x5c,
 * 0x5e); a slider's kind (0x42), the function its moves go to (0x78).  The
 * lists' table at 0x5563e8 (0x14 bytes a list: its name, its lines -- the
 * language's text numbers, words to a 0 --, which of them may be chosen,
 * and where the one chosen is kept, at 0x10) is looked up by name.  A
 * button's Enter on a listname steps its list to the next line that may be
 * chosen; on "racenow" it starts the race (6), or over a network says this
 * machine is ready (0x6fd508) -- the host once every machine is (0x79f5f8,
 * 0x60 a player); on "exitprogram" it leaves the game (10).  A list's keys
 * move its line by one, by a page, open it or close it.
 *
 * The menus' text: the font chosen, a text placed by its alignment (1 and 4
 * right, 2 and 5 centred; past 2 with a shadow in colour 8), drawn by the 3D
 * card's font in a race's pause screens (0x559234), by the 2D screen's
 * otherwise; the mouse read and put on the 640 by 480 screen the menus are
 * laid out on.  The HUD's art, hud.fsh, is the language's (GeHud.fsh ...)
 * and kept loaded at 0x55922c while its name is the one before (0x662850).
 *
 * The attract mode: after 0x1400 ticks of the clock (0x79c1a4) with the
 * mouse still and no dialog up, the music stops and the next of titleav.mad,
 * demoav1-3.mad plays from the movies' folder (0x7a32b4), unless movies are
 * off (0x7a1fdc); the keys flushed around it.  And the keyboard's ring
 * (0x7f6fe0, its read and write indexes and size at 0x7f7474, 0x7f747c,
 * 0x7f7480, under the lock at 0x7f7478) taken a key at a time; the font's
 * quads drawn and those of a later frame kept (0x49be40); the network's
 * locks freed; the controls' bindings that are digital noted.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, strings copied two bytes a turn
 * and measured with repne scasb.  The switches go by the targets nfs3.exe's
 * tables hold (0x44ac7c, 0x46c930, 0x46c990, 0x46cac8, 0x4961f0).  Windows'
 * functions are called through their imports' slots, every function of the
 * game's that is not this file's -- and those of this file's that the checks
 * stand in for, for the other files' natives -- by address. */
namespace nfs3hp
{
namespace frontend
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg16;
using x86::reg32;
using x86::reg8;
using x86::sreg16;
using x86::sreg32;

// The menus.
constexpr reg32 kInRace = 0x559234;           // the menus are a race's pause screens
constexpr reg32 kTextColour = 0x561b34, kScreenTextColour = 0x559434;
constexpr reg32 kLanguage = 0x6fbb4c;         // 1 to 5: German, French, Spanish, Italian, Swedish
constexpr reg32 kLists = 0x5563e8, kListLines = 0x5563ec, kListAllowed = 0x5563f0;
constexpr reg32 kListChosen = 0x5563f8, kListBytes = 0x14;
constexpr reg32 kListNotFound = 0x5389fc;     // "list not found: %s\n"
constexpr reg32 kRaceNow = 0x53a9cc, kExitProgram = 0x53a9e4;
constexpr reg32 kNetworkRace = 0x7a22e0, kNetworkHost = 0x7a22da, kNetworkReady = 0x6fd508;
constexpr reg32 kNetworkPlayers = 0x7a2274;   // the word at 0x7a2276 how many
constexpr reg32 kNetworkPlayerReady = 0x79f5f8, kNetworkPlayerBytes = 0x60;
constexpr reg32 kPlayers = 0x6fd3b8;          // 3: the list's box wider
constexpr reg32 kMouseX = 0x55e5e4, kMouseY = 0x55e5e8, kMouseClick = 0x55e5ec;
constexpr reg32 kMouseButtons = 0x55e5f4, kMouseWheel = 0x55e5f8;
constexpr reg32 kSliderFlags = 0x55eb2e;      // 0x20 a demo's command line, 0x10 ...
// The HUD's art.
constexpr reg32 kHud = 0x539004;              // "hud.fsh"
constexpr reg32 kLanguageHuds[] = {0x53900c, 0x539018, 0x539024, 0x539030, 0x53903c};
constexpr reg32 kHudShapes = 0x55922c, kHudName = 0x662850;
// The dimmed background's shades.
constexpr reg32 kShadeFull = 0x791b50, kShadeMost = 0x791b54, kShadeLess = 0x791b4c;
constexpr reg32 kSixTenths = 0x5395e0;        // double 0.6
// The controls.
constexpr reg32 kGameMode = 0x6fd3b0;         // 1: two players on one screen
constexpr reg32 kControllers = 0x6fc970;      // 0x88 bytes each, the first byte's 4 a game pad
constexpr reg32 kFirstDigital = 0x6fd2dc, kSecondDigital = 0x6fd348;
// The attract mode and the movies.
constexpr reg32 kMoviesOff = 0x7a1fdc, kMovieFolder = 0x7a32b4, kProcessorSpeed = 0x5652a4;
constexpr reg32 kSlowProcessor = 0x7ed6b40, kFastProcessor = 0xbebc200;   // 133 and 200 MHz
constexpr reg32 kClock = 0x79c1a4, kAttractSince = 0x55e548, kAttractMovie = 0x55e54c;
constexpr reg32 kMouseBeforeX = 0x55e550, kMouseBeforeY = 0x55e554;
constexpr reg32 kAttractOff = 0x6fbb54, kMusicVolume = 0x6fbbe8, kAttractTicks = 0x1400;
constexpr reg32 kMovies[] = {0x53beac, 0x53beb8, 0x53bec4, 0x53bed0};   // titleav, demoav1-3.mad
// The network's locks.
constexpr reg32 kNetworkLock = 0x55e5b8, kNetworkLock2 = 0x55ecb4, kNetworkLock3 = 0x55ecb8;
constexpr reg32 kNetworkRecord = 0x79f918;
// The keyboard's ring.
constexpr reg32 kKeyRing = 0x7f6fe0, kKeyRead = 0x7f7474, kKeyLock = 0x7f7478;
constexpr reg32 kKeyWrite = 0x7f747c, kKeyRingSize = 0x7f7480;
// What is called by address.
constexpr reg32 kEnterCriticalSection = 0x5344b8, kLeaveCriticalSection = 0x534588;
constexpr reg32 kMusicStreamMake = 0x410330, kMusicStart = 0x4104f0, kMusicStop = 0x4109d0;
constexpr reg32 kMusicStreamEnd = 0x410aa0, kMenuEffect = 0x4181d0, kTrace = 0x42d500;
constexpr reg32 kSetRenderState = 0x431900, kReadMouse = 0x435310;
constexpr reg32 kCodelinkMatches = 0x4429c0, kDialogShown = 0x4438b0;
constexpr reg32 kToScreenX = 0x451400, kToScreenY = 0x451440, kTextWidth = 0x452020;
constexpr reg32 kSelectFont = 0x452100, kDrawList = 0x4613e0;
constexpr reg32 kSliderSetSingle = 0x469480, kSliderSingle = 0x469520, kSliderDrawSingle = 0x469680;
constexpr reg32 kSliderHighlightSingle = 0x46a5f0, kSliderSetRange = 0x46add0, kSliderRange = 0x46afd0;
constexpr reg32 kSliderDrawRange = 0x46b3a0, kSliderHighlightRange = 0x46c320;
constexpr reg32 kLoadQfs = 0x4956f0, kPlayMovieFile = 0x495bc0, kSetPointer = 0x49bfc0;
constexpr reg32 kNetworkSlot = 0x4a6690, kViewport = 0x4beb80, kQuadIndices = 0x4c1e20;
constexpr reg32 kDrawText = 0x4d1000, kFlushText = 0x4d1340, kTextScale = 0x4d1390;
constexpr reg32 kLanguageText = 0x4d1850, kDrawQuads = 0x4d5840, kClearBuffers = 0x4d5d30;
constexpr reg32 kClearBuffersReset = 0x4d5d70, kScreenText = 0x4da4a0, kFillZero = 0x4e070c;
constexpr reg32 kStrstr = 0x4e0820, kFileExists = 0x4e0e60, kFree = 0x4e1890;
constexpr reg32 kMemmove = 0x4ea4f0, kFreeLock = 0x4eb360, kStrcmp = 0x4ee310;
constexpr reg32 kKeyCharacter = 0x4f0010, kWaitForKey = 0x4f0120, kFlushKeys = 0x4f0240;
// This file's that the checks stand in for: by address too.
constexpr reg32 kFindList = 0x442c80;

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

reg16 half(win32::WinApplication* app, reg32 address)
{
    return app->getMemory<reg16>(address);
}

void putHalf(win32::WinApplication* app, reg32 address, reg16 value)
{
    app->getMemory<reg16>(address) = value;
}

/* mov r, [address]; sar r, 0x10: the word at address + 2, signed. */
reg32 high(win32::WinApplication* app, reg32 address)
{
    return reg32(sreg32(at(app, address)) >> 16);
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

/* push ebp, mov ebp, esp after the registers named, and sub esp, `locals`;
 * mov esp, ebp, pop ebp, the registers popped and ret the other way. */
void enter(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 locals)
{
    for (reg32* r : saved)
        push(app, cpu, *r);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= locals;
}

void leave(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved)
{
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    for (auto r = std::rbegin(saved); r != std::rend(saved); ++r)
        **r = pop(app, cpu);
    cpu.esp += 4;
}

/* Two bytes a turn from esi to edi to the string's end: esi and al as the
 * copy leaves them, edi past what it wrote. */
void copyPairs(win32::WinApplication* app, x86::CPU& cpu)
{
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
}

/* push edi; the string at esi copied to edi; pop edi. */
void copyString(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    copyPairs(app, cpu);
    cpu.edi = pop(app, cpu);
}

/* cwde: ax sign-extended into eax. */
void cwde(x86::CPU& cpu)
{
    cpu.eax = reg32(sreg32(sreg16(cpu.ax)));
}

/* fnstsw ax; sahf. */
void statusToFlags(x86::CPU& cpu)
{
    cpu.ax = cpu.fpu.status.word;
    cpu.flags.lo = reg8(0x02 | (cpu.ah & 0xd7));
}

}  // namespace

void bindingIsDigital(win32::WinApplication* app, x86::CPU& cpu);
void noteDigitalControls(win32::WinApplication* app, x86::CPU& cpu);
void listAllowed(win32::WinApplication* app, x86::CPU& cpu);
void listLength(win32::WinApplication* app, x86::CPU& cpu);
void findList(win32::WinApplication* app, x86::CPU& cpu);
void loadShapes(win32::WinApplication* app, x86::CPU& cpu);
void setTextColour(win32::WinApplication* app, x86::CPU& cpu);
void screenToMenuX(win32::WinApplication* app, x86::CPU& cpu);
void screenToMenuY(win32::WinApplication* app, x86::CPU& cpu);
void readMenuMouse(win32::WinApplication* app, x86::CPU& cpu);
void dimBackground(win32::WinApplication* app, x86::CPU& cpu);
void drawTextAt(win32::WinApplication* app, x86::CPU& cpu);
void drawMenuText(win32::WinApplication* app, x86::CPU& cpu);
void buttonKey(win32::WinApplication* app, x86::CPU& cpu);
void listKey(win32::WinApplication* app, x86::CPU& cpu);
void layoutList(win32::WinApplication* app, x86::CPU& cpu);
void sliderSetValue(win32::WinApplication* app, x86::CPU& cpu);
void sliderValue(win32::WinApplication* app, x86::CPU& cpu);
void sliderSetOnMove(win32::WinApplication* app, x86::CPU& cpu);
void sliderDraw(win32::WinApplication* app, x86::CPU& cpu);
void sliderSetColour(win32::WinApplication* app, x86::CPU& cpu);
void playMovie(win32::WinApplication* app, x86::CPU& cpu);
void resetAttractTimer(win32::WinApplication* app, x86::CPU& cpu);
void attractMode(win32::WinApplication* app, x86::CPU& cpu);
void freeNetworkLocks(win32::WinApplication* app, x86::CPU& cpu);
void allPlayersReady(win32::WinApplication* app, x86::CPU& cpu);
void flushQuads(win32::WinApplication* app, x86::CPU& cpu);
void mouseKey(win32::WinApplication* app, x86::CPU& cpu);
void pointerInBox(win32::WinApplication* app, x86::CPU& cpu);
void nextKey(win32::WinApplication* app, x86::CPU& cpu);

/* 0x43c000: whether binding eax is digital: 1 unless it is a controller's
 * (its low byte 1), then whether that controller (its top four bits) is a
 * game pad (4 in its record's first byte). */
void bindingIsDigital(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.edx <<= 24;
    cpu.edx = reg32(sreg32(cpu.edx) >> 24);
    if (cpu.edx != 1)
        cpu.eax = 1;
    else
    {
        cpu.eax >>= 28;
        cpu.edx = cpu.eax;
        cpu.eax <<= 4;
        cpu.eax += cpu.edx;
        cpu.eax = (byte(app, cpu.eax * 8 + kControllers) & 4) != 0 ? 1 : 0;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x43c040: the game mode's control set (0x4904d0) looked at: whether its
 * steering, throttle and brake are digital (0x6fd2dc on), and the second
 * player's (0x6fd348 on) with two on one screen. */
void noteDigitalControls(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kGameMode);
    if (!byAddress(app, cpu, 0x4904d0))
        return;
    cpu.ebx = at(app, kGameMode);
    cpu.edx = cpu.eax;
    cpu.ecx = cpu.eax;
    if (cpu.ebx == 1)
    {
        for (reg32 i = 0; i < 3; ++i)
        {
            cpu.eax = at(app, cpu.edx + 0x38 + 4 * i);
            if (!direct(app, cpu, bindingIsDigital))
                return;
            put(app, kSecondDigital + 4 * i, cpu.eax);
        }
    }
    for (reg32 i = 0; i < 3; ++i)
    {
        cpu.eax = at(app, cpu.ecx + 4 + 4 * i);
        if (!direct(app, cpu, bindingIsDigital))
            return;
        put(app, kFirstDigital + 4 * i, cpu.eax);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* The lists' table looked through for the name at ecx, ebx counting from 0:
 * up to the entry whose name it is (strcmp 0), or the end (a name 0).  eax
 * left the entry's offset (ebx times 0x14); false when the game stopped. */
bool lookUpList(win32::WinApplication* app, x86::CPU& cpu)
{
    for (;;)
    {
        cpu.eax = cpu.ebx * 4;
        cpu.eax += cpu.ebx;
        cpu.eax <<= 2;
        cpu.edx = at(app, cpu.eax + kLists);
        if (cpu.edx == 0)
            break;
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kStrcmp))
            return false;
        if (cpu.eax == 0)
            break;
        ++cpu.ebx;
    }
    cpu.eax = cpu.ebx * 4;
    cpu.eax += cpu.ebx;
    cpu.eax <<= 2;
    return true;
}

}  // namespace

/* 0x442bf0: which lines of the list named eax may be chosen (a word each,
 * nonzero: it may), or 0 -- no name, no such list. */
void listAllowed(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.ebx = 0;
    if (cpu.eax != 0)
    {
        if (!lookUpList(app, cpu))
            return;
        if (at(app, cpu.eax + kLists) != 0)
            cpu.eax = at(app, cpu.eax + kListAllowed);
        else
            cpu.eax = 0;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x442c50: how many lines the list named eax has (findList's, to its 0). */
void listLength(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.edx}, 4);
    cpu.edx = cpu.ebp - 4;
    if (!byAddress(app, cpu, kFindList))
        return;
    cpu.ecx = cpu.eax;
    cpu.eax = 0;
    while (half(app, cpu.ecx + cpu.eax * 2) != 0)
        ++cpu.eax;
    leave(app, cpu, {&cpu.ecx, &cpu.edx});
}

/* 0x442c80: the lines of the list named eax (the language's text numbers,
 * words to a 0), where the one chosen is kept to [edx]; not found, "list not
 * found: %s" traced, a key waited for (0x4f0120), and 0. */
void findList(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.ebx = 0;
    if (cpu.eax != 0)
    {
        if (!lookUpList(app, cpu))
            return;
        if (at(app, cpu.eax + kLists) != 0)
        {
            cpu.edx = at(app, cpu.eax + kListChosen);
            put(app, cpu.esi, cpu.edx);
            cpu.eax = at(app, cpu.eax + kListLines);
        }
        else
        {
            push(app, cpu, cpu.ecx);
            push(app, cpu, kListNotFound);
            if (!byAddress(app, cpu, kTrace))
                return;
            cpu.esp += 8;
            if (!byAddress(app, cpu, kWaitForKey))
                return;
            cpu.eax = 0;
        }
    }
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x44ac90: the shapes of the .fsh named eax loaded (0x4956f0) and kept at
 * 0x55922c -- hud.fsh's name turned into the language's in place first --
 * unless they are already, by that name (0x662850), freeing those before.
 * eax left them. */
void loadShapes(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.edx = kHud;
    if (!byAddress(app, cpu, kStrstr))
        return;
    cpu.edi = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.edx = at(app, kLanguage);
        --cpu.edx;
        if (cpu.edx <= 4)
        {
            // The table at 0x44ac7c: 0x44acbc, 0x44acc5, 0x44accc, 0x44acd3, 0x44acda.
            cpu.esi = kLanguageHuds[cpu.edx];
            if (cpu.edx == 0)
                cpu.edi = cpu.eax;
            copyString(app, cpu);
        }
    }
    bool load = true;
    if (at(app, kHudShapes) != 0)
    {
        cpu.edx = kHudName;
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kStrcmp))
            return;
        if (cpu.eax == 0)
            load = false;
        else
        {
            cpu.eax = at(app, kHudShapes);
            if (!byAddress(app, cpu, kFree))
                return;
        }
    }
    if (load)
    {
        cpu.edx = 0x10;
        cpu.eax = cpu.ecx;
        cpu.edi = kHudName;
        if (!byAddress(app, cpu, kLoadQfs))
            return;
        cpu.esi = cpu.ecx;
        put(app, kHudShapes, cpu.eax);
        copyString(app, cpu);
    }
    cpu.eax = at(app, kHudShapes);
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4513c0: the menus' text's colour, eax: the 3D card's font's in a race's
 * pause screens (0x561b34), the 2D screen's (0x559434) otherwise. */
void setTextColour(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    put(app, at(app, kInRace) != 0 ? kTextColour : kScreenTextColour, cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

namespace
{

/* idiv ecx after mov edx, esi; mov eax, esi; sar edx, 0x1f. */
void divideEsi(x86::CPU& cpu)
{
    cpu.edx = cpu.esi;
    cpu.eax = cpu.esi;
    cpu.edx = reg32(sreg32(cpu.edx) >> 31);
    const std::int64_t dividend = std::int64_t(sreg32(cpu.eax));
    cpu.eax = reg32(sreg32(dividend / sreg32(cpu.ecx)));
    cpu.edx = reg32(sreg32(dividend % sreg32(cpu.ecx)));
}

}  // namespace

/* 0x451480: x eax on the screen's own, on the 640 wide screen of the menus:
 * times 640 over the viewport's width. */
void screenToMenuX(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0x10);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.ecx = ebp - 0xc;
    cpu.ebx = ebp - 0x10;
    cpu.edx = ebp - 4;
    cpu.eax = ebp - 8;
    if (!byAddress(app, cpu, kViewport))
        return;
    cpu.eax = cpu.esi;
    cpu.esi <<= 2;
    cpu.esi += cpu.eax;
    cpu.esi <<= 7;
    cpu.ecx = at(app, ebp - 0x10);
    divideEsi(cpu);
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
}

/* 0x4514c0: y eax on the screen's own, on the 480 high screen of the menus:
 * times 480 over the viewport's height. */
void screenToMenuY(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0x10);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.ecx = ebp - 0xc;
    cpu.ebx = ebp - 0x10;
    cpu.edx = ebp - 4;
    cpu.eax = ebp - 8;
    cpu.esi <<= 5;
    if (!byAddress(app, cpu, kViewport))
        return;
    cpu.eax = cpu.esi;
    cpu.esi <<= 4;
    cpu.esi -= cpu.eax;
    cpu.ecx = at(app, ebp - 0xc);
    divideEsi(cpu);
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi});
}

/* 0x451500: the mouse read (0x435310: the buttons to [eax], x to [edx], y to
 * [ebx], the wheel to [ecx]), x and y put on the menus' 640 by 480 screen in
 * a race's pause screens. */
void readMenuMouse(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edi = cpu.edx;
    cpu.esi = cpu.ebx;
    if (!byAddress(app, cpu, kReadMouse))
        return;
    if (at(app, kInRace) != 0)
    {
        cpu.eax = at(app, cpu.edi);
        if (!direct(app, cpu, screenToMenuX))
            return;
        put(app, cpu.edi, cpu.eax);
        cpu.eax = at(app, cpu.esi);
        if (!direct(app, cpu, screenToMenuY))
            return;
        put(app, cpu.esi, cpu.eax);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x451530 (a float on the stack): the screen behind the menus dimmed by it
 * (0x4d1390) -- in a race's pause screens by one of three shades instead:
 * 1 or more [0x791b50], 0.6 or more [0x791b54], less [0x791b4c]. */
void dimBackground(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {}, 8);
    const reg32 ebp = cpu.ebp;
    if (at(app, kInRace) != 0)
    {
        cpu.fpu.push(x86::Float(app->getMemory<float>(ebp + 8)));      // fld dword ptr [ebp + 8]
        cpu.fpu.push(1.0);                                              // fld1
        std::swap(cpu.fpu.st(0), cpu.fpu.st(1));                        // fxch st(1)
        app->getMemory<double>(ebp - 8) = double(cpu.fpu.pop());        // fstp qword ptr [ebp - 8]
        cpu.fpu.compare(cpu.fpu.st(0), x86::Float(app->getMemory<double>(ebp - 8)));
        cpu.fpu.pop();                                                  // fcomp
        statusToFlags(cpu);
        if (!cpu.flags.cf && !cpu.flags.zf)                             // ja: 1 above it
        {
            cpu.fpu.push(x86::Float(app->getMemory<double>(ebp - 8)));
            cpu.fpu.compare(cpu.fpu.st(0), x86::Float(app->getMemory<double>(kSixTenths)));
            cpu.fpu.pop();
            statusToFlags(cpu);
            cpu.eax = at(app, cpu.flags.cf ? kShadeLess : kShadeMost);
        }
        else
            cpu.eax = at(app, kShadeFull);
        put(app, ebp + 8, cpu.eax);
    }
    push(app, cpu, at(app, ebp + 8));
    if (!byAddress(app, cpu, kTextScale))
        return;
    cpu.fpu.pop();                                                      // fstp st(0)
    leave(app, cpu, {});
    cpu.esp += 4;
}

/* 0x451590: text eax drawn at edx, ebx of the menus' screen: by the 3D
 * card's font (0x4d1000) at its place on the screen's own in a race's pause
 * screens, by the 2D screen's (0x4da4a0) otherwise. */
void drawTextAt(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.edx;
    if (at(app, kInRace) != 0)
    {
        if (!byAddress(app, cpu, kToScreenX))
            return;
        cpu.edx = cpu.eax;
        cpu.eax = cpu.ebx;
        if (!byAddress(app, cpu, kToScreenY))
            return;
        cpu.ebx = cpu.eax;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kDrawText))
            return;
        cpu.fpu.pop();                                                  // fstp st(0)
        if (!byAddress(app, cpu, kFlushText))
            return;
    }
    else
    {
        cpu.edx = cpu.eax;
        cpu.ecx = 0;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kScreenText))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x452190 (stdcall 8): text eax (none: nothing) drawn in font ecx at edx,
 * ebx -- its right at x with the stack's first word 1 or 4, its middle with
 * 2 or 5; past 2 with a shadow in colour 8 a pixel down and right first --
 * in the colour of the stack's second word. */
void drawMenuText(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    put(app, ebp - 4, cpu.eax);
    cpu.esi = cpu.edx;
    cpu.edi = cpu.ebx;
    cpu.ebx = at(app, ebp + 0x10);
    cpu.edx = cpu.ecx;
    if (cpu.eax != 0)
    {
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kSelectFont))
            return;
        cpu.ecx = at(app, ebp - 4);
        if (cpu.ebx == 1 || cpu.ebx == 4)
        {
            cpu.eax = cpu.ecx;
            if (!byAddress(app, cpu, kTextWidth))
                return;
            cpu.esi -= cpu.eax;
        }
        else if (cpu.ebx == 2 || cpu.ebx == 5)
        {
            cpu.eax = cpu.ecx;
            if (!byAddress(app, cpu, kTextWidth))
                return;
            cpu.edx = cpu.eax;
            cpu.edx = reg32(sreg32(cpu.edx) >> 31);
            cpu.eax -= cpu.edx;
            cpu.eax = reg32(sreg32(cpu.eax) >> 1);
            cpu.esi -= cpu.eax;
        }
        if (sreg32(cpu.ebx) > 2)
        {
            cpu.eax = 8;
            if (!direct(app, cpu, setTextColour))
                return;
            cpu.ebx = cpu.edi + 1;
            cpu.edx = cpu.esi + 1;
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, drawTextAt))
                return;
        }
        cpu.eax = at(app, ebp + 0x14);
        if (!direct(app, cpu, setTextColour))
            return;
        cpu.ebx = cpu.edi;
        cpu.edx = cpu.esi;
        cpu.eax = cpu.ecx;
        if (!direct(app, cpu, drawTextAt))
            return;
    }
    leave(app, cpu, {&cpu.esi, &cpu.edi});
    cpu.esp += 8;
}

/* 0x461270: key bx on button eax.  With a listname (+0x58), Enter steps its
 * list to the next line that may be chosen, wrapping at its end (none but
 * the one: it stays), the list redrawn (0x4613e0) if the button is of kind
 * 0xf and its handler (+0x64) called, 2.  Otherwise Enter calls its handler
 * (+0x64) -- its answer -- or on "racenow" starts the race (6), over a
 * network this machine ready or not (0x6fd508; the host once every machine
 * is), 0; on "exitprogram" 10; with a nextmenu 5; else 3.  Other keys 0. */
void buttonKey(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    const auto done = [&] {
        cpu.eax = cpu.ebx;
        leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
    };
    cpu.ecx = cpu.eax;
    cpu.edi = cpu.ebx;
    cpu.esi = cpu.eax;
    cpu.edx = at(app, cpu.eax + 0x58);
    cpu.ebx = 0;
    bool handler = false;
    if (cpu.edx == 0)
    {
        if (cpu.di != 0xd)
            return done();
        if (at(app, cpu.eax + 0x64) != 0)
            handler = true;
        else
        {
            cpu.edx = kRaceNow;
            cpu.eax = at(app, cpu.eax + 0x10);
            if (!byAddress(app, cpu, kCodelinkMatches))
                return;
            if (cpu.eax != 0)
            {
                if (at(app, kNetworkRace) == 0)
                {
                    cpu.ebx = 6;
                    return done();
                }
                if (half(app, kNetworkHost) != 0)
                {
                    if (!direct(app, cpu, allPlayersReady))
                        return;
                    if (cpu.eax != 0)
                        put(app, kNetworkReady, 1);
                    return done();
                }
                cpu.eax = at(app, kNetworkReady) == 0 ? 1 : 0;
                put(app, kNetworkReady, cpu.eax);
                return done();
            }
            cpu.edx = kExitProgram;
            cpu.eax = at(app, cpu.ecx + 0x10);
            if (!byAddress(app, cpu, kCodelinkMatches))
                return;
            cpu.ebx = cpu.eax != 0 ? 0xa : at(app, cpu.ecx + 0x40) != 0 ? 5 : 3;
            return done();
        }
    }
    else
    {
        cpu.eax = cpu.edx;
        cpu.edx = ebp - 0x10;
        if (!byAddress(app, cpu, kFindList))
            return;
        put(app, ebp - 4, cpu.eax);
        cpu.eax = at(app, cpu.ecx + 0x58);
        if (!direct(app, cpu, listAllowed))
            return;
        cpu.edx = cpu.eax;
        if (cpu.di != 0xd)
            return done();
        cpu.eax = at(app, ebp - 0x10);
        cpu.eax = at(app, cpu.eax);
        cpu.ebx = 2;
        put(app, ebp - 8, cpu.eax);
        for (;;)
        {
            cpu.eax = at(app, ebp - 0x10);
            put(app, cpu.eax, at(app, cpu.eax) + 1);
            cpu.eax = at(app, ebp - 0x10);
            cpu.eax = at(app, cpu.eax);
            cpu.eax += cpu.eax;
            put(app, ebp - 0xc, cpu.eax);
            cpu.eax = at(app, ebp - 4);
            cpu.eax += at(app, ebp - 0xc);
            if (half(app, cpu.eax) == 0)
            {
                cpu.eax = at(app, ebp - 0x10);
                put(app, cpu.eax, 0);
            }
            if (cpu.edx == 0)
                break;
            cpu.eax = at(app, ebp - 0x10);
            cpu.eax = at(app, cpu.eax);
            cpu.eax += cpu.eax;
            cpu.di = half(app, cpu.edx + cpu.eax);
            if (cpu.di != 0)
                break;
            cpu.eax = at(app, ebp - 0x10);
            cpu.edi = at(app, ebp - 8);
            if (cpu.edi == at(app, cpu.eax))
                break;
        }
        if (half(app, cpu.esi + 0x48) != 0xf)
            return done();
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kDrawList))
            return;
        if (at(app, cpu.esi + 0x64) == 0)
            return done();
        cpu.eax = cpu.ecx;
        handler = true;
    }
    if (handler)
    {
        if (!byAddress(app, cpu, at(app, cpu.esi + 0x64)))
            return;
        cpu.ebx = cpu.eax;
    }
    done();
}

namespace
{

/* The list's pointer to its line chosen (0x4641ca on): x the middle of its
 * box, y its line's -- the chosen less the first shown, 16 a line, from the
 * box's top and 8 down; ebx its box's top. */
void pointAtLine(win32::WinApplication* app, x86::CPU& cpu, reg32 first)
{
    cpu.edx = high(app, cpu.ebx + 0x1c);
    cpu.eax = cpu.edx;
    cpu.edx = reg32(sreg32(cpu.edx) >> 31);
    cpu.eax -= cpu.edx;
    cpu.eax = reg32(sreg32(cpu.eax) >> 1);
    cpu.edx = high(app, cpu.ebx + 0x1a);
    if (first == 0x5a)
    {
        // 0x4641e0 and 0x46451b: the first shown read before the line.
        cpu.ecx = at(app, cpu.ebx + 0x5a);
        cpu.eax += cpu.edx;
        cpu.edx = at(app, cpu.ebx + 0x54);
        cpu.ecx = reg32(sreg32(cpu.ecx) >> 16);
        cpu.edx = reg32(sreg32(cpu.edx) >> 16);
        cpu.ebx = at(app, cpu.ebx + 0x18);
        cpu.edx -= cpu.ecx;
    }
    else
    {
        // 0x464376, 0x464436, 0x4644b0: the line read first.
        cpu.ecx = at(app, cpu.ebx + 0x54);
        cpu.eax += cpu.edx;
        cpu.edx = at(app, cpu.ebx + 0x5a);
        cpu.ecx = reg32(sreg32(cpu.ecx) >> 16);
        cpu.edx = reg32(sreg32(cpu.edx) >> 16);
        cpu.ecx -= cpu.edx;
        cpu.ebx = at(app, cpu.ebx + 0x18);
        cpu.edx = cpu.ecx;
    }
    cpu.ebx = reg32(sreg32(cpu.ebx) >> 16);
    cpu.edx <<= 4;
    cpu.edx += cpu.ebx;
    cpu.edx += 8;
}

}  // namespace

/* 0x463ff0: key si on list eax (its name at +0x64; none such: 0), 2 when it
 * took it.  Closed (+0x40 0): left and right step its line chosen back and
 * on, wrapping, to one that may be chosen (as many tries as it has lines);
 * Enter opens it -- the line chosen shown, the box laid out (0x464560), the
 * pointer put on the line -- with the menus' click (0x4181d0).  Open: up and
 * down move the line by one, page up and down by the lines shown, the lines
 * shown following it, the pointer on it; Enter on the box (0x49c1f0) on a
 * line that may be chosen chooses it and closes it, Escape or Enter off it
 * closes it, with the click.  Other keys 0, or 2 having opened or closed
 * it. */
void listKey(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    const auto done = [&] { leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}); };
    const auto doneWithEdi = [&] {
        cpu.eax = cpu.edi;
        done();
    };
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.ebx;
    cpu.edx = ebp - 0x10;
    cpu.ebx = cpu.eax;
    cpu.eax = at(app, cpu.eax + 0x64);
    if (!byAddress(app, cpu, kFindList))
        return;
    cpu.edx = cpu.eax;
    cpu.eax = at(app, cpu.ecx + 0x64);
    cpu.edi = 0;
    if (!direct(app, cpu, listAllowed))
        return;
    put(app, ebp - 8, cpu.eax);
    if (cpu.edx == 0)
    {
        cpu.eax = 0;
        return done();
    }
    cpu.eax = at(app, cpu.ecx + 0x64);
    if (!direct(app, cpu, listLength))
        return;
    cpu.edx = high(app, cpu.ecx + 0x56);
    put(app, ebp - 4, cpu.eax);
    put(app, ebp - 0xc, cpu.edx);
    cpu.edx = high(app, ebp - 6);
    cpu.eax = at(app, ebp - 4);
    if (sreg32(cpu.edx) < sreg32(at(app, ebp - 0xc)))
        cpu.edx = cpu.eax;
    else
        cpu.dx = half(app, cpu.ecx + 0x58);
    putHalf(app, cpu.ebx + 0x5a, cpu.dx);
    if (half(app, cpu.ebx + 0x40) == 0)
    {
        cpu.edx = cpu.esi;
        if (cpu.si < 0x4b00)
        {
            if (cpu.si != 0xd)
                return doneWithEdi();
            // 0x46416c: Enter opens it.
            cpu.edx = 0x7f;
            cpu.eax = 1;
            if (!byAddress(app, cpu, kMenuEffect))
                return;
            putHalf(app, cpu.ebx + 0x40, 1);
            cpu.eax = at(app, ebp - 0x10);
            cpu.ax = half(app, cpu.eax);
            putHalf(app, cpu.ebx + 0x56, cpu.ax);
            cpu.edx = high(app, cpu.ebx + 0x54);
            cpu.eax = high(app, cpu.ebx + 0x58);
            cpu.edi = 2;
            if (sreg32(cpu.edx) >= sreg32(cpu.eax))
            {
                cpu.dx = half(app, cpu.ebx + 0x5a);
                cpu.ax = half(app, cpu.ebx + 0x56);
                --cpu.edx;
                putHalf(app, cpu.ebx + 0x5e, cpu.ax);
                cpu.eax -= cpu.edx;
                putHalf(app, cpu.ebx + 0x5c, cpu.ax);
            }
            else
            {
                cpu.dx = half(app, cpu.ebx + 0x5a);
                putHalf(app, cpu.ebx + 0x5c, 0);
                --cpu.edx;
                cpu.ax = half(app, cpu.ebx + 0x5c);
                cpu.eax += cpu.edx;
                putHalf(app, cpu.ebx + 0x5e, cpu.ax);
            }
            cpu.eax = cpu.ecx;
            if (!direct(app, cpu, layoutList))
                return;
            pointAtLine(app, cpu, 0x5a);
            if (!byAddress(app, cpu, kSetPointer))
                return;
            return doneWithEdi();
        }
        if (cpu.si == 0x4b00)
        {
            // 0x464087: left, a line back.
            cpu.edx = at(app, ebp - 0x10);
            cpu.dx = half(app, cpu.edx);
            cpu.ecx = cpu.edx;
            putHalf(app, cpu.ebx + 0x56, cpu.dx);
            --cpu.ecx;
            cpu.edi = 2;
            putHalf(app, cpu.ebx + 0x56, cpu.cx);
            if (sreg16(cpu.cx) < 0)
            {
                cpu.edx = cpu.eax;
                --cpu.edx;
                putHalf(app, cpu.ebx + 0x56, cpu.dx);
            }
            if (at(app, ebp - 8) != 0)
            {
                cpu.edx = cpu.eax;
                for (;;)
                {
                    cpu.ecx = high(app, cpu.ebx + 0x54);
                    cpu.esi = at(app, ebp - 8);
                    cpu.ecx += cpu.ecx;
                    cpu.ecx += cpu.esi;
                    if (half(app, cpu.ecx) != 0)
                        break;
                    --cpu.edx;
                    if (cpu.dx == 0xffff)
                        break;
                    cpu.cx = half(app, cpu.ebx + 0x56);
                    --cpu.ecx;
                    putHalf(app, cpu.ebx + 0x56, cpu.cx);
                    if (sreg16(cpu.cx) >= 0)
                        continue;
                    cpu.ecx = cpu.eax;
                    --cpu.ecx;
                    putHalf(app, cpu.ebx + 0x56, cpu.cx);
                }
            }
            cpu.edx = high(app, cpu.ebx + 0x54);
            cpu.eax = at(app, ebp - 0x10);
            put(app, cpu.eax, cpu.edx);
            cpu.eax = cpu.edi;
            return done();
        }
        if (cpu.si != 0x4d00)
            return doneWithEdi();
        // 0x4640f6: right, a line on.
        cpu.edx = at(app, ebp - 0x10);
        cpu.dx = half(app, cpu.edx);
        putHalf(app, cpu.ebx + 0x56, cpu.dx);
        ++cpu.edx;
        putHalf(app, cpu.ebx + 0x56, cpu.dx);
        cpu.ecx = high(app, cpu.ebx + 0x54);
        cpu.edx = reg32(sreg32(sreg16(cpu.ax)));
        cpu.edi = 2;
        if (sreg32(cpu.ecx) >= sreg32(cpu.edx))
            putHalf(app, cpu.ebx + 0x56, 0);
        if (at(app, ebp - 8) != 0)
        {
            cpu.edx = cpu.eax;
            for (;;)
            {
                cpu.ecx = high(app, cpu.ebx + 0x54);
                cpu.esi = at(app, ebp - 8);
                cpu.ecx += cpu.ecx;
                cpu.ecx += cpu.esi;
                if (half(app, cpu.ecx) != 0)
                    break;
                --cpu.edx;
                if (cpu.dx == 0xffff)
                    break;
                putHalf(app, cpu.ebx + 0x56, reg16(half(app, cpu.ebx + 0x56) + 1));
                cpu.esi = high(app, cpu.ebx + 0x54);
                cpu.ecx = reg32(sreg32(sreg16(cpu.ax)));
                if (sreg32(cpu.esi) < sreg32(cpu.ecx))
                    continue;
                putHalf(app, cpu.ebx + 0x56, 0);
            }
        }
        cpu.eax = high(app, cpu.ebx + 0x54);
        cpu.edx = at(app, ebp - 0x10);
        put(app, cpu.edx, cpu.eax);
        cpu.eax = cpu.edi;
        return done();
    }
    // 0x464212: open.  Escape, or Enter off a line that may be chosen:
    // closed, with the click (0x4642c9).
    const auto close = [&] {
        cpu.edx = 0x7f;
        cpu.eax = 1;
        cpu.edi = 2;
        if (!byAddress(app, cpu, kMenuEffect))
            return;
        cpu.eax = cpu.ecx;
        putHalf(app, cpu.ebx + 0x40, 0);
        if (!direct(app, cpu, layoutList))
            return;
        doneWithEdi();
    };
    // The pointer put on the line, the result (0x464543).
    const auto pointThere = [&](reg32 first) {
        pointAtLine(app, cpu, first);
        if (!byAddress(app, cpu, kSetPointer))
            return;
        doneWithEdi();
    };
    if (cpu.si < 0x4800)
    {
        if (cpu.si < 0xd)
            return doneWithEdi();
        if (cpu.si != 0xd)
        {
            if (cpu.si == 0x1b)
                return close();
            return doneWithEdi();
        }
        // 0x46426f: Enter.
        cpu.eax = cpu.ebx + 0x1a;
        if (!direct(app, cpu, pointerInBox))
            return;
        if (cpu.eax == 0)
            return close();
        cpu.edi = at(app, ebp - 8);
        if (cpu.edi != 0)
        {
            cpu.eax = high(app, cpu.ebx + 0x54);
            cpu.eax += cpu.eax;
            cpu.eax += cpu.edi;
            if (half(app, cpu.eax) == 0)
                return close();
        }
        cpu.edx = 0x7f;
        cpu.eax = 1;
        if (!byAddress(app, cpu, kMenuEffect))
            return;
        putHalf(app, cpu.ebx + 0x40, 0);
        cpu.eax = high(app, cpu.ebx + 0x54);
        cpu.edx = at(app, ebp - 0x10);
        put(app, cpu.edx, cpu.eax);
        cpu.eax = cpu.ecx;
        cpu.edi = 2;
        if (!direct(app, cpu, layoutList))
            return;
        return doneWithEdi();
    }
    if (cpu.si == 0x4800)
    {
        // 0x464456: up a line, the lines shown up one with it above the first.
        cpu.cx = half(app, cpu.ebx + 0x56);
        --cpu.ecx;
        cpu.edi = 2;
        putHalf(app, cpu.ebx + 0x56, cpu.cx);
        if (sreg16(cpu.cx) < 0)
            cpu.eax = 0;
        else
        {
            cwde(cpu);
            cpu.edx = high(app, cpu.ebx + 0x54);
            --cpu.eax;
            if (!(sreg32(cpu.edx) > sreg32(cpu.eax)))
                cpu.eax = cpu.edx;
        }
        putHalf(app, cpu.ebx + 0x56, cpu.ax);
        cpu.edx = high(app, cpu.ebx + 0x54);
        cpu.eax = high(app, cpu.ebx + 0x5a);
        if (sreg32(cpu.edx) < sreg32(cpu.eax))
        {
            cpu.dx = half(app, cpu.ebx + 0x5c);
            cpu.ax = half(app, cpu.ebx + 0x5e);
            --cpu.edx;
            --cpu.eax;
            putHalf(app, cpu.ebx + 0x5c, cpu.dx);
            putHalf(app, cpu.ebx + 0x5e, cpu.ax);
        }
        return pointThere(0x54);
    }
    if (cpu.si < 0x5000)
    {
        if (cpu.si != 0x4900)
            return doneWithEdi();
        // 0x4642f3: page up, the lines shown up a page with it above the first.
        cpu.dx = half(app, cpu.ebx + 0x5a);
        cpu.cx = half(app, cpu.ebx + 0x56);
        cpu.ecx -= cpu.edx;
        cpu.edi = 2;
        putHalf(app, cpu.ebx + 0x56, cpu.cx);
        if (sreg16(cpu.cx) < 0)
            cpu.edx = 0;
        else
        {
            cpu.edx = reg32(sreg32(sreg16(cpu.ax)));
            cpu.ecx = high(app, cpu.ebx + 0x54);
            --cpu.edx;
            if (!(sreg32(cpu.ecx) > sreg32(cpu.edx)))
                cpu.edx = cpu.ecx;
        }
        putHalf(app, cpu.ebx + 0x56, cpu.dx);
        cpu.ecx = high(app, cpu.ebx + 0x54);
        cpu.edx = high(app, cpu.ebx + 0x5a);
        if (sreg32(cpu.ecx) < sreg32(cpu.edx))
        {
            cpu.cx = half(app, cpu.ebx + 0x5c);
            cpu.dx = half(app, cpu.ebx + 0x5a);
            cpu.ecx -= cpu.edx;
            putHalf(app, cpu.ebx + 0x5c, cpu.cx);
            if (sreg16(cpu.cx) < 0)
                cpu.eax = 0;
            else
            {
                cwde(cpu);
                cpu.edx = high(app, cpu.ebx + 0x5a);
                --cpu.eax;
                if (!(sreg32(cpu.edx) > sreg32(cpu.eax)))
                    cpu.eax = cpu.edx;
            }
            cpu.dx = half(app, cpu.ebx + 0x5a);
            --cpu.edx;
            putHalf(app, cpu.ebx + 0x5c, cpu.ax);
            cpu.eax += cpu.edx;
            putHalf(app, cpu.ebx + 0x5e, cpu.ax);
        }
        return pointThere(0x54);
    }
    if (cpu.si == 0x5000)
    {
        // 0x4644d0: down a line, the lines shown down one with it below the last.
        cpu.cx = half(app, cpu.ebx + 0x56);
        ++cpu.ecx;
        cpu.edi = 2;
        putHalf(app, cpu.ebx + 0x56, cpu.cx);
        if (sreg16(cpu.cx) < 0)
            cpu.edx = 0;
        else
        {
            cwde(cpu);
            cpu.edx = high(app, cpu.ebx + 0x54);
            --cpu.eax;
            if (sreg32(cpu.edx) > sreg32(cpu.eax))
                cpu.edx = cpu.eax;
        }
        putHalf(app, cpu.ebx + 0x56, cpu.dx);
        cpu.eax = high(app, cpu.ebx + 0x5c);
        cpu.edx = high(app, cpu.ebx + 0x54);
        if (sreg32(cpu.edx) > sreg32(cpu.eax))
        {
            cpu.dx = half(app, cpu.ebx + 0x5c);
            cpu.ax = half(app, cpu.ebx + 0x5e);
            ++cpu.edx;
            ++cpu.eax;
            putHalf(app, cpu.ebx + 0x5c, cpu.dx);
            putHalf(app, cpu.ebx + 0x5e, cpu.ax);
        }
        return pointThere(0x5a);
    }
    if (cpu.si != 0x5100)
        return doneWithEdi();
    // 0x464396: page down, the lines shown down a page with it below the last.
    cpu.dx = half(app, cpu.ebx + 0x5a);
    cpu.cx = half(app, cpu.ebx + 0x56);
    cpu.ecx += cpu.edx;
    cpu.edi = 2;
    putHalf(app, cpu.ebx + 0x56, cpu.cx);
    if (sreg16(cpu.cx) < 0)
        cpu.edx = 0;
    else
    {
        cpu.edx = reg32(sreg32(sreg16(cpu.ax)));
        cpu.ecx = high(app, cpu.ebx + 0x54);
        --cpu.edx;
        if (!(sreg32(cpu.ecx) > sreg32(cpu.edx)))
            cpu.edx = cpu.ecx;
    }
    putHalf(app, cpu.ebx + 0x56, cpu.dx);
    cpu.ecx = high(app, cpu.ebx + 0x54);
    cpu.edx = high(app, cpu.ebx + 0x5c);
    if (sreg32(cpu.ecx) > sreg32(cpu.edx))
    {
        cpu.cx = half(app, cpu.ebx + 0x5e);
        cpu.dx = half(app, cpu.ebx + 0x5a);
        cpu.ecx += cpu.edx;
        putHalf(app, cpu.ebx + 0x5e, cpu.cx);
        if (sreg16(cpu.cx) < 0)
            cpu.edx = 0;
        else
        {
            cpu.ecx = reg32(sreg32(sreg16(cpu.ax)));
            cpu.edx = high(app, cpu.ebx + 0x5c);
            --cpu.ecx;
            if (sreg32(cpu.edx) > sreg32(cpu.ecx))
                cpu.edx = cpu.ecx;
        }
        cpu.cx = half(app, cpu.ebx + 0x5a);
        --cpu.ecx;
        putHalf(app, cpu.ebx + 0x5e, cpu.dx);
        cpu.edx -= cpu.ecx;
        putHalf(app, cpu.ebx + 0x5c, cpu.dx);
        if (sreg16(cpu.dx) < 0)
            cpu.edx = 0;
        else
        {
            cwde(cpu);
            cpu.edx = high(app, cpu.ebx + 0x5a);
            --cpu.eax;
            if (sreg32(cpu.edx) > sreg32(cpu.eax))
                cpu.edx = cpu.eax;
        }
        putHalf(app, cpu.ebx + 0x5c, cpu.dx);
    }
    pointThere(0x54);
}

/* 0x464560: list eax's box laid out: open, as wide as its widest line
 * (0x28 at least) with its margins (0x23 for three players, 0xf else) and as
 * high as its lines shown, 16 a line, under or beside it (+0x52, +0x54);
 * closed (or without lines), the box of its line chosen. */
void layoutList(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 8);
    const reg32 ebp = cpu.ebp;
    cpu.edx = at(app, kPlayers);
    cpu.ecx = cpu.eax;
    cpu.edx = cpu.edx == 3 ? 0x23 : 0xf;
    put(app, ebp - 4, cpu.edx);
    cpu.eax = at(app, cpu.ecx + 0x64);
    cpu.edx = ebp - 8;
    if (!byAddress(app, cpu, kFindList))
        return;
    cpu.dx = half(app, cpu.ecx + 0x40);
    cpu.edi = cpu.eax;
    if (cpu.dx != 0 && cpu.eax != 0)
    {
        putHalf(app, cpu.ecx + 0x1e, 0x28);
        cpu.ebx = 0;
        for (;;)
        {
            cpu.eax = cpu.ebx + cpu.ebx;
            cpu.eax += cpu.edi;
            cpu.si = half(app, cpu.eax);
            if (cpu.si == 0)
                break;
            cpu.eax = reg32(sreg32(sreg16(cpu.si)));
            cpu.edx = 0x12;
            if (!byAddress(app, cpu, kLanguageText))
                return;
            if (!byAddress(app, cpu, kTextWidth))
                return;
            cpu.edx = high(app, cpu.ecx + 0x1c);
            cpu.esi = cpu.eax;
            if (sreg32(cpu.eax) > sreg32(cpu.edx))
                putHalf(app, cpu.ecx + 0x1e, cpu.ax);
            ++cpu.ebx;
        }
        cpu.eax = at(app, ebp - 4);
        cpu.di = half(app, cpu.ecx + 0x1e);
        cpu.eax += 5;
        cpu.edi += cpu.eax;
        cpu.ax = half(app, cpu.ecx + 0x5a);
        cpu.eax <<= 4;
        cpu.eax += 5;
        putHalf(app, cpu.ecx + 0x20, cpu.ax);
        cpu.ax = half(app, cpu.ecx + 0x52);
        putHalf(app, cpu.ecx + 0x1e, cpu.di);
        if (cpu.ax != 0)
        {
            cpu.dx = half(app, cpu.ecx + 0x20);
            cpu.ax = half(app, cpu.ecx + 8);
            cpu.eax -= cpu.edx;
            cpu.eax += 0xe;
            cpu.bx = half(app, cpu.ecx + 0x54);
            putHalf(app, cpu.ecx + 0x1a, cpu.ax);
            if (cpu.bx != 0)
            {
                cpu.dx = half(app, cpu.ecx + 6);
                cpu.ax = half(app, cpu.ecx + 0x1e);
                cpu.edx += 0xaa;
                cpu.edx -= cpu.eax;
                putHalf(app, cpu.ecx + 0x1c, cpu.dx);
            }
            else
            {
                cpu.ax = half(app, cpu.ecx + 6);
                cpu.dx = half(app, cpu.ecx + 0x1e);
                cpu.eax += 0xc8;
                cpu.eax -= cpu.edx;
                putHalf(app, cpu.ecx + 0x1c, cpu.ax);
            }
        }
        else
        {
            cpu.ax = half(app, cpu.ecx + 8);
            cpu.eax += 0x10;
            putHalf(app, cpu.ecx + 0x1a, cpu.ax);
            cpu.ax = half(app, cpu.ecx + 6);
            cpu.eax += 0x40;
            putHalf(app, cpu.ecx + 0x1c, cpu.ax);
        }
    }
    else
    {
        if (half(app, cpu.ecx + 0x52) != 0)
        {
            cpu.ax = half(app, cpu.ecx + 6);
            if (half(app, cpu.ecx + 0x54) == 0)
                cpu.eax += 0xa;
            putHalf(app, cpu.ecx + 0x1c, cpu.ax);
            putHalf(app, cpu.ecx + 0x1e, 0xcf);
            cpu.ax = half(app, cpu.ecx + 8);
            putHalf(app, cpu.ecx + 0x20, 0x13);
            cpu.eax += 0xc;
        }
        else
        {
            putHalf(app, cpu.ecx + 0x1e, 0x101);
            cpu.ax = half(app, cpu.ecx + 6);
            putHalf(app, cpu.ecx + 0x20, 0x1f);
            putHalf(app, cpu.ecx + 0x1c, cpu.ax);
            cpu.ax = half(app, cpu.ecx + 8);
        }
        putHalf(app, cpu.ecx + 0x1a, cpu.ax);
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x46c950 (stdcall 8): slider eax set to the stack's value -- a range's
 * (kind 2, +0x42) end of the stack's second word (0x46add0), none for kind
 * 1, a single one's (0x469480) else. */
void sliderSetValue(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const reg32 ebp = cpu.ebp;
    cpu.edx = cpu.eax;
    cpu.dx = half(app, cpu.eax + 0x42);
    // The table at 0x46c930: 0x46c97e, 0x46c988, 0x46c96d, 0x46c97e, 0x46c97e, 0x46c97e.
    if (cpu.dx <= 5)
        cpu.edx &= 0xffff;
    if (cpu.dx == 2)
    {
        cpu.edx = at(app, ebp + 0x10);
        push(app, cpu, cpu.edx);
        push(app, cpu, at(app, ebp + 0xc));
        if (!byAddress(app, cpu, kSliderSetRange))
            return;
    }
    else if (cpu.dx != 1)
    {
        push(app, cpu, 0);
        push(app, cpu, at(app, ebp + 0xc));
        if (!byAddress(app, cpu, kSliderSetSingle))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4 + 8;
}

/* 0x46c9b0: slider eax's value onto the x87's stack -- a range's (kind 2)
 * end edx (0x46afd0), 0 for kind 1, a single one's (0x469520) else -- as a
 * float. */
void sliderValue(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = cpu.eax;
    cpu.ebx = 0;
    cpu.cx = half(app, cpu.eax + 0x42);
    put(app, ebp - 4, cpu.ebx);
    // The table at 0x46c990: 0x46c9e0, 0x46c9ea, 0x46c9d6, 0x46c9e0, 0x46c9e0, 0x46c9e0.
    if (cpu.cx <= 5)
        cpu.ecx &= 0xffff;
    if (cpu.cx == 2)
    {
        if (!byAddress(app, cpu, kSliderRange))
            return;
        app->getMemory<float>(ebp - 4) = float(cpu.fpu.pop());
    }
    else if (cpu.cx != 1)
    {
        cpu.edx = 0;
        if (!byAddress(app, cpu, kSliderSingle))
            return;
        app->getMemory<float>(ebp - 4) = float(cpu.fpu.pop());
    }
    cpu.fpu.push(x86::Float(app->getMemory<float>(ebp - 4)));
    leave(app, cpu, {&cpu.ebx, &cpu.ecx});
}

/* 0x46cac0: the function slider eax's moves go to, edx (+0x78). */
void sliderSetOnMove(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    put(app, cpu.eax + 0x78, cpu.edx);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x46cae0: slider eax drawn, highlighted first if edx -- a range's (kind 2:
 * 0x46c320, 0x46b3a0), none for kind 1, a single one's (0x46a5f0, 0x469680)
 * else; greyed out (+4's bit 0) from a demo's command line (0x55eb2e). eax
 * left what the drawing answered, 0 for kind 1. */
void sliderDraw(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.ebx = 0;
    const reg8 flags = byte(app, kSliderFlags);
    const bool kept = ((flags & 0x20) && (byte(app, cpu.eax + 0x18) & 1))
                      || ((flags & 0x10) && half(app, cpu.ecx + 0x18) != 0);
    if (!kept && ((flags & 0x20) || (flags & 0x10)))
        putByte(app, cpu.ecx + 4, byte(app, cpu.ecx + 4) | 1);
    cpu.si = half(app, cpu.ecx + 0x42);
    // The table at 0x46cac8: 0x46cb4a, 0x46cb5c, 0x46cb36, 0x46cb4a, 0x46cb4a, 0x46cb4a.
    if (cpu.si <= 5)
        cpu.esi &= 0xffff;
    if (cpu.si == 2)
    {
        if (cpu.edx != 0 && !byAddress(app, cpu, kSliderHighlightRange))
            return;
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kSliderDrawRange))
            return;
        cpu.ebx = cpu.eax;
    }
    else if (cpu.si != 1)
    {
        if (cpu.edx != 0 && !byAddress(app, cpu, kSliderHighlightSingle))
            return;
        cpu.eax = cpu.ecx;
        if (!byAddress(app, cpu, kSliderDrawSingle))
            return;
        cpu.ebx = cpu.eax;
    }
    cpu.eax = cpu.ebx;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x46cca0: slider eax's bar's colours, bl and dl (+0x3e, +0x3f). */
void sliderSetColour(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    putByte(app, cpu.eax + 0x3e, cpu.bl);
    putByte(app, cpu.eax + 0x3f, cpu.dl);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4960e0: movie eax played from the movies' folder (0x7a32b4), when movies
 * are on and the file is there (0x4e0e60): the keys flushed (0x4f0240), the
 * buffers cleared, the music's stream ended; the movie (0x495bc0) at the
 * quality the processor's speed allows (1 under 133 MHz, 2 under 200, 3),
 * told the processor is slow under 133; the buffers cleared again, the keys
 * flushed, the music's stream made again.  1. */
void playMovie(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x100;
    cpu.ebp -= 0x82;
    const reg32 ebp = cpu.ebp;
    cpu.ecx = cpu.eax;
    cpu.edx = at(app, kMoviesOff);
    if (cpu.edx == 0)
    {
        cpu.esi = kMovieFolder;
        cpu.edi = ebp - 0x7e;
        copyString(app, cpu);
        // strcat: the name after the folder's.
        cpu.edi = ebp - 0x7e;
        cpu.esi = cpu.ecx;
        push(app, cpu, cpu.edi);
        cpu.ecx = 0;
        --cpu.ecx;
        cpu.al = 0;
        while (cpu.ecx != 0)
        {
            --cpu.ecx;
            const reg8 c = byte(app, cpu.edi);
            ++cpu.edi;
            if (c == cpu.al)
                break;
        }
        --cpu.edi;
        copyPairs(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.eax = ebp - 0x7e;
        if (!byAddress(app, cpu, kFileExists))
            return;
        if (cpu.eax != 0)
        {
            if (!byAddress(app, cpu, kFlushKeys) || !byAddress(app, cpu, kClearBuffers)
                || !byAddress(app, cpu, kMusicStreamEnd))
                return;
            cpu.ebx = at(app, kProcessorSpeed);
            put(app, ebp + 0x7e, cpu.edx);
            if (sreg32(cpu.ebx) < sreg32(kSlowProcessor))
                cpu.ecx = 1;
            else if (sreg32(cpu.ebx) < sreg32(kFastProcessor))
                cpu.ecx = 2;
            else
                cpu.ecx = 3;
            if (sreg32(at(app, kProcessorSpeed)) < sreg32(kSlowProcessor))
                put(app, ebp + 0x7e, 1);
            push(app, cpu, 1);
            cpu.edx = ebp + 0x7e;
            cpu.eax = ebp - 0x7e;
            cpu.ebx = 0;
            if (!byAddress(app, cpu, kPlayMovieFile) || !byAddress(app, cpu, kClearBuffersReset)
                || !byAddress(app, cpu, kFlushKeys) || !byAddress(app, cpu, kMusicStreamMake))
                return;
        }
    }
    cpu.eax = 1;
    cpu.esp = ebp + 0x82;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4961e0: the attract mode's wait started again, from the clock now. */
void resetAttractTimer(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kClock);
    put(app, kAttractSince, cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x496200: the main menu's attract mode, every pass: with movies on and it
 * not off (0x6fbb54), its wait started again while a dialog is up or as the
 * mouse moves (0); 0x1400 ticks on, the music stopped, the next of its four
 * movies played (0x55e54c, 0 to 3), the menus' tune started again, 1. */
void attractMode(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const auto done = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.esi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (at(app, kMoviesOff) != 0 || at(app, kAttractOff) != 0)
    {
        cpu.eax = 0;
        return done();
    }
    if (!byAddress(app, cpu, kDialogShown))
        return;
    if (cpu.al != 0 && !direct(app, cpu, resetAttractTimer))
        return;
    cpu.ebx = at(app, kMouseX);
    bool moved = cpu.ebx != at(app, kMouseBeforeX);
    if (!moved)
    {
        cpu.esi = at(app, kMouseY);
        moved = cpu.esi != at(app, kMouseBeforeY);
    }
    if (moved)
    {
        cpu.eax = at(app, kMouseX);
        put(app, kMouseBeforeX, cpu.eax);
        cpu.eax = at(app, kMouseY);
        put(app, kMouseBeforeY, cpu.eax);
        if (!direct(app, cpu, resetAttractTimer))
            return;
        cpu.eax = 0;
        return done();
    }
    cpu.eax = at(app, kClock);
    cpu.eax -= at(app, kAttractSince);
    if (sreg32(cpu.eax) < sreg32(kAttractTicks))
    {
        cpu.eax = 0;
        return done();
    }
    if (!byAddress(app, cpu, kMusicStop))
        return;
    cpu.eax = at(app, kAttractMovie);
    // The table at 0x4961f0: 0x4962a3, 0x4962aa, 0x4962b1, 0x4962b8.
    if (cpu.eax <= 3)
    {
        cpu.eax = kMovies[cpu.eax];
        if (!direct(app, cpu, playMovie))
            return;
    }
    cpu.eax = 0x16;
    cpu.edx = at(app, kMusicVolume);
    cpu.ebx = 0;
    if (!byAddress(app, cpu, kMusicStart))
        return;
    cpu.edx = at(app, kAttractMovie);
    ++cpu.edx;
    cpu.ecx = 4;
    cpu.eax = cpu.edx;
    cpu.edx = reg32(sreg32(cpu.edx) >> 31);
    const std::int64_t dividend = std::int64_t(sreg32(cpu.eax));
    cpu.eax = reg32(sreg32(dividend / 4));
    cpu.edx = reg32(sreg32(dividend % 4));
    put(app, kAttractMovie, cpu.edx);
    if (!direct(app, cpu, resetAttractTimer))
        return;
    cpu.eax = 1;
    done();
}

/* 0x49a4d0: the network's three locks freed (0x4eb360) and forgotten, the
 * record at 0x79f918 cleared. */
void freeNetworkLocks(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kNetworkLock);
    if (!byAddress(app, cpu, kFreeLock))
        return;
    cpu.edx = 0;
    cpu.eax = at(app, kNetworkLock2);
    put(app, kNetworkLock, cpu.edx);
    if (!byAddress(app, cpu, kFreeLock))
        return;
    cpu.eax = at(app, kNetworkLock3);
    put(app, kNetworkLock2, cpu.edx);
    if (!byAddress(app, cpu, kFreeLock))
        return;
    cpu.eax = kNetworkRecord;
    put(app, kNetworkLock3, cpu.edx);
    cpu.edx = kNetworkPlayerBytes;
    if (!byAddress(app, cpu, kFillZero))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x49ab60: 1 when in a network race of two machines or more every other
 * machine's player (0x4a6690) is ready (0x79f5f8, 0x60 a player); else 0. */
void allPlayersReady(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    const auto done = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.eax = 0;
    if (at(app, kNetworkRace) == 0 || sreg16(half(app, kNetworkPlayers + 2)) < 2)
        return done();
    cpu.edx = 1;
    for (;;)
    {
        cpu.eax = high(app, kNetworkPlayers);
        if (sreg32(cpu.edx) >= sreg32(cpu.eax))
            break;
        cpu.eax = reg32(sreg32(sreg16(cpu.dx)));
        if (!byAddress(app, cpu, kNetworkSlot))
            return;
        cwde(cpu);
        if (cpu.eax == 0xffffffff)
        {
            cpu.eax = 0;
            return done();
        }
        cpu.ecx = cpu.eax;
        cpu.eax <<= 2;
        cpu.eax -= cpu.ecx;
        cpu.eax <<= 5;
        if (byte(app, cpu.eax + kNetworkPlayerReady) == 0)
        {
            cpu.eax = 0;
            return done();
        }
        ++cpu.edx;
    }
    cpu.eax = 1;
    done();
}

/* 0x49be40: the font's quads of list eax drawn: its texture's state set
 * (0x431900), the quads (0x4d5840) and their indices (0x4c1e20); then those
 * of a later frame than the list's (a word at +0x20010 each four) kept --
 * the others taken out, those after moved down (0x4ea4f0) -- and the list's
 * frame 0xfff. */
void flushQuads(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = cpu.eax;
    cpu.edx = at(app, cpu.eax + 0xc);
    cpu.esi = 0;
    if (cpu.edx != 0)
    {
        cpu.edx = at(app, cpu.eax);
        cpu.eax = 1;
        if (!byAddress(app, cpu, kSetRenderState))
            return;
        cpu.eax = cpu.ecx;
        cpu.eax += 0x20010;
        cpu.edi = cpu.ecx + 0x10;
        put(app, ebp - 4, cpu.eax);
        cpu.edx = cpu.edi;
        cpu.eax = at(app, cpu.ecx + 0xc);
        cpu.ebx = at(app, ebp - 4);
        cpu.eax = reg32(sreg32(cpu.eax) >> 2);
        if (!byAddress(app, cpu, kDrawQuads))
            return;
        cpu.ebx = at(app, ebp - 4);
        cpu.eax = at(app, cpu.ecx + 0xc);
        cpu.edx = cpu.edi;
        cpu.eax = reg32(sreg32(cpu.eax) >> 2);
        if (!byAddress(app, cpu, kQuadIndices))
            return;
        for (;;)
        {
            cpu.ebx = at(app, cpu.ecx + 0xc);
            if (sreg32(cpu.esi) >= sreg32(cpu.ebx))
                break;
            cpu.eax = cpu.esi * 4;
            cpu.edx = cpu.ecx + cpu.eax;
            cpu.edi = at(app, cpu.ecx + 4);
            if (sreg32(cpu.edi) >= sreg32(at(app, cpu.edx + 0x20010)))
            {
                cpu.esi += 4;
                continue;
            }
            cpu.ebx -= cpu.esi;
            cpu.edx = cpu.ecx + 0x20010;
            cpu.ebx <<= 2;
            cpu.edx += cpu.eax;
            cpu.ebx -= 0x10;
            cpu.eax = cpu.edx + 0x10;
            if (!byAddress(app, cpu, kMemmove))
                return;
            put(app, cpu.ecx + 0xc, at(app, cpu.ecx + 0xc) - 4);
        }
        put(app, cpu.ecx + 4, 0xfff);
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x49c080: the mouse read into the menus' (0x55e5f4 its buttons, 0x55e5e4
 * and 0x55e5e8 the pointer, 0x55e5f8 the wheel) as a key: a button pressed,
 * the click forgotten (0x55e5ec) and Enter (0xd) for the left, Escape (0x1b)
 * for another; none, 0. */
void mouseKey(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = kMouseWheel;
    cpu.ebx = kMouseY;
    cpu.edx = kMouseX;
    cpu.eax = kMouseButtons;
    if (!direct(app, cpu, readMenuMouse))
        return;
    cpu.ah = byte(app, kMouseButtons);
    if ((cpu.ah & 0xf) != 0)
    {
        cpu.edx = 0;
        put(app, kMouseClick, cpu.edx);
        cpu.eax = (cpu.ah & 1) != 0 ? 0xd : 0x1b;
    }
    else
        cpu.eax = 0;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x49c1f0: whether the menus' pointer is inside box eax (y, x, width,
 * height, words), edges out. */
void pointerInBox(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    bool inside = false;
    cpu.edx = at(app, cpu.eax);
    cpu.ecx = at(app, kMouseX);
    cpu.edx = reg32(sreg32(cpu.edx) >> 16);
    if (sreg32(cpu.edx) < sreg32(cpu.ecx))
    {
        cpu.ecx = high(app, cpu.eax + 2);
        cpu.ebx = at(app, kMouseX);
        cpu.edx += cpu.ecx;
        if (sreg32(cpu.edx) > sreg32(cpu.ebx))
        {
            cpu.esi = at(app, kMouseY);
            cpu.edx = reg32(sreg32(sreg16(half(app, cpu.eax))));
            if (sreg32(cpu.edx) < sreg32(cpu.esi))
            {
                cpu.eax = high(app, cpu.eax + 4);
                cpu.eax += cpu.edx;
                inside = sreg32(cpu.eax) > sreg32(cpu.esi);
            }
        }
    }
    cpu.eax = inside ? 1 : 0;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4cc970: the next key off the keyboard's ring, under its lock: its scan
 * code in the high word, its character -- the ring's, or the scan code's
 * with the shifts of its low byte (0x4f0010) -- in the low; keys without one
 * passed over; none, 0. */
void nextKey(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.edx = at(app, kKeyLock);
    push(app, cpu, cpu.edx);
    cpu.esi = 0;
    cpu.ebx = 0;
    if (!windows(app, cpu, kEnterCriticalSection))
        return;
    for (;;)
    {
        cpu.ecx = at(app, kKeyWrite);
        cpu.eax = at(app, kKeyRead);
        if (cpu.eax == cpu.ecx || cpu.ebx != 0)
            break;
        cpu.eax = at(app, cpu.eax * 4 + kKeyRing);
        put(app, ebp - 4, cpu.eax);
        cpu.ebx = cpu.eax;
        cpu.esi = byte(app, ebp - 3);
        cpu.ebx = reg32(sreg32(cpu.ebx) >> 16);
        if (cpu.ebx == 0)
        {
            cpu.edx = 0;
            cpu.eax = cpu.esi;
            cpu.dl = byte(app, ebp - 4);
            if (!byAddress(app, cpu, kKeyCharacter))
                return;
            cpu.ebx = cpu.eax;
        }
        cpu.edx = at(app, kKeyRead);
        ++cpu.edx;
        cpu.ecx = at(app, kKeyRingSize);
        cpu.eax = cpu.edx;
        cpu.edx = reg32(sreg32(cpu.edx) >> 31);
        const std::int64_t dividend = std::int64_t(sreg32(cpu.eax));
        cpu.eax = reg32(sreg32(dividend / sreg32(cpu.ecx)));
        cpu.edx = reg32(sreg32(dividend % sreg32(cpu.ecx)));
        put(app, kKeyRead, cpu.edx);
    }
    cpu.edi = at(app, kKeyLock);
    push(app, cpu, cpu.edi);
    if (!windows(app, cpu, kLeaveCriticalSection))
        return;
    cpu.eax = cpu.esi;
    cpu.eax <<= 16;
    cpu.eax |= cpu.ebx;
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

}  // namespace frontend
}  // namespace nfs3hp
