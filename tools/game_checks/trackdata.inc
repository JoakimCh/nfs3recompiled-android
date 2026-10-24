// game_checks.cpp's parts for the track's data and a place on it (native_trackdata.cpp), included in each
// table with the macro naming the part.
#if defined(TRACKDATA_WINDOWS)
// {from, to}, -- what the functions write, compared
// The cases' own (the track's nodes and blocks' tables, the places on it,
// the .ccm, the cars, buffers), the track's blocks, the nodes' globals.  The
// .ccm's and simhts.dat's globals (0x552e48 on) and the track's number
// (0x6fd4ac) are on pages compared already.
{0xd00000, 0xd10000}, {0x571000, 0x575000}, {0x5dd000, 0x5de000},
#elif defined(TRACKDATA_EFFECTS)
kTdCcm,      // the .ccm loaded (loadFileQuietly) in a track's case: its file, or none; else as kNothing
kTdCarNode,  // a car's node (0x4217e0) in a track's case: one of the track's; else as kNothing
#elif defined(TRACKDATA_EFFECT_CASES)
case kTdCcm:
case kTdCarNode:
{
    // Only in the track's cases (the case's mark at 0xd0fffc): elsewhere as
    // the row it stands before (kNothing) leaves eax.
    const x86::reg32 more = random(id ^ 0xabcd);
    if (word(0xd0fffc) != x86::reg32(g_seed))
        result = more % 4 != 0 ? r : cpu.eax;
    else if (s.effect == kTdCcm)
        result = r % 6 == 0 ? 0 : 0xd0a000;
    else
        result = (r >> 4) % 9 == 0 ? 0 : (r >> 8) % std::max<x86::reg32>(word(0x5dd940), 1);
    break;
}
#elif defined(TRACKDATA_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// Before the EA rows: loadFileQuietly, which gives the track's cases their
// .ccm (as ea_support.inc's row elsewhere), and a car's node, which the
// render's natives call too (not held here).
{0x4e0fe0, "loadFileQuietly", kWatcom, 2, 0, kEax, -1, 0, kTdCcm},
{0x4217e0, "a car's node", kWatcom, 1, 0, kEax, -1, 0, kTdCarNode},
// This file's own that the sound's natives call by address: as the
// generated code's stand-ins (decompiled_standins.inc) had them before.  Each
// tested on its own.
{0x420bf0, "inTunnel", kStdcall, 0, 4, kEax, -1, 0, kNothing},
{0x4211c0, "carSectionKind", kWatcom, 1, 0, kEax, -1, 0, kNothing},
#elif defined(TRACKDATA_POINTERS)
#elif defined(TRACKDATA_PROMISES)
// {"trackdata::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared, and the x87's stack in use.
{"trackdata::loadCcmPoints", true, true, 0, true, kNoHeap, true},
{"trackdata::freeCcmPoints", true, true, 0, true, kNoHeap, true},
{"trackdata::loadSimHeights", true, true, 0, true, kNoHeap, true},
{"trackdata::freeSimHeights", true, true, 0, true, kNoHeap, true},
{"trackdata::openTrackNodes", true, true, 0, true, kNoHeap, true},
{"trackdata::closeTrackNodes", true, true, 0, true, kNoHeap, true},
{"trackdata::nearestNodeCoarse", true, true, 0, true, kNoHeap, true},
{"trackdata::followNode", true, true, 0, true, kNoHeap, true},
{"trackdata::nearestNode", true, true, 0, true, kNoHeap, true},
{"trackdata::quadVertices", true, true, 0, true, kNoHeap, true},
{"trackdata::quadStepForward", true, true, 0, true, kNoHeap, true},
{"trackdata::quadStepBack", true, true, 0, true, kNoHeap, true},
{"trackdata::quadToFixed", true, true, 0, true, kNoHeap, true},
{"trackdata::quadSet", true, true, 0, true, kNoHeap, true},
{"trackdata::nodeSection", true, true, 0, true, kNoHeap, true},
{"trackdata::resetPosition", true, true, 0, true, kNoHeap, true},
{"trackdata::findQuad", true, true, 0, true, kNoHeap, true},
{"trackdata::findQuadNearby", true, true, 0, true, kNoHeap, true},
{"trackdata::findQuadByLinks", true, true, 0, true, kNoHeap, true},
{"trackdata::findQuadFallback", true, true, 0, true, kNoHeap, true},
{"trackdata::locateOnRoad", true, true, 0, true, kNoHeap, true},
{"trackdata::updatePosition", true, true, 0, true, kNoHeap, true},
{"trackdata::findMatchingQuad", true, true, 0, true, kNoHeap, true},
{"trackdata::quadEdgeFlags", true, true, 0, true, kNoHeap, true},
{"trackdata::sectionItemCount", true, true, 0, true, kNoHeap, true},
{"trackdata::sectionItem", true, true, 0, true, kNoHeap, true},
{"trackdata::setLaneOffsets", true, true, 0, true, kNoHeap, true},
{"trackdata::lanePosition", true, true, 0, true, kNoHeap, true},
{"trackdata::positionFrame", true, true, 0, true, kNoHeap, true},
{"trackdata::snapToTrack", true, true, 0, true, kNoHeap, true},
{"trackdata::placeOnTrack", true, true, 0, true, kNoHeap, true},
{"trackdata::positionColour", true, true, 0, true, kNoHeap, true},
{"trackdata::positionSurface", true, true, 0, true, kNoHeap, true},
{"trackdata::surfaceUnder", true, true, 0, true, kNoHeap, true},
{"trackdata::inTunnel", true, true, 0, true, kNoHeap, true},
{"trackdata::carFacingWay", true, true, 0, true, kNoHeap, true},
{"trackdata::carSectionKind", true, true, 0, true, kNoHeap, true},
#elif defined(TRACKDATA_ARGUMENTS)
/* Where the track's cases keep their own: the header and its nodes, the
 * strips (after room for those before the first), the vertices, the nodes'
 * entries, the polygons, the normals, the colours, the items; places on the
 * track, places, the .ccm's file, a car, buffers written; the case's mark. */
constexpr x86::reg32 kTdHeader = 0xd00000, kTdNodes = kTdHeader + 8;  // 64 nodes at most
constexpr x86::reg32 kTdStrips = 0xd01000 + 14 * 8;
constexpr x86::reg32 kTdVertices = 0xd03000, kTdEntries = 0xd05000, kTdPolygons = 0xd05400 + 8 * 8;
constexpr x86::reg32 kTdNormals = 0xd06800, kTdColours = 0xd06c00, kTdItems = 0xd07800;
constexpr x86::reg32 kTdPlaces = 0xd08000;  // 8 of 0x80
constexpr x86::reg32 kTdPoints = 0xd08800;  // 16 of 0x10
constexpr x86::reg32 kTdCcmFile = 0xd0a000, kTdCar = 0xd0b000, kTdOut = 0xd0d000;
constexpr x86::reg32 kTdMark = 0xd0fffc;
constexpr x86::reg32 kTdLanes = 6;  // strips a node at most

x86::reg32 g_tdCount = 0;  // the case's nodes

void putFloat(CheckApp& g, x86::reg32 at, float f)
{
    std::memcpy(&g.getMemory<x86::reg8>(at), &f, 4);
}

/* A vertex of the grid: node i's j-th edge across the road, x going down
 * with j so that a place between lands inside its quad -- a little off now
 * and then. */
void putVertex(CheckApp& g, x86::reg32 at, x86::reg32 i, x86::reg32 j)
{
    const float jitter = chance(10) ? float(x86::sreg32(below(200)) - 100) / 100.0f : 0.0f;
    putFloat(g, at, 12.0f - 4.0f * float(j) + jitter);
    putFloat(g, at + 4, float(x86::sreg32(below(400)) - 200) / 50.0f);
    putFloat(g, at + 8, 16.0f * float(i) + (chance(10) ? jitter : 0.0f));
}

/* A place nearby the road: within a node's quads mostly, past the road's
 * sides or ends now and then, or anywhere; 16.16, at `at`. */
x86::reg32 aTdPoint(CheckApp& g, x86::reg32 at)
{
    const x86::reg32 node = below(g_tdCount);
    x86::sreg32 x = x86::sreg32(0xc0000) - x86::sreg32(below(0x180000));
    x86::sreg32 z = x86::sreg32(node * 0x100000 + below(0x100000));
    if (chance(15))
        x += x86::sreg32(below(0x400000)) - 0x200000;
    if (chance(10))
        z += x86::sreg32(below(0x2000000)) - 0x1000000;
    g.word(at) = chance(3) ? random32() : x86::reg32(x);
    g.word(at + 4) = x86::reg32(x86::sreg32(below(0x80000)) - 0x40000);
    g.word(at + 8) = chance(3) ? random32() : x86::reg32(z);
    return at;
}

/* A place on the track (0x78 bytes): at a node, its block and entry, a strip
 * across the road and its polygon, normal and quad -- or none -- as found or
 * not, at either end now and then. */
x86::reg32 aTdPlace(CheckApp& g, x86::reg32 at)
{
    const x86::reg32 node = below(g_tdCount);
    const x86::reg32 block = 0x571370 + 0x5c0 * (node >> 3);
    const x86::reg32 count = g.getMemory<x86::reg8>(kTdEntries + 8 * node + 2);
    const x86::reg32 lane = chance(80) && count != 0 ? below(count) : below(kTdLanes);
    const x86::reg32 strip = node * kTdLanes + lane;
    for (x86::reg32 i = 0; i < 0x78; i += 4)
        g.word(at + i) = random32() & (chance(50) ? 0x1fffff : 0xffffffff);
    g.word(at) = block;
    aTdPoint(g, at + 4);
    g.word(at + 0x10) = node;
    const bool on = chance(75);
    g.word(at + 0x14) = on || chance(30) ? kTdStrips + 14 * strip : 0;
    g.word(at + 0x18) = on || chance(30) ? kTdPolygons + 8 * strip : 0;
    g.word(at + 0x1c) = kTdNormals + 12 * below(16);
    g.word(at + 0x20) = kTdEntries + 8 * node;
    const x86::reg32 corners[4] = {(node * (kTdLanes + 1) + lane + 1), (node * (kTdLanes + 1) + lane),
                                   ((node + 1) * (kTdLanes + 1) + lane), ((node + 1) * (kTdLanes + 1) + lane + 1)};
    for (x86::reg32 k = 0; k < 4; ++k)
        g.word(at + 0x54 + 4 * k) = chance(97) ? kTdVertices + 12 * corners[k] : 0;
    // The quad in 16.16, of its corners mostly.
    if (chance(80))
        for (x86::reg32 k = 0; k < 12; ++k)
        {
            float f;
            std::memcpy(&f, &g.getMemory<x86::reg8>(g.word(at + 0x54 + 4 * (k / 3)) + 4 * (k % 3)), 4);
            g.word(at + 0x24 + 4 * k) = x86::reg32(x86::sreg32(f * 65536.0f));
        }
    g.word(at + 0x64) = chance(60) ? 2 : chance(70) ? 1 : random32();
    g.getMemory<x86::reg16>(at + 0x68) = x86::reg16(below(2));
    g.getMemory<x86::reg16>(at + 0x6a) = x86::reg16(below(2));
    g.word(at + 0x6c) = chance(70) ? 0 : below(3);
    g.word(at + 0x70) = chance(85) ? lane : chance(50) ? 0xffffffff : below(kTdLanes + 2);
    g.word(at + 0x74) = below(2);
    return at;
}

/* The track's world: its nodes (16 apart along z, their bytes any), blocks
 * of 8, the nodes' entries (strips across, links), a grid of vertices and
 * the strips between them, polygons (off the road now and then), normals,
 * colours and items; the globals; the .ccm's file; places on it, places. */
void makeTrackWorld(CheckApp& g)
{
    g_tdCount = chance(70) ? 8 * (1 + below(6)) : 2 + below(62);
    const x86::reg32 count = g_tdCount;
    g.word(kTdMark) = x86::reg32(g_seed);
    for (x86::reg32 at = kTdHeader; at < kTdMark; at += 4)
        g.word(at) = random32();
    g.word(kTdHeader) = random32();
    g.getMemory<x86::reg16>(kTdHeader + 6) = x86::reg16(count);
    for (x86::reg32 i = 0; i < count; ++i)
    {
        const x86::reg32 node = kTdNodes + 0x24 * i;
        g.word(node) = x86::reg32(x86::sreg32(below(0x40000)) - 0x20000);
        g.word(node + 4) = x86::reg32(x86::sreg32(below(0x80000)) - 0x40000);
        g.word(node + 8) = i * 0x100000 + below(0x10000);
        for (x86::reg32 k = 0xc; k < 0x24; ++k)
            g.getMemory<x86::reg8>(node + k) = x86::reg8(random32());
        // The tunnels' nibbles: 2 often, 0 often.
        const x86::reg8 nibbles[] = {0, 2, 0x20, 0x22, 0x12, 0x21, 0x11, 0};
        if (chance(80))
            g.getMemory<x86::reg8>(node + 0xe) = nibbles[below(8)];
        // The entry: the first strip, how many across, a kind, its links.
        const x86::reg32 entry = kTdEntries + 8 * i;
        g.getMemory<x86::reg16>(entry) = x86::reg16(i * kTdLanes);
        g.getMemory<x86::reg8>(entry + 2) = x86::reg8(chance(90) ? 1 + below(kTdLanes) : 0);
        g.getMemory<x86::reg8>(entry + 3) = x86::reg8(random32());
        g.getMemory<x86::reg16>(entry + 4) = x86::reg16(chance(30) ? 0xffff : below(count));
        g.getMemory<x86::reg16>(entry + 6) = x86::reg16(chance(30) ? 0xffff : below(count));
    }
    // The vertices: a row for each node and one past the last.
    for (x86::reg32 i = 0; i <= count; ++i)
        for (x86::reg32 j = 0; j <= kTdLanes; ++j)
            putVertex(g, kTdVertices + 12 * (i * (kTdLanes + 1) + j), i, j);
    // The strips (and the 8 before the first, as a lane -1 reads), the polygons.
    for (x86::sreg32 k = -8; k < x86::sreg32(count * kTdLanes); ++k)
    {
        const x86::reg32 i = k < 0 ? 0 : x86::reg32(k) / kTdLanes, j = k < 0 ? 0 : x86::reg32(k) % kTdLanes;
        const x86::reg32 strip = kTdStrips + 14 * x86::reg32(k);
        const x86::reg32 w[4] = {i * (kTdLanes + 1) + j, i * (kTdLanes + 1) + j + 1,
                                 (i + 1) * (kTdLanes + 1) + j + 1, (i + 1) * (kTdLanes + 1) + j};
        const bool flip = chance(10);
        for (x86::reg32 n = 0; n < 4; ++n)
            g.getMemory<x86::reg16>(strip + 2 * n) = x86::reg16(w[flip ? 3 - n : n]);
        g.getMemory<x86::reg16>(strip + 8) = x86::reg16(random32());
        g.word(strip + 10) = random32();
        const x86::reg32 polygon = kTdPolygons + 8 * x86::reg32(k);
        g.getMemory<x86::reg8>(polygon) = x86::reg8(below(16));
        g.getMemory<x86::reg8>(polygon + 1) = x86::reg8((random32() & 0xf0) | (chance(15) ? 0xe : below(16)));
    }
    for (x86::reg32 at = kTdNormals; at < kTdNormals + 12 * 16; at += 2)
        g.getMemory<x86::reg16>(at) = x86::reg16(chance(10) ? 0 : x86::sreg32(below(0x10000)) - 0x8000);
    // The blocks.
    for (x86::reg32 b = 0; b < 8; ++b)
    {
        const x86::reg32 block = 0x571370 + 0x5c0 * b;
        for (x86::reg32 k = 0; k < 0x5c0; k += 4)
            g.word(block + k) = random32();
        g.word(block + 0x3c) = kTdStrips;
        g.word(block + 0x70) = kTdVertices;
        g.word(block + 0x74) = kTdColours;
        g.word(block + 0x584) = 8 * b;
        g.word(block + 0x58c) = kTdEntries + 8 * 8 * b;
        g.word(block + 0x594) = kTdPolygons;
        g.word(block + 0x59c) = kTdNormals;
        g.word(block + 0x5a0) = chance(20) ? 0 : 1 + below(8);
        g.word(block + 0x5a4) = kTdItems;
    }
    // The globals.
    g.word(0x5dd938) = kTdHeader;
    g.word(0x5dd93c) = kTdNodes;
    g.word(0x5dd940) = count;
    g.word(0x5dd948) = kTdNodes;
    g.word(0x5dd930) = chance(80) ? 1 + below(16) : chance(50) ? x86::reg32(-1 - x86::sreg32(below(16))) : 1 + below(0x1000);
    g.word(0x5dd934) = x86::reg32(x86::sreg32(below(0x20000)) - 0x10000);
    g.word(0x6fd4ac) = chance(90) ? below(9) : chance(50) ? 9 + below(4) : random32();
    g.word(0x6fd4c0) = chance(50) ? 0 : chance(80) ? 1 : random32();
    g.word(0x552e48) = chance(30) ? 0 : chance(50) ? kTdCcmFile : 0x1f0000 + 0x400 * below(8);
    g.word(0x552e4c) = below(12);
    g.word(0x552e50) = kTdCcmFile + 8;
    g.word(0x552e54) = chance(30) ? 0 : 0x1f0000 + 0x400 * below(8);
    // The .ccm: a few points nearby the road.
    g.word(kTdCcmFile + 4) = chance(10) ? 0 : 1 + below(12);
    for (x86::reg32 i = 0; i < 12; ++i)
    {
        aTdPoint(g, kTdCcmFile + 8 + 0x1c * i);
        g.word(kTdCcmFile + 8 + 0x1c * i + 0x18) = random32();
    }
    for (x86::reg32 i = 0; i < 8; ++i)
        aTdPlace(g, kTdPlaces + 0x80 * i);
    for (x86::reg32 i = 0; i < 16; ++i)
        aTdPoint(g, kTdPoints + 0x10 * i);
    // A car: its index, its place and heading (floats), its speeds, which
    // way the track goes, its node.
    for (x86::reg32 at = kTdCar; at < kTdCar + 0xa00; at += 4)
        g.word(at) = random32();
    g.word(kTdCar + 4) = below(8);
    const x86::reg32 nearby = kTdNodes + 0x24 * below(count);
    putFloat(g, kTdCar + 8, float(x86::sreg32(g.word(nearby))) / 65536.0f + float(below(100)) / 10.0f - 5.0f);
    putFloat(g, kTdCar + 0xc, float(x86::sreg32(below(400)) - 200) / 50.0f);
    putFloat(g, kTdCar + 0x10, float(x86::sreg32(g.word(nearby + 8))) / 65536.0f + float(below(400)) / 10.0f - 20.0f);
    for (const x86::reg32 at : {0x2cu, 0x30u, 0x34u, 0xa4u, 0xacu})
        putFloat(g, kTdCar + at, float(x86::sreg32(below(2000)) - 1000) / 100.0f);
    if (chance(5))
        putFloat(g, kTdCar + 0xa4, 0.0f);
    g.word(kTdCar + 0x998) = chance(50) ? 0 : 1;
    g.word(kTdCar + 0x1c) = below(count);
}

bool makeTrackdataArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    makeTrackWorld(g);
    const auto place = [&] { return kTdPlaces + 0x80 * below(8); };
    const auto point = [&] { return kTdPoints + 0x10 * below(16); };
    const auto flag = [] { return chance(50) ? 0 : chance(80) ? 1 : random32(); };
    if (name == "openTrackNodes")
        cpu.eax = kTdHeader;
    else if (name == "nearestNodeCoarse" || name == "followNode" || name == "nearestNode" || name == "findQuad"
             || name == "findQuadNearby" || name == "findQuadFallback" || name == "locateOnRoad")
    {
        cpu.eax = point();
        cpu.edx = place();
    }
    else if (name == "findQuadByLinks")
    {
        cpu.eax = point();
        cpu.edx = place();
        cpu.ebx = below(g_tdCount);
    }
    else if (name == "updatePosition")
    {
        cpu.eax = point();
        cpu.edx = place();
        cpu.ebx = flag();
    }
    else if (name == "quadVertices" || name == "quadStepForward" || name == "quadStepBack" || name == "quadToFixed"
             || name == "quadSet" || name == "nodeSection" || name == "sectionItemCount")
        cpu.eax = place();
    else if (name == "resetPosition")
    {
        cpu.eax = below(g_tdCount);
        cpu.edx = place();
    }
    else if (name == "findMatchingQuad")
    {
        static const x86::reg32 modes[] = {4, 8, 2, 1, 4, 8, 0, 3};
        cpu.eax = chance(95) ? modes[below(8)] : random32();
        cpu.edx = kTdPlaces + 0x80 * below(4);
        cpu.ebx = kTdPlaces + 0x80 * (4 + below(4));
    }
    else if (name == "quadEdgeFlags")
    {
        cpu.eax = point();
        cpu.edx = place();
        cpu.ebx = chance(20) ? cpu.edx : place();
        cpu.ecx = kTdOut + 4 * below(16);
    }
    else if (name == "sectionItem")
    {
        cpu.eax = place();
        cpu.edx = chance(85) ? below(9) : x86::reg32(-1 - x86::sreg32(below(3)));
        cpu.ebx = kTdOut + 4 * below(16);
        cpu.ecx = kTdOut + 0x100 + 2 * below(16);
    }
    else if (name == "setLaneOffsets")
    {
        cpu.eax = random32();
        cpu.edx = random32();
    }
    else if (name == "lanePosition")
    {
        cpu.eax = place();
        cpu.edx = kTdOut + 4 * below(16);
        cpu.ebx = flag();
    }
    else if (name == "positionFrame")
    {
        cpu.eax = place();
        cpu.edx = kTdOut + 4 * below(16);
        cpu.esi = kTdOut + 0x100 + 4 * below(16);
    }
    else if (name == "snapToTrack")
    {
        // Three floats nearby the road; the node to look nearby and the follow flag.
        cpu.eax = kTdOut + 0x200;
        aTdPoint(g, cpu.eax);
        for (x86::reg32 k = 0; k < 12; k += 4)
            putFloat(g, cpu.eax + k, float(x86::sreg32(g.word(cpu.eax + k))) / 65536.0f);
        cpu.esi = kTdOut + 0x400;
        cpu.ebx = below(g_tdCount);
        cpu.edx = flag();
    }
    else if (name == "placeOnTrack")
    {
        cpu.eax = point();
        cpu.edx = flag();
        cpu.ebx = below(g_tdCount);
        cpu.esi = kTdOut + 0x400;
    }
    else if (name == "positionColour" || name == "positionSurface")
    {
        cpu.eax = place();
        cpu.edx = flag();
    }
    else if (name == "surfaceUnder")
    {
        cpu.eax = chance(80) ? 0xc0 + below(0x5a0) : random32();
        cpu.edx = chance(90) ? below(13) : random32();
    }
    else if (name == "inTunnel")
    {
        const x86::reg32 at = point();
        stack[0] = g.word(at);
        stack[1] = g.word(at + 4);
        stack[2] = g.word(at + 8);
        stack[3] = below(g_tdCount);
    }
    else if (name == "carFacingWay" || name == "carSectionKind")
        cpu.eax = kTdCar;
    return true;
}
#endif
