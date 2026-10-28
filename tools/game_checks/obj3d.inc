// game_checks.cpp's parts for the menus' 3D object (src/nfs3hp/port_obj3d.cpp,
// nfs3hp::port::obj3d), included in each table with the macro naming the part.
// The world is the menus' drawing's (frontend_draw.inc's makeFeDrawWorld), the
// cars' (load_cardb.inc, load_carmodels.inc), and the object's own: its menu
// item, its loader, a model, a .viv's header, in the cases' area below.
#if defined(OBJ3D_WINDOWS)
// {from, to}, -- what the functions write, compared
// The cases' area; the random car drawn last; the model's names, the logo's
// place; the code's tables the object copies (made up as nfs3.exe has them).
{0xe40000, 0xe48000}, {0x55a000, 0x55b000}, {0x678000, 0x679000}, {0x465d00, 0x465d80},
#elif defined(OBJ3D_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kObj3dPair,     // the renderer's lists (0x4bbe70, 0x4bbe90, 0x4bbec0, 0x49c470, 0x4c7380): a list's pair at esi, none first
kObj3dVectors,  // vertices::rotateVectors (0x4e03b0): eax vectors of three floats to [ecx]
kObj3dVivEntry, // ea::findVivEntry (0x4679f0): a file's offset to [ebx], its size to [ecx]; none now and then
#elif defined(OBJ3D_EFFECT_CASES)
// case kSomething: ... break;
case kObj3dPair:
    // The list's first record none (what a list's records are, the renderer
    // walks), its last any; the pair's address back, as the real ones do.
    if (cpu.esi < kMemory - 8)
    {
        word(cpu.esi) = 0;
        word(cpu.esi + 4) = r;
    }
    result = cpu.esi;
    break;
case kObj3dVectors:
    for (x86::reg32 i = 0; i < 3 * std::min<x86::reg32>(words[0], 4) && words[3] < kMemory - 0x40; ++i)
    {
        const float f = float(x86::sreg32(random(id + 0x40 + i) % 4001) - 2000) / 100.0f;
        std::memcpy(&word(words[3] + 4 * i), &f, 4);
    }
    break;
case kObj3dVivEntry:
    if (words[2] < kMemory - 4 && words[3] < kMemory - 4)
    {
        word(words[2]) = r % 5 == 0 ? 0 : (r >> 8) % 0x10000;
        word(words[3]) = (r >> 4) % 5 == 0 ? 0 : (r >> 12) % 0x400;
    }
    break;
#elif defined(OBJ3D_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// What the object calls of the renderer that hands back through a pointer:
// the lists' pairs (taken in esi), a light turned, a model drawn (its float
// left on the x87, which the object pops).
{0x4bbe70, "a list emptied", kWatcom, 0, 0, kEax, -1, 0, kObj3dPair},
{0x4bbe90, "a list of one record", kWatcom, 1, 0, kEax, -1, 0, kObj3dPair},
{0x4bbec0, "two lists joined", kStdcall, 0, 4, kEax, -1, 0, kObj3dPair},
{0x49c470, "the drawn records taken", kWatcom, 0, 0, kEax, -1, 0, kObj3dPair},
{0x4c7380, "a list sorted", kStdcall, 0, 2, kEax, -1, 0, kObj3dPair},
{0x4e03b0, "vectors turned", kWatcom, 4, 0, kEax, 1, 3, kObj3dVectors},
{0x49de20, "a model drawn", kStdcall, 4, 5, kEax, -1, 0, kFloatBack},
// load::loadTgaTexture, which only the object calls by address: its texture
// would be made in a block of the game's at 0 now and then, over what the
// driver's about is read from when there is none (load_carmodels.inc's
// cmBlockAtZero); held against its code on its own.
{0x49d320, "a model's texture from a .tga", kStdcall, 4, 3, kEax, -1, 0, kNothing},
// ea::findVivEntry, which only the object calls by address: the header it
// walks is the one the object's reads asked for, which the stand-ins never
// fill (and each part's read byte-swaps its count again, as the game's code
// does); held against its code on its own.
{0x4679f0, "a .viv's entry found", kWatcom, 4, 0, kEax, 1, 2, kObj3dVivEntry},
#elif defined(OBJ3D_PROMISES)
// {"port::obj3d::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax, esi, edi, ebp, esp; the x87's stack, its live registers and its words.
{"port::obj3d::carVivPath", true, true, 0, true, kNoHeap, true},
{"port::obj3d::flareQuad", true, true, 0, true, kNoHeap, true},
{"port::obj3d::lightPlaced", true, true, 0, true, kNoHeap, true},
{"port::obj3d::headlightGlare", true, true, 0, true, kNoHeap, true},
{"port::obj3d::taillightGlare", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectLights", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectDragged", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectBounds", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectDraw", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectKeyed", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectPassed", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectReleased", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectOpened", true, true, 0, true, kNoHeap, true},
{"port::obj3d::objectClosed", true, true, 0, true, kNoHeap, true},
{"port::obj3d::resetLoader", true, true, 0, true, kNoHeap, true},
{"port::obj3d::genericVivPath", true, true, 0, true, kNoHeap, true},
{"port::obj3d::genericModelName", true, true, 0, true, kNoHeap, true},
{"port::obj3d::trackVivPath", true, true, 0, true, kNoHeap, true},
{"port::obj3d::trackModelName", true, true, 0, true, kNoHeap, true},
{"port::obj3d::chooseFiles", true, true, 0, true, kNoHeap, true},
{"port::obj3d::readPrehead", true, true, 0, true, kNoHeap, true},
{"port::obj3d::readHead", true, true, 0, true, kNoHeap, true},
{"port::obj3d::readModel", true, true, 0, true, kNoHeap, true},
{"port::obj3d::readTexture", true, true, 0, true, kNoHeap, true},
{"port::obj3d::readShapes", true, true, 0, true, kNoHeap, true},
{"port::obj3d::takeModel", true, true, 0, true, kNoHeap, true},
{"port::obj3d::fadeIn", true, true, 0, true, kNoHeap, true},
{"port::obj3d::fadeOut", true, true, 0, true, kNoHeap, true},
{"port::obj3d::wantedChanged", true, true, 0, true, kNoHeap, true},
{"port::obj3d::runLoader", true, true, 0, true, kNoHeap, true},
{"port::obj3d::carColour", true, true, 0, true, kNoHeap, true},
{"port::obj3d::makeTexture", true, true, 0, true, kNoHeap, true},
{"port::obj3d::drawLogo", true, true, 0, true, kNoHeap, true},
#elif defined(OBJ3D_ARGUMENTS)
/* The object's world: its item, its loader, its model and its copy, a .viv's
 * header, the buffers the functions write to. */
constexpr x86::reg32 kObjItem = 0xe40000, kObjLoader = 0xe40200, kObjViv = 0xe41000, kObjModel = 0xe42000;
constexpr x86::reg32 kObjOut = 0xe44000, kObjPath = 0xe45000;

/* A float of a sane size: within `range` either side of 0, now and then 0
 * or a small one. */
x86::reg32 anObjFloat(float range)
{
    const float f = chance(5) ? 0.0f : (float(below(20001)) / 10000.0f - 1.0f) * range;
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

/* A depth in front of the eye mostly. */
x86::reg32 anObjDepth()
{
    return chance(90) ? anObjFloat(1.0f) & 0x7fffffff | (chance(5) ? 0 : 0x40000000) : anObjFloat(10.0f);
}

x86::reg32 anObjBlock()
{
    return chance(15) ? 0 : kBlocks + 0x400 * below(8);
}

/* A short name of the menus' letters. */
void anObjName(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    const x86::reg32 length = below(most);
    for (x86::reg32 i = 0; i < length; ++i)
        g.getMemory<x86::reg8>(at + i) = x86::reg8('a' + below(26));
    g.getMemory<x86::reg8>(at + length) = 0;
}

void makeObj3dWorld(CheckApp& g, x86::CPU& cpu)
{
    makeFeDrawWorld(g, cpu);
    makeCardbWorld(g);
    makeCarmodelsWorld(g);
    // The code's tables the object copies: the light's direction, the
    // identity, the colours of none.
    static const x86::reg32 tables[] = {0x3f800000, 0, 0xbf800000, 0x3f800000, 0, 0, 0, 0x3f800000, 0, 0, 0, 0x3f800000};
    for (x86::reg32 i = 0; i < 12; ++i)
        g.word(0x465d10 + 4 * i) = tables[i];
    for (x86::reg32 at = 0x465d40; at < 0x465d60; at += 4)
        g.word(at) = chance(90) ? 0 : random32();
    // The stack below the caller's: none of what a stand-in leaves unwritten
    // is a pointer the renderer walks.
    for (x86::reg32 at = cpu.esp - 0x1000; at < cpu.esp; at += 4)
        g.word(at) = 0;
    for (x86::reg32 at = 0xe40000; at < 0xe48000; at += 4)
        g.word(at) = random32();
    // The model, as the models' textures take one (load_carmodels.inc), its
    // texture's .tga at kCmPixels: its box, its lights (headlights and taillights mostly),
    // its parts, its colours.
    cmModel(g, kObjModel, chance(80) ? 1 : below(3));
    cmTga(g, kCmPixels, 16);
    for (x86::reg32 i = 0; i < 3; ++i)
        g.word(kObjModel + 0x28 + 4 * i) = chance(95) ? anObjFloat(3.0f) & 0x7fffffff : random32();
    const x86::reg32 lights = chance(10) ? 0 : below(6);
    g.word(kObjModel + 0x34) = lights;
    for (x86::reg32 i = 0; i < 3 * 6; ++i)
        g.word(kObjModel + 0x38 + 4 * i) = anObjFloat(3.0f);
    g.word(kObjModel + 0xf8) = below(20);
    g.word(kObjModel + 0x7fc) = chance(20) ? 0 : 1 + below(4);
    // What the model's stand-in "made ready" hands back is what it was handed:
    // the models read are the model, the textures read the .tga.
    for (x86::reg32 i = 0; i < 6; ++i)
        g.getMemory<x86::reg8>(kObjModel + 0xa04 + 0x40 * i) = x86::reg8(chance(40) ? 0x48 : chance(60) ? 0x54 : random32());
    // The .viv's header: its files' count and size (big-endian), its entries.
    const x86::reg32 entries = below(4);
    auto big = [](x86::reg32 v) { return v >> 24 | (v >> 8 & 0xff00) | (v << 8 & 0xff0000) | v << 24; };
    g.word(kObjViv) = random32();
    g.word(kObjViv + 4) = random32();
    g.word(kObjViv + 8) = big(entries);
    g.word(kObjViv + 0xc) = big(below(0x400));
    x86::reg32 entry = kObjViv + 0x10;
    for (x86::reg32 i = 0; i < entries; ++i)
    {
        g.word(entry) = big(chance(10) ? 0 : below(0x10000));
        g.word(entry + 4) = big(chance(10) ? 0 : below(0x400));
        anObjName(g, entry + 8, 12);
        entry += 8;
        while (g.getMemory<x86::reg8>(entry) != 0)
            ++entry;
        ++entry;
    }
    // The game's blocks, where a .viv's header is read into (the loader's
    // own block, made afresh when the object is shown): a header of no
    // files -- each part's read byte-swaps the header's count again, as the
    // game's code does, and only 0 is few files both ways round.
    for (x86::reg32 b = 0; b < 8; ++b)
    {
        const x86::reg32 block = kBlocks + 0x400 * b;
        g.word(block + 8) = 0;
        for (x86::reg32 at = block + 0x10; at < block + 0x80; at += 4)
            g.word(at) = random32() & 0x7f7f7f7f;
        g.getMemory<x86::reg8>(block + 0x80) = 0;
    }
    // The loader: its names (one of the .viv's now and then), its reads,
    // its header, its blocks, its state and what it waits on.
    for (x86::reg32 i = 0; i < 4; ++i)
        anObjName(g, kObjLoader + (i == 0 ? 0 : 0xe0 + 0x20 * i), 12);
    if (entries != 0 && chance(50))
        for (x86::reg32 i = 1; i < 4; ++i)
            for (x86::reg32 c = 0; c < 0x10; ++c)
                g.getMemory<x86::reg8>(kObjLoader + 0xe0 + 0x20 * i + c) = g.getMemory<x86::reg8>(kObjViv + 0x18 + c);
    for (x86::reg32 i = 0; i < 5; ++i)
        g.word(kObjLoader + 0x160 + 4 * i) = chance(20) ? 0 : random32();
    g.word(kObjLoader + 0x180) = big(below(0x400));
    g.word(kObjLoader + 0x184) = below(0x400);
    g.word(kObjLoader + 0x188) = chance(15) ? 0 : kObjViv;
    g.word(kObjLoader + 0x18c) = chance(15) ? 0 : kObjModel;
    g.word(kObjLoader + 0x190) = chance(15) ? 0 : kCmPixels;
    g.word(kObjLoader + 0x194) = anObjBlock();
    g.word(kObjLoader + 0x198) = chance(90) ? below(10) : random32();
    g.word(kObjLoader + 0x19c) = chance(90) ? below(9) : random32();
    // The item: its kind (a player's car, a random one, a track, the generic
    // car, the split screen's, the cars shown), its state.
    static const x86::reg16 kinds[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 0, 7, 11};
    g.getMemory<x86::reg16>(kObjItem + 0x80) = x86::reg16(chance(95) ? kinds[below(12)] : random32());
    g.getMemory<x86::reg8>(kObjItem + 5) = x86::reg8(random32());
    g.word(kObjItem + 0x3c) = chance(15) ? 0 : kObjModel;
    g.word(kObjItem + 0x40) = anObjBlock();
    for (x86::reg32 i = 0; i < 6; ++i)
        g.word(kObjItem + 0x44 + 4 * i) = anObjFloat(i < 3 ? 360.0f : 5.0f);
    g.word(kObjItem + 0x5c) = anObjFloat(2.0f);
    g.word(kObjItem + 0x60) = anObjFloat(2.0f);
    g.word(kObjItem + 0x64) = anObjDepth();
    for (x86::reg32 i = 0; i < 6; ++i)
        g.word(kObjItem + 0x68 + 4 * i) = anObjFloat(i < 3 ? 1.0f : 0.02f);
    g.getMemory<x86::reg16>(kObjItem + 0x82) = x86::reg16(below(2));
    g.word(kObjItem + 0x84) = chance(20) ? 0 : below(20) << 16 | below(2);
    g.getMemory<x86::reg8>(kObjItem + 0x88) = x86::reg8(chance(70) ? 0 : chance(90) ? 1 : random32());
    g.getMemory<x86::reg16>(kObjItem + 0x8a) = x86::reg16(below(640));
    g.word(kObjItem + 0x8c) = chance(90) ? below(0x100) : random32();
    const x86::reg32 clock = g.word(0x79c1a4);
    g.word(kObjItem + 0x90) = chance(10) ? 0 : clock - below(0x40);
    g.word(kObjItem + 0x94) = chance(20) ? clock : clock - below(8);
    g.word(kObjItem + 0x98) = clock - below(8);
    g.getMemory<x86::reg16>(kObjItem + 0x9c) = x86::reg16(below(10));
    g.getMemory<x86::reg16>(kObjItem + 0x9e) = x86::reg16(chance(20) ? 0xffff : below(10));
    g.word(kObjItem + 0xa0) = clock - below(0x100);
    g.word(kObjItem + 0xa4) = chance(15) ? 0 : random32() | 1;  // a texture handle, as the models' cases make one
    g.word(kObjItem + 0xa8) = chance(15) ? 0 : kObjModel;
    g.word(kObjItem + 0xac) = chance(15) ? 0 : kCmPixels;
    for (x86::reg32 i = 0; i < 5; ++i)
        g.getMemory<x86::reg8>(kObjItem + 0xb0 + i) = x86::reg8(chance(50) ? 0 : 1);
    g.word(kObjItem + 0xb8) = chance(10) ? 0 : kObjLoader;
    // The menus' globals the object reads: whose cars, the track, the
    // players, the mouse, over a race or not, the pause, the flares' and
    // the logo's textures, the projection, the renderer's states.
    for (const x86::reg32 at : {0x6fd2bcu, 0x6fd328u, 0x6fd4acu, 0x664788u, 0x664784u})
        g.word(at) = chance(90) ? below(10) : random32();
    g.word(0x6fd4d4) = chance(90) ? below(8) : random32();
    g.word(0x55a4dc) = below(8);
    g.word(0x555748) = chance(80) ? 0 : 1;
    g.getMemory<x86::reg8>(0x55eb2f) = x86::reg8(chance(70) ? random32() & ~0x40u : random32() | 0x40);
    g.word(0x553030) = below(2);
    g.word(0x553034) = below(2);
    g.word(0x55302c) = anObjFloat(1.0f);
    g.word(0x678a54) = chance(10) ? 0 : random32();
    g.word(0x55a4d4) = chance(20) ? 0 : random32();
    g.word(0x55a4d8) = random32();
    g.word(0x55a4d0) = random32();
    g.word(0x554e4c) = random32();
    g.word(0x7a3a60) = chance(50) ? 0 : random32();
    g.word(0x56009c) = anObjFloat(400.0f);
    g.word(0x5600a0) = anObjFloat(400.0f);
    g.word(0x5600a4) = anObjFloat(400.0f);
    g.word(0x5600a8) = anObjFloat(300.0f);
    g.word(0x79c1a4) = clock;
}

bool makeObj3dArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    makeObj3dWorld(g, cpu);
    // Many of the loader's steps and the object's draw: a few hundred calls.
    g_mostCalls = 400;
    const x86::reg32 item = chance(5) ? 0 : kObjItem;
    cpu.eax = item;
    cpu.edx = chance(50) ? 0 : chance(90) ? 1 : random32();
    if (name == "carVivPath")
    {
        cpu.eax = below(8);
        cpu.edx = kObjPath;
    }
    else if (name == "flareQuad")
    {
        stack[0] = anObjFloat(3.0f);
        stack[1] = anObjFloat(3.0f);
        stack[2] = chance(10) ? 0x80000000 * below(2) : anObjDepth();
        stack[3] = random32();
        stack[4] = chance(90) ? anObjFloat(1.0f) & 0x7fffffff : anObjFloat(1.0f);
    }
    else if (name == "lightPlaced")
    {
        cpu.eax = kObjModel;
        cpu.edx = chance(90) ? below(7) : below(0x100);
        cpu.ebx = kObjOut;
        cpu.ecx = kObjOut + 0x40;
        for (x86::reg32 i = 0; i < 3; ++i)
            stack[i] = anObjFloat(3.0f);
    }
    else if (name == "headlightGlare" || name == "taillightGlare" || name == "objectLights")
    {
        for (x86::reg32 i = 0; i < 3; ++i)
            g.word(kObjOut + 0x80 + 4 * i) = i == 2 ? anObjDepth() : anObjFloat(3.0f);
        g.word(kObjOut + 0x100) = random32();
        g.word(kObjOut + 0x104) = random32();
        if (name == "objectLights")
        {
            cpu.eax = kObjModel;
            cpu.edx = kObjOut + 0x40;
            cpu.ebx = kObjOut + 0x80;
            cpu.ecx = random32();
            cpu.esi = kObjOut + 0x100;
        }
        else
        {
            cpu.eax = kObjOut + 0x100;
            cpu.edx = kObjModel;
            cpu.ebx = kObjOut + 0x40;
            cpu.ecx = kObjOut + 0x80;
            stack[0] = chance(90) ? below(7) : below(0x100);
            stack[1] = chance(80) ? below(0x100) : random32();
        }
    }
    else if (name == "objectOpened" && (g.getMemory<x86::reg16>(kObjItem + 0x80) == 4
                                        || g.getMemory<x86::reg16>(kObjItem + 0x80) == 5
                                        || g.getMemory<x86::reg16>(kObjItem + 0x80) == 6))
    {
        // A car's object: the generic car's and the track's paths are made
        // through sprintf from a function of one push, whose logged words reach
        // the dead return address's slot above it -- written there, from the
        // shown object's loader's loop, by the game's own memset's push on the
        // generated side only (chooseFiles' and runLoader's cases hold those).
        g.getMemory<x86::reg16>(kObjItem + 0x80) = x86::reg16(chance(50) ? 1 : 9);
    }
    else if (name == "objectBounds")
        cpu.edx = chance(80) ? kObjItem + 0x1a : kObjOut;
    else if (name == "resetLoader" || name == "readPrehead" || name == "readHead" || name == "readModel"
             || name == "readTexture" || name == "readShapes")
        cpu.eax = chance(5) ? 0 : kObjLoader;
    else if (name == "genericVivPath" || name == "trackVivPath")
        cpu.eax = kObjPath;
    else if (name == "genericModelName" || name == "trackModelName")
        cpu.eax = chance(90) ? below(100) : random32();
    else if (name == "carColour")
        cpu.edx = kObjOut + 0x200;
    else if (name == "drawLogo")
    {
        cpu.eax = random32();
        cpu.edx = below(640);
        cpu.ebx = below(480);
        cpu.ecx = chance(90) ? 0x100 : below(0x200);
        stack[0] = chance(90) ? 0x100 : below(0x200);
        stack[1] = random32();
    }
    return true;
}
#endif
