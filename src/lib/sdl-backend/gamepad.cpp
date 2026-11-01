#include <lib/gamepad.h>
#include <lib/gamepad_policy.h>
#include <lib/touch_input.h>
#include <lib/controller_profile.h>
#include <lib/forcefeedback.h>
#ifdef __ANDROID__
#include <jni.h>
#endif
#include <SDL3/SDL.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <utility>
#include <vector>


namespace win32
{

/* ----------------------------------------------------------------------
 * Slots.  A slot is a stable identity the game binds its controls to; the
 * physical joystick behind it comes and goes.  Slots remember an
 * SDL_JoystickID rather than a position in SDL's device array, because that
 * position is not stable: unplug the first of two pads and the second one
 * slides down to index 0.
 *
 * Hotplug works even though the Gamepad constructor turns SDL's joystick
 * events off: SDL's Android backend appends to its device list and bumps the
 * count *before* the event push it then skips, and the three-second device
 * scan (ANDROID_JoystickDetect) hangs off SDL_UpdateJoysticks, which
 * SDL_PumpEvents calls every frame regardless of whether joystick events are
 * enabled.  Only SDL_HINT_AUTO_UPDATE_JOYSTICKS could switch that off, and
 * nothing here touches it. */
struct Slot
{
    SDL_JoystickID id = 0;
    SDL_Joystick*  handle = nullptr;
    /* The same pad through SDL's gamepad layer, whenever SDL has a mapping
     * for it -- on Android that is every pad, since SDL builds one from what
     * the device reports. */
    SDL_Gamepad*   gamepad = nullptr;
};
static Slot s_slots[Gamepad::kSlotCount];
std::atomic<int> s_context{int(Gamepad::Context::Menu)};
static std::atomic<std::uint64_t> s_controllerProfile[Gamepad::kSlotCount];
static std::atomic<x86::reg32> s_androidButtons[Gamepad::kSlotCount];
// Android face buttons and directions can arrive through different paths.
// Keep face-button authority (the A/B duplicate fix), but select D-pad
// authority only after Android actually reports a direction.
static constexpr x86::reg32 kAndroidRoute = 1u << 16;
static constexpr x86::reg32 kAndroidDpadRoute = 1u << 17;
static constexpr x86::reg32 kAndroidRoutes = kAndroidRoute | kAndroidDpadRoute;
static std::atomic<x86::reg32> s_nativeButtons[Gamepad::kSlotCount];
static std::atomic<std::uint64_t> s_racePause[Gamepad::kSlotCount];
static std::atomic<x86::reg32> s_pauseConsumed[Gamepad::kSlotCount];
static padpolicy::CaptureGate s_captureGate[Gamepad::kSlotCount];
static x86::reg32 s_physicalButtons[Gamepad::kSlotCount];

/* Which physical pad belongs in which slot is the launcher's decision, not
 * SDL's: the player picks them in Controls -> Gamepad, and NFS3Activity
 * resolves that choice against the pads Android has attached and hands the
 * result down here whenever a pad comes or goes.  What arrives is each pad's
 * Android input-device descriptor -- the one identifier Android keeps across
 * reconnects and reboots, and which differs between two pads of one model.
 *
 * SDL never exposes that descriptor, but it keeps a fingerprint of it: the
 * Android joystick driver builds each GUID with the descriptor as the name
 * SDL_CreateJoystickGUID runs through SDL_crc16, into bytes 2-3, and nothing
 * afterwards touches those two bytes (the capability bits it adds go into
 * bytes 12-15).  So a pad is recognised by hashing the descriptor the same way
 * and comparing. */
static std::mutex  s_assignmentMutex;
static std::string s_assignment[Gamepad::kSlotCount];
static bool        s_assignmentKnown = false;
static bool        s_assignmentChanged = false;

void Gamepad::setSlotDescriptors(const char* first, const char* second)
{
    std::lock_guard<std::mutex> lock(s_assignmentMutex);
    const char* values[] = { first ? first : "", second ? second : "" };
    for (unsigned slot = 0; slot < kSlotCount; ++slot) {
        if (s_assignment[slot] != values[slot]) {
            s_androidButtons[slot].store(0);
        }
        s_assignment[slot] = values[slot];
    }
    s_assignmentKnown = true;
    s_assignmentChanged = true;
}

static bool assignmentChanged()
{
    std::lock_guard<std::mutex> lock(s_assignmentMutex);
    return s_assignmentChanged;
}

static bool joystickHasDescriptor(SDL_JoystickID id, const std::string& descriptor)
{
    if (descriptor.empty())
        return false;
    const SDL_GUID guid = SDL_GetJoystickGUIDForID(id);
    const Uint16 fingerprint = Uint16(guid.data[2] | (guid.data[3] << 8));
    return fingerprint == SDL_crc16(0, descriptor.data(), descriptor.size());
}

static void placeInSlot(x86::reg32 slot, SDL_JoystickID id)
{
    if (s_slots[slot].id == id)
        return;
    if (s_slots[slot].gamepad)
        SDL_CloseGamepad(s_slots[slot].gamepad);
    if (s_slots[slot].handle)
        SDL_CloseJoystick(s_slots[slot].handle);
    s_slots[slot] = Slot();
    if (!id)
        return;
    SDL_Joystick* handle = SDL_OpenJoystick(id);
    if (!handle)
        return;
    s_slots[slot].id = id;
    s_slots[slot].handle = handle;
    if (SDL_IsGamepad(id))
        s_slots[slot].gamepad = SDL_OpenGamepad(id);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "gamepad slot %u <- %s",
                unsigned(slot), SDL_GetJoystickName(handle));
}

static void refreshSlots()
{
    int count = 0;
    SDL_JoystickID* ids = SDL_GetJoysticks(&count);

    std::string wanted[Gamepad::kSlotCount];
    bool known;
    {
        std::lock_guard<std::mutex> lock(s_assignmentMutex);
        known = s_assignmentKnown;
        for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
            wanted[slot] = s_assignment[slot];
        s_assignmentChanged = false;
    }

    if (known)
    {
        /* An empty slot stays empty: the launcher had no pad for it, and
         * guessing one here would undo exactly the choice it made. */
        for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
        {
            SDL_JoystickID match = 0;
            for (int i = 0; i < count && !match; ++i)
                if (joystickHasDescriptor(ids[i], wanted[slot]))
                    match = ids[i];
            placeInSlot(slot, match);
        }
        SDL_free(ids);
        return;
    }

    /* Nobody has said which pad goes where -- the desktop build, where there
     * is no launcher -- so slots fill in the order pads were found. */
    for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
    {
        if (!s_slots[slot].id)
            continue;
        bool stillThere = false;
        for (int i = 0; i < count; ++i)
            if (ids[i] == s_slots[slot].id) { stillThere = true; break; }
        if (!stillThere)
            placeInSlot(slot, 0);
    }
    for (int i = 0; i < count; ++i)
    {
        bool held = false;
        for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
            if (s_slots[slot].id == ids[i]) { held = true; break; }
        for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount && !held; ++slot)
            if (!s_slots[slot].id) { placeInSlot(slot, ids[i]); held = true; }
    }
    SDL_free(ids);
}

void Input::poll()
{
    SDL_UpdateJoysticks();
    refreshSlots();
}

SDL_Joystick* Gamepad::joystick() const
{
    return m_slot < kSlotCount ? s_slots[m_slot].handle : nullptr;
}

namespace
{
void updateButtonKeys();
}

void Gamepad::update()
{
    /* The only place slots are rescanned while the game is running.
     * The game's Poll (answered in nfs3hp/native_controls_host.cpp) would be
     * the natural home for it, but the game never calls it -- a full traced session on device shows not one Poll --
     * whereas this runs once per frame from the renderer.  Once a second is
     * quick enough to notice a pad being plugged in and keeps SDL_GetJoysticks'
     * allocation out of the frame loop; an assignment sent from the launcher
     * side is applied on the very next frame instead of waiting it out. */
    static Uint64 s_lastSlotScan = 0;
    const Uint64 now = SDL_GetTicks();
    /* The pads' state, once a frame, before it is read.  This used to happen
     * as a side effect of the message pump, which ran SDL_PumpEvents -- and
     * SDL_UpdateJoysticks with it -- thousands of times a second while it
     * spun in SDL_WaitEvent (see SDL_HINT_POLL_SENTINEL in nfs3hp_main.cpp).
     * The pump now sleeps until something happens; a pad read through HIDAPI,
     * a DualSense among them, still needs its reports taken in. */
    SDL_UpdateJoysticks();
    if (assignmentChanged() || now - s_lastSlotScan >= 1000)
    {
        s_lastSlotScan = now;
        refreshSlots();
    }
    updateButtonKeys();
    forcefeedback::update();
}

x86::reg32 Input::getButtonCount() const
{
    return 0;
}

x86::reg32 Input::getAxesCount() const
{
    return 0;
}

/* ----------------------------------------------------------------------
 * Mouse.  Fed entirely by an SDL event watch rather than SDL_GetRelativeMouseState():
 * a watch runs synchronously inside SDL_PushEvent regardless of which thread
 * generated the event and regardless of whether anything is polling
 * SDL_PollEvent/WaitEvent right now, so it can back the buffered
 * (GetDeviceData) read path with real per-event ordering, not just an
 * immediate-mode accumulator.  getState() (GetDeviceState) is served from the
 * same accumulator the watch fills, so both read paths agree with each
 * other.  Installed lazily from mouseImpl()'s first call -- always after
 * SDL_Init(), since nothing reaches Mouse::getState()/drainBuffer() before
 * the game's controls ask the port for a mouse device. */
namespace
{

bool SDLCALL mouseEventWatch(void* userdata, SDL_Event* event);

struct MouseImpl
{
    SDL_Mutex*  mutex;
    float       accumDx, accumDy, accumDz;
    x86::reg32  buttons;

    static const x86::reg32 kBufferCapacity = 64;
    Mouse::BufferedEvent buffer[kBufferCapacity];
    x86::reg32  bufferHead, bufferCount;

    MouseImpl()
        :   mutex(SDL_CreateMutex())
        ,   accumDx(0.f), accumDy(0.f), accumDz(0.f)
        ,   buttons(0)
        ,   bufferHead(0), bufferCount(0)
    {
        /* Registered exactly once, thanks to mouseImpl()'s function-local
         * static -- see the comment above this namespace for why a watch
         * instead of SDL_GetRelativeMouseState(). */
        SDL_AddEventWatch(mouseEventWatch, nullptr);
    }

    /* Caller holds mutex.  Drops the oldest entry once full -- DirectInput
     * would report a buffer-overflow flag instead, but nothing here reads
     * that flag back. */
    void pushEvent(x86::reg32 offset, x86::sreg32 value)
    {
        const x86::reg32 idx = (bufferHead + bufferCount) % kBufferCapacity;
        if (bufferCount == kBufferCapacity)
            bufferHead = (bufferHead + 1) % kBufferCapacity;
        else
            ++bufferCount;
        buffer[idx].offset = offset;
        buffer[idx].value  = value;
    }
};

MouseImpl& mouseImpl()
{
    static MouseImpl s_impl;
    return s_impl;
}

bool SDLCALL mouseEventWatch(void* /*userdata*/, SDL_Event* event)
{
    MouseImpl& m = mouseImpl();
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        SDL_LockMutex(m.mutex);
        m.accumDx += event->motion.xrel;
        m.accumDy += event->motion.yrel;
        if (event->motion.xrel != 0.f)
            m.pushEvent(DIMOFS_X, x86::sreg32(event->motion.xrel));
        if (event->motion.yrel != 0.f)
            m.pushEvent(DIMOFS_Y, x86::sreg32(event->motion.yrel));
        SDL_UnlockMutex(m.mutex);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
    {
        /* Only the first 4 buttons exist in the classic DIMOUSESTATE
         * layout this port hardcodes (see DIMOFS_* in gamepad.h). */
        int bit = -1;
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:   bit = 0; break;
        case SDL_BUTTON_RIGHT:  bit = 1; break;
        case SDL_BUTTON_MIDDLE: bit = 2; break;
        case SDL_BUTTON_X1:     bit = 3; break;
        default: break;
        }
        if (bit >= 0)
        {
            const bool down = event->type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            SDL_LockMutex(m.mutex);
            if (down) m.buttons |= (x86::reg32(1) << bit);
            else      m.buttons &= ~(x86::reg32(1) << bit);
            m.pushEvent(DIMOFS_BUTTON0 + bit, down ? 0x80 : 0x00);
            SDL_UnlockMutex(m.mutex);
        }
        break;
    }
    case SDL_EVENT_MOUSE_WHEEL:
        SDL_LockMutex(m.mutex);
        m.accumDz += event->wheel.y * 120.f;
        m.pushEvent(DIMOFS_Z, x86::sreg32(event->wheel.y * 120.f));
        SDL_UnlockMutex(m.mutex);
        break;
    default:
        break;
    }
    /* Let the event continue on to the normal queue -- window.cpp's message
     * pump still sees (and currently ignores) it too. */
    return true;
}

}

void Mouse::movePointer(x86::sreg32 dx, x86::sreg32 dy)
{
    if (!dx && !dy)
        return;
    MouseImpl& m = mouseImpl();
    SDL_LockMutex(m.mutex);
    m.accumDx += float(dx);
    m.accumDy += float(dy);
    if (dx)
        m.pushEvent(DIMOFS_X, dx);
    if (dy)
        m.pushEvent(DIMOFS_Y, dy);
    SDL_UnlockMutex(m.mutex);
}

void Mouse::pressPointer(x86::reg32 button, bool down)
{
    if (button > 3)
        return;
    MouseImpl& m = mouseImpl();
    SDL_LockMutex(m.mutex);
    if (down) m.buttons |= (x86::reg32(1) << button);
    else      m.buttons &= ~(x86::reg32(1) << button);
    m.pushEvent(DIMOFS_BUTTON0 + button, down ? 0x80 : 0x00);
    SDL_UnlockMutex(m.mutex);
}

Mouse::MouseState Mouse::getState()
{
    /* mouseImpl() installs the event watch on its first call ever (from
     * either this function or drainBuffer()) -- motion before the game asks
     * for mouse state the first time is simply never captured, which is
     * fine, since nothing would have consumed it anyway. */
    MouseImpl& m = mouseImpl();

    MouseState result;
    SDL_LockMutex(m.mutex);
    result.dx = x86::sreg32(m.accumDx);
    result.dy = x86::sreg32(m.accumDy);
    result.dz = x86::sreg32(m.accumDz);
    /* Keep the fractional remainder so slow, sub-pixel motion accumulates
     * across several reads instead of being truncated away every time. */
    m.accumDx -= float(result.dx);
    m.accumDy -= float(result.dy);
    m.accumDz -= float(result.dz);
    result.buttons = m.buttons;
    SDL_UnlockMutex(m.mutex);
    return result;
}

x86::reg32 Mouse::drainBuffer(BufferedEvent* out, x86::reg32 max)
{
    MouseImpl& m = mouseImpl();
    SDL_LockMutex(m.mutex);
    const x86::reg32 n = m.bufferCount < max ? m.bufferCount : max;
    for (x86::reg32 i = 0; i < n; ++i)
        out[i] = m.buffer[(m.bufferHead + i) % MouseImpl::kBufferCapacity];
    m.bufferHead = (m.bufferHead + n) % MouseImpl::kBufferCapacity;
    m.bufferCount -= n;
    SDL_UnlockMutex(m.mutex);
    return n;
}

x86::reg32 Mouse::getButtonCount() const
{
    return 4;
}

x86::reg32 Mouse::getAxesCount() const
{
    return 3;
}

/* ----------------------------------------------------------------------
 * The touch overlay's half of slot 0: steering and the pedals.  The overlay
 * speaks to the game through keys, and the launcher owns which key each
 * on-screen control sends (Controls -> Touch -> Keys), handed down as
 * NFS_TOUCH_<ACTION>.  The control profile binds steering and the pedals to
 * the slot's axes rather than to keys, so what the overlay is doing with
 * those four is read back off the keyboard state and folded into the axes.
 * Its other controls are keys the profile binds as they are.  Resolved once --
 * the environment is written before the native thread starts and never
 * changes afterwards. */
enum TouchAxisAction
{
    TOUCH_STEER_LEFT, TOUCH_STEER_RIGHT, TOUCH_ACCELERATE, TOUCH_BRAKE, TOUCH_AXIS_ACTIONS
};

static const SDL_Scancode* touchAxisKeys()
{
    static const auto s_keys = []() {
        struct Action { const char* variable; SDL_Scancode fallback; };
        static const Action actions[TOUCH_AXIS_ACTIONS] =
        {
            { "NFS_TOUCH_STEER_LEFT",  SDL_SCANCODE_LEFT  },
            { "NFS_TOUCH_STEER_RIGHT", SDL_SCANCODE_RIGHT },
            { "NFS_TOUCH_ACCELERATE",  SDL_SCANCODE_UP    },
            { "NFS_TOUCH_BRAKE",       SDL_SCANCODE_DOWN  },
        };
        std::array<SDL_Scancode, TOUCH_AXIS_ACTIONS> resolved;
        for (int i = 0; i < TOUCH_AXIS_ACTIONS; ++i)
        {
            const char* name = SDL_getenv(actions[i].variable);
            resolved[i] = name && *name
                ? SDL_GetScancodeFromKey(SDL_GetKeyFromName(name), nullptr)
                : actions[i].fallback;
        }
        return resolved;
    }();
    return s_keys.data();
}

/* Whether the on-screen controls drive as the keyboard they are, which is what
 * the launcher binds them as when no pad has the first slot (NFS_TOUCH_DRIVE,
 * ControlProfile.driveWith).  Then the game reads those keys itself, steers
 * them its own way and can record and replay a race driven on them, and none of
 * the folding below belongs: it would put the same press on the axes as well,
 * and the game would be driven twice over. */
static bool touchDrivesAsKeys()
{
    static const bool s_keys = []() {
        const char* how = SDL_getenv("NFS_TOUCH_DRIVE");
        return how && SDL_strcmp(how, "keys") == 0;
    }();
    return s_keys;
}

/* Whether the touch overlay's steering buttons are what steers player one, for
 * Gamepad::touchSteering(): set while one of them is held, cleared once the
 * pad steers the slot's axis itself, left alone while nothing steers -- so the
 * wheel a button let go of still comes back to the centre the same way. */
static bool s_touchSteering = false;
/* How far off the centre the pad has to steer to count, a quarter of the
 * range: a stick resting a little off-centre must not take steering back. */
static const int kPadSteerThreshold = 8192;

/* Larger magnitude wins rather than a sum, so a stick resting off-centre
 * cannot cancel a finger or a button asking for full lock, and no two sources
 * can push an axis past its range. */
static void blendAxis(GamepadState& state, x86::reg32 axis, int value)
{
    if (std::abs(value) > std::abs(int(state.axes[axis])))
        state.axes[axis] = x86::sreg16(value);
}

/* What a DirectInput driver did with an axis before the game saw it, on a
 * value measured from the centre: nothing inside the dead zone, the far end
 * from the saturation point on, and a straight line between the two, so the
 * end of the dead zone is not a jump.  Left alone at the defaults, the value
 * stays exactly as read.
 *
 * A saturation at or inside the dead zone is not applied.  DirectInput would
 * make the axis a switch, but the game's Dead Zone screen cannot ask for one:
 * its two handles always stay a tenth of the travel apart (sub_442ef0).  What
 * does ask for one is every config.dat written while GetProperty answered
 * nothing: the game saved the stack garbage it read back as "saturation 0"
 * (100 in the file), and the launcher took that for the game's default
 * (ControlProfile).  It sends it again at every start (sub_472b60). */
static int shapeAxis(int value, const Gamepad::AxisResponse& response)
{
    if (response.deadZone == 0 && (response.saturation >= 10000 || response.saturation == 0))
        return value;
    const int full = 32767;
    const int deadZone = int(response.deadZone) * full / 10000;
    const int saturation = response.saturation > response.deadZone
        ? int(response.saturation) * full / 10000 : full;
    const int magnitude = std::min(std::abs(value), full);
    int shaped;
    if (magnitude <= deadZone)
        shaped = 0;
    else if (magnitude >= saturation)
        shaped = full;
    else
        shaped = (magnitude - deadZone) * full / (saturation - deadZone);
    return value < 0 ? -shaped : shaped;
}

Gamepad::AxisResponse Gamepad::axisResponse(x86::reg32 axis) const
{
    return axis < kDirectInputAxes ? m_axisResponse[axis] : AxisResponse();
}

void Gamepad::setAxisResponse(x86::reg32 axis, const AxisResponse& response)
{
    if (axis < kDirectInputAxes)
        m_axisResponse[axis] = response;
}

/* ----------------------------------------------------------------------
 * Buttons keep their launcher mappings unless the player binds them natively
 * in the game's Controls screen. The menu uses its own confirm/back/arrows;
 * capture exposes buttons without sending those menu keys. */

namespace
{

struct ButtonBinding
{
    SDL_Keycode  key = SDLK_UNKNOWN;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;
    int          axis = -1;         // Gamepad::kAxisSteer or kAxisPedals
    int          direction = 0;     // -1 or +1 along it
};

struct PadButton
{
    const char*       name;         // the <BUTTON> in NFS_GAMEPAD<n>_<BUTTON>
    SDL_GamepadButton button;
    /* A trigger has no button (SDL_GAMEPAD_BUTTON_INVALID) and is read off
     * its axis instead (buttonDown). */
    SDL_GamepadAxis   trigger;
    /* Only for a variable that is not set at all -- a build without the
     * launcher.  The launcher's own defaults, GamepadButtons.java. */
    const char*       defaults[Gamepad::kSlotCount];
    const char*       menu;         // the same, for NFS_GAMEPAD<n>_<BUTTON>_UI
};

const PadButton s_padButtons[] =
{
    { "SOUTH",          SDL_GAMEPAD_BUTTON_SOUTH,          SDL_GAMEPAD_AXIS_INVALID,       { "B",      "E"      }, "Return" },
    { "EAST",           SDL_GAMEPAD_BUTTON_EAST,           SDL_GAMEPAD_AXIS_INVALID,       { "Space",  "D"      }, "Escape" },
    { "WEST",           SDL_GAMEPAD_BUTTON_WEST,           SDL_GAMEPAD_AXIS_INVALID,       { "S",      "P"      }, ""       },
    { "NORTH",          SDL_GAMEPAD_BUTTON_NORTH,          SDL_GAMEPAD_AXIS_INVALID,       { "C",      "Q"      }, ""       },
    { "LEFT_SHOULDER",  SDL_GAMEPAD_BUTTON_LEFT_SHOULDER,  SDL_GAMEPAD_AXIS_INVALID,       { "Z",      "G"      }, ""       },
    { "RIGHT_SHOULDER", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, SDL_GAMEPAD_AXIS_INVALID,       { "A",      "F"      }, ""       },
    { "LEFT_STICK",     SDL_GAMEPAD_BUTTON_LEFT_STICK,     SDL_GAMEPAD_AXIS_INVALID,       { "H",      "W"      }, ""       },
    { "RIGHT_STICK",    SDL_GAMEPAD_BUTTON_RIGHT_STICK,    SDL_GAMEPAD_AXIS_INVALID,       { "L",      "Y"      }, ""       },
    { "BACK",           SDL_GAMEPAD_BUTTON_BACK,           SDL_GAMEPAD_AXIS_INVALID,       { "R",      "X"      }, "" },
    { "START",          SDL_GAMEPAD_BUTTON_START,          SDL_GAMEPAD_AXIS_INVALID,       { "Escape", "Escape" }, "" },
    { "DPAD_UP",        SDL_GAMEPAD_BUTTON_DPAD_UP,        SDL_GAMEPAD_AXIS_INVALID,       { "Up",     "Up"     }, "Up"     },
    { "DPAD_DOWN",      SDL_GAMEPAD_BUTTON_DPAD_DOWN,      SDL_GAMEPAD_AXIS_INVALID,       { "Down",   "Down"   }, "Down"   },
    { "DPAD_LEFT",      SDL_GAMEPAD_BUTTON_DPAD_LEFT,      SDL_GAMEPAD_AXIS_INVALID,       { "Left",   "Left"   }, "Left"   },
    { "DPAD_RIGHT",     SDL_GAMEPAD_BUTTON_DPAD_RIGHT,     SDL_GAMEPAD_AXIS_INVALID,       { "Right",  "Right"  }, "Right"  },
    /* Nothing by default, in a race or a menu: the triggers are the pedals'
     * axis, and only a pad set to Digital has them send keys. */
    { "LEFT_TRIGGER",   SDL_GAMEPAD_BUTTON_INVALID,        SDL_GAMEPAD_AXIS_LEFT_TRIGGER,  { "",       ""       }, ""       },
    { "RIGHT_TRIGGER",  SDL_GAMEPAD_BUTTON_INVALID,        SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, { "",       ""       }, ""       },
};
constexpr size_t kPadButtons = SDL_arraysize(s_padButtons);

/* A trigger counts as held from a third of its travel, and as let go only
 * below a sixth: a finger resting near the point cannot chatter the key. */
const Sint16 kTriggerDown = 32767 / 3;
const Sint16 kTriggerUp = 32767 / 6;

bool buttonDown(SDL_Gamepad* pad, const PadButton& button, bool held)
{
    if (button.button != SDL_GAMEPAD_BUTTON_INVALID)
        return SDL_GetGamepadButton(pad, button.button);
    return SDL_GetGamepadAxis(pad, button.trigger) > (held ? kTriggerUp : kTriggerDown);
}

// A face-key report must not hide directions that arrive only through SDL.
// Once Android reports a direction, its whole D-pad group becomes authoritative
// so delayed or conflicting SDL direction reports cannot generate a second press.
bool automaticPhysicalButton(const Slot& source, x86::reg32 androidState, unsigned index, bool held)
{
    const bool android = (androidState & (1u << index)) != 0;
    const bool dpad = index >= 10 && index <= 13;
    if (androidState & (dpad ? kAndroidDpadRoute : kAndroidRoute)) {
        if (index < 14) return android;
        // Triggers can be analog-only, digital-only, or reported both ways.
        return android || (source.gamepad && buttonDown(source.gamepad, s_padButtons[index], held));
    }
    if (source.gamepad) return buttonDown(source.gamepad, s_padButtons[index], held);
    bool raw = source.handle && index < unsigned(SDL_GetNumJoystickButtons(source.handle))
        && SDL_GetJoystickButton(source.handle, int(index));
    // SDL hats are digital D-pads too, even on an unmapped joystick. Report
    // the same four virtual buttons for navigation and in-game capture.
    if (dpad && source.handle && SDL_GetNumJoystickHats(source.handle) > 0) {
        static constexpr Uint8 directions[] = { SDL_HAT_UP, SDL_HAT_DOWN, SDL_HAT_LEFT, SDL_HAT_RIGHT };
        raw = raw || (SDL_GetJoystickHat(source.handle, 0) & directions[index - 10]);
    }
    return raw;
}

// Profiles override only the requested functions, independent of SDL's database.
bool physicalButton(const Slot& source, x86::reg32 androidState, unsigned index, bool held)
{
    const unsigned slot=unsigned(&source-s_slots);
    const auto profile=s_controllerProfile[slot].load();
    const auto context=Gamepad::Context(s_context.load());
    const bool menu=context==Gamepad::Context::Menu || context==Gamepad::Context::Pause;
    const int assigned=controllerprofile::button(profile,index,menu);
    if(assigned>=0)return assigned!=0;
    return automaticPhysicalButton(source,androidState,index,held);
}

int menuAxis(const Slot& slot, int axis)
{
    if (slot.gamepad)
        return SDL_GetGamepadAxis(slot.gamepad, axis ? SDL_GAMEPAD_AXIS_LEFTY : SDL_GAMEPAD_AXIS_LEFTX);
    return slot.handle && SDL_GetNumJoystickAxes(slot.handle) > axis
        ? SDL_GetJoystickAxis(slot.handle, axis) : 0;
}

ButtonBinding parseBinding(const char* value)
{
    ButtonBinding binding;
    if (!value || !*value)
        return binding;
    static const struct { const char* name; int axis; int direction; } s_axisActions[] =
    {
        { "axis:steer_left",  int(Gamepad::kAxisSteer),  -1 },
        { "axis:steer_right", int(Gamepad::kAxisSteer),  +1 },
        { "axis:accelerate",  int(Gamepad::kAxisPedals), -1 },
        { "axis:brake",       int(Gamepad::kAxisPedals), +1 },
    };
    for (const auto& action : s_axisActions)
    {
        if (SDL_strcasecmp(value, action.name) == 0)
        {
            binding.axis = action.axis;
            binding.direction = action.direction;
            return binding;
        }
    }
    binding.key = SDL_GetKeyFromName(value);
    if (binding.key != SDLK_UNKNOWN)
        binding.scancode = SDL_GetScancodeFromKey(binding.key, nullptr);
    if (binding.scancode == SDL_SCANCODE_UNKNOWN)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "gamepad: no key called \"%s\"", value);
        binding.key = SDLK_UNKNOWN;
    }
    return binding;
}

/* What is on the screen, as the game layer sees it (Gamepad::context): a race
 * being driven, or a menu -- which a replay counts as, since nobody is driving
 * one either.  A button means one thing while driving and another outside it,
 * the way the on-screen controls have two layouts, and from the same signal. */


/* Both meanings of every button of every slot: the racing one the launcher
 * sets (NFS_GAMEPAD<n>_<BUTTON>) and the one a menu and a replay get
 * (..._UI), which the launcher fixes -- the lower face button confirms, the
 * right one goes back, the D-pad moves the highlight, the rest say nothing. */
const ButtonBinding& buttonBinding(x86::reg32 slot, size_t button, Gamepad::Context context)
{
    static const auto s_bindings = []() {
        std::array<std::array<std::array<ButtonBinding, kPadButtons>, 2>, Gamepad::kSlotCount> table;
        for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
        {
            std::string summary;
            for (size_t i = 0; i < kPadButtons; ++i)
            {
                char variable[72];
                SDL_snprintf(variable, sizeof(variable), "NFS_GAMEPAD%u_%s",
                             unsigned(slot) + 1, s_padButtons[i].name);
                // Unset means the default; set but empty means nothing.
                const char* value = SDL_getenv(variable);
                if (!value)
                    value = s_padButtons[i].defaults[slot];
                table[slot][0][i] = parseBinding(value);
                SDL_snprintf(variable, sizeof(variable), "NFS_GAMEPAD%u_%s_UI",
                             unsigned(slot) + 1, s_padButtons[i].name);
                const char* menu = SDL_getenv(variable);
                if (!menu)
                    menu = s_padButtons[i].menu;
                table[slot][1][i] = parseBinding(menu);
                summary += ' ';
                summary += s_padButtons[i].name;
                summary += '=';
                summary += value;
                if (*menu)
                {
                    summary += '/';
                    summary += menu;
                }
            }
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "gamepad slot %u buttons (race/menu):%s",
                        unsigned(slot), summary.c_str());
        }
        return table;
    }();
    return s_bindings[slot][context == Gamepad::Context::Race ? 0 : 1][button];
}

/* How many held buttons, across both pads, are keeping each key down.  Two
 * pads can share a key -- both D-pads send the arrows -- and the key must stay
 * down until the last of them lets go. */
Uint8 s_keyHolders[SDL_SCANCODE_COUNT];

void sendKey(const ButtonBinding& binding, bool down)
{
    if (binding.scancode == SDL_SCANCODE_UNKNOWN)
        return;
    Uint8& holders = s_keyHolders[binding.scancode];
    if (down ? holders++ != 0 : (holders == 0 || --holders != 0))
        return;
    SDL_Event event;
    SDL_zero(event);
    event.type = down ? SDL_EVENT_KEY_DOWN : SDL_EVENT_KEY_UP;
    event.key.timestamp = SDL_GetTicksNS();
    event.key.scancode = binding.scancode;
    event.key.key = binding.key;
    event.key.down = down;
    SDL_PushEvent(&event);
}

struct SlotButtons
{
    SDL_JoystickID pad = 0;
    bool pauseLatched = false, pauseSent = false;
    x86::reg32 pauseSources = 0, pauseMenuSources = 0;
    bool           held[kPadButtons] = {};
    Uint64         repeatAt[kPadButtons] = {};
    bool           sent[kPadButtons] = {};    // its key went down and has not come up
    /* Which key that was.  A button held across the end of a race sends one
     * key and would otherwise be let go of by another, leaving the first one
     * down for good. */
    ButtonBinding  sentAs[kPadButtons] = {};
};
SlotButtons s_slotButtons[Gamepad::kSlotCount];

std::atomic<bool> s_gameKeysMuted{false};

/* A key a muted pad keeps quiet: all of them but Escape, which the game never
 * binds to a car -- it is the pause menu, and a pad keeps its way into that. */
bool muteable(const ButtonBinding& binding)
{
    return binding.scancode != SDL_SCANCODE_UNKNOWN && binding.scancode != SDL_SCANCODE_ESCAPE;
}

void updateButtonKeys()
{
    const Gamepad::Context context = Gamepad::Context(s_context.load(std::memory_order_relaxed));
    // The first frame resolves and logs every binding, before anything is pressed.
    buttonBinding(0, 0, context);
    const bool muted = s_gameKeysMuted.load(std::memory_order_relaxed);
    static const ButtonBinding escape = parseBinding("Escape");
    for (x86::reg32 slot = 0; slot < Gamepad::kSlotCount; ++slot)
    {
        SlotButtons& buttons = s_slotButtons[slot];
        const Slot& source = s_slots[slot];
        /* A pad that leaves its slot -- unplugged, or handed to the other
         * player -- lets go of whatever it held, or the key would stay down. */
        if (buttons.pad != source.id)
        {
            for (size_t i = 0; i < kPadButtons; ++i)
            {
                if (buttons.sent[i])
                    sendKey(buttons.sentAs[i], false);
                buttons.held[i] = buttons.sent[i] = false;
            }
            if (buttons.pauseSent) sendKey(escape, false);
            buttons.pauseSent = buttons.pauseLatched = false;
            buttons.pauseSources = buttons.pauseMenuSources = s_pauseConsumed[slot] = 0;
            buttons.pad = source.id;
        }
        const x86::reg32 androidState = s_androidButtons[slot].load();
        x86::reg32 physical = 0;
        for (unsigned i = 0; i < kPadButtons; ++i)
            if (physicalButton(source, androidState, i, (s_physicalButtons[slot] & (1u << i)) != 0)) physical |= 1u << i;
        s_physicalButtons[slot] = physical;
        const bool capture = context == Gamepad::Context::Capture;
        s_captureGate[slot].sample(physical, capture);
        const x86::reg32 native = s_nativeButtons[slot].load();
        // Evaluate physical sources before menu remapping and before in-game
        // bindings suppress launcher keys. Never combine two controllers.
        const auto pause = s_racePause[slot].load();
        const int firstIndex = int((pause >> 20) & 31) - 1;
        const int secondIndex = int((pause >> 25) & 31) - 1;
        auto pauseHeld = [&](int index, unsigned bit) {
            return (pause & (1ull << bit)) ||
                (index >= 0 && index < int(kPadButtons) &&
                 automaticPhysicalButton(source, androidState, unsigned(index),
                     buttons.pauseLatched));
        };
        const bool firstHeld = pauseHeld(firstIndex, 17);
        const bool secondHeld = pauseHeld(secondIndex, 18);
        if (buttons.pauseSent) {
            sendKey(escape, false);
            buttons.pauseSent = false;
        }
        if (buttons.pauseLatched && !firstHeld && !secondHeld)
            buttons.pauseLatched = false;
        if (!buttons.pauseLatched && (pause & (1ull << 16)) &&
            context == Gamepad::Context::Race && firstHeld && secondHeld) {
            buttons.pauseLatched = true;
            buttons.pauseSources = x86::reg32(pause & 0xffff);
            buttons.pauseMenuSources = x86::reg32((pause >> 32) & 0xffff);
            buttons.pauseSent = true;
        }
        // Keep the combination out of the pause menu until BOTH controls are
        // released, including any menu actions mapped to those controls.
        s_pauseConsumed[slot] = buttons.pauseLatched ? buttons.pauseSources : 0;
        const auto consumed = s_pauseConsumed[slot] |
            (buttons.pauseLatched && context != Gamepad::Context::Race ? buttons.pauseMenuSources : 0);

        for (size_t i = 0; i < kPadButtons; ++i)
        {
            const ButtonBinding& binding = buttonBinding(slot, i, context);
            const bool suppressed = capture || (consumed & (1u << i)) ||
                (context == Gamepad::Context::Race && ((native & (1u << i)) ||
                    ((pause & (1ull << 16)) && (int(i) == firstIndex || int(i) == secondIndex) &&
                     binding.scancode == SDL_SCANCODE_ESCAPE)));
            /* A key that is down goes up as soon as it stops being what this
             * button means -- muted, or a race gave way to a menu under a
             * thumb that never moved. */
            if (buttons.sent[i]
                && (suppressed || (muted && muteable(buttons.sentAs[i])) || buttons.sentAs[i].scancode != binding.scancode))
            {
                sendKey(buttons.sentAs[i], false);
                buttons.sent[i] = false;
            }
            bool down = (physical & (1u << i)) != 0;
            if (context == Gamepad::Context::Menu || context == Gamepad::Context::Pause) {
                const char* name = s_padButtons[i].name;
                if (SDL_strncmp(name, "DPAD_", 5) == 0 &&
                    controllerprofile::allowMenuAxis(s_controllerProfile[slot].load(),unsigned(i-10))) {
                    const bool horizontal = i == 12 || i == 13;
                    int value = menuAxis(source, horizontal ? 0 : 1);
                    if (i == 10 || i == 12) value = -value;
                    down = down || padpolicy::direction(value, buttons.held[i]);
                }
            }
            const bool changed = down != buttons.held[i];
            buttons.held[i] = down;
            if (down && !buttons.sent[i] && changed && !suppressed && !(muted && muteable(binding)))
            {
                sendKey(binding, true);
                buttons.sentAs[i] = binding;
                buttons.sent[i] = true;
                buttons.repeatAt[i] = SDL_GetTicks() + 400;
            }
            else if (down && buttons.sent[i] && !suppressed
                     && (context == Gamepad::Context::Menu || context == Gamepad::Context::Pause)
                     && i >= 10 && i <= 13 && SDL_GetTicks() >= buttons.repeatAt[i]) {
                SDL_Event event{};
                event.type = SDL_EVENT_KEY_DOWN;
                event.key.timestamp = SDL_GetTicksNS();
                event.key.scancode = binding.scancode;
                event.key.key = binding.key;
                event.key.down = true;
                event.key.repeat = true;
                SDL_PushEvent(&event);
                buttons.repeatAt[i] = SDL_GetTicks() + 120;
            }
            else if (!down && buttons.sent[i])
            {
                sendKey(buttons.sentAs[i], false);
                buttons.sent[i] = false;
            }
        }
        if (buttons.pauseSent) sendKey(escape, true);
    }
}

}

void Gamepad::controllerProfile(unsigned slot,std::uint64_t state) {
    if(slot<kSlotCount)s_controllerProfile[slot].store(state);
}

void Gamepad::racePause(unsigned slot,std::uint64_t state) {
    if(slot<kSlotCount)s_racePause[slot].store(state);
}


void Gamepad::androidButton(unsigned slot, int button, bool down)
{
    if (slot >= kSlotCount) return;
    if (button < 0) { s_androidButtons[slot].fetch_and(kAndroidRoutes); return; }
    if (button >= 16) return;
    const auto routes = kAndroidRoute | (button >= 10 && button <= 13 ? kAndroidDpadRoute : 0);
    if (down) s_androidButtons[slot].fetch_or(routes | (1u << button));
    else {
        // One atomic state carries both ownership and held bits.
        auto previous = s_androidButtons[slot].load();
        while (!s_androidButtons[slot].compare_exchange_weak(previous,
                (previous | routes) & ~(1u << button))) {}
    }
}
void Gamepad::nativeButtons(unsigned slot, x86::reg32 mask)
{
    if (slot < kSlotCount) s_nativeButtons[slot].store(mask);
}
void Gamepad::muteGameKeys(bool muted)
{
    s_gameKeysMuted.store(muted, std::memory_order_relaxed);
}

void Gamepad::context(Context context)
{
    s_context.store(int(context), std::memory_order_relaxed);
}

Gamepad::Gamepad(x86::reg32 gamepadIndex)
    :   m_slot(gamepadIndex)
{
    refreshSlots();
    SDL_SetJoystickEventsEnabled(false);
}

Gamepad::~Gamepad()
{
    forcefeedback::detach(this);
    /* The slot outlives the device object: the joystick handle belongs to the
     * slot table, which survives the game releasing and recreating its
     * devices. */
}

x86::reg32 Gamepad::getCount()
{
    return kSlotCount;
}

/* The shape a slot reports never changes, whatever is or is not plugged in.
 * The game keeps a description of every device in config.dat and compares it
 * with what it finds at each start; on any difference it throws its control
 * bindings away and generates new ones.  So a slot is always the same two
 * axes and sixteen buttons, matching ControlProfile.java. Old settings files
 * are migrated before startup without replacing the player's bindings. */
x86::reg32 Gamepad::getButtonCount() const
{
    return 16;
}

x86::reg32 Gamepad::getAxesCount() const
{
    return 2;
}

bool Gamepad::touchSteering()
{
    return s_touchSteering || (touchinput::held() & 3u)!=0;
}

GamepadState Gamepad::getState() const
{
    // The original binding routine waits for button-up before drawing again.
    // HIDAPI pads must keep receiving reports during that wait too.
    if (Context(s_context.load()) == Context::Capture) SDL_UpdateJoysticks();
    GamepadState result;
    memset(&result, 0, sizeof(result));

    /* A pad is read by polling its live state.  SDL's joystick and gamepad
     * *events* are no use here: the constructor turns joystick events off
     * (the game enumerates its DirectInput devices before a frame is drawn),
     * and SDL3 derives gamepad events from joystick events, so neither ever
     * arrives -- but the state queried below stays current regardless. */
    /* The game's dead zone and saturation go on what the pad itself reports,
     * before the buttons and the touch overlay are blended in: those only ever
     * ask for the centre or full travel, which no dead zone changes anyway. */
    const AxisResponse& steerResponse = m_axisResponse[kAxisSteer];
    const AxisResponse& pedalResponse = m_axisResponse[kAxisPedals];
    const Slot* slot = m_slot < kSlotCount ? &s_slots[m_slot] : nullptr;
    if (slot && slot->gamepad)
    {
        result.axes[kAxisSteer] = x86::sreg16(shapeAxis(
            SDL_GetGamepadAxis(slot->gamepad, SDL_GAMEPAD_AXIS_LEFTX), steerResponse));
        /* Both triggers share one axis, the way combined pedals did on wheels
         * of the time: the right trigger pulls it up, towards accelerate, the
         * left one down, towards brake.  SDL's standard layout rests a trigger
         * at 0 and takes it to 32767, so the difference always fits -- and
         * pressing both cancels out, as those pedals did.  Each trigger is
         * half of that axis, from its centre to one end, so the pedals' dead
         * zone goes on each before they are combined: on the difference it
         * would swallow a light press of one whenever the other rested on its
         * trigger too. */
        const x86::reg32 native = s_nativeButtons[m_slot].load() | s_pauseConsumed[m_slot];
        result.axes[kAxisPedals] = x86::sreg16(
              ((native & (1u << 14)) ? 0 : shapeAxis(SDL_GetGamepadAxis(slot->gamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER), pedalResponse))
            - ((native & (1u << 15)) ? 0 : shapeAxis(SDL_GetGamepadAxis(slot->gamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER), pedalResponse)));
        // Axis-only D-pads and left-stick Y must reach the same game Y axis
        // in menus, capture and racing. Keep the existing combined triggers;
        // the largest magnitude wins instead of adding or cancelling inputs.
        blendAxis(result, kAxisPedals, shapeAxis(
            SDL_GetGamepadAxis(slot->gamepad, SDL_GAMEPAD_AXIS_LEFTY), pedalResponse));
        /* A button put on an axis steers or works a pedal, which is a racing
         * thing whatever else is on the screen. */
        for (size_t i = 0; i < kPadButtons; ++i)
        {
            const ButtonBinding& binding = buttonBinding(m_slot, i, Context::Race);
            if (binding.axis >= 0 && !((s_nativeButtons[m_slot].load() | s_pauseConsumed[m_slot]) & (1u << i))
                && physicalButton(*slot, s_androidButtons[m_slot].load(), unsigned(i), false))
                blendAxis(result, x86::reg32(binding.axis), binding.direction * 32767);
        }
    }
    else if (SDL_Joystick* pad = joystick())
    {
        /* A device SDL has no gamepad mapping for: its first two axes, where
         * a plain joystick keeps them. */
        const int axes = SDL_GetNumJoystickAxes(pad);
        if (axes > 0)
            result.axes[kAxisSteer] = x86::sreg16(shapeAxis(SDL_GetJoystickAxis(pad, 0), steerResponse));
        if (axes > 1)
            result.axes[kAxisPedals] = x86::sreg16(shapeAxis(SDL_GetJoystickAxis(pad, 1), pedalResponse));
    }

    if (m_slot < kSlotCount) {
        const Context mode = Context(s_context.load());
        const x86::reg32 androidState = s_androidButtons[m_slot].load();
        x86::reg32 physical = 0;
        if (slot) for (unsigned i = 0; i < kPadButtons; ++i)
            if (physicalButton(*slot, androidState, i, (s_physicalButtons[m_slot] & (1u << i)) != 0)) physical |= 1u << i;
        // The binding screen polls between swaps too. Do not wait for update().
        const auto usable = s_captureGate[m_slot].sample(physical, mode == Context::Capture);
        if (mode == Context::Capture) {
            result.buttons = usable;
            // A configured axis direction is captured as its canonical D-pad
            // button, rather than racing the original analog axis for capture.
            if(controllerprofile::axisHeld(s_controllerProfile[m_slot].load()))
                for(auto& axis:result.axes)axis=0;
        }
        else if (mode == Context::Race) result.buttons = usable & s_nativeButtons[m_slot].load() & ~s_pauseConsumed[m_slot];
    }

    if (m_slot == 0 && !touchDrivesAsKeys())
    {
        const bool* keys = SDL_GetKeyboardState(nullptr);
        const SDL_Scancode* touch = touchAxisKeys();
        auto held = [keys, touch](int action) {
            return touch[action] != SDL_SCANCODE_UNKNOWN && keys[touch[action]];
        };
        const int touchSteer = int(held(TOUCH_STEER_RIGHT)) - int(held(TOUCH_STEER_LEFT));
        if (touchSteer != 0)
            s_touchSteering = true;
        else if (std::abs(int(result.axes[kAxisSteer])) > kPadSteerThreshold)
            s_touchSteering = false;
        blendAxis(result, kAxisSteer, 32767 * touchSteer);
        blendAxis(result, kAxisPedals,
                  32767 * (int(held(TOUCH_BRAKE)) - int(held(TOUCH_ACCELERATE))));
    }
    return result;
}


}


#ifdef __ANDROID__
namespace {
// SDL supplies an attached JNIEnv on every calling thread. No global Activity refs.
void androidForceFeedback(x86::reg32 slot,float strength,const win32::Gamepad::RumbleDetail& detail) {
    JNIEnv* env=static_cast<JNIEnv*>(SDL_GetAndroidJNIEnv());
    jobject activity=static_cast<jobject>(SDL_GetAndroidActivity());
    if(!env||!activity)return;
    jclass cls=env->GetObjectClass(activity);
    jmethodID method=env->GetMethodID(cls,"onForceFeedback","(IFFFFFF)V");
    if(method)env->CallVoidMethod(activity,method,jint(slot),jfloat(strength),jfloat(detail.impact),
                                  jfloat(detail.road),jfloat(detail.roadHz),jfloat(detail.engine),jfloat(detail.engineHz));
    if(env->ExceptionCheck())env->ExceptionClear();
    env->DeleteLocalRef(cls);env->DeleteLocalRef(activity);
}
}

#endif
bool win32::Gamepad::hasForceFeedback() const {
#ifdef __ANDROID__
    /* Yes, for both slots, whatever is plugged in.  A pad's vibration belongs
     * to the game now -- Options -> Controllers -> Force Feedback, with Stick
     * Volume at zero as the off switch -- and the game asks this once, at
     * startup: an answer that followed the hardware would leave a pad
     * connected later without force feedback for the whole session.  The
     * phone's motor keeps its own switch and strength in the launcher, applied
     * in GameHaptics, and an effect with no motor behind it is dropped there. */
    return true;
#else
    SDL_Joystick* pad=joystick();
    return pad&&SDL_GetBooleanProperty(SDL_GetJoystickProperties(pad),SDL_PROP_JOYSTICK_CAP_RUMBLE_BOOLEAN,false);
#endif
}
void win32::Gamepad::rumble(float strength) {
    rumble(strength,RumbleDetail());
}
void win32::Gamepad::rumble(float strength,const RumbleDetail& detail) {
#ifdef __ANDROID__
    /* Which motors a slot drives is decided in GameHaptics, which owns both
     * the enable switches and the two strength sliders: slot 0 reaches the
     * phone and the first pad, slot 1 the second pad. */
    androidForceFeedback(m_slot,strength,detail);
#else
    (void)detail;
    SDL_Joystick* pad=joystick();
    if(pad)SDL_RumbleJoystick(pad,Uint16(strength*65535),Uint16(strength*65535),100);
#endif
}
void win32::Gamepad::phoneTick(float turn) {
#ifdef __ANDROID__
    JNIEnv* env=static_cast<JNIEnv*>(SDL_GetAndroidJNIEnv());
    jobject activity=static_cast<jobject>(SDL_GetAndroidActivity());
    if(!env||!activity)return;
    jclass cls=env->GetObjectClass(activity);
    jmethodID method=env->GetMethodID(cls,"onPhoneTick","(F)V");
    if(method)env->CallVoidMethod(activity,method,jfloat(turn));
    if(env->ExceptionCheck())env->ExceptionClear();
    env->DeleteLocalRef(cls);env->DeleteLocalRef(activity);
#else
    (void)turn;
#endif
}

#ifdef __ANDROID__
extern "C" JNIEXPORT void JNICALL
Java_dev_nfs3hp_port_TouchControlsOverlay_nativeTouchAction(JNIEnv*,jclass,jint action,jboolean down){
    win32::touchinput::set(unsigned(action),down==JNI_TRUE);
}
#endif



#ifdef __ANDROID__
extern "C" JNIEXPORT void JNICALL
Java_dev_nfs3hp_port_NFS3Activity_nativeControllerProfile(JNIEnv*,jclass,jint slot,jlong state){
    win32::Gamepad::controllerProfile(unsigned(slot),std::uint64_t(state));
}
#endif

#ifdef __ANDROID__
extern "C" JNIEXPORT void JNICALL
Java_dev_nfs3hp_port_NFS3Activity_nativeRacePause(JNIEnv*,jclass,jint slot,jlong state){
    win32::Gamepad::racePause(unsigned(slot),std::uint64_t(state));
}
#endif
