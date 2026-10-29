// game_checks.cpp's parts for the dialogs, rewritten (src/nfs3hp/port_dialogs.cpp,
// port::dialogs), included in each table with the macro naming the part.
// The world is the dialog's own variables -- the kind up, its lines, buttons
// and boxes, the line typed in, a list's entries and ticks, the fade, the
// help box -- made up for each case over the loop's (loop.inc's: the menus',
// the mouse, the clock) and menus.inc's scratch.  What the dialogs call
// outside them is a stand-in on both sides: the layout (native whole,
// frontend_checks'), the text, the 2D drawing and the shapes (generate.py's
// STOOD_IN for the port's own, whose cases are their own), the callback the
// dialog hands its answer to, through a pseudo-slot.
#if defined(DIALOGS_HOOKS)
// nfs3hp_main.cpp: the box's emblem kept round on a wide screen (tools/apply_widescreen.py).
namespace nfs3hp
{
void dialogEmblem(bool) {}
}
#elif defined(DIALOGS_WINDOWS)
// {from, to}, -- what the functions write, compared (and the world made for the cases)
// The dialog's variables (0x558afc to 0x558d08), the pause screens' art.
{0x558000, 0x559000}, {0x749000, 0x74a000},
#elif defined(DIALOGS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kDlgWidth,      // a text's width: a few pixels to a few hundred
kDlgShapeSize,  // a shape's size: a word each to [edx] and [ebx]
kDlgCallback,   // the dialog's callback: 0 mostly, else an answer's result; the byte [edx] cleared now and then
#elif defined(DIALOGS_EFFECT_CASES)
// case kSomething: ... break;
case kDlgWidth:
    result = r % 9 == 0 ? 0 : 4 + (r >> 8) % 320;
    break;
case kDlgShapeSize:
    if (cpu.edx < kMemory - 4)
        getMemory<x86::reg16>(cpu.edx) = x86::reg16(r % 5 == 0 ? 0 : 6 + (r >> 4) % 40);
    if (cpu.ebx < kMemory - 4)
        getMemory<x86::reg16>(cpu.ebx) = x86::reg16(r % 5 == 0 ? 0 : 6 + (r >> 12) % 40);
    break;
case kDlgCallback:
{
    static const x86::reg32 results[] = {1, 2, 3, 4, 5, 10, 2, 0};
    result = r % 3 != 0 ? 0 : results[(r >> 8) % 8];
    if (cpu.edx < kMemory - 4 && (r >> 20) % 2 == 0)
        getMemory<x86::reg8>(cpu.edx) = 0;
    break;
}
#elif defined(DIALOGS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// What the dialogs call: the text's font and width, the 2D drawing and the
// shapes (the port's own, held on their own), the layout (native whole), and
// the dialog functions that others call by address and that are rewritten
// now (a message ended, the dialogs' art loaded, the dialog closed).
{0x452100, "a font selected", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x452020, "a text's width", kWatcom, 2, 0, kEax, -1, 0, kDlgWidth},
{0x4d8860, "a shaded box", kStdcall, 4, 4, kEax, -1, 0, kNothing},
{0x4d8ac0, "a field's box", kStdcall, 4, 4, kEax, -1, 0, kNothing},
{0x4d8910, "a rectangle filled", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x4db000, "a textured quad", kStdcall, 4, 14, kEax, -1, 0, kNothing},
{0x4d7160, "an art shape drawn", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4d66f0, "a shape's size", kWatcom, 3, 0, kEax, -1, 0, kDlgShapeSize},
{0x443a90, "the lines' box", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x443c00, "the buttons' box", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x443d20, "the buttons placed", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x444570, "the pointer on a button", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x444a60, "a message ended", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x445de0, "the dialogs' art loaded", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x445f10, "the dialog closed", kWatcom, 0, 0, kEax, -1, 0, kNothing},
#elif defined(DIALOGS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// The dialog's callback (+0x558b18), by pseudo-slot: told the answer in eax and
// the byte that keeps the dialog up in edx.
{0xfff828, "the dialog's callback", kWatcom, 2, 0, kEax, -1, 0, kDlgCallback},
#elif defined(DIALOGS_PROMISES)
// {"port::dialogs::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax and the registers the port keeps; the x87's stack and words where the
// layout's floats go through it.  Not the eax of what only the dialog's own
// functions call and ignore the result of (the lines, the buttons, the list,
// the help box, the entries' layout, the field), by liveness on nfs3.exe.
{"port::dialogs::dialogShown", true, true, 0},
{"port::dialogs::dialogKind", true, true, 0},
{"port::dialogs::drawBox", true, true, 0, true, kNoHeap, true},
{"port::dialogs::drawLines", true, false, 0, true, kNoHeap, true},
{"port::dialogs::drawButtons", true, false, 0, true, kNoHeap, true},
{"port::dialogs::drawEditField", true, false, 0, true, kNoHeap, true},
{"port::dialogs::buttonUnderMouse", true, true, 0},
{"port::dialogs::questionKey", true, true, 0},
{"port::dialogs::questionPass", true, true, 0},
{"port::dialogs::endMessage", true, true, 0},
{"port::dialogs::messageKey", true, true, 0},
{"port::dialogs::messagePass", true, true, 0},
{"port::dialogs::editKey", true, true, 0},
{"port::dialogs::editPass", true, true, 0},
{"port::dialogs::listFocus", true, true, 0},
{"port::dialogs::pointAtEntry", true, true, 0},
{"port::dialogs::entryUnderMouse", true, true, 0},
{"port::dialogs::placeEntries", true, false, 0},
{"port::dialogs::drawList", true, false, 0},
{"port::dialogs::listKey", true, true, 0},
{"port::dialogs::listPass", true, true, 0},
{"port::dialogs::openList", true, true, 0, true, kNoHeap, true},
{"port::dialogs::drawDialogHelp", true, false, 0},
{"port::dialogs::loadDialogArt", true, true, 0},
{"port::dialogs::dialogKey", true, true, 0},
{"port::dialogs::closeDialog", true, true, 0},
{"port::dialogs::dialogPass", true, true, 0},
#elif defined(DIALOGS_ARGUMENTS)
/* Where the dialogs' cases keep their own, in menus.inc's scratch: the arrays
 * of lines, buttons and their help, a list's names, ticks and help, and the
 * ticks themselves. */
constexpr x86::reg32 kDlLines = 0x30f000, kDlButtons = 0x30f040, kDlButtonHelp = 0x30f080, kDlNames = 0x30f0c0;
constexpr x86::reg32 kDlTicks = 0x30f100, kDlEntryHelp = 0x30f140, kDlTickWords = 0x30f200;
constexpr x86::reg32 kDlCallbackSlot = 0xfff828;

/* A float of the screen's, on the 640 by 480, now and then a wild one. */
x86::reg32 aDlgFloat(x86::reg32 most)
{
    const float f = chance(95) ? float(below(most)) + (chance(30) ? 0.5f : 0.0f) : float(int(below(2000)) - 700) / 3.0f;
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

void makeDialogsWorld(CheckApp& g, x86::CPU& cpu)
{
    makeLoopWorld(g, cpu);
    // (The clip is set by the game's own code on both sides: the 2D drawing's world, its THRASH slots.)
    makeFeDrawWorld(g, cpu);
    x86::reg32 slot = 120;
    // Which dialog is up, and its callback.
    g.getMemory<x86::reg8>(0x558b10) = x86::reg8(chance(80) ? 1 : chance(50) ? 0 : random32());
    g.word(0x558b14) = chance(90) ? below(5) : random32();
    g.word(0x558b18) = chance(70) ? standInFor(kDlCallbackSlot) : 0;
    // Lines and buttons: strings, their arrays, some entries null.
    static const char* const texts[] = {"Are you sure?", "OK", "Cancel", "Yes", "No", "A longer line of text here", "x",
                                        "Quit the game", "", "Player 1"};
    for (x86::reg32 i = 0; i < 10; ++i)
    {
        g.word(kDlLines + 4 * i) = chance(10) ? 0 : mnString(g, slot, texts[below(10)]);
        g.word(kDlButtons + 4 * i) = chance(10) ? 0 : mnString(g, slot, texts[below(10)]);
        g.word(kDlButtonHelp + 4 * i) = chance(20) ? 0 : mnString(g, slot, chance(10) ? "" : "help for it");
        g.word(kDlNames + 4 * i) = chance(10) ? 0 : mnString(g, slot, texts[below(10)]);
        g.word(kDlEntryHelp + 4 * i) = chance(20) ? 0 : mnString(g, slot, "help for an entry");
        g.word(kDlTicks + 4 * i) = chance(20) ? 0 : kDlTickWords + 4 * i;
        g.word(kDlTickWords + 4 * i) = chance(50) ? 0 : 1;
    }
    g.word(0x558b1c) = chance(90) ? below(5) : random32() % 12;
    g.word(0x558b20) = chance(95) ? kDlLines : 0;
    g.word(0x558b30) = chance(90) ? below(5) : chance(50) ? 9 + below(3) : random32() % 20;
    g.word(0x558b34) = chance(95) ? kDlButtons : 0;
    g.word(0x558b38) = chance(50) ? 0 : kDlButtonHelp;
    g.word(0x558b3c) = chance(15) ? 0xffffffff : chance(90) ? below(g.word(0x558b30) + 1) : random32() % 12;
    g.word(0x558b40) = below(500);
    g.word(0x558b44) = chance(70) ? g.word(0x79c1a4) - below(700) : random32();
    g.word(0x558b48) = chance(30) ? 0 : chance(70) ? below(800) : random32();
    g.getMemory<x86::reg8>(0x558b4c) = x86::reg8(chance(50) ? 1 : 0);
    // The line typed in.
    g.word(0x558b2c) = chance(40) ? 1 : 0;
    g.word(0x558b50) = chance(85) ? below(24) : random32() % 300;
    g.word(0x558b54) = chance(85) ? below(24) : random32() % 300;
    {
        std::string s;
        for (x86::reg32 i = below(chance(90) ? 20 : 250); i > 0; --i)
            s += char('a' + below(26));
        std::memset(&g.getMemory<char>(0x558b58), 0, 0x100);
        std::memcpy(&g.getMemory<char>(0x558b58), s.c_str(), std::min<std::size_t>(s.size(), 0xff));
    }
    g.word(0x558c5c) = chance(90) ? below(4) : random32() % 8;
    g.word(0x661070) = chance(90) ? 20 + below(220) : random32() % 400;
    g.word(0x558d08) = chance(90) ? below(25) : random32() % 40;
    // A list's.
    g.word(0x558c60) = chance(30) ? 0xffffffff : below(7);
    g.getMemory<x86::reg8>(0x558c64) = x86::reg8(chance(90) ? below(7) : random32());
    g.word(0x558c68) = chance(95) ? kDlNames : 0;
    g.word(0x558c6c) = chance(95) ? kDlTicks : 0;
    g.word(0x558c70) = chance(50) ? 0 : kDlEntryHelp;
    g.word(0x558c74) = below(500);
    g.word(0x558c78) = below(400);
    // The box (floats), the buttons' and entries' boxes, the fade.
    const x86::reg32 top = below(200), left = below(200);
    const float rect[4] = {float(top), float(left), float(top + 60 + below(200)), float(left + 100 + below(300))};
    std::memcpy(&g.getMemory<char>(0x661050), rect, 16);
    if (chance(10))
        for (x86::reg32 i = 0; i < 4; ++i)
            g.word(0x661050 + 4 * i) = aDlgFloat(640);
    for (x86::reg32 i = 0; i < 10; ++i)
    {
        const x86::reg32 at = 0x661000 + 8 * i;
        g.getMemory<x86::reg16>(at) = x86::reg16(chance(50) ? g.word(0x55e5e8) - below(20) : below(480));
        g.getMemory<x86::reg16>(at + 2) = x86::reg16(chance(50) ? g.word(0x55e5e4) - below(80) : below(640));
        g.getMemory<x86::reg16>(at + 4) = x86::reg16(20 + below(120));
        g.getMemory<x86::reg16>(at + 6) = x86::reg16(chance(50) ? 17 : 30);
    }
    for (x86::reg32 i = 0; i < 6; ++i)
    {
        const x86::reg32 at = 0x660fd0 + 8 * i;
        g.getMemory<x86::reg16>(at) = x86::reg16(chance(50) ? g.word(0x55e5e8) - below(14) : below(480));
        g.getMemory<x86::reg16>(at + 2) = x86::reg16(chance(50) ? g.word(0x55e5e4) - below(80) : below(640));
        g.getMemory<x86::reg16>(at + 4) = x86::reg16(20 + below(120));
        g.getMemory<x86::reg16>(at + 6) = x86::reg16(chance(50) ? 18 : 30);
    }
    g.word(0x661064) = chance(40) ? 255 : chance(80) ? below(256) : random32();
    // Its art and the pause screens'.
    for (const x86::reg32 at : {0x66108c, 0x661068, 0x661060, 0x558b24, 0x558b28, 0x66106c, 0x749a38})
        g.word(at) = random32();
    // The help box over it.
    g.word(0x558afc) = chance(30) ? 0 : chance(30) ? 1 : 0xffffffff;
    g.word(0x558b00) = chance(50) ? g.word(0x55e5e4) : below(640);
    g.word(0x558b04) = chance(50) ? g.word(0x55e5e8) : below(480);
    g.word(0x558b08) = chance(40) ? 0xffffffff : below(7);
    g.word(0x558b0c) = chance(50) ? 0 : mnString(g, slot, chance(10) ? "" : "dialog help");
    g.word(0x661084) = g.word(0x79c1a4) + below(300) - 150;
    g.word(0x661088) = chance(30) ? 0 : chance(40) ? 255 : below(300);
    g.word(0x661074) = random32();
    g.word(0x661078) = random32();
    g.word(0x66107c) = random32();
    g.word(0x661080) = random32();
}

x86::reg32 aDlgKey()
{
    static const x86::reg32 keys[] = {0x0d, 0x1b, 0x20, 0x08, 0x5300, 0x4800, 0x4b00, 0x4d00, 0x5000, 'a', 'Z', '7', 0x7f, 0};
    const x86::reg32 key = chance(92) ? keys[below(14)] : below(0x10000);
    return chance(20) ? (random32() & 0xffff0000) | key : key;
}

bool makeDialogsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    makeDialogsWorld(g, cpu);
    const auto aRect = [&] { return chance(95) ? 0x661050 : 0x30ff00; };
    if (name == "dialogShown")
        cpu.eax = random32();
    else if (name == "drawBox" || name == "drawEditField")
        cpu.eax = aRect();
    else if (name == "drawLines")
    {
        cpu.eax = chance(90) ? below(5) : random32() % 12;
        cpu.edx = kDlLines;
        cpu.ebx = aRect();
    }
    else if (name == "drawButtons")
        cpu.edx = chance(15) ? 0xffffffff : below(5);
    else if (name == "questionKey" || name == "messageKey" || name == "editKey" || name == "listKey" || name == "dialogKey")
        cpu.eax = aDlgKey();
    else if (name == "pointAtEntry")
        cpu.eax = chance(80) ? below(7) : chance(50) ? 0xffffffff : random32();
    else if (name == "placeEntries")
    {
        cpu.eax = chance(90) ? below(8) : random32() % 12;
        cpu.edx = kDlNames;
    }
    else if (name == "openList")
    {
        cpu.eax = chance(90) ? below(4) : 0;
        cpu.edx = chance(95) ? kDlLines : 0;
        cpu.ebx = chance(90) ? below(8) : 0;
        cpu.ecx = chance(95) ? kDlNames : 0;
        a[0] = chance(95) ? kDlTicks : 0;
        a[1] = chance(50) ? 0 : kDlEntryHelp;
        a[2] = chance(90) ? below(12) : 0;
        a[3] = chance(95) ? kDlButtons : 0;
        a[4] = chance(50) ? 0 : kDlButtonHelp;
        a[5] = chance(80) ? below(5) : random32() % 12 - 3;
        a[6] = chance(50) ? 0 : 1;
        a[7] = chance(70) ? standInFor(kDlCallbackSlot) : 0;
    }
    return true;
}
#endif
