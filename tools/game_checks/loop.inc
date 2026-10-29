// game_checks.cpp's parts for the menu loop, rewritten (src/nfs3hp/port_loop.cpp,
// port::loop), included in each table with the macro naming the part.
// The world is the menus' own tables -- the screens (0x6040d0, 0x24 bytes each)
// and their items (0x604ee0, 0xbc each, a screen's ended by an item of type
// 0), the loop's and the help box's variables, the race settings -- made up
// for each case, over menus.inc's (the language's text, its strings).  What
// the loop calls outside it is a stand-in on both sides: the handlers its
// tables hold through pseudo-slots, the drawing, the text, the dialogs, the
// music, the network's screens (generate.py's STOOD_IN for the port's own,
// whose cases are their own).
#if defined(LOOP_WINDOWS)
// {from, to}, -- what the functions write, compared (and the world made for the cases)
// The loop's and the help box's variables, the settings, the screens and
// their items, the history and the dialogs' lines, the clock, the network's
// flags, the display's flag, the mouse, the loop's flags.
{0x552000, 0x553000}, {0x555000, 0x556000}, {0x559000, 0x55a000}, {0x55d000, 0x560000}, {0x563000, 0x564000},
{0x600000, 0x640000}, {0x661000, 0x665000}, {0x6fb000, 0x6fc000}, {0x6fd000, 0x6fe000}, {0x79c000, 0x79d000},
{0x7a2000, 0x7a4000}, {0x8b7000, 0x8b8000}, {0x9ef000, 0x9f0000},
#elif defined(LOOP_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kLoopAction,    // a handler's or a dialog's result: 0 mostly, else what leaves a screen
kLoopPass,      // an item's pass: 0 mostly, 3 or 4 (it ends the pass) now and then, 12
kLoopDrawn,     // an item's drawing: 0 mostly, else anything
kLoopKey,       // the menus' key: none half the time, else Enter, Escape, an arrow, another
kLoopKeyResult, // the network's key: 0, kHandled or another
kLoopBusy,      // the network is busy: 0 or 1
kLoopMeasure,   // a text box measured: the widest line to [ecx], the height to the first stack word's place
kLoopFocus,     // the dialog's button focused: 0, 1 or another
#elif defined(LOOP_EFFECT_CASES)
// case kSomething: ... break;
case kLoopAction:
{
    static const x86::reg32 actions[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 2};
    result = r % 4 != 0 ? 0 : actions[(r >> 8) % 12];
    break;
}
case kLoopPass:
    result = r % 6 == 0 ? ((r >> 8) % 2 ? 3 : 4) : r % 5 == 0 ? 12 : 0;
    break;
case kLoopDrawn:
    result = r % 3 != 0 ? 0 : (r >> 8) | 1;
    break;
case kLoopKey:
{
    static const x86::reg32 keys[] = {0x0d, 0x1b, 0x4800, 0x4b00, 0x4d00, 0x5000, 'a', 0x4800, 0x1b};
    result = r % 2 == 0 ? 0 : keys[(r >> 8) % 9] | ((r >> 4) % 4 == 0 ? (r & 0xffff0000) : 0);
    break;
}
case kLoopKeyResult:
    result = r % 3 == 0 ? 2 : r % 3 == 1 ? 0 : (r >> 8) % 8;
    break;
case kLoopBusy:
    result = r % 3 == 0 ? 0 : 1;
    break;
case kLoopMeasure:
    // (The caller's: the width to [ecx], the height to the first stack word's place.)
    if (cpu.ecx < kMemory - 4)
        word(cpu.ecx) = 8 + (r >> 4) % 380;
    if (word(esp + 4) < kMemory - 4)
        word(word(esp + 4)) = 8 + (r >> 12) % 120;
    break;
case kLoopFocus:
    result = r % 3;
    break;
#elif defined(LOOP_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// What the loop calls: the port's own rewrites that are held on their own
// (generate.py's STOOD_IN) -- the keys, the text boxes, the frame and the
// gradient, the pointer, the screens started, the .MNU files, the network's
// leaving -- and the game's that the loop calls with the registers it means
// (the registers a row logs are those the caller passes).
{0x451960, "a menu key", kWatcom, 1, 0, kEax, -1, 0, kLoopKey},
{0x451b20, "the menu key reset", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x451fc0, "a text box drawn", kStdcall, 4, 6, kEax, -1, 0, kNothing},
{0x451ff0, "a text box measured", kStdcall, 4, 2, kEax, -1, 0, kLoopMeasure},
{0x452110, "the menus ended", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d8550, "a gradient rectangle", kStdcall, 4, 2, kEax, -1, 0, kNothing},
{0x4d8930, "a frame", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x4dab90, "the pointer drawn", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4daf80, "the screens started", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d1750, "the language's text loaded", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x440d20, "the network's screens left", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x449510, "the menus loaded", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x449960, "the menus' files checked", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x44a960, "the items shown", kWatcom, 1, 0, kEax, -1, 0, kNothing},
// The loop's own that the widgets and the fields call by address (buttons.inc
// has the screen shown): whether the keys are taken, an item selected, the
// items drawn.
{0x449df0, "the keys taken", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x44a470, "an item selected", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x44a4f0, "the items drawn", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x445f50, "a dialog's pass", kWatcom, 0, 0, kEax, -1, 0, kLoopAction},
{0x445e60, "a key for the dialog", kWatcom, 1, 0, kEax, -1, 0, kLoopAction},
{0x441040, "the network screens' pass", kWatcom, 0, 0, kEax, -1, 0, kLoopAction},
{0x441700, "a key for the network screens", kWatcom, 1, 0, kEax, -1, 0, kLoopKeyResult},
{0x441680, "the network busy", kWatcom, 0, 0, kEax, -1, 0, kLoopBusy},
{0x4446c0, "the dialog's button focused", kWatcom, 0, 0, kEax, -1, 0, kLoopFocus},
{0x444c10, "the dialog's text", kWatcom, 0, 0, kEax, -1, 0, kString},
#elif defined(LOOP_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// The handlers the tables hold, by pseudo-slot: an item's (+0x24 as the
// screen opens, +0x28 as it closes, +0x2c to draw it, +0x30 for a key, +0x34
// once it is up, +0x38 every pass) and a screen's (+0x08 as it opens, +0x0c
// as it closes, +0x10 every pass), and the display restored (the import's
// slot at 0x9ef918).
{0xfff800, "an item's handler as it opens", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0xfff804, "an item's handler as it closes", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0xfff808, "an item's drawing", kWatcom, 2, 0, kEax, -1, 0, kLoopDrawn},
{0xfff80c, "an item's key", kWatcom, 3, 0, kEax, -1, 0, kLoopAction},
{0xfff810, "an item's handler once up", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0xfff814, "an item's pass", kWatcom, 2, 0, kEax, -1, 0, kLoopPass},
{0xfff818, "a screen's handler as it opens", kWatcom, 2, 0, kEax, -1, 0, kLoopAction},
{0xfff81c, "a screen's handler as it closes", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0xfff820, "a screen's handler every pass", kWatcom, 2, 0, kEax, -1, 0, kLoopAction},
{0xfff824, "the display restored", kWatcom, 0, 0, kEax, -1, 0, kNothing},
#elif defined(LOOP_PROMISES)
// {"port::loop::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax and the registers the port keeps; not the eax of the help box and of the
// race settings' check, which no caller reads (by liveness on nfs3.exe: only
// the menu loop calls them and goes on without it).
{"port::loop::itemUsable", true, true, 0},
{"port::loop::keyAllowed", true, true, 0},
{"port::loop::drawHelp", true, false, 0},
{"port::loop::keysTaken", true, true, 0},
{"port::loop::selectable", true, true, 0},
{"port::loop::pointAtSelected", true, true, 0},
{"port::loop::selectPrevious", true, true, 0},
{"port::loop::selectNext", true, true, 0},
{"port::loop::escapeButton", true, true, 0},
{"port::loop::handleKey", true, true, 0},
{"port::loop::selectedIndex", true, true, 0},
{"port::loop::selectItem", true, true, 0},
{"port::loop::drawItems", true, true, 0},
{"port::loop::releaseMouse", true, true, 0},
{"port::loop::itemUnderMouse", true, true, 0},
{"port::loop::itemsShown", true, true, 0},
{"port::loop::passItems", true, true, 0},
{"port::loop::hideItems", true, true, 0},
{"port::loop::leaveScreen", true, true, 0},
{"port::loop::resetItems", true, true, 0},
{"port::loop::enterScreen", true, true, 0},
{"port::loop::menuByName", true, true, 0},
{"port::loop::currentMenu", true, true, 0},
{"port::loop::popMenu", true, true, 0},
{"port::loop::pushMenu", true, true, 0},
{"port::loop::setHistory", true, true, 0},
{"port::loop::player1NameAnswer", true, true, 0},
{"port::loop::player2NameAnswer", true, true, 0},
{"port::loop::quitAnswer", true, true, 0},
{"port::loop::waitWhileSuspended", true, true, 0},
{"port::loop::menuLoop", true, true, 0},
{"port::loop::fitRaceSettings", true, false, 0},
#elif defined(LOOP_ARGUMENTS)
/* Where the loop's cases keep their own, in menus.inc's scratch: the list of
 * names a history is set from, a word the functions write to (the loop's
 * action, the byte that closes a dialog), the edit text. */
constexpr x86::reg32 kLpNames = 0x30ea00, kLpWord = 0x30ec00, kLpClose = 0x30ec10;
constexpr x86::reg32 kLpScreens = 0x6040d0, kLpItems = 0x604ee0, kLpItemSize = 0xbc;

/* The handlers' pseudo-slots (loop.inc's LOOP_POINTERS). */
constexpr x86::reg32 kLpOnShow = 0xfff800, kLpOnHide = 0xfff804, kLpOnDraw = 0xfff808, kLpOnKey = 0xfff80c;
constexpr x86::reg32 kLpOnShown = 0xfff810, kLpOnPass = 0xfff814, kLpOnEnter = 0xfff818, kLpOnExit = 0xfff81c;
constexpr x86::reg32 kLpOnFrame = 0xfff820, kLpRestore = 0xfff824;

static const char* const kLpScreenNames[] = {"main", "location", "car1", "car2", "opponent", "showcase", "interior",
                                             "history", "compare", "options", "audio", "ipx", "postgame", "pause",
                                             "mainmult", "nothing"};
static const char* const kLpCodelinks[] = {"escape", "racenow", "BACK", "OK", "escape BACK", "a escape", "MAIN_BUTTON",
                                           "racenow escape", ""};

/* An item made up at `at`: its widget's type and state, its place, layer and
 * box (round the mouse, now and then), its help and codelink, its handlers. */
void makeLoopItem(CheckApp& g, x86::reg32 at, x86::reg32& slot, x86::reg32 mouseX, x86::reg32 mouseY, bool first)
{
    static const x86::reg32 types[] = {5, 5, 5, 5, 0x11, 0x12, 0x13, 0x1d, 2, 7, 0x0b};
    g.word(at) = chance(95) ? types[below(11)] : 1 + below(40);
    x86::reg32 state = 0;
    for (const x86::reg32 bit : {0x0001u, 0x0100u, 0x0200u, 0x0400u, 0x0800u, 0x1000u, 0x0010u, 0x2000u})
        if (chance(bit == 0x0400 ? 10 : bit == 0x1000 ? 12 : 22))
            state |= bit;
    // (A screen's first item can be selected, and used in a locked lobby: the
    // selection loops go round until one can, and would for ever else.)
    if (first)
        state &= ~0x1301u;
    g.getMemory<x86::reg16>(at + 4) = x86::reg16(state);
    g.getMemory<x86::reg16>(at + 6) = x86::reg16(below(640));
    g.getMemory<x86::reg16>(at + 8) = x86::reg16(below(480));
    g.getMemory<x86::reg16>(at + 0xa) = x86::reg16(chance(60) ? below(5) : chance(50) ? 8 : below(12));
    g.word(at + 0xc) = chance(70) ? mnString(g, slot, chance(15) ? "" : "some help text") : 0;
    g.word(at + 0x10) = first ? mnString(g, slot, "racenow") : chance(80) ? mnString(g, slot, kLpCodelinks[below(9)]) : 0;
    g.getMemory<x86::reg16>(at + 0x14) = x86::reg16(chance(15) ? 1 : 0);
    g.getMemory<x86::reg16>(at + 0x16) = x86::reg16(chance(15) ? 1 : 0);
    const bool around = chance(50);
    const x86::reg32 width = 10 + below(200), height = 10 + below(60);
    g.getMemory<x86::reg16>(at + 0x1a) = x86::reg16(around ? mouseY - below(height) : below(480));
    g.getMemory<x86::reg16>(at + 0x1c) = x86::reg16(around ? mouseX - below(width) : below(640));
    g.getMemory<x86::reg16>(at + 0x1e) = x86::reg16(width);
    g.getMemory<x86::reg16>(at + 0x20) = x86::reg16(height);
    const x86::reg32 handlers[] = {kLpOnShow, kLpOnHide, kLpOnDraw, kLpOnKey, kLpOnShown, kLpOnPass};
    for (x86::reg32 h = 0; h < 6; ++h)
        g.word(at + 0x24 + 4 * h) = chance(70) ? standInFor(handlers[h]) : 0;
    g.word(at + 0x3c) = 0;
    g.word(at + 0x40) = chance(70) ? mnString(g, slot, kLpScreenNames[below(16)]) : 0;
}

/* The loop's world: the language's text (menus.inc's), the screens with
 * their items, the loop's and the help box's variables, the settings the
 * race keeps consistent. */
void makeLoopWorld(CheckApp& g, x86::CPU& cpu)
{
    // (The pointer is placed by the game's own code, on both sides: the menus' world, the viewport and the mouse.)
    makeMenusWorld(g, cpu);
    x86::reg32 slot = 0;
    // The language's text: its lines' offsets, to 16 texts after them.
    g.word(0x563a80) = kMnTexts;
    for (x86::reg32 i = 0; i < 0x7a7; ++i)
        g.word(kMnTexts + 4 * i) = 0x1ea0 + 0x20 * (i % 16);
    for (x86::reg32 i = 0; i < 16; ++i)
        std::strcpy(&g.getMemory<char>(kMnTexts + 0x1ea0 + 0x20 * i), ("line" + std::to_string(i)).c_str());
    cpu.fpu.count = 0;

    // The mouse, the clock, the display.
    const x86::reg32 mouseX = below(640), mouseY = below(480);
    g.word(0x55e5e4) = chance(5) ? random32() : mouseX;
    g.word(0x55e5e8) = chance(5) ? random32() : mouseY;
    g.word(0x79c1a4) = chance(90) ? below(100000) : random32();
    g.getMemory<x86::reg8>(0x7a3a58) = x86::reg8(random32() & (chance(40) ? 0xff : 0xfd) | (chance(40) ? 2 : 0));
    g.getMemory<x86::reg8>(0x55eb2e) = x86::reg8(chance(50) ? 0 : chance(50) ? 0x10 : chance(50) ? 0x20 : random32());

    // The screens and their items.
    for (x86::reg32 at = kLpScreens; at < kLpScreens + 0x24 * 10; at += 4)
        g.word(at) = 0;
    for (x86::reg32 at = kLpItems; at < kLpItems + kLpItemSize * 80; at += 4)
        g.word(at) = 0;
    const x86::reg32 count = chance(4) ? 0 : 1 + below(6);
    g.word(0x660bb0) = count;
    x86::reg32 next = below(3);
    for (x86::reg32 i = 0; i < count; ++i)
    {
        const x86::reg32 at = kLpScreens + 0x24 * i;
        g.word(at + 8) = chance(60) ? standInFor(kLpOnEnter) : 0;
        g.word(at + 0xc) = chance(60) ? standInFor(kLpOnExit) : 0;
        g.word(at + 0x10) = chance(60) ? standInFor(kLpOnFrame) : 0;
        g.word(at + 0x14) = mnString(g, slot, kLpScreenNames[below(16)]);
        const x86::reg32 n = below(7);
        g.getMemory<x86::reg16>(at + 0x18) = x86::reg16(next);
        const x86::reg32 pick = chance(30) ? 100 : chance(85) ? below(n + 1) : x86::reg32(int(below(14)) - 3);
        g.getMemory<x86::reg16>(at + 0x1a) = x86::reg16(pick);
        g.getMemory<x86::reg16>(at + 0x1c) = x86::reg16(chance(30) ? 100 : chance(85) ? below(n + 1) : x86::reg32(int(below(14)) - 3));
        for (x86::reg32 j = 0; j < n; ++j)
            makeLoopItem(g, kLpItems + kLpItemSize * (next + j), slot, mouseX, mouseY, j == 0);
        next += n + 1 + below(2);
    }
    // The screen shown, the history, the movie's screen.
    const auto aScreen = [&] { return kLpScreens + 0x24 * below(count + (chance(8) ? 2 : 1)); };
    g.word(0x559230) = chance(8) ? 0 : aScreen();
    for (x86::reg32 i = 0; i < 20; ++i)
        g.word(0x662800 + 4 * i) = chance(50) ? 0 : aScreen();
    g.word(0x559224) = chance(60) ? 0 : mnString(g, slot, kLpScreenNames[below(16)]);

    // The loop's variables.
    g.word(0x559234) = chance(15) ? 1 : 0;
    g.word(0x662968) = chance(20) ? 1 : 0;
    g.word(0x7a22e0) = chance(25) ? 1 : 0;
    g.getMemory<x86::reg16>(0x7a22dc) = x86::reg16(chance(40) ? 1 : 0);
    g.word(0x6fd508) = chance(50) ? below(4) : 0;
    g.word(0x5556d0) = chance(10) ? 1 : 0;
    g.getMemory<x86::reg8>(0x559250) = x86::reg8(chance(10) ? 1 : 0);
    g.word(0x563aa4) = random32();
    g.word(0x563aa8) = random32();
    g.word(0x563aac) = random32();
    g.word(0x8b7630) = random32();
    g.word(0x55eb10) = random32();
    g.word(0x559228) = chance(50) ? 0 : random32();
    g.word(0x55922c) = chance(50) ? 0 : random32();
    g.word(0x66296c) = random32();
    g.getMemory<x86::reg8>(0x559251) = x86::reg8(chance(30) ? 1 : 0);
    g.word(0x55e894) = chance(25) ? 1 : 0;
    g.word(0x6fbb4c) = below(4);
    g.word(0x6fbbe8) = below(4);
    g.word(0x559444) = chance(30) ? 1 + below(3) : 0;
    g.word(0x55fec0) = random32();
    g.word(0x559c60) = chance(80) ? 0 : random32();
    g.word(0x559c68) = random32();
    g.word(0x9ef918) = standInFor(kLpRestore);
    std::strcpy(&g.getMemory<char>(0x7a2db4), "art\\");
    g.word(0x664658) = chance(50) ? 1 : 0;
    g.word(0x662970) = random32();
    g.word(0x662974) = random32();
    g.word(0x66297c) = random32();
    g.word(0x662980) = random32();
    for (const x86::reg32 name : {0x6fd2fc, 0x6fd368})
    {
        const std::string s = chance(40) ? "" : chance(50) ? "Racer" : "A name longer than the buffer of ten";
        std::strcpy(&g.getMemory<char>(name), s.c_str());
    }

    // The help box.
    g.word(0x559248) = chance(60) ? g.word(0x559230) : random32();
    g.word(0x559238) = chance(50) ? 1 : 0;
    g.word(0x55923c) = chance(50) ? g.word(0x55e5e4) : below(640);
    g.word(0x559240) = chance(50) ? g.word(0x55e5e8) : below(480);
    g.word(0x662950) = g.word(0x79c1a4) + below(300) - 150;
    g.word(0x559244) = chance(50) ? 0xffffffff : below(6);
    g.word(0x55924c) = chance(50) ? 0 : mnString(g, slot, chance(15) ? "" : "help");
    g.word(0x662964) = chance(50) ? 0 : chance(50) ? 255 : random32();
    g.word(0x662958) = random32();
    g.word(0x66295c) = random32();
    g.word(0x662960) = random32();
    g.word(0x662954) = random32();
    g.word(0x559450) = random32();

    // The race settings.
    g.word(0x6fd3b8) = chance(90) ? below(5) : random32();
    g.word(0x6fd3b0) = chance(90) ? below(4) : random32();
    g.word(0x6fd4d0) = chance(90) ? below(4) : random32();
    g.word(0x6fd4d4) = chance(90) ? below(6) : random32();
    g.word(0x559258) = chance(25) ? 0xffffffff : chance(50) ? g.word(0x6fd4d0) : below(4);
    g.word(0x55925c) = chance(50) ? g.word(0x6fd4d4) : below(6);
    g.word(0x559260) = chance(25) ? 0xffffffff : chance(50) ? g.word(0x6fd3b8) : below(5);
    g.word(0x6fbbe4) = chance(50) ? 0 : below(3);
    g.word(0x6fbbd8) = random32();
    g.word(0x6fbc00) = chance(90) ? below(3) : random32();
    g.word(0x55292c) = random32();
    g.word(0x6fd504) = chance(90) ? below(5) : random32();
    g.getMemory<x86::reg16>(0x55639c) = x86::reg16(random32());
    g.word(0x6fd4e8) = random32();
    g.word(0x6fd4ac) = random32();
    g.word(0x55d004) = random32();
    g.word(0x6fd4b0) = random32();
    g.word(0x6fd4b4) = random32();
    g.word(0x6fd2ac) = chance(50) ? 0 : random32();
    g.getMemory<x86::reg16>(0x7a2276) = x86::reg16(below(4));
    g.word(0x55e5d0) = chance(50) ? g.getMemory<x86::reg16>(0x7a2276) : below(4);
    g.word(0x6fd2bc) = random32();
    g.word(0x6fd328) = random32();
}

/* A key: Enter, Escape, an arrow, any other; with garbage above it now and then. */
x86::reg32 aLoopKey()
{
    static const x86::reg32 keys[] = {0x0d, 0x1b, 0x4800, 0x4b00, 0x4d00, 0x5000, 'a', 0x20, 0};
    const x86::reg32 key = chance(90) ? keys[below(9)] : below(0x10000);
    return chance(20) ? (random32() & 0xffff0000) | key : key;
}

bool makeLoopArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    makeLoopWorld(g, cpu);
    (void)a;
    x86::reg32 slot = 300;
    const x86::reg32 count = g.word(0x660bb0);
    const auto aScreen = [&] { return kLpScreens + 0x24 * below(count + (chance(10) ? 2 : 1)); };
    // An item: one of the first, the end of a screen's, or any word.
    const auto anItem = [&] {
        return chance(85) ? kLpItems + kLpItemSize * below(20) : chance(50) ? kLpItems + kLpItemSize * below(60) : kLpItems + below(0x30000);
    };
    const auto aScreenName = [&] { return mnString(g, slot, kLpScreenNames[below(16)]); };
    if (name == "itemUsable")
        cpu.eax = anItem();
    else if (name == "keyAllowed")
    {
        cpu.eax = aScreen();
        cpu.edx = aLoopKey();
    }
    else if (name == "selectable")
    {
        cpu.eax = chance(80) ? below(8) : chance(50) ? 100 : chance(50) ? x86::reg32(-1 - int(below(5))) : below(20);
        cpu.edx = aScreen();
    }
    else if (name == "pointAtSelected" || name == "selectPrevious" || name == "selectNext" || name == "drawItems"
             || name == "itemUnderMouse" || name == "itemsShown" || name == "passItems" || name == "hideItems"
             || name == "resetItems" || name == "enterScreen")
    {
        cpu.eax = aScreen();
        g_mostCalls = 300;
    }
    else if (name == "escapeButton")
    {
        cpu.eax = chance(5) ? 0 : aScreen();
        cpu.edx = kLpWord;
        g.word(kLpWord) = random32();
    }
    else if (name == "handleKey")
    {
        cpu.eax = aScreen();
        cpu.edx = aLoopKey();
        g_mostCalls = 300;
    }
    else if (name == "selectItem")
        cpu.eax = anItem();
    else if (name == "leaveScreen")
    {
        static const x86::reg32 actions[] = {0, 1, 3, 4, 5, 6, 7, 9, 10, 11, 13, 9};
        cpu.eax = aScreen();
        cpu.edx = chance(90) ? actions[below(12)] : random32();
    }
    else if (name == "menuByName")
        cpu.eax = chance(5) ? 0 : aScreenName();
    else if (name == "setHistory")
    {
        cpu.eax = kLpNames;
        const x86::reg32 n = below(5);
        for (x86::reg32 i = 0; i < 6; ++i)
            g.word(kLpNames + 4 * i) = i < n ? aScreenName() : 0;
    }
    else if (name == "player1NameAnswer" || name == "player2NameAnswer")
    {
        cpu.eax = chance(90) ? below(4) : random32();
        cpu.edx = kLpClose;
        g.word(kLpClose) = random32();
    }
    else if (name == "quitAnswer")
    {
        cpu.eax = chance(90) ? below(4) : random32();
        cpu.edx = chance(20) ? 0 : kLpClose;
        g.word(kLpClose) = random32();
    }
    else if (name == "waitWhileSuspended")
    {
        cpu.eax = aScreen();
        cpu.edx = kLpWord;
        g.word(kLpWord) = random32();
        g_mostCalls = 40;
    }
    else if (name == "menuLoop")
    {
        cpu.eax = chance(30) ? mnString(g, slot, "postgame") : aScreenName();
        cpu.edx = 0;
        if (chance(40))
        {
            cpu.edx = kLpNames;
            const x86::reg32 n = below(4);
            for (x86::reg32 i = 0; i < 5; ++i)
                g.word(kLpNames + 4 * i) = i < n ? aScreenName() : 0;
        }
        g_mostCalls = 150 + below(300);
    }
    else if (name == "drawHelp" && chance(60))
    {
        // The help box ready to show: the screen shown has an item selected,
        // the pointer has rested on it, no keys taken, the box not shown yet,
        // the pointer anywhere across the screen.
        for (x86::reg32 i = 0; i < count; ++i)
        {
            const x86::reg32 screen = kLpScreens + 0x24 * i;
            const x86::reg32 first = g.getMemory<x86::reg16>(screen + 0x18);
            const x86::reg32 it = kLpItems + kLpItemSize * first;
            if (g.word(it) == 0)
                continue;
            g.word(0x559230) = screen;
            g.getMemory<x86::reg16>(screen + 0x1a) = 0;
            g.getMemory<x86::reg16>(it + 4) &= ~0x0400;
            g.word(it + 0xc) = mnString(g, slot, chance(90) ? "some help text" : "");
            g.word(0x559248) = screen;
            g.word(0x559238) = 0;
            g.word(0x559244) = 0xffffffff;
            g.word(0x55e5e4) = below(660);
            g.word(0x55e5e8) = below(500);
            g.word(0x55923c) = g.word(0x55e5e4);
            g.word(0x559240) = g.word(0x55e5e8);
            g.word(0x662950) = g.word(0x79c1a4) - below(50);
            g.word(0x559234) = chance(30) ? 1 : 0;
            break;
        }
    }
    // (currentMenu, popMenu, pushMenu, keysTaken, selectedIndex, releaseMouse, drawHelp, fitRaceSettings: no arguments.)
    else if (name == "releaseMouse")
        cpu.eax = random32();
    return true;
}
#endif
