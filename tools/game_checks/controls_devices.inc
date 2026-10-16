// game_checks.cpp's parts for the control sets for the devices the game knows (native_controls_devices.cpp), included in
// each table with the macro naming the part.
#if defined(CONTROLS_WINDOWS)
// {from, to}, -- what the functions write, compared
#elif defined(CONTROLS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
    kDevicesCopy,  // the game's memmove (0x4ea4f0): ebx bytes from eax to edx
#elif defined(CONTROLS_EFFECT_CASES)
// case kSomething: ... break;
        case kDevicesCopy:
            if (words[2] <= 0x1000 && words[0] < kMemory - 0x1000 && words[1] < kMemory - 0x1000)
                std::memmove(&getMemory<x86::reg8>(words[1]), &getMemory<x86::reg8>(words[0]), words[2]);
            break;
#elif defined(CONTROLS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
    // The game's memmove, which the control sets are copied into the players' with: what it copies logged.
    {0x4ea4f0, "memmove", kWatcom, 3, 0, kEax | kEdx | kEbx, 0, 13, kDevicesCopy},
#elif defined(CONTROLS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(CONTROLS_PROMISES)
// {"controls::name", watcom, result, arguments, fpu, heap, liveOnly},
    // The control sets for the devices the game knows (native_controls_devices.cpp): every register compared
    // -- but edx where a controller's name is looked for: the game's strstr (0x4e0820) leaves its argument
    // register edx as its code goes, native watcom::strstr as it was; Watcom's callers count on neither.
    {"controls::controlsFor", true, true, 0},
    {"controls::defaultControls", true, true, 0},
    {"controls::setControls", true, true, 0},
    {"controls::controllerNamed", true, true, 2},
    {"controls::knownControllerControls", true, true, 2},
    {"controls::sideWinderGamePadControls", true, true, 2},
    {"controls::gravisGripControls", true, true, 2},
    {"controls::wingManForceControls", true, true, 2},
    {"controls::combatStickControls", true, true, 2},
    {"controls::sideWinderProControls", true, true, 2},
    {"controls::sideWinderWheelControls", true, true, 2},
    {"controls::steeringWheelControls", true, true, 2},
    {"controls::keyboardControls", true, true, 0},
    {"controls::gamePadControls", true, true, 0},
    {"controls::joystickControls", true, true, 0},
    {"controls::otherControllerControls", true, true, 0},
#elif defined(CONTROLS_ARGUMENTS)
/* The control sets' cases: the controllers -- 8 records, of every kind, named
 * as the devices the game knows (in the middle of a longer name now and
 * then), or otherwise, or not at all; their buttons and second axes -- the
 * players' sets as anything, the keyboard's defaults in the code's bytes; a
 * mode (1 two players on one screen, mostly 0 or 1), a controller (the first
 * two mostly), which of the players' sets, a set to copy. */
bool makeDevicesArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "controlsFor", "defaultControls", "setControls", "controllerNamed", "knownControllerControls",
        "sideWinderGamePadControls", "gravisGripControls", "wingManForceControls", "combatStickControls",
        "sideWinderProControls", "sideWinderWheelControls", "steeringWheelControls", "keyboardControls",
        "gamePadControls", "joystickControls", "otherControllerControls"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    (void)stack;
    static const char* const known[] = {
        "Microsoft SideWinder game pad", "Gravis GrIP", "Logitech WingMan Force", "CH F-16 Combat Stick",
        "Microsoft 3D SideWinder Pro", "Microsoft SideWinder Force Feedback Wheel", "CH Steering Wheel",
        "Microsoft SideWinder", "Gravis", "Joystick", "Thrustmaster Formula T2"};
    static const x86::reg32 kinds[] = {0, 1, 2, 3, 4, 5, 6};
    g.word(0x6fd204) = below(9);
    for (x86::reg32 c = 0; c < 8; ++c)
    {
        const x86::reg32 record = 0x6fc970 + 0x88 * c;
        for (x86::reg32 at = record; at < record + 0x88; at += 4)
            g.word(at) = random32();
        g.word(record) = chance(90) ? kinds[below(7)] : random32();
        // The name: a known one, inside another now and then, or another, or none.
        std::string text;
        if (chance(75))
        {
            text = known[chance(85) ? below(7) : below(11)];
            if (chance(15))
                text = "My " + text + " 2";
        }
        else if (chance(70))
            for (x86::reg32 i = 0, n = below(30); i < n; ++i)
                text += char(' ' + below(95));
        for (x86::reg32 i = 0; i < text.size(); ++i)
            g.getMemory<x86::reg8>(record + 4 + i) = x86::reg8(text[i]);
        g.getMemory<x86::reg8>(record + 4 + text.size()) = 0;
        g.word(record + 0x38) = chance(20) ? 0 : chance(70) ? random32() & 0x3ff : random32();
        g.word(record + 0x40) = chance(40) ? 0 : chance(70) ? 1 : random32();
    }
    // The players' sets, and what is after them, as anything.
    for (x86::reg32 at = 0x6fd20c; at < 0x6fd400; at += 4)
        g.word(at) = random32();
    // A set to copy.
    for (x86::reg32 at = 0x616000; at < 0x616100; at += 4)
        g.word(at) = random32();
    cpu.eax = chance(45) ? 1 : chance(80) ? 0 : chance(50) ? 2 : random32();
    cpu.edx = chance(85) ? below(2) : below(8);
    if (name == "setControls")
    {
        cpu.edx = 0x616000 + 4 * below(0x10);
        cpu.ebx = chance(85) ? below(3) : random32();
    }
    else if (name == "keyboardControls")
        cpu.edx = chance(50) ? 2 : chance(50) ? below(2) : random32();
    else if (name == "controllerNamed")
    {
        static const x86::reg32 texts[] = {0x53bbe0, 0x53bc00, 0x53bc0c, 0x53bc24, 0x53bc3c, 0x53bc58, 0x53bc84};
        cpu.eax = below(8);
        cpu.edx = texts[below(7)];
    }
    return true;
}
#endif
