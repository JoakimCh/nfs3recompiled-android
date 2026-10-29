// game_checks.cpp's parts for the menus' widgets, rewritten (src/nfs3hp/port_buttons.cpp,
// port::buttons), included in each table with the macro naming the part.
// The world is the menus' (frontend_glue.inc's lists, frontend_draw.inc's
// drawing and shapes): what the widgets call of the port's own -- the text,
// the 2D drawing, the shapes -- runs on both sides, as the generated code
// calls it; what is not rewritten has its stand-ins.
#if defined(BUTTONS_WINDOWS)
// {from, to}, -- what the functions write, compared
// The lists' scrolling and the select list's clicks (0x55a424 to 0x55a434);
// the track's map and its slide, the map's cars (0x677d40 to 0x6788ec).
{0x55a000, 0x55b000}, {0x677000, 0x679000},
#elif defined(BUTTONS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kButtonsShown,   // the menu shown now: 0 or 1
kButtonsScreen,  // the screen's items: the cases' screen record
kButtonsFound,   // a menu's item by name: one of the cases' items, or none
#elif defined(BUTTONS_EFFECT_CASES)
// case kSomething: ... break;
case kButtonsShown:
    result = r % 4 == 0 ? 0 : 1;
    break;
case kButtonsScreen:
    result = 0x61e300;
    break;
case kButtonsFound:
    result = r % 4 == 0 ? 0 : 0x604ee0 + 0xbc * ((r >> 8) % 6);
    break;
#elif defined(BUTTONS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The menu loop's and the dialogs' that the widgets call (the frontend's
// natives frontend_checks holds, no stand-in of their own here): whether
// the screen is the one shown now, a dialog's message, a menu's item found
// by name (logged); the screen's items; and EA's new bitmap and a shape of
// it, a block of the menus' art.
{0x44a660, "the menu shown now", kWatcom, 2, 0, kEax, -1, 0, kButtonsShown},
{0x444be0, "a dialog's message", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x442a40, "a menu's item found", kWatcom, 2, 0, kEax, 1, 8, kButtonsFound},
{0x44aeb0, "the screen's items", kWatcom, 0, 0, kEax, -1, 0, kButtonsScreen},
{0x4ef190, "a bitmap made", kWatcom, 4, 0, kEax, -1, 0, kBlock},
{0x4ef1e0, "a bitmap's shape", kWatcom, 2, 0, kEax, -1, 0, kBlock},
// port_shapes' art's textures, which the image and the track's map ask of a
// bitmap's shape: stood in (generate.py's STOOD_IN, but for shapeByName,
// whose port code calls it as C++) -- its graphics are the shapes' cases'.
{0x4d6390, "the art's textures", kWatcom, 3, 0, kEax, -1, 0, kSomething},
// The replays listed into a select list (load::listReplays); the window
// taken and cleared, the frame shown (the graphics' natives): the files' and
// the graphics' worlds are their own cases'.
{0x4475a0, "the replays listed", kWatcom, 2, 0, kEax, 1, 4, kNothing},
{0x4d9120, "the window taken and cleared", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d9140, "the frame shown", kWatcom, 0, 0, kEax, -1, 0, kNothing},
#elif defined(BUTTONS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// A rectangle's drawing over it (+0x54), a select list's function told of a
// line chosen (+0x74): by pseudo-slot.
{0xfff6c4, "a rectangle's drawing over", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0xfff6c8, "a select list's choice told", kWatcom, 2, 0, kEax, -1, 0, kNothing},
#elif defined(BUTTONS_PROMISES)
// {"port::buttons::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax and the registers the port keeps; the x87's stack, its live registers,
// its words.  The three layouts' eax no caller reads (by liveness on
// nfs3.exe: buttonKey and cascadeKey and listKey after their calls, the menu
// loop's "up" call through the widgets' table): not compared.
{"port::buttons::joinListedGame", true, true, 0, true, kNoHeap, true},
{"port::buttons::drawReadyMarks", true, true, 0, true, kNoHeap, true},
{"port::buttons::networkLeft", true, true, 0, true, kNoHeap, true},
{"port::buttons::drawLicence", true, true, 0, true, kNoHeap, true},
{"port::buttons::listColours", true, true, 0, true, kNoHeap, true},
{"port::buttons::listAllowed", true, true, 0, true, kNoHeap, true},
{"port::buttons::listLength", true, true, 0, true, kNoHeap, true},
{"port::buttons::findList", true, true, 0, true, kNoHeap, true},
{"port::buttons::menuEdited", true, true, 0, true, kNoHeap, true},
{"port::buttons::menuRecordEdited", true, true, 0, true, kNoHeap, true},
{"port::buttons::loadShapes", true, true, 0, true, kNoHeap, true},
{"port::buttons::redrawMenu", true, true, 0, true, kNoHeap, true},
{"port::buttons::textBoxDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::textBoxKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::textBoxUp", true, true, 0, true, kNoHeap, true},
{"port::buttons::textBoxShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::textBoxHidden", true, true, 0, true, kNoHeap, true},
{"port::buttons::slideTrackMap", true, true, 0, true, kNoHeap, true},
{"port::buttons::drawTrackFacts", true, true, 0, true, kNoHeap, true},
{"port::buttons::drawGlow", true, true, 0, true, kNoHeap, true},
{"port::buttons::trackMapShape", true, true, 0, true, kNoHeap, true},
{"port::buttons::rectDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::speechDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::speechShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::speechHidden", true, true, 0, true, kNoHeap, true},
{"port::buttons::textDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::textUp", true, true, 0, true, kNoHeap, true},
{"port::buttons::textShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::imageDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::imageUp", true, true, 0, true, kNoHeap, true},
{"port::buttons::imageShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::pulseOn", true, true, 0, true, kNoHeap, true},
{"port::buttons::pulseColour", true, true, 0, true, kNoHeap, true},
{"port::buttons::buttonDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::buttonKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::layoutMenuItem", true, false, 0, true, kNoHeap, true},
{"port::buttons::buttonShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeLayoutClosed", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeLineText", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadePass", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::cascadeUp", true, false, 0, true, kNoHeap, true},
{"port::buttons::checkboxDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::checkboxKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::checkboxShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::checkboxUp", true, true, 0, true, kNoHeap, true},
{"port::buttons::boxOverlayDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListHidden", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListPass", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::selectListUp", true, true, 0, true, kNoHeap, true},
{"port::buttons::dropListDraw", true, true, 0, true, kNoHeap, true},
{"port::buttons::dropListPass", true, true, 0, true, kNoHeap, true},
{"port::buttons::dropListShown", true, true, 0, true, kNoHeap, true},
{"port::buttons::listKey", true, true, 0, true, kNoHeap, true},
{"port::buttons::layoutList", true, false, 0, true, kNoHeap, true},
{"port::buttons::drawTurnedShape", true, true, 0, true, kNoHeap, true},
{"port::buttons::drawColouredRectangle", true, true, 0, true, kNoHeap, true},
#elif defined(BUTTONS_ARGUMENTS)
/* Where the widgets' cases keep their own: an item; texts; the screen's
 * record (kButtonsScreen); the select list's lines; the network games found;
 * strings named; a buffer handed in. */
constexpr x86::reg32 kBtnItem = 0x61e000, kBtnTexts = 0x61e100, kBtnScreen = 0x61e300, kBtnLines = 0x61e400;
constexpr x86::reg32 kBtnGames = 0x61e500, kBtnNames = 0x61e800, kBtnOut = 0x61ec00;

/* The menu shapes' names the widgets ask for: known (the first 24 of the
 * shapes the drawing's world knows), so that their search ends there --
 * one not known is made from the art, deep in the graphics' code. */
const char* const kBtnShapeNames[] = {"bup1", "bdn1", "yup1", "ydn1", "yar1", "bdd2", "weel", "badg",
                                      "yel1", "yel2", "ldro", "lhte", "rdro", "rhte", "ytri", "tdd1",
                                      "yar2", "comb", "blit", "byar", "3btt", "2btt", "tbkn", "sbkn"};

x86::reg32 btnName(x86::reg32 i)
{
    return kBtnNames + 8 * i;
}

/* A menu shape's record: one the world has tiles for. */
x86::reg16 aBtnShape()
{
    return x86::reg16(chance(90) ? below(20) : below(100));
}

x86::reg16 btnWord(x86::reg32 most)
{
    return x86::reg16(chance(90) ? below(most) : chance(50) ? below(most + 200) - 100 : random32());
}

void setBtnHalf(CheckApp& g, x86::reg32 at, x86::reg32 value)
{
    g.getMemory<x86::reg16>(at) = x86::reg16(value);
}

/* The widgets' world: the menus' lists and screen (frontend_glue.inc), the
 * drawing and the shapes (frontend_draw.inc, shapes.inc) -- the names asked
 * for known, the blocks small shapes --, the fonts' lists with room; the
 * buttons' styles, the races' places, the tables the images and the track's
 * map read; an item of random words with sane places, shapes and strings. */
void makeButtonsWorld(CheckApp& g, x86::CPU& cpu, x86::reg32* a)
{
    makeFeGlueWorld(g, cpu);
    makeShapesWorld(g, cpu, a);
    makeFeDrawWorld(g, cpu);
    // The click's sound: its world as the sound's cases have it.
    makeSoundArguments(g, "playMenuEffect", cpu, a);
    saneQuadLists(g);
    // The fonts' lists: room for long texts.
    for (x86::reg32 font = 0; font < 2; ++font)
        g.word(0x7f74c0 + 0x24010 * font + 4) = 0x400 + below(0x200);
    // The lists' lines: the language's (none past its lines, whose names'
    // stand-ins are the text's cases').
    for (x86::reg32 at = kFeLines; at < kFeLines + 0x180; at += 2)
        if (g.getMemory<x86::reg16>(at) != 0)
            g.getMemory<x86::reg16>(at) = x86::reg16(1 + below(0x7a6));
    // The lists: four, all named, their colours (a dword a line) or none.
    for (x86::reg32 i = 0; i < 4; ++i)
    {
        g.word(0x5563e8 + 0x14 * i) = kFeNames + 0x10 * i;
        g.word(0x5563e8 + 0x14 * i + 0xc) = chance(50) ? 0 : 0x61e600;
    }
    for (x86::reg32 at = 0x61e600; at < 0x61e700; at += 4)
        g.word(at) = random32();
    // The shapes known: the names asked for first.
    for (x86::reg32 i = 0; i < 24; ++i)
    {
        for (x86::reg32 c = 0; c < 4; ++c)
            g.getMemory<char>(0x8b48c0 + 0x14 * i + 0x10 + c) = kBtnShapeNames[i][c];
        feString(g, btnName(i), kBtnShapeNames[i]);
    }
    g.word(0x8b7628) = 24 + below(4);
    for (x86::reg32 block = 0; block < 8; ++block)
    {
        g.word(kBlocks + 0x400 * block) = 0x78 + below(7);
        g.word(kBlocks + 0x400 * block + 4) = (1 + below(15)) | (1 + below(15)) << 16;
        g.word(kBlocks + 0x400 * block + 0x20) = kBlocks + 0x400 * below(8);
    }
    // Strings: the image's art's kinds, the buttons' styles' names.
    static const char* const more[] = {"LL1of1", "LL3of3", "art.fsh", "\x01x.fsh"};
    for (x86::reg32 i = 0; i < 4; ++i)
        feString(g, btnName(24 + i), more[i]);
    for (x86::reg32 i = 0; i < 6; ++i)
        aMenuText(g, kBtnTexts + 0x20 * i, 0x18);
    // The language's text: its lines' offsets, to 16 texts after them.
    g.word(0x563a80) = kBuffers;
    for (x86::reg32 i = 0; i < 0x7a7; ++i)
        g.word(kBuffers + 4 * i) = 0x1ea0 + 0x20 * (i % 16);
    for (x86::reg32 i = 0; i < 16; ++i)
        aMenuText(g, kBuffers + 0x1ea0 + 0x20 * i, 0x18);
    // The buttons' styles (0x40 bytes each from 0x559fe4): a name, offsets,
    // their shapes' names (known, or none), colours.
    for (x86::reg32 s = 0; s < 0x11; ++s)
    {
        const x86::reg32 at = 0x559fe4 + 0x40 * s;
        g.word(at) = s < 0x10 || chance(50) ? btnName(below(26)) : 0;
        for (x86::reg32 o = 4; o < 0x40; o += 4)
            g.word(at + o) = chance(70) ? below(40) - 10 : random32() % 0x200;
        for (const x86::reg32 o : {0xcu, 0x10u, 0x18u})
            g.word(at + o) = chance(20) ? 0 : btnName(below(20));
        g.word(at + 0x14) = chance(30) ? 0xff : below(0x100);
    }
    g.word(0x559fe4 + 0x40 * 0x10) = 0;
    // The races' places, the screens' modes, the network.
    for (x86::reg32 i = 0; i < 12; ++i)
    {
        g.getMemory<x86::reg16>(0x559c6c + 4 * i) = btnWord(640);
        g.getMemory<x86::reg16>(0x559c94 + 4 * i) = btnWord(480);
    }
    g.word(0x66296c) = chance(30) ? 9 : below(12);
    g.word(0x559c68) = chance(70) ? 0 : 1;
    g.word(0x662968) = chance(50) ? 0 : 1;
    // The tracks' and the cars' tables the images read: names known.
    for (x86::reg32 i = 0; i < 0x40; ++i)
    {
        g.word(0x559fb0 + 4 * i) = btnName(below(20));
        g.word(0x559cbc + 4 * i) = btnName(below(20));
        g.word(0x559644 + 4 * i) = kBtnTexts;
        g.word(0x559668 + 4 * i) = random32();
        g.word(0x55968c + 4 * i) = random32();
    }
    g.word(0x6fd4ac) = below(9);
    g.word(0x678870) = chance(50) ? g.word(0x6fd4ac) : below(9);
    for (const x86::reg32 at : {0x678800u, 0x678860u, 0x6787f8u, 0x678858u, 0x678808u, 0x678868u})
        g.word(at) = below(4);
    g.word(0x559228) = kBlocks + 0x400 * below(8);
    // The cars: classes, the player's.
    g.word(0x6fd328) = below(30);
    g.word(0x6fd2bc) = below(30);
    g.word(0x6fd4b4) = below(10);
    g.word(0x6fd470) = below(3);
    g.word(0x6fd2b0) = random32();
    // The select list's double click, the lists' scrolling.
    for (x86::reg32 at = 0x55a424; at < 0x55a438; at += 4)
        g.word(at) = g.word(0x79c1a4) - below(0x100);
    g.word(0x55a430) = below(3);
    g.word(0x664658) = chance(50) ? 0 : 1;
    // The screen's record (kButtonsScreen) and its items: some, then none.
    g.getMemory<x86::reg16>(kBtnScreen + 0x18) = x86::reg16(below(3));
    for (x86::reg32 n = 0; n < 8; ++n)
        g.word(0x604ee0 + 0xbc * n) = n < 3 + below(4) ? random32() | 1 : 0;
    // The network games found, the select list of the screen.
    g.word(0x5f3ff0) = kBtnGames;
    g.getMemory<x86::reg16>(kBtnGames) = x86::reg16(chance(80) ? 1 + below(5) : 0);
    g.word(kBtnGames + 4) = kBtnGames + 0x20;
    g.word(0x5556c8) = kBtnItem;
    // The track's map.
    g.word(0x559818) = below(7) - 1;
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        g.getMemory<x86::reg16>(0x677d4e + 2 * i) = btnWord(640);
        g.getMemory<x86::reg16>(0x677d56 + 2 * i) = btnWord(480);
        g.getMemory<x86::reg16>(0x677d5e + 2 * i) = btnWord(480);
        g.getMemory<x86::reg16>(0x677d66 + 2 * i) = btnWord(640);
        g.getMemory<x86::reg16>(0x677d6e + 2 * i) = chance(30) ? 0 : aBtnShape();
    }
    for (const x86::reg32 at : {0x677d40u, 0x677d42u, 0x677d44u, 0x677d46u, 0x677d90u, 0x677d92u})
        g.getMemory<x86::reg16>(at) = aBtnShape();
    for (x86::reg32 i = 0; i < 9; ++i)
    {
        g.getMemory<x86::reg16>(0x5596b0 + 2 * i) = btnWord(640);
        g.getMemory<x86::reg16>(0x5596c2 + 2 * i) = btnWord(480);
        g.word(0x5597f4 + 4 * i) = below(6);
    }
    // The map's step: 0 to 2 (past them the code reads a float of its frame
    // it never set, which differs between the generated code's stack and the
    // port's under drawGlow's other calls).
    g.word(0x677d7c) = below(3);
    static const x86::reg32 alongs[] = {0, 0x3c, 0x100, 0x14, 0xc};
    g.word(0x677d78) = chance(40) ? alongs[below(5)] : below(0x120);
    g.word(0x677d8c) = chance(80) ? g.word(0x6fd4ac) : below(9);
    g.word(0x677d80) = chance(30) ? 0 : kBlocks;
    g.word(0x559820) = chance(70) ? 0 : 1;
    g.word(0x559824) = below(0x1000);
    g.word(0x55981c) = below(0x400) - 0x100;
    g.word(0x559fdc) = below(0x200);
    g.word(0x559fe0) = g.word(0x79c1a4) + below(16) - 8;
    g.word(0x55574c) = below(0x400) - 0x100;
    // Not on the license's screen's wait.
    g.word(0x5f40c4) = 0;
    if (x86::sreg32(g.word(0x79c1a4)) < 5)
        g.word(0x79c1a4) = 5 + below(0x10000);
    g.word(0x5f40c0) = below(4);
    g.word(0x555c34) = below(4);
    for (x86::reg32 i = 0; i < 4; ++i)
        g.word(0x555758 + 0x10 * i) = below(3);
    g.word(0x555c2c) = below(500) - 100;
    g.word(0x555c38) = chance(50) ? 0 : aBtnShape();
    g.word(0x66108c) = aBtnShape();
    for (const x86::reg32 at : {0x5f3ff4u, 0x5f3ff6u, 0x5f3ff8u, 0x5f4004u})
        g.getMemory<x86::reg16>(at) = chance(30) ? 0 : aBtnShape();
    g.word(0x555748) = chance(50) ? 0 : 1;
    g.word(0x5f3fcc) = chance(70) ? 0x251 + below(0x40) : below(0x251);
    // The item: random words, its place, box, shapes and strings sane.
    for (x86::reg32 at = kBtnItem; at < kBtnItem + 0xc0; at += 4)
        g.word(at) = random32();
    setBtnHalf(g, kBtnItem + 6, btnWord(640));
    setBtnHalf(g, kBtnItem + 8, btnWord(480));
    setBtnHalf(g, kBtnItem + 0x1a, btnWord(480));
    setBtnHalf(g, kBtnItem + 0x1c, btnWord(640));
    setBtnHalf(g, kBtnItem + 0x1e, btnWord(400));
    setBtnHalf(g, kBtnItem + 0x20, btnWord(300));
    g.word(kBtnItem + 0x10) = kFeNames + 0x10 * below(6);
    g.word(kBtnItem + 0x3c) = chance(10) ? 0 : kBtnTexts + 0x20 * below(6);
}

/* A list's name: of the table's mostly, none of them, an empty one, none. */
x86::reg32 aBtnListName()
{
    return chance(5) ? 0 : kFeNames + 0x10 * below(4);
}

/* A key: Enter, Escape, the arrows, the pages, anything. */
x86::reg32 aBtnKey()
{
    static const x86::reg32 keys[] = {0xd, 0x1b, 0x4b00, 0x4d00, 0x4800, 0x5000, 0x4900, 0x5100};
    return (random32() & 0xffff0000) | (chance(90) ? keys[below(8)] : random32() & 0xffff);
}

/* A list's words: chosen, most, shown, first, last -- at `chosen` on, in
 * that order but for the shown before the first. */
void btnListWords(CheckApp& g, x86::reg32 chosen, x86::reg32 most, x86::reg32 shown, x86::reg32 first,
                  x86::reg32 last)
{
    setBtnHalf(g, chosen, chance(85) ? below(0x40) - 4 : random32());
    setBtnHalf(g, most, chance(90) ? (chance(20) ? 0 : 1 + below(12)) : random32());
    setBtnHalf(g, shown, chance(90) ? 1 + below(12) : random32());
    const x86::reg16 f = x86::reg16(chance(85) ? below(0x38) : random32());
    setBtnHalf(g, first, f);
    setBtnHalf(g, last, chance(80) ? f + below(12) : random32());
}

bool makeButtonsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    makeButtonsWorld(g, cpu, a);
    const x86::reg32 it = kBtnItem;
    cpu.eax = it;
    cpu.edx = chance(50) ? 0 : chance(80) ? 1 : random32();
    cpu.ebx = aBtnKey();
    const auto shapes = [&](x86::reg32 from, x86::reg32 to) {
        for (x86::reg32 at = from; at < to; at += 2)
            setBtnHalf(g, at, aBtnShape());
    };
    if (name == "listColours" || name == "listAllowed" || name == "listLength" || name == "findList")
    {
        cpu.eax = aBtnListName();
        cpu.edx = kFeOut + 4 * below(4);
    }
    else if (name == "loadShapes")
    {
        static const char* const files[] = {"hud.fsh", "art\\hud.fsh", "front.fsh", "art\\GeHud.fsh", "hud.fshx",
                                            "fedata\\art\\hud.fsh"};
        const x86::reg32 i = below(6);
        feString(g, kFeName, files[i]);
        if (chance(30))
            feString(g, 0x662850, files[i]);
        cpu.eax = kFeName;
    }
    else if (name == "joinListedGame")
        g.word(it + 0x4c) = below(4);
    else if (name == "menuEdited")
        cpu.eax = below(64);
    else if (name == "drawReadyMarks")
    {
        cpu.eax = below(640);
        cpu.edx = below(480);
    }
    else if (name == "networkLeft")
    {
        if (g.word(0x555748) != 0 && g.word(0x5f3fcc) < 0x251)
            g_mostCalls = 1 + below(12);
    }
    else if (name == "drawColouredRectangle")
    {
        cpu.eax = below(640);
        cpu.edx = below(480);
        cpu.ebx = below(640);
        cpu.ecx = below(480);
        for (x86::reg32 i = 0; i < 4; ++i)
            a[i] = random32();
    }
    else if (name == "drawTurnedShape")
    {
        cpu.eax = aBtnShape();
        cpu.edx = below(640);
        cpu.ebx = below(480);
        cpu.ecx = below(200) - 100;
        a[0] = below(0x2000);
        static const float scales[] = {1.0f, 0.5f, 2.0f, 0.75f};
        const float s = chance(90) ? scales[below(4)] : float(below(4000)) / 1000.0f;
        std::memcpy(&a[1], &s, 4);
    }
    else if (name == "trackMapShape")
    {
        cpu.eax = aBtnShape();
        cpu.edx = below(4);
    }
    else if (name.compare(0, 7, "textBox") == 0)
    {
        setBtnHalf(g, it + 0x40, chance(50) ? 0 : 1);
        setBtnHalf(g, it + 0x42, below(20));
        setBtnHalf(g, it + 0x44, 20 + below(300));
        setBtnHalf(g, it + 0x46, 16 + below(200));
        setBtnHalf(g, it + 0x48, below(10));
        setBtnHalf(g, it + 0x4a, below(12) - 2);
        if (g.getMemory<x86::reg16>(it + 0x40) != 0 && name == "textBoxHidden")
            g.word(it + 0x3c) = kBlocks + 0x400 * below(8);
        else if (chance(80))
        {
            aBoxText(g, kTextBox, 0x60);
            g.word(it + 0x3c) = kTextBox;
        }
        static const float sizes[] = {1.0f, 1e-7f, 5e-8f, 2e-7f};
        const float size = sizes[below(4)];
        std::memcpy(&g.word(0x559450), &size, 4);
    }
    else if (name == "rectDraw")
    {
        g.word(it + 0x58) = chance(90) ? below(3) : random32();
        setBtnHalf(g, it + 0x4c, below(300));
        setBtnHalf(g, it + 0x4e, below(200));
        setBtnHalf(g, it + 0x50, below(20));
        g.word(it + 0x54) = chance(50) ? 0 : standInFor(0xfff6c4);
    }
    else if (name.compare(0, 4, "text") == 0)
    {
        setBtnHalf(g, it + 0x40, chance(50) ? 1 : below(3));
        setBtnHalf(g, it + 0x42, below(3));
        setBtnHalf(g, it + 0x44, below(5));
        setBtnHalf(g, it + 0x46, below(10));
        setBtnHalf(g, it + 0x48, below(2));
        setBtnHalf(g, it + 0x4a, chance(90) ? below(6) : random32());
        const float scale = float(below(3000)) / 1000.0f;
        std::memcpy(&g.word(it + 0x4c), &scale, 4);
        if (chance(50))
            g.word(it + 0x4c) = chance(50) ? 0 : 0x80000000;
        g.word(it + 0x50) = chance(50) ? 0 : chance(80) ? aBtnListName() : kFeNames + 0x10 * 5;
    }
    else if (name.compare(0, 5, "image") == 0)
    {
        g.word(it + 0x3c) = chance(10) ? 0 : btnName(chance(70) ? below(20) : 20 + below(3));
        // Shown, an image without a name has no codelink either (a codelink's
        // picture is looked up by its name; none is not among the shapes).
        if (name == "imageShown" && (chance(30) || g.word(it + 0x3c) == 0))
            g.word(it + 0x10) = 0;
        g.word(it + 0x40) = chance(40) ? 0 : btnName(26 + below(2));
        setBtnHalf(g, it + 0x44, chance(10) ? 0 : aBtnShape());
        setBtnHalf(g, it + 0x48, chance(50) ? 0 : below(0x100));
        setBtnHalf(g, it + 0x4a, chance(50) ? 0 : 1);
        setBtnHalf(g, it + 0x4c, chance(30) ? 0 : below(200) - 30);
    }
    else if (name.compare(0, 6, "button") == 0 || name == "layoutMenuItem")
    {
        g.word(it + 0x40) = chance(50) ? 0 : random32();
        g.word(it + 0x44) = chance(20) ? 0 : btnName(chance(70) ? below(26) : 24 + below(2));
        static const x86::reg16 styles[] = {0, 1, 2, 3, 0xf, 4};
        setBtnHalf(g, it + 0x48, chance(95) ? styles[below(6)] : below(0x10));
        setBtnHalf(g, it + 0x4a, below(10));
        shapes(it + 0x4c, it + 0x52);
        setBtnHalf(g, it + 0x52, chance(30) ? 0 : below(200) - 30);
        setBtnHalf(g, it + 0x56, below(4));
        g.word(it + 0x58) = chance(40) ? 0 : aBtnListName();
        setBtnHalf(g, it + 0x5c, below(4));
        setBtnHalf(g, it + 0x5e, below(100) - 20);
        setBtnHalf(g, it + 0x60, btnWord(640));
        setBtnHalf(g, it + 0x62, btnWord(480));
        g.word(it + 0x64) = chance(50) ? 0 : standInFor(0xfff6c0);
    }
    else if (name.compare(0, 7, "cascade") == 0)
    {
        setBtnHalf(g, it + 0x40, below(10));
        setBtnHalf(g, it + 0x42, chance(50) ? 0 : 1);
        setBtnHalf(g, it + 0x44, chance(70) ? 0 : 1);
        shapes(it + 0x46, it + 0x52);
        btnListWords(g, it + 0x52, it + 0x54, it + 0x56, it + 0x58, it + 0x5a);
        shapes(it + 0x5c, it + 0x60);
        g.word(it + 0x60) = aBtnListName();
        if (name == "cascadeLineText")
        {
            const x86::reg32 list = below(3);
            cpu.edx = kBtnOut;
            cpu.ebx = kFeLines + 0x80 * list;
            cpu.ecx = kFeChosen + 4 * list;
            g.word(it + 0x60) = chance(60) ? btnName(below(28)) : aBtnListName();
            static const char* const kinds[] = {"opcars", "car2", "cars", "tracks"};
            feString(g, kFeNames + 0x10 * 5, kinds[below(4)]);
            if (chance(70))
                g.word(it + 0x60) = kFeNames + 0x10 * 5;
        }
        else if (chance(40))
        {
            // The tracks' list itself, in the lists' table.
            feString(g, kFeNames + 0x10 * 5, chance(70) ? "tracks" : "rectrk");
            g.word(0x5563e8) = kFeNames + 0x10 * 5;
            g.word(it + 0x60) = kFeNames + 0x10 * 5;
        }
    }
    else if (name.compare(0, 8, "checkbox") == 0 || name == "boxOverlayDraw")
    {
        setBtnHalf(g, it + 0x40, chance(50) ? 0 : 1);
        g.getMemory<x86::reg8>(it + 0x42) = x86::reg8(chance(50) ? 0 : 1);
    }
    else if (name.compare(0, 10, "selectList") == 0)
    {
        const x86::reg32 count = chance(15) ? 0 : 1 + below(12);
        g.word(it + 0x40) = chance(50) ? 0 : kBtnTexts;
        g.word(it + 0x48) = count;
        g.word(it + 0x4c) = chance(90) ? below(14) : random32();
        setBtnHalf(g, it + 0x50, chance(10) ? 0 : 1 + below(10));
        setBtnHalf(g, it + 0x52, below(10));
        setBtnHalf(g, it + 0x54, below(12) - 1);
        setBtnHalf(g, it + 0x56, below(14));
        shapes(it + 0x58, it + 0x60);
        for (x86::reg32 i = 0; i < 16; ++i)
        {
            g.word(kBtnLines + 8 * i) = kBtnTexts + 0x20 * below(6);
            g.word(kBtnLines + 8 * i + 4) = random32();
        }
        g.word(it + 0x70) = count == 0 && chance(30) ? 0 : name == "selectListHidden" ? kBlocks + 0x400 * below(8) : kBtnLines;
        g.word(it + 0x74) = chance(50) ? 0 : standInFor(0xfff6c8);
        // The pointer on its lines or arrows now and then.
        if (chance(50))
        {
            g.word(0x55e5e4) = g.getMemory<x86::reg16>(it + 0x1c) + below(220);
            g.word(0x55e5e8) = g.getMemory<x86::reg16>(it + 0x1a) + below(220);
        }
    }
    else if (name.compare(0, 8, "dropList") == 0 || name == "listKey" || name == "layoutList")
    {
        setBtnHalf(g, it + 0x40, chance(50) ? 0 : 1);
        shapes(it + 0x42, it + 0x52);
        setBtnHalf(g, it + 0x52, chance(50) ? 0 : 1);
        setBtnHalf(g, it + 0x54, chance(50) ? 0 : 1);
        btnListWords(g, it + 0x56, it + 0x58, it + 0x5a, it + 0x5c, it + 0x5e);
        shapes(it + 0x60, it + 0x64);
        g.word(it + 0x64) = aBtnListName();
        if (chance(30))
        {
            setBtnHalf(g, it + 6, 0x65);
            setBtnHalf(g, it + 8, 0x45);
        }
        static const char* const kinds[] = {"opcars", "cars", "tracks", "rectrk"};
        feString(g, kFeNames + 0x10 * 5, kinds[below(4)]);
        if (chance(40))
        {
            g.word(0x5563e8) = kFeNames + 0x10 * 5;
            g.word(it + 0x64) = kFeNames + 0x10 * 5;
        }
    }
    return true;
}
#endif
