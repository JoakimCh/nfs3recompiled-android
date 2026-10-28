// game_checks.cpp's parts for the port's 2D drawing (src/nfs3hp/port_draw2d.cpp,
// nfs3hp::port::draw2d), included in each table with the macro naming the part.
// The world is the menus' drawing's (frontend_draw.inc's makeFeDrawWorld), and
// the cases of the functions that were frontend::'s before are made as they were.
#if defined(DRAW2D_WINDOWS)
// {from, to}, -- what the functions write, compared
// The menu shapes known, their tiles, the 2D screens' font's squares and place.
{0x8b4000, 0x8b8000},
#elif defined(DRAW2D_PROMISES)
// {"port::draw2d::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax, esi, edi, ebp, esp; the x87's stack, its live registers and its words.
{"port::draw2d::quadOutcodes", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawShadedRectangle", true, true, 0, true, kNoHeap, true},
{"port::draw2d::gradientRectangle", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawShadedBox", true, true, 0, true, kNoHeap, true},
{"port::draw2d::filledRectangle", true, true, 0, true, kNoHeap, true},
{"port::draw2d::frame", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawPanel", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawFieldBox", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawTileRectangle", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawLine", true, true, 0, true, kNoHeap, true},
{"port::draw2d::fontCharacter", true, true, 0, true, kNoHeap, true},
{"port::draw2d::accentedCharacter", true, true, 0, true, kNoHeap, true},
{"port::draw2d::buildScreenFont", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawScreenCharacter", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawTurnedCharacter", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawTurnedText", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawTitleText", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawScreenText", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawPointer", true, true, 0, true, kNoHeap, true},
{"port::draw2d::startScreens", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawTexturedQuad", true, true, 0, true, kNoHeap, true},
{"port::draw2d::drawShadedQuad", true, true, 0, true, kNoHeap, true},
#elif defined(DRAW2D_ARGUMENTS)
/* A colour: any, now and then the menus' highlight or its turned text's. */
x86::reg32 aDraw2dColour()
{
    return chance(10) ? 0xff000000 | 0xffe440 : chance(5) ? 0x1ffe43f : random32();
}

/* The 2D screens' font as the font's maker leaves it in the middle: its
 * place, its rows, its accented characters by language. */
void makeDraw2dFont(CheckApp& g)
{
    g.word(0x8b7618) = chance(90) ? below(0x100) : random32();
    g.word(0x8b7614) = below(0x100);
    g.word(0x564178) = chance(90) ? below(0x40) : random32();
    g.word(0x56417c) = chance(90) ? below(0x40) : random32();
    for (x86::reg32 i = 0; i < 6; ++i)
    {
        const x86::reg32 text = kFeTexts + 0x200 + 0x10 * i;
        aMenuText(g, text, 8);
        g.word(0x564160 + 4 * i) = text;
    }
    g.word(0x6fbb4c) = chance(90) ? below(7) : random32();
    g.getMemory<x86::reg8>(0x565010) = x86::reg8(chance(50) ? 8 : below(0x20));
    g.word(0x8b7620) = below(4);
}

/* The menus' pointer: its kind (-2 none), picture, the clock it last moved
 * on, whether the pointers are loaded, the pictures' textures (none now and
 * then) and hot spots. */
void makeDraw2dPointer(CheckApp& g)
{
    g.word(0x563d3c) = chance(10) ? x86::reg32(0) - 2 : below(4);
    g.word(0x563d48) = chance(95) ? below(10) : random32() % 0x20;
    g.word(0x563d44) = g.word(0x79c1a4) - below(8);
    g.word(0x8b7630) = chance(10) ? 0 : 1;
    for (x86::reg32 at = 0x563b34; at < 0x563b34 + 40 * 5; at += 4)
        g.word(at) = chance(15) ? 0 : random32();
    for (x86::reg32 at = 0x563d4c; at < 0x563d4c + 80 * 5; at += 4)
        g.word(at) = below(32);
}

bool makeDraw2dArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    // The functions that were frontend::'s: their cases as frontend_draw.inc makes them.
    static const char* const before[] = {"quadOutcodes", "gradientRectangle", "filledRectangle", "frame",
                                         "accentedCharacter", "drawScreenCharacter", "drawScreenText",
                                         "drawTexturedQuad", "drawShadedQuad"};
    if (std::find_if(std::begin(before), std::end(before), [&](const char* n) { return name == n; })
        != std::end(before))
        return makeFeDrawArguments(g, name, cpu, stack);
    static const char* const names[] = {
        "drawShadedRectangle", "drawShadedBox", "drawPanel", "drawFieldBox", "drawTileRectangle", "drawLine",
        "fontCharacter", "buildScreenFont", "drawTurnedCharacter", "drawTurnedText", "drawTitleText",
        "drawPointer", "startScreens"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeFeDrawWorld(g, cpu);
    makeDraw2dFont(g);
    for (x86::reg32 i = 0; i < 4; ++i)
        aMenuText(g, kFeTexts + 0x40 * i, 0x30);
    if (name == "drawShadedRectangle" || name == "drawLine")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = aScreenX();
        cpu.ecx = aScreenY();
        for (x86::reg32 i = 0; i < 4; ++i)
            stack[i] = aDraw2dColour();
    }
    else if (name == "drawShadedBox" || name == "drawPanel" || name == "drawFieldBox")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = below(300);
        cpu.ecx = below(200);
        for (x86::reg32 i = 0; i < 4; ++i)
            stack[i] = aDraw2dColour();
    }
    else if (name == "drawTileRectangle")
    {
        cpu.eax = chance(90) ? below(12) : chance(50) ? below(100) : random32() % 0x1000;
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
        cpu.ecx = aScreenX();
        stack[0] = aScreenY();
        stack[1] = aDraw2dColour();
        stack[2] = aDraw2dColour();
    }
    else if (name == "fontCharacter")
    {
        cpu.eax = kFeTexts + below(4);
        cpu.edx = chance(90) ? below(0x100) : random32() % 0x200;
    }
    else if (name == "drawTurnedCharacter")
    {
        cpu.eax = below(0x100);
        cpu.edx = below(0x100);
        cpu.ebx = aScreenX();
        cpu.ecx = aScreenY();
        stack[0] = chance(95) ? below(0x20) : random32() % 0x100 - 0x80;
        stack[1] = chance(95) ? below(0x20) : random32() % 0x100 - 0x80;
        stack[2] = aDraw2dColour();
        stack[3] = below(0x100);
        stack[4] = chance(80) ? 0 : 1;
        stack[5] = chance(80) ? below(0x800) - 0x400 : random32();
        stack[6] = chance(90) ? feFloat(float(below(4000)) / 1000.0f) : random32();
    }
    else if (name == "drawTurnedText")
    {
        cpu.eax = kFeTexts + 0x40 * below(4);
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
        stack[0] = chance(90) ? feFloat(float(below(4000)) / 1000.0f) : random32();
        stack[1] = chance(80) ? below(0x800) - 0x400 : random32();
        stack[2] = aDraw2dColour();
    }
    else if (name == "drawTitleText")
    {
        cpu.eax = kFeTexts + 0x40 * below(4);
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
        cpu.ecx = chance(30) ? 0 : chance(80) ? 1 : random32();
        g.word(0x564184) = chance(90) ? below(0xc0) - 0x20 : random32();
        g.getMemory<x86::reg8>(0x7a3a58) = x86::reg8(chance(70) ? random32() & ~6u : random32());
    }
    else if (name == "drawPointer")
        makeDraw2dPointer(g);
    else if (name == "buildScreenFont" || name == "startScreens")
    {
        // The font's two .ffn files, their characters: a few hundred calls.
        g_mostCalls = 800;
        // The bitmap EA's stand-in hands back is a record of the graphics'
        // window (kRecord): its shape (+0x20) one of the window's corners, a
        // shape's header as graphics::shapeTexture reads it.
        for (x86::reg32 record = 0; record < 64; ++record)
            g.word(0xc00000 + 0x40 * record + 0x20) = 0xc01000 + 0x40 * below(64);
        for (x86::reg32 corner = 0; corner < 64; ++corner)
        {
            g.word(0xc01000 + 0x40 * corner) = chance(90) ? 0x78 + below(7) : random32();
            g.word(0xc01000 + 0x40 * corner + 4) = below(130) | below(130) << 16;
        }
    }
    if (name == "drawShadedRectangle")
        g.word(0x559234) = chance(30);
    return true;
}
#endif
