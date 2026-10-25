// game_checks.cpp's parts for a car's handling -- the handling made from the
// player's setup, the automatic gear, the revs matched to the speed, the drive
// reset, a car at rest settled, an axle's tyres' forces (native_handling.cpp)
// -- included in each table with the macro naming the part.
#if defined(HANDLING_WINDOWS)
// {from, to}, -- what the functions write, compared
// The cases' own: the car, its handling, the player's setup, an axle, the
// cases' mark (0xd10000 to 0xd14000).  The race's globals (0x6fd000), the
// setup's middle (0x55d024) and the race's frame (0x7d3684) are on pages
// compared already.
{0xd10000, 0xd14000},
#elif defined(HANDLING_EFFECTS)
// kSomething,  -- a stand-in's effect of this file's
kHandlingDot,      // 0x4e01f0, a dot product, in the handling's cases: -40 to 40 onto the x87; else as kMathResult
kHandlingVectors,  // vectors added (0x4dffb0) or scaled (0x4e0050): three floats where the result goes
kHandlingTurn,     // 0x496bf0, a 2D turn: two floats where its last two words point
#elif defined(HANDLING_EFFECT_CASES)
// case kSomething: ... break;
case kHandlingDot:
    cpu.fpu.count += 1;
    if (word(0xd13ffc) != x86::reg32(g_seed))
    {
        // Not the handling's case: as the dot product's row elsewhere (kMathResult).
        cpu.fpu.st(0) = r % 5 != 0 ? x86::Float(double(x86::sreg32(r)) / 7.0) : x86::Float(r % 2 ? INFINITY : NAN);
    }
    else
    {
        // A speed along an axis, an axis's part: 0 now and then, small, as a race has them.
        const float f = r % 7 == 0 ? 0.0f
                        : r % 5 == 0 ? float(x86::sreg32((r >> 4) % 2001) - 1000) / 1000.0f
                                     : float(x86::sreg32((r >> 4) % 8001) - 4000) / 100.0f;
        cpu.fpu.st(0) = x86::Float(f);
    }
    break;
case kHandlingVectors:
case kHandlingTurn:
{
    // (n, the vector, the other, the result) for the vectors added, (n, the
    // vector; the scale, the result) scaled -- the result the fourth word
    // either way; (x, y, the angle; &x, &y) for the turn.
    const x86::reg32 count = s.effect == kHandlingTurn ? 2 : 3;
    for (x86::reg32 i = 0; i < count; ++i)
    {
        const x86::reg32 to = s.effect == kHandlingTurn ? words[3 + i] : words[3] + 4 * i;
        const float f = float(x86::sreg32(random(id + 0x40 + i) % 8001) - 4000) / 100.0f;
        if (to < kMemory - 4)
            std::memcpy(&word(to), &f, 4);
    }
    break;
}
#elif defined(HANDLING_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// A dot product of two vectors (eax, edx) onto the x87, as sound_lib.inc's
// row has it elsewhere; vectors added (n, a, b, the result at ecx) and
// scaled (n, a; the scale, the result, ret 8), the vector logged; a 2D turn
// by an angle (ret 0x14); a square root of a stack float.
{0x4e01f0, "a dot product", kWatcom, 4, 0, kEax, 0, 3, kHandlingDot},
{0x4dffb0, "vectors added", kWatcom, 4, 0, kEax | kEbx | kEcx | kEdx, 1, 3, kHandlingVectors},
{0x4e0050, "vectors scaled", kStdcall, 2, 2, kEax | kEdx, 1, 3, kHandlingVectors},
{0x496bf0, "a 2D turn", kStdcall, 0, 5, kEax, -1, 0, kHandlingTurn},
{0x4ea920, "a square root", kStdcall, 0, 1, 0, -1, 0, kFloatBack},
#elif defined(HANDLING_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
#elif defined(HANDLING_PROMISES)
// {"handling::name", watcom, result, arguments, fpu, heap, liveOnly},
// Every register compared, eax too, and the x87's stack, its control and
// status words (a compare's flags) -- its registers in use.
{"handling::logisticCurve", true, true, 0, true, kNoHeap, true},
{"handling::steeringGrip", true, true, 0, true, kNoHeap, true},
{"handling::setupSlipLimit", true, true, 0, true, kNoHeap, true},
{"handling::setupGripLoss", true, true, 0, true, kNoHeap, true},
{"handling::tyreGrip", true, true, 0, true, kNoHeap, true},
{"handling::tyreSlide", true, true, 0, true, kNoHeap, true},
{"handling::axleForces", true, true, 0, true, kNoHeap, true},
{"handling::applyTuning", true, true, 0, true, kNoHeap, true},
{"handling::automaticGear", true, true, 0, true, kNoHeap, true},
{"handling::matchRevsToSpeed", true, true, 0, true, kNoHeap, true},
{"handling::resetDriveState", true, true, 0, true, kNoHeap, true},
{"handling::settleAtRest", true, true, 0, true, kNoHeap, true},
#elif defined(HANDLING_ARGUMENTS)
/* Where the handling's cases keep their own: the car (0x9a4 bytes and more),
 * its handling's record, the player's setup (the car's +0x220), an axle's
 * record, the cases' mark. */
constexpr x86::reg32 kHgCar = 0xd10000, kHgHandling = 0xd11000, kHgSetup = 0xd11800, kHgAxle = 0xd11c00;
constexpr x86::reg32 kHgMark = 0xd13ffc;

x86::reg32 hgBits(float f)
{
    x86::reg32 bits;
    std::memcpy(&bits, &f, 4);
    return bits;
}

/* A float as the handling's fields have them: the thresholds its code
 * compares with, a little either side; 0; small, middling, negative. */
x86::reg32 aHandlingFloat()
{
    static const float marks[] = {0.015f, 0.02f, 0.05f, 0.1f, 0.15f, 0.2f, 0.25f, 0.5f, 0.75f, 0.85f,
                                  0.9f, 0.95f, 1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 13.4f, 16.0f, 30.0f};
    const x86::reg32 kind = below(100);
    if (kind < 35)
        return hgBits(marks[below(20)] * (chance(20) ? -1.0f : 1.0f)
                      * (chance(50) ? 1.0f : chance(50) ? 1.001f : 0.999f));
    if (kind < 45)
        return 0;
    if (kind < 80)
        return hgBits(float(x86::sreg32(below(4001)) - 2000) / 1000.0f);
    return hgBits(float(x86::sreg32(below(12001)) - 4000) / 100.0f);
}

/* A float from `from` to `to`, or one of the marks now and then. */
x86::reg32 aHandlingRange(float from, float to)
{
    return chance(85) ? hgBits(from + (to - from) * float(below(10001)) / 10000.0f) : aHandlingFloat();
}

/* A unit vector's three floats, or anything now and then. */
void putHandlingAxis(CheckApp& g, x86::reg32 at)
{
    const float x = float(x86::sreg32(below(2001)) - 1000) / 1000.0f;
    const float y = float(x86::sreg32(below(2001)) - 1000) / 1000.0f;
    const float z = float(x86::sreg32(below(2001)) - 1000) / 1000.0f;
    const float n = std::sqrt(x * x + y * y + z * z);
    const float s = n > 0.001f ? 1.0f / n : 1.0f;
    for (x86::reg32 i = 0; i < 3; ++i)
        g.word(at + 4 * i) = chance(90) ? hgBits((i == 0 ? x : i == 1 ? y : z) * s) : aHandlingFloat();
}

/* The handling's world: the car -- each field made up, then those its code
 * walks set as a race has them: its records, the gear, the revs, the
 * driver's inputs, the speeds and slips -- its handling (the gears and their
 * ratios, the torque's curve, the revs' range), the player's setup, an axle,
 * and the race's globals the functions read. */
void makeHandlingWorld(CheckApp& g)
{
    for (x86::reg32 at = kHgCar; at < kHgMark; at += 4)
        g.word(at) = chance(70) ? aHandlingFloat() : chance(50) ? below(4) : random32();
    g.word(kHgMark) = x86::reg32(g_seed);
    const x86::reg32 car = kHgCar, h = kHgHandling;
    g.word(car + 0x528) = h;
    g.word(car + 0x220) = kHgSetup;
    g.word(car + 0x1f0) = below(8);
    g.getMemory<x86::reg8>(car + 0x200) = x86::reg8(random32());
    g.word(car + 0x2c4) = below(5);
    g.word(car + 0x160) = chance(90) ? below(3) : below(8);
    g.getMemory<x86::reg16>(car + 0x164) = x86::reg16(chance(70) ? 0 : below(8));
    // The driver's inputs: the gear (reverse, neutral, the gears), the
    // handbrake, the wheel's time turned, the steering.
    for (x86::reg32 at = car + 0x504; at < car + 0x514; ++at)
        g.getMemory<x86::reg8>(at) = x86::reg8(chance(50) ? below(3) : random32());
    g.getMemory<x86::reg8>(car + 0x50b) = x86::reg8(chance(95) ? below(9) : random32());
    g.getMemory<x86::reg8>(car + 0x50d) = x86::reg8(chance(50) ? 0 : chance(80) ? 1 : random32());
    g.word(car + 0x514) = chance(30) ? 0 : chance(80) ? below(0x190) : x86::reg32(-x86::sreg32(below(8)));
    // (full lock, as a keyboard steers, often: past 0x7f the tyres' grip is cut)
    g.word(car + 0x51c) = chance(25) ? 0
                          : chance(35) ? x86::reg32(chance(50) ? 0x7f + below(2) : -x86::sreg32(0x7f + below(2)))
                                       : x86::reg32(x86::sreg32(below(0x101)) - 0x80);
    // The engine: revs, the clutch, the wheels' turn, the throttle and brake,
    // the axles' slip, its speeds.
    g.word(car + 0x590) = chance(90) ? below(0x2800) : random32();
    g.word(car + 0x594) = chance(40) ? 0 : chance(60) ? 1 : below(4);
    g.word(car + 0x59c) = below(0x1000);
    g.word(car + 0x5a4) = aHandlingRange(-10.0f, 150.0f);
    g.word(car + 0x5b0) = aHandlingRange(0.0f, 1.0f);
    g.word(car + 0x5f0) = aHandlingRange(0.0f, 1.0f);
    g.word(car + 0x5c0) = aHandlingRange(-5.0f, 5.0f);
    g.word(car + 0x5c4) = aHandlingRange(-5.0f, 5.0f);
    g.word(car + 0x4f4) = aHandlingRange(-15.0f, 70.0f);
    g.word(car + 0x4ec) = aHandlingRange(-15.0f, 15.0f);
    g.word(car + 0x15c) = aHandlingRange(0.0f, 1.0f);
    g.word(car + 0x10c) = aHandlingRange(-1.0f, 1.0f);
    g.word(car + 0x20c) = aHandlingRange(0.8f, 1.1f);
    for (x86::reg32 at = car + 0x52c; at < car + 0x5a0; at += 4)
        if (at != car + 0x590 && at != car + 0x594 && at != car + 0x59c)
            g.word(at) = aHandlingRange(0.0f, 4.0f);
    // Its axes, speed and spin.
    for (const x86::reg32 at : {0xc0u, 0xccu, 0xd8u, 0x130u, 0x190u, 0x1a8u})
        putHandlingAxis(g, car + at);
    g.word(car + 0x134) = chance(70) ? aHandlingRange(0.8f, 1.0f) : aHandlingRange(-1.0f, 1.0f);
    for (x86::reg32 i = 0; i < 3; ++i)
    {
        g.word(car + 0xa4 + 4 * i) = aHandlingRange(-3.0f, 3.0f);
        g.word(car + 0xe4 + 4 * i) = aHandlingRange(-1.0f, 1.0f);
    }
    // The handling: its gears, their ratios, the torque's curve, the revs'
    // idle and limit, its scales.
    for (x86::reg32 at = h; at < h + 0x400; at += 4)
        g.word(at) = aHandlingRange(0.1f, 3.0f);
    g.word(h + 8) = chance(90) ? 3 + below(6) : below(11);
    g.word(h + 0xc) = chance(90) ? 3 + below(6) : below(11);
    for (x86::reg32 i = 0; i < 0x29; ++i)
        g.word(h + 0x114 + 4 * i) = aHandlingRange(0.0f, 1.5f);
    // The gears' ratios and the top speed they turn into revs by (the revs a
    // 256th the torque curve's index): never wild, as the index must not be.
    for (x86::reg32 at = h + 0x90; at < h + 0xd4; at += 4)
        g.word(at) = hgBits(10.0f + float(below(14001)) / 100.0f);
    g.word(h + 0x1c8) = hgBits(20.0f + float(below(10001)) / 100.0f);
    g.word(h + 0x1c0) = chance(90) ? 500 + below(1500) : random32() % 0x4000;
    g.word(h + 0x1c4) = chance(90) ? 5000 + below(5000) : random32() % 0x4000;
    g.getMemory<x86::reg8>(h + 0x1d4) = x86::reg8(chance(50) ? 0 : 1);
    g.word(h + 0x1dc) = aHandlingRange(0.2f, 0.8f);
    g.word(h + 0x234) = aHandlingRange(0.4f, 0.6f);
    g.word(h + 0x254) = aHandlingRange(0.2f, 0.8f);
    // The player's setup: as its middle (kDefaultSetup) now and then, else a
    // slider's way either side -- never 0 where the code divides by it (the
    // top speed's revs index the torque's curve).
    static const float middle[] = {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    for (x86::reg32 at = kHgSetup; at < kHgSetup + 0x80; at += 4)
        g.word(at) = aHandlingFloat();
    for (x86::reg32 i = 0; i < 7; ++i)
        g.word(kHgSetup + 0x40 + 4 * i) =
            chance(40) ? hgBits(middle[i]) : hgBits(middle[i] - 0.5f + float(below(10001)) / 10000.0f);
    for (x86::reg32 i = 0; i < 7; ++i)
        g.word(0x55d024 + 4 * i) = chance(95) ? hgBits(middle[i]) : aHandlingFloat();
    // An axle: its drive, grip, wheels' angle, speeds across and along,
    // forces, whether the front's, slip.
    g.word(kHgAxle) = aHandlingRange(-20.0f, 20.0f);
    g.word(kHgAxle + 4) = aHandlingRange(0.0f, 30.0f);
    g.word(kHgAxle + 0xc) = chance(50) ? 0 : chance(10) ? 0x80000000 : aHandlingRange(-0.6f, 0.6f);
    g.word(kHgAxle + 0x10) = aHandlingRange(-20.0f, 20.0f);
    g.word(kHgAxle + 0x18) = aHandlingRange(-20.0f, 60.0f);
    g.word(kHgAxle + 0x28) = chance(50) ? 0 : chance(90) ? 1 : random32();
    // The race's: the mode, the series, the handling's flags, its options,
    // the players' kinds, the frame.
    g.word(0x6fd3b0) = chance(80) ? below(3) : below(6);
    g.word(0x6fd3b8) = below(5);
    g.word(0x6fd4fc) = chance(80) ? below(0x40) : random32();
    g.word(0x6fd490) = chance(50) ? 0 : 1;
    g.word(0x6fd4a4) = chance(50) ? 0 : 1;
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x6fd548 + 0x6c * i) = chance(60) ? 1 : below(3);
    g.word(0x7d3684) = random32();
}

bool makeHandlingArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    // The race's x87, as the controls' cases make it (controls_race.inc): a
    // control word of every precision and rounding, one or none on its stack.
    makeRaceWorld(g, cpu);
    makeHandlingWorld(g);
    cpu.eax = kHgCar;
    if (name == "logisticCurve")
        stack[0] = chance(80) ? hgBits(float(below(10001)) / 10000.0f) : aHandlingFloat();
    else if (name == "setupSlipLimit")
        cpu.eax = kHgSetup + 0x58;
    else if (name == "setupGripLoss")
        cpu.edx = kHgSetup + 0x58;
    else if (name == "tyreGrip" || name == "tyreSlide" || name == "axleForces")
        cpu.edx = kHgAxle;
    return true;
}
#endif
