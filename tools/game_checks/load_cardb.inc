// game_checks.cpp's parts for the cars' database: the cars' list and records read from fedata, car.viv, the .FEC and carp.txt
// (native_load_cardb.cpp), included in each table with the macro naming the part.
#if defined(LOAD_WINDOWS)
// {from, to}, -- what the functions write, compared
// The classes' list of class 0xff's cars, past the others (0x5552d8 + 0x100 *
// 0xc8: the game's data trusted).  The list, the menus' items, the walks'
// data, the cache, the globals and the carmodel folder's path (0x7a28b4) are
// on pages compared already; the records in the harness's (0x61d000 to
// 0x620000) and in the game's blocks (0x1f0000).
{0x56f000, 0x570000},
#elif defined(LOAD_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kCardbCarId,      // makeCarId: zeros at eax, the number first
kCardbFolder,     // the folders' walk: a name at 0x5f3aec, or none (always none once a car is loaded)
kCardbFile,       // the files' walk: a name at 0x5f39ac, or none
kCardbSpecs,      // a car's specs loaded: a word to [ecx]
kCardbFindNext,   // FindNextFileA: a folder's or file's attributes and short name, or FALSE
kCardbGuid,       // CoCreateGuid: 16 bytes and S_OK, or E_FAIL
kCardbVivEntry,   // a .viv's entry looked up: one of the cases' 4, or none
#elif defined(LOAD_EFFECT_CASES)
// case kSomething: ... break;
case kCardbCarId:
    if (words[0] < kMemory - 0x10)
    {
        for (x86::reg32 i = 0; i < 0x10; i += 4)
            word(words[0] + i) = 0;
        word(words[0]) = words[1];
    }
    result = words[0];
    break;
case kCardbFolder:
{
    // None once the list holds a car loaded into the game's blocks: the
    // blocks are handed out again, and a second would make the list a loop.
    bool loaded = false;
    std::vector<x86::reg32> listed;
    for (x86::reg32 car = word(0x554f70), n = 0; car != 0 && car < kMemory - 0x400 && n < 64; car = word(car), ++n)
    {
        loaded = loaded || (car >= kBlocks && car < kBlocks + 0x2000);
        listed.push_back(car);
    }
    result = 0;
    if (r % 5 != 0 && !loaded)
    {
        const x86::reg32 kind = (r >> 8) % 10;
        std::string name = kind == 0 ? "traffic" : kind == 1 ? "TRAFFIC" : "c";
        if (kind >= 2 && kind <= 4 && !listed.empty())
        {
            const x86::reg32 car = listed[(r >> 12) % listed.size()];
            name.clear();
            for (x86::reg32 i = 0; i < 0x20 && getMemory<char>(car + 0x110 + i) != 0; ++i)
                name += getMemory<char>(car + 0x110 + i);
        }
        else if (kind >= 2)
            name += char('0' + (r >> 16) % 10), name += char('a' + (r >> 20) % 6);
        for (x86::reg32 i = 0; i <= name.size(); ++i)
            getMemory<char>(0x5f3aec + i) = i < name.size() ? name[i] : 0;
        word(0x5f3ac0) = 0x10;
        result = 0x5f3aec;
    }
    break;
}
case kCardbFile:
    result = 0;
    if (r % 3 != 0)
    {
        const char name[] = {'f', char('0' + (r >> 8) % 10), '.', 'd', 0};
        for (x86::reg32 i = 0; i < sizeof name; ++i)
            getMemory<char>(0x5f39ac + i) = name[i];
        word(0x5f3980) = 0x20;
        result = 0x5f39ac;
    }
    break;
case kCardbSpecs:
    if (words[3] < kMemory - 4)
        word(words[3]) = r % 3 == 0 ? 0 : random(id + 1);
    break;
case kCardbFindNext:
{
    static const char* const names[] = {".", "..", "car", "Data", "f50", "x1"};
    result = r % 4 != 0 ? 1 : 0;
    if (result != 0 && words[1] < kMemory - 0x140)
    {
        word(words[1]) = ((r >> 8) % 3 == 0 ? 0x20 : 0x10 | ((r >> 10) & 0x20)) | ((r >> 16) % 4 == 0 ? (r >> 20) & 7 : 0);
        const std::string name = names[(r >> 12) % 6];
        for (x86::reg32 i = 0; i <= name.size(); ++i)
            getMemory<char>(words[1] + 0x2c + i) = i < name.size() ? name[i] : 0;
    }
    break;
}
case kCardbGuid:
    result = r % 5 == 0 ? 0x80004005 : 0;
    if (result == 0 && words[0] < kMemory - 0x10)
        for (x86::reg32 i = 0; i < 0x10; i += 4)
            word(words[0] + i) = random(id + i);
    break;
case kCardbVivEntry:
    result = r % 3 == 0 ? 0 : 0x61ee00 + 0x30 * ((r >> 8) % 4);
    break;
#elif defined(LOAD_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// This file's that the saves' natives call (makeCarId), and the folders' and
// files' walks, called by address so that the list's loading walks sane
// names (FindFirstFileA's stand-in makes up long ones) and ends.
{0x438ad0, "makeCarId", kWatcom, 2, 0, kEax | kEdx, -1, 0, kCardbCarId},
{0x4386b0, "firstSubfolder", kWatcom, 1, 0, kEax, 0, 4, kCardbFolder},
{0x4387e0, "nextSubfolder", kWatcom, 0, 0, kEax, -1, 0, kCardbFolder},
{0x438870, "firstFile", kWatcom, 1, 0, kEax, 0, 4, kCardbFile},
{0x438970, "nextFile", kWatcom, 0, 0, kEax, -1, 0, kCardbFile},
// The game's: the language's name and a language's, a car's specs
// loaded (ret 4: the path's), the players' settings checked, the classes'
// comparison of two cars' names (qsort's).
{0x478290, "the language's name", kWatcom, 0, 0, kEax, -1, 0, kString},
{0x4782b0, "a language's name", kWatcom, 1, 0, kEax, -1, 0, kString},
{0x49c700, "a car's specs loaded", kStdcall, 4, 1, kScratch | kEbx, 0, 4, kCardbSpecs},
{0x4dc940, "a player's settings checked", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x43a4d0, "two cars' names compared", kWatcom, 2, 0, kEax | kEdx, -1, 0, kCompare},
#elif defined(LOAD_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// Windows' functions the walks and the new car's id call that nothing else does.
{0x5344d0, "FindNextFileA", kStdcall, 0, 2, kScratch, -1, 0, kCardbFindNext},
{0x534478, "CoCreateGuid", kStdcall, 0, 1, kScratch, -1, 0, kCardbGuid},
#elif defined(LOAD_PROMISES)
// {"load::name", watcom, result, arguments, fpu, heap, liveOnly},
{"load::endWithSlash", true, true, 0},
{"load::folderWritable", true, true, 0},
{"load::firstFreeHexFolder", true, true, 0},
{"load::firstFreePlayerFolder", true, true, 0},
{"load::freePlayerCarFolder", true, true, 0},
{"load::firstSubfolder", true, true, 0},
{"load::nextSubfolder", true, true, 0},
{"load::firstFile", true, true, 0},
{"load::nextFile", true, true, 0},
{"load::removeFolder", true, true, 0},
{"load::firstCar", true, true, 0},
{"load::nextCar", true, true, 0},
{"load::makeCarId", true, true, 0},
{"load::firstCarGlobal", true, true, 0},
{"load::nextCarGlobal", true, true, 0},
{"load::appendCar", true, true, 0},
{"load::carCount", true, true, 0},
{"load::countCars", true, true, 0},
{"load::unlinkCar", true, true, 0},
{"load::insertCarByName", true, true, 0},
{"load::joinCarLists", true, true, 0},
{"load::carListOf", true, true, 0},
{"load::takePoliceCars", true, true, 0},
{"load::takeClasslessCars", true, true, 0},
{"load::takeOrdinaryCars", true, true, 0},
{"load::sortCars", true, true, 0},
{"load::carName", true, true, 0},
{"load::carFolder", true, true, 0},
{"load::carFilePrefix", true, true, 0},
{"load::carId", true, true, 0},
{"load::carFlag40", true, true, 0},
{"load::carFlag4", true, true, 0},
{"load::carHasNumericId", true, true, 0},
{"load::idIsNumeric", true, true, 0},
{"load::numericId", true, true, 0},
{"load::carIsBonus", true, true, 0},
{"load::carIsPolice", true, true, 0},
{"load::carIsFerrariOrMercedes", true, true, 0},
{"load::carClass", true, true, 0},
{"load::findCarById", true, true, 0},
{"load::clearCarCache", true, true, 0},
{"load::carRecord", true, true, 0},
{"load::fecText", true, true, 0},
{"load::findCarByName", true, true, 0},
{"load::attachFecTexts", true, true, 0},
{"load::bonusCarLocked", true, true, 0},
{"load::checkDuplicateCars", true, true, 0},
{"load::loadCarList", true, true, 0},
{"load::carSelectable", true, true, 0},
{"load::buildCarClassLists", true, true, 0},
{"load::copyCarAsNew", true, true, 0},
{"load::loadCarSpecs", true, true, 0},
{"load::writeCarFec", true, true, 0},
{"load::readCarFecBody", true, true, 0},
{"load::readCarFec", true, true, 0},
{"load::carFecPath", true, true, 0},
{"load::loadCarFec", true, true, 0},
{"load::placeCarVivPath", true, true, 0},
{"load::swapBytes", true, true, 0},
{"load::writeBigEndian", true, true, 0},
{"load::appendCarpToViv", true, true, 0},
{"load::lastCarLoaded", true, true, 0},
{"load::setLastCarId", true, true, 0},
{"load::setLastCarName", true, true, 0},
{"load::setLastCarFlags", true, true, 0},
{"load::markLastCarFlag8", true, true, 0},
#elif defined(LOAD_ARGUMENTS)
/* Where the cars' cases keep their own: 8 records (0x3a8 apart), the .viv's
 * 4 entries (0x30 each: +0x20 the data's length, +0x24 the data), cursors,
 * ids and pairs, strings (8 of 0x80: paths and names), the entries' data (4
 * of 0x100), and what the functions write. */
constexpr x86::reg32 kCardbRecords = 0x61d000, kCardbRecordStride = 0x3a8;
constexpr x86::reg32 kCardbEntries = 0x61ee00;
constexpr x86::reg32 kCardbWords = 0x61ef00;
constexpr x86::reg32 kCardbStrings = 0x61f000;
constexpr x86::reg32 kCardbData = 0x61f400;
constexpr x86::reg32 kCardbOut = 0x61f800;

x86::reg32 aCardbRecord(x86::reg32 i)
{
    return kCardbRecords + kCardbRecordStride * i;
}

void putCardbString(CheckApp& g, x86::reg32 at, const std::string& text)
{
    for (x86::reg32 i = 0; i <= text.size(); ++i)
        g.getMemory<char>(at + i) = i < text.size() ? text[i] : 0;
}

/* A car's name: one of a few, the same now and then. */
std::string aCardbName()
{
    static const char* const names[] = {"Diablo SV", "F50", "CL 600", "Jaguar XJR-15", "Corvette",
                                        "El Nino", "Spectre R42", "Mercedes", "Ferrari", "Atlas", "", "f50"};
    return names[below(12)];
}

/* A folder's name: "c" and two characters, "traffic" now and then. */
std::string aCardbFolder()
{
    if (chance(8))
        return chance(50) ? "traffic" : "Traffic";
    return std::string("c") + char('0' + below(10)) + char('a' + below(6));
}

/* An id into the 16 bytes at `at`: a number (of the bonus cars', 15, 16,
 * 0x21, below 0x40) and zeros, or anything, or one of them spoilt. */
void putCardbId(CheckApp& g, x86::reg32 at)
{
    static const x86::reg32 numbers[] = {0x11, 0x12, 0x24, 0x27, 0x31, 0xf, 0x10, 0x21};
    for (x86::reg32 i = 0; i < 0x10; i += 4)
        g.word(at + i) = chance(55) ? 0 : random32();
    g.word(at) = chance(50) ? numbers[below(8)] : chance(60) ? below(0x40) : random32();
}

/* A place in the list: of the 8 mostly, past them, of the other ranges
 * (names and folders by table), now and then a little below 0. */
x86::reg32 aCardbIndex()
{
    if (chance(70))
        return below(10);
    static const x86::reg32 edges[] = {0x31, 0x32, 0x1f3, 0x1f4, 0x257, 0x258, 0x2bb, 0x2bc};
    switch (below(7))
    {
    case 5: return edges[below(8)];
    case 0: return 0x32 + below(0x1c2);
    case 1: return 0x1f4 + below(0x64);
    case 2: return 0x258 + below(0x64);
    case 3: return 0x2bc + below(0x100);
    case 4: return x86::reg32(-1 - x86::sreg32(below(4)));
    default: return 0x30 + below(4);
    }
}

/* A chain of `count` of the records from `first` on, linked in order (sorted
 * by name where asked), its head and its last; 0 and anything for none. */
std::pair<x86::reg32, x86::reg32> aCardbChain(CheckApp& g, x86::reg32 first, x86::reg32 count, bool sorted)
{
    std::vector<x86::reg32> cars;
    for (x86::reg32 i = 0; i < count; ++i)
        cars.push_back(aCardbRecord(first + i));
    if (sorted)
        std::sort(cars.begin(), cars.end(), [&](x86::reg32 a, x86::reg32 b) {
            return std::strcmp(&g.getMemory<char>(a + 0x10), &g.getMemory<char>(b + 0x10)) < 0;
        });
    for (size_t i = 0; i < cars.size(); ++i)
        g.word(cars[i]) = i + 1 < cars.size() ? cars[i + 1] : 0;
    if (cars.empty())
        return {0, chance(50) ? 0 : random32()};
    return {cars.front(), cars.back()};
}

/* A car's fedata as the game reads it, into the block at `at` (0x400):
 * version 9 mostly, the flags' words, the class, the id, the .FEC's texts
 * (their count at +0x2d, their offsets at +0x2f, the texts at +0x100 on:
 * the maker's first, the name third). */
void putCardbFedata(CheckApp& g, x86::reg32 at)
{
    static const char* const makers[] = {"Ferrari", "Mercedes", "ferrari", "MERCEDES", "Lotus", "Jaguar"};
    for (x86::reg32 i = 0; i < 0x400; i += 4)
        g.word(at + i) = random32();
    const auto word16 = [&](x86::reg32 offset, x86::reg32 value) {
        g.getMemory<x86::reg16>(at + offset) = x86::reg16(value);
    };
    word16(4, chance(85) ? 9 : below(12));
    for (const x86::reg32 offset : {6u, 8u, 0xeu, 0x10u, 0x14u})
        word16(offset, chance(25) ? 1 + below(3) : 0);
    word16(0xa, chance(80) ? below(4) : chance(50) ? 0xff : 0xffff);
    putCardbId(g, at + 0x18);
    const x86::reg32 count = chance(85) ? 3 + below(3) : chance(50) ? 0 : below(3);
    word16(0x2d, count);
    for (x86::reg32 i = 0; i < 6; ++i)
    {
        g.getMemory<x86::reg32>(at + 0x2f + 4 * i) = 0x100 + 0x40 * i;
        putCardbString(g, at + 0x100 + 0x40 * i, i == 0 ? makers[below(6)] : aCardbName());
    }
}

/* The cars' world: the records and the list of some of them, the cursor,
 * the count, the cache, the last car loaded, the walks' handles; the
 * carmodel folder's path, the language, the options, the bonus cars
 * unlocked, the mode and the players' cars; the game's blocks as fedata;
 * the .viv's entries; the stand-ins' FILEs (and modules, folders' names)
 * in low memory zeroed. */
void makeCardbWorld(CheckApp& g)
{
    for (x86::reg32 at = 0x7700; at < 0x7800; at += 4)
        g.word(at) = 0;
    g.word(0) = 0x6f6c;  // "lo": what a folder's name of 0 reads
    for (x86::reg32 at = kCardbRecords; at < 0x620000; at += 4)
        g.word(at) = random32();
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        const x86::reg32 car = aCardbRecord(i);
        g.getMemory<x86::reg16>(car + 4) = x86::reg16(below(6));
        g.word(car + 8) = kCardbData + 0x100 * below(4);
        g.word(car + 0xc) = g.word(car + 8) + 0x2f;
        putCardbString(g, car + 0x10, aCardbName());
        const std::string folder = aCardbFolder();
        putCardbString(g, car + 0x110, folder);
        putCardbString(g, car + 0x210, folder);
        putCardbString(g, car + 0x310, "car");
        putCardbId(g, car + 0x31c);
        if (i > 0 && chance(10))
            for (x86::reg32 j = 0; j < 0x10; j += 4)
                g.word(car + 0x31c + j) = g.word(aCardbRecord(below(i)) + 0x31c + j);
        g.word(car + 0x380) = random32() & (chance(70) ? 0x7f : 0xffffffff);
        g.word(car + 0x388) = chance(80) ? below(4) : chance(50) ? 0xff : 0xffffffff;
    }
    // The list: some of the records, in an order of their own.
    x86::reg32 order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (x86::reg32 i = 7; i > 0; --i)
        std::swap(order[i], order[below(i + 1)]);
    const x86::reg32 count = chance(10) ? 0 : 1 + below(chance(70) ? 6 : 8);
    for (x86::reg32 i = 0; i < count; ++i)
        g.word(aCardbRecord(order[i])) = i + 1 < count ? aCardbRecord(order[i + 1]) : 0;
    g.word(0x554f70) = count == 0 ? 0 : aCardbRecord(order[0]);
    const auto aListed = [&] { return count == 0 || chance(10) ? 0 : aCardbRecord(order[below(count)]); };
    g.word(0x5f3ccc) = aListed();
    g.word(0x5f3cc8) = chance(80) ? count : below(9);
    const bool cached = chance(50);
    for (x86::reg32 i = 0; i < 0x32; ++i)
        g.word(0x5f3c00 + 4 * i) = !cached || chance(60) ? 0
                                   : chance(85) && i < count ? aCardbRecord(order[i]) : aListed();
    // Below the cache, where a place below 0 reads and writes: 0 or a record.
    for (x86::reg32 i = 1; i <= 4; ++i)
        g.word(0x5f3c00 - 4 * i) = chance(50) ? 0 : aCardbRecord(below(8));
    g.word(0x554f74) = chance(85) ? aListed() : aCardbRecord(below(8));
    g.word(0x554f78) = chance(40) ? 0 : 0x7f00 + below(0x100);
    g.word(0x554f7c) = chance(40) ? 0 : 0x7f00 + below(0x100);
    // The carmodel folder, the language, the options, the bonus cars, the mode, the players.
    static const char* const paths[] = {"gamedata\\carmodel", "gamedata\\carmodel\\", "", "c:\\nfs3\\cars"};
    putCardbString(g, 0x7a28b4, paths[below(4)]);
    g.word(0x7a3a50) = below(7);
    g.getMemory<x86::reg8>(0x55eb2e) = x86::reg8(chance(70) ? random32() & 0xcf : random32());
    g.word(0x6fd2a8) = chance(30) ? 0 : random32() & (chance(70) ? 0x1f : 0xffffffff);
    g.word(0x6fd3b8) = chance(40) ? 3 : below(6);
    g.word(0x6fd3b0) = chance(80) ? below(2) : below(4);
    g.word(0x6fd2bc) = below(9);
    g.word(0x6fd328) = below(9);
    g.word(0x554f50) = chance(70) ? 0 : chance(70) ? below(4) : x86::reg32(-1 - x86::sreg32(below(3)));
    // The game's blocks, as cars' fedata; the .viv's entries and their data.
    for (x86::reg32 b = 0; b < 8; ++b)
        putCardbFedata(g, kBlocks + 0x400 * b);
    for (x86::reg32 e = 0; e < 4; ++e)
    {
        g.word(kCardbEntries + 0x30 * e + 0x20) = below(0x100);
        g.word(kCardbEntries + 0x30 * e + 0x24) = kCardbData + 0x100 * e;
    }
    // Strings: a path, names.
    putCardbString(g, kCardbStrings, paths[below(4)]);
    for (x86::reg32 i = 1; i < 8; ++i)
        putCardbString(g, kCardbStrings + 0x80 * i, chance(50) ? aCardbName() : aCardbFolder());
}

bool makeLoadCardbArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "endWithSlash", "folderWritable", "firstFreeHexFolder", "firstFreePlayerFolder", "freePlayerCarFolder",
        "firstSubfolder", "nextSubfolder", "firstFile", "nextFile", "removeFolder", "firstCar", "nextCar",
        "makeCarId", "firstCarGlobal", "nextCarGlobal", "appendCar", "carCount", "countCars", "unlinkCar",
        "insertCarByName", "joinCarLists", "carListOf", "takePoliceCars", "takeClasslessCars",
        "takeOrdinaryCars", "sortCars", "carName", "carFolder", "carFilePrefix", "carId", "carFlag40",
        "carFlag4", "carHasNumericId", "idIsNumeric", "numericId", "carIsBonus", "carIsPolice",
        "carIsFerrariOrMercedes", "carClass", "findCarById", "clearCarCache", "carRecord", "fecText",
        "findCarByName", "attachFecTexts", "bonusCarLocked", "checkDuplicateCars", "loadCarList",
        "carSelectable", "buildCarClassLists", "copyCarAsNew", "loadCarSpecs", "writeCarFec",
        "readCarFecBody", "readCarFec", "carFecPath", "loadCarFec", "placeCarVivPath", "swapBytes",
        "writeBigEndian", "appendCarpToViv", "lastCarLoaded", "setLastCarId", "setLastCarName",
        "setLastCarFlags", "markLastCarFlag8"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makeCardbWorld(g);
    // The walks' and the folders' loops: bounded, whatever the stand-ins say.
    g_mostCalls = 3000;
    const x86::reg32 esp = cpu.esp;
    const auto aString = [] { return kCardbStrings + 0x80 * below(8); };
    const auto aFile = [] { return chance(10) ? 0 : 0x7700 + 0x10 * below(0x10); };
    // A record of the 8 not in the list, where there is one.
    const auto aFreeRecord = [&] {
        std::vector<x86::reg32> free;
        for (x86::reg32 i = 0; i < 8; ++i)
        {
            bool listed = false;
            for (x86::reg32 car = g.word(0x554f70); car != 0; car = g.word(car))
                listed = listed || car == aCardbRecord(i);
            if (!listed)
                free.push_back(aCardbRecord(i));
        }
        return free.empty() ? aCardbRecord(below(8)) : free[below(x86::reg32(free.size()))];
    };
    const auto aRecord = [] { return aCardbRecord(below(8)); };
    if (name == "endWithSlash" || name == "folderWritable" || name == "firstSubfolder" || name == "firstFile"
        || name == "removeFolder" || name == "appendCarpToViv")
        cpu.eax = aString();
    else if (name == "firstFreeHexFolder" || name == "firstFreePlayerFolder")
    {
        cpu.eax = aString();
        cpu.edx = kCardbOut;
    }
    else if (name == "freePlayerCarFolder")
        cpu.eax = kCardbOut;
    else if (name == "firstCar" || name == "nextCar")
    {
        cpu.eax = kCardbWords;
        g.word(kCardbWords) = chance(15) ? 0 : g.word(0x5f3ccc);
    }
    else if (name == "makeCarId" || name == "setLastCarId")
    {
        cpu.eax = kCardbWords + 4 * below(8);
        cpu.edx = chance(50) ? below(0x40) : random32();
    }
    else if (name == "appendCar")
        cpu.eax = chance(90) ? aFreeRecord() : aRecord();
    else if (name == "unlinkCar" || name == "bonusCarLocked")
        cpu.eax = chance(80) ? aRecord() : aFreeRecord();
    else if (name == "insertCarByName")
    {
        // A chain of the first records, sorted mostly, and one of the others.
        for (x86::reg32 i = 0; i < 8; ++i)
            g.word(aCardbRecord(i)) = 0;
        const x86::reg32 count = below(6);
        const auto chain = aCardbChain(g, 0, count, chance(85));
        cpu.esi = kCardbWords + 0x40;
        stack[0] = chain.first;
        stack[1] = chain.second;
        stack[2] = aCardbRecord(count + below(8 - count));
        g.word(0x554f70) = 0;
    }
    else if (name == "joinCarLists")
    {
        for (x86::reg32 i = 0; i < 8; ++i)
            g.word(aCardbRecord(i)) = 0;
        const x86::reg32 first = below(5), second = below(9 - first);
        const auto a = aCardbChain(g, 0, first, false);
        const auto b = aCardbChain(g, first, second, false);
        cpu.esi = kCardbWords + 0x40;
        stack[0] = a.first;
        stack[1] = a.second;
        stack[2] = b.first;
        stack[3] = b.second;
        g.word(0x554f70) = 0;
    }
    else if (name == "carListOf")
    {
        cpu.esi = kCardbWords + 0x40;
        cpu.eax = chance(15) ? 0 : g.word(0x554f70);
    }
    else if (name == "takePoliceCars" || name == "takeClasslessCars" || name == "takeOrdinaryCars")
        cpu.esi = kCardbWords + 0x40;
    else if (name == "carName" || name == "carFolder" || name == "carFilePrefix" || name == "carId"
             || name == "carFlag40" || name == "carFlag4" || name == "carHasNumericId" || name == "carIsBonus"
             || name == "carIsPolice" || name == "carIsFerrariOrMercedes" || name == "carClass"
             || name == "carRecord" || name == "carSelectable" || name == "loadCarSpecs" || name == "loadCarFec")
        cpu.eax = aCardbIndex();
    else if (name == "idIsNumeric" || name == "numericId" || name == "findCarById")
    {
        if (chance(50))
            cpu.eax = aRecord() + 0x31c;
        else
        {
            cpu.eax = kCardbWords + 0x80;
            putCardbId(g, cpu.eax);
            // One of the id's words spoilt now and then.
            if (chance(30))
                g.getMemory<x86::reg8>(cpu.eax + 4 + below(12)) = x86::reg8(1 + below(255));
        }
    }
    else if (name == "fecText")
    {
        // The texts' header: their count, the fedata, the offsets.
        cpu.eax = kCardbWords + 0x60;
        g.getMemory<x86::reg16>(cpu.eax) = x86::reg16(chance(80) ? below(7) : chance(50) ? 0x8000 + below(4) : 0);
        g.word(cpu.eax + 4) = random32();
        g.word(cpu.eax + 8) = kCardbData + 0x10 * below(8);
        cpu.edx = chance(85) ? below(8) : x86::reg32(-1 - x86::sreg32(below(3)));
    }
    else if (name == "findCarByName")
        cpu.eax = chance(60) ? aRecord() + 0x10 : aString();
    else if (name == "attachFecTexts")
    {
        cpu.eax = aRecord();
        cpu.edx = chance(50) ? kBlocks + 0x400 * below(8) : kCardbData + 0x100 * below(4);
    }
    else if (name == "copyCarAsNew")
    {
        cpu.eax = chance(60) ? aRecord() + 0x10 : aString();
        cpu.edx = aCardbIndex();
    }
    else if (name == "writeCarFec")
    {
        cpu.eax = aString();
        cpu.edx = aRecord();
    }
    else if (name == "readCarFecBody" || name == "readCarFec")
    {
        cpu.eax = aFile();
        cpu.edx = aRecord();
        // The .FEC's first word, where fread (which writes nothing) leaves it: 1 now and then.
        if (name == "readCarFec" && chance(50))
            g.word(esp - 0x18) = 1;
    }
    else if (name == "carFecPath")
    {
        cpu.eax = aCardbIndex();
        cpu.edx = kCardbOut;
    }
    else if (name == "swapBytes")
        cpu.eax = kCardbWords + below(0x20);
    else if (name == "writeBigEndian")
    {
        cpu.eax = aFile();
        cpu.edx = random32();
    }
    else if (name == "setLastCarName")
        cpu.eax = aString();
    else if (name == "setLastCarFlags")
        cpu.eax = random32();
    if (name == "loadCarFec")
    {
        // Its .FEC's first word and readCarFec's, where fread leaves them.
        if (chance(50))
            g.word(esp - 0x1c) = 1;
        if (chance(50))
            g.word(esp - 0x164) = 1;
    }
    return true;
}
#endif
