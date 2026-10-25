// game_checks.cpp's parts for a car's physics step and its leaves -- the
// per-frame step, the full step, the speed in the car's axes, the steering's
// angle, the dampings (native_physics.cpp) -- included in each table with the
// macro naming the part.
#if defined(PHYSICS_WINDOWS)
// {from, to}, -- what the functions write, compared
// The cases' car and its records are in the harness's (0x624000 to
// 0x627000); the globals: gravity in the car's axes (0x7a3a40, the page
// compared already), the race's frame counter (0x7d3684), the race's flags
// (0x6fd000, compared already).
{0x7d3000, 0x7d4000},
#elif defined(PHYSICS_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kPhWheelForce,  // a wheel's force (0x4aca4f): its record at edx, +0x10 to +0x24, floats made up
#elif defined(PHYSICS_EFFECT_CASES)
// case kSomething: ... break;
case kPhWheelForce:
    // What physicsStep sums of the four records afterwards: their forces
    // across and forward (+0x1c, +0x24) and the rest of them, a car's sizes.
    for (x86::reg32 k = 0x10; k < 0x28; k += 4)
    {
        const float f = float(x86::sreg32(random(id + k) % 40001) - 20000) / 10.0f;
        std::memcpy(&word(cpu.edx + k), &f, 4);
    }
    break;
#elif defined(PHYSICS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// The game's quick length of two stack floats onto the x87's stack (ret 8),
// every register kept; the engine's force onto it (0x4aaed1, the engine's
// file's); a wheel's force from its record at edx (0x4aca4f, the wheels'
// file's), the record's 12 words logged.
{0x4967e0, "two floats' length", kStdcall, 0, 2, 0, -1, 0, kFloatBack},
{0x4aaed1, "the engine's force", kWatcom, 1, 0, kEax, -1, 0, kFloatBack},
{0x4aca4f, "a wheel's force", kWatcom, 2, 0, kEax, 1, 12, kPhWheelForce},
// The module's other parts, native too (native_drivetrain.cpp,
// native_handling.cpp): the driver's inputs, the wheels' grip, a car at rest
// settled, the handling from the setup -- and the car's physics itself, which
// raceload's natives call -- by address, to stand-ins as any callee.
{0x4a9bc4, "the driver's inputs", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4aab41, "the wheels' grip", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4aa8e7, "a car at rest settled", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4a78d6, "the handling from the setup", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4ae4c1, "the car's physics", kWatcom, 1, 0, kEax, -1, 0, kNothing},
#elif defined(PHYSICS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(PHYSICS_PROMISES)
// {"physics::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared, eax too, and the x87's stack, its control and
// status words (a compare's flags) -- its registers in use.
{"physics::clearWheelForces", true, true, 0, true, kNoHeap, true},
{"physics::steerAngle", true, true, 0, true, kNoHeap, true},
{"physics::sideSlip", true, true, 0, true, kNoHeap, true},
{"physics::groundSpeed", true, true, 0, true, kNoHeap, true},
{"physics::physicsStep", true, true, 0, true, kNoHeap, true},
{"physics::carPhysics", true, true, 0, true, kNoHeap, true},
{"physics::settleLoadShift", true, true, 0, true, kNoHeap, true},
{"physics::driveForce", true, true, 0, true, kNoHeap, true},
{"physics::holdStill", true, true, 0, true, kNoHeap, true},
{"physics::sideGrip", true, true, 0, true, kNoHeap, true},
{"physics::handbrakeDrag", true, true, 0, true, kNoHeap, true},
{"physics::yawDamping", true, true, 0, true, kNoHeap, true},
{"physics::idleDamping", true, true, 0, true, kNoHeap, true},
{"physics::coastDamping", true, true, 0, true, kNoHeap, true},
{"physics::spinTorque", true, true, 0, true, kNoHeap, true},
#elif defined(PHYSICS_ARGUMENTS)
/* Where the physics' cases keep their own: the car, its handling, its
 * choice (+0x220), four wheels' records of 0x30 for clearWheelForces. */
constexpr x86::reg32 kPhCar = 0x624000, kPhHandling = 0x625000, kPhChoice = 0x625400, kPhRecords = 0x625800;

/* A float as the physics' fields have them: the thresholds its code compares
 * with (and the speeds the others make of them), a little either side; 0;
 * within `scale` either way; now and then tiny or huge.  No NaNs: which of
 * two a sum keeps is the host compiler's on the doubles' build. */
x86::reg32 aPhysicsFloat(float scale)
{
    static const float marks[] = {0.05f, 0.15f, 0.2f, 0.25f, 0.5f, 0.75f, 0.9f, 1.0f, 1.5f, 2.0f, 4.0f,
                                  5.0f,  13.4f, 20.0f, 26.7f, 28.0f, 40.0f, 64.0f, 100.0f};
    float f;
    const x86::reg32 kind = below(100);
    if (kind < 30)
        f = marks[below(19)] * (chance(40) ? -1.0f : 1.0f) * (chance(50) ? 1.0f : chance(50) ? 1.001f : 0.999f);
    else if (kind < 40)
        f = chance(20) ? -0.0f : 0.0f;
    else if (kind < 97)
        f = scale * float(x86::sreg32(below(20001)) - 10000) / 10000.0f;
    else
        f = (chance(50) ? 1e-30f : 1e30f) * (chance(50) ? -1.0f : 1.0f) * float(1 + below(100));
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

void putPhysicsFloat(CheckApp& g, x86::reg32 at, float f)
{
    std::memcpy(&g.word(at), &f, 4);
}

/* The car's world: the car -- each field a float mostly, a count, anything
 * -- then those its code walks set as a race has them: its records, its
 * speeds and spin, its inputs, its stage and flags; its handling's; the
 * race's globals; the x87 of every precision and rounding. */
void makePhysicsWorld(CheckApp& g, x86::CPU& cpu)
{
    const x86::reg32 car = kPhCar;
    for (x86::reg32 at = car; at < kPhRecords + 0x100; at += 4)
    {
        const x86::reg32 kind = below(100);
        g.word(at) = kind < 70 ? aPhysicsFloat(10.0f) : kind < 85 ? 0 : kind < 95 ? below(8) : random32();
    }
    g.word(car + 0x528) = kPhHandling;
    g.word(car + 0x220) = kPhChoice;
    // Its speed, spin and axes (world), its speed and spin in its own axes.
    for (x86::reg32 i = 0; i < 3; ++i)
    {
        g.word(car + 0xa4 + 4 * i) = aPhysicsFloat(60.0f);
        g.word(car + 0xe4 + 4 * i) = aPhysicsFloat(4.0f);
        g.word(car + 0x4ec + 4 * i) = aPhysicsFloat(i == 2 ? 60.0f : 8.0f);
        g.word(car + 0x4f8 + 4 * i) = aPhysicsFloat(4.0f);
        g.word(car + 0x2e8 + 4 * i) = aPhysicsFloat(20.0f);
        g.word(car + 0x2f4 + 4 * i) = aPhysicsFloat(4.0f);
    }
    for (x86::reg32 i = 0; i < 9; ++i)
        g.word(car + 0x190 + 4 * i) = aPhysicsFloat(1.0f);
    g.word(car + 0x5b0) = aPhysicsFloat(chance(50) ? 0.3f : 2.0f);
    g.word(car + 0x5a4) = aPhysicsFloat(60.0f);
    g.word(car + 0x5bc) = aPhysicsFloat(2.0f);
    for (x86::reg32 at = car + 0x5c0; at < car + 0x5e8; at += 4)
        g.word(at) = aPhysicsFloat(2.0f);
    g.word(car + 0x1a0) = aPhysicsFloat(1.0f);
    if (chance(70))
        putPhysicsFloat(g, car + 0x134, float(below(1001)) / 1000.0f);
    if (chance(70))
        putPhysicsFloat(g, car + 0x10c, float(below(2001)) / 1000.0f);
    // The pedals' travel, 0 to 1 mostly.
    for (const x86::reg32 at : {car + 0x5ec, car + 0x5f0})
        if (chance(80))
            putPhysicsFloat(g, at, chance(30) ? (chance(50) ? 0.0f : 1.0f) : float(below(1001)) / 1000.0f);
    // The race's stage, its flags, the slices to be put back on, the frames
    // since; the track's kind, the surface.
    g.getMemory<x86::reg16>(car + 0x164) = x86::reg16(chance(70) ? 0 : chance(80) ? 1 + below(8) : random32());
    g.getMemory<x86::reg8>(car + 0x200) = x86::reg8(chance(70) ? random32() & ~2u : random32());
    g.getMemory<x86::reg8>(car + 0x8a) = x86::reg8(chance(70) ? 0 : random32());
    g.word(car + 0x524) = chance(75) ? 0 : below(0x30);
    g.word(car + 0x184) = chance(75) ? 0 : below(0x100);
    g.word(car + 0x160) = chance(90) ? below(4) : random32();
    g.word(car + 0x18c) = below(16);
    g.word(car + 0x594) = chance(50) ? 1 : below(3);
    g.word(car + 0x5f4) = chance(60) ? 0 : random32();
    // The driver's inputs: the pedals, the gear, the handbrake, the steering
    // (about the code's 4, 32 and 64 now and then).
    for (const x86::reg32 at : {car + 0x508, car + 0x509})
        g.getMemory<x86::reg8>(at) = x86::reg8(chance(50) ? below(0x20) : random32());
    g.getMemory<x86::reg8>(car + 0x50b) = x86::reg8(chance(90) ? below(8) : random32());
    g.getMemory<x86::reg8>(car + 0x50d) = x86::reg8(chance(50) ? 0 : chance(80) ? 1 : random32());
    {
        static const x86::sreg32 steers[] = {0, 3, 4, 5, 31, 32, 33, 63, 64, 65, 127, 128};
        const x86::sreg32 steer = chance(50) ? steers[below(12)] : x86::sreg32(below(257)) - 128;
        g.word(car + 0x51c) = x86::reg32(chance(50) ? steer : -steer);
    }
    // The revs, about the handling's idle.
    g.word(kPhHandling + 0x1c0) = 500 + below(1500);
    g.word(car + 0x590) = chance(30) ? g.word(kPhHandling + 0x1c0) + below(1000) : below(9000);
    // The handling's, as a car's performance has them: the front's share, the
    // brakes', the back's, the load's share, the steering's lock, the mass,
    // the shift's, a wheel's size; the choice's tuning, about 1.
    for (x86::reg32 at = kPhHandling; at < kPhHandling + 0x400; at += 4)
        if (at != kPhHandling + 0x1c0)
            g.word(at) = aPhysicsFloat(4.0f);
    putPhysicsFloat(g, kPhHandling + 0x1d0, float(below(1001)) / 1000.0f);
    putPhysicsFloat(g, kPhHandling + 0x1d8, float(below(30001)) / 1000.0f);
    putPhysicsFloat(g, kPhHandling + 0x1dc, float(below(1001)) / 1000.0f);
    putPhysicsFloat(g, kPhHandling + 0x234, float(below(1001)) / 1000.0f);
    putPhysicsFloat(g, kPhHandling + 0x23c, float(10 + below(600)) / 10.0f);
    if (chance(90))
        putPhysicsFloat(g, kPhHandling + 0x248, float(800 + below(1200)));
    putPhysicsFloat(g, kPhHandling + 0x254, float(below(2001)) / 10000.0f);
    putPhysicsFloat(g, kPhHandling + 0x258, float(200 + below(300)) / 1000.0f);
    putPhysicsFloat(g, kPhChoice + 0x58, chance(30) ? 1.0f : float(500 + below(1001)) / 1000.0f);
    // The wheels' records for clearWheelForces.
    for (x86::reg32 at = kPhRecords; at < kPhRecords + 0xc0; at += 4)
        g.word(at) = random32();
    // The race's: the players on this machine, the race's type, the frame
    // (the countdown's end at 0x200), gravity in the car's axes (forward
    // about 0.5 now and then), a word never used.
    g.word(0x6fd3b0) = chance(90) ? below(5) : random32();
    g.word(0x6fd3b8) = chance(90) ? below(5) : random32();
    g.word(0x7d3684) = chance(80) ? 0x200 + below(0x10000) : below(0x200);
    g.word(0x7a3a40) = aPhysicsFloat(10.0f);
    g.word(0x7a3a44) = aPhysicsFloat(10.0f);
    g.word(0x7a3a48) = chance(50) ? aPhysicsFloat(1.0f) : aPhysicsFloat(10.0f);
    g.word(0x6fd494) = random32();
    // The x87: a control word of every precision and rounding, one or none on its stack.
    static const x86::reg16 precisions[] = {0x000, 0x200, 0x300};
    cpu.fpu.setControl(x86::reg16(0x7f | precisions[below(3)] | below(4) << 10 | (random32() & 0x1000)));
    cpu.fpu.count = below(2);
    for (x86::Float& f : cpu.fpu.regs)
        f = x86::Float(anyDouble());
}

bool makePhysicsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    makePhysicsWorld(g, cpu);
    cpu.eax = name == "clearWheelForces" ? kPhRecords + 0x30 * below(4) : kPhCar;
    return true;
}
#endif
