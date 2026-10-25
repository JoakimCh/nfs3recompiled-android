#include "native_guest.h"

/* The game's data: the cars' database, read from the carmodel folder (its
 * path at 0x7a28b4) a car's folder at a time.  disassemble_nfs3hp.py binds
 * each address to the function of that name here (LOAD_CARDB_NATIVES), and
 * the generated code calls it by name.  tools/game_checks holds each against
 * its generated code.
 *
 * The cars are a list (its head at 0x554f70) of records of 0x3a4 bytes: +0
 * the next, +4 the .FEC's texts (their count, a word; +8 the fedata read in,
 * +0xc its offsets at +0x2f), +0x10 the car's name, +0x110 and +0x210 its
 * folder's, +0x310 its files' prefix ("car"), +0x315 the fedata's first four
 * bytes, +0x31c its id (16 bytes: for the game's own cars a number below 50
 * and zeros), +0x32c and +0x378 the .FEC's two quads, +0x334 and +0x338 its
 * specs (car.viv's), +0x380 its flags (1 a bonus car, 2, 4, 8, 0x10 a police
 * car, 0x20 a Ferrari or a Mercedes, 0x40), +0x384 a nibble of the fedata's,
 * +0x388 its class (0xff none), +0x38c to +0x3a0 more of the fedata's.  A
 * record by its place in the list goes through a cache of 50 (0x5f3c00); the
 * count is kept at 0x5f3cc8, the last car loaded at 0x554f74.  A car's
 * fedata is its folder's fedata.<language> or the entry of that name in its
 * car.viv; it must be of version 9.  loadCarList reads every folder in, sorts
 * the list (ordinary cars by name, then the police's, then those of no
 * class, then the rest), makes the car menus' items and colours
 * (0x554fa8.., 0x555138..) and the classes' lists (0x5552d8..).  The folders
 * and files are walked with FindFirstFileA's handles at 0x554f78 (folders,
 * their data at 0x5f3ac0) and 0x554f7c (files, at 0x5f3980).
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the frame's locals in the guest's memory,
 * the registers as the code leaves them, a string's copy and length as the
 * runtime's inline loops leave esi, edi, ecx and eax.  The functions of this
 * file that tools/game_checks stands in for (the folders' and files' walkers,
 * carRecord, carFolder, carId, carIsPolice, loadCarList) are called by
 * address, as is every other function of the game's and Windows' through its
 * imports. */
namespace nfs3hp
{
namespace load
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg16;
using x86::reg32;
using x86::reg8;
using x86::sreg32;
using App = win32::WinApplication;
using CPU = x86::CPU;

// The list and its records.
constexpr reg32 kCarList = 0x554f70, kLastCar = 0x554f74, kCache = 0x5f3c00, kCount = 0x5f3cc8;
constexpr reg32 kCursor = 0x5f3ccc, kRecordBytes = 0x3a4;
// The folders' and files' walks: the handles, the find data, the names in it.
constexpr reg32 kFolderFind = 0x554f78, kFileFind = 0x554f7c;
constexpr reg32 kFolderData = 0x5f3ac0, kFolderName = 0x5f3aec, kFileData = 0x5f3980, kFileName = 0x5f39ac;
// What a car's name is where there is no record of it (0x32 to 0x1f3).
constexpr reg32 kNoRecordName = 0x554f80;
// The other cars' names, folders and prefixes, by their numbers.
constexpr reg32 kNamesFrom500 = 0x55c944, kFoldersTo499 = 0x55cfb0, kFoldersFrom500 = 0x55c92c;
constexpr reg32 kPrefixesFrom600 = 0x55c75c;
// The carmodel folder, the language, the bonus cars unlocked, the options.
constexpr reg32 kCarmodelPath = 0x7a28b4, kLanguage = 0x7a3a50, kBonusUnlocked = 0x6fd2a8, kOptions = 0x55eb2e;
// What carSelectable asks: the game's mode, the players' kind, their cars.
constexpr reg32 kGameMode = 0x6fd3b8, kPlayersKind = 0x6fd3b0, kPlayerCar = 0x6fd2bc, kSecondCar = 0x6fd328;
// The menus': the cars' items, flags and colours; the car of id 0x21.
constexpr reg32 kMenuHeads = 0x555130, kMenuColoursHead = 0x555204;
constexpr reg32 kCarItems = 0x555138, kCarItemOn = 0x5551a2, kCarColours = 0x555214;
constexpr reg32 kAllItems = 0x554fa8, kAllItemOn = 0x55500a, kAllColours = 0x55506c, kCar21 = 0x6fdc30;
constexpr reg32 kWhite = 0xff649dfd, kGrey = 0x908080, kFirstItem = 0x7bd;
// The classes' lists: 0xc8 bytes each, their counts, and how many cars are not in them.
constexpr reg32 kClassLists = 0x5552d8, kClassCounts = 0x5555f8, kNotListed = 0x554f50;
constexpr reg32 kClassCompare = 0x43a4d0;
// The game's strings.
constexpr reg32 kExistNam = 0x537658, kWriteBinary = 0x537664, kHexFolder = 0x537668, kPlayerFolder = 0x537670;
constexpr reg32 kAllFiles = 0x537684, kDot = 0x537688, kDotDot = 0x53768c, kEmpty = 0x537690, kCar = 0x537694;
constexpr reg32 kDuplicates = 0x5376a4, kTraffic = 0x5376d0, kFedataPath = 0x5376d8, kReadBinary = 0x5376e4;
constexpr reg32 kCarVivUpper = 0x5376e8, kFerrari = 0x5376f0, kMercedes = 0x5376f8, kCarViv = 0x537704;
constexpr reg32 kFedataName = 0x53770c, kFec = 0x537718, kPlaceViv = 0x537720, kCarpTxt = 0x537738;
constexpr reg32 kReadUpdate = 0x537744;
// Windows' functions, by their imports' slots.
constexpr reg32 kCoCreateGuid = 0x534478, kFindClose = 0x5344c8, kFindFirstFileA = 0x5344cc;
constexpr reg32 kFindNextFileA = 0x5344d0;
// The game's functions, by address: a path ended with '\', a file copied,
// the language's name, the car's specs loaded, a player's settings checked;
// the .viv's (track's) lookup, its write and its parse; a file written whole.
constexpr reg32 kAddSlash = 0x4529a0, kCopyFile = 0x452a00, kLanguageName = 0x478290;
constexpr reg32 kLanguageNameOf = 0x4782b0, kLoadSpecs = 0x49c700, kPlayerSettings = 0x4dc940;
constexpr reg32 kVivEntry = 0x418fe0, kVivSave = 0x419460, kVivParse = 0x4195f0, kWriteWhole = 0x4eebb0;
constexpr reg32 kError = 0x401010, kSprintf = 0x4df690, kMemset = 0x4e0640, kFillZero = 0x4e070c;
constexpr reg32 kStrncpy = 0x4e0e30, kLoadFileQuietly = 0x4e0fe0, kAllocate = 0x4e1620, kFree = 0x4e1890;
constexpr reg32 kFseek = 0x4e9088, kFread = 0x4e9200, kStricmp = 0x4e9ec0, kMkdir = 0x4eb1d0;
constexpr reg32 kFopen = 0x4edfe8, kFclose = 0x4ee100, kRemove = 0x4ee2e0, kStrrchr = 0x4ee2f0;
constexpr reg32 kStrcmp = 0x4ee310, kChmod = 0x4ee3c0, kRmdir = 0x4ee400, kFtell = 0x4ee420;
constexpr reg32 kQsort = 0x4ee4f8, kFwrite = 0x4eebd0;
constexpr reg32 kOpenViv = 0x43b830, kCloseViv = 0x43b9b0, kFindInViv = 0x43b9d0;
// This file's that tools/game_checks stands in for.
constexpr reg32 kFirstSubfolder = 0x4386b0, kNextSubfolder = 0x4387e0, kFirstFile = 0x438870;
constexpr reg32 kNextFile = 0x438970, kCarFolder = 0x4392b0, kCarId = 0x439520, kCarIsPolice = 0x4396b0;
// And the carmodels' natives' (carRecord, loadCarList).
constexpr reg32 kCarRecord = 0x439a50, kLoadCarList = 0x439d90;

sreg32 s(reg32 value)
{
    return sreg32(value);
}

reg16 word16(App* app, reg32 address)
{
    return app->getMemory<reg16>(address);
}

void putWord16(App* app, reg32 address, reg16 value)
{
    app->getMemory<reg16>(address) = value;
}

void push(App* app, CPU& cpu, reg32 value)
{
    cpu.esp -= 4;
    put(app, cpu.esp, value);
}

reg32 pop(App* app, CPU& cpu)
{
    const reg32 value = at(app, cpu.esp);
    cpu.esp += 4;
    return value;
}

/* The registers pushed in the order given, and popped back into them in the
 * order given. */
void save(App* app, CPU& cpu, std::initializer_list<reg32> values)
{
    for (const reg32 value : values)
        push(app, cpu, value);
}

void restore(App* app, CPU& cpu, std::initializer_list<reg32*> registers)
{
    for (reg32* reg : registers)
        *reg = pop(app, cpu);
}

/* A call as the code makes it: the return address's slot, and esp as the
 * callee leaves it.  False when the game stopped in it. */
bool direct(App* app, CPU& cpu, void (*function)(App*, CPU&))
{
    cpu.esp -= 4;
    function(app, cpu);
    return !cpu.terminate;
}

bool byAddress(App* app, CPU& cpu, reg32 target)
{
    cpu.esp -= 4;
    app->dynamic_call(target, cpu);
    return !cpu.terminate;
}

/* A Windows function, through its import's slot. */
bool windows(App* app, CPU& cpu, reg32 slot)
{
    return byAddress(app, cpu, at(app, slot));
}

/* Two bytes a turn from esi to edi to the string's end: esi, edi and al as
 * the loop leaves them. */
void copyLoop(App* app, CPU& cpu)
{
    for (;;)
    {
        cpu.al = byte(app, cpu.esi);
        putByte(app, cpu.edi, cpu.al);
        if (cpu.al == 0)
            break;
        cpu.al = byte(app, cpu.esi + 1);
        cpu.esi += 2;
        putByte(app, cpu.edi + 1, cpu.al);
        cpu.edi += 2;
        if (cpu.al == 0)
            break;
    }
}

/* repne scasb from edi for al, ecx counting down. */
void scan(App* app, CPU& cpu)
{
    while (cpu.ecx != 0)
    {
        --cpu.ecx;
        const reg8 c = byte(app, cpu.edi);
        ++cpu.edi;
        if (c == cpu.al)
            break;
    }
}

/* push edi; the string at esi copied to edi; pop edi. */
void copyString(App* app, CPU& cpu)
{
    push(app, cpu, cpu.edi);
    copyLoop(app, cpu);
    cpu.edi = pop(app, cpu);
}

/* push edi; sub ecx, ecx; dec ecx; mov al, 0; repne scasb; dec edi; the
 * string at esi copied there; pop edi: strcat as the runtime inlines it. */
void appendString(App* app, CPU& cpu)
{
    push(app, cpu, cpu.edi);
    cpu.ecx = 0xffffffff;
    cpu.al = 0;
    scan(app, cpu);
    --cpu.edi;
    copyLoop(app, cpu);
    cpu.edi = pop(app, cpu);
}

/* sub ecx, ecx; dec ecx; xor eax, eax; repne scasb; not ecx; dec ecx: the
 * length of the string at edi in ecx, edi past its end, eax 0. */
void stringLength(App* app, CPU& cpu)
{
    cpu.ecx = 0xffffffff;
    cpu.eax = 0;
    scan(app, cpu);
    cpu.ecx = ~cpu.ecx;
    --cpu.ecx;
}

/* push edi; mov eax, ecx; shr ecx, 2; rep movsd; mov cl, al; and cl, 3;
 * rep movsb; pop edi: ecx bytes from esi to edi. */
void moveBytes(App* app, CPU& cpu)
{
    push(app, cpu, cpu.edi);
    cpu.eax = cpu.ecx;
    cpu.ecx >>= 2;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.esi += 4;
        cpu.edi += 4;
    }
    cpu.cl = cpu.al;
    cpu.cl &= 3;
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        putByte(app, cpu.edi, byte(app, cpu.esi));
        ++cpu.esi;
        ++cpu.edi;
    }
    cpu.edi = pop(app, cpu);
}

/* movsd, twice: a list's two words (its head, its tail) from esi to edi. */
void moveList(App* app, CPU& cpu)
{
    for (unsigned i = 0; i < 2; ++i)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.esi += 4;
        cpu.edi += 4;
    }
}

/* xor eax, eax; repe cmpsb; je; sbb eax, eax; sbb eax, -1: ecx bytes at esi
 * and edi compared, eax 0 if alike, -1 if esi's first unlike byte is below
 * edi's, else 1. */
void compareBytes(App* app, CPU& cpu)
{
    cpu.eax = 0;
    bool equal = true, below = false;
    while (cpu.ecx != 0)
    {
        --cpu.ecx;
        const reg8 a = byte(app, cpu.esi), b = byte(app, cpu.edi);
        ++cpu.esi;
        ++cpu.edi;
        equal = a == b;
        below = a < b;
        if (!equal)
            break;
    }
    if (!equal)
        cpu.eax = below ? 0xffffffff : 1;
}

}  // namespace

void endWithSlash(App* app, CPU& cpu);
void folderWritable(App* app, CPU& cpu);
void firstFreeHexFolder(App* app, CPU& cpu);
void firstFreePlayerFolder(App* app, CPU& cpu);
void freePlayerCarFolder(App* app, CPU& cpu);
void firstSubfolder(App* app, CPU& cpu);
void nextSubfolder(App* app, CPU& cpu);
void firstFile(App* app, CPU& cpu);
void nextFile(App* app, CPU& cpu);
void removeFolder(App* app, CPU& cpu);
void firstCar(App* app, CPU& cpu);
void nextCar(App* app, CPU& cpu);
void makeCarId(App* app, CPU& cpu);
void firstCarGlobal(App* app, CPU& cpu);
void nextCarGlobal(App* app, CPU& cpu);
void appendCar(App* app, CPU& cpu);
void carCount(App* app, CPU& cpu);
void countCars(App* app, CPU& cpu);
void unlinkCar(App* app, CPU& cpu);
void insertCarByName(App* app, CPU& cpu);
void joinCarLists(App* app, CPU& cpu);
void carListOf(App* app, CPU& cpu);
void takePoliceCars(App* app, CPU& cpu);
void takeClasslessCars(App* app, CPU& cpu);
void takeOrdinaryCars(App* app, CPU& cpu);
void sortCars(App* app, CPU& cpu);
void carName(App* app, CPU& cpu);
void carFolder(App* app, CPU& cpu);
void carFilePrefix(App* app, CPU& cpu);
void carId(App* app, CPU& cpu);
void carFlag40(App* app, CPU& cpu);
void carFlag4(App* app, CPU& cpu);
void carHasNumericId(App* app, CPU& cpu);
void idIsNumeric(App* app, CPU& cpu);
void numericId(App* app, CPU& cpu);
void carIsBonus(App* app, CPU& cpu);
void carIsPolice(App* app, CPU& cpu);
void carIsFerrariOrMercedes(App* app, CPU& cpu);
void carClass(App* app, CPU& cpu);
void findCarById(App* app, CPU& cpu);
void clearCarCache(App* app, CPU& cpu);
void carRecord(App* app, CPU& cpu);
void fecText(App* app, CPU& cpu);
void findCarByName(App* app, CPU& cpu);
void attachFecTexts(App* app, CPU& cpu);
void bonusCarLocked(App* app, CPU& cpu);
void checkDuplicateCars(App* app, CPU& cpu);
void loadCarList(App* app, CPU& cpu);
void carSelectable(App* app, CPU& cpu);
void buildCarClassLists(App* app, CPU& cpu);
void copyCarAsNew(App* app, CPU& cpu);
void loadCarSpecs(App* app, CPU& cpu);
void writeCarFec(App* app, CPU& cpu);
void readCarFecBody(App* app, CPU& cpu);
void readCarFec(App* app, CPU& cpu);
void carFecPath(App* app, CPU& cpu);
void loadCarFec(App* app, CPU& cpu);
void placeCarVivPath(App* app, CPU& cpu);
void swapBytes(App* app, CPU& cpu);
void writeBigEndian(App* app, CPU& cpu);
void appendCarpToViv(App* app, CPU& cpu);
void lastCarLoaded(App* app, CPU& cpu);
void setLastCarId(App* app, CPU& cpu);
void setLastCarName(App* app, CPU& cpu);
void setLastCarFlags(App* app, CPU& cpu);
void markLastCarFlag8(App* app, CPU& cpu);

namespace
{

/* firstFreeHexFolder and firstFreePlayerFolder: the first name made of the
 * counter by `format` into the buffer edx whose folder, under the path eax,
 * cannot be written to (is not there). */
void firstFreeFolder(App* app, CPU& cpu, reg32 format)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x134;
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.ebx = 0;
    put(app, cpu.ebp - 4, cpu.ebx);
    do
    {
        push(app, cpu, cpu.ebx);
        push(app, cpu, format);
        push(app, cpu, cpu.edx);
        if (!byAddress(app, cpu, kSprintf))
            return;
        cpu.esp += 0xc;
        cpu.esi = at(app, cpu.ebp - 8);
        cpu.edi = cpu.ebp - 0x134;
        copyString(app, cpu);
        cpu.eax = cpu.ebp - 0x134;
        cpu.edi = cpu.ebp - 0x134;
        cpu.esi = cpu.edx;
        if (!direct(app, cpu, endWithSlash))
            return;
        appendString(app, cpu);
        cpu.eax = cpu.ebp - 0x134;
        ++cpu.ebx;
        if (!direct(app, cpu, folderWritable))
            return;
        if (cpu.eax == 0)
            put(app, cpu.ebp - 4, 1);
    } while (at(app, cpu.ebp - 4) == 0);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* The walks' FindClose: the handle at `handle` closed, 0 there and in eax. */
bool closeFind(App* app, CPU& cpu, reg32 handle)
{
    cpu.ebx = at(app, handle);
    push(app, cpu, cpu.ebx);
    cpu.esi = 0;
    if (!windows(app, cpu, kFindClose))
        return false;
    put(app, handle, cpu.esi);
    cpu.eax = 0;
    return true;
}

/* The walks' FindNextFileA on the handle at `handle`, into `data`. */
bool findNext(App* app, CPU& cpu, reg32 handle, reg32 data)
{
    push(app, cpu, data);
    cpu.ecx = at(app, handle);
    push(app, cpu, cpu.ecx);
    return windows(app, cpu, kFindNextFileA);
}

/* Whether the folder's name found is neither "." nor "..": strcmp with each. */
bool notDots(App* app, CPU& cpu, bool& stopped)
{
    stopped = true;
    for (const reg32 dots : {kDot, kDotDot})
    {
        cpu.edx = kFolderName;
        cpu.eax = dots;
        if (!byAddress(app, cpu, kStrcmp))
            return false;
        if (cpu.eax == 0)
        {
            stopped = false;
            return false;
        }
    }
    stopped = false;
    return true;
}

/* The search's path, made by firstSubfolder and firstFile in their frame:
 * the path at eax copied, strrchr'd for '\' (its result unused), ended with
 * '\' and "*.*". */
bool searchPath(App* app, CPU& cpu)
{
    cpu.edi = cpu.ebp + 0x7e;
    cpu.esi = cpu.eax;
    cpu.edx = 0x5c;
    copyString(app, cpu);
    cpu.eax = cpu.ebp + 0x7e;
    cpu.esi = kAllFiles;
    if (!byAddress(app, cpu, kStrrchr))
        return false;
    cpu.eax = cpu.ebp + 0x7e;
    cpu.edi = cpu.ebp + 0x7e;
    if (!direct(app, cpu, endWithSlash))
        return false;
    appendString(app, cpu);
    return true;
}

/* The car's file closed as loadCarList has it open: its car.viv (closeViv),
 * or the fedata's own file (fclose). */
bool closeCarFile(App* app, CPU& cpu)
{
    if (cpu.esi != 0)
    {
        cpu.edx = cpu.ebp - 0x18;
        cpu.eax = cpu.esi;
        return byAddress(app, cpu, kCloseViv);
    }
    cpu.eax = at(app, cpu.ebp - 0x18);
    return byAddress(app, cpu, kFclose);
}

/* The flag tests of a car by its place: the record's flags masked. */
void carFlagTest(App* app, CPU& cpu, reg32 mask)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    cpu.eax = at(app, cpu.eax + 0x380);
    cpu.eax &= mask;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* The take-outs' insertion: the car at esi out of the list and into the
 * frame's list by name (insertCarByName with the frame's two words and
 * the car), the list's head in esi again.  `head` and `tail` the registers
 * the code pushes them through. */
bool moveCarOver(App* app, CPU& cpu, reg32& head, reg32& tail)
{
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, unlinkCar))
        return false;
    push(app, cpu, cpu.esi);
    tail = at(app, cpu.ebp - 4);
    push(app, cpu, tail);
    head = at(app, cpu.ebp - 8);
    push(app, cpu, head);
    cpu.esi = cpu.ebp - 8;
    if (!direct(app, cpu, insertCarByName))
        return false;
    cpu.esi = at(app, kCarList);
    return true;
}

/* The take-outs' end: the frame's list to the result at edx, eax it. */
void takeOutEnd(App* app, CPU& cpu)
{
    cpu.esi = cpu.ebp - 8;
    cpu.edi = cpu.edx;
    moveList(app, cpu);
    cpu.eax = cpu.edx;
}

/* sortCars' join: the frame's list at ebp-0x20 joined with the one in the
 * frame at `other`, pushed through `a` to `d` as the code has them. */
bool joinInto(App* app, CPU& cpu, reg32 other, reg32& a, reg32& b, reg32& c, reg32& d)
{
    a = at(app, cpu.ebp - other + 4);
    push(app, cpu, a);
    b = at(app, cpu.ebp - other);
    push(app, cpu, b);
    c = at(app, cpu.ebp - 0x1c);
    push(app, cpu, c);
    d = at(app, cpu.ebp - 0x20);
    push(app, cpu, d);
    cpu.esi = cpu.ebp - 0x20;
    return direct(app, cpu, joinCarLists);
}

/* loadCarList's way to the next folder: the count of cars one less where
 * asked, nextSubfolder. */
bool skipFolder(App* app, CPU& cpu, bool counted)
{
    if (counted)
        put(app, cpu.ebp - 0xc, at(app, cpu.ebp - 0xc) - 1);
    return byAddress(app, cpu, kNextSubfolder);
}

/* loadCarList's car let go: the record and the fedata freed. */
bool freeCar(App* app, CPU& cpu, reg32 first, reg32 second)
{
    cpu.eax = at(app, cpu.ebp - first);
    if (!byAddress(app, cpu, kFree))
        return false;
    cpu.eax = at(app, cpu.ebp - second);
    return byAddress(app, cpu, kFree);
}

/* loadCarList's flag of the record (ebp-4) set where the fedata's (ebp-8)
 * word at `offset` is not 0. */
void flagFromWord(App* app, CPU& cpu, reg32 offset, reg8 flag)
{
    cpu.eax = at(app, cpu.ebp - 8);
    if (word16(app, cpu.eax + offset) != 0)
    {
        cpu.eax = at(app, cpu.ebp - 4);
        putByte(app, cpu.eax + 0x380, byte(app, cpu.eax + 0x380) | flag);
    }
}

/* loadCarList's byte of the fedata at `from` to the record's `to`. */
void byteOver(App* app, CPU& cpu, reg32 from, reg32 to)
{
    cpu.eax = at(app, cpu.ebp - 8);
    cpu.al = byte(app, cpu.eax + from);
    putByte(app, cpu.edx + to, cpu.al);
}

/* loadCarList's test of the .FEC's first text: the record flagged 0x20
 * where it is `name` (stricmp). */
bool flagMaker(App* app, CPU& cpu, reg32 name)
{
    cpu.eax = at(app, cpu.ebp - 4);
    cpu.edx = 0;
    cpu.eax += 4;
    if (!direct(app, cpu, fecText))
        return false;
    cpu.edx = cpu.eax;
    cpu.eax = name;
    if (!byAddress(app, cpu, kStricmp))
        return false;
    if (cpu.eax == 0)
    {
        cpu.eax = at(app, cpu.ebp - 4);
        putByte(app, cpu.eax + 0x380, byte(app, cpu.eax + 0x380) | 0x20);
    }
    return true;
}

/* loadCarList's menu item of the car edx: its text's id, on, white -- off
 * and grey if it is a bonus car still locked (the record at `record`). */
bool menuItem(App* app, CPU& cpu, reg32& index2, reg32 record, reg32 items, reg32 on, reg32 colours, bool viaEbx)
{
    cpu.edi = 1;
    cpu.eax = cpu.edx;
    index2 = cpu.edx + cpu.edx;
    if (viaEbx)
        cpu.ebx = kWhite;
    cpu.eax += kFirstItem;
    putWord16(app, index2 + on, cpu.di);
    cpu.edi = cpu.edx * 4;
    putWord16(app, index2 + items, cpu.ax);
    if (viaEbx)
    {
        cpu.eax = record;
        put(app, cpu.edi + colours, cpu.ebx);
    }
    else
    {
        put(app, cpu.edi + colours, kWhite);
        cpu.eax = record;
    }
    if (!direct(app, cpu, bonusCarLocked))
        return false;
    if (cpu.eax != 0)
    {
        cpu.eax = 0;
        putWord16(app, index2 + on, cpu.ax);
        put(app, cpu.edi + colours, kGrey);
    }
    return true;
}

/* copyCarAsNew's path: the new folder (ebp-0x3ac) and car.viv in the buffer
 * at ebp-0x154. */
bool newVivPath(App* app, CPU& cpu)
{
    cpu.esi = cpu.ebp - 0x3ac;
    cpu.edi = cpu.ebp - 0x154;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x154;
    cpu.esi = kCarViv;
    cpu.edi = cpu.ebp - 0x154;
    if (!direct(app, cpu, endWithSlash))
        return false;
    appendString(app, cpu);
    return true;
}

}  // namespace

/* 0x438340: the path at eax ended with '\' (0x4529a0, which adds one where
 * it has none). */
void endWithSlash(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kAddSlash))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x438350: whether the folder eax can be written to -- its exist.nam made
 * (fopen "wb"), closed and removed: 1, else 0. */
void folderWritable(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x12c;
    cpu.ebp -= 0x1aa;
    cpu.edi = cpu.ebp + 0x7e;
    cpu.esi = cpu.eax;
    cpu.edx = kWriteBinary;
    copyString(app, cpu);
    cpu.eax = cpu.ebp + 0x7e;
    cpu.esi = kExistNam;
    cpu.edi = cpu.ebp + 0x7e;
    if (!direct(app, cpu, endWithSlash))
        return;
    appendString(app, cpu);
    cpu.eax = cpu.ebp + 0x7e;
    if (!byAddress(app, cpu, kFopen))
        return;
    if (cpu.eax != 0)
    {
        if (!byAddress(app, cpu, kFclose))
            return;
        cpu.eax = cpu.ebp + 0x7e;
        if (!byAddress(app, cpu, kRemove))
            return;
        cpu.eax = 1;
    }
    cpu.esp = cpu.ebp + 0x1aa;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x4383f0: the first "%04X" name, into edx, of a folder not there under
 * the path eax (a new car's folder, copyCarAsNew's). */
void firstFreeHexFolder(App* app, CPU& cpu)
{
    firstFreeFolder(app, cpu, kHexFolder);
}

/* 0x4384f0: the first "P%03d" name, into edx, of a folder not there under
 * the path eax. */
void firstFreePlayerFolder(App* app, CPU& cpu)
{
    firstFreeFolder(app, cpu, kPlayerFolder);
}

/* 0x4385a0: the first "P%03d" folder not there in the carmodel folder, its
 * name into eax.  No caller in the game. */
void freePlayerCarFolder(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x12c;
    cpu.edx = cpu.eax;
    cpu.esi = kCarmodelPath;
    cpu.edi = cpu.ebp - 0x12c;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x12c;
    if (!direct(app, cpu, endWithSlash))
        return;
    cpu.eax = cpu.ebp - 0x12c;
    if (!direct(app, cpu, firstFreePlayerFolder))
        return;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx});
    cpu.esp += 4;
}

/* 0x4386b0: the first folder in the folder eax (FindFirstFileA of its
 * "*.*", the handle kept at 0x554f78), "." and ".." passed over: its name
 * (0x5f3aec), or 0 -- the search closed -- where there is none. */
void firstSubfolder(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x12c;
    cpu.ebp -= 0x1aa;
    const auto leave = [&] {
        cpu.esp = cpu.ebp + 0x1aa;
        restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    if (!searchPath(app, cpu))
        return;
    push(app, cpu, kFolderData);
    cpu.eax = cpu.ebp + 0x7e;
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kFindFirstFileA))
        return;
    put(app, kFolderFind, cpu.eax);
    if (cpu.eax == 0xffffffff)
    {
        cpu.edx = 0;
        cpu.eax = 0;
        put(app, kFolderFind, cpu.edx);
        return leave();
    }
    for (;;)
    {
        if (byte(app, kFolderData) & 0x10)
        {
            bool stopped;
            if (notDots(app, cpu, stopped))
            {
                cpu.eax = kFolderName;
                return leave();
            }
            if (stopped)
                return;
        }
        if (!findNext(app, cpu, kFolderFind, kFolderData))
            return;
        cpu.eax = cpu.eax == 0 ? 1 : 0;
        if (cpu.eax != 0)
            break;
    }
    if (!closeFind(app, cpu, kFolderFind))
        return;
    leave();
}

/* 0x4387e0: the next folder of firstSubfolder's search, "." and ".."
 * passed over: its name, or 0 -- the search closed -- at its end. */
void nextSubfolder(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.ebp});
    cpu.ebp = cpu.esp;
    const auto leave = [&] {
        restore(app, cpu, {&cpu.ebp, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    if (at(app, kFolderFind) != 0)
    {
        for (;;)
        {
            if (!findNext(app, cpu, kFolderFind, kFolderData))
                return;
            if (cpu.eax == 0)
            {
                if (!closeFind(app, cpu, kFolderFind))
                    return;
                break;
            }
            if ((byte(app, kFolderData) & 0x10) == 0)
                continue;
            bool stopped;
            if (notDots(app, cpu, stopped))
            {
                cpu.eax = kFolderName;
                return leave();
            }
            if (stopped)
                return;
        }
    }
    cpu.eax = 0;
    leave();
}

/* 0x438870: the first file (not a folder) in the folder eax (the handle
 * kept at 0x554f7c): its name (0x5f39ac), or 0 -- the search closed. */
void firstFile(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x12c;
    cpu.ebp -= 0x1aa;
    const auto leave = [&] {
        cpu.esp = cpu.ebp + 0x1aa;
        restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    if (!searchPath(app, cpu))
        return;
    push(app, cpu, kFileData);
    cpu.eax = cpu.ebp + 0x7e;
    push(app, cpu, cpu.eax);
    if (!windows(app, cpu, kFindFirstFileA))
        return;
    put(app, kFileFind, cpu.eax);
    if (cpu.eax == 0xffffffff)
    {
        cpu.edx = 0;
        cpu.eax = 0;
        put(app, kFileFind, cpu.edx);
        return leave();
    }
    for (;;)
    {
        if ((byte(app, kFileData) & 0x10) == 0)
        {
            cpu.eax = kFileName;
            return leave();
        }
        if (!findNext(app, cpu, kFileFind, kFileData))
            return;
        cpu.eax = cpu.eax == 0 ? 1 : 0;
        if (cpu.eax != 0)
            break;
    }
    if (!closeFind(app, cpu, kFileFind))
        return;
    leave();
}

/* 0x438970: the next file of firstFile's search: its name, or 0 -- the
 * search closed -- at its end. */
void nextFile(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.ebp});
    cpu.ebp = cpu.esp;
    const auto leave = [&] {
        restore(app, cpu, {&cpu.ebp, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    if (at(app, kFileFind) != 0)
    {
        for (;;)
        {
            if (!findNext(app, cpu, kFileFind, kFileData))
                return;
            if (cpu.eax == 0)
            {
                if (!closeFind(app, cpu, kFileFind))
                    return;
                break;
            }
            if ((byte(app, kFileData) & 0x10) == 0)
            {
                cpu.eax = kFileName;
                return leave();
            }
        }
    }
    cpu.eax = 0;
    leave();
}

/* 0x4389d0: the folder eax removed: each file in it made writable (chmod
 * 0x180) and removed, then the folder itself (rmdir; not its folders). */
void removeFolder(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x12c;
    cpu.ebp -= 0x1aa;
    cpu.ebx = cpu.eax;
    if (!byAddress(app, cpu, kFirstFile))
        return;
    for (;;)
    {
        cpu.edx = cpu.eax;
        if (cpu.edx == 0)
            break;
        cpu.edi = cpu.ebp + 0x7e;
        cpu.esi = cpu.ebx;
        copyString(app, cpu);
        cpu.eax = cpu.ebp + 0x7e;
        cpu.edi = cpu.ebp + 0x7e;
        cpu.esi = cpu.edx;
        if (!direct(app, cpu, endWithSlash))
            return;
        appendString(app, cpu);
        cpu.edx = 0x180;
        cpu.eax = cpu.ebp + 0x7e;
        if (!byAddress(app, cpu, kChmod))
            return;
        cpu.eax = cpu.ebp + 0x7e;
        if (!byAddress(app, cpu, kRemove))
            return;
        if (!byAddress(app, cpu, kNextFile))
            return;
    }
    cpu.edx = 0x180;
    cpu.eax = cpu.ebx;
    if (!byAddress(app, cpu, kChmod))
        return;
    cpu.eax = cpu.ebx;
    if (!byAddress(app, cpu, kRmdir))
        return;
    cpu.esp = cpu.ebp + 0x1aa;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x438a80: the list's first car, the cursor at eax set to it; 0 if none. */
void firstCar(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = at(app, kCarList);
    put(app, cpu.eax, cpu.edx);
    cpu.eax = cpu.edx == 0 ? 0 : cpu.edx;
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x438aa0: the car after the cursor at eax, the cursor moved on to it; 0
 * at the end. */
void nextCar(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = at(app, cpu.eax);
    if (cpu.edx == 0)
        cpu.eax = 0;
    else
    {
        cpu.edx = at(app, cpu.edx);
        put(app, cpu.eax, cpu.edx);
        cpu.eax = cpu.edx == 0 ? 0 : cpu.edx;
    }
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x438ad0: a car's id of the number edx into the 16 bytes at eax: zeros,
 * the number first (memset's eax and edx left). */
void makeCarId(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.edx;
    cpu.ebx = 0x10;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kMemset))
        return;
    put(app, cpu.ecx, cpu.esi);
    restore(app, cpu, {&cpu.ebp, &cpu.esi, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x438af0: the list's first car, the list's own cursor (0x5f3ccc) set to
 * it. */
void firstCarGlobal(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = at(app, kCarList);
    cpu.eax = cpu.edx == 0 ? 0 : cpu.edx;
    put(app, kCursor, cpu.edx);
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x438b10: the car after the list's own cursor, the cursor moved on. */
void nextCarGlobal(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = at(app, kCursor);
    if (cpu.edx == 0)
        cpu.eax = 0;
    else
    {
        cpu.edx = at(app, cpu.edx);
        cpu.eax = cpu.edx == 0 ? 0 : cpu.edx;
    }
    put(app, kCursor, cpu.edx);
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x438b90: the record eax put at the list's end. */
void appendCar(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, firstCarGlobal))
        return;
    cpu.ecx = cpu.eax;
    if (cpu.eax == 0)
        put(app, kCarList, cpu.edx);
    else
    {
        cpu.ebx = cpu.eax;
        while (cpu.ecx != 0)
        {
            if (!direct(app, cpu, nextCarGlobal))
                return;
            cpu.ebx = cpu.ecx;
            cpu.ecx = cpu.eax;
        }
        put(app, cpu.ebx, cpu.edx);
        put(app, cpu.edx, cpu.ecx);
    }
    restore(app, cpu, {&cpu.ebp, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x438bd0: the count of cars countCars kept. */
void carCount(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kCount);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x438be0: the cars in the list counted, the count kept (0x5f3cc8). */
void countCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.eax = cpu.ebp - 4;
    if (!direct(app, cpu, firstCar))
        return;
    cpu.edx = 0;
    while (cpu.eax != 0)
    {
        cpu.eax = cpu.ebp - 4;
        if (!direct(app, cpu, nextCar))
            return;
        ++cpu.edx;
    }
    cpu.eax = cpu.edx;
    put(app, kCount, cpu.edx);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x438c10: the record eax taken out of the list, where it is in it. */
void unlinkCar(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.eax = at(app, kCarList);
    if (cpu.eax == cpu.edx)
    {
        cpu.eax = at(app, cpu.edx);
        put(app, kCarList, cpu.eax);
    }
    else
        while (cpu.eax != 0)
        {
            cpu.ecx = at(app, cpu.eax);
            if (cpu.edx == cpu.ecx)
            {
                cpu.edx = at(app, cpu.ecx);
                put(app, cpu.eax, cpu.edx);
                break;
            }
            cpu.eax = cpu.ecx;
        }
    restore(app, cpu, {&cpu.ebp, &cpu.edx, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x438c50: the record (the stack's third word) put into the list of the
 * first two (its head and its tail) before the first car whose name is not
 * below its own (strcmp), else at its end; the list to the pair at esi,
 * eax it.  ret 0xc. */
void insertCarByName(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.ebx = cpu.esi;
    cpu.esi = at(app, cpu.ebp + 0x20);
    put(app, cpu.esi, 0);
    if (at(app, cpu.ebp + 0x18) == 0)
    {
        put(app, cpu.ebp + 0x1c, cpu.esi);
        put(app, cpu.ebp + 0x18, cpu.esi);
    }
    else
    {
        cpu.ecx = cpu.ebp + 0x18;
        for (;;)
        {
            cpu.edi = at(app, cpu.ecx);
            if (cpu.edi == 0)
                break;
            cpu.edx = cpu.edi + 0x10;
            cpu.eax = cpu.esi + 0x10;
            if (!byAddress(app, cpu, kStrcmp))
                return;
            if (s(cpu.eax) < 0)
            {
                cpu.eax = at(app, cpu.ecx);
                put(app, cpu.esi, cpu.eax);
                put(app, cpu.ecx, cpu.esi);
                break;
            }
            cpu.ecx = at(app, cpu.ecx);
            cpu.eax = at(app, cpu.ecx);
            if (cpu.eax != 0)
                continue;
            put(app, cpu.esi, cpu.eax);
            cpu.eax = at(app, cpu.ebp + 0x1c);
            put(app, cpu.eax, cpu.esi);
            put(app, cpu.ebp + 0x1c, cpu.esi);
            break;
        }
    }
    cpu.edi = cpu.ebp - 8;
    cpu.esi = cpu.ebp + 0x18;
    moveList(app, cpu);
    cpu.esi = cpu.ebp - 8;
    cpu.edi = cpu.ebx;
    moveList(app, cpu);
    cpu.eax = cpu.ebx;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4 + 0xc;
}

/* 0x438cc0: two lists (the stack's two pairs of head and tail) joined, the
 * second after the first, to the pair at esi, eax it.  ret 0x10. */
void joinCarLists(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.edx = cpu.esi;
    if (at(app, cpu.ebp + 0x14) == 0)
    {
        cpu.edi = cpu.ebp - 8;
        cpu.esi = cpu.ebp + 0x1c;
    }
    else
    {
        cpu.ebx = at(app, cpu.ebp + 0x1c);
        if (cpu.ebx == 0)
        {
            cpu.edi = cpu.ebp - 8;
            cpu.esi = cpu.ebp + 0x14;
        }
        else
        {
            cpu.esi = at(app, cpu.ebp + 0x18);
            cpu.eax = at(app, cpu.ebp + 0x20);
            cpu.edi = cpu.ebp - 8;
            put(app, cpu.esi, cpu.ebx);
            cpu.esi = cpu.ebp + 0x14;
            put(app, cpu.ebp + 0x18, cpu.eax);
        }
    }
    moveList(app, cpu);
    cpu.esi = cpu.ebp - 8;
    cpu.edi = cpu.edx;
    moveList(app, cpu);
    cpu.eax = cpu.edx;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ebx});
    cpu.esp += 4 + 0x10;
}

/* 0x438d20: the chain from the car eax as a list -- its head, and its last
 * car as its tail -- to the pair at esi, eax it.  A chain of none leaves the
 * tail as the frame had it. */
void carListOf(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.edx = cpu.esi;
    put(app, cpu.ebp - 8, cpu.eax);
    while (cpu.eax != 0)
    {
        cpu.ecx = at(app, cpu.eax);
        if (cpu.ecx == 0)
        {
            put(app, cpu.ebp - 4, cpu.eax);
            break;
        }
        cpu.eax = cpu.ecx;
    }
    takeOutEnd(app, cpu);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x438d60: the police cars (flag 0x10) taken out of the list into one of
 * their own, by name, to the pair at esi. */
void takePoliceCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.edx = cpu.esi;
    cpu.ecx = 0;
    cpu.esi = at(app, kCarList);
    put(app, cpu.ebp - 8, cpu.ecx);
    put(app, cpu.ebp - 4, cpu.ecx);
    while (cpu.esi != 0)
    {
        cpu.bl = byte(app, cpu.esi + 0x380);
        cpu.eax = at(app, cpu.esi);
        if (cpu.bl & 0x10)
        {
            if (!moveCarOver(app, cpu, cpu.edi, cpu.esi))
                return;
        }
        else
            cpu.esi = cpu.eax;
    }
    takeOutEnd(app, cpu);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x438dc0: the cars of no class (0xff) taken out of the list into one of
 * their own, by name, to the pair at esi. */
void takeClasslessCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.edx = cpu.esi;
    cpu.ecx = 0;
    cpu.esi = at(app, kCarList);
    put(app, cpu.ebp - 8, cpu.ecx);
    put(app, cpu.ebp - 4, cpu.ecx);
    while (cpu.esi != 0)
    {
        cpu.edi = at(app, cpu.esi + 0x388);
        cpu.eax = at(app, cpu.esi);
        if (cpu.edi == 0xff)
        {
            if (!moveCarOver(app, cpu, cpu.ecx, cpu.eax))
                return;
        }
        else
            cpu.esi = cpu.eax;
    }
    takeOutEnd(app, cpu);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x438e30: the ordinary cars -- of a class, neither police (0x10) nor of
 * flag 8 -- taken out of the list into one of their own, by name, to the
 * pair at esi. */
void takeOrdinaryCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    cpu.edx = cpu.esi;
    cpu.ecx = 0;
    cpu.esi = at(app, kCarList);
    put(app, cpu.ebp - 8, cpu.ecx);
    put(app, cpu.ebp - 4, cpu.ecx);
    while (cpu.esi != 0)
    {
        cpu.edi = at(app, cpu.esi + 0x388);
        cpu.eax = at(app, cpu.esi);
        if (cpu.edi != 0xff)
        {
            cpu.bl = byte(app, cpu.esi + 0x380);
            if ((cpu.bl & 0x10) == 0 && (cpu.bl & 8) == 0)
            {
                if (!moveCarOver(app, cpu, cpu.ecx, cpu.eax))
                    return;
                continue;
            }
        }
        cpu.esi = cpu.eax;
    }
    takeOutEnd(app, cpu);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x438eb0: the list sorted: the ordinary cars by name, then the police's
 * by name, then those of no class by name, then the rest as they were; the
 * records' cache cleared. */
void sortCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x20;
    if (!direct(app, cpu, clearCarCache))
        return;
    if (at(app, kCarList) != 0)
    {
        cpu.esi = cpu.ebp - 0x20;
        if (!direct(app, cpu, takeOrdinaryCars))
            return;
        cpu.esi = cpu.ebp - 0x10;
        if (!direct(app, cpu, takePoliceCars))
            return;
        if (!joinInto(app, cpu, 0x10, cpu.ecx, cpu.ebx, cpu.esi, cpu.edi))
            return;
        cpu.esi = cpu.ebp - 8;
        if (!direct(app, cpu, takeClasslessCars))
            return;
        if (!joinInto(app, cpu, 8, cpu.eax, cpu.edx, cpu.ecx, cpu.ebx))
            return;
        cpu.esi = cpu.ebp - 0x18;
        cpu.eax = at(app, kCarList);
        if (!direct(app, cpu, carListOf))
            return;
        if (!joinInto(app, cpu, 0x18, cpu.esi, cpu.edi, cpu.eax, cpu.edx))
            return;
        cpu.eax = at(app, cpu.ebp - 0x20);
        put(app, kCarList, cpu.eax);
    }
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x439250: the name of the car eax: the table's for 500 to 599, 0x554f80
 * for 50 to 499, else its record's +0x10 (0x10 where it has none). */
void carName(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (s(cpu.eax) >= 0x1f4 && s(cpu.eax) <= 0x257)
        cpu.eax = at(app, cpu.eax * 4 + kNamesFrom500);
    else if (s(cpu.eax) >= 0x32 && s(cpu.eax) <= 0x1f3)
        cpu.eax = kNoRecordName;
    else
    {
        if (!byAddress(app, cpu, kCarRecord))
            return;
        cpu.eax += 0x10;
    }
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4392b0: the folder's name of the car eax: its record's +0x110, else
 * the tables' for up to 499 and 500 to 599, else 0. */
void carFolder(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    if (cpu.eax != 0)
        cpu.eax += 0x110;
    else
    {
        cpu.eax = cpu.edx * 4;
        if (s(cpu.edx) <= 0x1f3)
            cpu.eax = at(app, cpu.eax + kFoldersTo499);
        else if (s(cpu.edx) <= 0x257)
            cpu.eax = at(app, cpu.eax + kFoldersFrom500);
        else
            cpu.eax = 0;
    }
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x439300: the prefix of the car eax's files: "car" for a record and for
 * 50 to 599, the table's for 600 to 699, else "". */
void carFilePrefix(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    if (cpu.eax != 0 || (s(cpu.edx) >= 0x32 && s(cpu.edx) <= 0x1f3) || (s(cpu.edx) >= 0x1f4 && s(cpu.edx) <= 0x257))
        cpu.edx = kCar;
    else if (s(cpu.edx) >= 0x258 && s(cpu.edx) <= 0x2bb)
        cpu.edx = at(app, cpu.edx * 4 + kPrefixesFrom600);
    else
        cpu.edx = kEmpty;
    cpu.eax = cpu.edx;
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x439520: the id of the car eax (its record's +0x31c). */
void carId(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    cpu.eax += 0x31c;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x439570: the car eax's flag 0x40 (the fedata's word at +0x14). */
void carFlag40(App* app, CPU& cpu)
{
    carFlagTest(app, cpu, 0x40);
}

/* 0x4395c0: the car eax's flag 4 (the fedata's word at +0xe). */
void carFlag4(App* app, CPU& cpu)
{
    carFlagTest(app, cpu, 4);
}

/* 0x439610: whether the car eax's id is one of the game's own (a number). */
void carHasNumericId(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kCarId))
        return;
    if (!direct(app, cpu, idIsNumeric))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x439620: whether the id at eax is a number: its words at +4 and +6 and
 * its dwords at +8 and +0xc 0, its first dword below 50. */
void idIsNumeric(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    bool numeric = false;
    if (word16(app, cpu.eax + 4) == 0 && word16(app, cpu.eax + 6) == 0)
    {
        cpu.edx = cpu.eax + 8;
        if (at(app, cpu.edx) == 0)
        {
            cpu.edx = cpu.eax + 0xc;
            numeric = at(app, cpu.edx) == 0 && at(app, cpu.eax) < 0x32;
        }
    }
    cpu.eax = numeric ? 1 : 0;
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x439660: the number of the id at eax, -1 if it is not one. */
void numericId(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, idIsNumeric))
        return;
    cpu.eax = cpu.eax == 0 ? 0xffffffff : at(app, cpu.edx);
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x439680: whether the car eax is a bonus car (flag 1). */
void carIsBonus(App* app, CPU& cpu)
{
    carFlagTest(app, cpu, 1);
}

/* 0x4396b0: whether the car eax is a police car (flag 0x10). */
void carIsPolice(App* app, CPU& cpu)
{
    carFlagTest(app, cpu, 0x10);
}

/* 0x4396e0: whether the car eax is a Ferrari or a Mercedes (flag 0x20, the
 * .FEC's first text). */
void carIsFerrariOrMercedes(App* app, CPU& cpu)
{
    carFlagTest(app, cpu, 0x20);
}

/* 0x439730: the class of the car eax (its record's +0x388). */
void carClass(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    cpu.eax = at(app, cpu.eax + 0x388);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x439990: the place in the list of the car whose id is the 16 bytes at
 * eax, -1 if none. */
void findCarById(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.ebp - 4;
    if (!direct(app, cpu, firstCar))
        return;
    cpu.ebx = 0;
    for (;;)
    {
        if (cpu.eax == 0)
        {
            cpu.eax = 0xffffffff;
            break;
        }
        cpu.ecx = 0x10;
        cpu.edi = cpu.eax + 0x31c;
        cpu.esi = cpu.edx;
        compareBytes(app, cpu);
        if (cpu.eax == 0)
        {
            cpu.eax = cpu.ebx;
            break;
        }
        cpu.eax = cpu.ebp - 4;
        if (!direct(app, cpu, nextCar))
            return;
        ++cpu.ebx;
    }
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x4399f0: the records' cache (50 at 0x5f3c00) cleared. */
void clearCarCache(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.ebx = 0xc8;
    cpu.eax = kCache;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kMemset))
        return;
    restore(app, cpu, {&cpu.ebp, &cpu.edx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x439a50: the record of the car eax, its place in the list: the cache's,
 * else the list walked and the record (or 0) cached; 0 above 49.  A place
 * below 0 walks the whole list and writes its 0 below the cache (the game's
 * bug). */
void carRecord(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        restore(app, cpu, {&cpu.ebp, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    cpu.edx = cpu.eax;
    cpu.ecx = 0;
    if (s(cpu.eax) > 0x31)
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.eax <<= 2;
    cpu.ebx = at(app, cpu.eax + kCache);
    if (cpu.ebx != 0)
    {
        cpu.eax = cpu.ebx;
        return leave();
    }
    cpu.eax = cpu.ebp - 4;
    if (!direct(app, cpu, firstCar))
        return;
    while (cpu.eax != 0 && cpu.ecx != cpu.edx)
    {
        cpu.eax = cpu.ebp - 4;
        if (!direct(app, cpu, nextCar))
            return;
        ++cpu.ecx;
    }
    put(app, cpu.edx * 4 + kCache, cpu.eax);
    leave();
}

/* 0x439af0: the .FEC's text edx of the texts at eax (a record's +4: their
 * count, a word; the fedata at +4, the offsets at +8): the fedata plus its
 * offset, 0 past the count. */
void fecText(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.ecx = reg32(sreg32(x86::sreg16(word16(app, cpu.eax))));
    --cpu.ecx;
    if (s(cpu.edx) > s(cpu.ecx))
        cpu.eax = 0;
    else
    {
        cpu.ecx = cpu.edx * 4;
        cpu.edx = at(app, cpu.eax + 8);
        cpu.eax = at(app, cpu.eax + 4);
        cpu.eax += at(app, cpu.ecx + cpu.edx);
    }
    restore(app, cpu, {&cpu.ebp, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x439b20: the place in the list of the car named eax (strcmp), -1 if
 * none. */
void findCarByName(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.ebp - 4;
    if (!direct(app, cpu, firstCar))
        return;
    cpu.ebx = 0;
    for (;;)
    {
        cpu.ecx = cpu.eax;
        if (cpu.ecx == 0)
            break;
        cpu.edx = cpu.ecx + 0x10;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kStrcmp))
            return;
        if (cpu.eax == 0)
            break;
        cpu.eax = cpu.ebp - 4;
        if (!direct(app, cpu, nextCar))
            return;
        ++cpu.ebx;
    }
    cpu.eax = cpu.ecx != 0 ? cpu.ebx : 0xffffffff;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x439bd0: the fedata edx's .FEC texts given to the record eax: the
 * fedata to its +8, their count (the fedata's word at +0x2d) to +4, their
 * offsets (+0x2f) to +0xc.  1, edx left at the offsets. */
void attachFecTexts(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    put(app, cpu.eax + 8, cpu.edx);
    cpu.dx = word16(app, cpu.edx + 0x2d);
    putWord16(app, cpu.eax + 4, cpu.dx);
    cpu.edx = at(app, cpu.eax + 8);
    cpu.edx += 0x2f;
    put(app, cpu.eax + 0xc, cpu.edx);
    cpu.eax = 1;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x439c10: whether the record eax is a bonus car still locked: a bonus
 * car (flag 1) of the game's own whose bit of those unlocked (0x6fd2a8) --
 * 0x27 1, 0x12 2, 0x11 4, 0x24 8, 0x31 0x10 -- is not set (all locked while
 * none is; any other number locked). */
void bonusCarLocked(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    const auto leave = [&] {
        restore(app, cpu, {&cpu.ebp, &cpu.edx});
        cpu.esp += 4;
    };
    if ((byte(app, cpu.eax + 0x380) & 1) == 0)
    {
        cpu.eax = 0;
        return leave();
    }
    cpu.edx = cpu.eax + 0x31c;
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, idIsNumeric))
        return;
    if (cpu.eax == 0)
        return leave();
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, numericId))
        return;
    reg8 bit = 0;
    if (at(app, kBonusUnlocked) != 0)
        switch (cpu.eax)
        {
        case 0x11: bit = 4; break;
        case 0x12: bit = 2; break;
        case 0x24: bit = 8; break;
        case 0x27: bit = 1; break;
        case 0x31: bit = 0x10; break;
        default: break;
        }
    cpu.eax = bit != 0 && (byte(app, kBonusUnlocked) & bit) != 0 ? 0 : 1;
    leave();
}

/* 0x439d20: an Error ("Duplicate cars found in carmodel folder!") for each
 * two cars of the same id. */
void checkDuplicateCars(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    if (!direct(app, cpu, carCount))
        return;
    put(app, cpu.ebp - 4, cpu.eax);
    for (cpu.edx = 0; s(cpu.edx) < s(at(app, cpu.ebp - 4)); ++cpu.edx)
    {
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarId))
            return;
        put(app, cpu.ebp - 8, cpu.eax);
        for (cpu.ebx = cpu.edx + 1; s(cpu.ebx) < s(at(app, cpu.ebp - 4)); ++cpu.ebx)
        {
            cpu.ecx = 0x10;
            cpu.eax = cpu.ebx;
            cpu.esi = at(app, cpu.ebp - 8);
            if (!byAddress(app, cpu, kCarId))
                return;
            cpu.edi = cpu.eax;
            compareBytes(app, cpu);
            if (cpu.eax == 0)
            {
                push(app, cpu, kDuplicates);
                if (!byAddress(app, cpu, kError))
                    return;
                cpu.esp += 4;
            }
        }
    }
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x439d90: the cars read in: each folder in the carmodel folder but
 * "traffic" and those already in the list -- its fedata.<language>, or that
 * entry of its car.VIV, read whole; of version 9, and of the ids 15 or 16
 * only where the options (0x55eb2e) ask -- made a record (its flags, class
 * and the rest from the fedata, its texts, name, folder), put at the list's
 * end, its specs and .FEC loaded.  Then the list counted and sorted, the car
 * menus' items and colours made, the classes' lists, the duplicates checked
 * for, the players' settings checked.  0, or -1 where memory or the texts
 * fail. */
void loadCarList(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x278;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    if (!direct(app, cpu, clearCarCache) || !direct(app, cpu, countCars))
        return;
    put(app, cpu.ebp - 0xc, cpu.eax);
    cpu.eax = kCarmodelPath;
    if (!byAddress(app, cpu, kFirstSubfolder))
        return;
    for (;;)
    {
        put(app, cpu.ebp - 0x10, cpu.eax);
        if (at(app, cpu.ebp - 0x10) == 0)
            break;
        cpu.edx = kTraffic;
        cpu.eax = at(app, cpu.ebp - 0x10);
        if (!byAddress(app, cpu, kStricmp))
            return;
        cpu.ecx = 0;
        if (cpu.eax == 0)
        {
            if (!skipFolder(app, cpu, false))
                return;
            continue;
        }
        cpu.eax = cpu.ebp - 0x14;
        if (!direct(app, cpu, firstCar))
            return;
        while (cpu.eax != 0)
        {
            cpu.edx = at(app, cpu.ebp - 0x10);
            cpu.eax += 0x110;
            if (!byAddress(app, cpu, kStrcmp))
                return;
            if (cpu.eax == 0)
            {
                cpu.ecx = 1;
                break;
            }
            cpu.eax = cpu.ebp - 0x14;
            if (!direct(app, cpu, nextCar))
                return;
        }
        if (cpu.ecx != 0)
        {
            if (!skipFolder(app, cpu, false))
                return;
            continue;
        }
        // The folder's path, and its fedata.<language> in it.
        cpu.esi = kCarmodelPath;
        cpu.edi = cpu.ebp - 0x14c;
        cpu.ecx = at(app, cpu.ebp - 0xc);
        copyString(app, cpu);
        cpu.eax = cpu.ebp - 0x14c;
        cpu.esi = at(app, cpu.ebp - 0x10);
        cpu.edi = cpu.ebp - 0x14c;
        ++cpu.ecx;
        if (!direct(app, cpu, endWithSlash))
            return;
        put(app, cpu.ebp - 0xc, cpu.ecx);
        appendString(app, cpu);
        cpu.eax = at(app, kLanguage);
        if (!byAddress(app, cpu, kLanguageNameOf))
            return;
        push(app, cpu, cpu.eax);
        push(app, cpu, kFedataPath);
        cpu.edi = cpu.ebp - 0x14c;
        stringLength(app, cpu);
        cpu.eax = cpu.ebp - 0x14c;
        cpu.eax += cpu.ecx;
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, kSprintf))
            return;
        cpu.esp += 0xc;
        cpu.edx = kReadBinary;
        cpu.eax = cpu.ebp - 0x14c;
        if (!byAddress(app, cpu, kFopen))
            return;
        put(app, cpu.ebp - 0x18, cpu.eax);
        if (cpu.eax != 0)
        {
            cpu.ebx = 2;
            cpu.edx = 0;
            if (!byAddress(app, cpu, kFseek))
                return;
            cpu.eax = at(app, cpu.ebp - 0x18);
            cpu.esi = 0;
            if (!byAddress(app, cpu, kFtell))
                return;
            put(app, cpu.ebp - 0x20, cpu.eax);
            put(app, cpu.ebp - 0x1c, cpu.esi);
        }
        else
        {
            // Not there: the entry of that name in the folder's car.VIV.
            cpu.esi = cpu.ebp - 0x14c;
            cpu.edi = cpu.ebp - 0x278;
            cpu.edx = 0x5c;
            copyString(app, cpu);
            cpu.eax = cpu.ebp - 0x278;
            if (!byAddress(app, cpu, kStrrchr))
                return;
            push(app, cpu, kCarVivUpper);
            ++cpu.eax;
            push(app, cpu, cpu.eax);
            if (!byAddress(app, cpu, kSprintf))
                return;
            cpu.esp += 8;
            cpu.edx = cpu.ebp - 0x18;
            cpu.eax = cpu.ebp - 0x278;
            if (!byAddress(app, cpu, kOpenViv))
                return;
            cpu.edi = cpu.eax;
            cpu.esi = cpu.eax;
            if (cpu.eax == 0)
            {
                put(app, cpu.ebp - 0xc, at(app, cpu.ebp - 0xc) - 1);
                if (!skipFolder(app, cpu, false))
                    return;
                continue;
            }
            cpu.edx = 0x5c;
            cpu.eax = cpu.ebp - 0x14c;
            cpu.ecx = cpu.ebp - 0x20;
            if (!byAddress(app, cpu, kStrrchr))
                return;
            cpu.edx = cpu.eax + 1;
            cpu.ebx = cpu.ebp - 0x1c;
            cpu.eax = cpu.edi;
            if (!byAddress(app, cpu, kFindInViv))
                return;
        }
        if (at(app, cpu.ebp - 0x20) == 0)
        {
            if (!closeCarFile(app, cpu) || !skipFolder(app, cpu, true))
                return;
            continue;
        }
        // The record and the fedata's memory.
        cpu.edx = kRecordBytes;
        cpu.eax = kEmpty;
        cpu.ebx = 0;
        if (!byAddress(app, cpu, kAllocate))
            return;
        cpu.edx = at(app, cpu.ebp - 0x20);
        cpu.ecx = cpu.eax;
        put(app, cpu.ebp - 4, cpu.eax);
        cpu.ebx = 0;
        cpu.eax = kEmpty;
        ++cpu.edx;
        if (!byAddress(app, cpu, kAllocate))
            return;
        cpu.edi = cpu.eax;
        put(app, cpu.ebp - 8, cpu.eax);
        if (cpu.ecx == 0 || cpu.eax == 0)
        {
            if (!closeCarFile(app, cpu))
                return;
            cpu.edx = at(app, cpu.ebp - 4);
            if (cpu.edx != 0)
            {
                cpu.eax = cpu.edx;
                if (!byAddress(app, cpu, kFree))
                    return;
            }
            cpu.ecx = at(app, cpu.ebp - 8);
            if (cpu.ecx != 0)
            {
                cpu.eax = cpu.ecx;
                if (!byAddress(app, cpu, kFree))
                    return;
            }
            cpu.eax = 0xffffffff;
            return leave();
        }
        cpu.ebx = kRecordBytes;
        cpu.eax = cpu.ecx;
        cpu.edx = 0;
        if (!byAddress(app, cpu, kMemset))
            return;
        cpu.edx = at(app, cpu.ebp - 0x1c);
        cpu.eax = at(app, cpu.ebp - 0x18);
        cpu.ebx = 0;
        if (!byAddress(app, cpu, kFseek))
            return;
        cpu.ecx = at(app, cpu.ebp - 0x18);
        cpu.ebx = 1;
        cpu.edx = at(app, cpu.ebp - 0x20);
        cpu.eax = cpu.edi;
        if (!byAddress(app, cpu, kFread))
            return;
        if (!closeCarFile(app, cpu))
            return;
        // Its version: 9.
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.eax = at(app, cpu.eax + 2);
        cpu.edx = at(app, cpu.ebp - 4);
        cpu.eax = reg32(s(cpu.eax) >> 16);
        putByte(app, cpu.edx + 0x38e, cpu.al);
        if (cpu.eax != 9)
        {
            cpu.eax = cpu.edx;
            if (!byAddress(app, cpu, kFree))
                return;
            cpu.eax = at(app, cpu.ebp - 8);
            if (!byAddress(app, cpu, kFree) || !skipFolder(app, cpu, true))
                return;
            continue;
        }
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.bl = byte(app, cpu.edx + 0x384);
        cpu.eax = at(app, cpu.eax + 0xa);
        cpu.bl &= 0xf0;
        cpu.eax = reg32(s(cpu.eax) >> 16);
        putByte(app, cpu.edx + 0x384, cpu.bl);
        cpu.eax &= 0xf;
        cpu.esi = at(app, cpu.edx + 0x384);
        cpu.esi |= cpu.eax;
        cpu.ecx = 0x10;
        put(app, cpu.edx + 0x384, cpu.esi);
        cpu.esi = at(app, cpu.ebp - 8);
        cpu.edi = cpu.edx + 0x31c;
        cpu.esi += 0x18;
        cpu.ebx = 5;
        moveBytes(app, cpu);
        cpu.edi = cpu.edx + 0x315;
        cpu.ecx = 4;
        cpu.eax = cpu.edi;
        cpu.edx = 0;
        cpu.esi = at(app, cpu.ebp - 8);
        if (!byAddress(app, cpu, kMemset))
            return;
        moveBytes(app, cpu);
        flagFromWord(app, cpu, 6, 1);
        flagFromWord(app, cpu, 8, 2);
        flagFromWord(app, cpu, 0xe, 4);
        flagFromWord(app, cpu, 0x10, 0x10);
        flagFromWord(app, cpu, 0x14, 0x40);
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.edx = at(app, cpu.ebp - 4);
        cpu.al = byte(app, cpu.eax + 0x12);
        putByte(app, cpu.edx + 0x3a0, cpu.al);
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.ax = word16(app, cpu.eax + 0x16);
        putWord16(app, cpu.edx + 0x38c, cpu.ax);
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.eax = at(app, cpu.eax + 8);
        cpu.eax = reg32(s(cpu.eax) >> 16);
        put(app, cpu.edx + 0x388, cpu.eax);
        byteOver(app, cpu, 0x28, 0x38f);
        byteOver(app, cpu, 0x29, 0x390);
        byteOver(app, cpu, 0x2a, 0x391);
        byteOver(app, cpu, 0x2b, 0x392);
        cpu.eax = at(app, cpu.ebp - 8);
        cpu.al = byte(app, cpu.eax + 0x2c);
        cpu.bl = byte(app, kOptions);
        putByte(app, cpu.edx + 0x393, cpu.al);
        if ((cpu.bl & 0x20) || (cpu.bl & 0x10))
        {
            cpu.edx = at(app, cpu.ebp - 4);
            cpu.edx += 0x31c;
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, numericId))
                return;
            if (cpu.eax != 0xf)
            {
                cpu.eax = cpu.edx;
                if (!direct(app, cpu, numericId))
                    return;
                if (cpu.eax != 0x10)
                {
                    if (!freeCar(app, cpu, 4, 8) || !skipFolder(app, cpu, true))
                        return;
                    continue;
                }
            }
        }
        // Its texts: the maker's (a Ferrari or a Mercedes), its name.
        cpu.edx = at(app, cpu.ebp - 8);
        cpu.eax = at(app, cpu.ebp - 4);
        if (!direct(app, cpu, attachFecTexts))
            return;
        cpu.ecx = cpu.eax;
        if (!flagMaker(app, cpu, kFerrari) || !flagMaker(app, cpu, kMercedes))
            return;
        if (cpu.ecx == 0)
        {
            if (!freeCar(app, cpu, 8, 4))
                return;
            cpu.eax = 0xffffffff;
            return leave();
        }
        cpu.eax = at(app, cpu.ebp - 4);
        cpu.edx = 2;
        cpu.eax += 4;
        cpu.edi = at(app, cpu.ebp - 4);
        if (!direct(app, cpu, fecText))
            return;
        cpu.edi += 0x10;
        cpu.esi = cpu.eax;
        copyString(app, cpu);
        cpu.edi = at(app, cpu.ebp - 4);
        cpu.esi = at(app, cpu.ebp - 0x10);
        cpu.edi += 0x110;
        copyString(app, cpu);
        cpu.edi = at(app, cpu.ebp - 4);
        cpu.esi = at(app, cpu.ebp - 0x10);
        cpu.edi += 0x210;
        cpu.ebx = 4;
        copyString(app, cpu);
        cpu.eax = at(app, cpu.ebp - 4);
        cpu.edx = kCar;
        cpu.eax += 0x310;
        if (!byAddress(app, cpu, kStrncpy))
            return;
        // As the game's strncpy leaves them, its count run down (native
        // watcom::strncpy keeps its arguments; the code after reads ebx).
        cpu.edx = 0;
        cpu.ebx = 0;
        cpu.eax = at(app, cpu.ebp - 4);
        cpu.edx = at(app, cpu.ebp - 0xc);
        put(app, cpu.eax, 0);
        if (!direct(app, cpu, appendCar))
            return;
        cpu.eax = at(app, cpu.ebp - 4);
        --cpu.edx;
        put(app, kLastCar, cpu.eax);
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, loadCarSpecs))
            return;
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, loadCarFec))
            return;
        if (!skipFolder(app, cpu, false))
            return;
    }
    // The list counted and sorted; the menus' items.
    if (!direct(app, cpu, countCars) || !direct(app, cpu, sortCars))
        return;
    cpu.eax = 0xc1;
    cpu.edx = 0xbe;
    cpu.ebx = 0xbf;
    cpu.ecx = 0xc0;
    putWord16(app, kMenuHeads, cpu.ax);
    putWord16(app, kMenuHeads + 2, cpu.dx);
    putWord16(app, kMenuHeads + 4, cpu.bx);
    cpu.eax = kWhite;
    putWord16(app, kMenuHeads + 6, cpu.cx);
    put(app, kMenuColoursHead, cpu.eax);
    cpu.edx = cpu.eax;
    put(app, kMenuColoursHead + 4, cpu.eax);
    put(app, kMenuColoursHead + 8, cpu.eax);
    put(app, kMenuColoursHead + 0xc, cpu.eax);
    cpu.edx ^= cpu.eax;
    for (;;)
    {
        if (!direct(app, cpu, carCount))
            return;
        if (s(cpu.edx) >= s(cpu.eax))
            break;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarRecord))
            return;
        cpu.esi = cpu.eax;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarIsPolice))
            return;
        if (cpu.eax != 0)
            break;
        if (!menuItem(app, cpu, cpu.ecx, cpu.esi, kCarItems, kCarItemOn, kCarColours, false))
            return;
        ++cpu.edx;
    }
    cpu.ebx = 0;
    putWord16(app, cpu.edx * 2 + kCarItems, cpu.bx);
    cpu.edx = 0;
    for (;;)
    {
        if (!direct(app, cpu, carCount))
            return;
        if (s(cpu.edx) >= s(cpu.eax))
            break;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarRecord))
            return;
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarId) || !direct(app, cpu, numericId))
            return;
        if (cpu.eax == 0x21)
        {
            put(app, kCar21, cpu.edx);
            break;
        }
        if (!menuItem(app, cpu, cpu.esi, cpu.ecx, kAllItems, kAllItemOn, kAllColours, true))
            return;
        ++cpu.edx;
    }
    cpu.ebx = 0;
    putWord16(app, cpu.edx * 2 + kAllItems, cpu.bx);
    if (!direct(app, cpu, buildCarClassLists) || !direct(app, cpu, checkDuplicateCars))
        return;
    cpu.eax = 0;
    if (!byAddress(app, cpu, kPlayerSettings))
        return;
    cpu.eax = 1;
    if (!byAddress(app, cpu, kPlayerSettings))
        return;
    cpu.eax = 0;
    leave();
}

/* 0x43a4f0: whether the car eax can be chosen: not a Ferrari or Mercedes
 * in mode 3, not a police car; a car of flag 0x40 of the game's own, not
 * flag 4 nor a bonus car, can; else only the player's own car (and with
 * [0x6fd3b0] 1 the second's). */
void carSelectable(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    const auto leave = [&](reg32 result) {
        cpu.eax = result;
        restore(app, cpu, {&cpu.ebp, &cpu.edx});
        cpu.esp += 4;
    };
    cpu.edx = cpu.eax;
    if (at(app, kGameMode) == 3)
    {
        if (!direct(app, cpu, carIsFerrariOrMercedes))
            return;
        if (cpu.eax != 0)
            return leave(0);
    }
    cpu.eax = cpu.edx;
    if (!byAddress(app, cpu, kCarIsPolice))
        return;
    if (cpu.eax != 0)
        return leave(0);
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, carFlag4))
        return;
    if (cpu.eax == 0)
    {
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, carHasNumericId))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = cpu.edx;
            if (!direct(app, cpu, carIsBonus))
                return;
            if (cpu.eax == 0)
            {
                cpu.eax = cpu.edx;
                if (!direct(app, cpu, carFlag40))
                    return;
                if (cpu.eax != 0)
                    return leave(1);
            }
        }
    }
    cpu.eax = at(app, kPlayersKind);
    if (cpu.eax == 0)
        return leave(cpu.edx == at(app, kPlayerCar) ? 1 : 0);
    if (cpu.eax == 1)
        return leave(cpu.edx == at(app, kPlayerCar) || cpu.edx == at(app, kSecondCar) ? 1 : 0);
    leave(0);
}

/* 0x43a580: the classes' lists: of the cars that can be chosen (the count
 * less [0x554f50]), each in list 0 and in its class's (class + 1), 0xc8
 * bytes each at 0x5552d8, their counts at 0x5555f8; lists 0 to 3 sorted by
 * name (qsort with 0x43a4d0).  The count of list 0. */
void buildCarClassLists(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 8;
    if (!direct(app, cpu, carCount))
        return;
    cpu.eax -= at(app, kNotListed);
    cpu.edx = 0x320;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.eax = kClassLists;
    if (!byAddress(app, cpu, kFillZero))
        return;
    cpu.edx = 0x10;
    cpu.eax = kClassCounts;
    if (!byAddress(app, cpu, kFillZero))
        return;
    for (cpu.edx = 0; s(cpu.edx) < s(at(app, cpu.ebp - 4)); ++cpu.edx)
    {
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, carSelectable))
            return;
        if (cpu.eax == 0)
            continue;
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, carClass))
            return;
        cpu.ecx = cpu.eax + 1;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarRecord))
            return;
        cpu.ebx = at(app, cpu.ecx * 4 + kClassCounts);
        cpu.edi = cpu.eax;
        cpu.eax = cpu.ebx * 4;
        put(app, cpu.ebp - 8, cpu.eax);
        cpu.eax = cpu.ecx * 4;
        cpu.eax -= cpu.ecx;
        ++cpu.ebx;
        cpu.eax <<= 3;
        put(app, cpu.ecx * 4 + kClassCounts, cpu.ebx);
        cpu.eax += cpu.ecx;
        cpu.ebx = at(app, cpu.ebp - 8);
        cpu.eax <<= 3;
        cpu.eax += cpu.ebx;
        put(app, cpu.eax + kClassLists, cpu.edi);
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarRecord))
            return;
        cpu.ecx = cpu.eax;
        cpu.eax = at(app, kClassCounts);
        ++cpu.eax;
        put(app, cpu.eax * 4 + kClassLists - 4, cpu.ecx);
        put(app, kClassCounts, cpu.eax);
    }
    for (reg32 list = 0; list < 4; ++list)
    {
        cpu.ecx = kClassCompare;
        cpu.ebx = 4;
        cpu.eax = kClassLists + 0xc8 * list;
        cpu.edx = at(app, kClassCounts + 4 * list);
        if (!byAddress(app, cpu, kQsort))
            return;
    }
    cpu.eax = at(app, kClassCounts);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43ae60: a copy of the car edx as a new car named eax: a new folder
 * ("%04X") in the carmodel folder, the car's car.viv copied into it, its
 * fedata.<language> entries (each language's, the language's counter
 * clobbered by the id's loop -- the game's bug) given the name and a new id
 * (CoCreateGuid), the .viv written back; the list loaded again and the new
 * car's record given back -- the folder removed and 0 where it fails.  No
 * caller in the game. */
void copyCarAsNew(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x604;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    const auto fail = [&] {
        cpu.eax = cpu.ebp - 0x3ac;
        if (!direct(app, cpu, removeFolder))
            return;
        cpu.eax = 0;
        leave();
    };
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.ebx = cpu.edx;
    cpu.esi = kCarmodelPath;
    cpu.edi = cpu.ebp - 0x604;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x604;
    cpu.esi = cpu.ebp - 0x604;
    cpu.edi = cpu.ebp - 0x3ac;
    if (!direct(app, cpu, endWithSlash))
        return;
    copyString(app, cpu);
    cpu.edi = cpu.ebp - 0x3ac;
    stringLength(app, cpu);
    cpu.eax = cpu.ebp - 0x3ac;
    cpu.edx = cpu.ecx + cpu.eax;
    cpu.eax = cpu.ebp - 0x604;
    if (!direct(app, cpu, firstFreeHexFolder))
        return;
    cpu.eax = cpu.ebp - 0x3ac;
    if (!byAddress(app, cpu, kMkdir))
        return;
    if (cpu.eax != 0)
    {
        cpu.eax = 0;
        return leave();
    }
    // The car's car.viv copied into the new folder.
    cpu.esi = cpu.ebp - 0x604;
    cpu.edi = cpu.ebp - 0x4d8;
    copyString(app, cpu);
    cpu.eax = cpu.ebx;
    cpu.edi = cpu.ebp - 0x4d8;
    if (!byAddress(app, cpu, kCarFolder))
        return;
    cpu.esi = cpu.eax;
    appendString(app, cpu);
    cpu.esi = cpu.ebp - 0x4d8;
    cpu.edi = cpu.ebp - 0x280;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x280;
    cpu.esi = kCarViv;
    cpu.edi = cpu.ebp - 0x280;
    if (!direct(app, cpu, endWithSlash))
        return;
    appendString(app, cpu);
    cpu.edx = cpu.ebp - 0x280;
    if (!newVivPath(app, cpu))
        return;
    cpu.eax = cpu.ebp - 0x154;
    cpu.esi = cpu.ebp - 0x3ac;
    cpu.edi = cpu.ebp - 0x154;
    if (!byAddress(app, cpu, kCopyFile))
        return;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x154;
    cpu.esi = kCarViv;
    cpu.edi = cpu.ebp - 0x154;
    if (!direct(app, cpu, endWithSlash))
        return;
    appendString(app, cpu);
    cpu.edx = 0x10;
    cpu.eax = cpu.ebp - 0x154;
    if (!byAddress(app, cpu, kLoadFileQuietly))
        return;
    cpu.edx = cpu.eax;
    if (cpu.eax != 0)
    {
        if (!byAddress(app, cpu, kVivParse))
            return;
        put(app, cpu.ebp - 0xc, cpu.eax);
    }
    cpu.eax = cpu.edx;
    cpu.edx = at(app, cpu.ebp - 0xc);
    if (!byAddress(app, cpu, kFree))
        return;
    // Each language's fedata entry: the name added, a new id.
    cpu.esi = 0;
    for (;;)
    {
        do
        {
            if (!byAddress(app, cpu, kLanguageName))
                return;
            push(app, cpu, cpu.eax);
            push(app, cpu, kFedataName);
            cpu.eax = cpu.ebp - 0x154;
            push(app, cpu, cpu.eax);
            if (!byAddress(app, cpu, kSprintf))
                return;
            cpu.esp += 0xc;
            cpu.edx = cpu.ebp - 0x154;
            cpu.eax = at(app, cpu.ebp - 0xc);
            if (!byAddress(app, cpu, kVivEntry))
                return;
            put(app, cpu.ebp - 4, cpu.eax);
            put(app, cpu.ebp - 0x14, cpu.eax);
            if (cpu.eax == 0)
                break;
            cpu.edi = at(app, cpu.ebp - 8);
            cpu.edx = at(app, cpu.ebp - 4);
            stringLength(app, cpu);
            cpu.edx = at(app, cpu.edx + 0x20);
            cpu.ebx = 0;
            cpu.edx += cpu.ecx;
            cpu.eax = kEmpty;
            ++cpu.edx;
            if (!byAddress(app, cpu, kAllocate))
                return;
            cpu.edx = cpu.eax;
            if (cpu.eax == 0)
                break;
            cpu.eax = at(app, cpu.ebp - 4);
            cpu.edi = cpu.edx;
            cpu.ecx = at(app, cpu.eax + 0x20);
            cpu.esi = at(app, cpu.eax + 0x24);
            moveBytes(app, cpu);
            cpu.edi = at(app, cpu.ebp - 8);
            stringLength(app, cpu);
            cpu.eax = at(app, cpu.ebp - 4);
            cpu.esi = at(app, cpu.ebp - 8);
            cpu.edi = at(app, cpu.eax + 0x20);
            ++cpu.ecx;
            cpu.edi += cpu.edx;
            moveBytes(app, cpu);
            cpu.eax = at(app, cpu.ebp - 4);
            cpu.eax = at(app, cpu.eax + 0x20);
            put(app, cpu.edx + 0x37, cpu.eax);
            cpu.eax = at(app, cpu.ebp - 4);
            cpu.eax = at(app, cpu.eax + 0x24);
            if (!byAddress(app, cpu, kFree))
                return;
            cpu.eax = at(app, cpu.ebp - 4);
            cpu.edi = at(app, cpu.ebp - 8);
            put(app, cpu.eax + 0x24, cpu.edx);
            cpu.edx = at(app, cpu.ebp - 4);
            stringLength(app, cpu);
            cpu.eax = cpu.ecx + 1;
            cpu.ebx = at(app, cpu.edx + 0x20);
            cpu.ebx += cpu.eax;
            cpu.eax = cpu.ebp - 0x28;
            push(app, cpu, cpu.eax);
            put(app, cpu.edx + 0x20, cpu.ebx);
            if (!windows(app, cpu, kCoCreateGuid))
                return;
            if (cpu.eax != 0)
                return fail();
            cpu.esi = 0;
            do
            {
                cpu.edx = at(app, cpu.ebp - 0x14);
                cpu.eax = cpu.esi * 4;
                cpu.edx = at(app, cpu.edx + 0x24);
                cpu.edx += cpu.eax;
                cpu.eax = at(app, cpu.eax + cpu.ebp - 0x28);
                ++cpu.esi;
                put(app, cpu.edx + 0x18, cpu.eax);
            } while (cpu.esi < 4);
        } while (false);
        ++cpu.esi;
        if (s(cpu.esi) >= 7)
            break;
    }
    // The .viv written back over the copy, the list loaded again.
    if (!newVivPath(app, cpu))
        return;
    cpu.eax = cpu.ebp - 0x154;
    cpu.edx = cpu.ebp - 0x18;
    if (!byAddress(app, cpu, kRemove))
        return;
    cpu.eax = at(app, cpu.ebp - 0xc);
    if (!byAddress(app, cpu, kVivSave))
        return;
    cpu.edx = cpu.eax;
    cpu.ecx = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.esi = at(app, cpu.ebp - 0x18);
        if (cpu.esi != 0)
        {
            cpu.eax = cpu.ebp - 0x154;
            cpu.ebx = cpu.esi;
            if (!byAddress(app, cpu, kWriteWhole))
                return;
            put(app, cpu.ebp - 0x10, cpu.eax);
        }
    }
    cpu.eax = cpu.ecx;
    cpu.edi = at(app, cpu.ebp - 0x10);
    if (!byAddress(app, cpu, kFree) || !byAddress(app, cpu, kLoadCarList))
        return;
    if (cpu.eax != 0)
        return fail();
    cpu.eax = at(app, cpu.ebp - 8);
    if (!direct(app, cpu, findCarByName))
        return;
    cpu.edx = cpu.eax;
    cpu.eax = cpu.edx;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    leave();
}

/* 0x43b3f0: the car eax's specs (0x49c700, of its folder's files of its
 * prefix) into its record's +0x338 and +0x394, the word it gives to +0x334.
 * 0. */
void loadCarSpecs(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x134;
    cpu.edx = cpu.eax;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    cpu.esi = kCarmodelPath;
    cpu.edi = cpu.ebp - 0x134;
    put(app, cpu.ebp - 4, cpu.eax);
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x134;
    if (!direct(app, cpu, endWithSlash))
        return;
    cpu.eax = cpu.edx;
    cpu.edi = cpu.ebp - 0x134;
    if (!byAddress(app, cpu, kCarFolder))
        return;
    cpu.esi = cpu.eax;
    appendString(app, cpu);
    cpu.eax = cpu.ebp - 0x134;
    if (!direct(app, cpu, endWithSlash))
        return;
    cpu.eax = cpu.edx;
    cpu.edi = cpu.ebp - 0x134;
    if (!direct(app, cpu, carFilePrefix))
        return;
    cpu.esi = cpu.eax;
    cpu.ebx = 0x10;
    appendString(app, cpu);
    cpu.eax = at(app, cpu.ebp - 4);
    cpu.edx = at(app, cpu.ebp - 4);
    cpu.eax += 0x394;
    cpu.ecx = cpu.ebp - 8;
    push(app, cpu, cpu.eax);
    cpu.edx += 0x338;
    cpu.eax = cpu.ebp - 0x134;
    if (!byAddress(app, cpu, kLoadSpecs))
        return;
    cpu.edx = at(app, cpu.ebp - 4);
    cpu.eax = at(app, cpu.ebp - 8);
    put(app, cpu.edx + 0x334, cpu.eax);
    cpu.eax = 0;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43b4f0: the record edx's .FEC written to the file eax: 1, then its
 * quads at +0x32c and +0x378.  0, or 1 if it cannot be made. */
void writeCarFec(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.edi = cpu.edx;
    put(app, cpu.ebp - 4, 1);
    cpu.edx = kWriteBinary;
    if (!byAddress(app, cpu, kFopen))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax == 0)
        cpu.edx = 1;
    else
    {
        cpu.ebx = 1;
        cpu.edx = 4;
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.ebp - 4;
        if (!byAddress(app, cpu, kFwrite))
            return;
        for (const reg32 quad : {0x32cu, 0x378u})
        {
            cpu.ebx = 1;
            cpu.edx = 8;
            cpu.eax = cpu.edi + quad;
            cpu.ecx = cpu.esi;
            if (!byAddress(app, cpu, kFwrite))
                return;
        }
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kFclose))
            return;
        cpu.edx = 0;
    }
    cpu.eax = cpu.edx;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43b570: the .FEC open at eax read into the record edx: from its start,
 * a word, then its two quads (the first's words to +0x32c and +0x330, the
 * second's to +0x378 and +0x37c).  0, or 1 if the first word is not read. */
void readCarFecBody(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x18;
    const auto leave = [&] {
        cpu.esp = cpu.ebp;
        restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
        cpu.esp += 4;
    };
    cpu.esi = cpu.eax;
    put(app, cpu.ebp - 4, cpu.edx);
    cpu.ebx = 0;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.ecx = cpu.esi;
    cpu.ebx = 1;
    cpu.edx = 4;
    cpu.eax = cpu.ebp - 8;
    if (!byAddress(app, cpu, kFread))
        return;
    if (cpu.eax != 1)
    {
        cpu.eax = 1;
        return leave();
    }
    cpu.edx = 8;
    cpu.ecx = cpu.esi;
    cpu.ebx = cpu.eax;
    cpu.eax = cpu.ebp - 0x18;
    if (!byAddress(app, cpu, kFread))
        return;
    cpu.ebx = 1;
    cpu.edx = 8;
    cpu.eax = cpu.ebp - 0x10;
    cpu.ecx = cpu.esi;
    if (!byAddress(app, cpu, kFread))
        return;
    cpu.edx = at(app, cpu.ebp - 4);
    cpu.eax = at(app, cpu.ebp - 0x18);
    cpu.ecx = 4;
    put(app, cpu.edx + 0x32c, cpu.eax);
    cpu.esi = cpu.ebp - 0x10;
    cpu.eax = at(app, cpu.ebp - 0x14);
    cpu.edi = cpu.edx + 0x378;
    put(app, cpu.edx + 0x330, cpu.eax);
    moveBytes(app, cpu);
    cpu.ecx = 4;
    cpu.esi = cpu.ebp - 0xc;
    cpu.edi = cpu.edx + 0x37c;
    moveBytes(app, cpu);
    cpu.eax = 0;
    leave();
}

/* 0x43b630: the .FEC open at eax read into the record edx where its first
 * word is 1 (readCarFecBody): 0, else -1. */
void readCarFec(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    cpu.ebx = 0;
    cpu.edx = 0;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.ecx = cpu.esi;
    cpu.ebx = 1;
    cpu.edx = 4;
    cpu.eax = cpu.ebp - 4;
    if (!byAddress(app, cpu, kFread))
        return;
    bool read = false;
    if (at(app, cpu.ebp - 4) == 1)
    {
        cpu.edx = cpu.edi;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, readCarFecBody))
            return;
        read = cpu.eax == 0;
    }
    if (!read)
        cpu.eax = 0xffffffff;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43b680: the path of the car eax's .FEC into the buffer edx: the
 * carmodel folder, its folder, its prefix and ".FEC". */
void carFecPath(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.ebx = cpu.eax;
    cpu.esi = kCarmodelPath;
    cpu.edi = cpu.edx;
    copyString(app, cpu);
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, endWithSlash))
        return;
    cpu.eax = cpu.ebx;
    if (!byAddress(app, cpu, kCarFolder))
        return;
    cpu.esi = cpu.eax;
    appendString(app, cpu);
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, endWithSlash))
        return;
    cpu.eax = cpu.ebx;
    if (!direct(app, cpu, carFilePrefix))
        return;
    cpu.esi = cpu.eax;
    appendString(app, cpu);
    cpu.esi = kFec;
    appendString(app, cpu);
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43b740: the car eax's .FEC read into its record (readCarFec) where it
 * is there, made anew (writeCarFec) where its first word is not 1.  0, or
 * -1 where it fails. */
void loadCarFec(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x130;
    cpu.ecx = cpu.eax;
    if (!byAddress(app, cpu, kCarRecord))
        return;
    cpu.edx = cpu.ebp - 0x130;
    cpu.edi = cpu.eax;
    cpu.eax = cpu.ecx;
    if (!direct(app, cpu, carFecPath))
        return;
    cpu.edx = kReadBinary;
    cpu.eax = cpu.ebp - 0x130;
    if (!byAddress(app, cpu, kFopen))
        return;
    cpu.esi = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.ebx = 1;
        cpu.edx = 4;
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.ebp - 4;
        if (!byAddress(app, cpu, kFread))
            return;
        cpu.edx = at(app, cpu.ebp - 4);
        cpu.ebx = cpu.edx != 1 ? 1 : 0;
        cpu.edx = cpu.edi;
        cpu.eax = cpu.esi;
        if (!direct(app, cpu, readCarFec))
            return;
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, kFclose))
            return;
        if (cpu.ecx != 0)
            cpu.eax = 0xffffffff;
        else
        {
            bool failed = false;
            if (cpu.ebx != 0)
            {
                cpu.eax = cpu.ebp - 0x130;
                cpu.edx = cpu.edi;
                if (!direct(app, cpu, writeCarFec))
                    return;
                failed = cpu.eax != 0;
            }
            cpu.eax = failed ? 0xffffffff : 0;
        }
    }
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43ba20: the placeholder car's car.viv (".\fedata\plac\car.viv"). */
void placeCarVivPath(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = kPlaceViv;
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x43ba30: the dword at eax byte-swapped in place (through the frame),
 * eax it. */
void swapBytes(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.edx = cpu.eax;
    cpu.ecx = cpu.eax;
    cpu.eax = 0;
    do
    {
        cpu.esi = 3;
        cpu.ebx = cpu.ecx + cpu.eax;
        cpu.esi -= cpu.eax;
        cpu.bl = byte(app, cpu.ebx);
        ++cpu.eax;
        putByte(app, cpu.esi + cpu.ebp - 4, cpu.bl);
    } while (s(cpu.eax) < 4);
    cpu.eax = at(app, cpu.ebp - 4);
    put(app, cpu.edx, cpu.eax);
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43ba70: the dword edx written big-endian to the file eax (fwrite's
 * result). */
void writeBigEndian(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 4;
    cpu.ecx = cpu.eax;
    put(app, cpu.ebp - 4, cpu.edx);
    cpu.eax = cpu.ebp - 4;
    cpu.ebx = 1;
    cpu.edx = 4;
    if (!direct(app, cpu, swapBytes))
        return;
    cpu.eax = cpu.ebp - 4;
    if (!byAddress(app, cpu, kFwrite))
        return;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43baa0: the carp.txt beside the .viv eax appended to it, 0x200 bytes a
 * time, and its first entry (+0x10, +0x14) pointed at it: where it starts
 * (the .viv's old length) and how long it is, big-endian. */
void appendCarpToViv(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ebx, cpu.ecx, cpu.edx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esp -= 0x30c;
    cpu.ecx = cpu.eax;
    cpu.edi = cpu.ebp - 0x10c;
    cpu.esi = cpu.eax;
    cpu.edx = 0x5c;
    copyString(app, cpu);
    cpu.eax = cpu.ebp - 0x10c;
    cpu.esi = kCarpTxt;
    if (!byAddress(app, cpu, kStrrchr))
        return;
    cpu.edi = cpu.eax + 1;
    cpu.edx = kReadUpdate;
    copyString(app, cpu);
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFopen))
        return;
    cpu.edx = kReadBinary;
    cpu.edi = cpu.eax;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.ebp - 0x10c;
    cpu.ebx = 2;
    if (!byAddress(app, cpu, kFopen))
        return;
    cpu.ecx = cpu.eax;
    put(app, cpu.ebp - 4, cpu.eax);
    cpu.edx = 0;
    cpu.eax = cpu.edi;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.eax = cpu.edi;
    cpu.ebx = 2;
    if (!byAddress(app, cpu, kFtell))
        return;
    cpu.edx = 0;
    put(app, cpu.ebp - 8, cpu.eax);
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFtell))
        return;
    cpu.ebx = 0;
    cpu.edx = cpu.eax;
    put(app, cpu.ebp - 0xc, cpu.eax);
    cpu.edx ^= cpu.eax;
    cpu.eax = cpu.ecx;
    if (!byAddress(app, cpu, kFseek))
        return;
    do
    {
        cpu.ecx = at(app, cpu.ebp - 4);
        cpu.ebx = 0x200;
        cpu.edx = 1;
        cpu.eax = cpu.ebp - 0x30c;
        if (!byAddress(app, cpu, kFread))
            return;
        cpu.edi = cpu.eax;
        if (cpu.eax == 0)
            break;
        cpu.edx = 1;
        cpu.ecx = cpu.esi;
        cpu.ebx = cpu.eax;
        cpu.eax = cpu.ebp - 0x30c;
        if (!byAddress(app, cpu, kFwrite))
            return;
    } while (cpu.edi == 0x200);
    cpu.eax = at(app, cpu.ebp - 4);
    cpu.edx = 0x10;
    if (!byAddress(app, cpu, kFclose))
        return;
    cpu.ebx = 0;
    cpu.eax = cpu.esi;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.edx = at(app, cpu.ebp - 8);
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, writeBigEndian))
        return;
    cpu.ebx = 0;
    cpu.edx = 0x14;
    cpu.eax = cpu.esi;
    if (!byAddress(app, cpu, kFseek))
        return;
    cpu.edx = at(app, cpu.ebp - 0xc);
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, writeBigEndian))
        return;
    cpu.eax = cpu.esi;
    if (!byAddress(app, cpu, kFclose))
        return;
    cpu.esp = cpu.ebp;
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.edx, &cpu.ecx, &cpu.ebx});
    cpu.esp += 4;
}

/* 0x43bbf0: the record of the last car loaded (0x554f74). */
void lastCarLoaded(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, kLastCar);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x43bc00: the 16 bytes at eax made the last car loaded's id. */
void setLastCarId(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.ecx, cpu.esi, cpu.edi, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.esi = cpu.eax;
    if (!direct(app, cpu, lastCarLoaded))
        return;
    if (cpu.eax != 0)
    {
        cpu.ecx = 0x10;
        cpu.edi = cpu.eax + 0x31c;
        moveBytes(app, cpu);
    }
    restore(app, cpu, {&cpu.ebp, &cpu.edi, &cpu.esi, &cpu.ecx});
    cpu.esp += 4;
}

/* 0x43bc40: the last car loaded's name printed with eax as the format (and
 * 0x100 its argument). */
void setLastCarName(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, lastCarLoaded))
        return;
    if (cpu.eax != 0)
    {
        push(app, cpu, 0x100);
        push(app, cpu, cpu.edx);
        cpu.eax += 0x10;
        push(app, cpu, cpu.eax);
        if (!byAddress(app, cpu, kSprintf))
            return;
        cpu.esp += 0xc;
    }
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x43bc70: eax made the last car loaded's flags. */
void setLastCarFlags(App* app, CPU& cpu)
{
    save(app, cpu, {cpu.edx, cpu.ebp});
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, lastCarLoaded))
        return;
    if (cpu.eax != 0)
        put(app, cpu.eax + 0x380, cpu.edx);
    restore(app, cpu, {&cpu.ebp, &cpu.edx});
    cpu.esp += 4;
}

/* 0x43bc90: the last car loaded given flag 8 (put after the others by
 * sortCars). */
void markLastCarFlag8(App* app, CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (!direct(app, cpu, lastCarLoaded))
        return;
    if (cpu.eax != 0)
        putByte(app, cpu.eax + 0x380, byte(app, cpu.eax + 0x380) | 8);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace load
}  // namespace nfs3hp
