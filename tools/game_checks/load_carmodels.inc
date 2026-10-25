// game_checks.cpp's parts for the cars' models and specs: carp.txt and car.viv for a race, the .fce and .art models and their textures, carspecs' .spc
// (native_load_carmodels.cpp), included in each table with the macro naming the part.
#if defined(LOAD_WINDOWS)
// {from, to}, -- what the functions write, compared
// The car's transfer (its name, the .viv sent from, Carp.txt's path); the
// data path and the specs' folder; the players' specs' tables.
{0x79f000, 0x7a0000}, {0x7a2000, 0x7a3000}, {0x8b8000, 0x8ba000},
#elif defined(LOAD_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kCarmodelsCar,    // 0x439a50: a car's record -- of the cars there are, to the first there is not -- or 0
kCarmodelsIndex,  // 0x439990: a car's index by its id, or -1
kCarmodelsSize,   // 0x4e43a0: a file's size: a spec file's or so, small, none, below 0
#elif defined(LOAD_EFFECT_CASES)
// case kSomething: ... break;
case kCarmodelsCar:
case kCarmodelsIndex:
case kCarmodelsSize:
{
    // Only in the models' cases (the case's mark at 0x61d3f8): elsewhere a
    // record as carRecord finds it, the others as kNothing leaves eax.  The cars there are: [0x61d3fc], their records
    // 0x40 bytes apart from 0x6000.
    const x86::reg32 more = random(id ^ 0xabcd);
    if (word(0x61d3f8) != x86::reg32(g_seed) && s.effect == kCarmodelsCar)
    {
        // Elsewhere a car's record as carRecord finds it (without its cache):
        // the list's (0x554f70) car at eax, 0 past 49 or the list's end --
        // never a made-up pointer, which the callers read the car through.
        result = 0;
        if (x86::sreg32(words[0]) >= 0 && x86::sreg32(words[0]) <= 0x31)
        {
            x86::reg32 car = word(0x554f70);
            for (x86::reg32 n = 0; car != 0 && car < kMemory - 0x400 && n != words[0] && n < 64; ++n)
                car = word(car);
            result = car < kMemory - 0x400 ? car : 0;
        }
    }
    else if (word(0x61d3f8) != x86::reg32(g_seed))
        result = more % 4 != 0 ? r : cpu.eax;
    else if (s.effect == kCarmodelsCar)
        result = words[0] < word(0x61d3fc) && r % 32 != 0 ? 0x6000 + 0x40 * (words[0] % 16) : 0;
    else if (s.effect == kCarmodelsIndex)
        result = r % 3 == 0 ? 0xffffffff : r % 50;
    else
        result = r % 6 == 0 ? 0 : r % 6 == 1 ? (r >> 8) % 0x30 : r % 13 == 2 ? 0x80000000 | r : (r >> 8) % 0xa00;
    break;
}
#elif defined(LOAD_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The car received put together: a path ended with a backslash, the car's
// folder marked (its first bytes logged), a file copied (eax to edx), the
// new car's .viv's name, a file put into it, the cars' data brought up to
// date, the transfer's state (its title, name, word, done).
{0x4529a0, "a path ended with a backslash", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4385a0, "the car's folder marked", kWatcom, 1, 0, kEax, 0, 4, kNothing},
{0x452a00, "a file copied", kWatcom, 2, 0, kEax, 0, 4, kNothing},
{0x43ba20, "the new car's .viv", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x43baa0, "a file put into the car's .viv", kWatcom, 1, 0, kEax, 0, 4, kNothing},
{0x439d90, "the cars' data brought up to date", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x43bc00, "the transfer's title", kWatcom, 1, 0, kEax, 0, 4, kNothing},
{0x43bc40, "the transfer's name", kWatcom, 1, 0, kEax, 0, 4, kNothing},
{0x43bc70, "the transfer's word", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x43bc90, "the transfer done", kWatcom, 0, 0, kEax, -1, 0, kNothing},
// The cars: a car's record by its index, its index by its id (the id's
// bytes logged); a file's size (eax its name, edx the mode); a model made
// ready -- the .fce at eax, which it gives back.
{0x439a50, "a car's record", kWatcom, 1, 0, kEax, -1, 0, kCarmodelsCar},
{0x439990, "a car's index by its id", kWatcom, 1, 0, kEax, 0, 4, kCarmodelsIndex},
{0x4e43a0, "a file's size", kWatcom, 2, 0, kEax, 0, 4, kCarmodelsSize},
{0x49cfa0, "a model made ready", kWatcom, 1, 0, 0, 0, 4, kNothing},
#elif defined(LOAD_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(LOAD_PROMISES)
// {"load::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared; the x87's stack and words too where the code
// uses it -- but edx and ebx, argument registers, where a chunk is written
// to its file: the game's fwrite (0x4eebd0) and native watcom::fwrite leave
// its argument registers differently (its own promise), and ebx comes out
// of the chunk's code as fwrite leaves it.
{"load::beginCarpReceive", true, true, 0},
{"load::receiveCarpChunk", true, true, 3},
{"load::beginCarpSend", true, true, 0},
{"load::readCarColors", true, true, 0, true, kNoHeap, true},
{"load::rgbToHsv", true, true, 0},
{"load::hsvToRgb", true, true, 0, true, kNoHeap, true},
{"load::tintPixel", true, true, 0, true, kNoHeap, true},
{"load::scaleTexture", true, true, 0, true, kNoHeap, true},
{"load::fitTexture", true, true, 0, true, kNoHeap, true},
{"load::loadArtTextures", true, true, 0, true, kNoHeap, true},
{"load::nearestModelColor", true, true, 0, true, kNoHeap, true},
{"load::loadTgaTexture", true, true, 0, true, kNoHeap, true},
{"load::loadCarModel", true, true, 0, true, kNoHeap, true},
{"load::loadVivCarModel", true, true, 0, true, kNoHeap, true},
{"load::copyVivCarModel", true, true, 0},
{"load::setSpecUsed", true, true, 0},
{"load::specUsed", true, true, 0},
{"load::specCarName", true, true, 0},
{"load::findSpec", true, true, 0},
{"load::freeSpecSlot", true, true, 0},
{"load::setSpec", true, true, 0},
{"load::defaultSpecs", true, true, 0},
{"load::refreshSpecs", true, true, 0},
{"load::specPath", true, true, 0},
{"load::readSpecs", true, true, 0},
{"load::loadPlayerSpecs", true, true, 0},
{"load::savePlayerSpecs", true, true, 0},
#elif defined(LOAD_ARGUMENTS)
/* Where the models' cases keep their own (0x61d000 on): the receiver's
 * record, a count, 12 bytes read, colours (hue, saturation, brightness and
 * the fourth; red, green, blue and the fourth), what is written out, a
 * header sent, a name, a car's id, a spec, the driver's formats, a colour's
 * four bytes, the case's mark and the cars there are; a chunk received, the
 * buffer it goes to, a texture, pixels.  In the low 64K: a car, a model, the
 * cars' records, where a texture is copied to, a car's .viv in memory. */
constexpr x86::reg32 kCmRecord = 0x61d000, kCmCount = 0x61d020, kCmTwelve = 0x61d040, kCmHsv = 0x61d060;
constexpr x86::reg32 kCmHsv2 = 0x61d070, kCmRgb = 0x61d080, kCmOut = 0x61d0a0, kCmHeader = 0x61d0e0;
constexpr x86::reg32 kCmName = 0x61d100, kCmId = 0x61d140, kCmSpec = 0x61d150, kCmFormats = 0x61d180;
constexpr x86::reg32 kCmColorBytes = 0x61d1c0, kCmMark = 0x61d3f8, kCmCarCount = 0x61d3fc;
constexpr x86::reg32 kCmData = 0x61d200, kCmBuffer = 0x61d400, kCmTexture = 0x61d800, kCmPixels = 0x61e000;
constexpr x86::reg32 kCmCar = 0x3000, kCmModel = 0x4000, kCmCars = 0x6000, kCmCopy = 0x6800, kCmViv = 0x8000;

/* What a stand-in called `index`-th in the case (from 0) makes of its
 * random: the r of game_checks.cpp's standIn, for the cases that must know
 * where the files it finds go. */
x86::reg32 cmPredicted(x86::reg32 index, x86::reg32 id)
{
    return x86::reg32(mix(g_seed ^ (std::uint64_t(index + 1) << 32) ^ id));
}

/* The texture's block (0x4e1620, the case's `index`-th call) at 0: the
 * texture written over the low dword THRASH_about's none is read from --
 * where the driver's about then stops the case (none in its slot). */
void cmBlockAtZero(CheckApp& g, x86::reg32 index)
{
    if (cmPredicted(index, 0x4e1620) % 6 == 0)
        g.word(0x9ef980) = 0;
}

/* A colour as hue, saturation, brightness and the fourth: in their 0 to 255
 * mostly -- the hue's last sixth and past it, 0 and 255, below 0 now and
 * then. */
void cmColor(CheckApp& g, x86::reg32 at)
{
    for (x86::reg32 i = 0; i < 3; ++i)
        g.word(at + 4 * i) = chance(10) ? 0 : chance(10) ? 0xff : chance(80) ? below(0x100)
                             : chance(50) ? 0x100 + below(0x80) : x86::reg32(-1 - x86::sreg32(below(0x80)));
    g.word(at + 0xc) = chance(30) ? 0xff : chance(80) ? below(0x100) : random32();
}

/* A model's colours: how many of each kind, each kind's colours. */
void cmModelColors(CheckApp& g, x86::reg32 model)
{
    g.word(model + 0x7fc) = chance(10) ? 0 : chance(90) ? 1 + below(6) : x86::reg32(-1 - x86::sreg32(below(3)));
    g.word(model + 0x900) = chance(25) ? 0 : chance(90) ? 1 + below(6) : x86::reg32(-1 - x86::sreg32(below(3)));
    for (x86::reg32 i = 0; i < 7; ++i)
    {
        cmColor(g, model + 0x800 + 0x10 * i);
        cmColor(g, model + 0x904 + 0x10 * i);
    }
}

/* Pixels, 32 bits each: any colour, the alpha 0, 0xff, its top bit clear or
 * set. */
void cmPixels(CheckApp& g, x86::reg32 at, x86::reg32 count)
{
    static const x86::reg8 alphas[] = {0, 0xff, 0x7f, 0x80, 0xfe, 1};
    for (x86::reg32 i = 0; i < count; ++i)
    {
        g.word(at + 4 * i) = random32() & 0xffffff;
        g.getMemory<x86::reg8>(at + 4 * i + 3) = chance(70) ? alphas[below(6)] : x86::reg8(random32());
    }
}

/* A short name: a letter or two to 14, ended. */
void cmName(CheckApp& g, x86::reg32 at)
{
    const x86::reg32 length = below(15);
    for (x86::reg32 i = 0; i < length; ++i)
        g.getMemory<x86::reg8>(at + i) = x86::reg8('a' + below(26));
    g.getMemory<x86::reg8>(at + length) = 0;
}

/* A size a texture is fitted to: 1 to 32 mostly, a power of two often. */
x86::reg32 cmMost()
{
    return chance(50) ? 1u << below(6) : chance(90) ? 1 + below(32) : chance(50) ? 0 : x86::reg32(-1 - x86::sreg32(below(4)));
}

/* A player: the first, the second, now and then neither. */
x86::reg32 cmPlayer()
{
    return chance(45) ? 0 : chance(85) ? 1 : chance(50) ? 2 + below(3) : chance(50) ? 0xffffffff : random32();
}

/* A spec's index: of the 50 mostly, past them or below 0 now and then. */
x86::reg32 cmIndex()
{
    return chance(85) ? below(50) : chance(30) ? 50 : chance(50) ? x86::reg32(-1 - x86::sreg32(below(3))) : random32();
}

/* The models' world: the case's mark, the cars there are and their records;
 * the data path and the specs' folder; short names where a file found or a
 * car's folder's name may be (the low 64K's first bytes and the 16 a loaded
 * file is put at); the driver's texture formats and its functions; colours;
 * the players' specs, their cars' ids mostly as the cars' are. */
void makeCarmodelsWorld(CheckApp& g)
{
    g.word(kCmMark) = x86::reg32(g_seed);
    g.word(kCmCarCount) = chance(10) ? 0 : chance(80) ? 1 + below(20) : 50 + below(20);
    for (x86::reg32 at = kCmCars; at < kCmCars + 0x800; at += 4)
        g.word(at) = random32();
    for (x86::reg32 at = kCmRecord; at < 0x61d3f8; at += 4)
        g.word(at) = random32();
    const x86::reg32 pathLength = chance(10) ? 0 : 1 + below(0x30);
    for (const x86::reg32 path : {0x7a28b4u, 0x7a2fb4u})
    {
        for (x86::reg32 i = 0; i < pathLength; ++i)
            g.getMemory<x86::reg8>(path + i) = chance(10) ? '\\' : x86::reg8('a' + below(26));
        g.getMemory<x86::reg8>(path + pathLength) = 0;
    }
    // Names every 8 bytes from 0, and in the 16 places a file loaded is put.
    for (x86::reg32 at = 0; at < 0x40; at += 8)
    {
        for (x86::reg32 i = 0; i < 7; ++i)
            g.getMemory<x86::reg8>(at + i) = x86::reg8(chance(15) ? 0 : 'a' + below(26));
        g.getMemory<x86::reg8>(at + 7) = 0;
    }
    for (x86::reg32 at = 0x7700; at < 0x7800; at += 0x10)
        cmName(g, at);
    cmName(g, kCmName);
    // THRASH_about's formats -- 1555 -- where the about is, and a small
    // number where none is, its bytes 1555 too: the 4444's buffer (a block of
    // the game's memory, at 0 now and then) would be written over the low
    // dword read where the about is none, for the next texture's.
    // THRASH_talloc and tupdate.
    g.word(0x30) = below(4);
    g.word(0xc) = 0x01010101;
    g.word(0x610030) = kCmFormats;
    g.getMemory<x86::reg8>(kCmFormats + 0xc) = 1;
    g.getMemory<x86::reg8>(kCmFormats + 0x1c) = x86::reg8(chance(90) ? 1 : 0);
    g.word(0x9ef968) = namedStandIn("_THRASH_talloc@20");
    g.word(0x9ef964) = namedStandIn("_THRASH_tupdate@12");
    g.word(0x7a3a6c) = chance(40) ? 0 : chance(70) ? 1 : random32();
    cmColor(g, kCmHsv);
    cmColor(g, kCmHsv2);
    // The cars' ids (0x439520 hands out these 64 places): some made anew.
    for (x86::reg32 i = 0; i < 64; ++i)
        if (chance(50))
            for (x86::reg32 at = 0; at < 16; at += 4)
                g.word(0xc00000 + 0x40 * i + at) = chance(30) ? 0 : random32();
    // The players' specs.
    for (const x86::reg32 table : {0x8b9200u, 0x8b88a0u})
        for (x86::reg32 i = 0; i < 50; ++i)
        {
            const x86::reg32 spec = table + 0x30 * i;
            for (x86::reg32 at = 0; at < 0x30; at += 4)
                g.word(spec + at) = random32();
            g.getMemory<x86::reg8>(spec) = x86::reg8(chance(50) ? 1 : chance(80) ? 0 : random32());
            if (chance(60))
                std::memcpy(&g.getMemory<x86::reg8>(spec + 4), &g.getMemory<x86::reg8>(0xc00000 + 0x40 * below(64)), 16);
        }
}

/* A model in the low 64K: its pictures' count, its colours. */
void cmModel(CheckApp& g, x86::reg32 model, x86::reg32 pictures)
{
    for (x86::reg32 at = 0; at < 0x40; at += 4)
        g.word(model + at) = random32();
    cmModelColors(g, model);
    for (x86::reg32 at = 0x1e00; at < 0x1e40; at += 4)
        g.word(model + at) = random32();
    g.word(model + 0xc) = pictures;
}

/* The .art's pictures at `at`, `count` of them, each a few pixels each way --
 * of no size now and then; the first of two pixels at least when `first`.
 * Every dword small (below 4) unless `colours`: a picture's size read
 * elsewhere is small too. */
void cmArt(CheckApp& g, x86::reg32 at, x86::reg32 count, bool colours, bool first)
{
    for (x86::reg32 i = 0; i < count; ++i)
    {
        x86::reg32 w = chance(10) ? 0 : 1 + below(colours ? 6 : 4), h = chance(10) ? 0 : 1 + below(colours ? 6 : 4);
        if (i == 0 && first)
        {
            w = 1 + below(4);
            h = 2 + below(3);
        }
        g.word(at) = w;
        g.word(at + 4) = h;
        if (colours)
            cmPixels(g, at + 8, w * h);
        else
            for (x86::reg32 p = 0; p < w * h; ++p)
                g.word(at + 8 + 4 * p) = below(4);
        at += 8 + 4 * w * h;
    }
}

/* A .tga at `at`: its id's length, width and height, its pixels. */
void cmTga(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    const x86::reg32 id = chance(70) ? 0 : below(8);
    const x86::reg32 w = chance(8) ? 0 : 1 + below(most), h = chance(8) ? 0 : 1 + below(most);
    for (x86::reg32 i = 0; i < 0x12; ++i)
        g.getMemory<x86::reg8>(at + i) = x86::reg8(random32());
    g.getMemory<x86::reg8>(at) = x86::reg8(id);
    g.getMemory<x86::reg16>(at + 0xc) = x86::reg16(w);
    g.getMemory<x86::reg16>(at + 0xe) = x86::reg16(h);
    cmPixels(g, at + 0x12 + id, w * h + 1);
}

bool makeLoadCarmodelsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "beginCarpReceive", "receiveCarpChunk", "beginCarpSend", "readCarColors", "rgbToHsv", "hsvToRgb",
        "tintPixel", "scaleTexture", "fitTexture", "loadArtTextures", "nearestModelColor", "loadTgaTexture",
        "loadCarModel", "loadVivCarModel", "copyVivCarModel", "setSpecUsed", "specUsed", "specCarName", "findSpec",
        "freeSpecSlot", "setSpec", "defaultSpecs", "refreshSpecs", "specPath", "readSpecs", "loadPlayerSpecs",
        "savePlayerSpecs"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeCarmodelsWorld(g);
    // The x87's word: the race's single precision, or the menus' double or
    // extended -- the precision the products are rounded to.
    cpu.fpu.setControl(x86::reg16(chance(50) ? 0x007f : chance(50) ? 0x027f : 0x037f));
    const auto aColor = [] { return chance(25) ? 0 : chance(50) ? kCmHsv : kCmHsv2; };
    if (name == "beginCarpReceive")
    {
        cpu.eax = kCmRecord;
        cpu.edx = chance(50) ? kCmBuffer : 0;
        cpu.ebx = chance(80) ? below(0x400) : random32();
    }
    else if (name == "receiveCarpChunk")
    {
        // The record: done now and then; what is in, what comes, the size --
        // all in with this chunk often; into its buffer, or a stream.
        const x86::reg32 in = below(0x200), count = below(0x1c0);
        g.word(kCmRecord) = chance(85) ? 0 : chance(50) ? 1 : random32();
        g.word(kCmRecord + 4) = chance(50) ? in + count : in + below(0x400);
        g.word(kCmRecord + 8) = kCmBuffer + below(0x40);
        g.word(kCmRecord + 0xc) = in;
        g.word(kCmRecord + 0x10) = chance(50) ? 0 : aStream();
        cpu.eax = kCmRecord;
        cpu.edx = kCmData;
        cpu.ebx = count;
    }
    else if (name == "beginCarpSend")
    {
        // The car: a name's address, or a small index whose bytes are a name
        // too.  Where the car's name (0x439250, the eighth call) would leave
        // eax made up, the case stops there: its name is read from eax.
        cpu.eax = kCmHeader;
        cpu.edx = chance(50) ? kCmName : below(0x38);
        if (cmPredicted(8, 0x439250 ^ 0xabcd) % 4 != 0)
            g_mostCalls = 8;
    }
    else if (name == "readCarColors")
    {
        // The file found or not: the frame's flag (its [ebp - 4]) 0 now and
        // then, for any of the places the case's esp may be.
        if (chance(30))
            for (x86::reg32 i = 0; i < 64; ++i)
                g.word(kStackHigh - 0x1000 - 4 * i - 0x10) = 0;
        cpu.eax = kCmName;
        cpu.edx = kCmOut;
        cpu.ebx = chance(85) ? below(18) : x86::reg32(-1 - x86::sreg32(below(3)));
        cpu.ecx = kCmCount;
        stack[0] = kCmTwelve;
    }
    else if (name == "rgbToHsv")
    {
        // Red, green, blue: 0 to 255 mostly, alike now and then, past them.
        for (x86::reg32 i = 0; i < 3; ++i)
            g.word(kCmRgb + 4 * i) = chance(10) ? 0 : chance(10) ? 0xff : chance(85) ? below(0x100)
                                     : chance(50) ? 0x100 + below(0x400) : x86::reg32(-1 - x86::sreg32(below(0x400)));
        if (chance(10))
            for (x86::reg32 i = 0; i < 3; ++i)
                g.word(kCmRgb + 4 * i) = chance(50) ? random32() >> below(32) : x86::reg32(-1 - x86::sreg32(random32() >> (1 + below(31))));
        if (chance(15))
            g.word(kCmRgb + 4 * below(3)) = g.word(kCmRgb + 4 * below(3));
        if (chance(10))
            g.word(kCmRgb + 4) = g.word(kCmRgb + 8) = g.word(kCmRgb);
        g.word(kCmRgb + 0xc) = random32();
        cpu.eax = kCmRgb;
        cpu.edx = kCmOut;
    }
    else if (name == "hsvToRgb")
    {
        cpu.eax = kCmHsv;
        cpu.edx = kCmOut;
    }
    else if (name == "tintPixel")
    {
        cpu.eax = chance(80) ? (random32() & 0xffff0000) | (chance(75) ? 0x8000 : 0) | below(0x8000) : random32();
        cpu.edx = kCmHsv;
    }
    else if (name == "scaleTexture" || name == "fitTexture")
    {
        // Pixels a few to 32 each way -- 64 wide for a texture fitted --
        // scaled to a few to 32 each way, or to nothing.
        const bool fit = name == "fitTexture";
        cpu.ebx = chance(5) ? 0 : 1 + below(fit ? 64 : 32);
        cpu.ecx = chance(5) ? 0 : 1 + below(32);
        cmPixels(g, kCmPixels, 0x800);
        cpu.edx = kCmPixels;
        if (fit)
        {
            cpu.eax = kCmTexture - 8;
            stack[0] = cmMost();
            // Now and then a texture up to 256 each way, for the larger powers of two.
            if (chance(5))
            {
                stack[0] = 0x80 + below(0x100);
                cpu.ebx = 0x80 + below(0x100);
                cpu.ecx = 1 + below(8);
            }
            stack[1] = aColor();
            stack[2] = aColor();
        }
        else
        {
            cpu.eax = kCmTexture;
            stack[0] = chance(5) ? 0 : 1 + below(32);
            stack[1] = chance(5) ? 0 : 1 + below(32);
            stack[2] = aColor();
            stack[3] = aColor();
        }
    }
    else if (name == "loadArtTextures")
    {
        const x86::reg32 pictures = chance(10) ? below(2) : chance(90) ? 2 + below(4) : x86::reg32(-1);
        cmModel(g, kCmModel, pictures);
        cmArt(g, kCmPixels, std::min<x86::reg32>(pictures, 6), true, false);
        cmBlockAtZero(g, 0);
        cpu.eax = kCmModel;
        cpu.edx = kCmPixels;
        cpu.ebx = cmMost();
        cpu.ecx = aColor();
    }
    else if (name == "nearestModelColor")
    {
        cmModel(g, kCmModel, 1);
        cpu.eax = kCmModel;
        cpu.edx = chance(50) ? kCmHsv : chance(50) ? kCmModel + 0x800 + 0x10 * below(6) : kCmModel + 0x904 + 0x10 * below(6);
    }
    else if (name == "loadTgaTexture")
    {
        cmModel(g, kCmModel, chance(80) ? 1 : below(3));
        cmTga(g, kCmPixels, chance(80) ? 16 : 40);
        cmBlockAtZero(g, 0);
        // One texture only: the driver taking 4444 now and then, or neither.
        if (chance(40))
            g.getMemory<x86::reg8>(kCmFormats + 0xc) = 0;
        cpu.eax = kCmModel;
        cpu.edx = kCmPixels;
        cpu.ebx = cmMost();
        cpu.ecx = chance(50) ? 0 : random32();
        stack[0] = aColor();
        stack[1] = chance(30) ? 0 : chance(80) ? 1 : random32();
        stack[2] = chance(40) ? 0 : kCmCopy;
    }
    else if (name == "loadCarModel")
    {
        // The two files loaded (0x4e0ec0: the second call, the sixth) put
        // where it puts them: the .fce, a model, and the .art's pictures --
        // the .tga's header among them; the low 64K's dwords about them small.
        const auto loaded = [](x86::reg32 index) {
            const x86::reg32 r = cmPredicted(index, 0x4e0ec0);
            return r % 8 != 0 ? 0x7700 + (r >> 8) % 0x10 * 0x10 : 0;
        };
        const x86::reg32 fce = loaded(1), art = loaded(5);
        const x86::reg32 pictures = chance(45) ? 1 : chance(75) ? 2 + below(3) : chance(50) ? 0 : 5;
        for (const x86::reg32 at : {fce, art})
            for (x86::reg32 i = 0; i < 0x80; ++i)
                g.word(at + 4 * i) = below(4);
        // The pictures' pixels any colour unless the model's count is put
        // among them (or the low dword THRASH_about's none is read from),
        // where a picture's size read from a pixel must be small.
        const bool apart = art != 0 && (fce == art || fce + 0xc < art || fce + 0xc >= art + 0x400);
        cmArt(g, art, std::max<x86::reg32>(pictures, 1), apart && chance(70), true);
        g.getMemory<x86::reg16>(art + 0xc) = x86::reg16(below(9));
        g.getMemory<x86::reg16>(art + 0xe) = x86::reg16(below(9));
        cmModelColors(g, fce);
        g.word(fce + 0xc) = pictures;
        g.word(0x30) = below(4);
        cmBlockAtZero(g, 6);
        // The pictures at 0: over the low bytes the driver's formats are read
        // from where its about is none -- the about stops the case.
        if (art == 0)
            g.word(0x9ef980) = 0;
        cpu.eax = kCmName;
        cpu.edx = cmMost();
        cpu.ebx = chance(80) ? below(8) : random32();
    }
    else if (name == "loadVivCarModel")
    {
        // The .viv's two files where 0x4ea290 says they are (its second call
        // and seventh), the block the .fce goes to (0x4e1620, the third): a
        // model's pictures' count in the file, its colours in the block.
        const x86::reg32 r1 = cmPredicted(1, 0x4ea290), r2 = cmPredicted(2, 0x4e1620), r6 = cmPredicted(6, 0x4ea290);
        const x86::reg32 fce = r1 % 5 == 0 ? 0 : (r1 >> 4) % 0x4000, tga = r6 % 5 == 0 ? 0 : (r6 >> 4) % 0x4000;
        const x86::reg32 block = r2 % 6 == 0 ? 0 : kBlocks + 0x400 * ((r2 >> 8) % 8);
        for (x86::reg32 at = kCmViv; at < kCmViv + 0x4800; at += 4)
            g.word(at) = random32();
        cmTga(g, kCmViv + tga, 16);
        const x86::reg32 pictures = chance(70) ? 1 : below(3);
        g.word(kCmViv + fce + 0xc) = pictures;
        g.word(block + 0xc) = pictures;
        cmModelColors(g, block);
        cmBlockAtZero(g, 7);
        // A block at 0 takes the file's bytes over the low dword THRASH_about's
        // none is read from: small there too.
        if (block == 0)
            g.word(kCmViv + fce + 0x30) = below(4);
        for (x86::reg32 i = 0; i < 4; ++i)
            g.getMemory<x86::reg8>(kCmColorBytes + i) = x86::reg8(chance(80) ? random32() : chance(50) ? 0 : 0xff);
        cpu.eax = kCmCar;
        cpu.edx = kCmName;
        cpu.ebx = cmMost();
        cpu.ecx = chance(30) ? 0 : kCmColorBytes;
        stack[0] = kCmViv;
    }
    else if (name == "copyVivCarModel")
    {
        cmModel(g, kCmModel, 1);
        g.word(kCmCar + 0x8a4) = chance(90) ? kCmModel : 0;
        cpu.eax = kCmCar;
        cpu.edx = kCmName;
        cpu.ebx = kCmViv;
    }
    else if (name == "setSpecUsed" || name == "specUsed" || name == "specCarName")
    {
        cpu.eax = cmPlayer();
        cpu.edx = cmIndex();
        cpu.ebx = random32();
    }
    else if (name == "findSpec")
    {
        // An id a spec has, a car's, or none's.
        const x86::reg32 player = cmPlayer();
        if (chance(50))
            std::memcpy(&g.getMemory<x86::reg8>(kCmId), &g.getMemory<x86::reg8>(0x8b88a0 + 0x960 * (player == 0) + 0x30 * below(50) + 4), 16);
        if (chance(20))
            g.getMemory<x86::reg8>(kCmId + 15) ^= x86::reg8(1 + below(255));
        cpu.eax = player;
        cpu.edx = chance(70) ? kCmId : 0xc00000 + 0x40 * below(64);
    }
    else if (name == "freeSpecSlot")
    {
        // Every spec in use now and then.
        const x86::reg32 player = cmPlayer();
        if (chance(30) && player < 2)
            for (x86::reg32 i = 0; i < 50; ++i)
                g.getMemory<x86::reg8>((player == 0 ? 0x8b9200 : 0x8b88a0) + 0x30 * i) = x86::reg8(chance(98) ? 1 : 0);
        cpu.eax = player;
    }
    else if (name == "setSpec")
    {
        cpu.eax = cmPlayer();
        cpu.edx = cmIndex();
        cpu.ebx = chance(30) ? 0 : kCmId;
        cpu.ecx = chance(30) ? 0 : kCmSpec;
    }
    else if (name == "defaultSpecs" || name == "refreshSpecs" || name == "loadPlayerSpecs"
             || name == "savePlayerSpecs")
    {
        // The specs' file as loaded quietly (trackdata.inc's 0x4e0fe0 gives
        // 0xd0a000 for a case with its mark), and a table all in use now and
        // then.
        g.word(0xd0fffc) = x86::reg32(g_seed);
        for (x86::reg32 i = 0; i < 0x960; i += 4)
            g.word(0xd0a000 + i) = random32();
        for (x86::reg32 i = 0; i < 50; ++i)
            if (chance(50))
                std::memcpy(&g.getMemory<x86::reg8>(0xd0a000 + 0x30 * i + 4), &g.getMemory<x86::reg8>(0xc00000 + 0x40 * below(64)), 16);
        const x86::reg32 player = cmPlayer();
        if (chance(20) && player < 2)
            for (x86::reg32 i = 0; i < 50; ++i)
                g.getMemory<x86::reg8>((player == 0 ? 0x8b9200 : 0x8b88a0) + 0x30 * i) = 1;
        cpu.eax = player;
    }
    else if (name == "specPath")
        cpu.eax = chance(80) ? kCmName : chance(50) ? 0x549784 : 0x54978c;
    else if (name == "readSpecs")
    {
        for (x86::reg32 i = 0; i < 0x1000; i += 4)
            g.word(kCmPixels + i) = random32();
        cpu.eax = cmPlayer();
        cpu.edx = chance(10) ? 0 : kCmPixels;
        cpu.ebx = chance(10) ? below(0x30) : chance(10) ? 0x30 + below(2) : chance(80) ? below(0xa00) : chance(50) ? 0x80000000 | random32() : 0x960;
    }
    return true;
}
#endif
