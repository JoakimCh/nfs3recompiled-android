#include <lib/gamepad.h>
#include <lib/gamepad_policy.h>
#include <lib/touch_input.h>
#include <lib/forcefeedback.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
namespace win32 {
GenericResource::GenericResource() : m_resourceIndex(0) {}
GenericResource::~GenericResource() {}
namespace forcefeedback { void update() {} void detach(Gamepad*) {} }
}
using win32::Gamepad;
struct Key { SDL_Keycode key; bool down, repeat; };
std::vector<Key> keys() {
    std::vector<Key> out; SDL_Event e;
    while (SDL_PollEvent(&e)) if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)
        out.push_back({e.key.key, e.key.down, e.key.repeat});
    return out;
}
void expect(SDL_Keycode key, bool down, bool repeat = false) {
    auto events = keys();
    if(events.size()!=1) { std::cerr << "expected key " << key << " down=" << down << " repeat=" << repeat << ", got " << events.size() << " events\n"; for(const auto& e:events)std::cerr << e.key << ":" << e.down << ":" << e.repeat << "\n"; }
    assert(events.size() == 1);
    assert(events[0].key == key && events[0].down == down && events[0].repeat == repeat);
}
int main() {
    win32::touchinput::active(true);win32::touchinput::set(2,true);
    assert(!Gamepad::touchSteering());win32::touchinput::set(0,true);assert(Gamepad::touchSteering());
    win32::touchinput::set(0,false);win32::touchinput::set(1,true);assert(Gamepad::touchSteering());
    win32::touchinput::active(false);assert(!Gamepad::touchSteering());

    using namespace win32::padpolicy;
    assert(!direction(16000,false) && direction(16001,false));
    assert(direction(10001,true) && !direction(10000,true));
    assert(boundButton(0x10000302,1) == 8 && boundButton(0x10000302,0) == 0);
    assert(boundButton(0x0080ff01,0) == 0 && boundButton(0x10001002,1) == 0);
    std::map<unsigned, unsigned> mem;
    const unsigned menu = 0x6040d0, item = 0x604ee0 + 23 * 0xbc;
    mem[menu + 0x18] = 20; mem[menu + 0x1a] = 3;
    mem[item + 0x30] = 0x43cf80; mem[item + 0x3c] = 0;
    auto word = [&](unsigned p) { return mem[p]; };
    auto half = [&](unsigned p) { return std::int16_t(mem[p]); };
    assert(controlsCapture(menu, word, half));
    mem[item + 0x3c] = 0xffff; assert(!controlsCapture(menu, word, half));
    mem[item + 0x3c] = 0; mem[item + 0x30] = 0x43d000; assert(!controlsCapture(menu, word, half));
    assert(!controlsCapture(0,word,half) && !controlsCapture(menu+1,word,half));
    mem[item + 0x30] = 0x43cf80; mem[menu + 0x1a] = 100; assert(!controlsCapture(menu,word,half));
    assert(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD));
    SDL_VirtualJoystickDesc desc{}; SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD; desc.naxes = 6; desc.nbuttons = 15;
    desc.axis_mask = 0x3f; desc.button_mask = 0x7fff; desc.name = "TV test pad";
    auto id = SDL_AttachVirtualJoystick(&desc); assert(id);
    auto joy = SDL_OpenJoystick(id); assert(joy);
    SDL_SetJoystickVirtualAxis(joy, 4, -32768); SDL_SetJoystickVirtualAxis(joy, 5, -32768);
    win32::Input::poll();
    Gamepad pad(0); Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    assert(pad.getButtonCount() == 16 && pad.getAxesCount() == 2);
    // X/Y D-pad menu movement, hysteresis, release, repeat and race isolation.
    SDL_SetJoystickVirtualAxis(joy,0,24000); Gamepad::update(); expect(SDLK_RIGHT,true);
    SDL_SetJoystickVirtualAxis(joy,0,12000); Gamepad::update(); assert(keys().empty());
    SDL_Delay(410); Gamepad::update(); expect(SDLK_RIGHT,true,true);
    SDL_SetJoystickVirtualAxis(joy,0,9000); Gamepad::update(); expect(SDLK_RIGHT,false);
    SDL_SetJoystickVirtualAxis(joy,1,-24000); Gamepad::update(); expect(SDLK_UP,true);
    Gamepad::context(Gamepad::Context::Race); Gamepad::update(); expect(SDLK_UP,false);
    assert(pad.getState().axes[Gamepad::kAxisPedals] == -24000);
    SDL_SetJoystickVirtualAxis(joy,1,24000); Gamepad::update(); keys();
    assert(pad.getState().axes[Gamepad::kAxisPedals] == 24000);
    Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
    assert(pad.getState().axes[Gamepad::kAxisPedals] == 24000);
    SDL_SetJoystickVirtualAxis(joy,1,-24000);
    assert(pad.getState().axes[Gamepad::kAxisPedals] == -24000);
    SDL_SetJoystickVirtualAxis(joy,1,0); Gamepad::update(); keys();
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    // An unmapped joystick still gets X/Y menus and first/second button A/B.
    SDL_VirtualJoystickDesc raw{}; SDL_INIT_INTERFACE(&raw);
    raw.type = SDL_JOYSTICK_TYPE_UNKNOWN; raw.naxes = 2; raw.nbuttons = 2; raw.name = "Unmapped TV pad";
    const auto rawId = SDL_AttachVirtualJoystick(&raw); assert(rawId && !SDL_IsGamepad(rawId));
    auto rawJoy = SDL_OpenJoystick(rawId); win32::Input::poll(); Gamepad::update(); keys();
    SDL_SetJoystickVirtualAxis(rawJoy,1,24000); Gamepad::update(); expect(SDLK_DOWN,true);
    SDL_SetJoystickVirtualAxis(rawJoy,1,0); Gamepad::update(); expect(SDLK_DOWN,false);
    SDL_SetJoystickVirtualButton(rawJoy,0,true); Gamepad::update(); expect(SDLK_RETURN,true);
    SDL_SetJoystickVirtualButton(rawJoy,0,false); Gamepad::update(); expect(SDLK_RETURN,false);
    SDL_SetJoystickVirtualButton(rawJoy,1,true); Gamepad::update(); expect(SDLK_ESCAPE,true);
    SDL_DetachVirtualJoystick(rawId); win32::Input::poll(); Gamepad::update(); expect(SDLK_ESCAPE,false);
    SDL_CloseJoystick(rawJoy);
    // Physical standardized A/B in menu.
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,true); Gamepad::update(); expect(SDLK_RETURN,true);
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,false); Gamepad::update(); expect(SDLK_RETURN,false);
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_EAST,true); Gamepad::update(); expect(SDLK_ESCAPE,true);
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_EAST,false); Gamepad::update(); expect(SDLK_ESCAPE,false);
    // Two pads holding the same menu key must share ownership correctly.
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    Gamepad::androidButton(0,0,true); Gamepad::update(); expect(SDLK_RETURN,true);
    Gamepad::androidButton(1,0,true); Gamepad::update(); assert(keys().empty());
    Gamepad::androidButton(0,0,false); Gamepad::update(); assert(keys().empty());
    Gamepad::androidButton(1,-1,false); Gamepad::update(); expect(SDLK_RETURN,false);
    // Mixed Android face buttons + SDL D-pad: a face-key report must not
    // disable directions delivered only through the joystick/gamepad path.
    std::cout << "Checking SDL D-pad after Android face reports\n" << std::flush;
    const SDL_GamepadButton directions[] = { SDL_GAMEPAD_BUTTON_DPAD_UP,
        SDL_GAMEPAD_BUTTON_DPAD_DOWN, SDL_GAMEPAD_BUTTON_DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT };
    const SDL_Keycode arrows[] = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
    for(unsigned d=0;d<4;++d) {
        Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
        SDL_SetJoystickVirtualButton(joy,directions[d],true); Gamepad::update(); expect(arrows[d],true);
        if(d==0) { SDL_Delay(410); Gamepad::update(); expect(arrows[d],true,true); }
        SDL_SetJoystickVirtualButton(joy,directions[d],false); Gamepad::update(); expect(arrows[d],false);
        Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
        SDL_SetJoystickVirtualButton(joy,directions[d],true);
        assert(pad.getState().buttons==(1u<<(10+d))); // capture can poll between swaps
        Gamepad::nativeButtons(0,1u<<(10+d)); Gamepad::context(Gamepad::Context::Race);
        Gamepad::update(); assert(keys().empty()); assert(pad.getState().buttons==(1u<<(10+d)));
        SDL_SetJoystickVirtualButton(joy,directions[d],false); Gamepad::update(); assert(pad.getState().buttons==0);
        Gamepad::nativeButtons(0,0);
    }
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    // A second player's unmapped joystick can report its D-pad as a hat,
    // including after that player's face buttons selected Android authority.
    {
        SDL_VirtualJoystickDesc hats{}; SDL_INIT_INTERFACE(&hats);
        hats.type=SDL_JOYSTICK_TYPE_UNKNOWN; hats.nbuttons=2; hats.nhats=1; hats.name="Raw hat test pad";
        auto hid=SDL_AttachVirtualJoystick(&hats); assert(hid && !SDL_IsGamepad(hid));
        auto hj=SDL_OpenJoystick(hid); assert(hj); win32::Input::poll(); Gamepad second(1);
        Gamepad::androidButton(1,0,false);
        const Uint8 hd[]={SDL_HAT_UP,SDL_HAT_DOWN,SDL_HAT_LEFT,SDL_HAT_RIGHT};
        for(unsigned d=0;d<4;++d) {
            Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
            SDL_SetJoystickVirtualHat(hj,0,hd[d]); Gamepad::update(); expect(arrows[d],true);
            SDL_SetJoystickVirtualHat(hj,0,SDL_HAT_CENTERED); Gamepad::update(); expect(arrows[d],false);
            Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
            SDL_SetJoystickVirtualHat(hj,0,hd[d]); assert(second.getState().buttons==(1u<<(10+d)));
            Gamepad::nativeButtons(1,1u<<(10+d)); Gamepad::context(Gamepad::Context::Race);
            Gamepad::update(); assert(keys().empty()); assert(second.getState().buttons==(1u<<(10+d)));
            assert(pad.getState().buttons==0); // second pad stays player two
            SDL_SetJoystickVirtualHat(hj,0,SDL_HAT_CENTERED); Gamepad::update(); assert(second.getState().buttons==0);
            Gamepad::nativeButtons(1,0);
        }
        Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
        SDL_SetJoystickVirtualHat(hj,0,SDL_HAT_LEFTUP);
        assert(second.getState().buttons==((1u<<10)|(1u<<12)));
        SDL_SetJoystickVirtualHat(hj,0,SDL_HAT_CENTERED); assert(second.getState().buttons==0);
        SDL_DetachVirtualJoystick(hid); win32::Input::poll(); Gamepad::update(); keys(); SDL_CloseJoystick(hj);
    }
    // Generic profile path, with no device/vendor-specific mapping repair.
    {
        Gamepad::context(Gamepad::Context::Menu);Gamepad::update();keys();
        const std::uint64_t dirs=15;
        for(unsigned d=0;d<4;d++) {
            Gamepad::controllerProfile(0,dirs);Gamepad::update();keys();
            Gamepad::controllerProfile(0,dirs|(1ull<<(8+d))|(1ull<<48));
            Gamepad::update();expect(arrows[d],true);Gamepad::update();assert(keys().empty());
            Gamepad::controllerProfile(0,dirs);Gamepad::update();expect(arrows[d],false);
            Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
            SDL_SetJoystickVirtualAxis(joy,0,24000);
            Gamepad::controllerProfile(0,dirs|(1ull<<(8+d))|(1ull<<48));
            assert(pad.getState().buttons==(1u<<(10+d)));
            assert(pad.getState().axes[Gamepad::kAxisSteer]==0);
            Gamepad::controllerProfile(0,dirs);SDL_SetJoystickVirtualAxis(joy,0,0);Gamepad::update();
            assert(pad.getState().buttons==0);Gamepad::context(Gamepad::Context::Menu);Gamepad::update();keys();
        }
        // Direction source A becomes only Up; the other slot stays idle.
        Gamepad second(1);
        Gamepad::controllerProfile(0,1ull|(1ull<<8)|(1ull<<16));
        Gamepad::androidButton(0,0,true);Gamepad::update();expect(SDLK_UP,true);
        Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
        Gamepad::androidButton(0,0,false);Gamepad::controllerProfile(0,1);Gamepad::update();keys();
        Gamepad::androidButton(0,0,true);Gamepad::controllerProfile(0,1ull|(1ull<<8)|(1ull<<16));
        assert(pad.getState().buttons==(1u<<10));assert(second.getState().buttons==0);
        Gamepad::androidButton(0,0,false);Gamepad::controllerProfile(0,0);Gamepad::update();keys();
        Gamepad::context(Gamepad::Context::Menu);Gamepad::update();keys();
        // An X-negative axis reassigned Up must not also send automatic Left.
        SDL_SetJoystickVirtualAxis(joy,0,-24000);
        Gamepad::controllerProfile(0,1ull|(1ull<<8)|(1ull<<48)|(1ull<<51));
        Gamepad::update();expect(SDLK_UP,true);
        SDL_SetJoystickVirtualAxis(joy,0,0);Gamepad::controllerProfile(0,1ull|(1ull<<51));Gamepad::update();expect(SDLK_UP,false);
        Gamepad::controllerProfile(0,0);Gamepad::update();keys();
        // B assigned Confirm and A assigned Back: no original/delayed key.
        const auto face=0x30ull|(1ull<<32)|(1ull<<33);
        Gamepad::controllerProfile(0,face);Gamepad::update();keys();
        Gamepad::androidButton(0,1,true);Gamepad::controllerProfile(0,face|(1ull<<12));
        Gamepad::update();expect(SDLK_RETURN,true);
        Gamepad::context(Gamepad::Context::Pause);Gamepad::update();assert(keys().empty());
        Gamepad::androidButton(0,1,false);Gamepad::controllerProfile(0,face);Gamepad::update();expect(SDLK_RETURN,false);
        Gamepad::androidButton(0,0,true);Gamepad::controllerProfile(0,face|(1ull<<13));Gamepad::update();expect(SDLK_ESCAPE,true);
        Gamepad::androidButton(0,0,false);Gamepad::controllerProfile(0,face);Gamepad::update();expect(SDLK_ESCAPE,false);
        // Menu assignments must not rename racing/remapping face buttons.
        Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
        Gamepad::androidButton(0,1,true);Gamepad::controllerProfile(0,face|(1ull<<12));
        assert(pad.getState().buttons==2);
        Gamepad::androidButton(0,1,false);Gamepad::controllerProfile(0,0);Gamepad::update();keys();
    }
    // A different, unknown pad with a deliberately incomplete SDL mapping.
    // Custom directions work without filling any SDL database entry.
    {
        SDL_VirtualJoystickDesc desc{};SDL_INIT_INTERFACE(&desc);desc.type=SDL_JOYSTICK_TYPE_GAMEPAD;
        desc.naxes=2;desc.nbuttons=19;desc.axis_mask=3;desc.button_mask=0x7ffff;desc.name="Unknown incomplete controller";
        auto id2=SDL_AttachVirtualJoystick(&desc);assert(id2);auto j2=SDL_OpenJoystick(id2);assert(j2);
        char guid[40];SDL_GUIDToString(SDL_GetJoystickGUIDForID(id2),guid,sizeof(guid));
        std::string partial=std::string(guid)+",Unknown incomplete controller,a:b0,b:b1,leftx:a0,lefty:a1,";
        assert(SDL_AddGamepadMapping(partial.c_str())>=0);
        auto gp=SDL_OpenGamepad(id2);assert(gp);SDL_SetJoystickVirtualButton(j2,12,true);SDL_UpdateJoysticks();
        assert(SDL_GetJoystickButton(j2,12) && !SDL_GetGamepadButton(gp,SDL_GAMEPAD_BUTTON_DPAD_DOWN));
        SDL_SetJoystickVirtualButton(j2,12,false);win32::Input::poll();Gamepad second(1);
        const auto defaultHats=15ull|(15ull<<53);
        for(unsigned d=0;d<4;d++) {
            Gamepad::context(Gamepad::Context::Menu);Gamepad::controllerProfile(1,defaultHats);Gamepad::update();keys();
            Gamepad::controllerProfile(1,defaultHats|(1ull<<(8+d)));Gamepad::update();expect(arrows[d],true);
            Gamepad::controllerProfile(1,defaultHats);Gamepad::update();expect(arrows[d],false);
            Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
            Gamepad::controllerProfile(1,defaultHats|(1ull<<(8+d)));assert(second.getState().buttons==(1u<<(10+d)));assert(pad.getState().buttons==0);
            Gamepad::controllerProfile(1,defaultHats);Gamepad::update();assert(second.getState().buttons==0);
        }
        char* mapping=SDL_GetGamepadMapping(gp);assert(mapping && !SDL_strstr(mapping,"dpup:"));SDL_free(mapping);
        Gamepad::controllerProfile(1,0);SDL_CloseGamepad(gp);SDL_DetachVirtualJoystick(id2);win32::Input::poll();Gamepad::update();keys();SDL_CloseJoystick(j2);
    }
    // Default generic Android hats stay authoritative over conflicting/late
    // SDL directions, without disabling simultaneous left-stick navigation.
    {
        Gamepad::context(Gamepad::Context::Menu);Gamepad::update();keys();
        const auto hats=15ull|(15ull<<53);
        Gamepad::controllerProfile(0,hats);Gamepad::update();keys();
        SDL_SetJoystickVirtualAxis(joy,0,24000);Gamepad::update();expect(SDLK_RIGHT,true);
        SDL_SetJoystickVirtualAxis(joy,0,0);Gamepad::update();expect(SDLK_RIGHT,false);
        for(unsigned d=0;d<4;++d) {
            SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],true);
            Gamepad::controllerProfile(0,hats|(1ull<<(8+d)));Gamepad::update();expect(arrows[d],true);
            Gamepad::context(Gamepad::Context::Pause);Gamepad::update();assert(keys().empty());
            Gamepad::controllerProfile(0,hats);Gamepad::update();expect(arrows[d],false);Gamepad::update();assert(keys().empty());
            SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],false);Gamepad::update();assert(keys().empty());
            Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
            Gamepad::controllerProfile(0,hats|(1ull<<(8+d)));assert(pad.getState().buttons==(1u<<(10+d)));
            Gamepad::controllerProfile(0,hats);Gamepad::update();assert(pad.getState().buttons==0);
            Gamepad::context(Gamepad::Context::Menu);Gamepad::update();keys();
        }
        Gamepad::controllerProfile(0,0);Gamepad::update();keys();
        // Select/Start must be quiet in both Menu and Pause, while still
        // remaining distinct physical buttons in in-game capture.
        for(auto mode:{Gamepad::Context::Menu,Gamepad::Context::Pause}) {
            Gamepad::context(mode);Gamepad::update();keys();
            for(int b:{8,9}) {Gamepad::androidButton(0,b,true);Gamepad::update();assert(keys().empty());Gamepad::androidButton(0,b,false);Gamepad::update();assert(keys().empty());}
        }
        Gamepad::context(Gamepad::Context::Capture);Gamepad::update();keys();
        for(int b:{8,9}) {Gamepad::androidButton(0,b,true);assert(pad.getState().buttons==(1u<<b));Gamepad::androidButton(0,b,false);Gamepad::update();assert(pad.getState().buttons==0);}
    }
    // One physical B must not also become the erroneous SDL A. No trailing
    // key may reappear if SDL releases later or the menu changes mid-press.
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,true);
    Gamepad::androidButton(0,1,true); Gamepad::update(); expect(SDLK_ESCAPE,true);
    Gamepad::update(); assert(keys().empty());
    Gamepad::context(Gamepad::Context::Pause); Gamepad::update(); assert(keys().empty());
    Gamepad::androidButton(0,1,false); Gamepad::update(); expect(SDLK_ESCAPE,false);
    Gamepad::update(); assert(keys().empty());
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,false); Gamepad::update(); assert(keys().empty());
    Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,true);
    Gamepad::androidButton(0,1,true); Gamepad::update(); assert(keys().empty());
    assert(pad.getState().buttons == 2);
    Gamepad::androidButton(0,1,false); Gamepad::update(); assert(pad.getState().buttons == 0);
    SDL_SetJoystickVirtualButton(joy,SDL_GAMEPAD_BUTTON_SOUTH,false); Gamepad::update(); keys();
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    // Android fallback works independently of a mapped SDL button.
    Gamepad::androidButton(0,0,true); Gamepad::update(); expect(SDLK_RETURN,true);
    // Enter capture with confirm held. It must not immediately bind itself.
    Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); expect(SDLK_RETURN,false);
    assert(pad.getState().buttons == 0);
    Gamepad::androidButton(0,0,false); Gamepad::update(); assert(keys().empty());
    Gamepad::androidButton(0,0,true); Gamepad::update(); assert(keys().empty());
    assert(pad.getState().buttons == 1);
    Gamepad::androidButton(0,-1,false); Gamepad::update(); keys();
    // Capture polls button-up while no renderer update is possible.
    SDL_SetJoystickVirtualAxis(joy,5,32767);
    assert(pad.getState().buttons == (1u<<15));
    SDL_SetJoystickVirtualAxis(joy,5,-32768);
    assert(pad.getState().buttons == 0);
    // Native in-game mapping suppresses the legacy racing key for that button.
    Gamepad::androidButton(0,-1,false); Gamepad::update(); keys();
    Gamepad::nativeButtons(0,1); Gamepad::context(Gamepad::Context::Race); Gamepad::update(); keys();
    Gamepad::androidButton(0,0,true); Gamepad::update(); assert(keys().empty());
    assert(pad.getState().buttons == 1);
    Gamepad::androidButton(0,0,false); Gamepad::update(); keys();
    Gamepad::nativeButtons(0,0); Gamepad::androidButton(0,0,true); Gamepad::update(); expect(SDLK_B,true);
    Gamepad::androidButton(0,-1,false); Gamepad::update(); expect(SDLK_B,false);
    // A remapped trigger must not also operate its old pedal axis.
    SDL_SetJoystickVirtualAxis(joy,5,32767); Gamepad::update(); keys();
    assert(pad.getState().axes[Gamepad::kAxisPedals] < -30000);
    Gamepad::nativeButtons(0,1u<<15); Gamepad::update(); keys();
    assert(pad.getState().axes[Gamepad::kAxisPedals] == 0);
    assert(pad.getState().buttons == (1u<<15));
    SDL_SetJoystickVirtualAxis(joy,5,-32768); Gamepad::update(); keys();
    Gamepad::nativeButtons(0,0);
    // Direct Android D-pad reports have their own authority. Conflicting SDL
    // directions and late SDL releases must not leak through or queue a press.
    for(unsigned d=0;d<4;++d) {
        Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
        SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],true);
        Gamepad::androidButton(0,10+d,true); Gamepad::update(); expect(arrows[d],true);
        Gamepad::context(Gamepad::Context::Pause); Gamepad::update(); assert(keys().empty());
        Gamepad::androidButton(0,10+d,false); Gamepad::update(); expect(arrows[d],false);
        Gamepad::update(); assert(keys().empty());
        SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],false); Gamepad::update(); assert(keys().empty());
        Gamepad::context(Gamepad::Context::Capture); Gamepad::update(); keys();
        Gamepad::androidButton(0,10+d,true); assert(pad.getState().buttons==(1u<<(10+d)));
        Gamepad::nativeButtons(0,1u<<(10+d)); Gamepad::context(Gamepad::Context::Race);
        Gamepad::update(); assert(keys().empty()); assert(pad.getState().buttons==(1u<<(10+d)));
        SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],true);
        Gamepad::androidButton(0,-1,false); Gamepad::update(); assert(pad.getState().buttons==0);
        Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); assert(keys().empty());
        SDL_SetJoystickVirtualButton(joy,directions[(d+1)%4],false); Gamepad::update(); assert(keys().empty());
        Gamepad::nativeButtons(0,0);
    }
    // Button identity must not depend on the other slot. Held menu keys release on unplug.
    Gamepad::context(Gamepad::Context::Menu); Gamepad::update(); keys();
    SDL_SetJoystickVirtualAxis(joy,0,-24000); Gamepad::update(); expect(SDLK_LEFT,true);
    SDL_DetachVirtualJoystick(id); win32::Input::poll(); Gamepad::update(); expect(SDLK_LEFT,false);
    SDL_CloseJoystick(joy);
    std::cout << "PASS: default Android hats + X/Y, single Confirm/Back without Start/Select menu/pause aliases; generic controller profiles (all directions, capture, axis suppression, source suppression, swapped A/B, no duplicates, race identity, player isolation) plus actual SDL3 gamepad axes, A/B, SDL/Android digital D-pad, raw hats, two-slot isolation, repeats, capture, remapping priority, delayed releases, pause clear and unplug\n";
}
