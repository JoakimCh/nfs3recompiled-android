// game_checks.cpp's parts for the menus' text and the 2D drawing under it, rewritten
// (src/nfs3hp/port_text.cpp, port::text), included in each table with the macro naming the part.
#if defined(TEXT_WINDOWS)
// {from, to}, -- what the functions write, compared
// The fonts' lists' vertices and vertex numbers (0x7f74c0 and 0x81b4d0, at
// 0x10 and 0x20010 each), as far as the cases' lists reach.
{0x7f8000, 0x7fb000}, {0x81c000, 0x81f000}, {0x817000, 0x818000}, {0x83b000, 0x83c000},
#elif defined(TEXT_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kTextKeyState,  // GetKeyState: a key up mostly, down (the top bit) now and then
#elif defined(TEXT_EFFECT_CASES)
// case kSomething: ... break;
case kTextKeyState:
    result = r % 3 == 0 ? 0xffff8000 | (r >> 8) % 2 : (r >> 8) % 2;
    break;
#elif defined(TEXT_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// This file's that the other natives call by address, as they keep to their
// conventions: the language's line (a string back); a text drawn, a text's
// width, both onto the x87's stack; a character's height in eax; the fonts'
// quads drawn; the text scale set (stdcall, the last onto the x87's stack:
// restoreTextScale pops it right after); the background dimmed; a menu's
// text drawn (logged); a list's quads drawn; a quad queued.
{0x4d1850, "languageText", kWatcom, 4, 0, kEax, -1, 0, kString},
{0x4d1000, "a text drawn", kWatcom, 3, 0, kEax, -1, 0, kFloatBack},
{0x4d1480, "a text's width", kWatcom, 1, 0, kEax, -1, 0, kFloatBack},
{0x4d1540, "a font's height", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4d1340, "the fonts' quads drawn", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d1390, "the text scale set", kStdcall, 0, 1, 0, -1, 0, kFloatBack},
{0x451530, "the background dimmed", kStdcall, 0, 1, kEax, -1, 0, kNothing},
{0x452190, "a menu text drawn", kStdcall, 4, 2, kScratch, 0, 4, kNothing},
{0x49be40, "the font's quads drawn", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x49bd30, "quads drawn", kStdcall, 4, 1, kEax | kEbx | kEcx | kEdx, -1, 0, kNothing},
#elif defined(TEXT_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// GetKeyState, whether Enter or Escape is still held (the menus' key).
{0x534738, "GetKeyState", kStdcall, 0, 1, kScratch, -1, 0, kTextKeyState},
#elif defined(TEXT_PROMISES)
// {"port::text::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax and the registers the port keeps; the x87's stack, its live registers,
// its words.
{"port::text::textWidth", true, true, 0, true, kNoHeap, true},
{"port::text::selectFont", true, true, 0, true, kNoHeap, true},
{"port::text::measureText", true, true, 0, true, kNoHeap, true},
{"port::text::textWidthWithOverhang", true, true, 0, true, kNoHeap, true},
{"port::text::drawText", true, true, 0, true, kNoHeap, true},
{"port::text::drawCharacter", true, true, 0, true, kNoHeap, true},
{"port::text::takeQuad", true, true, 0, true, kNoHeap, true},
{"port::text::viewport", true, true, 0, true, kNoHeap, true},
{"port::text::toScreenX", true, true, 0, true, kNoHeap, true},
{"port::text::toScreenY", true, true, 0, true, kNoHeap, true},
{"port::text::specialText", true, true, 0, true, kNoHeap, true},
{"port::text::languageText", true, true, 0, true, kNoHeap, true},
{"port::text::flushFonts", true, true, 0, true, kNoHeap, true},
{"port::text::setTextScale", true, true, 0, true, kNoHeap, true},
{"port::text::keepTextScale", true, true, 0, true, kNoHeap, true},
{"port::text::restoreTextScale", true, true, 0, true, kNoHeap, true},
{"port::text::characterWidth", true, true, 0, true, kNoHeap, true},
{"port::text::characterOverhang", true, true, 0, true, kNoHeap, true},
{"port::text::setTextColour", true, true, 0, true, kNoHeap, true},
{"port::text::screenToMenuX", true, true, 0, true, kNoHeap, true},
{"port::text::screenToMenuY", true, true, 0, true, kNoHeap, true},
{"port::text::readMenuMouse", true, true, 0, true, kNoHeap, true},
{"port::text::dimBackground", true, true, 0, true, kNoHeap, true},
{"port::text::drawTextAt", true, true, 0, true, kNoHeap, true},
{"port::text::drawMenuText", true, true, 0, true, kNoHeap, true},
{"port::text::flushQuads", true, true, 0, true, kNoHeap, true},
{"port::text::joystickKey", true, true, 0, true, kNoHeap, true},
{"port::text::captureKeys", true, true, 0, true, kNoHeap, true},
{"port::text::scanCodeOfKey", true, true, 0, true, kNoHeap, true},
{"port::text::keyOfScanCode", true, true, 0, true, kNoHeap, true},
{"port::text::menuKey", true, true, 0, true, kNoHeap, true},
{"port::text::resetMenuKey", true, true, 0, true, kNoHeap, true},
{"port::text::nextWord", true, true, 0, true, kNoHeap, true},
{"port::text::drawWrappedText", true, true, 0, true, kNoHeap, true},
{"port::text::drawTextBox", true, true, 0, true, kNoHeap, true},
{"port::text::measureTextBox", true, true, 0, true, kNoHeap, true},
{"port::text::menusEnd", true, true, 0, true, kNoHeap, true},
{"port::text::queueQuad", true, true, 0, true, kNoHeap, true},
{"port::text::unqueueQuad", true, true, 0, true, kNoHeap, true},
{"port::text::mouseMenuKey", true, true, 0, true, kNoHeap, true},
{"port::text::loadLanguageText", true, true, 0, true, kNoHeap, true},
#elif defined(TEXT_HOOKS)
/* nfs3hp_main.cpp's HUD editor measuring each quad queued
 * (tools/apply_hud_editor.py, at sub_49bd30's start, which generate.py makes
 * to the game's code too): logged as a call out, on both sides. */
void nfs3hp::hudQueueQuad(win32::WinApplication* app, x86::reg32 list, x86::reg32 a, x86::reg32 b, x86::reg32 c,
                          x86::reg32 d)
{
    static_cast<win32::CheckApp*>(app)->calls.push_back({0xfffe40, {list, a, b, c, d}});
}
#elif defined(TEXT_ARGUMENTS)
/* Where the text's cases keep their own: a text in a box, where its widest
 * line, its height and its lines go, a word taken. */
constexpr x86::reg32 kTextBox = kTexts, kTextOut = kBuffers + 0x1000, kTextWord = kBuffers + 0x1100;

/* A text for a box at `at`: words of the font's characters (up to 40: the
 * game's code takes a word into 100 bytes of its frame), between them spaces
 * and tabs, now and then a line's end (
,  and a character), never one
 * on its own at the end -- nor a bare 
, at which the game's code would take
 * no word and go round for ever. */
void aBoxText(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    x86::reg32 n = 0;
    const x86::reg32 length = chance(5) ? 0 : 1 + below(most);
    bool word = chance(80);
    while (n < length)
    {
        if (word)
        {
            for (x86::reg32 i = 1 + below(chance(90) ? 10 : 40); i > 0 && n < length; --i)
                g.getMemory<x86::reg8>(at + n++) = x86::reg8(chance(95) ? 0x21 + below(0x5e) : 0x80 + below(0x80));
        }
        else if (chance(85) || n + 2 >= length)
        {
            for (x86::reg32 i = 1 + below(3); i > 0 && n < length; --i)
                g.getMemory<x86::reg8>(at + n++) = x86::reg8(chance(80) ? 0x20 : 9);
        }
        else
        {
            g.getMemory<x86::reg8>(at + n++) = 0xd;
            g.getMemory<x86::reg8>(at + n++) = x86::reg8(chance(60) ? 0xa : chance(20) ? 9 : 0x21 + below(0x5e));
        }
        word = !word;
    }
    g.getMemory<x86::reg8>(at + n) = 0;
}

/* A font's list of quads: its texture's state, its next free vertex, its
 * vertex numbers queued (four a quad, most often), small mostly. */
x86::reg32 aQuadList(CheckApp& g)
{
    const x86::reg32 list = 0x7f74c0 + 0x24010 * below(2);
    g.word(list) = random32();
    g.word(list + 4) = chance(90) ? below(0x40) : random32();
    g.word(list + 0xc) = chance(10) ? 0 : chance(90) ? 4 * below(0x10) : below(0x40);
    for (x86::reg32 i = 0; i < 0x48; ++i)
        g.word(list + 0x20010 + 4 * i) = chance(90) ? below(0x40) : random32();
    return list;
}

/* The fonts' lists as the game keeps them: few vertex numbers queued and
 * room for a text's vertices, so that the characters drawn -- queued now, as
 * the game's code queues them, where the frontend's natives handed them to a
 * stand-in -- stay in the list (past its first vertex they would overwrite
 * its head, the game's code as much as the port's). */
void saneQuadLists(CheckApp& g)
{
    for (x86::reg32 font = 0; font < 2; ++font)
    {
        const x86::reg32 list = 0x7f74c0 + 0x24010 * font;
        g.word(list + 0xc) = chance(90) ? 4 * below(0x10) : below(0x40);
        g.word(list + 4) = 0x80 + below(0x100);
    }
}

bool makeTextArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    // Those that were the frontend's natives: the worlds and arguments their
    // cases had there.
    if (makeMenusArguments(g, name, cpu, stack))
    {
        saneQuadLists(g);
        return true;
    }
    if (name == "specialText" || name == "languageText")
    {
        makeFrontendArguments(g, name, cpu, stack);
        return true;
    }
    if (makeFeGlueArguments(g, name, cpu, stack) || makeFeDrawArguments(g, name, cpu, stack))
    {
        if (name != "flushQuads")
            saneQuadLists(g);
        return true;
    }
    static const char* const names[] = {
        "joystickKey", "captureKeys", "scanCodeOfKey", "keyOfScanCode", "menuKey", "resetMenuKey", "nextWord",
        "drawWrappedText", "drawTextBox", "measureTextBox", "menusEnd", "queueQuad", "unqueueQuad",
        "mouseMenuKey", "loadLanguageText"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    if (name == "menuKey")
    {
        // The click's sound: its world as the sound's cases have it.
        makeSoundArguments(g, "playMenuEffect", cpu, stack);
    }
    // The menus' (fonts, screen, mouse, keyboard) as the glue's cases have them.
    makeFeGlueWorld(g, cpu);
    saneQuadLists(g);
    static const x86::reg32 keys[] = {0xd, 0x1b, 0x4800, 0x5000, 0x4b00, 0x4d00, 0x48, 0x50, 0x4b, 0x4d, 0x1c,
                                      1, 0, 0x20, 0x7f, 0x1a001b, 0xe007f, 0x1c000d};
    const auto aKey = [&] { return chance(85) ? keys[below(18)] : chance(50) ? below(0x10000) : random32(); };
    // The mouse: there or not, a button clicked, its wheel turned.
    g.word(0x55e600) = chance(30) ? 0 : chance(90) ? 1 : random32();
    g.getMemory<x86::reg8>(0x55e5ed) = x86::reg8(chance(50) ? 0 : chance(50) ? below(0x10) : random32());
    g.word(0x55e5f8) = chance(40) ? 0 : chance(80) ? below(3) - 1 : random32();
    if (name == "scanCodeOfKey" || name == "keyOfScanCode")
        cpu.eax = aKey();
    else if (name == "menuKey")
    {
        // A key held or none, when it repeats first and next, the joystick's
        // turn: about the clock.
        cpu.eax = chance(70) ? 1 : chance(50) ? 0 : random32();
        const x86::reg32 clock = below(0x1000000);
        g.word(0x79c1a4) = clock;
        g.word(0x664648) = chance(30) ? 0 : chance(70) ? keys[below(4)] : aKey();
        g.word(0x664644) = clock + below(0x60) - 0x30;
        g.word(0x559440) = clock + below(0x30) - 0x18;
        g.word(0x55943c) = clock + below(0x60) - 0x30;
    }
    else if (name == "nextWord")
    {
        aBoxText(g, kTextBox, 0x30);
        cpu.eax = kTextBox + (chance(70) ? 0 : below(0x10));
        cpu.edx = kTextWord;
    }
    else if (name == "drawWrappedText" || name == "drawTextBox" || name == "measureTextBox")
    {
        aBoxText(g, kTextBox, chance(80) ? 0x60 : 0x200);
        // The 2D screens' size: 1, or so small that the widths their text
        // stand-in makes up come out within a box's.
        static const float sizes[] = {1.0f, 1e-7f, 5e-8f, 2e-7f};
        const float size = sizes[below(4)];
        std::memcpy(&g.word(0x559450), &size, 4);
        g.word(0x563aa4) = random32();
        for (x86::reg32 at = kTextOut; at < kTextOut + 0x10; at += 4)
            g.word(at) = random32();
        const auto out = [&](x86::reg32 i) { return chance(15) ? 0 : kTextOut + 4 * i; };
        cpu.eax = chance(5) ? 0 : kTextBox;
        cpu.edx = random32();
        cpu.ebx = name == "measureTextBox" ? (chance(90) ? below(400) : random32()) : random32();
        cpu.ecx = name == "measureTextBox" ? out(0) : chance(90) ? below(640) : random32();
        if (name == "measureTextBox")
        {
            stack[0] = out(1);
            stack[1] = out(2);
        }
        else
        {
            stack[0] = chance(90) ? below(480) : random32();
            stack[1] = chance(90) ? below(400) : random32();
            stack[2] = out(0);
            stack[3] = out(1);
            stack[4] = out(2);
            stack[5] = chance(60) ? 0 : chance(80) ? 1 : random32();
            stack[6] = chance(50) ? 0x400 : chance(80) ? below(6) : random32();
            stack[7] = chance(50) ? 0 : chance(80) ? below(6) - 2 : random32();
        }
    }
    else if (name == "queueQuad" || name == "unqueueQuad")
    {
        // A quad: one of those queued now and then, any small numbers else.
        const x86::reg32 list = aQuadList(g);
        cpu.eax = list;
        x86::reg32 quad[4];
        const x86::reg32 queued = g.word(list + 0xc);
        if (chance(50) && x86::sreg32(queued) >= 4 && queued < 0x48)
        {
            const x86::reg32 at = list + 0x20010 + 4 * (4 * below(queued / 4));
            for (x86::reg32 i = 0; i < 4; ++i)
                quad[i] = g.word(at + 4 * i);
            // Now and then all but one of its vertices.
            if (chance(30))
                quad[below(4)] += 1 + below(3);
        }
        else
            for (x86::reg32& n : quad)
                n = chance(90) ? below(0x40) : random32();
        cpu.edx = quad[0];
        cpu.ebx = quad[1];
        cpu.ecx = quad[2];
        stack[0] = quad[3];
    }
    else if (name == "loadLanguageText")
    {
        cpu.eax = chance(80) ? below(7) : chance(50) ? 7 + below(8) : x86::reg32(-1 - x86::sreg32(below(4)));
        g.word(0x563a80) = chance(30) ? 0 : kBlocks + 0x400 * below(8);
    }
    return true;
}
#endif
