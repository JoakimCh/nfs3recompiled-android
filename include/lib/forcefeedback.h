#ifndef LIB_FORCEFEEDBACK_H_
#define LIB_FORCEFEEDBACK_H_

#include <lib/gamepad.h>
#include <winapi/types.h>

/* The game's force-feedback effects, played as rumble.  The game makes them
 * as DirectInput's -- a constant force for its jolts, a sine for the engine,
 * a square for the road, a spring for the wheel -- and its side of
 * DirectInput (src/nfs3hp/native_controls_input.cpp) hands them here as they
 * come: an effect made for a pad from DirectInput's description of it, its
 * parameters changed, started, stopped, unloaded; the device's gain and its
 * commands.  Each pad's effects are mixed into its motors' level. */
namespace win32 { namespace forcefeedback
{

constexpr HRESULT kInvalid = 0x80070057, kUnsupported = 0x80004001;

/* DirectInput's DIENVELOPE and DIEFFECT, as the game's memory holds them:
 * its pointers are the game's addresses. */
struct Envelope
{
    DWORD dwSize;
    DWORD dwAttackLevel;
    DWORD dwAttackTime;
    DWORD dwFadeLevel;
    DWORD dwFadeTime;
};

struct Parameters
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwDuration;
    DWORD dwSamplePeriod;
    DWORD dwGain;
    DWORD dwTriggerButton;
    DWORD dwTriggerRepeatInterval;
    DWORD cAxes;
    x86::reg32 rgdwAxes;
    x86::reg32 rglDirection;
    x86::reg32 lpEnvelope;
    DWORD cbTypeSpecificParams;
    x86::reg32 lpvTypeSpecificParams;
    DWORD dwStartDelay;
};

class Effect;

/* Whether the effect DirectInput's GUID names is one this plays. */
bool supported(const GUID& guid);
/* An effect for `pad` of the kind `guid` names, with `parameters` (or none
 * yet), to `*effect`; 0, or the error DirectInput would give. */
HRESULT create(WinApplication* app, Gamepad* pad, const GUID& guid, const Parameters* parameters, Effect** effect);
void destroy(WinApplication* app, Effect* effect);
/* DirectInput's SetParameters, its DIEP_ flags. */
HRESULT setParameters(WinApplication* app, Effect* effect, const Parameters& parameters, DWORD flags);
HRESULT start(Effect* effect, DWORD iterations, DWORD flags);
HRESULT stop(Effect* effect);
HRESULT download(Effect* effect);
HRESULT unload(Effect* effect);

/* Every frame: the effects a button fires, and the motors' levels. */
void update();
/* DirectInput's SendForceFeedbackCommand, its DISFFC_ flags. */
void command(Gamepad* pad, DWORD flags);
/* GetForceFeedbackState's DIGFFS_ flags. */
DWORD state(Gamepad* pad);
/* The device's gain, DIPROP_FFGAIN, 0 to 10000. */
void gain(Gamepad* pad, DWORD value);
/* A pad gone: its effects silent and let go of. */
void detach(Gamepad* pad);

}}

#endif
