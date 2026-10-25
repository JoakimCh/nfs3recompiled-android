// game_checks.cpp's parts for the menus' drawing: their 3D and 2D, text and shapes
// (native_frontend_draw.cpp), included in each table with the macro naming the part.
#if defined(FE_WINDOWS)
// {from, to}, -- what the functions write, compared
// The 2D screens' highlighted line (0x7a1b98); the code's pages with the
// tables the code copies into its frames (0x45ccd0, 0x469020, 0x469040,
// 0x4d5740, 0x4d57c0) and the two-axis slider's switch's (0x46b36c, jumped
// through by esi), which the harness has not loaded: written by makeFeDrawWorld
// as nfs3.exe has them, read only; the harness's own (0x61d000 to 0x620000).
{0x7a1000, 0x7a2000}, {0x45c000, 0x45d000}, {0x469000, 0x46a000}, {0x46b000, 0x46c000}, {0x4d5000, 0x4d6000},
{0x61d000, 0x620000},
#elif defined(FE_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
#elif defined(FE_EFFECT_CASES)
// case kSomething: ... break;
#elif defined(FE_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// This file's functions that the menus' other code calls (frontend_glue's), as
// they keep to their conventions: a menu item laid out; a slider's value set,
// read (onto the x87's stack), the slider drawn (eax 0, edx its own), worked
// by the mouse -- and a two-axis slider's; a .qfs loaded (its name's first 16
// bytes logged; a block back); the fonts' quads drawn; the screen's quads'
// outcodes.
{0x4613e0, "a menu item laid out", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x469480, "a slider's value set", kStdcall, 1, 2, kEax, -1, 0, kNothing},
{0x469520, "a slider's value", kWatcom, 1, 0, 0, -1, 0, kFloatBack},
{0x469680, "a slider drawn", kWatcom, 2, 0, kEax | kEdx, -1, 0, kNothing},
{0x46a5f0, "a slider worked by the mouse", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x46add0, "a two-axis slider's value set", kStdcall, 1, 2, kEax, -1, 0, kNothing},
{0x46afd0, "a two-axis slider's value", kWatcom, 2, 0, 0, -1, 0, kFloatBack},
{0x46b3a0, "a two-axis slider drawn", kWatcom, 2, 0, kEax | kEdx, -1, 0, kNothing},
{0x46c320, "a two-axis slider worked by the mouse", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4d1340, "the fonts' quads drawn", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d5840, "the quads' outcodes", kWatcom, 3, 0, kEax | kEdx | kEbx, -1, 0, kNothing},
// The text scale set (0x4d1390), its last onto the x87's stack: as its ret 4
// has it, stdcall -- game_checks.cpp's row further on (kWatcom, its word left
// on the stack) is shadowed by this one, the first found; drop that at merge.
// restoreTextScale pops ebp right after it.
{0x4d1390, "the text scale set", kStdcall, 0, 1, 0, -1, 0, kFloatBack},
// What they call that has no stand-in: the quad of four vertices clipped and
// drawn (0x4c12e0, the port's vertices' native) -- the vertices, 0x80 bytes
// from eax, logged, as they are in the caller's frame.
{0x4c12e0, "a quad clipped and drawn", kWatcom, 4, 0, kEax | kEbx | kEcx | kEdx, 0, 32, kNothing},
#elif defined(FE_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// A slider's function, told of a change: the slider at eax.
{0xfff200, "a slider's function", kWatcom, 1, 0, kEax, -1, 0, kNothing},
#elif defined(FE_PROMISES)
// {"frontend::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared; the x87's stack, its live registers and its words too.
{"frontend::layoutMenuItem", true, true, 0, true, kNoHeap, true},
{"frontend::sliderPartUnderPointer", true, true, 0, true, kNoHeap, true},
{"frontend::sliderThumbPlace", true, true, 0, true, kNoHeap, true},
{"frontend::snapToStep", true, true, 0, true, kNoHeap, true},
{"frontend::setSliderValue", true, true, 0, true, kNoHeap, true},
{"frontend::sliderStoredValue", true, true, 0, true, kNoHeap, true},
{"frontend::dragSliderTo", true, true, 0, true, kNoHeap, true},
{"frontend::drawSlider", true, true, 0, true, kNoHeap, true},
{"frontend::trackSlider", true, true, 0, true, kNoHeap, true},
{"frontend::twoAxisThumbPlace", true, true, 0, true, kNoHeap, true},
{"frontend::setTwoAxisValue", true, true, 0, true, kNoHeap, true},
{"frontend::twoAxisValue", true, true, 0, true, kNoHeap, true},
{"frontend::dragTwoAxisTo", true, true, 0, true, kNoHeap, true},
{"frontend::drawTwoAxis", true, true, 0, true, kNoHeap, true},
{"frontend::trackTwoAxis", true, true, 0, true, kNoHeap, true},
{"frontend::loadQfs", true, true, 0, true, kNoHeap, true},
{"frontend::flushFonts", true, true, 0, true, kNoHeap, true},
{"frontend::setTextScale", true, true, 0, true, kNoHeap, true},
{"frontend::keepTextScale", true, true, 0, true, kNoHeap, true},
{"frontend::restoreTextScale", true, true, 0, true, kNoHeap, true},
{"frontend::characterWidth", true, true, 0, true, kNoHeap, true},
{"frontend::characterOverhang", true, true, 0, true, kNoHeap, true},
{"frontend::quadOutcodes", true, true, 0, true, kNoHeap, true},
{"frontend::shapeByName", true, true, 0, true, kNoHeap, true},
{"frontend::drawShape", true, true, 0, true, kNoHeap, true},
{"frontend::gradientRectangle", true, true, 0, true, kNoHeap, true},
{"frontend::filledRectangle", true, true, 0, true, kNoHeap, true},
{"frontend::frame", true, true, 0, true, kNoHeap, true},
{"frontend::accentedCharacter", true, true, 0, true, kNoHeap, true},
{"frontend::drawScreenCharacter", true, true, 0, true, kNoHeap, true},
{"frontend::drawScreenText", true, true, 0, true, kNoHeap, true},
{"frontend::drawTexturedQuad", true, true, 0, true, kNoHeap, true},
{"frontend::drawShadedQuad", true, true, 0, true, kNoHeap, true},
#elif defined(FE_ARGUMENTS)
/* Where the drawing's cases keep their own: a slider's record, a menu item,
 * the words their callers hand pointers to, vertices and quads, texts. */
constexpr x86::reg32 kFeSlider = 0x61d000, kFeDrawItem = 0x61d200, kFeWords = 0x61d400;
constexpr x86::reg32 kFeVertices = 0x61d600, kFeQuads = 0x61da00, kFeTexts = 0x61dc00;

/* THRASH's functions by name, as kThrashNames has them (the slots at 0x9ef900
 * on): what the graphics' natives these call reach. */
const char* const kFeThrashNames[] = {
    "_THRASH_drawpointmesh@12", "_THRASH_drawpointstrip@8", "_THRASH_drawlinestrip@8", "_THRASH_drawlinemesh@12",
    "_THRASH_drawpoint@4", "_THRASH_writerect@20", "_THRASH_treset@0", "_THRASH_drawtristrip@8",
    "_THRASH_readrect@20", "_THRASH_drawtrimesh@12", "_THRASH_drawline@8", "_THRASH_clip@16",
    "_THRASH_drawquadmesh@12", "_THRASH_settexture@4", "_THRASH_window@4", "_THRASH_idle@0",
    "_THRASH_pageflip@0", "_THRASH_selectdisplay@4", "_THRASH_sync@4", "_THRASH_drawquad@16",
    "_THRASH_flushwindow@0", "_THRASH_lockwindow@0", "_THRASH_setvideomode@12", "_THRASH_unlockwindow@4",
    "_THRASH_drawtrifan@8", "_THRASH_tupdate@12", "_THRASH_talloc@20", "_THRASH_setstate@8",
    "_THRASH_clearwindow@0", "_THRASH_drawtri@12", "_THRASH_init@0", "_THRASH_restore@0",
    "_THRASH_about@0", "_THRASH_is@0",
};

x86::reg32 feFloat(float f)
{
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

/* A value of a slider's: within 0 and 1 mostly, a little past either end,
 * 0 or 1 exactly. */
x86::reg32 aSliderValue()
{
    return chance(10) ? feFloat(below(2)) : feFloat(float(x86::sreg32(below(1400)) - 200) / 1000.0f);
}

/* A step: a tenth, a quarter, a twentieth, none, past 1, below 0, any. */
x86::reg32 aStep()
{
    static const float steps[] = {0.1f, 0.25f, 0.05f, 0.0f, 1.5f, -0.1f, 0.3333f, 1.0f};
    return chance(90) ? feFloat(steps[below(8)]) : feFloat(float(below(2000)) / 1000.0f - 0.5f);
}

/* A place on the 640 by 480 screen, or past it now and then. */
x86::reg32 aScreenX()
{
    return chance(95) ? below(640) : below(2000) - 1000;
}

x86::reg32 aScreenY()
{
    return chance(95) ? below(480) : below(2000) - 1000;
}

/* A slider's record: its kind (2 the two-axis one's, of 6 parts; the others
 * of 4), its parts' rectangles near each other and the pointer, its values,
 * steps, texts, its function, its state with the mouse. */
void makeSlider(CheckApp& g, bool twoAxis)
{
    for (x86::reg32 at = kFeSlider; at < kFeSlider + 0xc0; at += 4)
        g.word(at) = random32();
    static const x86::reg16 kinds[] = {0, 1, 3, 4, 5};
    const x86::reg16 kind = x86::reg16(chance(95) ? (twoAxis ? 2 : kinds[below(5)]) : below(6));
    g.getMemory<x86::reg16>(kFeSlider + 0x42) = kind;
    g.getMemory<x86::reg16>(kFeSlider + 0x40) = x86::reg16(below(10));
    // The parts: y, x, width, height each -- the track (1) wide, a thumb on it.
    const x86::reg32 left = below(400), top = below(380);
    for (x86::reg32 part = 0; part < 6; ++part)
    {
        const x86::reg32 at = kFeSlider + 0x7c + 8 * part;
        g.getMemory<x86::reg16>(at) = x86::reg16(chance(90) ? top + below(60) : aScreenY());
        g.getMemory<x86::reg16>(at + 2) = x86::reg16(chance(90) ? left + below(200) : aScreenX());
        g.getMemory<x86::reg16>(at + 4) = x86::reg16(chance(95) ? 4 + below(part == 1 || part == 5 ? 220 : 40) : below(700) - 50);
        g.getMemory<x86::reg16>(at + 6) = x86::reg16(chance(95) ? 4 + below(40) : below(500) - 50);
    }
    // The pointer in a part now and then.
    const x86::reg32 part = kFeSlider + 0x7c + 8 * below(6);
    g.word(0x55e5e4) = chance(50) ? g.getMemory<x86::reg16>(part + 2) + below(40) : aScreenX();
    g.word(0x55e5e8) = chance(50) ? g.getMemory<x86::reg16>(part) + below(30) : aScreenY();
    g.word(kFeSlider + 0x44) = aStep();
    g.word(kFeSlider + 0x48) = chance(80) ? feFloat(0.1f) : aStep();
    g.word(kFeSlider + 0x54) = aSliderValue();
    g.word(kFeSlider + 0x58) = aSliderValue();
    g.word(kFeSlider + 0x78) = chance(50) ? standInFor(0xfff200) : 0;
    g.word(kFeSlider + 0xac) = g.word(0x79c1a4) - (chance(80) ? below(0x40) : random32());
    g.getMemory<x86::reg16>(kFeSlider + 0xb0) = x86::reg16(chance(30) ? 0xffff : chance(90) ? below(7) : random32());
    g.getMemory<x86::reg16>(kFeSlider + 0xb2) = x86::reg16(below(4));
    g.getMemory<x86::reg16>(kFeSlider + 0xa) =
        x86::reg16(chance(80) ? g.getMemory<x86::reg16>(kFeSlider + 0xb2) : below(4));
    static const x86::reg8 repeats[] = {2, 3, 0xff, 0};
    g.getMemory<x86::reg8>(kFeSlider + 0xb4) = x86::reg8(chance(95) ? repeats[below(4)] : random32());
    g.getMemory<x86::reg16>(kFeSlider + 0xb6) = x86::reg16(chance(40) ? 0 : chance(80) ? below(0x90) : random32());
    g.getMemory<x86::reg16>(kFeSlider + 0x18) = x86::reg16(chance(50) ? 0 : chance(50) ? 1 : random32());
    g.getMemory<x86::reg8>(kFeSlider + 0x3c) = x86::reg8(chance(60) ? 1 : below(3));
    g.getMemory<x86::reg8>(kFeSlider + 0x3d) = x86::reg8(below(2));
    g.getMemory<x86::reg8>(kFeSlider + 0x3e) = x86::reg8(below(2));
    g.getMemory<x86::reg16>(kFeSlider + 0x1a) = x86::reg16(aScreenY());
    g.getMemory<x86::reg16>(kFeSlider + 0x1c) = x86::reg16(aScreenX());
    g.getMemory<x86::reg16>(kFeSlider + 0x1e) = x86::reg16(below(300));
    g.getMemory<x86::reg16>(kFeSlider + 0x20) = x86::reg16(below(100));
    for (const x86::reg32 text : {0x60u, 0x68u, 0x6cu, 0x70u})
        g.word(kFeSlider + text) = chance(40) ? 0 : aString();
    g.getMemory<x86::reg8>(kFeSlider + 0x74) = x86::reg8(chance(90) ? below(3) : random32());
    g.getMemory<x86::reg8>(kFeSlider + 0x75) = x86::reg8(chance(90) ? below(6) : random32());
}

/* The drawing's world: the menus' fonts and screen (makeMenusWorld), the
 * graphics' driver's functions by name, the code's tables, the clip, the
 * menus' state, the sliders' art, the 2D screens' fonts and quads, the menu
 * shapes known. */
void makeFeDrawWorld(CheckApp& g, x86::CPU& cpu)
{
    makeMenusWorld(g, cpu);
    for (x86::reg32 i = 0; i < sizeof kFeThrashNames / sizeof *kFeThrashNames; ++i)
        g.word(kThrashSlots + 4 * i) = chance(98) ? namedStandIn(kFeThrashNames[i]) : 0;
    // The code's tables: zeros, the quads' vertices' template, the switch.
    for (x86::reg32 at = 0x45ccd0; at < 0x45cdd0; at += 4)
        g.word(at) = 0;
    for (x86::reg32 at = 0x469020; at < 0x469080; at += 4)
        g.word(at) = 0;
    for (const x86::reg32 table : {0x4d5740u, 0x4d57c0u})
        for (x86::reg32 v = 0; v < 4; ++v)
            for (x86::reg32 i = 0; i < 8; ++i)
                g.word(table + 0x20 * v + 4 * i) = i == 2 ? 0x37800080 : i == 3 ? 0x3f7fff00 : 0;
    static const x86::reg32 parts[] = {0x46b49a, 0x46b49a, 0x46b618, 0x46b618, 0x46b79a, 0x46b857};
    for (x86::reg32 i = 0; i < 6; ++i)
        g.word(0x46b36c + 4 * i) = parts[i];
    // The screen's viewport, put back after the 2D screens' clip: a sane one
    // (graphics::setClip's 80-bit arithmetic is the game's only within reason).
    for (x86::reg32 i = 0; i < 4; ++i)
        g.word(0x7cda70 + 4 * i) = i < 2 ? below(64) : 320 + below(1000);
    // The screen, its clip's bounds (floats, as their ints compare).
    g.word(0x7cdac8) = chance(90) ? g.word(0x7cdac8) : below(2000);
    g.word(0x7d34f8) = feFloat(chance(90) ? 1.0f : float(below(100)));
    g.word(0x7d34fc) = feFloat(chance(70) ? 0.0f : float(below(100)));
    g.word(0x7d3504) = feFloat(chance(70) ? 0.0f : float(below(100)));
    g.word(0x7d350c) = feFloat(float(x86::sreg32(g.word(0x7cdac8))) - float(below(2)));
    g.word(0x7d3500) = feFloat(float(x86::sreg32(g.word(0x7cdacc))) - float(below(2)));
    // The menus: their state, the 2D screens sliding in, the clock.
    g.getMemory<x86::reg8>(0x55eb2e) = x86::reg8(random32());
    g.word(0x559c60) = chance(50) ? 0 : chance(70) ? below(500) : random32();
    g.word(0x79c1a4) = random32();
    g.word(0x749a38) = random32();
    g.word(0x559234) = chance(50) ? 0 : chance(90) ? 1 : random32();
    // The sliders' art: each kind's parts' shapes, -1 for none.
    for (x86::reg32 at = 0x678aa0; at < 0x678b40; at += 2)
        g.getMemory<x86::reg16>(at) = x86::reg16(chance(25) ? 0xffff : below(0x40));
    // The 2D screens' fonts: the font, the quad's depth, the highlight's line,
    // colours, the characters' squares, the accented characters.
    static const x86::reg32 fonts[] = {0x24, 0x10, 0xd, 0x12};
    g.word(0x664650) = chance(90) ? fonts[below(4)] : random32();
    g.word(0x563aa8) = feFloat(float(below(1000)) / 1000.0f);
    g.word(0x563aac) = feFloat(float(below(1000)) / 1000.0f);
    g.word(0x563aa0) = chance(50) ? 0 : 1;
    g.word(0x7a1b98) = chance(80) ? below(640) : random32();
    g.word(0x563aa4) = random32();
    g.word(0x559434) = chance(50) ? 0 : random32();
    g.word(0x8b7624) = random32();
    for (x86::reg32 at = 0x8b763c; at < 0x8b7a74; ++at)
        g.getMemory<x86::reg8>(at) = x86::reg8(chance(90) ? below(0x40) : random32());
    const x86::reg32 accents = kFeTexts + 0x300;
    aMenuText(g, accents, 20);
    for (x86::reg32 i = 0; i < 20 && g.getMemory<x86::reg8>(accents + i) != 0; ++i)
        if (chance(50))
            g.getMemory<x86::reg8>(accents + i) = x86::reg8(0xc0 + below(0x40));
    g.word(0x564180) = accents;
    // The fonts' scale.
    g.word(0x840188) = chance(50) ? 0 : 1;
    g.word(0x840190) = feFloat(chance(80) ? 1.0f : float(below(3000)) / 1000.0f);
    g.word(0x561b40) = feFloat(float(below(3000)) / 1000.0f);
    // The menu shapes known: their names, a few.
    g.word(0x8b7628) = chance(90) ? below(12) : 0;
    for (x86::reg32 i = 0; i < 12; ++i)
        for (x86::reg32 c = 0; c < 4; ++c)
            g.getMemory<x86::reg8>(0x8b48c0 + 0x14 * i + 0x10 + c) = x86::reg8('a' + below(3));
    g.word(0x559228) = random32();
    // And what graphics::artShapeTextures makes a new one's textures from, as
    // graphics_world.inc has it: the art's tiles, the shapes' records, a
    // shape's header at the start of each block the allocation hands out.
    g.word(0x8b762c) = chance(10) ? 0x31f - below(4) : below(0x300);
    for (x86::reg32 record = 0; record < 100; ++record)
    {
        const x86::reg32 at = 0x8b48c0 + 0x14 * record;
        const x86::reg32 first = chance(10) ? 0xffff : below(0x300);
        g.word(at + 4) = (1 + below(4)) | (1 + below(4)) << 16;
        g.word(at + 0xc) = first | (first == 0xffff ? 0 : first + below(12)) << 16;
    }
    for (x86::reg32 tile = 0; tile < 0x320; ++tile)
        g.word(0x8b5094 + 0xc * tile) = below(64) | below(8) << 16;
    for (x86::reg32 block = 0; block < 8; ++block)
    {
        g.word(kBlocks + 0x400 * block) = chance(90) ? 0x78 + below(7) : random32();
        g.word(kBlocks + 0x400 * block + 4) = below(130) | below(130) << 16;
    }
    // The texts: four of 0x40.
    for (x86::reg32 i = 0; i < 4; ++i)
        aMenuText(g, kFeTexts + 0x40 * i, 0x30);
    // What the list's line reads: an index, small.
    g.word(0) = below(0x10);
}

bool makeFeDrawArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "layoutMenuItem", "sliderPartUnderPointer", "sliderThumbPlace", "snapToStep", "setSliderValue", "sliderStoredValue",
        "dragSliderTo", "drawSlider", "trackSlider", "twoAxisThumbPlace", "setTwoAxisValue", "twoAxisValue",
        "dragTwoAxisTo", "drawTwoAxis", "trackTwoAxis", "loadQfs", "flushFonts", "setTextScale", "keepTextScale",
        "restoreTextScale", "characterWidth", "characterOverhang", "quadOutcodes", "shapeByName", "drawShape",
        "gradientRectangle", "filledRectangle", "frame", "accentedCharacter", "drawScreenCharacter",
        "drawScreenText", "drawTexturedQuad", "drawShadedQuad"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeFeDrawWorld(g, cpu);
    const bool twoAxis = name.find("TwoAxis") != std::string::npos || name == "twoAxisValue";
    makeSlider(g, twoAxis);
    for (x86::reg32 at = kFeWords; at < kFeWords + 0x40; at += 4)
        g.word(at) = random32();
    if (name == "layoutMenuItem")
    {
        for (x86::reg32 at = kFeDrawItem; at < kFeDrawItem + 0x60; at += 4)
            g.word(at) = random32() % 0x200;
        static const x86::reg16 kinds[] = {0, 1, 2, 3, 0xf, 3, 0xf};
        g.getMemory<x86::reg16>(kFeDrawItem + 0x48) = x86::reg16(chance(90) ? kinds[below(7)] : below(0x10));
        g.word(kFeDrawItem + 0x3c) = chance(15) ? 0 : kFeTexts;
        g.word(kFeDrawItem + 0x40) = chance(50) ? 0 : 1;
        g.word(kFeDrawItem + 0x58) = chance(30) ? 0 : chance(20) ? kFeTexts + 0x3f : kFeTexts + 0x40;
        g.getMemory<x86::reg8>(kFeTexts + 0x3f) = 0;
        static const x86::reg32 screens[] = {0, 0x53a5fc, 0x53a65c, kFeTexts + 0x80};
        g.word(kFeDrawItem + 0x44) = screens[below(4)];
        g.getMemory<x86::reg16>(kFeDrawItem + 0x56) = x86::reg16(chance(90) ? below(3) : random32());
        g.getMemory<x86::reg8>(kFeDrawItem + 0x5c) = x86::reg8(chance(90) ? below(3) : random32());
        g.getMemory<x86::reg16>(kFeDrawItem + 0x5e) = x86::reg16(chance(50) ? 0 : below(100) - 20);
        cpu.eax = kFeDrawItem;
    }
    else if (name == "sliderThumbPlace" || name == "twoAxisThumbPlace")
    {
        cpu.eax = kFeSlider;
        cpu.ebx = kFeWords;
        cpu.ecx = kFeWords + 4;
        stack[0] = kFeWords + 8;
        stack[1] = kFeWords + 0xc;
        stack[2] = kFeWords + 0x10;
        if (name == "twoAxisThumbPlace")
        {
            cpu.ecx = kFeWords + 0x14;
            cpu.edx = below(3);
            cpu.ebx = chance(90) ? below(6) : random32();
        }
    }
    else if (name == "snapToStep")
    {
        stack[0] = aStep();
        stack[1] = aSliderValue();
    }
    else if (name == "setSliderValue" || name == "setTwoAxisValue")
    {
        cpu.eax = kFeSlider;
        stack[0] = aSliderValue();
        stack[1] = name == "setSliderValue" ? 0 : chance(90) ? below(3) : 3;
    }
    else if (name == "dragSliderTo" || name == "dragTwoAxisTo")
    {
        cpu.eax = kFeSlider;
        cpu.edx = chance(90) ? below(300) - 30 : random32();
        cpu.ebx = chance(90) ? below(3) : random32();
    }
    else if (name == "twoAxisValue")
    {
        cpu.eax = kFeSlider;
        cpu.edx = below(2);
    }
    else if (name == "sliderPartUnderPointer" || name == "sliderStoredValue" || name == "drawSlider" || name == "trackSlider"
             || name == "drawTwoAxis" || name == "trackTwoAxis")
    {
        cpu.eax = kFeSlider;
        cpu.edx = chance(50) ? 0 : random32();
    }
    else if (name == "loadQfs")
    {
        const x86::reg32 text = kFeTexts + 0x100;
        static const char* const files[] = {"menu", "art\\menu.qfs", "a.b\\c", "x:", "fe/back", "", ".qfs", "a.b/c", "d.e:f"};
        const char* file = files[below(9)];
        std::strcpy(&g.getMemory<char>(text), file);
        if (chance(20))
            aMenuText(g, text, 0x30);
        cpu.eax = text;
        std::strcpy(&g.getMemory<char>(kFeTexts + 0x180), chance(80) ? ".qfs" : "");
        g.word(0x55e544) = kFeTexts + 0x180;
    }
    else if (name == "setTextScale")
    {
        stack[0] = feFloat(chance(90) ? float(below(3000)) / 1000.0f : 1.0f);
    }
    else if (name == "characterWidth" || name == "characterOverhang")
    {
        cpu.eax = random32();
        g.word(0x840184) = below(2);
    }
    else if (name == "quadOutcodes")
    {
        for (x86::reg32 v = 0; v < 16; ++v)
            for (x86::reg32 i = 0; i < 4; ++i)
                g.word(kFeVertices + 0x20 * v + 4 * i) =
                    chance(90) ? feFloat(float(x86::sreg32(below(1600)) - 200)) : random32();
        for (x86::reg32 i = 0; i < 0x80; i += 4)
            g.word(kFeQuads + i) = below(16);
        cpu.eax = chance(95) ? below(9) : random32() | 0x80000000;
        cpu.edx = kFeVertices;
        cpu.ebx = kFeQuads;
    }
    else if (name == "shapeByName")
    {
        const x86::reg32 text = kFeTexts + 0x100;
        for (x86::reg32 c = 0; c < 4; ++c)
            g.getMemory<x86::reg8>(text + c) = x86::reg8('a' + below(3));
        g.getMemory<x86::reg8>(text + 4) = 0;
        cpu.eax = text;
        // Found among the shapes known, or none known: where the search
        // runs out, the game's strncmp leaves ebx otherwise than the port's
        // (watcom::strncmp, ebx an argument), and the tick's stand-in logs it.
        if (chance(50))
        {
            g.word(0x8b7628) = 0;
        }
        else
        {
            const x86::reg32 count = 1 + below(12), found = below(count);
            g.word(0x8b7628) = count;
            for (x86::reg32 c = 0; c < 4; ++c)
                g.getMemory<x86::reg8>(text + c) = g.getMemory<x86::reg8>(0x8b48c0 + 0x14 * found + 0x10 + c);
        }
    }
    else if (name == "drawShape")
    {
        cpu.eax = below(0x40);
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
    }
    else if (name == "gradientRectangle" || name == "filledRectangle" || name == "frame")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = name == "gradientRectangle" ? aScreenX() : below(300);
        cpu.ecx = name == "gradientRectangle" ? aScreenY() : below(200);
    }
    else if (name == "accentedCharacter")
    {
        cpu.eax = (random32() & 0xffffff00) | (chance(50) ? 0xc0 + below(0x40) : below(0x100));
        if (chance(15))
            cpu.al = chance(50) ? 0xc9 : 0xe9;
        g.word(0x6fbb4c) = chance(40) ? 2 : below(8);
    }
    else if (name == "drawScreenCharacter")
    {
        cpu.eax = below(0x100);
        cpu.edx = below(0x100);
        cpu.ebx = aScreenX();
        cpu.ecx = aScreenY();
        stack[0] = chance(95) ? below(0x20) : random32() % 0x100 - 0x80;
        stack[1] = chance(95) ? below(0x20) : random32() % 0x100 - 0x80;
        stack[2] = chance(30) ? 0xffe440 : random32();
        stack[3] = below(0x100);
        stack[4] = chance(80) ? 0 : 1;
    }
    else if (name == "drawScreenText")
    {
        cpu.eax = kFeTexts;
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
        cpu.ecx = chance(80) ? 0 : 1;
    }
    else if (name == "drawTexturedQuad" || name == "drawShadedQuad")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = aScreenX();
        cpu.ecx = aScreenY();
        stack[0] = aScreenX();
        stack[1] = aScreenY();
        stack[2] = aScreenX();
        stack[3] = aScreenY();
        if (name == "drawTexturedQuad")
        {
            // The texture's corners (floats), the texture, the colour.
            for (x86::reg32 i = 4; i < 9; ++i)
                stack[i] = feFloat(float(below(1000)) / 1000.0f);
            for (x86::reg32 i = 9; i < 12; ++i)
                g.word(cpu.esp + 4 + 4 * i) = feFloat(float(below(1000)) / 1000.0f);
            g.word(cpu.esp + 4 + 4 * 12) = random32();
            g.word(cpu.esp + 4 + 4 * 13) = random32();
        }
    }
    return true;
}
#endif
