import sys
sys.path.append('disasm')
from disasm import disassembler, dll


DATA_SEGMENTS = [(0x401004, 0x401010),
                 (0x405734, 0x405740),
                 (0x409ff0, 0x40a010),
                 (0x40cb00, 0x40cb20),
                 (0x412920, 0x412994),
                 (0x41a880, 0x41a8c8),
                 (0x420814, 0x420840),
                 (0x4212b0, 0x421360),
                 (0x423d50, 0x423d90),
                 (0x42d550, 0x42d618),
                 (0x42dd30, 0x42dd58),
                 (0x434ea0, 0x434f14),
                 (0x43f180, 0x43f1e4),
                 (0x44e150, 0x44e170),
                 (0x4489f0, 0x448ef2),
                 (0x454f10, 0x455020),
                 # Up to 0x45cdd0, not 0x45cdc0: the 16 bytes in between are
                 # alignment padding, and stopping short of them made the
                 # recompiler seed a function on the padding.  The real prologue
                 # is at 0x45cdd0, the game takes that address as a text-field
                 # callback, and the call found nothing registered.
                 (0x45cb60, 0x45cdd0),
                 (0x465d10, 0x465d60),
                 (0x46ccb0, 0x46cce0),
                 (0x472160, 0x4721f0),
                 (0x478310, 0x478320),
                 (0x47ba70, 0x47bbb8),
                 (0x488030, 0x4880b0),
                 (0x489630, 0x4896f0),
                 (0x491110, 0x491120),
                 (0x493360, 0x493380),
                 (0x493370, 0x493380),
                 (0x49e060, 0x49e080),
                 (0x4975b0, 0x497620),
                 (0x49c3e0, 0x49c410),
                 (0x49e060, 0x49e080),
                 (0x4a2f50, 0x4a3050),
                 (0x4a4050, 0x4a4060),
                 (0x4a6f80, 0x4a7080),
                 (0x4af3b0, 0x4b0700),
                 (0x4b5580, 0x4b56d0),
                 (0x4b6a10, 0x4b6a10),
                 (0x4b7a10, 0x4b7a60),
                 (0x4c9a70, 0x4c9a80),
                 (0x4d0650, 0x4d06f0),
                 (0x4d5740, 0x4d5840),
                 (0x4dfae5, 0x4dfaf0),
                 (0x4f7fa5, 0x4f8020),
                 (0x51679d, 0x5167b3),
                 (0x52efb0, 0x52f318),
                 (0x533ef0, 0x534000),]


MERGE_ROUTINES = [(0x405740, 0x405791),
                  (0x405740, 0x4057a0),
                  (0x420840, 0x42088a),
                  (0x420840, 0x420a71),
                  (0x420840, 0x420a7a),
                  (0x420840, 0x420a83),
                  (0x420840, 0x420aac),
                  (0x420840, 0x420b53),]

# Methods the game reaches only through its tables, so small (mov eax, 1;
# ret -- a bare ret -- a jmp) that they read as the tail of the function
# before them; a call to one found nothing registered and was skipped.
# 0x4f5fd0 is the IPX transport's (table 0x566e70): skipping it crashed both
# machines as an IPX race was joined.
KNOWN_SUBROUTINES = [0x4ff3d0, 0x4f5fd0, 0x505970, 0x509c60,]

SKIP_INSTRUCTIONS = [0x4a3aec]


SPLIT_INSTRUCTIONS = [0x4e08af, 0x4e087a, 0x4eee0f]


THREAD_ROUTINES = []
# Busy waits on the main thread that only another thread can end.  Only one
# guest thread runs at a time, and a loop without API calls never lets go.
# 0x4e773f: sub_4e7720 waits for the game timer's tick [0x79c1a4] (the IPX
# library calls it on the main thread); 0x51436a: the IPX library waits for
# [edx+0xa8] to be cleared.  Without these the IPX lobby hangs.
THREAD_SEGMENTS = [0x43ac67, 0x43ac97, 0x46785e, 0x4f06f7, 0x4f2191, 0x495b68, 0x4d9158, 0x4c4e84, 0x4f7d0e,
                   0x4e773f, 0x51436a]

# The game's own functions that are native: each address is the port's
# function of that name in src/nfs3hp/native_game.cpp, no code is generated
# for it, and the generated code calls it by name.  They are AZHP's
# (third_party/azhp/SYMBOLS.md) -- the game's side of THRASH and iSND, and the
# logger -- and the four more lambdas iSNDloaddll hands eacsnd with AZHP's
# three; EA's names where the game's messages give them.  tools/game_checks
# generates their code all the same, to compare the natives with.
GAME_NATIVES = {
    0x401010: "Error",
    0x40faf0: "Is3DSoundAvailable",
    0x4df6c0: "Message",
    0x4e1a00: "StopSoundBufferLambda",
    0x4e1a0c: "AcquireSoundBufferPositionLambda",
    0x4e1a24: "AcquireSoundDataLambda",
    0x4e1a34: "PrintSoundLambda",
    0x4e1a64: "TraceSoundLambda",
    0x4e1a88: "abortmessagewrapper",
    0x4e1adc: "TickSoundLambda",
    0x4e1ae4: "iSNDconvertsample",
    0x4e1d48: "audiofocushandler",
    0x4e1dd4: "iSNDloaddll",
    0x4e21b0: "SNDcaps",
    0x4e2234: "SoundServeHandler",
    0x4eba70: "AcquireWindow",
    0x4f8390: "THRASH_opendll",
}

# The Watcom C runtime's functions that are native: each address is the port's
# function of that name in src/nfs3hp/native_watcom.cpp, in nfs3hp::watcom --
# Open Watcom's names (src/nfs3hp/watcom.md maps the runtime in nfs3.exe).
# tools/game_checks compares them with their generated code as well.
WATCOM_NATIVES = {
    0x4dfd56: "watcom::CHP",            # __CHP
    0x4e0640: "watcom::memset",
    0x4e06d9: "watcom::IF_DATAN2",      # IF@DATAN2
    0x4e0820: "watcom::strstr",
    0x4e0e30: "watcom::strncpy",
    0x4e28a0: "watcom::unlink",
    0x4e9030: "watcom::update_buffer",  # __update_buffer
    0x4e9070: "watcom::reset_buffer",   # __reset_buffer
    0x4e9088: "watcom::fseek",
    0x4e9200: "watcom::fread",
    0x4e9ec0: "watcom::stricmp",        # _stricmp
    0x4eb1d0: "watcom::mkdir",
    0x4eb1f0: "watcom::initrandnext",
    0x4eb1fc: "watcom::rand",
    0x4eb220: "watcom::srand",
    0x4eb390: "watcom::strncmp",
    0x4edd80: "watcom::open_flags",     # __open_flags
    0x4edebc: "watcom::doopen",         # __doopen
    0x4edfa4: "watcom::fsopen",         # _fsopen
    0x4edfe8: "watcom::fopen",
    0x4ee100: "watcom::fclose",
    0x4ee144: "watcom::shutdown_stream", # __shutdown_stream
    0x4ee214: "watcom::doclose",        # __doclose
    0x4ee2e0: "watcom::remove",
    0x4ee2f0: "watcom::strrchr",
    0x4ee310: "watcom::strcmp",
    0x4ee3c0: "watcom::chmod",
    0x4ee400: "watcom::rmdir",
    0x4ee420: "watcom::ftell",
    0x4ee480: "watcom::med3",
    0x4ee4d0: "watcom::byteswap",
    0x4ee4f8: "watcom::qsort",
    0x4eebd0: "watcom::fwrite",
    0x4eede0: "watcom::toupper",
    0x4eedf0: "watcom::strncat",
    0x4eff60: "watcom::strtok",
    0x4f0260: "watcom::chdir",
    0x4f0430: "watcom::atoi",
    0x4f0490: "watcom::atol",
    0x4f0570: "watcom::fgets",
    0x4f05f0: "watcom::access",
    0x4f0730: "watcom::getcwd",
    0x4f07d0: "watcom::getdiskfree",    # _getdiskfree
    0x4f0ae0: "watcom::tolower",
    0x4f1c30: "watcom::floor",
    0x4f22b0: "watcom::time",
    0x4f2d78: "watcom::ceil",
    0x4f7900: "watcom::nmalloc",        # _nmalloc
    0x4f79f0: "watcom::nfree",          # _nfree
    0x4f7c90: "watcom::control87",      # _control87
    0x4f7d70: "watcom::fflush",
    0x4f7d80: "watcom::fputs",
    0x4f8020: "watcom::strupr",         # _strupr
    0x4f8040: "watcom::localtime_",     # _localtime
    0x4f8094: "watcom::localtime",
    0x4f80b4: "watcom::IF_DEXP",        # IF@DEXP
    0x4f8116: "watcom::exp",
    0x4f9482: "watcom::IF_DACOS",       # IF@DACOS
    0x4fb300: "watcom::bsearch",
    0x4ff0ec: "watcom::GetThreadPtr",   # __GetThreadPtr
    0x4ff0f4: "watcom::NullAccess",     # __NullAccessRtn
    0x4ff4c0: "watcom::STOSB",          # __STOSB
    0x4ff4f7: "watcom::STOSD",          # __STOSD
    0x500f8c: "watcom::set_errno_dos",  # __set_errno_dos
    0x500ff4: "watcom::set_errno_nt",   # __set_errno_nt
    0x502760: "watcom::flush",          # __flush
    0x502880: "watcom::set_errno",      # __set_errno
    0x502890: "watcom::set_EDOM",       # __set_EDOM
    0x5028a4: "watcom::set_ERANGE",     # __set_ERANGE
    0x5028c8: "watcom::set_doserrno",   # __set_doserrno
    0x5028e0: "watcom::lseek",
    0x502960: "watcom::tell",           # _tell
    0x5029c0: "watcom::ioalloc",        # __ioalloc
    0x502a50: "watcom::qread",          # __qread
    0x502af0: "watcom::fgetc",
    0x502bb8: "watcom::filbuf",         # __filbuf
    0x502be8: "watcom::fill_buffer",    # __fill_buffer
    0x508ff4: "watcom::sopen",          # _sopen
    0x50901c: "watcom::sopen_",         # __sopen
    0x509250: "watcom::allocfp",        # __allocfp
    0x509314: "watcom::freefp",         # __freefp
    0x509380: "watcom::chktty",         # __chktty
    0x5095b0: "watcom::close",          # __close
    0x509640: "watcom::fixed_GetFileAttributesA", # __fixed_GetFileAttributesA
    0x5096c0: "watcom::qwrite",         # __qwrite
    0x5097b0: "watcom::fputc",
    0x50c540: "watcom::setbits",        # __setbits
    0x50ea4e: "watcom::modf",
    0x50eb30: "watcom::getctime",       # __getctime
    0x50eba0: "watcom::mktime",
    0x515300: "watcom::MemAllocator",   # __MemAllocator
    0x5153b0: "watcom::MemFree",        # __MemFree
    0x5154e0: "watcom::LinkUpNewNHeap", # __LinkUpNewNHeap
    0x515558: "watcom::CreateNewNHeap", # __CreateNewNHeap
    0x515614: "watcom::ExpandDGROUP",   # __ExpandDGROUP
    0x515628: "watcom::AdjustAmount",   # __AdjustAmount
    0x515680: "watcom::nmemneed",       # __nmemneed
    0x515850: "watcom::flushall",
    0x515858: "watcom::flushall_",      # __flushall
    0x515fa0: "watcom::brktime",        # __brktime
    0x5160f0: "watcom::leapyear",       # __leapyear
    0x51612c: "watcom::calc_yday",
    0x516224: "watcom::check_order",
    0x516270: "watcom::isindst",        # __isindst
    0x51652c: "watcom::time_less",
    0x51655c: "watcom::math87_err",     # __math87_err
    0x51a1ba: "watcom::DSQRT",          # __@DSQRT
    0x51e2b0: "watcom::handlesFull",    # _sopen's: no handle free
    0x51e304: "watcom::allocPOSIXHandle", # __allocPOSIXHandle
    0x51e45c: "watcom::freePOSIXHandle", # __freePOSIXHandle
    0x51e4f0: "watcom::NTGetFakeHandle", # __NTGetFakeHandle
    0x522d80: "watcom::fsync",
    0x522de0: "watcom::GetIOMode",      # __GetIOMode
    0x522e38: "watcom::SetIOMode",      # __SetIOMode
    0x5234d0: "watcom::GetNTAccessAttr", # __GetNTAccessAttr
    0x523504: "watcom::GetNTShareAttr", # __GetNTShareAttr
    0x523560: "watcom::isatty",
    0x5241c0: "watcom::nheapshrink",    # _nheapshrink
    0x5241fc: "watcom::ReturnMemToSystem", # __ReturnMemToSystem
    0x52425c: "watcom::ReleaseNHeap",   # _nheapshrink's step
}
GAME_NATIVES.update(WATCOM_NATIVES)

# The game's code that uses MMX, native: each address is the port's function
# of that name in src/nfs3hp/native_mmx.cpp, in nfs3hp::mmx -- the SND
# library's MMX routines and the memmove the game's file reads copy with.
# Only 0x4ea4f0's and 0x4f09c0's emms are left generated.  tools/game_checks
# compares them with their generated code as well.
MMX_NATIVES = {
    0x5033e4: "mmx::copySwapped",       # the memmove's copy, xchg edx, eax first
    0x5033e5: "mmx::copy",              # its copy: eax to, edx from, ebx bytes
    0x51f5dd: "mmx::addMono8",
    0x51f6c7: "mmx::addStereo8",
    0x51f7ad: "mmx::addMono16",
    0x51f897: "mmx::addStereo16",
    0x520830: "mmx::outputMono8",
    0x520870: "mmx::outputStereo8",
    0x520920: "mmx::outputStereo16",
    0x5209a0: "mmx::clear",
    0x520a00: "mmx::emms",
    0x520a10: "mmx::outputMono16",
    0x5270f0: "mmx::interpolateMono8",
    0x527170: "mmx::interpolateStereo8",
    0x527210: "mmx::interpolateMono16",
    0x527290: "mmx::interpolateStereo16",
    0x52d1a0: "mmx::xaMono",
    0x52d250: "mmx::xaStereo",
}
GAME_NATIVES.update(MMX_NATIVES)

# eacsnd.dll's data inside its code (tools/sound_checks/generate.py makes it
# the same way).
EACSND_DATA_SEGMENTS = [(0xa35749, 0xa3575f), (0xa372bf, 0xa372dd)]

# eacsnd.dll is native: each export is the port's function of that name in
# src/nfs3hp/native_sound.cpp (the driver) and native_isnd.cpp (the rest), and
# none of its code is generated.  tools/sound_checks generates it all the same,
# to compare the natives with.
EACSND_NATIVES = {
    "_iSNDdllversion@0": "iSNDdllversion",
    "_iSNDdirectsetfunctions@32": "iSNDdirectsetfunctions",
    "_iSNDdirectcaps@4": "iSNDdirectcaps",
    "_iSNDdirectstart@8": "iSNDdirectstart",
    "_iSNDdirectstop@0": "iSNDdirectstop",
    "_iSNDdirectrecordstart@16": "iSNDdirectrecordstart",
    "_iSNDdirectrecordpacket@4": "iSNDdirectrecordpacket",
    "_iSNDdirectrecordstop@0": "iSNDdirectrecordstop",
    "_iSNDdirectserve@0": "iSNDdirectserve",
    "_iSNDdirectvol@8": "iSNDdirectvol",
    "_iSNDdirectpos3d@12": "iSNDdirectpos3d",
    "_iSNDdirectrate@8": "iSNDdirectrate",
    "_iSNDdirectcreate3dbuf@28": "iSNDdirectcreate3dbuf",
    "_iSNDdirectremovebuf@4": "iSNDdirectremovebuf",
    "_iSNDdirectplay3d@28": "iSNDdirectplay3d",
    "_iSNDdirectstopbuf@4": "iSNDdirectstopbuf",
}

# voodoo2a.dll, the Voodoo2 driver behind THRASH: data in its code, and two
# functions that are a bare ret after another (THRASH_flushwindow, THRASH_idle).
# tools/thrash_checks generates it with these.
VOODOO2A_DATA_SEGMENTS = [(0xa83204, 0xa83210), (0xA86833, 0xA868A2)]
VOODOO2A_KNOWN_SUBROUTINES = [0xA847D0, 0xA84810]

# voodoo2a is native: each export is the port's function of that name in
# src/nfs3hp/native_thrash.cpp, and none of its code is generated.  Of its own
# functions only one is handed out to be called: sub_a84360, which
# THRASH_setvideomode gives the game's window thread to run on message 0x465.
VOODOO2A_NATIVES = {
    "_THRASH_about@0": "THRASH_about",
    "_THRASH_clearwindow@0": "THRASH_clearwindow",
    "_THRASH_clip@16": "THRASH_clip",
    "_THRASH_drawline@8": "THRASH_drawline",
    "_THRASH_drawlinemesh@12": "THRASH_drawlinemesh",
    "_THRASH_drawlinestrip@8": "THRASH_drawlinestrip",
    "_THRASH_drawpoint@4": "THRASH_drawpoint",
    "_THRASH_drawpointmesh@12": "THRASH_drawpointmesh",
    "_THRASH_drawpointstrip@8": "THRASH_drawpointstrip",
    "_THRASH_drawquad@16": "THRASH_drawquad",
    "_THRASH_drawquadmesh@12": "THRASH_drawquadmesh",
    "_THRASH_drawtri@12": "THRASH_drawtri",
    "_THRASH_drawtrifan@8": "THRASH_drawtrifan",
    "_THRASH_drawtrimesh@12": "THRASH_drawtrimesh",
    "_THRASH_drawtristrip@8": "THRASH_drawtristrip",
    "_THRASH_flushwindow@0": "THRASH_flushwindow",
    "_THRASH_idle@0": "THRASH_idle",
    "_THRASH_init@0": "THRASH_init",
    "_THRASH_is@0": "THRASH_is",
    "_THRASH_lockwindow@0": "THRASH_lockwindow",
    "_THRASH_pageflip@0": "THRASH_pageflip",
    "_THRASH_readrect@20": "THRASH_readrect",
    "_THRASH_restore@0": "THRASH_restore",
    "_THRASH_selectdisplay@4": "THRASH_selectdisplay",
    "_THRASH_setstate@8": "THRASH_setstate",
    "_THRASH_settexture@4": "THRASH_settexture",
    "_THRASH_setvideomode@12": "THRASH_setvideomode",
    "_THRASH_sync@4": "THRASH_sync",
    "_THRASH_talloc@20": "THRASH_talloc",
    "_THRASH_treset@0": "THRASH_treset",
    "_THRASH_tupdate@12": "THRASH_tupdate",
    "_THRASH_unlockwindow@4": "THRASH_unlockwindow",
    "_THRASH_window@4": "THRASH_window",
    "_THRASH_writerect@20": "THRASH_writerect",
}
VOODOO2A_CALLBACKS = {0xa84360: "THRASH_modemessage"}

if __name__ == '__main__':
    application = disassembler.disassemble('nfs3hp', 'nfs3hp/nfs3.exe', DATA_SEGMENTS,
                                           KNOWN_SUBROUTINES, SPLIT_INSTRUCTIONS,
                                           THREAD_ROUTINES, THREAD_SEGMENTS, MERGE_ROUTINES)
    eacsnd = disassembler.disassemble('eacsnd', 'nfs3hp/eacsnd.dll', type=dll.DLL,
                                      data_segments=EACSND_DATA_SEGMENTS, rebase_after=application)
    eacsnd.native('nfs3hp', EACSND_NATIVES)
    # softtria.dll, the software renderer, is not on the port: the game loads
    # one renderer, the one the registry's "Thrash Driver" names (sub_4b5720),
    # unless a command-line option names another, and the port sets voodoo2 and
    # gives no options.  So none of it is built -- no code, no data, no library,
    # and LoadLibrary("softtria.dll") would fail as it does with the file
    # missing.  It is read only for where voodoo2a goes after it.
    softtria = dll.DLL('softtria', 'nfs3hp/softtria.dll', eacsnd.sections[-1][1] + eacsnd.sections[-1][2])
    voodoo2a = disassembler.disassemble('voodoo2a', 'nfs3hp/voodoo2a.dll', type=dll.DLL,
                                        data_segments=VOODOO2A_DATA_SEGMENTS,
                                        known_subroutines=VOODOO2A_KNOWN_SUBROUTINES, rebase_after=softtria)
    voodoo2a.native('nfs3hp', VOODOO2A_NATIVES, VOODOO2A_CALLBACKS)
    application.write(THREAD_SEGMENTS, skip_instructions=SKIP_INSTRUCTIONS, dlls=[eacsnd, voodoo2a],
                      natives=GAME_NATIVES)
    from pathlib import Path
    for stale in Path('src/nfs3hp/disassembly').glob('softtria.*'):
        stale.unlink()  # what an earlier run wrote of softtria

    # Reapply the reviewed port heap budget after regenerating the original code.
    from tools.apply_heap_budget import apply
    apply(Path(__file__).resolve().parent)

    # tools/apply_glide_output.py is deliberately NOT applied.  Advertising a
    # 32-bit output depth blacked out every race on device while leaving the
    # resolution list still reading 16-bit -- the table is rewritten after the
    # game has already built that list, and read again by something later.
    # Confirmed by bisection: reverting these two files alone brought the
    # picture back.  The tool is kept for whoever picks the work up again; its
    # half for voodoo2a, whose code is no longer generated, would now go into
    # THRASH_about and measureModes in src/nfs3hp/native_thrash.cpp.

    from tools.apply_menu_unlock import apply as apply_menu_unlock
    apply_menu_unlock(Path(__file__).resolve().parent)

    # Download Car: off both car screens, there being nothing left to download.
    from tools.apply_hide_download import apply as apply_hide_download
    apply_hide_download(Path(__file__).resolve().parent)

    # RaceNet, Modem and Serial: off the connection screen, EA's server being
    # gone and a phone having neither of the others.
    from tools.apply_hide_connections import apply as apply_hide_connections
    apply_hide_connections(Path(__file__).resolve().parent)

    # TCP/IP port: 9803 as the Modern Patch has it, or 1030 for the original.
    from tools.apply_network_port import apply as apply_network_port
    apply_network_port(Path(__file__).resolve().parent)

    # Car detail: every car's texture at the player's size, a larger transform
    # buffer and wheel spin kept per car, so split screen and the mirror match.
    from tools.apply_car_detail import apply as apply_car_detail
    apply_car_detail(Path(__file__).resolve().parent)

    # View Distance: Full by default and 500 in every view, split screen and
    # night included; the other settings stay the game's own.
    from tools.apply_track_detail import apply as apply_track_detail
    apply_track_detail(Path(__file__).resolve().parent)

    # The rear-view mirror at the main view's distances and car detail.
    from tools.apply_mirror_detail import apply as apply_mirror_detail
    apply_mirror_detail(Path(__file__).resolve().parent)

    # Race state: which of the two on-screen layouts belongs on the screen.
    from tools.apply_race_state import apply as apply_race_state
    apply_race_state(Path(__file__).resolve().parent)

    # Races at the x87's extended precision, as the Modern Patch runs them:
    # the race loop's fldcw down to single precision goes through
    # nfs3hp::raceControl (NFS_FPU_EXTENDED).
    from tools.apply_race_precision import apply as apply_race_precision
    apply_race_precision(Path(__file__).resolve().parent)

    # HUD scale: the parts of a HUD element keep their proportions on a wide
    # screen instead of growing with its width.
    from tools.apply_hud_scale import apply as apply_hud_scale
    apply_hud_scale(Path(__file__).resolve().parent)

    # Cabin fit: the in-car dashboard and wheel keep their shape on a wide screen.
    from tools.apply_cabin_fit import apply as apply_cabin_fit
    apply_cabin_fit(Path(__file__).resolve().parent)

    # HUD editor: an element is framed, moved and checked for room as it is
    # drawn, and written back to the layout as laid out.
    from tools.apply_hud_editor import apply as apply_hud_editor
    apply_hud_editor(Path(__file__).resolve().parent)

    # Loading screen: 4:3 in the middle of a wide screen, as the Modern Patch
    # shows it.
    from tools.apply_loading_screen import apply as apply_loading_screen
    apply_loading_screen(Path(__file__).resolve().parent)

    from tools.apply_movie_tap import apply as apply_movie_tap
    apply_movie_tap(Path(__file__).resolve().parent)

    # Alpha intensity: the Advanced Graphics slider, which the original applies
    # on its Direct3D driver only.
    from tools.apply_alpha_intensity import apply as apply_alpha_intensity
    apply_alpha_intensity(Path(__file__).resolve().parent)

    # Widescreen: a 16:9 screen size in the list, Hor+ cameras, and the
    # interface fitted to the screen it is drawn on.
    from tools.apply_widescreen import apply as apply_widescreen
    apply_widescreen(Path(__file__).resolve().parent)


    # Music: a track is streamed from its own file instead of from a copy the
    # game makes of it at every race start.
    from tools.apply_music_stream import apply as apply_music_stream
    apply_music_stream(Path(__file__).resolve().parent)

    # Text entry: the phone's keyboard comes up by itself while the game waits
    # for a name to be typed.
    from tools.apply_text_entry import apply as apply_text_entry
    apply_text_entry(Path(__file__).resolve().parent)

    # Force feedback: player one's car keeps its effects when the on-screen
    # controls are bound as keys, which leaves no axis on the pad to claim them.
    from tools.apply_force_feedback_car import apply as apply_force_feedback_car
    apply_force_feedback_car(Path(__file__).resolve().parent)

    # Full colour: the Screen Size list shows the depth a race is drawn in (the
    # Voodoo2 driver's taking the game's 32-bit textures is native_thrash.cpp's).
    from tools.apply_full_colour import apply as apply_full_colour
    apply_full_colour(Path(__file__).resolve().parent)

    # First settings: a game that starts with no settings file -- data copied
    # straight off the disc -- gets the phone's, as an import writes them.
    from tools.apply_first_settings import apply as apply_first_settings
    apply_first_settings(Path(__file__).resolve().parent)

    # Native vertex loops: the hottest render functions as float arithmetic in
    # the x87's order, the generated code kept behind them.
    from tools.apply_native_vertices import apply as apply_native_vertices
    apply_native_vertices(Path(__file__).resolve().parent)

    # The opponents' pull and steering, decompiled into C++ that comes out as
    # the generated code to the bit (src/nfs3hp/native_ai.h).
    from tools.apply_native_ai import apply as apply_native_ai
    apply_native_ai(Path(__file__).resolve().parent)

    # The rest of the drawing native, function by function, behind the same
    # kind of hook.
    from tools.apply_native_render import apply as apply_native_render
    apply_native_render(Path(__file__).resolve().parent)

    # The game's sound mixer native: decoding, resampling, volume and pan.
    from tools.apply_native_mixer import apply as apply_native_mixer
    apply_native_mixer(Path(__file__).resolve().parent)

    # The loading native: RefPack, the FSH textures' alpha scans, an FCE's
    # polygon records and a track's FRD.
    from tools.apply_native_loading import apply as apply_native_loading
    apply_native_loading(Path(__file__).resolve().parent)

    # The movies native: the MAD player, decoder and display (decomp/mad), after
    # apply_movie_tap's MovieSession.
    from tools.apply_native_movie import apply as apply_native_movie
    apply_native_movie(Path(__file__).resolve().parent)

    # The menus decompiled a screen at a time, the generated code kept behind
    # them: first the main menu.
    from tools.apply_native_frontend import apply as apply_native_frontend
    apply_native_frontend(Path(__file__).resolve().parent)
