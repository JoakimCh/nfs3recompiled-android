// game_checks.cpp's parts for what the main menu calls of the game's own: a race started or the game left, the HUD's art, the attract mode's movies, the lists' keys
// (native_frontend_glue.cpp), included in each table with the macro naming the part.
#if defined(FE_WINDOWS)
// {from, to}, -- what the functions write, compared
// The HUD's art's name kept; the dimmed background's shades; the movies'
// switch; the keyboard's ring.
{0x662000, 0x663000}, {0x791000, 0x792000}, {0x7a1000, 0x7a2000}, {0x7f6000, 0x7f7000},
#elif defined(FE_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kFeList,        // findList: one of the three lists' lines (0x61d200 + 0x80 each), where its chosen is kept (0x61d600 + 4 each) to [edx]
kFeKey,         // nextKey: none half the time, else a scan code and a character
kFeMouseKey,    // mouseKey: none, Enter or Escape
kFeFlagByte,    // a dialog shown: al 0 or 1, the rest of eax anything
#elif defined(FE_EFFECT_CASES)
// case kSomething: ... break;
case kFeList:
{
    // makeFeGlueWorld's lists and their chosen lines.
    const x86::reg32 list = r % 3;
    result = 0x61d200 + 0x80 * list;
    if (cpu.edx < kMemory - 4)
        word(cpu.edx) = 0x61d600 + 4 * list;
    break;
}
case kFeKey:
    result = r % 2 == 0 ? 0 : ((r >> 8) % 0x80) << 16 | (r >> 16) % 0x100;
    break;
case kFeFlagByte:
    result = (r & 0xffffff00) | (r >> 8) % 2;
    break;
case kFeMouseKey:
    result = r % 3 == 0 ? 0 : r % 3 == 1 ? 0xd : 0x1b;
    break;
#elif defined(FE_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// This file's that the other files' natives call: a list found by its name
// (logged), the network's locks freed, the mouse as a key, the keyboard's
// next key.
{0x442c80, "a list found", kWatcom, 2, 0, kEax | kEdx, 0, 2, kFeList},
{0x49a4d0, "the network's locks freed", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x49c080, "the mouse as a key", kWatcom, 0, 0, kEax, -1, 0, kFeMouseKey},
{0x4cc970, "the next key", kWatcom, 0, 0, kEax, -1, 0, kFeKey},
// What they call of the game's: the menus' click; the music stopped, a tune
// started, the music's stream ended and made again; both buffers cleared
// (and the textures reset); a codelink's name matched (the name logged), a
// dialog up; a movie played (its path logged, and the frame up to the
// slow processor's flag edx points at); the quads' indices.
{0x4181d0, "a menu effect played", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4109d0, "the music stopped", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4104f0, "a tune started", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x410aa0, "the music's stream ended", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x410330, "the music's stream made", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d5d30, "both buffers cleared", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4d5d70, "both buffers cleared, the textures reset", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4429c0, "a codelink matches", kWatcom, 2, 0, kEax, 1, 2, kMainThread},
{0x4438b0, "a dialog shown", kWatcom, 0, 0, kEax, -1, 0, kFeFlagByte},
{0x495bc0, "a movie played", kStdcall, 4, 1, kEax, 0, 64, kNothing},
{0x4c1e20, "the quads' indices", kWatcom, 3, 0, kEax, -1, 0, kNothing},
#elif defined(FE_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// A button's handler (+0x64), by pseudo-slot.
{0xfff6c0, "a button's handler", kWatcom, 1, 0, kEax, -1, 0, kNothing},
#elif defined(FE_PROMISES)
// {"frontend::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared; the x87's stack too where a float goes through it.
{"frontend::bindingIsDigital", true, true, 0},
{"frontend::noteDigitalControls", true, true, 0},
{"frontend::listAllowed", true, true, 0},
{"frontend::listLength", true, true, 0},
{"frontend::findList", true, true, 0},
{"frontend::loadShapes", true, true, 0},
{"frontend::buttonKey", true, true, 0},
{"frontend::listKey", true, true, 0},
{"frontend::layoutList", true, true, 0},
{"frontend::sliderValue", true, true, 0, true, kNoHeap, true},
{"frontend::sliderSetOnMove", true, true, 0},
{"frontend::sliderSetColour", true, true, 0},
{"frontend::playMovie", true, true, 0},
{"frontend::resetAttractTimer", true, true, 0},
{"frontend::attractMode", true, true, 0},
{"frontend::freeNetworkLocks", true, true, 0},
{"frontend::allPlayersReady", true, true, 0},
{"frontend::mouseKey", true, true, 0},
{"frontend::pointerInBox", true, true, 0},
{"frontend::nextKey", true, true, 0},
#elif defined(FE_ARGUMENTS)
/* Where the glue's cases keep their own: an item of a screen; the three
 * lists' lines (0x80 bytes each, zeros past their end); which lines of the
 * four lists may be chosen; where the three lists' chosen are kept; the
 * lists' names; a name or a text handed in; a box; four dwords handed out. */
constexpr x86::reg32 kFeItem = 0x61d000, kFeLines = 0x61d200, kFeAllowed = 0x61d400;
constexpr x86::reg32 kFeChosen = 0x61d600, kFeNames = 0x61d800, kFeName = 0x61d900;
constexpr x86::reg32 kFeBox = 0x61da00, kFeOut = 0x61da40;

/* A string of `text` at `at`. */
void feString(CheckApp& g, x86::reg32 at, const char* text)
{
    do
        g.getMemory<char>(at++) = *text;
    while (*text++ != 0);
}

/* A word's worth of the menus' screen: within it mostly, off it now and then. */
x86::reg16 feScreenWord(x86::reg32 most)
{
    return x86::reg16(chance(90) ? below(most) : chance(50) ? below(most + 200) - 100 : random32());
}

/* The glue's world, on the menus' (the fonts, the viewport -- never 0 wide
 * or high --, the pointer, the mouse, the race's pause screens or not): the
 * lists' table at 0x5563e8 -- four lists, lstA to lstD, their lines the
 * three of kFeLines, whose chosen are within them -- now and then empty;
 * a screen's item of random words; the controllers; the network's
 * players; the movies, the clock, the attract mode; the keyboard's ring;
 * the HUD's art. */
void makeFeGlueWorld(CheckApp& g, x86::CPU& cpu)
{
    makeMenusWorld(g, cpu);
    for (x86::reg32 at = 0x7cda78; at < 0x7cda80; at += 4)
        if (g.word(at) == 0)
            g.word(at) = 1;
    // The lists' lines and their chosen.
    for (x86::reg32 at = kFeLines; at < kFeLines + 0x180; at += 4)
        g.word(at) = 0;
    for (x86::reg32 list = 0; list < 3; ++list)
    {
        const x86::reg32 length = chance(10) ? 0 : 1 + below(chance(70) ? 12 : 0x37);
        for (x86::reg32 i = 0; i < length; ++i)
            g.getMemory<x86::reg16>(kFeLines + 0x80 * list + 2 * i) = x86::reg16(1 + below(0x900));
        g.word(kFeChosen + 4 * list) = length == 0 ? 0 : below(length);
    }
    // Which may be chosen: half of them, now and then none.
    for (x86::reg32 list = 0; list < 4; ++list)
    {
        const bool none = chance(15);
        for (x86::reg32 at = kFeAllowed + 0x80 * list; at < kFeAllowed + 0x80 * (list + 1); at += 2)
            g.getMemory<x86::reg16>(at) = x86::reg16(none || chance(50) ? 0 : chance(80) ? 1 : random32());
    }
    static const char* const names[] = {"lstA", "lstB", "lstC", "lstD", "nolist", ""};
    for (x86::reg32 i = 0; i < 6; ++i)
        feString(g, kFeNames + 0x10 * i, names[i]);
    const x86::reg32 lists = chance(10) ? 0 : 1 + below(4);
    for (x86::reg32 i = 0; i < 5; ++i)
    {
        const x86::reg32 entry = 0x5563e8 + 0x14 * i;
        g.word(entry) = i < lists ? kFeNames + 0x10 * i : 0;
        g.word(entry + 4) = kFeLines + 0x80 * (i % 3);
        g.word(entry + 8) = chance(15) ? 0 : kFeAllowed + 0x80 * i;
        g.word(entry + 0xc) = random32();
        g.word(entry + 0x10) = kFeChosen + 4 * (i % 3);
    }
    // An item: random words, its strings ours.
    for (x86::reg32 at = kFeItem; at < kFeItem + 0x100; at += 4)
        g.word(at) = random32();
    g.word(kFeItem + 0x10) = kFeNames + 0x10 * below(6);
    // The controllers' kinds, the device sets' bindings: a controller's (1) often.
    for (x86::reg32 c = 0; c < 16; ++c)
        g.getMemory<x86::reg8>(0x6fc970 + 0x88 * c) = x86::reg8(random32());
    for (x86::reg32 at = 0x6fd20c; at < 0x6fd2a8; at += 4)
        g.word(at) = chance(50) ? (random32() & 0xffffff00) | 1 : random32();
    g.word(0x6fd3b0) = chance(90) ? below(3) : random32();
    g.word(0x6fd3b8) = chance(30) ? 3 : below(5);
    // The network: a race over it, this machine the host, ready; its players
    // and theirs ready.
    g.word(0x7a22e0) = chance(30) ? 0 : chance(80) ? 1 : random32();
    g.getMemory<x86::reg16>(0x7a22da) = x86::reg16(chance(50) ? 0 : 1);
    g.word(0x6fd508) = chance(40) ? 0 : chance(80) ? 1 : random32();
    g.word(0x7a2274) = (chance(90) ? below(9) : random32() % 0x10000) << 16 | (random32() & 0xffff);
    for (x86::reg32 at = 0x79f500; at < 0x79f9a0; ++at)
        g.getMemory<x86::reg8>(at) = x86::reg8(random32());
    for (x86::reg32 slot = 0; slot < 8; ++slot)
        g.getMemory<x86::reg8>(0x79f5f8 + 0x60 * slot) = x86::reg8(chance(80) ? 1 : 0);
    // The mouse where the menus have it, the buttons, where it was.
    g.word(0x55e5e4) = chance(90) ? below(640) : random32();
    g.word(0x55e5e8) = chance(90) ? below(480) : random32();
    g.word(0x55e5ec) = random32();
    g.word(0x55e5f4) = random32();
    g.word(0x55e5f8) = random32();
    g.word(0x55e550) = chance(70) ? g.word(0x55e5e4) : random32();
    g.word(0x55e554) = chance(70) ? g.word(0x55e5e8) : random32();
    g.getMemory<x86::reg8>(0x55eb2e) = x86::reg8(random32());
    // The movies: off, their folder, the processor's speed; the clock and the
    // attract mode's wait, its movie, its being off, the menus' music's volume.
    g.word(0x7a1fdc) = chance(80) ? 0 : chance(50) ? 1 : random32();
    static const char* const folders[] = {"", "fedata\\movies\\", "D:\\nfs3\\gamedata\\movies\\", "m\\"};
    feString(g, 0x7a32b4, folders[below(4)]);
    static const x86::reg32 speeds[] = {0x7ed6b40, 0xbebc200, 0};
    g.word(0x5652a4) = chance(30) ? speeds[below(3)] + below(3) - 1 : chance(80) ? below(0x10000000) : random32();
    g.word(0x79c1a4) = random32();
    g.word(0x55e548) = g.word(0x79c1a4) - (chance(90) ? 0x1400 + below(0x20) - 0x10 : random32());
    g.word(0x55e54c) = chance(85) ? below(4) : chance(50) ? 4 + below(4) : random32();
    g.word(0x6fbb54) = chance(80) ? 0 : random32();
    g.word(0x6fbbe8) = random32();
    // The network's locks.
    for (const x86::reg32 at : {0x55e5b8u, 0x55ecb4u, 0x55ecb8u})
        g.word(at) = chance(20) ? 0 : random32();
    // The keyboard's ring: its size (0x125 at most, the ring's room), where
    // it is read and written, each key a scan code and its shifts or with a
    // character; its lock.
    const x86::reg32 size = chance(80) ? 1 + below(0x40) : 1 + below(0x125);
    g.word(0x7f7480) = size;
    g.word(0x7f7474) = below(size);
    g.word(0x7f747c) = chance(20) ? g.word(0x7f7474) : below(size);
    for (x86::reg32 i = 0; i < 0x125; ++i)
        g.word(0x7f6fe0 + 4 * i) = chance(60) ? below(0x10000) : random32();
    g.word(0x7f7478) = random32();
    // The HUD's art: the language, the shapes kept or none, their name.
    g.word(0x6fbb4c) = chance(85) ? below(7) : random32();
    g.word(0x55922c) = chance(30) ? 0 : kBlocks + 0x400 * below(8);
    static const char* const huds[] = {"hud.fsh", "art\\hud.fsh", "front.fsh", "art\\GeHud.fsh", "hud.fshx"};
    feString(g, 0x662850, huds[below(5)]);
}

/* The item as a list: its name one of the table's (or none of them), open
 * or closed, beside or under it, its box, its line chosen and the lines it
 * shows. */
void makeFeList(CheckApp& g)
{
    g.word(kFeItem + 0x64) = kFeNames + 0x10 * (chance(80) ? below(4) : 4 + below(2));
    g.getMemory<x86::reg16>(kFeItem + 0x40) = x86::reg16(chance(45) ? 0 : chance(90) ? 1 : random32());
    for (const x86::reg32 at : {0x52u, 0x54u})
        g.getMemory<x86::reg16>(kFeItem + at) = x86::reg16(chance(50) ? 0 : chance(90) ? 1 : random32());
    g.getMemory<x86::reg16>(kFeItem + 6) = feScreenWord(640);
    g.getMemory<x86::reg16>(kFeItem + 8) = feScreenWord(480);
    g.getMemory<x86::reg16>(kFeItem + 0x1a) = feScreenWord(480);
    g.getMemory<x86::reg16>(kFeItem + 0x1c) = feScreenWord(640);
    g.getMemory<x86::reg16>(kFeItem + 0x1e) = feScreenWord(400);
    g.getMemory<x86::reg16>(kFeItem + 0x20) = feScreenWord(300);
    g.getMemory<x86::reg16>(kFeItem + 0x56) = x86::reg16(chance(85) ? below(0x40) - 4 : random32());
    g.getMemory<x86::reg16>(kFeItem + 0x58) = x86::reg16(chance(90) ? 1 + below(12) : random32());
    g.getMemory<x86::reg16>(kFeItem + 0x5a) = x86::reg16(chance(90) ? 1 + below(12) : random32());
    const x86::reg16 first = x86::reg16(chance(85) ? below(0x38) : random32());
    g.getMemory<x86::reg16>(kFeItem + 0x5c) = first;
    g.getMemory<x86::reg16>(kFeItem + 0x5e) = x86::reg16(chance(80) ? first + below(12) : random32());
}

bool makeFeGlueArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "bindingIsDigital", "noteDigitalControls", "listAllowed", "listLength", "findList", "loadShapes",
        "setTextColour", "screenToMenuX", "screenToMenuY", "readMenuMouse", "dimBackground", "drawTextAt",
        "drawMenuText", "buttonKey", "listKey", "layoutList", "sliderSetValue", "sliderValue",
        "sliderSetOnMove", "sliderDraw", "sliderSetColour", "playMovie", "resetAttractTimer", "attractMode",
        "freeNetworkLocks", "allPlayersReady", "flushQuads", "mouseKey", "pointerInBox", "nextKey"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeFeGlueWorld(g, cpu);
    const x86::reg32 text = kStrings + 0x40 * 62;
    aMenuText(g, text, 30);
    // A list's name: of the table's mostly, none of them, an empty one, none.
    const auto aListName = [] {
        return chance(5) ? 0 : kFeNames + 0x10 * (chance(80) ? below(4) : 4 + below(2));
    };
    if (name == "bindingIsDigital")
        cpu.eax = (random32() & 0xffffff00) | (chance(60) ? 1 : chance(50) ? 0x81 : below(0x100));
    else if (name == "listAllowed" || name == "findList" || name == "listLength")
    {
        cpu.eax = aListName();
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
    else if (name == "screenToMenuX" || name == "screenToMenuY")
        cpu.eax = chance(90) ? below(2000) - 300 : random32();
    else if (name == "readMenuMouse")
    {
        cpu.eax = kFeOut;
        cpu.edx = kFeOut + 4;
        cpu.ebx = kFeOut + 8;
        cpu.ecx = kFeOut + 0xc;
        for (x86::reg32 i = 0; i < 4; ++i)
            g.word(kFeOut + 4 * i) = chance(80) ? below(1000) : random32();
    }
    else if (name == "dimBackground")
    {
        static const float values[] = {0.0f, 0.5f, 0.6f, 0.59999f, 0.60001f, 1.0f, 0.99999f, 1.5f, -1.0f};
        const float value = values[below(9)];
        std::memcpy(&stack[0], &value, 4);
        if (chance(10))
            stack[0] = random32();
        for (x86::reg32 at = 0x791b4c; at < 0x791b58; at += 4)
            g.word(at) = chance(80) ? anyFloatBits((std::uint64_t(random32()) << 32) | random32()) : random32();
    }
    else if (name == "drawTextAt" || name == "drawMenuText")
    {
        cpu.eax = name == "drawMenuText" && chance(10) ? 0 : text;
        cpu.edx = chance(90) ? below(640) : random32();
        cpu.ebx = chance(90) ? below(480) : random32();
        cpu.ecx = chance(80) ? below(4) : random32();
        stack[0] = chance(90) ? below(7) : random32();
        stack[1] = random32();
    }
    else if (name == "buttonKey")
    {
        g.word(kFeItem + 0x58) = chance(50) ? 0 : aListName();
        g.word(kFeItem + 0x64) = chance(50) ? 0 : standInFor(0xfff6c0);
        g.word(kFeItem + 0x40) = chance(50) ? 0 : random32();
        g.getMemory<x86::reg16>(kFeItem + 0x48) = x86::reg16(chance(50) ? 0xf : random32());
        cpu.eax = kFeItem;
        cpu.ebx = (random32() & 0xffff0000) | (chance(80) ? 0xd : random32() & 0xffff);
    }
    else if (name == "listKey" || name == "layoutList")
    {
        makeFeList(g);
        static const x86::reg32 keys[] = {0xd, 0x1b, 0x4b00, 0x4d00, 0x4800, 0x5000, 0x4900, 0x5100};
        cpu.eax = kFeItem;
        cpu.ebx = (random32() & 0xffff0000) | (chance(90) ? keys[below(8)] : random32() & 0xffff);
    }
    else if (name == "sliderSetValue" || name == "sliderValue" || name == "sliderSetOnMove"
             || name == "sliderDraw" || name == "sliderSetColour")
    {
        g.getMemory<x86::reg16>(kFeItem + 0x42) = x86::reg16(chance(90) ? below(7) : random32());
        if (chance(50))
            g.getMemory<x86::reg16>(kFeItem + 0x18) = x86::reg16(chance(50) ? 0 : 1);
        cpu.eax = kFeItem;
        cpu.edx = chance(40) ? 0 : chance(60) ? 1 : random32();
        stack[0] = aPlace();
        stack[1] = chance(80) ? below(2) : random32();
    }
    else if (name == "playMovie")
    {
        static const char* const movies[] = {"titleav.mad", "demoav1.mad", "x.mad", ""};
        feString(g, kFeName, movies[below(4)]);
        cpu.eax = kFeName;
    }
    else if (name == "flushQuads")
    {
        // A font's list: its texture, its frame, its quads (four indices
        // each, so many that they are a quad's: 4 at a time mostly), each
        // index's frame.
        const x86::reg32 list = 0x7f74c0 + 0x24010 * below(2);
        g.word(list) = random32();
        g.word(list + 4) = chance(80) ? below(0x10) : random32();
        g.word(list + 0xc) = chance(15) ? 0 : chance(90) ? 4 * below(0x10) : below(0x40);
        for (x86::reg32 i = 0; i < 0x48; ++i)
            g.word(list + 0x20010 + 4 * i) = chance(80) ? below(0x10) : random32();
        cpu.eax = list;
    }
    else if (name == "pointerInBox")
    {
        // A box near the pointer: y, x, width, height.
        const x86::reg32 x = g.word(0x55e5e4), y = g.word(0x55e5e8);
        g.getMemory<x86::reg16>(kFeBox) = x86::reg16(chance(80) ? y - below(40) + 5 : random32());
        g.getMemory<x86::reg16>(kFeBox + 2) = x86::reg16(chance(80) ? x - below(40) + 5 : random32());
        g.getMemory<x86::reg16>(kFeBox + 4) = x86::reg16(chance(80) ? below(60) : random32());
        g.getMemory<x86::reg16>(kFeBox + 6) = x86::reg16(chance(80) ? below(60) : random32());
        for (x86::reg32 at = kFeBox + 8; at < kFeBox + 0x10; at += 4)
            g.word(at) = random32();
        cpu.eax = kFeBox;
    }
    return true;
}
#endif
