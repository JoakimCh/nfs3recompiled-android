"""The game's menus decompiled, one screen at a time; never patch input EXEs.

Each screen's handlers -- the row of the name -> handler table at 0x555c48
(enter, exit, frame) and the functions only that screen calls -- go to C++ in
src/nfs3hp/native_frontend_*.cpp, entered from the top of their generated
functions the way tools/apply_native_vertices.py enters the vertex loops:
when the decompiled one says no, the generated code runs.  It says no with
NFS_FE_NATIVE=0, for the functions NFS_FE_NATIVE_OFF names, and when a string
of the game's it hands on is not at the address it expects.

The menu engine is decompiled a layer at a time, in
src/nfs3hp/native_frontend_menus.cpp: what reads FeData\Menus\*.mnu into the
screen and item tables, and the item lookup the screens use; then, in
native_frontend_loop.cpp, the menu loop -- a screen opened, its items drawn
and passed, the selection moved by the keys and the mouse, the screens gone
to and back from; in native_frontend_dialogs.cpp, the dialogs over the screens
-- a question, a message, a line to type in, a list to tick -- laid out in the
x87's own arithmetic, drawn, and answered through their callbacks.  The widgets
stay generated for now; the decompiled code calls into them by address (see
src/nfs3hp/native_frontend.h).

First, the main menu, where a race is set up, in its three forms: MAIN.MNU
for one player, MAINSPLT.MNU for two on one machine, MAINMULT.MNU for a race
over a network.  Their handlers fit the screen's items to the kind of race; a
player's name button opens a dialog whose answer comes back to a function of
its own; mainmult chooses the race from a list of its own (sub_440160,
sub_440390), and its Back asks before leaving a network game (sub_4400d0,
which the ipx screen uses too, and the answer, sub_43fcb0).
"""
from pathlib import Path

from tools.apply_native_vertices import apply as apply_sites

HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_main.cpp.\n"
MENUS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_menus.cpp.\n"
LOOP_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_loop.cpp.\n"
DIALOG_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_dialogs.cpp.\n"
OPTIONS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_options.cpp.\n"
CARS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_cars.cpp.\n"
TRACKS_HEADER = "// Port (tools/apply_native_frontend.py): defined in native_frontend_tracks.cpp.\n"

# (module, function, decompiled stand-in)
SITES = [
    # main: as the screen opens, as it closes, every pass of the menu loop.
    ("nfs3hp", "sub_45d050", "mainMenuOnEnter"),
    ("nfs3hp", "sub_45d2f0", "mainMenuOnExit"),
    ("nfs3hp", "sub_45cff0", "mainMenuOnFrame"),
    # The player's name button, and the name dialog's answer.
    ("nfs3hp", "sub_45cef0", "mainMenuOnPlayerName"),
    ("nfs3hp", "sub_45cdd0", "mainMenuPlayerNameAnswer"),
    # mainsplt, and player two's name.
    ("nfs3hp", "sub_45d360", "splitMenuOnEnter"),
    ("nfs3hp", "sub_45d620", "splitMenuOnExit"),
    ("nfs3hp", "sub_45d300", "splitMenuOnFrame"),
    ("nfs3hp", "sub_45cf70", "splitMenuOnPlayer2Name"),
    ("nfs3hp", "sub_45ce60", "splitMenuPlayer2NameAnswer"),
    # mainmult: its race list, its Back and the question before leaving.
    ("nfs3hp", "sub_440470", "multiMenuOnEnter"),
    ("nfs3hp", "sub_4405b0", "multiMenuOnExit"),
    ("nfs3hp", "sub_4403f0", "multiMenuOnFrame"),
    ("nfs3hp", "sub_440160", "multiMenuApplyRaceList"),
    ("nfs3hp", "sub_440390", "multiMenuFollowRaceType"),
    ("nfs3hp", "sub_4400d0", "multiMenuOnBack"),
    ("nfs3hp", "sub_43fcb0", "multiMenuLeaveAnswer"),
]

# The menu engine: the .MNU loader and what it reads with.
MENUS_SITES = [
    # The item lookup: a codelink's names, a screen's item by one of them,
    # and a screen's handlers from the table by its name.
    ("nfs3hp", "sub_4429c0", "menuCodelinkMatches"),
    ("nfs3hp", "sub_442a40", "menuFindItem"),
    ("nfs3hp", "sub_442b10", "menuAssignHandlers"),
    # A key's row in the keyword table, the string pool, the widget types.
    ("nfs3hp", "sub_448f00", "menuKeywordIndex"),
    ("nfs3hp", "sub_448f50", "menuStoreString"),
    ("nfs3hp", "sub_448fd0", "menuWidgetType"),
    ("nfs3hp", "sub_449020", "menuWidgetName"),
    ("nfs3hp", "sub_449060", "menuInitItem"),
    ("nfs3hp", "sub_4490e0", "menuSectionType"),
    # A value by its kind, into the item's field.
    ("nfs3hp", "sub_449130", "menuParseInt"),
    ("nfs3hp", "sub_449170", "menuParseLong"),
    ("nfs3hp", "sub_4491b0", "menuParseFloat"),
    ("nfs3hp", "sub_449240", "menuSetField"),
    # A file's lines, the files a screen leads to, and the editor's checks.
    ("nfs3hp", "sub_4493b0", "menuReadEntry"),
    ("nfs3hp", "sub_449510", "menuLoadMenus"),
    ("nfs3hp", "sub_4498a0", "menuCheckMenuFile"),
    ("nfs3hp", "sub_449960", "menuCheckMenuFiles"),
    ("nfs3hp", "sub_449990", "menuCallOnLoad"),
]

# The menu loop and moving through the screens.
LOOP_SITES = [
    # The loop itself, the race settings it keeps consistent, the help box.
    ("nfs3hp", "sub_44b230", "menuLoopStandIn"),
    ("nfs3hp", "sub_44be60", "menuFitRaceSettings"),
    ("nfs3hp", "sub_449aa0", "menuDrawHelp"),
    # A screen opened and left, its items' handlers in turn.
    ("nfs3hp", "sub_44ab40", "menuEnterScreen"),
    ("nfs3hp", "sub_44aa30", "menuLeaveScreen"),
    ("nfs3hp", "sub_44aad0", "menuResetItems"),
    ("nfs3hp", "sub_44a960", "menuShowItems"),
    ("nfs3hp", "sub_44a860", "menuItemsShown"),
    ("nfs3hp", "sub_44a9e0", "menuHideItems"),
    ("nfs3hp", "sub_44a8b0", "menuPassItems"),
    ("nfs3hp", "sub_44a4f0", "menuDrawItems"),
    ("nfs3hp", "sub_44b1a0", "menuWaitWhileSuspended"),
    # The selection: by the keys, by the mouse, and what may be selected.
    ("nfs3hp", "sub_44a2d0", "menuHandleKey"),
    ("nfs3hp", "sub_449f30", "menuSelectPrevious"),
    ("nfs3hp", "sub_44a0c0", "menuSelectNext"),
    ("nfs3hp", "sub_449e50", "menuSelectable"),
    ("nfs3hp", "sub_4499b0", "menuItemUsable"),
    ("nfs3hp", "sub_4499f0", "menuKeyAllowed"),
    ("nfs3hp", "sub_449ea0", "menuPointAtSelected"),
    ("nfs3hp", "sub_44a6b0", "menuItemUnderMouse"),
    ("nfs3hp", "sub_44a690", "menuReleaseMouse"),
    ("nfs3hp", "sub_44a660", "menuShownNow"),
    ("nfs3hp", "sub_44a440", "menuSelectedIndex"),
    ("nfs3hp", "sub_44a470", "menuSelectItem"),
    ("nfs3hp", "sub_44a240", "menuEscapeButton"),
    ("nfs3hp", "sub_449df0", "menuKeysTaken"),
    # The screens gone through: the shown one, by name, the history.
    ("nfs3hp", "sub_44aeb0", "menuCurrent"),
    ("nfs3hp", "sub_44ae00", "menuCurrentName"),
    ("nfs3hp", "sub_44ae60", "menuByNameStandIn"),
    ("nfs3hp", "sub_44aec0", "menuPop"),
    ("nfs3hp", "sub_44af10", "menuPush"),
    ("nfs3hp", "sub_44af50", "menuSetHistory"),
    # The dialogs the loop opens: the players' names, quitting.
    ("nfs3hp", "sub_44af90", "menuPlayer1NameAnswer"),
    ("nfs3hp", "sub_44b040", "menuPlayer2NameAnswer"),
    ("nfs3hp", "sub_44b0f0", "menuQuitAnswer"),
]

# The dialogs over the screens.
DIALOG_SITES = [
    # The dialog up, whatever its kind: its pass, a key for it, its art.
    ("nfs3hp", "sub_445f50", "dialogPassStandIn"),
    ("nfs3hp", "sub_445e60", "dialogKeyStandIn"),
    ("nfs3hp", "sub_445ac0", "dialogDrawHelp"),
    ("nfs3hp", "sub_445de0", "dialogLoadArt"),
    ("nfs3hp", "sub_445f00", "dialogFadedIn"),
    ("nfs3hp", "sub_445f10", "dialogClose"),
    ("nfs3hp", "sub_4438b0", "dialogShownStandIn"),
    ("nfs3hp", "sub_4438c0", "dialogKindStandIn"),
    ("nfs3hp", "sub_4446c0", "dialogFocusStandIn"),
    # A question: opened, its keys, its pass.
    ("nfs3hp", "sub_4446d0", "dialogOpenQuestion"),
    ("nfs3hp", "sub_444910", "dialogQuestionKey"),
    ("nfs3hp", "sub_4449d0", "dialogQuestionPass"),
    # A message.
    ("nfs3hp", "sub_444a80", "dialogOpenMessage"),
    ("nfs3hp", "sub_444be0", "dialogMessageById"),
    ("nfs3hp", "sub_444a60", "dialogEndMessage"),
    ("nfs3hp", "sub_444b20", "dialogMessageKey"),
    ("nfs3hp", "sub_444b60", "dialogMessagePass"),
    # A line to type in.
    ("nfs3hp", "sub_444c20", "dialogOpenEdit"),
    ("nfs3hp", "sub_444c10", "dialogEditText"),
    ("nfs3hp", "sub_444f50", "dialogEditKey"),
    ("nfs3hp", "sub_4450c0", "dialogEditPass"),
    # A list to tick entries of.
    ("nfs3hp", "sub_445750", "dialogOpenList"),
    ("nfs3hp", "sub_445150", "dialogListFocus"),
    ("nfs3hp", "sub_445520", "dialogListKey"),
    ("nfs3hp", "sub_445680", "dialogListPass"),
    ("nfs3hp", "sub_4452d0", "dialogPlaceEntries"),
    ("nfs3hp", "sub_445380", "dialogDrawList"),
    ("nfs3hp", "sub_445160", "dialogPointAtEntry"),
    ("nfs3hp", "sub_4451d0", "dialogEntryUnderMouse"),
    # The layout as one opens, the drawing on each pass, the pointer.
    ("nfs3hp", "sub_443a90", "dialogLinesBox"),
    ("nfs3hp", "sub_443c00", "dialogButtonRowBox"),
    ("nfs3hp", "sub_443d20", "dialogPlaceButtons"),
    ("nfs3hp", "sub_4438d0", "dialogDrawBox"),
    ("nfs3hp", "sub_443f40", "dialogDrawLines"),
    ("nfs3hp", "sub_444000", "dialogDrawButtons"),
    ("nfs3hp", "sub_444350", "dialogDrawEditField"),
    ("nfs3hp", "sub_444570", "dialogPointAtButton"),
    ("nfs3hp", "sub_4445d0", "dialogButtonUnderMouse"),
]

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
    ("nfs3hp", "sub_437600", "funkeysOnEnter"),
    ("nfs3hp", "sub_4377c0", "funkeysOnExit"),
    ("nfs3hp", "sub_4377d0", "hardkeysOnEnter"),
    ("nfs3hp", "sub_437e00", "audioOnEnter"),
    ("nfs3hp", "sub_438070", "audioOnExit"),
    ("nfs3hp", "sub_438260", "audioOnFrame"),
    ("nfs3hp", "sub_437a90", "audioVolumeDraw"),
    ("nfs3hp", "sub_437990", "audioMenuMusicMoved"),
    ("nfs3hp", "sub_4379b0", "audioRaceMusicMoved"),
    ("nfs3hp", "sub_4379d0", "audioEffectsMoved"),
    ("nfs3hp", "sub_437a20", "audioEngineMoved"),
    ("nfs3hp", "sub_437a70", "audioSpeechMoved"),
    ("nfs3hp", "sub_43d4d0", "controlsOnEnter"),
    ("nfs3hp", "sub_43d5f0", "controlsOnExit"),
    ("nfs3hp", "sub_43d3f0", "controlsCancelKey"),
    ("nfs3hp", "sub_43d460", "controlsResetClicked"),
    ("nfs3hp", "sub_43d410", "controlsResetAnswered"),
    ("nfs3hp", "sub_43d9a0", "deadZoneFillList"),
    ("nfs3hp", "sub_4432c0", "deadZoneOnEnter"),
    ("nfs3hp", "sub_443430", "deadZoneOnExit"),
    ("nfs3hp", "sub_442db0", "deadZoneCancelKey"),
    ("nfs3hp", "sub_443260", "deadZoneChooseKey"),
    ("nfs3hp", "sub_443290", "deadZoneChooseKeyInRace"),
    ("nfs3hp", "sub_443070", "deadZoneShowController"),
    ("nfs3hp", "sub_442e60", "deadZoneAxisIndex"),
    ("nfs3hp", "sub_442dd0", "deadZoneApplyAxis"),
    ("nfs3hp", "sub_442ef0", "deadZoneAxisMoved"),
    ("nfs3hp", "sub_442ff0", "deadZoneAxisDraw"),
    ("nfs3hp", "sub_447dd0", "forceOnEnter"),
    ("nfs3hp", "sub_4481c0", "forceOnExit"),
    ("nfs3hp", "sub_447b40", "forceCancelKey"),
    ("nfs3hp", "sub_447b60", "forceStrengthMoved"),
    ("nfs3hp", "sub_447c40", "forceRoadEffectsMoved"),
    ("nfs3hp", "sub_447c70", "forceCollisionMoved"),
    ("nfs3hp", "sub_447ca0", "forceEngineMoved"),
    ("nfs3hp", "sub_447cd0", "forceBodyRollMoved"),
    ("nfs3hp", "sub_447d50", "forceRoadGripMoved"),
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
    apply_sites(root, SITES, HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, MENUS_SITES, MENUS_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, LOOP_SITES, LOOP_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, DIALOG_SITES, DIALOG_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, OPTIONS_SITES, OPTIONS_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, CARS_SITES, CARS_HEADER, "tools/apply_native_frontend.py")
    apply_sites(root, TRACKS_SITES, TRACKS_HEADER, "tools/apply_native_frontend.py")


if __name__ == "__main__":
    apply(Path(__file__).resolve().parents[1])
