"""The game's menus decompiled, one screen at a time; never patch input EXEs.

Each screen's handlers -- the row of the name -> handler table at 0x555c48
(enter, exit, frame) and the functions only that screen calls -- go to C++ in
src/nfs3hp/native_frontend_*.cpp, entered from the top of their generated
functions the way tools/apply_native_vertices.py enters the vertex loops:
when the decompiled one says no, the generated code runs.  It says no with
NFS_FE_NATIVE=0, for the functions NFS_FE_NATIVE_OFF names, and when a string
of the game's it hands on is not at the address it expects.

The menu engine is decompiled a layer at a time: what reads FeData\Menus\*.mnu
into the screen and item tables, and the item lookup the screens use, is
rewritten whole, port::menus (src/nfs3hp/port_menus.cpp), and so is the menu
loop -- a screen opened, its items drawn and passed, the selection moved by the
keys and the mouse, the screens gone to and back from -- port::loop
(src/nfs3hp/port_loop.cpp), and so are the dialogs over the screens -- a
question, a message, a line to type in, a list to tick -- port::dialogs
(src/nfs3hp/port_dialogs.cpp), with no hooks left here.  The widgets stay
generated for now; the decompiled code calls into them by address (see
src/nfs3hp/native_frontend.h).

The main menu, where a race is set up, in its three forms -- MAIN.MNU for
one player, MAINSPLT.MNU for two on one machine, MAINMULT.MNU for a race over
a network -- was the first; it is native whole now, its handlers bound to
their addresses with no generated code behind them (disassemble_nfs3hp.py's
MENU_NATIVES, native_frontend_main.cpp), and so is what it calls of the loop
(a screen's items shown, the shown screen's name) and of the dialogs (a question,
a message and a line to type in opened, their layout and the pointer on their
button): those are no longer among the sites below.
"""
from pathlib import Path

from tools.apply_native_vertices import apply as apply_sites

MENUS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_menus.cpp.\n"
DIALOG_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_dialogs.cpp.\n"
OPTIONS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.\n"
CARS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.\n"
TRACKS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_tracks.cpp.\n"

# (module, function, decompiled stand-in)
# The options screens: options, audio, audfeed, funkeys, hardkeys, control1,
# deadzone, force, graphics and advgrph -- their handlers, the handlers they
# hand their items (a key, drawing, a slider's moves) and the few functions
# only they call.
OPTIONS_SITES = [
    ("nfs3hp", "sub_442aa0", "optionsOnEnter"),
    ("nfs3hp", "sub_4374b0", "feedOnEnter"),
    ("nfs3hp", "sub_437590", "feedOnExit"),
    ("nfs3hp", "sub_437250", "feedSeparate"),
    ("nfs3hp", "sub_437300", "feedTimeButtonKey"),
    ("nfs3hp", "sub_437390", "feedPositionButtonKey"),
    ("nfs3hp", "sub_437420", "feedSpeedButtonKey"),
    ("nfs3hp", "sub_437350", "feedTimeListKey"),
    ("nfs3hp", "sub_4373e0", "feedPositionListKey"),
    ("nfs3hp", "sub_437470", "feedSpeedListKey"),
    ("nfs3hp", "sub_437e00", "audioOnEnter"),
    ("nfs3hp", "sub_438070", "audioOnExit"),
    ("nfs3hp", "sub_438260", "audioOnFrame"),
    ("nfs3hp", "sub_437a90", "audioVolumeDraw"),
    ("nfs3hp", "sub_437990", "audioMenuMusicMoved"),
    ("nfs3hp", "sub_4379b0", "audioRaceMusicMoved"),
    ("nfs3hp", "sub_4379d0", "audioEffectsMoved"),
    ("nfs3hp", "sub_437a20", "audioEngineMoved"),
    ("nfs3hp", "sub_437a70", "audioSpeechMoved"),
    ("nfs3hp", "sub_448440", "graphicsOnEnter"),
    ("nfs3hp", "sub_4484e0", "graphicsOnExit"),
    ("nfs3hp", "sub_448430", "graphicsOnFrame"),
    ("nfs3hp", "sub_448610", "advancedOnEnter"),
    ("nfs3hp", "sub_448770", "advancedOnExit"),
    ("nfs3hp", "sub_4485a0", "advancedOnFrame"),
    ("nfs3hp", "sub_448570", "advancedIntensityMoved"),
]

# The cars' screens: car1 and car2, opponent and cedbasic (a car's tuning),
# with the handlers they hand their items and the few functions only they call.
CARS_SITES = [
    ("nfs3hp", "sub_4104b0", "carMenuMusicBack"),
    ("nfs3hp", "sub_4267a0", "carSaveFrame"),
    ("nfs3hp", "sub_4267f0", "trackSaveFrame"),
    ("nfs3hp", "sub_426870", "carRecord"),
    ("nfs3hp", "sub_426b00", "trackRecord"),
    ("nfs3hp", "sub_426d60", "car1OnEnter"),
    ("nfs3hp", "sub_426ef0", "car2OnEnter"),
    ("nfs3hp", "sub_426e20", "car1OnFrame"),
    ("nfs3hp", "sub_426f80", "car2OnFrame"),
    ("nfs3hp", "sub_426ee0", "car1OnExit"),
    ("nfs3hp", "sub_427040", "car2OnExit"),
    ("nfs3hp", "sub_426c20", "car1EditClicked"),
    ("nfs3hp", "sub_426c40", "car2EditClicked"),
    ("nfs3hp", "sub_426c60", "car1ColourClicked"),
    ("nfs3hp", "sub_426ce0", "car2ColourClicked"),
    ("nfs3hp", "sub_427050", "opponentFitCar"),
    ("nfs3hp", "sub_4270c0", "opponentFitArt"),
    ("nfs3hp", "sub_4272a0", "opponentOnEnter"),
    ("nfs3hp", "sub_4272e0", "opponentOnExit"),
    ("nfs3hp", "sub_427190", "opponentOnFrame"),
    ("nfs3hp", "sub_4272f0", "tuningLoad"),
    ("nfs3hp", "sub_427370", "tuningSave"),
    ("nfs3hp", "sub_4273e0", "tuningEngineMoved"),
    ("nfs3hp", "sub_427470", "tuningBrakesMoved"),
    ("nfs3hp", "sub_427500", "tuningSteeringMoved"),
    ("nfs3hp", "sub_427590", "tuningGearsMoved"),
    ("nfs3hp", "sub_427620", "tuningSuspensionMoved"),
    ("nfs3hp", "sub_4276b0", "tuningAeroMoved"),
    ("nfs3hp", "sub_427740", "tuningTiresMoved"),
    ("nfs3hp", "sub_4277d0", "tuningSetSliders"),
    ("nfs3hp", "sub_4279b0", "tuningRememberSliders"),
    ("nfs3hp", "sub_427ac0", "tuningSlidersMoved"),
    ("nfs3hp", "sub_427c20", "tuningBindSliders"),
    ("nfs3hp", "sub_427d00", "tuningLoadAdvanced"),
    ("nfs3hp", "sub_427d80", "tuningDefaultsAnswered"),
    ("nfs3hp", "sub_427e10", "tuningDoneKey"),
    ("nfs3hp", "sub_427ea0", "tuningCancelKey"),
    ("nfs3hp", "sub_427f40", "tuningCarListKey"),
    ("nfs3hp", "sub_427fb0", "tuningDefaultsKey"),
    ("nfs3hp", "sub_428020", "tuningBindDoneCancel"),
    ("nfs3hp", "sub_428060", "tuningFitButtons"),
    ("nfs3hp", "sub_4281e0", "tuningPrepare"),
    ("nfs3hp", "sub_428360", "tuningOnEnter"),
    ("nfs3hp", "sub_4283b0", "tuningOnExit"),
    ("nfs3hp", "sub_4dcaf0", "tuningAdvancedDiffers"),
    ("nfs3hp", "sub_4dcb60", "tuningCopyAdvanced"),
]

# The track's: location and trkinfo.
TRACKS_SITES = [
    ("nfs3hp", "sub_4487e0", "locationOnEnter"),
    ("nfs3hp", "sub_4487d0", "locationOnFrame"),
    ("nfs3hp", "sub_4489e0", "locationOnExit"),
    ("nfs3hp", "sub_456200", "infoPlaceTrackPlaces"),
    ("nfs3hp", "sub_4568d0", "infoOnEnter"),
    ("nfs3hp", "sub_456890", "infoOnFrame"),
    ("nfs3hp", "sub_456990", "infoOnExit"),
    ("nfs3hp", "sub_4c94e0", "infoSpeak"),
    ("nfs3hp", "sub_4c9590", "infoStopSpeaking"),
]


def apply(root):
    apply_sites(root, OPTIONS_SITES, OPTIONS_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, CARS_SITES, CARS_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, TRACKS_SITES, TRACKS_HEADER, "tools/apply_native_frontend.py")


if __name__ == "__main__":
    apply(Path(__file__).resolve().parents[1])
