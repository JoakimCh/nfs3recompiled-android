// game_checks.cpp's parts for the menu files, rewritten (src/nfs3hp/port_menus.cpp,
// port::menus), included in each table with the macro naming the part.
// The world is the game's own tables -- the widgets' registry, the parser's
// keywords, the screens' handlers by name, the names of the language's text,
// all as the game loads them -- and the screens' and items' tables, the
// string pool and the language's text made up for each case.  What the loader
// reads a file with (fgets), calls for a key it does not know (the key wait)
// and builds a path with (sprintf, fopen, fclose) are stand-ins on both sides:
// a .MNU is made up line by line from the game's own widget, key and text
// names.
#if defined(MENUS_WINDOWS)
// {from, to}, -- what the functions write, compared
// The parser's tables, the string pool, the rest of the item table with the item
// counters, and the scratch strings of the cases.
{0x556000, 0x558000}, {0x5f4000, 0x600000}, {0x640000, 0x661000}, {0x300000, 0x314000},
#elif defined(MENUS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kMenusLine,  // fgets: a line of a .MNU, or its end
#elif defined(MENUS_EFFECT_CASES)
// case kSomething: ... break;
case kMenusLine:
{
    // (the buffer, its size, the file): a section, a key and its value, a
    // comment, a blank line, one the loader calls the key wait on, or the end
    // of the file; its ending a \n, a \r\n or none.  The names are the game's.
    std::uint64_t q = random64(id);
    const auto next = [&](x86::reg32 n) {
        q = mix(q);
        return x86::reg32(q >> 24) % n;
    };
    std::vector<std::string> widgets, keys;
    std::vector<x86::reg32> kinds;
    for (x86::reg32 at = 0x557a84; word(at) != 0; at += 12)
        widgets.push_back(&getMemory<char>(word(at + 4)));
    for (x86::reg32 at = 0x557c10; word(at) != 0; at += 16)
    {
        keys.push_back(&getMemory<char>(word(at + 4)));
        kinds.push_back(word(at + 8));
    }
    const auto textName = [&] { return std::string(&getMemory<char>(word(0x561c44 + 4 * next(0x789)))); };
    static const char* const screens[] = {"main", "location", "car1", "audio", "graphics", "options", "garage"};
    std::string line;
    if (next(9) == 0)
    {
        result = 0;
        break;
    }
    switch (next(16))
    {
    case 0:
        break;
    case 1:
        line = "; " + textName();
        break;
    case 2:
    case 3:
    case 4:
        line = next(8) == 0 ? "[nothing]" : "[" + widgets[next(widgets.size())] + "]";
        if (next(6) == 0)
            line = "  " + line;
        break;
    case 5:
        line = next(2) ? "[" + widgets[next(widgets.size())] : widgets[next(widgets.size())] + "]";
        break;
    case 6:
        line = next(2) ? "garbage" : "key without a value";
        break;
    case 7:
        line = keys[next(keys.size())] + (next(2) ? " =" : "=");
        break;
    case 8:
        // (A key past the loader's 0x100 bytes of them would write over the
        // frame's saved registers: the original's, and not a case to hold.)
        line = std::string(next(3) ? 0x40 : 0xe0, 'a') + (next(2) ? " = 1" : "");
        break;
    case 9:
        line = next(2) ? "=" + textName() : "[";
        break;
    default:
    {
        const x86::reg32 k = next(keys.size());
        std::string value;
        switch (kinds[k])
        {
        case 0:
        case 1:
        case 2:
        case 3:
            value = next(8) == 0 ? "-" + std::to_string(next(100)) : next(8) == 0 ? "12ab" : std::to_string(next(next(2) ? 300 : 70000));
            break;
        case 5:
            value = next(2) ? textName() : next(4) ? "kMenu" + textName() : "some words";
            break;
        case 6:
            value = next(5) == 0 ? "1e5" : next(5) == 0 ? "-" + std::to_string(next(9)) + ".25" : std::to_string(next(9)) + "." + std::to_string(next(100));
            break;
        default:
            value = next(3) ? screens[next(7)] : textName();
            break;
        }
        if (keys[k] == "nextmenu")
            value = next(6) == 0 ? "" : screens[next(7)];
        static const char* const around[] = {" = ", "=", "\t=\t", "  =  "};
        line = (next(5) == 0 ? " " : "") + keys[k] + around[next(4)] + value + (next(6) == 0 ? "  " : "");
        break;
    }
    }
    static const char* const ends[] = {"\n", "\n", "\n", "\r\n", "\r\n", ""};
    line += ends[next(6)];
    const x86::reg32 room = words[1] > 0 && words[1] < 0x10000 ? words[1] - 1 : 0;
    const x86::reg32 count = std::min<x86::reg32>(room, x86::reg32(line.size()));
    for (x86::reg32 i = 0; i < count; ++i)
        getMemory<x86::reg8>(words[0] + i) = x86::reg8(line[i]);
    getMemory<x86::reg8>(words[0] + count) = 0;
    result = words[0];
    break;
}
#elif defined(MENUS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// What the loader calls that is not the game's own to hold here: a line of the
// file (the file's runtime is the files' world) and the key wait.
{0x4f0570, "a line of a file", kWatcom, 3, 0, kEax, -1, 0, kMenusLine},
{0x4f0120, "a key waited for", kWatcom, 0, 0, kEax, -1, 0, kNothing},
#elif defined(MENUS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// A screen's onLoad handler (+0), by pseudo-slot.
{0xfff6d0, "a screen's onLoad handler", kWatcom, 1, 0, kEax, -1, 0, kNothing},
#elif defined(MENUS_PROMISES)
// {"port::menus::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax and the registers the port keeps; the x87's stack and words too, where
// a float goes through it.
{"port::menus::codelinkMatches", true, true, 0, true, kNoHeap, true},
{"port::menus::assignHandlers", true, true, 0, true, kNoHeap, true},
{"port::menus::keywordIndex", true, true, 0, true, kNoHeap, true},
{"port::menus::storeString", true, true, 0, true, kNoHeap, true},
{"port::menus::widgetType", true, true, 0, true, kNoHeap, true},
{"port::menus::widgetName", true, true, 0, true, kNoHeap, true},
{"port::menus::initItem", true, true, 0, true, kNoHeap, true},
{"port::menus::sectionType", true, true, 0, true, kNoHeap, true},
{"port::menus::parseInt", true, true, 0, true, kNoHeap, true},
{"port::menus::parseLong", true, true, 0, true, kNoHeap, true},
{"port::menus::parseFloat", true, true, 0, true, kNoHeap, true},
{"port::menus::setField", true, true, 0, true, kNoHeap, true},
{"port::menus::readEntry", true, true, 0, true, kNoHeap, true},
{"port::menus::loadMenus", true, true, 0, true, kNoHeap, true},
{"port::menus::checkMenuFile", true, true, 0, true, kNoHeap, true},
{"port::menus::checkMenuFiles", true, true, 0, true, kNoHeap, true},
{"port::menus::callOnLoad", true, true, 0, true, kNoHeap, true},
{"port::menus::appendBackslash", true, true, 0, true, kNoHeap, true},
#elif defined(MENUS_ARGUMENTS)
/* Where the cases keep their own, in 0x300000 on: 0x1c0 strings of 0x80
 * bytes; the key, the value and the line count of an entry read, a path, a
 * file handle, and the language's text. */
constexpr x86::reg32 kMnStrings = 0x300000, kMnKey = 0x30e000, kMnValue = 0x30e100, kMnCount = 0x30e500;
constexpr x86::reg32 kMnPath = 0x30e600, kMnFile = 0x30e800, kMnTexts = 0x310000;
constexpr x86::reg32 kMnItems = 0x604ee0, kMnItemSize = 0xbc, kMnMenus = 0x6040d0;

/* What the game has in its tables, read from its own memory. */
struct MenuFilesVocabulary
{
    std::vector<std::string> handlers, widgets, keys, texts;
    std::vector<x86::reg32> types, kinds;
    std::vector<x86::reg8> keywordTable;  // as the game loads it
};

const MenuFilesVocabulary& menuFilesVocabulary(CheckApp& g)
{
    static MenuFilesVocabulary v;
    if (!v.keys.empty())
        return v;
    for (x86::reg32 at = 0x555c48; g.word(at) != 0; at += 0x18)
        v.handlers.push_back(&g.getMemory<char>(g.word(at)));
    for (x86::reg32 at = 0x557a84; g.word(at) != 0; at += 12)
    {
        v.widgets.push_back(&g.getMemory<char>(g.word(at + 4)));
        v.types.push_back(g.word(at));
    }
    x86::reg32 end = 0x557c10;
    for (; g.word(end) != 0; end += 16)
    {
        v.keys.push_back(&g.getMemory<char>(g.word(end + 4)));
        v.kinds.push_back(g.word(end + 8));
    }
    end += 16;
    v.keywordTable.assign(&g.getMemory<x86::reg8>(0x557c10), &g.getMemory<x86::reg8>(0x557c10) + (end - 0x557c10));
    for (x86::reg32 i = 0; i < 0x789; ++i)
        v.texts.push_back(&g.getMemory<char>(g.word(0x561c44 + 4 * i)));
    return v;
}

/* A string of the case's, in the next free slot of the scratch. */
x86::reg32 mnString(CheckApp& g, x86::reg32& slot, const std::string& text)
{
    const x86::reg32 at = kMnStrings + 0x80 * (slot++ % 0x1c0);
    std::memcpy(&g.getMemory<char>(at), text.c_str(), std::min<std::size_t>(text.size(), 0x7e));
    g.getMemory<char>(at + std::min<std::size_t>(text.size(), 0x7e)) = 0;
    return at;
}

/* A name as the game has it, its case turned now and then. */
std::string mnVariant(const std::string& name)
{
    std::string s = name;
    if (chance(15))
        for (char& c : s)
            if (chance(40))
                c = char(std::isupper((unsigned char)c) ? std::tolower((unsigned char)c) : std::toupper((unsigned char)c));
    return s;
}

/* A screen's name: one the handlers' table has mostly. */
std::string mnScreenName(const MenuFilesVocabulary& v)
{
    static const char* const others[] = {"nothing", "car2", "x", "MAIN2", "", "location2"};
    return chance(75) ? mnVariant(v.handlers[below(v.handlers.size())]) : others[below(6)];
}

/* The case's world: the game's tables as it loads them; the screens (0 to 6)
 * with their names, handlers and flags; the first items; the string pool, the
 * item made last; the language's text. */
void makeMenuFilesWorld(CheckApp& g, x86::CPU& cpu)
{
    const MenuFilesVocabulary& v = menuFilesVocabulary(g);
    std::memcpy(&g.getMemory<x86::reg8>(0x557c10), v.keywordTable.data(), v.keywordTable.size());
    // A kind there is not now and then, in a row the case may use.
    if (chance(4))
        g.word(0x557c10 + 16 * below(v.keys.size()) + 8) = 7 + below(3);
    x86::reg32 slot = 0;
    const x86::reg32 count = chance(8) ? 0 : 1 + below(chance(95) ? 6 : 12);
    for (x86::reg32 at = kMnMenus; at < kMnMenus + 0x24 * 14; at += 4)
        g.word(at) = 0;
    for (x86::reg32 i = 0; i < count; ++i)
    {
        const x86::reg32 at = kMnMenus + 0x24 * i;
        for (x86::reg32 h = 0; h < 5; ++h)
            g.word(at + 4 * h) = chance(50) ? 0 : standInFor(0xfff6d0);
        g.word(at + 0x14) = mnString(g, slot, mnScreenName(v));
        g.getMemory<x86::reg16>(at + 0x18) = x86::reg16(below(30));
        g.getMemory<x86::reg16>(at + 0x1a) = x86::reg16(below(5));
        g.getMemory<x86::reg16>(at + 0x1e) = x86::reg16(chance(50) ? 1 : chance(80) ? 0 : random32());
        g.getMemory<x86::reg16>(at + 0x20) = x86::reg16(chance(70) ? 0 : chance(80) ? 1 : random32());
    }
    g.word(0x660bb0) = count;
    // The pool: mostly nearly empty; full to the brim now and then.
    g.word(0x660ba8) = chance(80) ? below(0x400) : chance(60) ? 0x10000 - below(0x80) : random32() % 0x10000;
    g.word(0x660bac) = chance(60) ? below(40) - 1 : chance(5) ? 1995 + below(8) : below(2000);
    // The first items: some of them random, the widget's type a plausible one.
    for (x86::reg32 at = kMnItems; at < kMnItems + kMnItemSize * 64; at += 4)
        g.word(at) = random32();
    for (x86::reg32 i = 0; i < 64; ++i)
    {
        const x86::reg32 at = kMnItems + kMnItemSize * i;
        g.word(at) = chance(80) ? v.types[below(v.types.size())] : chance(50) ? 0 : random32();
        g.word(at + 0x10) = chance(60) ? mnString(g, slot, mnVariant(v.handlers[below(v.handlers.size())])) : 0;
        g.word(at + 0x40) = chance(60) ? mnString(g, slot, mnScreenName(v)) : 0;
    }
    g.word(0x55921c) = 0;
    // sscanf's float (the runtime's slot).
    g.word(0x56ac68) = standInFor(0x56ac68);
    // The language's text: its lines' offsets, to 16 texts after them.
    g.word(0x563a80) = kMnTexts;
    for (x86::reg32 i = 0; i < 0x7a7; ++i)
        g.word(kMnTexts + 4 * i) = 0x1ea0 + 0x20 * (i % 16);
    for (x86::reg32 i = 0; i < 16; ++i)
        std::strcpy(&g.getMemory<char>(kMnTexts + 0x1ea0 + 0x20 * i), ("line" + std::to_string(i)).c_str());
    cpu.fpu.count = 0;
}

/* A name a codelink may hold: some words apart by spaces (a tab now and then,
 * a space too many). */
std::string mnCodelink(const MenuFilesVocabulary& v)
{
    static const char* const words[] = {"MAIN_LOCATION_BUTTON", "BACK", "OK", "car1", "track", "a", "ab", "abc"};
    std::string s;
    const x86::reg32 n = chance(60) ? 1 : 1 + below(4);
    for (x86::reg32 i = 0; i < n; ++i)
        s += (i ? (chance(90) ? " " : chance(50) ? "  " : "\t") : "") + std::string(chance(70) ? words[below(8)] : v.keys[below(v.keys.size())].c_str());
    return s;
}

bool makeMenuFilesArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* a)
{
    makeMenuFilesWorld(g, cpu);
    const MenuFilesVocabulary& v = menuFilesVocabulary(g);
    x86::reg32 slot = 200;
    const auto aMenu = [&] { return kMnMenus + 0x24 * below(g.word(0x660bb0) + (chance(10) ? 2 : 1)); };
    (void)a;
    if (name == "codelinkMatches")
    {
        cpu.eax = chance(5) ? 0 : mnString(g, slot, mnCodelink(v));
        if (chance(3))
        {
            std::string s;
            // (Past the 0x200 bytes strtok's copy has in the frame it would
            // write over the saved registers: the original's, not a case.)
            while (s.size() < 0x1c0)
                s += mnCodelink(v) + " ";
            s.resize(std::min<std::size_t>(s.size(), 0x1ff));
            std::memcpy(&g.getMemory<char>(kMnValue), s.c_str(), s.size() + 1);
            cpu.eax = kMnValue;
        }
        std::string first = &g.getMemory<char>(cpu.eax);
        first = first.substr(0, first.find_first_of(" 	"));
        cpu.edx = chance(5) ? 0 : chance(60) ? mnString(g, slot, first) : mnString(g, slot, chance(50) ? "BACK" : mnCodelink(v));
    }
    else if (name == "assignHandlers")
    {
        cpu.eax = aMenu();
        g.word(cpu.eax + 0x14) = mnString(g, slot, mnScreenName(v));
        for (x86::reg32 h = 0; h < 5; ++h)
            g.word(cpu.eax + 4 * h) = chance(50) ? 0 : random32();
    }
    else if (name == "keywordIndex")
    {
        cpu.eax = mnString(g, slot, chance(70) ? mnVariant(v.keys[below(v.keys.size())])
                                                : chance(50) ? "nothing" : v.keys[below(v.keys.size())] + "x");
        cpu.edx = chance(60) ? v.types[below(v.types.size())] : chance(15) ? 1 : chance(60) ? below(40) : random32();
    }
    else if (name == "storeString")
    {
        std::string s;
        for (x86::reg32 i = below(chance(80) ? 20 : 100); i > 0; --i)
            s += char('a' + below(26));
        cpu.eax = mnString(g, slot, s);
        // The pool full to the string's length now and then.
        if (chance(25))
            g.word(0x660ba8) = 0x10000 - x86::reg32(s.size()) - 1 + below(3) - 1;
        if (chance(5))
            cpu.eax = 0x5f40d0 + below(0x100);  // a string of the pool itself
    }
    else if (name == "widgetType")
        cpu.eax = mnString(g, slot, chance(70) ? mnVariant(v.widgets[below(v.widgets.size())]) : chance(50) ? "nothing" : "");
    else if (name == "widgetName")
        cpu.eax = chance(70) ? v.types[below(v.types.size())] : chance(70) ? below(40) : random32();
    else if (name == "initItem")
    {
        cpu.eax = chance(90) ? below(64) : chance(70) ? below(2000) : 1999;
        cpu.edx = chance(70) ? v.types[below(v.types.size())] : chance(40) ? 0 : chance(70) ? below(40) : random32();
    }
    else if (name == "sectionType")
    {
        std::string s;
        const x86::reg32 kind = below(10);
        if (kind < 4)
            s = "[" + mnVariant(v.widgets[below(v.widgets.size())]) + "]";
        else if (kind == 4)
            s = "[nothing]";
        else if (kind == 5)
            s = "[]";
        else if (kind == 6)
            s = "[" + v.widgets[below(v.widgets.size())];
        else if (kind == 7)
            s = v.widgets[below(v.widgets.size())] + "]";
        else if (kind == 8)
            s = "";
        else
            s = "[";
        std::memcpy(&g.getMemory<char>(kMnKey), s.c_str(), s.size() + 1);
        cpu.eax = kMnKey;
    }
    else if (name == "parseInt" || name == "parseLong")
    {
        static const char* const numbers[] = {"0", "1", "123", "99999", "2147483647", "4294967295", "99999999999", "-5",
                                              "12ab", "ab", "", " 5", "5 ", "007", "00", "+3", "1.5"};
        cpu.eax = mnString(g, slot, chance(80) ? numbers[below(17)] : std::to_string(random32()));
    }
    else if (name == "parseFloat")
    {
        static const char* const floats[] = {"0", "1", "1.5", "0.25", "-3", "12", "abc", "1.5x", "-0.0", "1e3", "3.14159",
                                             "0000.5", ".5", "5.", "-", "--1", "1-2", "100000000000000000000", "", "1.0.0",
                                             "00.00", "-1.5", "0.1", "16777217", "1e-50", "nan", "inf", "1,5", "x1"};
        cpu.eax = mnString(g, slot, chance(85) ? floats[below(29)]
                                                : std::to_string(int(below(1000)) - 500) + "." + std::to_string(below(1000)));
    }
    else if (name == "setField")
    {
        cpu.eax = chance(90) ? below(64) : below(2000);
        cpu.edx = below(v.keys.size());
        const x86::reg32 kind = g.word(0x557c10 + 16 * cpu.edx + 8);
        std::string s;
        if (kind <= 3)
            s = chance(10) ? std::to_string(random32()) : chance(10) ? "-7" : chance(10) ? "9x" : std::to_string(below(chance(50) ? 300 : 70000));
        else if (kind == 5)
            s = chance(50) ? v.texts[below(v.texts.size())] : chance(50) ? "kMenu" + v.texts[below(v.texts.size())].substr(5) : chance(50) ? "kTextNobody" : "hello";
        else if (kind == 6)
            s = chance(20) ? "x" : chance(20) ? "-2.5" : std::to_string(below(100)) + "." + std::to_string(below(100));
        else
            for (x86::reg32 i = below(30); i > 0; --i)
                s += char('a' + below(26));
        cpu.ebx = mnString(g, slot, s);
        if (chance(25))
            g.word(0x660ba8) = 0x10000 - x86::reg32(s.size()) - below(4) - 2 + below(4);
    }
    else if (name == "readEntry")
    {
        cpu.eax = kMnFile;
        cpu.edx = kMnKey;
        cpu.ebx = kMnValue;
        cpu.ecx = kMnCount;
        g.word(kMnCount) = chance(90) ? below(100) : random32();
    }
    else if (name == "loadMenus")
    {
        cpu.eax = mnString(g, slot, mnScreenName(v));
        cpu.edx = chance(35) ? (chance(80) ? 1 : random32() | 1) : 0;
    }
    else if (name == "checkMenuFile")
        cpu.eax = below(g.word(0x660bb0) + 1);
    else if (name == "checkMenuFiles")
        cpu.eax = random32();
    else if (name == "callOnLoad")
        cpu.eax = aMenu();
    else if (name == "appendBackslash")
    {
        static const char* const paths[] = {"", "x", "abc\\", "\\", ".\\FeData\\Menus", ".\\FeData\\Menus\\", "a/b", "\\\\",
                                            "dir\\sub", "c:"};
        std::strcpy(&g.getMemory<char>(kMnPath), paths[below(10)]);
        cpu.eax = kMnPath;
    }
    else
        return false;
    return true;
}
#endif
