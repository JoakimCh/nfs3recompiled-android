/* The graphics' natives' worlds (native_graphics.cpp): the polygon records,
 * corners, pixels and screen records their pointers lead to, made up in a
 * window of their own, and what THRASH_about's record holds -- the formats
 * the driver takes, its modes, its texture memory.  Included twice by
 * game_checks.cpp: for the window (GRAPHICS_WINDOWS) and for the cases
 * (GRAPHICS_ARGUMENTS). */

#ifdef GRAPHICS_WINDOWS
    // The graphics' records, corners, pixels and descriptions.
    {0xc00000, 0xc08000},
#endif

#ifdef GRAPHICS_ARGUMENTS
constexpr x86::reg32 kGfxRecords = 0xc00000;  // 64 records of 0x40
constexpr x86::reg32 kGfxCorners = 0xc01000;  // 64 corners of 0x40
constexpr x86::reg32 kGfxPixels = 0xc02000;   // 0x2000 bytes of pixels to read
constexpr x86::reg32 kGfxScratch = 0xc04000;  // 64 words, 0x10 apart, a result written into each
constexpr x86::reg32 kGfxFormats = 0xc05000;  // THRASH_about's formats (+0x30): a word each 0x10
constexpr x86::reg32 kGfxModes = 0xc06000;    // its modes (+0x40): 0x28 bytes each
constexpr x86::reg32 kGfxEnd = 0xc08000;

x86::reg32 gfxRecord()
{
    return kGfxRecords + 0x40 * below(64);
}

x86::reg32 gfxCorner()
{
    return kGfxCorners + 0x40 * below(64);
}

x86::reg32 gfxScratch()
{
    return kGfxScratch + 0x10 * below(64);
}

/* THRASH_about's record, and the null one a failed THRASH_about leaves the
 * code reading: its formats, its modes and their count, its texture memory
 * on either side of the 2 MB the game warns under. */
void makeAbout(CheckApp& g, x86::reg32 record)
{
    g.word(record + 0x30) = kGfxFormats;
    g.word(record + 0x3c) = chance(10) ? x86::reg32(0) - 1 : below(20);
    g.word(record + 0x40) = kGfxModes;
    g.word(record + 0x70) = chance(50) ? below(0x400000) : 0x200000 + below(3) - 1;
    g.word(record + 0x74) = below(0x200000);
}

/* THRASH_about's modes as a driver lists them -- 4:3 and 16:9 sizes and
 * others, 15, 16 and 32 bits, available or not, one to three colour
 * buffers -- with now and then a word made up. */
void makeModes(CheckApp& g)
{
    static const x86::reg32 widths[] = {320, 512, 640, 800, 960, 1024, 1280, 856, 0xffff};
    for (x86::reg32 mode = 0; mode < 24; ++mode)
    {
        const x86::reg32 record = kGfxModes + 0x28 * mode;
        const x86::reg32 width = widths[below(9)];
        g.word(record) = width;
        g.word(record + 4) = chance(60) ? width * 3 / 4 : chance(50) ? width * 9 / 16 : below(1200);
        g.word(record + 8) = chance(40) ? 16 : chance(40) ? 15 : chance(50) ? 32 : random32();
        g.word(record + 0x10) = chance(80) ? below(4) : random32();
        g.word(record + 0x14) = chance(90) ? below(4) : random32();
        g.word(record + 0x18) = chance(90) ? below(4) : random32();
    }
}

void makeGraphicsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    for (x86::reg32 at = kGfxRecords; at < kGfxEnd; at += 4)
        g.word(at) = random32();
    makeAbout(g, kAboutRecord);
    makeAbout(g, 0);
    // The software renderers' and Direct3D's ways are dead stubs on the port:
    // the driver is voodoo2a's.
    g.word(0x7a3a58) = 0x10;
    // The x87 as the game runs it -- a race's single precision or the menus'
    // and an extended race's 64 bits, to nearest -- set as fldcw sets it, so
    // that what the arithmetic rounds to goes with the word (Watcom's __CHP,
    // generated, sets it again from the word; the native leaves it).
    cpu.fpu.setControl(chance(50) ? 0x007f : 0x037f);
    if (name == "drawLineRecord" || name == "lockFrameBuffer")
        cpu.eax = gfxRecord();
    else if (name == "drawColouredQuadRecord")
    {
        cpu.eax = gfxRecord();
        for (x86::reg32 corner = 0; corner < 4; ++corner)
            g.word(cpu.eax + 8 + 4 * corner) = gfxCorner();
        g.word(cpu.eax + 0x18) = chance(30) ? 0 : random32();
    }
    else if (name == "flushLineMesh")
    {
        cpu.eax = gfxRecord();
        g.word(cpu.eax) = chance(30) ? 0 : random32();
    }
    else if (name == "updateTexture")
    {
        cpu.edx = kGfxPixels + 2 * below(0x400);
        cpu.ebx = chance(5) ? x86::reg32(0) - below(4) : below(24);
        cpu.ecx = below(24);
    }
    else if (name == "modeSize")
    {
        cpu.eax = below(26) - 2;
        cpu.edx = gfxScratch();
        cpu.ebx = gfxScratch();
        cpu.ecx = gfxScratch();
        a[0] = gfxScratch();
    }
    else if (name == "warnTextureMemory")
        cpu.edx = below(6);  // [0x7a3a50], one of the six; the tables' words are its text's strings
    else if (name == "drawTextBox")
        g.word(0x840184) = below(16);
    else if (name == "shapeIntoTexture")
    {
        cpu.edx = gfxCorner();
        cpu.ebx = below(16);
    }
    else if (name == "useDriverSlot" || name == "keepDriverSlot")
        cpu.eax = chance(90) ? below(8) : random32();
    else if (name == "setUpScreen")
    {
        cpu.eax = chance(30) ? 0xff : chance(20) ? 0 : below(3);
        cpu.ebx = gfxRecord();
    }
    else if (name == "listScreenModes" || name == "findScreenMode")
    {
        makeModes(g);
        if (name == "listScreenModes")
            cpu.eax = namedStandIn("_listedMode@4");  // the list's: the mode in eax, its width in edx
        else
            cpu.eax = chance(10) ? 0xffff : chance(70) ? 320 * (1 + below(4)) : random32() % 2000;
    }
    else if (name == "makeArtTexture")
    {
        cpu.edx = gfxScratch();
        g.word(cpu.edx) = chance(90) ? 3 + below(4) : random32();
        cpu.eax = below(64);
    }
    else if (name == "shapeTexture")
    {
        cpu.eax = gfxScratch();
        cpu.edx = gfxCorner();
        cpu.ebx = below(16);
    }
    else if (name == "artShapeTextures" || name == "drawArtShape")
    {
        // The art's records and tiles: a few of each in use, their tiles' sizes and places small.
        g.word(0x8b7628) = below(90);
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
        if (name == "artShapeTextures")
        {
            cpu.eax = gfxCorner();
            g.word(cpu.eax) = chance(90) ? 0x78 + below(7) : random32();
            g.word(cpu.eax + 4) = below(130) | below(130) << 16;  // its width and height
            cpu.edx = chance(30) ? x86::reg32(0) - below(3) : chance(50) ? 0 : below(90);
        }
        else
        {
            cpu.eax = below(100);
            g.word(0x559234) = chance(15);
        }
    }
    else if (name == "drawShadedRectangle")
        g.word(0x559234) = chance(30);
    else if (name == "hudMessageBox")
        cpu.eax = below(4);
    else if (name == "hudEditorFrame")
    {
        cpu.eax = gfxRecord();
        g.word(cpu.eax + 4) = below(700) << 16;  // +6: the left, a word
        g.word(cpu.eax + 8) = below(500);        // +8: the top, a word
        g.word(cpu.eax + 0x60) = below(700);
        g.word(cpu.eax + 0x64) = below(500);
        g.word(0x7cdac8) = 320 << below(3);
    }
    else if (name == "captureScreen" || name == "showWaitMessage" || name == "gameMain")
        // Their waits -- for a file name not taken, for a menu that quits -- end with the case.
        g_mostCalls = name == "gameMain" ? 80 : 25;
    else if (name == "loadCabinInstruments" || name == "showLoadingScreen")
    {
        // The records the stand-ins hand back point at each other, so that
        // what is read through them stays in the window.
        for (x86::reg32 at = kGfxRecords; at < kGfxEnd; at += 4)
            g.word(at) = chance(50) ? kGfxRecords + 4 * below((kGfxEnd - kGfxRecords) / 4 - 0x100) : below(0x400);
        g.word(0x6fd4f4) = below(8);
        // A race's track: what sub_43bcb0 counts its pictures from, never none.
        for (x86::reg32 race = 0; race < 8; ++race)
            g.word(0x6fd540 + 0x6c * race) = 1 + below(5);
    }
    else if (name == "drawLoadingProgress")
        g.word(0x79f288) = chance(80);
    else if (name == "raceFrame")
    {
        cpu.eax = below(3);
        static const x86::reg32 drivers[] = {0x10, 0x02, 0x04, 0x40};
        g.word(0x7a3a58) = drivers[below(4)];  // softtria's ways too: they are in the same code
    }
    else if (name == "shapeToPixels")
    {
        // The driver's formats, a word each: taken (bit 0), not for alpha (bit 2), or not at all.
        for (x86::reg32 format = 0; format < 16; ++format)
            g.word(kGfxFormats + 4 * format) = chance(30) ? 0 : below(8);
        for (const x86::reg32 record : {kAboutRecord, x86::reg32(0)})
        {
            g.word(record + 0x10) = 1 << below(5);
            g.word(record + 0x14) = 0x40 << below(4);
            g.word(record + 0x1c) = 1 << below(5);
            g.word(record + 0x20) = 0x40 << below(4);
        }
        // With no THRASH_about, the record of its own in the frame (ebp - 0x9c)
        // points at the formats too.
        g.word(cpu.esp - 0xc - 0x9c + 0x30) = kGfxFormats;
        static const x86::reg32 shapes[] = {0x7a, 0x7b, 0x7d, 0x6d, 0x7e, 0x78};
        cpu.eax = gfxScratch();
        cpu.edx = gfxCorner();
        g.word(cpu.edx) = chance(90) ? shapes[below(6)] : random32();
        g.word(cpu.edx + 4) = (1 + below(300)) | (1 + below(300)) << 16;
        cpu.ecx = chance(30) ? 0 : 0x20 << below(4);
        a[0] = gfxScratch();
        static const x86::reg32 asked[] = {0, 2, 3, 4, 6, 7, 11, 5};
        g.word(a[0]) = asked[below(8)];
    }
}
#endif
