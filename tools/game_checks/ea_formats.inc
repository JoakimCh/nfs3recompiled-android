// game_checks.cpp's parts for EA's formats and keys under the menus: shapes located, unpack, loadpack, inkey
// (native_ea_formats.cpp), included in each table with the macro naming the part.
#if defined(EA_WINDOWS)
// {from, to}, -- what the functions write, compared
// The secondary timer's callbacks and lock (0x9f0c00 to 0x9f0c38).  The keys'
// globals and tables (0x564810 to 0x564a5f), the key hook and the timer's
// thread (0x5651d0, 0x5652ac: the sound's page), where an Error is from
// (0x552190), the loaded files (0x7700 on) and the blocks (0x1f0000 on) are
// on pages compared already; the cases' shape files and packed data in the
// harness's (0x61d000 to 0x620000).
{0x9f0000, 0x9f1000},
#elif defined(EA_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kFormatsKey,        // the key hook, a key taken: none (0) half the time, else a key
kFormatsCharacter,  // keyCharacter: a character, or a key of its own (shifted up a byte)
#elif defined(EA_EFFECT_CASES)
// case kSomething: ... break;
case kFormatsKey:
    result = r % 2 == 0 ? 0 : (r >> 8) % 4 == 0 ? (r >> 16) % 0x80 << 8 : 1 + (r >> 16) % 0xff;
    break;
case kFormatsCharacter:
    result = r % 5 == 0 ? (r >> 8) % 0x80 << 8 : (r >> 8) % 0x100;
    break;
#elif defined(EA_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// This file's that the other natives call (native_ea_formats.cpp, each held against its code here): a shape
// located (the shape file and the name's address, the name logged; a block or none back); a scan code's
// character; inkey (a key); the menus' keys flushed; a timer's callback removed; a packed file loaded
// (its name's first 16 bytes logged; a block or none back).
{0x4ef270, "locateShape", kWatcom, 2, 0, kEax | kEdx, 1, 1, kBlock},
{0x4f0010, "keyCharacter", kWatcom, 1, 0, kEax, -1, 0, kFormatsCharacter},
{0x4f0120, "inkey", kWatcom, 0, 0, kEax, -1, 0, kSomething},
{0x4f0240, "flushKeys", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4f29b0, "removeLowTimer", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4f2e20, "loadpackadr", kWatcom, 2, 0, kEax | kEdx, 0, 4, kBlock},
// The menus' next key taken, which flushKeys calls until none: a key or none.
#elif defined(EA_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// The key hook (set by the window's code): the next key, or none.
{0x5651d0, "the key hook", kWatcom, 0, 0, kEax, -1, 0, kFormatsKey},
#elif defined(EA_PROMISES)
// {"ea::name", watcom, result, arguments, fpu, heap, liveOnly},
{"ea::locateShape", true, true, 0},
{"ea::keyCharacter", true, true, 0},
{"ea::keyFromHook", true, true, 0},
{"ea::inkey", true, true, 0},
{"ea::flushKeys", true, true, 0},
{"ea::unpackQuietly", true, true, 0},
{"ea::unpack", true, true, 0},
{"ea::unpackSizeQuietly", true, true, 0},
{"ea::unpacksize", true, true, 0},
{"ea::stopLowTimer", true, true, 0},
{"ea::removeLowTimer", true, true, 0},
{"ea::loadpackadr", true, true, 0},
#elif defined(EA_ARGUMENTS)
/* Where the formats' cases keep their own: a shape file, the name looked
 * for, packed data and where it is unpacked to. */
constexpr x86::reg32 kFormatsShapes = 0x61d000, kFormatsName = 0x61dff0;
constexpr x86::reg32 kFormatsPacked = 0x61e000, kFormatsUnpacked = 0x61f000;

/* A code of packed data's: one of those known mostly (or that plus 1), any
 * now and then; and its mark: 0xfb mostly, 0x32, or any. */
x86::reg8 aPackCode()
{
    static const x86::reg8 codes[] = {0x10, 0x18, 0x30, 0x32, 0x34, 0x46, 0x4a};
    static const x86::reg8 edges[] = {0x0f, 0x10, 0x7f, 0x80};
    return x86::reg8(chance(80)   ? codes[below(7)] | below(2)
                     : chance(30) ? edges[below(4)]
                     : chance(50) ? 0x10 + below(0x70)
                                  : random32());
}

x86::reg8 aPackMark()
{
    return x86::reg8(chance(75) ? 0xfb : chance(50) ? 0x32 : random32());
}

/* Packed data's header at `at`: its code, its mark, its size unpacked. */
void makePackHeader(CheckApp& g, x86::reg32 at)
{
    g.getMemory<x86::reg8>(at) = aPackCode();
    g.getMemory<x86::reg8>(at + 1) = aPackMark();
    const x86::reg32 size = chance(10) ? 0 : chance(80) ? below(0x2000) : random32();
    g.getMemory<x86::reg8>(at + 2) = x86::reg8(size >> 16);
    g.getMemory<x86::reg8>(at + 3) = x86::reg8(size >> 8);
    g.getMemory<x86::reg8>(at + 4) = x86::reg8(size);
}

/* A name of a shape's: one of a few, so that some are found and some twice. */
x86::reg32 aShapeName()
{
    static const x86::reg32 names[] = {0x30303030, 0x31303030, 0x6e6f6369, 0x6b636162, 0x00000000};
    return chance(90) ? names[below(5)] : random32();
}

bool makeEaFormatsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    (void)stack;
    static const char* const names[] = {
        "locateShape", "keyCharacter", "keyFromHook", "inkey", "flushKeys",
        "unpackQuietly", "unpack", "unpackSizeQuietly", "unpacksize", "stopLowTimer",
        "removeLowTimer", "loadpackadr"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    // The keys held, Ctrl+Esc's leaving, Caps Lock; the key hook, mostly there.
    for (const x86::reg32 key : {0x564835u, 0x564842u, 0x56484eu, 0x564850u})
        g.getMemory<x86::reg8>(key) = x86::reg8(chance(75) ? 0 : chance(80) ? 0x80 : random32());
    g.word(0x564810) = chance(50) ? 0 : chance(80) ? 1 : random32();
    g.word(0x564814) = chance(50) ? 0 : chance(80) ? 1 : random32();
    g.word(0x5651d0) = chance(80) ? standInFor(0x5651d0) : 0;
    // The secondary timer: its lock or none, its thread's id or ended, its
    // callbacks -- a few of the same, gaps, the rest none.
    static const x86::reg32 callbacks[] = {0x4f5110, 0x514260, 0x4c9860, 0x4a0000,
                                           0x4a0010, 0x4a0020, 0x4a0030, 0x4a0040};
    g.word(0x9f0c34) = chance(15) ? 0 : 0x640000 - 0x100 + below(0x10) * 0x10;
    g.word(0x5652ac) = chance(50) ? 0 : random32();
    const x86::reg32 used = chance(30) ? 0 : chance(60) ? 1 + below(3) : below(9);
    const bool distinct = chance(40);  // each slot its own: the one removed anywhere, the last too
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x9f0c00 + 4 * i) = i < used ? (distinct ? callbacks[i] : chance(90) ? callbacks[below(4)] : 0)
                                   : chance(95) ? 0 : random32();
    // The game's errors on, or not.
    g.word(0x56440c) = chance(50) ? 0 : chance(80) ? 1 : random32();
    // The files loadFile gives (0x7700 to 0x77f0), each packed or not, the
    // size of the block before them (memBlockSize's, 0xc before) within what
    // the copy takes mostly.
    for (x86::reg32 at = 0x7700 - 0x10; at < 0x7800; at += 0x10)
    {
        for (x86::reg32 i = 0; i < 0x10; i += 4)
            g.word(at + i) = random32();
        g.word(at + 4) = chance(85) ? below(0x1000) : random32();
        if (at >= 0x7700 && chance(70))
            makePackHeader(g, at);
    }
    // A shape file: a count of entries (none, a few, now and then any), their
    // names and offsets; the name looked for, one of the file's mostly.
    const x86::reg32 count = chance(10) ? 0 : chance(90) ? 1 + below(20) : chance(50) ? below(0x1f0) : random32();
    g.word(kFormatsShapes + 8) = count;
    for (x86::reg32 i = 0; i < 0x1f0; ++i)
    {
        g.word(kFormatsShapes + 0x10 + 8 * i) = aShapeName();
        g.word(kFormatsShapes + 0x14 + 8 * i) = chance(90) ? below(0x10000) : random32();
    }
    g.word(kFormatsName) = aShapeName();
    // Packed data.
    for (x86::reg32 at = kFormatsPacked; at < kFormatsPacked + 0x100; at += 4)
        g.word(at) = random32();
    const x86::reg32 packed = kFormatsPacked + (chance(70) ? 0 : below(0x80));
    makePackHeader(g, packed);
    if (name == "locateShape")
    {
        cpu.eax = kFormatsShapes;
        cpu.edx = chance(80) ? kFormatsName : kFormatsShapes + 0x10 + 8 * below(0x20);
        // Past a count that runs over the file: the words are what they are,
        // as long as they are the guest's.
        if (count > 0x1f0)
            g.word(kFormatsShapes + 8) = count % 0x1f0;
    }
    else if (name == "keyCharacter")
    {
        // A scan code of the tables' mostly, Caps Lock's or Esc's often; ecx
        // where Ctrl+Esc's exit coming back reads with it.
        cpu.eax = chance(20) ? 0x3a : chance(20) ? 1 : chance(90) ? below(0x5b) : 0x5b + below(0x80);
        cpu.ecx = chance(50) ? 0x564898 + below(0x100) : below(0xe00000);
    }
    else if (name == "inkey" || name == "flushKeys")
    {
        g_mostCalls = 40;  // the key hook never giving one
        // inkey's check of a surface locked on, mostly, which names it in its Error.
        g.word(0x564364) = chance(70) ? 1 : 0;
    }
    else if (name == "unpackQuietly" || name == "unpack" || name == "unpackSizeQuietly"
             || name == "unpacksize")
    {
        cpu.eax = packed;
        cpu.edx = kFormatsUnpacked + below(0x10);
        cpu.ebx = random32();
    }
    else if (name == "stopLowTimer" || name == "removeLowTimer")
    {
        cpu.eax = chance(85) ? callbacks[below(8)] : chance(50) ? 0 : random32();
        g_mostCalls = 30;  // the thread never ending
    }
    else if (name == "loadpackadr")
    {
        cpu.eax = 0x600000 + 0x40 * below(64);  // a string of the harness's
        cpu.edx = chance(50) ? below(0x40) : random32();
    }
    return true;
}
#endif
