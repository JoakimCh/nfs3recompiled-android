// game_checks.cpp's parts for the controls read and turned into the players'
// actions every frame (native_controls_pipeline.cpp), included in each table
// with the macro naming the part.
#if defined(CONTROLS_WINDOWS)
// {from, to}, -- what the functions write, compared
// The joysticks' arrows (0x5f0770, after their states from 0x5eff30); the
// replay's frames and the queue stopped; the race's menus up.
{0x5f0000, 0x5f1000}, {0x560000, 0x561000}, {0x7d3000, 0x7d4000},
#elif defined(CONTROLS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kPipelineJoystick,  // readJoystick: the state at edx, made up, mostly; or 0
kPipelineKey,       // a key's state: 0 mostly, 0x80 now and then
kPipelineQueued,    // an input queued: taken mostly, or 0
#elif defined(CONTROLS_EFFECT_CASES)
// case kSomething: ... break;
case kPipelineJoystick:
{
    // The DIJOYSTATE and the game's after it: x and y about their middle,
    // the buttons' bytes, the axes, the buttons as bits, the hats' directions.
    result = r % 6 == 0 ? 0 : words[1];
    if (result != 0 && words[1] >= 0x5eff30 && words[1] + 0x84 <= 0x5f1000)
    {
        std::uint64_t bits = random64(id);
        for (x86::reg32 i = 0; i < 0x84; i += 4)
        {
            bits = mix(bits);
            const x86::reg32 b = x86::reg32(bits >> 16);
            x86::reg32 value = b;
            if (i < 8)
                value = bits % 9 == 0 ? b : b % 0x200;
            else if (i >= 0x30 && i < 0x50)
                value = (b & 0x80808080) & (bits % 3 == 0 ? 0xffffffff : 0);
            else if (i >= 0x50 && i < 0x70)
                value = bits % 11 == 0 ? b : b % 0x10000;
            else if (i == 0x70)
                value = bits % 2 == 0 ? 0 : b;
            else if (i >= 0x74)
                value = bits % 13 == 0 ? b : b % 9;
            word(words[1] + i) = value;
        }
    }
    break;
}
case kPipelineKey:
    result = r % 4 == 0 ? 0x80 : 0;
    break;
case kPipelineQueued:
    result = r % 4 == 0 ? 0 : 1;
    break;
#elif defined(CONTROLS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The joysticks read (native_controls_input.cpp's); a key's state; an
// input queued -- a player's four bytes logged -- and one sent over the
// network.
{0x4358f0, "a joystick read", kWatcom, 2, 0, kEax, -1, 0, kPipelineJoystick},
{0x4eb1c0, "a key's state", kWatcom, 1, 0, kEax, -1, 0, kPipelineKey},
{0x4c6530, "an input queued", kWatcom, 2, 0, kEax, 1, 1, kPipelineQueued},
{0x4c60c0, "an input sent", kWatcom, 1, 0, kEax, 0, 2, kNothing},
#elif defined(CONTROLS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(CONTROLS_PROMISES)
// {"controls::name", watcom, result, arguments, fpu, heap, liveOnly},
{"controls::clearJoysticks", true, true, 0},
{"controls::readJoysticks", true, true, 0},
{"controls::pollJoystick", true, true, 0},
{"controls::buttonHeld", true, true, 0},
{"controls::hatPointing", true, true, 0},
{"controls::axisAmount", true, true, 0},
{"controls::keyHeld", true, true, 0},
{"controls::controlHeld", true, true, 0},
{"controls::controlHeldNo", true, true, 0},
{"controls::controlHeldYes", true, true, 0},
{"controls::controlHeldByKind", true, true, 0},
{"controls::noControl", true, true, 0},
{"controls::bindPlayersControls", true, true, 0},
{"controls::startRaceControls", true, true, 0},
{"controls::readRaceControls", true, true, 0},
{"controls::bindControl", true, true, 0},
{"controls::bindFunctionKeys", true, true, 0},
{"controls::queueRaceControls", true, true, 0},
#elif defined(CONTROLS_ARGUMENTS)
/* A control of kind `kind` (any of 0 to 4 if -1): a device's number on top, a
 * key of the arrows' or Enter's or another, an axis's half or the whole of
 * it, a button, a hat's direction. */
x86::reg32 aPipelineControl(int kind = -1)
{
    const x86::reg32 k = kind < 0 ? below(5) : x86::reg32(kind);
    const x86::reg32 device = below(16) << 28;
    switch (k)
    {
    case 1:
    {
        static const x86::reg32 halves[][2] = {{0x80, 0xff}, {0x7f, 0}, {0, 0xff}, {0xff, 0}, {0x40, 0x40}};
        const x86::reg32 h = below(6);
        const x86::reg32 from = h < 5 ? halves[h][0] : below(0x100), to = h < 5 ? halves[h][1] : below(0x100);
        return device | (chance(90) ? below(8) : below(16)) << 24 | from << 16 | to << 8 | 1;
    }
    case 2:
        return device | (chance(90) ? below(0x20) : below(0x100)) << 8 | 2;
    case 3:
        return device | below(4) << 24 | (chance(90) ? below(9) : below(0x1000)) << 8 | 3;
    case 4:
    {
        static const x86::reg32 keys[] = {0x4b, 0x4d, 0x48, 0x50, 0x1c, 0x37, 0x0f};
        const x86::reg32 key = chance(60) ? keys[below(7)] : below(0x100);
        return device | (chance(5) ? below(0x100) << 16 : 0) | key << 8 | 4;
    }
    default:
        return device | (random32() & 0x0fffff00);
    }
}

/* The race's controls' world: the kinds' table as nfs3.exe has it, the
 * joysticks' list and states, the menus' arrows, the keys held, the race's
 * table of actions and the players' sets, the mode, the replay, the queue. */
void makePipelineWorld(CheckApp& g)
{
    static const x86::reg32 kinds[] = {0x4318b0, 0x431740, 0x4316c0, 0x4316f0, 0x4317d0, 0x431800, 0, 0};
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x554e34 + 4 * i) = kinds[i];
    // The joysticks' states, then their list: some of the 16, in any order, up to a negative byte.
    for (x86::reg32 at = 0x5eff30; at < 0x5f0780; at += 4)
    {
        const x86::reg32 i = (at - 0x5eff30) % 0x84;
        const x86::reg32 b = random32();
        g.word(at) = i < 8 ? (chance(10) ? b : b % 0x200)
                     : i >= 0x30 && i < 0x50 ? (chance(30) ? b & 0x80808080 : 0)
                     : i >= 0x50 && i < 0x70 ? (chance(10) ? b : b % 0x10000)
                     : i >= 0x74 ? (chance(10) ? b : b % 9)
                     : chance(50) ? 0 : b;
    }
    x86::reg32 devices[16];
    for (x86::reg32 i = 0; i < 16; ++i)
        devices[i] = i;
    for (x86::reg32 i = 15; i > 0; --i)
        std::swap(devices[i], devices[below(i + 1)]);
    const x86::reg32 listed = chance(10) ? 16 : below(8);
    for (x86::reg32 i = 0; i < 16; ++i)
        g.getMemory<x86::reg8>(0x5eff20 + i) =
            x86::reg8(i < listed ? devices[i] : i == listed ? (chance(80) ? 0xff : 0x80 | random32()) : random32());
    g.word(0x5f0770) = chance(50) ? 0 : chance(80) ? below(0x20) : random32();
    // The keys held.
    for (x86::reg32 at = 0x564818; at < 0x564918; ++at)
        g.getMemory<x86::reg8>(at) = x86::reg8(chance(85) ? 0 : chance(70) ? 0x80 : random32());
    // The race's actions, the players' sets.
    for (x86::reg32 at = 0x79c340; at < 0x79c4a0; at += 4)
        g.word(at) = chance(25) ? 0 : aPipelineControl();
    for (x86::reg32 at = 0x6fd20c; at < 0x6fd2a8; at += 4)
        g.word(at) = chance(10) ? 0 : aPipelineControl();
    for (x86::reg32 at = 0x79c1b0; at < 0x79c338; at += 4)
        g.word(at) = random32();
    g.word(0x79c338) = random32();
    g.word(0x79c33c) = random32();
    g.word(0x79c4ac) = chance(80) ? below(0x10000) : random32();
    // The mode, the replay, the menus, the queue, this machine's player, the steering swapped, the number keys.
    g.word(0x6fd3b0) = chance(90) ? below(4) : random32();
    g.word(0x6fd3a0) = chance(90) ? below(4) : random32();
    g.word(0x7d36a0) = chance(60) ? 0 : chance(80) ? 1 : random32();
    g.word(0x7d36a8) = chance(60) ? 0 : chance(80) ? 1 : random32();
    g.word(0x560104) = random32();
    g.word(0x560108) = chance(70) ? 0 : chance(80) ? 1 : random32();
    g.word(0x6fd4f4) = below(8);
    g.word(0x6fd4c4) = chance(50) ? 0 : chance(80) ? 1 : random32();
    for (x86::reg32 at = 0x6fbc04; at <= 0x6fbc0c; at += 4)
        g.word(at) = chance(90) ? below(11) : random32();
}

bool makePipelineArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    (void)stack;
    static const char* const names[] = {
        "clearJoysticks", "readJoysticks", "pollJoystick", "buttonHeld", "hatPointing", "axisAmount", "keyHeld",
        "controlHeld", "controlHeldNo", "controlHeldYes", "controlHeldByKind", "noControl", "bindPlayersControls",
        "startRaceControls", "readRaceControls", "bindControl", "bindFunctionKeys", "queueRaceControls"};
    if (std::find_if(std::begin(names), std::end(names), [&](const char* n) { return name == n; })
        == std::end(names))
        return false;
    makePipelineWorld(g);
    if (name == "pollJoystick")
        cpu.eax = chance(90) ? below(16) : random32();
    else if (name == "buttonHeld")
        cpu.eax = aPipelineControl(chance(90) ? 2 : -1);
    else if (name == "hatPointing")
        cpu.eax = aPipelineControl(chance(90) ? 3 : -1);
    else if (name == "axisAmount")
        cpu.eax = aPipelineControl(chance(90) ? 1 : -1);
    else if (name == "keyHeld")
        cpu.eax = aPipelineControl(chance(90) ? 4 : -1);
    else if (name == "controlHeld")
        cpu.eax = aPipelineControl();
    else if (name == "controlHeldByKind")
    {
        // In controlHeld's frame: eax the control, edx its kind (5 controlHeld again, now and then).
        cpu.eax = aPipelineControl();
        cpu.edx = chance(80) ? (cpu.eax & 0xff) : chance(80) ? below(5) : 5;
    }
    else if (name == "bindControl")
    {
        cpu.eax = below(0x58);
        cpu.edx = chance(10) ? 0 : aPipelineControl();
    }
    return true;
}
#endif
