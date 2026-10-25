// game_checks.cpp's parts for the race's data files: the track's file cache and paths, its textures, horizon, sky and weather, the opponents' speed tables, the cameras, the ghost
// (native_load_track.cpp), included in each table with the macro naming the part.
#if defined(LOAD_WINDOWS)
// {from, to}, -- what the functions write, compared
// The cameras' views (0x56f234 on; their files' slots at 0x570a34 are the
// sound's page already), the weather's counts and shapes (0x8ca1e8 on), the
// ghost's records' count (0x6bc6b4, read).
{0x56f000, 0x570000}, {0x8ca000, 0x8cb000}, {0x6bc000, 0x6bd000},
#elif defined(LOAD_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kLoadTrackNumber,     // 0x4be020: a horizon's number: small mostly, now and then up to 120, +-360 or negative; the text on
kLoadTrackBigCount,   // 0x4ea440: a BIGF's files: 0 to 5, none now and then
kLoadTrackBigName,    // 0x4ea4a0: a BIGF's file's name into [ebx], up to 23 long (zeros to 0x20), and ebx back
kLoadTrackFoundFile,  // load::findCachedFile's: a cache's node (named, sized, its data), or none
kLoadTrackPacked,     // load::packFileCache's: a buffer and its size to [edx], or 0 and 0
kLoadTrackCache,      // load::openFileCache's: a cache with its head, or none
kLoadTrackGhostRead,  // load::readGhost's: [0x55d000] 1 for a handle
#elif defined(LOAD_EFFECT_CASES)
// case kSomething: ... break;
case kLoadTrackNumber:
    // (&the text's place): the number, the text's place a few on.
    // 360 and -360 now and then: a whole turn of the clouds, exactly 1 or -1.
    result = r % 10 == 0   ? x86::reg32(-x86::sreg32((r >> 8) % 1000))
             : r % 16 == 1 ? (r & 0x100 ? 360 : x86::reg32(-360))
             : r % 3 == 0  ? (r >> 8) % 120
                           : (r >> 8) % 12;
    if (words[0] < kMemory - 4)
        word(words[0]) += 1 + (r >> 24) % 6;
    break;
case kLoadTrackBigCount:
    result = r % 8 == 0 ? 0 : (r >> 8) % 6;
    break;
case kLoadTrackBigName:
    // (the BIGF, the file, the name's buffer): the buffer's 0x20 bytes past
    // the name cleared -- what a frame below it held, the game's code for a
    // native (memset's) and the native leave otherwise, and 0x4ea290 logs.
    if (words[2] < kMemory - 0x20)
    {
        const x86::reg32 length = (r >> 8) % 0x18;
        text(words[2], length, random64(id));
        for (x86::reg32 at = words[2] + length; at < words[2] + 0x20; ++at)
            getMemory<x86::reg8>(at) = 0;
    }
    result = words[2];
    break;
case kLoadTrackFoundFile:
{
    const x86::reg32 node = 0x61f800 + 0x40 * ((r >> 8) % 8);
    result = r % 3 == 0 ? 0 : node;
    if (result != 0)
    {
        text(node, (r >> 4) % 0x1f, random64(id));
        word(node + 0x20) = (r >> 12) % 0x400;
        word(node + 0x24) = r % 7 == 0 ? 0 : 0x61e000 + 0x400 * ((r >> 16) % 4);
        word(node + 0x28) = 0;
        word(node + 0x2c) = 0;
    }
    break;
}
case kLoadTrackPacked:
    // (the cache, &the size)
    result = r % 4 == 0 ? 0 : 0x61e000;
    if (words[1] < kMemory - 4)
        word(words[1]) = result == 0 ? 0 : 0x10 + (r >> 8) % 0x400;
    break;
case kLoadTrackCache:
    result = r % 4 == 0 ? 0 : 0x61fc00;
    if (result != 0)
    {
        word(0x61fc00) = 0x42494746;
        word(0x61fc04) = 0x61fc40;
        word(0x61fc08) = 0x61fc40;
        for (x86::reg32 at = 0x61fc40; at < 0x61fc70; at += 4)
            word(at) = 0;
    }
    break;
case kLoadTrackGhostRead:
    if (words[0] != 0)
        word(0x55d000) = 1;
    break;
#elif defined(LOAD_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The horizon's numbers read one by one from its text, the text's place logged.
{0x4be020, "a horizon's number read", kWatcom, 1, 0, kEax, 0, 1, kLoadTrackNumber},
// EA's BIGF archive's: its files counted, a file's name (the cache's reading).
{0x4ea440, "a BIGF's files counted", kWatcom, 1, 0, kEax, -1, 0, kLoadTrackBigCount},
{0x4ea4a0, "a BIGF's file's name", kWatcom, 3, 0, kEax, -1, 0, kLoadTrackBigName},
// The sun's cosine, a float of degrees on the stack, left on the x87's.
{0x4ea950, "a cosine", kStdcall, 0, 1, 0, -1, 0, kFloatBack},
// The track's textures loaded from a .qfs: its path (its first bytes logged)
// and the loading's flags, which it hands on to its file's loading.
{0x4956f0, "a .qfs's shapes loaded", kWatcom, 2, 0, kEax | kEdx, 0, 4, kNothing},
// fwrite, as the ghost is written (watcom::fwrite, held against its code on its own).
{0x4eebd0, "fwrite", kWatcom, 4, 0, kEax | kEdx, -1, 0, kNothing},
// This file's functions other files call (load::findCachedFile, packFileCache,
// openFileCache, writeGhost, readGhost): held against their code on their own.
{0x418fe0, "a cached file found", kWatcom, 2, 0, kEax | kEdx, 1, 4, kLoadTrackFoundFile},
{0x419460, "a file cache packed", kWatcom, 2, 0, kEax | kEdx, -1, 0, kLoadTrackPacked},
{0x4195f0, "a file cache opened", kWatcom, 1, 0, kEax, 0, 1, kLoadTrackCache},
{0x477ac0, "the ghost written", kWatcom, 2, 0, kEax | kEdx, -1, 0, kNothing},
{0x477b00, "the ghost read", kWatcom, 1, 0, kEax, -1, 0, kLoadTrackGhostRead},
#elif defined(LOAD_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(LOAD_PROMISES)
// {"load::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared; the horizon's x87 stack too, in use.  But edx
// after a name is looked for (findFileNode, findCachedFile): the code leaves
// it as stricmp (0x4e9ec0) does, and the game's stricmp and native
// watcom::stricmp leave their argument registers differently.
{"load::loadOpponentSpeeds", true, true, 0},
{"load::clearTrackCameras", true, true, 0},
{"load::loadTrackCameras", true, true, 0},
{"load::swapBigEndian", true, true, 0},
{"load::newFileNode", true, true, 0},
{"load::freeFileNode", true, true, 0},
{"load::findFileNode", true, true, 2},
{"load::insertFileNode", true, true, 0},
{"load::newEmptyFileNode", true, true, 0},
{"load::freeFileNodes", true, true, 0},
{"load::countFileNodes", true, true, 0},
{"load::findCachedFile", true, true, 2},
{"load::addCachedFile", true, true, 0},
{"load::newFileCache", true, true, 0},
{"load::freeFileCache", true, true, 0},
{"load::bigHeaderSize", true, true, 0},
{"load::cachedDataSize", true, true, 0},
{"load::writeBigFile", true, true, 0},
{"load::packFileCache", true, true, 0},
{"load::readBigFile", true, true, 0},
{"load::openFileCache", true, true, 0},
{"load::trackFilePath", true, true, 0},
{"load::trackFolderPath", true, true, 0},
{"load::loadTrackTextures", true, true, 0},
{"load::saveGhost", true, true, 0},
{"load::writeGhost", true, true, 0},
{"load::readGhost", true, true, 0},
{"load::loadHorizon", true, true, 0, true, kNoHeap, true},
{"load::loadSky", true, true, 0},
{"load::loadWeatherShapes", true, true, 0},
#elif defined(LOAD_ARGUMENTS)
/* Where the track's cases keep their own: names and paths, the cache's
 * record, its nodes (0x40 apart), its files' data (0x80 each), a BIGF
 * archive or the buffer one is written to (up to 0x1800), and what this
 * file's stand-ins hand back (0x61f800 on). */
constexpr x86::reg32 kLoadTrackNames = 0x61d000, kLoadTrackCacheRecord = 0x61d200, kLoadTrackNodes = 0x61d400;
constexpr x86::reg32 kLoadTrackData = 0x61d800, kLoadTrackBig = 0x61e000, kLoadTrackOut = 0x61d300;

/* A name into `at`: letters and digits mostly, 0 to `most` long. */
x86::reg32 aLoadTrackName(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._";
    const x86::reg32 length = chance(5) ? 0 : 1 + below(most);
    for (x86::reg32 i = 0; i < length; ++i)
        g.getMemory<x86::reg8>(at + i) = chance(97) ? x86::reg8(letters[below(sizeof letters - 1)])
                                                    : x86::reg8(0x20 + below(0x60));
    g.getMemory<x86::reg8>(at + length) = 0;
    return at;
}

/* The file cache's world: a cache ('FGIB' mostly) with its head and 0 to 7
 * files after it, linked both ways, each named (now and then as another,
 * its case changed), sized (now and then 0) and with its data (now and then
 * none); the last node its last. */
x86::reg32 makeLoadTrackCache(CheckApp& g, x86::reg32& files)
{
    files = chance(10) ? 0 : 1 + below(7);
    const x86::reg32 cache = kLoadTrackCacheRecord;
    g.word(cache) = chance(90) ? 0x42494746 : chance(50) ? 0x46474942 : random32();
    g.word(cache + 4) = chance(5) ? 0 : kLoadTrackNodes;
    for (x86::reg32 i = 0; i <= files; ++i)
    {
        const x86::reg32 node = kLoadTrackNodes + 0x40 * i;
        if (i == 0)
            g.getMemory<x86::reg8>(node) = 0;
        else if (i > 1 && chance(15))
        {
            // Another's name, its case changed here and there.
            const x86::reg32 from = kLoadTrackNodes + 0x40 * (1 + below(i - 1));
            x86::reg32 at = 0;
            for (; at < 0x1f && g.getMemory<x86::reg8>(from + at) != 0; ++at)
            {
                const x86::reg8 c = g.getMemory<x86::reg8>(from + at);
                g.getMemory<x86::reg8>(node + at) = chance(30) && ((c | 0x20) >= 'a' && (c | 0x20) <= 'z') ? x86::reg8(c ^ 0x20) : c;
            }
            g.getMemory<x86::reg8>(node + at) = 0;
        }
        else
            aLoadTrackName(g, node, 0x1e);
        g.word(node + 0x20) = i == 0 ? 0 : chance(4) ? 0 : 1 + below(0x80);
        g.word(node + 0x24) = i == 0 ? 0 : chance(4) ? 0 : kLoadTrackData + 0x80 * (i - 1);
        g.word(node + 0x28) = i < files ? node + 0x40 : 0;
        g.word(node + 0x2c) = i == 0 ? 0 : node - 0x40;
    }
    g.word(cache + 8) = chance(5) ? 0 : kLoadTrackNodes + 0x40 * files;
    for (x86::reg32 at = kLoadTrackData; at < kLoadTrackData + 0x800; at += 4)
        g.word(at) = random32();
    return cache;
}

/* A name to look for: one of the cache's (its case changed now and then),
 * or another. */
x86::reg32 aLoadTrackLookup(CheckApp& g, x86::reg32 files)
{
    const x86::reg32 at = kLoadTrackNames + 0x100;
    if (files != 0 && chance(70))
    {
        const x86::reg32 from = kLoadTrackNodes + 0x40 * (1 + below(files));
        x86::reg32 i = 0;
        for (; i < 0x1f && g.getMemory<x86::reg8>(from + i) != 0; ++i)
        {
            const x86::reg8 c = g.getMemory<x86::reg8>(from + i);
            g.getMemory<x86::reg8>(at + i) = chance(20) && ((c | 0x20) >= 'a' && (c | 0x20) <= 'z') ? x86::reg8(c ^ 0x20) : c;
        }
        g.getMemory<x86::reg8>(at + i) = 0;
        return at;
    }
    return aLoadTrackName(g, at, 0x1e);
}

/* The race's world: the track, its folder, backwards or not, night and
 * weather, the options, the loading stopped now and then; the speeds', the
 * cameras', the textures', the sky's and the weather's globals; the ghost's;
 * the blocks the allocation's stand-in hands out. */
void makeLoadTrackWorld(CheckApp& g)
{
    g.text(0x7a27b4, chance(20) ? 0 : below(0x20), random32());
    g.text(0x7a2934, chance(20) ? 0 : below(0x20), random32());
    g.word(0x6fd4ac) = chance(90) ? below(30) : random32();
    g.word(0x6fd4c0) = chance(60) ? 0 : chance(90) ? 1 : random32();
    g.word(0x6fd4c4) = chance(50) ? 0 : 1;
    g.word(0x6fd4c8) = chance(50) ? 0 : 1;
    g.word(0x6fd4cc) = chance(50) ? 0 : 1;
    g.getMemory<x86::reg8>(0x7a3a58) = x86::reg8(random32());
    g.word(0x55e88c) = chance(80) ? 0 : 1;
    g.word(0x5dd940) = chance(85) ? below(3000) : random32();
    for (const x86::reg32 at : {0x552558u, 0x55255cu, 0x56f22cu, 0x5dd850u, 0x563a90u, 0x55d000u})
        g.word(at) = random32();
    g.word(0x6fd3a0) = chance(60) ? 0 : below(3);
    g.word(0x6fd3ac) = chance(40) ? 0 : 1;
    g.word(0x6bc6b4) = chance(90) ? below(0x400) : random32();
    g.getMemory<x86::reg8>(0x8ca1e8) = x86::reg8(chance(30) ? 0 : random32());
    // The game's allocation's blocks (kBlocks): anything, as memory taken is.
    for (x86::reg32 at = kBlocks; at < kBlocks + 0x2000; at += 4)
        g.word(at) = random32();
    for (x86::reg32 at = 0x8ca1ec; at < 0x8ca200; at += 4)
        g.word(at) = chance(70) ? below(0x1000) : random32();
}

/* What a stand-in will make of the case's call at index `k` (game_checks.cpp's
 * random: the case's seed, the calls made, the address): the game's
 * allocation's block (kBlock) and a BIGF entry's (kRaceloadVivEntry). */
x86::reg32 loadTrackRandom(x86::reg32 k, x86::reg32 address)
{
    return x86::reg32(mix(g_seed ^ (std::uint64_t(k + 1) << 32) ^ address));
}

x86::reg32 loadTrackBlock(x86::reg32 k)
{
    const x86::reg32 r = loadTrackRandom(k, 0x4e1620);
    return r % 6 == 0 ? 0 : kBlocks + 0x400 * ((r >> 8) % 8);
}

/* The cache's reading (load::readBigFile, and load::openFileCache's with
 * the cache and its head it makes first): the 8 blocks the allocation's
 * stand-in hands out at random may give a file's data the block of a node or
 * of the cache made before it, or a node the cache's block, whose links the
 * copy or the node's name then make wild -- as no game's allocation would.
 * The case stopped at that call (g_mostCalls), as the calls go: the files counted, each one's name and entry, its data's
 * block and its node's; and at 200 calls, for a list a node's block given
 * twice made a loop of. */
void limitLoadTrackReading(CheckApp& g, x86::reg32 cache, x86::reg32 data, bool opened)
{
    g_mostCalls = 200;
    if (data == 0 || g.word(data) != 0x46474942 || (!opened && cache == 0))
        return;
    std::vector<x86::reg32> made;  // the blocks given a node or the cache
    x86::reg32 k = 0;
    const bool usable = opened || (g.word(cache + 4) != 0 && g.word(cache + 8) != 0);
    x86::reg32 cacheBlock = 0;
    if (opened)
    {
        cacheBlock = loadTrackBlock(0);
        if (cacheBlock == 0 || loadTrackBlock(1) == 0)
            return;
        made = {cacheBlock, loadTrackBlock(1)};
        k = 2;
    }
    const x86::reg32 r = loadTrackRandom(k++, 0x4ea440);
    const x86::reg32 count = r % 8 == 0 ? 0 : (r >> 8) % 6;
    for (x86::reg32 i = 0; i < count; ++i)
    {
        const x86::reg32 entry = loadTrackRandom(k + 1, 0x4ea290);
        k += 2;
        if (entry == 0)
            return;
        if ((entry % 7 == 0 ? 0 : (entry >> 8) % 0x400) == 0)
            continue;
        if (!usable)
            return;
        const x86::reg32 block = loadTrackBlock(k);
        if (std::find(made.begin(), made.end(), block) != made.end())
        {
            g_mostCalls = long(k);
            return;
        }
        if (block == 0)
            return;
        const x86::reg32 node = loadTrackBlock(++k);
        if (opened && node == cacheBlock)
        {
            // The node's name written over the cache's list.
            g_mostCalls = long(k);
            return;
        }
        ++k;
        if (node == 0)
            return;
        made.push_back(node);
    }
}

bool makeLoadTrackArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "loadOpponentSpeeds", "clearTrackCameras", "loadTrackCameras", "swapBigEndian", "newFileNode",
        "freeFileNode", "findFileNode", "insertFileNode", "newEmptyFileNode", "freeFileNodes", "countFileNodes",
        "findCachedFile", "addCachedFile", "newFileCache", "freeFileCache", "bigHeaderSize", "cachedDataSize",
        "writeBigFile", "packFileCache", "readBigFile", "openFileCache", "trackFilePath", "trackFolderPath",
        "loadTrackTextures", "saveGhost", "writeGhost", "readGhost", "loadHorizon", "loadSky", "loadWeatherShapes"};
    if (std::find(std::begin(names), std::end(names), name) == std::end(names))
        return false;
    (void)stack;
    makeLoadTrackWorld(g);
    x86::reg32 files = 0;
    const x86::reg32 cache = makeLoadTrackCache(g, files);
    const auto aNode = [&] { return kLoadTrackNodes + 0x40 * below(files + 1); };
    // A BIGF archive's start: 'BIGF' mostly, its other words anything.
    for (x86::reg32 at = kLoadTrackBig; at < kLoadTrackBig + 0x1800; at += 4)
        g.word(at) = random32();
    g.word(kLoadTrackBig) = chance(85) ? 0x46474942 : random32();
    if (name == "loadTrackCameras")
        cpu.eax = aLoadTrackName(g, kLoadTrackNames, 0x30);
    else if (name == "swapBigEndian")
        cpu.eax = kLoadTrackNames + below(0x2ff0);
    else if (name == "freeFileNode")
        cpu.eax = chance(10) ? 0 : kLoadTrackNodes + 0x40 * (1 + below(files + 1));
    else if (name == "findFileNode")
    {
        cpu.eax = aLoadTrackLookup(g, files);
        cpu.edx = chance(80) ? kLoadTrackNodes : aNode();
    }
    else if (name == "insertFileNode")
    {
        cpu.eax = aLoadTrackName(g, kLoadTrackNames, 0x1e);
        cpu.edx = below(0x400);
        cpu.ebx = chance(10) ? 0 : kLoadTrackData + below(0x800);
        cpu.ecx = aNode();
    }
    else if (name == "freeFileNodes")
        cpu.eax = chance(10) ? 0 : aNode();
    else if (name == "countFileNodes" || name == "freeFileCache" || name == "bigHeaderSize")
        cpu.eax = chance(5) && name != "countFileNodes" ? 0 : cache;
    else if (name == "cachedDataSize")
    {
        g.word(cache + 4) = kLoadTrackNodes;
        cpu.eax = cache;
    }
    else if (name == "findCachedFile")
    {
        cpu.eax = chance(5) ? 0 : cache;
        cpu.edx = aLoadTrackLookup(g, files);
    }
    else if (name == "addCachedFile")
    {
        cpu.eax = chance(5) ? 0 : cache;
        cpu.edx = aLoadTrackName(g, kLoadTrackNames, 0x1e);
        cpu.ebx = chance(5) ? 0 : below(0x400);
        cpu.ecx = kLoadTrackBig + below(0x1000);
    }
    else if (name == "writeBigFile")
    {
        cpu.eax = chance(5) ? 0 : kLoadTrackBig;
        cpu.edx = chance(5) ? 0 : cache;
        cpu.ebx = chance(10) ? below(0x100) : chance(5) ? 0 : 0x400 + below(0x1400);
    }
    else if (name == "packFileCache")
    {
        cpu.eax = chance(5) ? 0 : cache;
        cpu.edx = kLoadTrackOut;
    }
    else if (name == "readBigFile")
    {
        cpu.eax = chance(5) ? 0 : cache;
        cpu.edx = chance(5) ? 0 : kLoadTrackBig;
        limitLoadTrackReading(g, cpu.eax, cpu.edx, false);
    }
    else if (name == "openFileCache")
    {
        cpu.eax = chance(5) ? 0 : kLoadTrackBig;
        limitLoadTrackReading(g, 0, cpu.eax, true);
    }
    else if (name == "trackFilePath" || name == "trackFolderPath")
        cpu.eax = aLoadTrackName(g, kLoadTrackNames, 0x20);
    else if (name == "writeGhost")
        cpu.eax = chance(10) ? 0 : 0x638000 + 0x40 * below(8);
    else if (name == "readGhost")
        cpu.eax = chance(10) ? 0 : 0x7700 + below(0x100);
    else if (name == "loadHorizon" || name == "loadSky")
    {
        cpu.eax = chance(90) ? below(30) : random32();
        // The x87's word as the game sets it: the race's single precision
        // mostly, the menus'.
        cpu.fpu.setControl(x86::reg16(chance(60) ? 0x007f : chance(50) ? 0x027f : 0x037f));
    }
    return true;
}
#endif
