/* game_checks.cpp's parts for the game's shapes rewritten (port::shapes,
 * src/nfs3hp/port_shapes.cpp), included in each table with the macro naming
 * the part.  The shapes' cases run what the code calls of its own for real
 * on both sides -- the converters under shapeToPixels, shapeToPixels under the
 * art's textures -- so their worlds keep the sizes small and every pointer in
 * the windows: the graphics' window (graphics_world.inc) for the pixels, the
 * shapes and the driver's record, the menus' art at 0x8b48c0 on. */
#if defined(SHAPES_WINDOWS)
// {from, to}, -- what the functions write, compared
// The menus' art: its shapes, tiles and the tiles' room; the blocks the
// allocation's stand-in hands out, which the art's pixels and tiles go into.
{0x8b4000, 0x8b8000}, {0x1f0000, 0x1f8000},
#elif defined(SHAPES_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// An 8-bit shape's palette (0x4fd1c0): a record in the graphics' window, as
// the converters read it -- 0x10 bytes on, 256 colours.
{0x4fd1c0, "a shape's palette", kWatcom, 1, 0, kEax, -1, 0, kRecord},
// A shape made a texture of its own (0x4d6070) and the textures let go of
// (0x4d5c40), as the 2D drawing calls them (port_draw2d's buildScreenFont,
// startScreens): stood in there, held against their code here on their own.
{0x4d6070, "a shape's texture", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4d5c40, "the textures let go of", kWatcom, 4, 0, kEax, -1, 0, kNothing},
#elif defined(SHAPES_PROMISES)
// {"port::shapes::name", watcom, result, arguments, fpu, heap, liveOnly},
// The x87's stack, its live registers and its words compared where the
// resizing works out its steps; a converter's eax, what is left of its walk,
// no caller reads (tools: callers_of.py -- shapeToPixels, render's
// paletteTexture), and is not compared.
{"port::shapes::scan4444", true, true, 0},
{"port::shapes::scan8888", true, true, 0},
{"port::shapes::scanNibbles", true, true, 0},
{"port::shapes::scanPaletted", true, true, 0},
{"port::shapes::scan1555", true, true, 0},
{"port::shapes::scan565", true, true, 0},
{"port::shapes::convert4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::convert8888", true, false, 0, true, kNoHeap, true},
{"port::shapes::convert8", true, false, 0, true, kNoHeap, true},
{"port::shapes::convert565", true, false, 0, true, kNoHeap, true},
{"port::shapes::convert1555", true, false, 0, true, kNoHeap, true},
{"port::shapes::nibblesTo1555", true, false, 0, true, kNoHeap, true},
{"port::shapes::nibblesTo565", true, false, 0, true, kNoHeap, true},
{"port::shapes::nibblesTo4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::nibblesTo8888", true, false, 0, true, kNoHeap, true},
{"port::shapes::paletteTo1555", true, false, 0, true, kNoHeap, true},
{"port::shapes::paletteTo565", true, false, 0, true, kNoHeap, true},
{"port::shapes::paletteTo4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::paletteTo8888", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb8888To4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb8888To565", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb8888To1555", true, false, 0, true, kNoHeap, true},
{"port::shapes::rgb565To1555", true, false, 0, true, kNoHeap, true},
{"port::shapes::rgb565To4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::rgb565To8888", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb1555To565", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb1555To4444", true, false, 0, true, kNoHeap, true},
{"port::shapes::argb1555To8888", true, false, 0, true, kNoHeap, true},
{"port::shapes::shapeToPixels", true, true, 0, true, kNoHeap, true},
{"port::shapes::resetTextures", true, true, 0, true, kNoHeap, true},
{"port::shapes::shapeByName", true, true, 0, true, kNoHeap, true},
{"port::shapes::shapeTexture", true, true, 0, true, kNoHeap, true},
{"port::shapes::cutTile", true, true, 0},
{"port::shapes::shape565To1555", true, true, 0},
{"port::shapes::tileRoom", true, true, 0},
{"port::shapes::artShapeTextures", true, true, 0, true, kNoHeap, true},
{"port::shapes::shapeSize", true, true, 0},
{"port::shapes::drawShapeQuad", true, true, 0, true, kNoHeap, true},
{"port::shapes::drawArtShape", true, true, 0, true, kNoHeap, true},
{"port::shapes::drawShape", true, true, 0, true, kNoHeap, true},
#elif defined(SHAPES_ARGUMENTS)
/* Where the converters' and scans' cases keep their own, in the graphics'
 * window: the shape's pixels (kGfxPixels, 0x2000 bytes), the texture's from
 * kGfxScratch on (to the window's end), the flag's word among the records. */
constexpr x86::reg32 kShapesOut = kGfxScratch, kShapesOutEnd = kGfxEnd;

/* A shape's size: small mostly, 0 or 1 now and then. */
x86::reg32 aShapeSide()
{
    return chance(10) ? below(2) : 1 + below(40);
}

/* A shape's header where `at` is, its pixels after it: a known format
 * mostly, sides of 1 to `most`. */
void makeShapeHeader(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    static const x86::reg32 formats[] = {0x7a, 0x7b, 0x7d, 0x6d, 0x7e, 0x78};
    g.word(at) = chance(90) ? formats[below(6)] : random32();
    g.word(at + 4) = (1 + below(most)) | (1 + below(most)) << 16;
}

/* Pixels as a shape of each format has them, with the values the code looks
 * for -- the keys, a clear alpha, index 0xff, nibbles of 0 -- now and then. */
void makeShapePixels(CheckApp& g, x86::reg32 from, x86::reg32 bytes)
{
    static const x86::reg32 keys[] = {0xff00f800, 0xff00fb00, 0x07c007c0, 0x07e007e0, 0x83e083e0,
                                      0x83c083c0, 0xffffffff, 0x80008000, 0x0f000f00, 0xf000f000};
    for (x86::reg32 at = from; at < from + bytes; at += 4)
        g.word(at) = chance(15) ? keys[below(10)] : chance(10) ? 0 : random32();
}

/* The x87, the graphics' window and THRASH_about's records as
 * graphics_world.inc makes them; THRASH's functions by name. */
void makeShapesWorld(CheckApp& g, x86::CPU& cpu, x86::reg32* a)
{
    makeGraphicsArguments(g, "", cpu, a);
    for (x86::reg32 i = 0; i < sizeof kThrashNames / sizeof *kThrashNames; ++i)
        g.word(kThrashSlots + 4 * i) = chance(97) ? namedStandIn(kThrashNames[i]) : 0;
    // The palette of an 8-bit shape (none now and then), the driver keying black.
    g.word(0x563a88) = chance(10) ? 0 : kGfxCorners;
    g.word(0x7a3a6c) = chance(50) ? 0 : 1;
}

/* With no THRASH_about, shapeToPixels reads the driver's formats out of a
 * record on its own stack (+0x30 of its frame's bottom): the formats, there,
 * for a shapeToPixels entered at `entry` (its return address's slot). */
void plantAboutFormats(CheckApp& g, x86::reg32 entry)
{
    g.word(entry - 0xc - 0x9c + 0x30) = kGfxFormats;
}

bool makeShapesArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    // Where each one's shapeToPixels is entered: its own frame, less its push and call.
    const x86::reg32 textureEntry = cpu.esp - 0xc - 0x14 - 8, artEntry = cpu.esp - 0x14 - 0x34 - 8;
    const x86::reg32 namedEntry = cpu.esp - 0x18 - 4 - 0x14 - 0x34 - 8;
    /* The art's shapes: of the formats the art takes.  Another is an Error,
     * and after it shapeToPixels reads what the game's stack holds -- its
     * kind and alpha for a format it does not know, the driver's formats
     * without THRASH_about -- which the game's Error (the generated side's)
     * and the port's leave otherwise. */
    static const x86::reg32 artFormats[] = {0x78, 0x7b, 0x7d, 0x7e};
    const auto anArtFormat = [] { return artFormats[below(4)]; };
    static const char* const scans[] = {"scan4444", "scan8888", "scanNibbles", "scanPaletted", "scan1555",
                                        "scan565"};
    static const char* const converters[] = {
        "convert4444", "convert8888", "convert8", "convert565", "convert1555", "nibblesTo1555", "nibblesTo565",
        "nibblesTo4444", "nibblesTo8888", "paletteTo1555", "paletteTo565", "paletteTo4444", "paletteTo8888",
        "argb8888To4444", "argb8888To565", "argb8888To1555", "rgb565To1555", "rgb565To4444", "rgb565To8888",
        "argb1555To565", "argb1555To4444", "argb1555To8888"};
    const auto among = [&](const char* const* from, const char* const* to) {
        return std::find_if(from, to, [&](const char* n) { return name == n; }) != to;
    };
    if (among(std::begin(scans), std::end(scans)))
    {
        makeShapesWorld(g, cpu, a);
        makeShapePixels(g, kGfxPixels, 0x2000);
        cpu.eax = kGfxPixels + below(0x40);
        cpu.edx = aShapeSide();
        cpu.ebx = aShapeSide();
        if (name == "scanNibbles")
        {
            // The width's oddness decides the first byte's end; a negative one runs on.
            static const x86::reg32 widths[] = {0, x86::reg32(-1), 1, 2, 7, 8, 64};
            cpu.edx = chance(70) ? widths[below(7)] : aShapeSide();
            cpu.ebx = chance(5) ? x86::reg32(-1) : below(4);
        }
    }
    else if (among(std::begin(converters), std::end(converters)))
    {
        makeShapesWorld(g, cpu, a);
        makeShapePixels(g, kGfxPixels, 0x2000);
        makeShapePixels(g, kGfxCorners, 0x400);  // the palette's colours
        // The shape's pixels and size, the texture's (no more than its room).
        cpu.eax = kShapesOut;
        cpu.edx = kGfxPixels + 4 * below(0x10);
        cpu.ebx = aShapeSide();
        cpu.ecx = aShapeSide();
        a[0] = chance(30) ? cpu.ebx : aShapeSide();
        a[1] = chance(30) ? cpu.ecx : aShapeSide();
        a[2] = gfxRecord();
    }
    else if (name == "shapeToPixels")
    {
        makeShapesWorld(g, cpu, a);
        makeGraphicsArguments(g, "shapeToPixels", cpu, a);
        // The shape small, the flag's word among the records.
        makeShapePixels(g, cpu.edx + 0x10, 0x400);
        g.word(cpu.edx + 4) = (1 + below(32)) | (1 + below(32)) << 16;
        cpu.ebx = gfxRecord();
    }
    else if (name == "shapeTexture")
    {
        makeShapesWorld(g, cpu, a);
        makeGraphicsArguments(g, "shapeTexture", cpu, a);
        makeShapeHeader(g, cpu.edx, 24);
        makeShapePixels(g, cpu.edx + 0x10, 0x400);
        cpu.ecx = chance(80) ? below(8) : random32();
        plantAboutFormats(g, textureEntry);
    }
    else if (name == "artShapeTextures" || name == "drawArtShape")
    {
        makeShapesWorld(g, cpu, a);
        for (const x86::reg32 at : {0x8b48c0u, 0x8b5090u, 0x8b6090u, 0x8b7090u})
            g.word(at) = decompiledValue();
        for (x86::reg32 at = 0x8b7a74; at < 0x8b7a74 + 300; ++at)
            g.getMemory<x86::reg8>(at) = x86::reg8(below(2));
        makeGraphicsArguments(g, name, cpu, a);
        if (name == "artShapeTextures")
        {
            makeShapePixels(g, cpu.eax + 0x10, 0x400);
            g.word(cpu.eax) = anArtFormat();
            g.word(cpu.eax + 4) = (1 + below(70)) | (1 + below(70)) << 16;
            plantAboutFormats(g, artEntry);
        }
        else
        {
            // The corners' depth and w, the clip's rectangle, as the menus have them or made up.
            for (const x86::reg32 at : {0x563aa8u, 0x563aacu, 0x7d34f8u, 0x7d34fcu, 0x7d3500u, 0x7d3504u, 0x7d350cu})
                g.word(at) = chance(50) ? decompiledValue() : feFloat(float(below(1000)) - 100.0f);
        }
    }
    else if (name == "resetTextures")
    {
        makeShapesWorld(g, cpu, a);
        g.word(0x563d44) = decompiledValue();
    }
    else if (name == "drawShapeQuad")
    {
        makeShapesWorld(g, cpu, a);
        // softtria's way too: it is in the same code, if dead on the port.
        g.word(0x7a3a58) = chance(70) ? 0x10 : chance(50) ? 0x02 : decompiledValue();
    }
    else if (name == "cutTile")
    {
        makeShapesWorld(g, cpu, a);
        cpu.eax = kGfxPixels - 0x10;
        g.word(cpu.eax + 4) = (1 + below(64)) | (1 + below(64)) << 16;
        cpu.edx = kShapesOut;
        static const x86::reg32 sizes[] = {32, 16, 8, 0, 1, 31};
        cpu.ebx = sizes[below(6)];
        cpu.ecx = chance(80) ? 0x20 * below(3) : below(80);
        a[0] = chance(80) ? 0x20 * below(3) : below(80);
    }
    else if (name == "shape565To1555")
    {
        makeShapesWorld(g, cpu, a);
        cpu.eax = kGfxPixels - 0x10;
        g.word(cpu.eax + 4) = (chance(5) ? 0 : 1 + below(64)) | (1 + below(60)) << 16;
    }
    else if (name == "tileRoom")
    {
        makeShapesWorld(g, cpu, a);
        for (x86::reg32 at = 0x8b7a74; at < 0x8b7a74 + 300; ++at)
            g.getMemory<x86::reg8>(at) = x86::reg8(chance(70) ? 1 : 0);
        // A column or row past the room, or before it, now and then (not so
        // far that the room's bytes looked at leave the game's memory).
        cpu.eax = chance(90) ? below(22) : below(60) - 30;
        cpu.edx = chance(90) ? below(17) : below(60) - 30;
        cpu.ebx = chance(70) ? 0 : chance(80) ? 1 : random32();
    }
    else if (name == "shapeSize")
    {
        cpu.eax = chance(90) ? below(104) - 2 : random32();
        cpu.edx = gfxScratch();
        cpu.ebx = gfxScratch() + 2;
    }
    else if (name == "shapeByName" || name == "drawShape")
    {
        // The menus' drawing's world (frontend_draw.inc), and what the art's
        // textures need of the driver: its record, its formats.
        makeShapesWorld(g, cpu, a);
        makeFeDrawWorld(g, cpu);
        plantAboutFormats(g, namedEntry);
        // The shapes the art's search finds (the blocks): small enough that
        // their pixels keep to a block of their own -- the allocation's
        // stand-in hands out the same 8 blocks of 0x400 for the shape, its
        // pixels and its tile, and a shape that runs into the next block
        // has its header written over, past the game's memory then.
        for (x86::reg32 block = 0; block < 8; ++block)
        {
            g.word(kBlocks + 0x400 * block) = anArtFormat();
            g.word(kBlocks + 0x400 * block + 4) = (1 + below(15)) | (1 + below(15)) << 16;
        }
        if (name == "drawShape")
        {
            cpu.eax = below(0x40);
            cpu.edx = aScreenX();
            cpu.ebx = aScreenY();
        }
        else
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
    }
    else
        return false;
    return true;
}
#endif
