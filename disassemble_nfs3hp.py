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
# for it, and the generated code calls it by name: the game's side of THRASH
# and iSND, the logger, the lambdas iSNDloaddll hands eacsnd, and the fill the
# game's code clears its memory with; EA's names where the game's messages
# give them.  tools/game_checks generates their code
# all the same, to compare the natives with.
GAME_NATIVES = {
    0x401010: "Error",
    0x40faf0: "Is3DSoundAvailable",
    0x4df6c0: "Message",
    0x4e070c: "fillZero",               # the game's fill at its three entries: zeros,
    0x4e0716: "fillByte",               # bl spread,
    0x4e0721: "fillWord",               # the pattern in ebx
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
    0x4df660: "watcom::mem_putc",
    0x4df674: "watcom::vsprintf",
    0x4df690: "watcom::sprintf",
    0x4dfd04: "watcom::exit",
    0x4dfd30: "watcom::_exit",
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
    0x4ee15c: "watcom::hexDigit",       # __MkTmpFile's digit
    0x4ee168: "watcom::MkTmpFile",      # __MkTmpFile
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
    0x4f04f0: "watcom::cget_string",
    0x4f051c: "watcom::uncget_string",
    0x4f0520: "watcom::vsscanf",
    0x4f0548: "watcom::sscanf",
    0x4f0570: "watcom::fgets",
    0x4f05f0: "watcom::access",
    0x4f0710: "watcom::sleep",
    0x4f0730: "watcom::getcwd",
    0x4f07d0: "watcom::getdiskfree",    # _getdiskfree
    0x4f0ae0: "watcom::tolower",
    0x4f1c30: "watcom::floor",
    0x4f22b0: "watcom::time",
    0x4f2d78: "watcom::ceil",
    0x4f45c0: "watcom::stackavail",
    0x4f4610: "watcom::GRO",            # __GRO
    0x4f4b80: "watcom::fprintf",
    0x4f7900: "watcom::nmalloc",        # _nmalloc
    0x4f79f0: "watcom::nfree",          # _nfree
    0x4f7af8: "watcom::TryInit",        # __TryInit
    0x4f7b2a: "watcom::TryHandler",     # __TryHandler
    0x4f7b61: "watcom::TryScope",       # __TryHandler's scopes
    0x4f7b7d: "watcom::Except",         # __Except
    0x4f7b87: "watcom::TryOuter",       # __TryHandler's next scope
    0x4f7b8c: "watcom::TryDone",        # __TryHandler's end
    0x4f7ba7: "watcom::global_unwind",  # __global_unwind
    0x4f7bc3: "watcom::local_unwind",   # __local_unwind
    0x4f7c20: "watcom::atexit",
    0x4f7c90: "watcom::control87",      # _control87
    0x4f7ce0: "watcom::kbhit",
    0x4f7d70: "watcom::fflush",
    0x4f7d80: "watcom::fputs",
    0x4f7e20: "watcom::do_getch",
    0x4f7f24: "watcom::getch",
    0x4f7fa0: "watcom::cstart_",        # _cstart_
    0x4f8020: "watcom::strupr",         # _strupr
    0x4f8040: "watcom::localtime_",     # _localtime
    0x4f8094: "watcom::localtime",
    0x4f80b4: "watcom::IF_DEXP",        # IF@DEXP
    0x4f8116: "watcom::exp",
    0x4f8122: "watcom::Strtold",        # __Strtold
    0x4f82b6: "watcom::strtod",
    0x4f8b50: "watcom::setenv",
    0x4f8ce8: "watcom::setenv_",        # __setenv
    0x4f8f38: "watcom::findenv",        # __findenv
    0x4f9482: "watcom::IF_DACOS",       # IF@DACOS
    0x4fb300: "watcom::bsearch",
    0x4fe1d0: "watcom::prtf",           # __prtf
    0x4fe578: "watcom::prtfSpec",       # __prtf's specification
    0x4fe6cc: "watcom::prtfFlags",      # __prtf's flags
    0x4fe734: "watcom::prtfLength",     # __prtf's strnlen
    0x4fe758: "watcom::prtfWideLength", # __prtf's wide strnlen
    0x4fe7c4: "watcom::prtfHex",        # __prtf's %p digits
    0x4fe81e: "watcom::prtfHexEnd",     # the end of __prtf's %p digits, %hf's too
    0x4fe828: "watcom::prtfFixed",      # __prtf's %hf
    0x4fe924: "watcom::prtfFloat",      # [__EFG_printf]
    0x4fe92c: "watcom::prtfZeros",      # __prtf's zero padding
    0x4fe970: "watcom::prtfWideOut",    # __prtf's %ls
    0x4fe9d4: "watcom::prtfConvert",    # __prtf's conversion
    0x4fefdc: "watcom::prtfUpper",      # __prtf's strupr
    0x4ff000: "watcom::file_putc",
    0x4ff014: "watcom::vfprintf",
    0x4ff0ec: "watcom::GetThreadPtr",   # __GetThreadPtr
    0x4ff0f4: "watcom::NullAccess",     # __NullAccessRtn
    0x4ff108: "watcom::NTInit",         # __NTInit
    0x4ff338: "watcom::NTMain",         # the program's start
    0x4ff38c: "watcom::exit_",          # __exit
    0x4ff3d0: "watcom::freeEnvironment",# the environment's copies freed
    0x4ff410: "watcom::callRoutine",    # __FiniRtns' call
    0x4ff41c: "watcom::InitRtns",       # __InitRtns
    0x4ff46c: "watcom::FiniRtns",       # __FiniRtns
    0x4ff4c0: "watcom::STOSB",          # __STOSB
    0x4ff4f7: "watcom::STOSD",          # __STOSD
    0x4ff624: "watcom::fpatan_wrap",    # __fpatan_wrap
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
    0x5093c0: "watcom::getpid",
    0x5094e0: "watcom::tmpdir",         # __tmpdir
    0x5095b0: "watcom::close",          # __close
    0x509640: "watcom::fixed_GetFileAttributesA", # __fixed_GetFileAttributesA
    0x5096c0: "watcom::qwrite",         # __qwrite
    0x5097b0: "watcom::fputc",
    0x50c540: "watcom::setbits",        # __setbits
    0x50c640: "watcom::cgetc",          # __scnf's
    0x50c648: "watcom::uncget",         # __scnf's
    0x50c650: "watcom::scnf",           # __scnf
    0x50c904: "watcom::get_opt",        # __scnf's
    0x50ca08: "watcom::scan_white",     # __scnf's
    0x50ca48: "watcom::scan_char",      # __scnf's
    0x50cb30: "watcom::scan_string",    # __scnf's
    0x50cc88: "watcom::report_scan",    # __scnf's
    0x50cce8: "watcom::makelist",       # __scnf's
    0x50cd2c: "watcom::scan_arb",       # __scnf's
    0x50ce18: "watcom::scan_float",     # __scnf's
    0x50d0f0: "watcom::scan_int",       # __scnf's
    0x50d510: "watcom::radix_value",    # __scnf's
    0x50d538: "watcom::chktrm",         # __scnf's
    0x50ea4e: "watcom::modf",
    0x50ead0: "watcom::getenv",
    0x50eb30: "watcom::getctime",       # __getctime
    0x50eba0: "watcom::mktime",
    0x511cd0: "watcom::fatalWrite",     # __fatal_runtime_error's
    0x511d0c: "watcom::fatal_runtime_error",# __fatal_runtime_error
    0x515300: "watcom::MemAllocator",   # __MemAllocator
    0x5153b0: "watcom::MemFree",        # __MemFree
    0x5154e0: "watcom::LinkUpNewNHeap", # __LinkUpNewNHeap
    0x515558: "watcom::CreateNewNHeap", # __CreateNewNHeap
    0x515614: "watcom::ExpandDGROUP",   # __ExpandDGROUP
    0x515628: "watcom::AdjustAmount",   # __AdjustAmount
    0x515680: "watcom::nmemneed",       # __nmemneed
    0x515690: "watcom::NTRealKey",      # __NTRealKey
    0x5156b8: "watcom::openConsoles",   # the console's handles
    0x515728: "watcom::NTConsoleInput", # __NTConsoleInput
    0x515734: "watcom::NTConsoleOutput", # __NTConsoleOutput
    0x515850: "watcom::flushall",
    0x515858: "watcom::flushall_",      # __flushall
    0x5158a0: "watcom::mainStart",      # the main thread's start
    0x515b34: "watcom::tzWindows",      # __tzset's without TZ
    0x515c2c: "watcom::tzset",          # __tzset
    0x515c90: "watcom::tzNumber",       # __tzset's number
    0x515cbc: "watcom::tzName",         # __tzset's zone
    0x515dd4: "watcom::tzRule",         # __tzset's rule
    0x515ec2: "watcom::tzDaylight",     # __tzset's daylight saving
    0x515fa0: "watcom::brktime",        # __brktime
    0x5160f0: "watcom::leapyear",       # __leapyear
    0x51612c: "watcom::calc_yday",
    0x516224: "watcom::check_order",
    0x516270: "watcom::isindst",        # __isindst
    0x51652c: "watcom::time_less",
    0x51655c: "watcom::math87_err",     # __math87_err
    0x5165d8: "watcom::ZBuf2LD",        # __ZBuf2LD
    0x51663a: "watcom::normalize",      # __ZBuf2LD's
    0x51667b: "watcom::scalePowers",    # __LDScale10x's
    0x5166cf: "watcom::scaleEnd",       # __LDScale10x's way out
    0x5166d8: "watcom::scaleBy",        # __LDScale10x's
    0x516759: "watcom::LDScale10x",     # __LDScale10x
    0x518050: "watcom::mbslen",         # _mbslen
    0x518080: "watcom::mbstowcs",
    0x518290: "watcom::wsetenv",        # __wsetenv
    0x518498: "watcom::wfindenv",       # __wfindenv
    0x5185c0: "watcom::nrealloc",       # _nrealloc
    0x518640: "watcom::memmove",
    0x51a1ba: "watcom::DSQRT",          # __@DSQRT
    0x51e060: "watcom::wctomb_",        # wctomb's core
    0x51e0a0: "watcom::utoa",
    0x51e0ec: "watcom::itoa",
    0x51e130: "watcom::ulltoa",
    0x51e220: "watcom::prtfUtoa",       # __prtf's utoa
    0x51e2b0: "watcom::handlesFull",    # _sopen's: no handle free
    0x51e304: "watcom::allocPOSIXHandle", # __allocPOSIXHandle
    0x51e45c: "watcom::freePOSIXHandle", # __freePOSIXHandle
    0x51e490: "watcom::initPOSIXHandles", # __initPOSIXHandles
    0x51e4f0: "watcom::NTGetFakeHandle", # __NTGetFakeHandle
    0x51e7ec: "watcom::initThreadData", # the main thread's data
    0x51eb00: "watcom::moduleWideName", # the module's wide name
    0x51eba0: "watcom::copyCommandLine", # the command line's copy
    0x51ebf0: "watcom::copyWideCommandLine", # the wide command line's copy
    0x51ec20: "watcom::stackLimits",    # the stack's limits
    0x51f0d0: "watcom::InitExceptionHandling", # __InitExceptionHandling
    0x51f11c: "watcom::DoneExceptionHandler",# __DoneExceptionHandler
    0x51f320: "watcom::atanSafe",       # __fpatan_wrap's atan2
    0x522d80: "watcom::fsync",
    0x522de0: "watcom::GetIOMode",      # __GetIOMode
    0x522e38: "watcom::SetIOMode",      # __SetIOMode
    0x522e60: "watcom::getche",
    0x5234d0: "watcom::GetNTAccessAttr", # __GetNTAccessAttr
    0x523504: "watcom::GetNTShareAttr", # __GetNTShareAttr
    0x523560: "watcom::isatty",
    0x523610: "watcom::fullpath",       # _fullpath
    0x523c00: "watcom::mbtowc",
    0x523ca0: "watcom::FDFS",           # __FDFS
    0x523cec: "watcom::U8M",            # __U8M
    0x523d10: "watcom::mbsnicmp",       # _mbsnicmp
    0x524190: "watcom::EnterWVIDEO",    # __EnterWVIDEO
    0x5241c0: "watcom::nheapshrink",    # _nheapshrink
    0x5241fc: "watcom::ReturnMemToSystem", # __ReturnMemToSystem
    0x52425c: "watcom::ReleaseNHeap",   # _nheapshrink's step
    0x524290: "watcom::callMain",       # main's call
    0x5242f0: "watcom::wcstombs",
    0x5243a7: "watcom::reporterror",    # __reporterror
    0x5243b1: "watcom::reportError",    # __reporterror's struct exception
    0x5250c0: "watcom::mbterm",         # _mbterm
    0x525100: "watcom::mbsinc",         # _mbsinc
    0x5252a0: "watcom::create_wide_environment",# __create_wide_environment
    0x525300: "watcom::wcslen",
    0x525320: "watcom::memcpy",
    0x525350: "watcom::wcscpy",
    0x525370: "watcom::towupper",       # the environment's towupper
    0x525380: "watcom::msize",          # _msize
    0x525390: "watcom::nexpand",        # _nexpand
    0x5253cc: "watcom::HeapManager_expand",# __HeapManager_expand
    0x525578: "watcom::nexpandFailed",  # _nexpand's way out
    0x525d59: "watcom::U8D",            # __U8D
    0x525df0: "watcom::calloc",
    0x526030: "watcom::initThread",     # the thread's data's start
    0x5269d4: "watcom::fdivSafe",       # __fdiv_fpr's division
    0x526aeb: "watcom::fdiv_fpr",       # __fdiv_fpr
    0x52b290: "watcom::putch",
    0x52b5b0: "watcom::mbclen",         # _mbclen
    0x52b5e0: "watcom::mbcicmp",        # _mbcicmp
    0x52b640: "watcom::startHook",      # a start-up hook
    0x52b647: "watcom::printMathError", # the maths' error printed
    0x52b68f: "watcom::callMatherr",    # _matherr's call
    0x52c178: "watcom::wputenv",        # __wputenv
    0x52c300: "watcom::wputenvFind",    # __wputenv's find
    0x52e310: "watcom::mbccpy",         # _mbccpy
    0x52e350: "watcom::mbsupr",         # _mbsupr
    0x52e3a0: "watcom::mbccmp",         # _mbccmp
    0x52e400: "watcom::get_std_stream", # __get_std_stream
    0x52ed30: "watcom::mbsnextc",       # _mbsnextc
    0x52ed70: "watcom::mbctoupper",     # _mbctoupper
    0x52ede0: "watcom::mbvtop",         # _mbvtop
    0x52eec0: "watcom::mbcupper932",    # _mbctoupper's, code page 932
    0x52eee0: "watcom::mbclower",       # _ismbclower's, code page 932
    0x52ef30: "watcom::mbclegal",       # _ismbclegal's
    0x52ef70: "watcom::mbbtrail",       # _ismbbtrail's
    0x533de4: "watcom::RtlUnwindThunk", # RtlUnwind's import
}
GAME_NATIVES.update(WATCOM_NATIVES)

# The menus' text and what the screens do around their items, native: each
# address is the port's function of that name in nfs3hp::frontend --
# src/nfs3hp/native_frontend_text.cpp's a line of the language's text by its
# number, the names past them, the checks of a line typed in, the font a text
# is measured and drawn in; native_frontend_screen.cpp's the pointer and the
# screens' art.  tools/game_checks compares them with their generated code.
FRONTEND_NATIVES = {
    0x43d9f0: "frontend::controllerName",
    0x448400: "frontend::displayModeName",
    0x4721f0: "frontend::nameValid",
    0x4d17b0: "frontend::specialText",
    0x4d1850: "frontend::languageText",
    0x443630: "frontend::shortNameCharacter",
    0x443660: "frontend::shortNameValid",
    0x443700: "frontend::languageNameValid",
    0x443780: "frontend::languageFileNameValid",
    0x443860: "frontend::lineAllowed",
    0x452020: "frontend::textWidth",
    0x452100: "frontend::selectFont",
    0x4d1430: "frontend::measureText",
    0x4d1480: "frontend::textWidthWithOverhang",
    0x4d1000: "frontend::drawText",
    0x4d06f0: "frontend::drawCharacter",
    0x49bcd0: "frontend::takeQuad",
    0x4beb80: "frontend::viewport",
    0x451400: "frontend::toScreenX",
    0x451440: "frontend::toScreenY",
    0x435230: "frontend::placePointer",
    0x49bfc0: "frontend::setPointer",
    0x440970: "frontend::loadScreenArt",
}
GAME_NATIVES.update(FRONTEND_NATIVES)

# The controls, native: each address is the port's function of that name in
# nfs3hp::controls -- src/nfs3hp/native_controls_input.cpp's the game's side
# of DirectInput (the devices found and opened, the mouse, the keyboard, the
# joysticks read, their force-feedback effects); native_controls_devices.cpp's
# the control sets the game makes for the devices it knows; and
# native_controls_race.cpp's the controls read in a race and kept in
# config.dat; native_controls_pipeline.cpp's the controls read and turned
# into the players' actions every frame of a race; native_controls_queue.cpp's
# the race's queue of inputs, by frame and player, that hands them to the cars
# and to the other machines in a network race, and the edges of the keys and
# actions the race's screens ask about.  tools/game_checks compares
# them with their generated code;
# what one of these files calls of another's it calls by address.
CONTROLS_INPUT_NATIVES = {
    0x434f20: "controls::startDirectInput",
    0x434fd0: "controls::stopDirectInput",
    0x4350a0: "controls::openMouse",
    0x4352d0: "controls::setPointerBounds",
    0x435310: "controls::readMouse",
    0x435600: "controls::findJoysticks",
    0x435690: "controls::describeJoystick",
    0x4358f0: "controls::readJoystick",
    0x435ae0: "controls::readAxisZone",
    0x435b40: "controls::setAxisZone",
    0x435b60: "controls::resetForceFeedback",
    0x435bc0: "controls::setAutocenter",
    0x435c60: "controls::pauseEffects",
    0x435cc0: "controls::continueEffects",
    0x435d20: "controls::actuatorsOn",
    0x435d90: "controls::actuatorsOff",
    0x435df0: "controls::setGain",
    0x435f10: "controls::createEffect",
    0x4361e0: "controls::startEffect",
    0x436230: "controls::stopEffect",
    0x436270: "controls::stopEffects",
    0x4362f0: "controls::downloadEffect",
    0x436310: "controls::unloadEffect",
    0x436330: "controls::updateEffect",
    0x436610: "controls::setCooperativeLevel",
    0x4366e0: "controls::acquireDevice",
    0x436800: "controls::unacquireDevice",
    0x4368c0: "controls::acquireResult",
    0x4368f0: "controls::effectPlaying",
    0x436930: "controls::hideCursor",
    0x436980: "controls::joystickFound",
    0x436b10: "controls::axisProperty",
}
CONTROLS_DEVICES_NATIVES = {
    0x4904d0: "controls::controlsFor",
    0x4904f0: "controls::defaultControls",
    0x4905b0: "controls::setControls",
    0x490610: "controls::controllerNamed",
    0x490640: "controls::knownControllerControls",
    0x4906b0: "controls::sideWinderGamePadControls",
    0x490770: "controls::gravisGripControls",
    0x490830: "controls::wingManForceControls",
    0x4908f0: "controls::combatStickControls",
    0x4909b0: "controls::sideWinderProControls",
    0x490a70: "controls::sideWinderWheelControls",
    0x490b30: "controls::steeringWheelControls",
    0x490c40: "controls::keyboardControls",
    0x490cb0: "controls::gamePadControls",
    0x490e30: "controls::joystickControls",
    0x490fa0: "controls::otherControllerControls",
}
CONTROLS_RACE_NATIVES = {
    0x470bc0: "controls::steadyEngineRumble",
    0x470c60: "controls::startEngineRumble",
    0x470cb0: "controls::silenceEngineRumble",
    0x470d10: "controls::setForceGain",
    0x470d30: "controls::findForceController",
    0x470dc0: "controls::createForceEffects",
    0x470f40: "controls::stopForces",
    0x470f80: "controls::stopForcesAgain",
    0x470fc0: "controls::stopForcesOnceMore",
    0x471000: "controls::stopForcesOrActuatorsOn",
    0x471070: "controls::stopForcesOrActuatorsOff",
    0x4710f0: "controls::forcePlayerCar",
    0x4711e0: "controls::startRaceForces",
    0x471240: "controls::stopRaceEffects",
    0x471270: "controls::crashJolt",
    0x471440: "controls::bumpJolt",
    0x4714f0: "controls::gearChangeKick",
    0x471650: "controls::steeringAmount",
    0x4716e0: "controls::playSteeringSpring",
    0x471860: "controls::playSlideSpring",
    0x4719f0: "controls::playRoadRumble",
    0x471af0: "controls::playEngineRumble",
    0x471dc0: "controls::isForceCar",
    0x471e10: "controls::raceForcesFrame",
    0x471fb0: "controls::allActuatorsOff",
    0x471fd0: "controls::playJolt",
    0x4720a0: "controls::stopEngineRumble",
    0x4720e0: "controls::stopSteeringSpring",
    0x472110: "controls::carSpeedMph",
    0x472b60: "controls::loadControllers",
}
CONTROLS_PIPELINE_NATIVES = {
    0x431580: "controls::clearJoysticks",
    0x4315a0: "controls::readJoysticks",
    0x431690: "controls::pollJoystick",
    0x4316c0: "controls::buttonHeld",
    0x4316f0: "controls::hatPointing",
    0x431740: "controls::axisAmount",
    0x4317d0: "controls::keyHeld",
    0x431800: "controls::controlHeld",
    0x431880: "controls::controlHeldNo",
    0x431885: "controls::controlHeldYes",
    0x43188d: "controls::controlHeldByKind",
    0x4318b0: "controls::noControl",
    0x48f1f0: "controls::bindPlayersControls",
    0x48f4f0: "controls::startRaceControls",
    0x48f550: "controls::readRaceControls",
    0x48f940: "controls::bindControl",
    0x48f970: "controls::bindFunctionKeys",
    0x48fa10: "controls::queueRaceControls",
}
CONTROLS_QUEUE_NATIVES = {
    0x48f6a0: "controls::takeCarControls",
    0x48f6e0: "controls::stepMenuChoice",
    0x48f710: "controls::stepMenuChoiceOfThree",
    0x48f740: "controls::actionPressed",
    0x48f7b0: "controls::functionKeyPressed",
    0x48f820: "controls::pressFunctionKey",
    0x48f860: "controls::functionKeyRepeats",
    0x48f8d0: "controls::keyPressed",
    0x48f920: "controls::firstFunctionKeyHeld",
    0x4c6080: "controls::appendToPacket",
    0x4c60c0: "controls::sendOwnInput",
    0x4c61e0: "controls::receiveInput",
    0x4c6530: "controls::queueInput",
    0x4c66a0: "controls::queueRemoteInput",
    0x4c67a0: "controls::takeQueuedFrame",
    0x4c6840: "controls::takenControls",
    0x4c6870: "controls::repeatMissingInputs",
    0x4c6970: "controls::syncFrame",
    0x4c69a0: "controls::framesTaken",
    0x4c69b0: "controls::framesQueued",
    0x4c69c0: "controls::queueLead",
    0x4c6a10: "controls::noteLag",
    0x4c6a40: "controls::setQueueDelays",
    0x4c6ae0: "controls::queueFull",
}
CONTROLS_GROUPS = (CONTROLS_INPUT_NATIVES, CONTROLS_DEVICES_NATIVES, CONTROLS_RACE_NATIVES,
                   CONTROLS_PIPELINE_NATIVES, CONTROLS_QUEUE_NATIVES)
for group in CONTROLS_GROUPS:
    GAME_NATIVES.update(group)

# EA's platform libraries, native whole, in nfs3hp::ea: native_ea_threads.cpp's
# threads, events, timers and locks; native_ea_memory.cpp's memory manager and
# memmove; native_ea_files.cpp's files, read and written a block at a time;
# native_ea_support.cpp's trace and log, files loaded whole and .viv archives.
# tools/game_checks compares them with their generated code.
EA_THREADS_NATIVES = {
    0x4df6f0: "ea::waitForObjects",
    0x4df730: "ea::threadStart",
    0x4df740: "ea::threadsInit",
    0x4df7a0: "ea::createThread",
    0x4df870: "ea::removeThread",
    0x4df8e0: "ea::sleepMs",
    0x4df8f0: "ea::sleepTicks",
    0x4df930: "ea::isThread",
    0x4df980: "ea::threadPriority",
    0x4dfa30: "ea::setThreadPriority",
    0x4dfaf0: "ea::exitThread",
    0x4dfb00: "ea::createEvent",
    0x4dfb20: "ea::postEvent",
    0x4dfb30: "ea::signalEvent",
    0x4dfb40: "ea::pollEvent",
    0x4dfb70: "ea::waitEvent",
    0x4dfb90: "ea::waitEventTicks",
    0x4dfbf0: "ea::waitForAny",
    0x4dfc00: "ea::closeEvent",
    0x4dfc10: "ea::createManualEvent",
    0x4dfc30: "ea::setEvent",
    0x4dfc40: "ea::resetEvent",
    0x4dfc50: "ea::pulseEvent",
    0x4dfc60: "ea::waitManualEvent",
    0x4dfc80: "ea::setAndCloseEvent",
    0x4dfca0: "ea::lastErrorText",
    0x4dfce0: "ea::setLastError",
    0x4dfcf0: "ea::lastError",
    0x4dfd00: "ea::doNothing",
    0x4dfd80: "ea::xRotation",
    0x4dfde0: "ea::yRotation",
    0x4dfe40: "ea::zRotation",
    0x4dfea0: "ea::axisRotation",
    0x4eb230: "ea::randomFraction",
    0x4eb260: "ea::growLocks",
    0x4eb2e0: "ea::makeLock",
    0x4eb340: "ea::enterLock",
    0x4eb350: "ea::leaveLock",
    0x4eb360: "ea::freeLock",
    0x4f9070: "ea::surfaceLocked",
    0x5221f0: "ea::physicalMemory",
}
EA_MEMORY_NATIVES = {
    0x4e1000: "ea::findFreeBlock",
    0x4e1030: "ea::findLargestFreeBlock",
    0x4e1080: "ea::linkFreeBlock",
    0x4e10e0: "ea::unlinkFreeBlock",
    0x4e1100: "ea::clearMemClasses",
    0x4e1120: "ea::markMemBlock",
    0x4e11e0: "ea::memClassOverhead",
    0x4e11f0: "ea::memBlockOverhead",
    0x4e1230: "ea::creatememclass",
    0x4e14b0: "ea::releasememclass",
    0x4e1500: "ea::getfreememclass",
    0x4e1580: "ea::largestmem",
    0x4e15b0: "ea::largestmemclass",
    0x4e15d0: "ea::memBlockSize",
    0x4e15e0: "ea::memBlockName",
    0x4e1610: "ea::memBlockFlags",
    0x4e1620: "ea::reservememadr",
    0x4e1890: "ea::purgememadr",
    0x4e1990: "ea::purgememclass",
    0x4e19d0: "ea::reservememStdcall",
    0x4e19f0: "ea::purgememStdcall",
    0x4ea4f0: "ea::memmove",
    0x503280: "ea::fpuCopySwapped",
    0x503281: "ea::fpuCopy",
    0x50356c: "ea::dwordCopySwapped",
    0x50356d: "ea::dwordCopy",
}
EA_FILES_NATIVES = {
    0x4e28c0: "ea::initHandlesDefault",
    0x4e28d0: "ea::openHandle",
    0x4e2ab0: "ea::openHandleErrorsAs",
    0x4e2ae0: "ea::openHandleToWrite",
    0x4e2ba0: "ea::openMapHandle",
    0x4e2da0: "ea::closeHandle",
    0x4e2de0: "ea::readHandle",
    0x4e2e20: "ea::writeHandle",
    0x4e2e60: "ea::seekHandle",
    0x4e2eb0: "ea::isSlash",
    0x4e2ebe: "ea::notSlash",
    0x4e2ed0: "ea::volumeRoot",
    0x4e2fd0: "ea::fullPathName",
    0x4e3110: "ea::logicalDrives",
    0x4e3120: "ea::driveOfPath",
    0x4e3250: "ea::driveLetter",
    0x4e32e0: "ea::diskFreeBytes",
    0x4e3330: "ea::driveNumber",
    0x4e3340: "ea::setDirectory",
    0x4e33a0: "ea::getDirectory",
    0x4e3410: "ea::handlesReady",
    0x4e3430: "ea::initHandles",
    0x4e34c0: "ea::closeAllHandles",
    0x4e3570: "ea::takeHandleSlot",
    0x4e3600: "ea::deleteFile",
    0x4e3620: "ea::openFileHandle",
    0x4e3980: "ea::handleInfo",
    0x4e3ae0: "ea::readHandleBytes",
    0x4e3cc0: "ea::writeHandleBytes",
    0x4e3e60: "ea::seekHandleTo",
    0x4e3f30: "ea::handlePosition",
    0x4e3fe0: "ea::closeHandleSlot",
    0x4e40a0: "ea::lockHandleDrive",
    0x4e40f0: "ea::unlockHandleDrive",
    0x4e4140: "ea::openMemoryHandle",
    0x4e41f0: "ea::handleMemory",
    0x501010: "ea::checkSurfaceUnlocked",
    0x501050: "ea::fileReport",
    0x501110: "ea::virtualAllocPages",
    0x501180: "ea::virtualFreePages",
    0x5011a0: "ea::touchMemoryPages",
    0x501270: "ea::openBlockHandle",
    0x501360: "ea::blockHandleFile",
    0x5013a0: "ea::closeBlockHandle",
    0x5013b0: "ea::readBlockHandle",
    0x501450: "ea::seekBlockHandle",
}
EA_SUPPORT_NATIVES = {
    0x42d510: "ea::gameTrace",
    0x43b830: "ea::openViv",
    0x43b9b0: "ea::closeViv",
    0x43b9d0: "ea::findInViv",
    0x4679f0: "ea::findVivEntry",
    0x4e08f0: "ea::monoPrintf",
    0x4e0980: "ea::monoPrintfAt",
    0x4e0a60: "ea::monoWrite",
    0x4e0c10: "ea::monoScroll",
    0x4e0ca0: "ea::monoClear",
    0x4e0d00: "ea::monoSetTop",
    0x4e0d50: "ea::monoSetAttribute",
    0x4e0d60: "ea::monoSetTab",
    0x4e0d70: "ea::monoPage",
    0x4e0d80: "ea::monoNoCursor",
    0x4e0dee: "ea::seedRandom",
    0x4e0e60: "ea::fileExists",
    0x4e0ec0: "ea::loadFile",
    0x4e0fe0: "ea::loadFileQuietly",
}
EA_NET_NATIVES = {
    0x49ecb0: "ea::dropMachine",
    0x49ecf0: "ea::announceMachineLeft",
    0x49eed0: "ea::endNetworkGame",
    0x49f1c0: "ea::sessionIndex",
    0x49f550: "ea::forgetPendingPlayer",
    0x4a5d10: "ea::sendOverLink",
    0x4a60e0: "ea::sendPacket",
    0x4a6390: "ea::resetNetwork",
    0x4a65e0: "ea::closeNetwork",
    0x4a6650: "ea::machineNumber",
    0x4a6690: "ea::playerMachine",
    0x4f4c50: "ea::netTrace",
    0x4f4f50: "ea::netShutGame",
    0x4f4f90: "ea::netEndGame",
    0x4f4ff0: "ea::netKillPlayer",
    0x4f5040: "ea::netCheckPlayer",
    0x4f5280: "ea::connRestore",
    0x4f5310: "ea::connSend",
    0x4f5330: "ea::connClose",
    0x50dc00: "ea::qnth",
    0x50dc20: "ea::qunlink",
    0x50dde0: "ea::qfree",
    0x50e150: "ea::qremove",
    0x50e1d0: "ea::qlength",
    0x50e220: "ea::qposition",
    0x50e470: "ea::qfindindex",
    0x50ed50: "ea::huffUnpack",
    0x510110: "ea::runUnpack",
    0x510420: "ea::dxtBlock",
    0x510760: "ea::dxtUnpack",
    0x510820: "ea::pairExpand",
    0x510870: "ea::pairUnpack",
    0x5123b0: "ea::layerSend",
    0x512530: "ea::layerCallPacker",
    0x512630: "ea::layerPackFromTop",
    0x5126c0: "ea::layerFree",
    0x512770: "ea::layerSendPacket",
}
EA_FORMATS_NATIVES = {
    0x4ef270: "ea::locateShape",
    0x4f0010: "ea::keyCharacter",
    0x4f0100: "ea::keyFromHook",
    0x4f0120: "ea::inkey",
    0x4f0240: "ea::flushKeys",
    0x4f2560: "ea::unpackQuietly",
    0x4f2620: "ea::unpack",
    0x4f26a0: "ea::unpackSizeQuietly",
    0x4f2710: "ea::unpacksize",
    0x4f2830: "ea::stopLowTimer",
    0x4f29b0: "ea::removeLowTimer",
    0x4f2e20: "ea::loadpackadr",
}
EA_GROUPS = (EA_THREADS_NATIVES, EA_MEMORY_NATIVES, EA_FILES_NATIVES, EA_SUPPORT_NATIVES,
             EA_NET_NATIVES, EA_FORMATS_NATIVES)
for group in EA_GROUPS:
    GAME_NATIVES.update(group)

# The game's data loaded and saved, native whole, in nfs3hp::load:
# native_load_track.cpp's race data files (the track's file cache, paths,
# textures, horizon, sky and weather, the opponents' speeds, the cameras, the
# ghost); native_load_cardb.cpp's cars' database (fedata, car.viv, .FEC,
# carp.txt); native_load_carmodels.cpp's cars' models and specs (.fce, .art,
# carspecs); native_load_saves.cpp's replays, records and config.dat, and
# EA's BIG archives, savefile and shape comments under them.
# tools/game_checks compares them with their generated code.
LOAD_TRACK_NATIVES = {
    0x40e000: "load::loadOpponentSpeeds",
    0x40f230: "load::clearTrackCameras",
    0x40f280: "load::loadTrackCameras",
    0x418d00: "load::swapBigEndian",
    0x418d40: "load::newFileNode",
    0x418d70: "load::freeFileNode",
    0x418dd0: "load::findFileNode",
    0x418e90: "load::insertFileNode",
    0x418f00: "load::newEmptyFileNode",
    0x418f40: "load::freeFileNodes",
    0x418f70: "load::countFileNodes",
    0x418fe0: "load::findCachedFile",
    0x419000: "load::addCachedFile",
    0x419080: "load::newFileCache",
    0x4190e0: "load::freeFileCache",
    0x419120: "load::bigHeaderSize",
    0x4191b0: "load::cachedDataSize",
    0x4191e0: "load::writeBigFile",
    0x419460: "load::packFileCache",
    0x419510: "load::readBigFile",
    0x4195f0: "load::openFileCache",
    0x41d8a0: "load::trackFilePath",
    0x41d8d0: "load::trackFolderPath",
    0x41dbc0: "load::loadTrackTextures",
    0x477a90: "load::saveGhost",
    0x477ac0: "load::writeGhost",
    0x477b00: "load::readGhost",
    0x478340: "load::loadHorizon",
    0x47ac30: "load::loadSky",
    0x4dcd20: "load::loadWeatherShapes",
}
LOAD_CARDB_NATIVES = {
    0x438340: "load::endWithSlash",
    0x438350: "load::folderWritable",
    0x4383f0: "load::firstFreeHexFolder",
    0x4384f0: "load::firstFreePlayerFolder",
    0x4385a0: "load::freePlayerCarFolder",
    0x4386b0: "load::firstSubfolder",
    0x4387e0: "load::nextSubfolder",
    0x438870: "load::firstFile",
    0x438970: "load::nextFile",
    0x4389d0: "load::removeFolder",
    0x438a80: "load::firstCar",
    0x438aa0: "load::nextCar",
    0x438ad0: "load::makeCarId",
    0x438af0: "load::firstCarGlobal",
    0x438b10: "load::nextCarGlobal",
    0x438b90: "load::appendCar",
    0x438bd0: "load::carCount",
    0x438be0: "load::countCars",
    0x438c10: "load::unlinkCar",
    0x438c50: "load::insertCarByName",
    0x438cc0: "load::joinCarLists",
    0x438d20: "load::carListOf",
    0x438d60: "load::takePoliceCars",
    0x438dc0: "load::takeClasslessCars",
    0x438e30: "load::takeOrdinaryCars",
    0x438eb0: "load::sortCars",
    0x439250: "load::carName",
    0x4392b0: "load::carFolder",
    0x439300: "load::carFilePrefix",
    0x439520: "load::carId",
    0x439570: "load::carFlag40",
    0x4395c0: "load::carFlag4",
    0x439610: "load::carHasNumericId",
    0x439620: "load::idIsNumeric",
    0x439660: "load::numericId",
    0x439680: "load::carIsBonus",
    0x4396b0: "load::carIsPolice",
    0x4396e0: "load::carIsFerrariOrMercedes",
    0x439730: "load::carClass",
    0x439990: "load::findCarById",
    0x4399f0: "load::clearCarCache",
    0x439a50: "load::carRecord",
    0x439af0: "load::fecText",
    0x439b20: "load::findCarByName",
    0x439bd0: "load::attachFecTexts",
    0x439c10: "load::bonusCarLocked",
    0x439d20: "load::checkDuplicateCars",
    0x439d90: "load::loadCarList",
    0x43a4f0: "load::carSelectable",
    0x43a580: "load::buildCarClassLists",
    0x43ae60: "load::copyCarAsNew",
    0x43b3f0: "load::loadCarSpecs",
    0x43b4f0: "load::writeCarFec",
    0x43b570: "load::readCarFecBody",
    0x43b630: "load::readCarFec",
    0x43b680: "load::carFecPath",
    0x43b740: "load::loadCarFec",
    0x43ba20: "load::placeCarVivPath",
    0x43ba30: "load::swapBytes",
    0x43ba70: "load::writeBigEndian",
    0x43baa0: "load::appendCarpToViv",
    0x43bbf0: "load::lastCarLoaded",
    0x43bc00: "load::setLastCarId",
    0x43bc40: "load::setLastCarName",
    0x43bc70: "load::setLastCarFlags",
    0x43bc90: "load::markLastCarFlag8",
}
LOAD_CARMODELS_NATIVES = {
    0x49b540: "load::beginCarpReceive",
    0x49b5f0: "load::receiveCarpChunk",
    0x49b800: "load::beginCarpSend",
    0x49c700: "load::readCarColors",
    0x49c880: "load::rgbToHsv",
    0x49ca50: "load::hsvToRgb",
    0x49cc50: "load::tintPixel",
    0x49cd00: "load::scaleTexture",
    0x49cea0: "load::fitTexture",
    0x49d130: "load::loadArtTextures",
    0x49d240: "load::nearestModelColor",
    0x49d320: "load::loadTgaTexture",
    0x49d450: "load::loadCarModel",
    0x4b7a60: "load::loadVivCarModel",
    0x4b7ba0: "load::copyVivCarModel",
    0x4dc3a0: "load::setSpecUsed",
    0x4dc3f0: "load::specUsed",
    0x4dc440: "load::specCarName",
    0x4dc490: "load::findSpec",
    0x4dc500: "load::freeSpecSlot",
    0x4dc5a0: "load::setSpec",
    0x4dc670: "load::defaultSpecs",
    0x4dc710: "load::refreshSpecs",
    0x4dc800: "load::specPath",
    0x4dc8b0: "load::readSpecs",
    0x4dc940: "load::loadPlayerSpecs",
    0x4dca50: "load::savePlayerSpecs",
}
LOAD_SAVES_NATIVES = {
    0x446060: "load::readReplayInfo",
    0x446780: "load::saveGhostAs",
    0x446990: "load::loadKeptReplay",
    0x446a10: "load::saveReplayAs",
    0x4475a0: "load::listReplays",
    0x44f510: "load::loadRecords",
    0x44f5f0: "load::saveRecords",
    0x472230: "load::languageStub",
    0x472250: "load::setLanguage",
    0x472300: "load::setCameraViews",
    0x4723f0: "load::defaultConfig",
    0x472820: "load::saveConfig",
    0x4728e0: "load::fileWriteTime",
    0x472940: "load::fileOlder",
    0x472980: "load::loadConfig",
    0x4bd1e0: "load::saveRaceReplay",
    0x4bd2e0: "load::readRaceReplay",
    0x4e9f00: "load::typeOfBigFile",
    0x4e9fe0: "load::bigHeaderLength",
    0x4ea040: "load::findBigEntry",
    0x4ea290: "load::locateBigEntry",
    0x4eeae0: "load::savefileadr",
    0x4eebb0: "load::savefileadrQuietly",
    0x4f2380: "load::fixedSine",
    0x4f23f0: "load::fixedCosine",
}
LOAD_GROUPS = (LOAD_TRACK_NATIVES, LOAD_CARDB_NATIVES, LOAD_CARMODELS_NATIVES, LOAD_SAVES_NATIVES)
for group in LOAD_GROUPS:
    GAME_NATIVES.update(group)

# What the main menu calls of the game's own, native whole, in nfs3hp::frontend:
# native_frontend_glue.cpp's -- a race started or the game left, the HUD's art,
# the attract mode's movies, the lists' keys -- and native_frontend_draw.cpp's
# -- the menus' 3D and 2D drawing, text and shapes.  tools/game_checks
# compares them with their generated code.
FRONTEND_GLUE_NATIVES = {
    0x43c000: "frontend::bindingIsDigital",
    0x43c040: "frontend::noteDigitalControls",
    0x442bf0: "frontend::listAllowed",
    0x442c50: "frontend::listLength",
    0x442c80: "frontend::findList",
    0x44ac90: "frontend::loadShapes",
    0x4513c0: "frontend::setTextColour",
    0x451480: "frontend::screenToMenuX",
    0x4514c0: "frontend::screenToMenuY",
    0x451500: "frontend::readMenuMouse",
    0x451530: "frontend::dimBackground",
    0x451590: "frontend::drawTextAt",
    0x452190: "frontend::drawMenuText",
    0x461270: "frontend::buttonKey",
    0x463ff0: "frontend::listKey",
    0x464560: "frontend::layoutList",
    0x46c950: "frontend::sliderSetValue",
    0x46c9b0: "frontend::sliderValue",
    0x46cac0: "frontend::sliderSetOnMove",
    0x46cae0: "frontend::sliderDraw",
    0x46cca0: "frontend::sliderSetColour",
    0x4960e0: "frontend::playMovie",
    0x4961e0: "frontend::resetAttractTimer",
    0x496200: "frontend::attractMode",
    0x49a4d0: "frontend::freeNetworkLocks",
    0x49ab60: "frontend::allPlayersReady",
    0x49be40: "frontend::flushQuads",
    0x49c080: "frontend::mouseKey",
    0x49c1f0: "frontend::pointerInBox",
    0x4cc970: "frontend::nextKey",
}
FRONTEND_DRAW_NATIVES = {
    0x4613e0: "frontend::layoutMenuItem",
    0x4692c0: "frontend::sliderPartUnderPointer",
    0x469340: "frontend::sliderThumbPlace",
    0x4693c0: "frontend::snapToStep",
    0x469480: "frontend::setSliderValue",
    0x469520: "frontend::sliderStoredValue",
    0x469590: "frontend::dragSliderTo",
    0x469680: "frontend::drawSlider",
    0x46a5f0: "frontend::trackSlider",
    0x46ac40: "frontend::twoAxisThumbPlace",
    0x46add0: "frontend::setTwoAxisValue",
    0x46afd0: "frontend::twoAxisValue",
    0x46b040: "frontend::dragTwoAxisTo",
    0x46b3a0: "frontend::drawTwoAxis",
    0x46c320: "frontend::trackTwoAxis",
    0x4956f0: "frontend::loadQfs",
    0x4d1340: "frontend::flushFonts",
    0x4d1390: "frontend::setTextScale",
    0x4d1400: "frontend::keepTextScale",
    0x4d1410: "frontend::restoreTextScale",
    0x4d1540: "frontend::characterWidth",
    0x4d1590: "frontend::characterOverhang",
    0x4d5840: "frontend::quadOutcodes",
    0x4d5db0: "frontend::shapeByName",
    0x4d7990: "frontend::drawShape",
    0x4d8550: "frontend::gradientRectangle",
    0x4d8910: "frontend::filledRectangle",
    0x4d8930: "frontend::frame",
    0x4d9320: "frontend::accentedCharacter",
    0x4d95c0: "frontend::drawScreenCharacter",
    0x4da4a0: "frontend::drawScreenText",
    0x4db000: "frontend::drawTexturedQuad",
    0x4db380: "frontend::drawShadedQuad",
}
FRONTEND_GROUPS = (FRONTEND_GLUE_NATIVES, FRONTEND_DRAW_NATIVES)
for group in FRONTEND_GROUPS:
    GAME_NATIVES.update(group)

# A car's race state, native whole, in nfs3hp::racestart (native_racestart.cpp):
# put back on the road, its wheels' marks, smoke and sounds, the camera's
# shake, a crash's effects, and the start's grid (TRKnnn\start.dat) with a car
# placed on it.  tools/game_checks compares them with their generated code.
RACESTART_NATIVES = {
    0x428f90: "racestart::respawnCar",
    0x429100: "racestart::resetCar",
    0x429260: "racestart::stuckCheck",
    0x4294c0: "racestart::clearRespawn",
    0x4294e0: "racestart::shakeAmplitude",
    0x4295a0: "racestart::startShake",
    0x4296c0: "racestart::startIdleShake",
    0x429790: "racestart::shakeWave",
    0x4297d0: "racestart::objectContacts",
    0x429880: "racestart::wheelSlip",
    0x4299a0: "racestart::wheelCells",
    0x429b40: "racestart::wheelSurface",
    0x429ba0: "racestart::endSkidMark",
    0x429d20: "racestart::extendSkidMark",
    0x429f10: "racestart::skidSounds",
    0x42a130: "racestart::wheelSpray",
    0x42a280: "racestart::surfaceEffects",
    0x42a480: "racestart::wheelSkid",
    0x42a560: "racestart::wheelEffects",
    0x42a7d0: "racestart::updateShake",
    0x42ac40: "racestart::crashEffects",
    0x42b480: "racestart::respawnEffects",
    0x42b660: "racestart::stopCarEffects",
    0x42b780: "racestart::carEffects",
    0x42b7b0: "racestart::airborneSpin",
    0x42b900: "racestart::updateCar",
    0x42ba00: "racestart::defaultGridPlace",
    0x42bb80: "racestart::loadStartGrid",
    0x42bc70: "racestart::gridPlace",
    0x42bcb0: "racestart::placeOnGrid",
}
GAME_NATIVES.update(RACESTART_NATIVES)

# The race's cars loaded, kept up and in collision, the race's messages and
# its controls' thread (0x42c2a0 to 0x42f550), native whole in nfs3hp::raceload
# (native_raceload.cpp).  tools/game_checks compares them with their generated code.
RACELOAD_NATIVES = {
    0x42c2a0: "raceload::loadCarPerformance",
    0x42c350: "raceload::loadRaceCar",
    0x42c400: "raceload::setCarHandlers",
    0x42c520: "raceload::freeCarShapes",
    0x42c530: "raceload::restartRaceCars",
    0x42c660: "raceload::clearCarSlots",
    0x42c680: "raceload::clearRaceCounts",
    0x42c6d0: "raceload::clearCarList",
    0x42c700: "raceload::loadRaceCars",
    0x42c7f0: "raceload::setTimeStep",
    0x42c830: "raceload::addCarTasks",
    0x42c950: "raceload::openCarViv",
    0x42ca80: "raceload::closeCarViv",
    0x42cab0: "raceload::removeCarTasks",
    0x42cc20: "raceload::countLaps",
    0x42cd00: "raceload::carAxesSpeed",
    0x42cdd0: "raceload::carForwardSpeed",
    0x42ce10: "raceload::carRaceDistance",
    0x42ce70: "raceload::updateRaceCars",
    0x42cff0: "raceload::frameFraction",
    0x42d020: "raceload::placeHeadlights",
    0x42d160: "raceload::placeCarShadow",
    0x42d3e0: "raceload::sortRaceCars",
    0x42d500: "raceload::emptyHook",
    0x42d520: "raceload::emptyHook2",
    0x42d620: "raceload::showMessage",
    0x42d710: "raceload::sendMessage",
    0x42d790: "raceload::openMessages",
    0x42d7f0: "raceload::closeMessages",
    0x42d800: "raceload::clearMessages",
    0x42d810: "raceload::sendTypedMessage",
    0x42d860: "raceload::newMessageLine",
    0x42d8a0: "raceload::freeMessageLine",
    0x42d8b0: "raceload::insertMessageLine",
    0x42d910: "raceload::freeMessageLines",
    0x42d940: "raceload::clearMessageLines",
    0x42d9b0: "raceload::showMessageLines",
    0x42da30: "raceload::appendMessageLine",
    0x42daf0: "raceload::closeMessageLines",
    0x42db70: "raceload::openMessageLines",
    0x42dc20: "raceload::raceControlsThread",
    0x42dc40: "raceload::wakeRaceControls",
    0x42dc60: "raceload::raceControlsTick",
    0x42dcb0: "raceload::startRaceControlsTick",
    0x42dd00: "raceload::stopRaceControlsTick",
    0x42dd60: "raceload::cornerInBox",
    0x42e010: "raceload::cornerInBoxBack",
    0x42e2c0: "raceload::cornerInBox2",
    0x42e4f0: "raceload::cornerInBoxBack2",
    0x42e720: "raceload::clampSpin",
    0x42e820: "raceload::applyImpulse",
    0x42e9c0: "raceload::bounceOffWall",
    0x42ee10: "raceload::hitWall",
    0x42efe0: "raceload::boxHitsWall",
    0x42f280: "raceload::carsCollide",
}
GAME_NATIVES.update(RACELOAD_NATIVES)

# The track's data and a place on it, native whole, in nfs3hp::trackdata
# (native_trackdata.cpp): the nodes, the .ccm and simhts.dat loaded with them,
# the road's quads found under a place, its frame, light and surface, the
# tunnels.  tools/game_checks compares them with their generated code.
TRACKDATA_NATIVES = {
    0x41e180: "trackdata::loadCcmPoints",
    0x41e2c0: "trackdata::freeCcmPoints",
    0x41e2f0: "trackdata::loadSimHeights",
    0x41e340: "trackdata::freeSimHeights",
    0x41e370: "trackdata::openTrackNodes",
    0x41e3b0: "trackdata::closeTrackNodes",
    0x41e3c0: "trackdata::nearestNodeCoarse",
    0x41e420: "trackdata::followNode",
    0x41e470: "trackdata::nearestNode",
    0x41e6a0: "trackdata::quadVertices",
    0x41e720: "trackdata::quadStepForward",
    0x41e770: "trackdata::quadStepBack",
    0x41e7c0: "trackdata::quadToFixed",
    0x41e8d0: "trackdata::quadSet",
    0x41e8f0: "trackdata::nodeSection",
    0x41e940: "trackdata::resetPosition",
    0x41e990: "trackdata::findQuad",
    0x41f090: "trackdata::findQuadNearby",
    0x41f330: "trackdata::findQuadByLinks",
    0x41f500: "trackdata::findQuadFallback",
    0x41f650: "trackdata::locateOnRoad",
    0x41f6e0: "trackdata::updatePosition",
    0x41f870: "trackdata::findMatchingQuad",
    0x41fd60: "trackdata::quadEdgeFlags",
    0x41ff10: "trackdata::sectionItemCount",
    0x41ff20: "trackdata::sectionItem",
    0x41ffa0: "trackdata::setLaneOffsets",
    0x41ffd0: "trackdata::lanePosition",
    0x420230: "trackdata::positionFrame",
    0x4205a0: "trackdata::snapToTrack",
    0x420650: "trackdata::placeOnTrack",
    0x4206f0: "trackdata::positionColour",
    0x4207e0: "trackdata::positionSurface",
    0x420840: "trackdata::surfaceUnder",
    0x420bf0: "trackdata::inTunnel",
    0x420d60: "trackdata::carFacingWay",
    0x4211c0: "trackdata::carSectionKind",
}
GAME_NATIVES.update(TRACKDATA_NATIVES)

# A car's physics step and its direct leaves, native whole, in nfs3hp::physics
# (native_physics.cpp): the step each frame, the full step, the speed in the
# car's axes, the steering's angle, the spin's torque, the dampings.  The
# engine's, the inputs' and the wheels' functions under it are other files'.
# tools/game_checks compares them with their generated code.
PHYSICS_NATIVES = {
    0x4ad250: "physics::clearWheelForces",
    0x4ad2e1: "physics::steerAngle",
    0x4ad672: "physics::sideSlip",
    0x4ad6eb: "physics::groundSpeed",
    0x4ad7a3: "physics::physicsStep",
    0x4ae4c1: "physics::carPhysics",
    0x4ae5c2: "physics::settleLoadShift",
    0x4ae68e: "physics::driveForce",
    0x4ae79b: "physics::holdStill",
    0x4ae85b: "physics::sideGrip",
    0x4ae98b: "physics::handbrakeDrag",
    0x4aea88: "physics::yawDamping",
    0x4aeffc: "physics::idleDamping",
    0x4af140: "physics::coastDamping",
    0x4af254: "physics::spinTorque",
}
GAME_NATIVES.update(PHYSICS_NATIVES)

# A car's handling, native whole, in nfs3hp::handling (native_handling.cpp):
# the physics' entries from outside -- the handling made from the player's
# setup, the automatic gear, the revs matched to the speed, the drive reset,
# a car at rest settled -- and an axle's tyres' forces with what they call.
# tools/game_checks compares them with their generated code.
HANDLING_NATIVES = {
    0x4a78d6: "handling::applyTuning",
    0x4a8bb9: "handling::automaticGear",
    0x4aa4f4: "handling::matchRevsToSpeed",
    0x4aa79f: "handling::resetDriveState",
    0x4aa8e7: "handling::settleAtRest",
    0x4abd9c: "handling::setupGripLoss",
    0x4ac027: "handling::setupSlipLimit",
    0x4ac094: "handling::tyreGrip",
    0x4ac3af: "handling::tyreSlide",
    0x4ac994: "handling::logisticCurve",
    0x4ac9dd: "handling::steeringGrip",
    0x4aca4f: "handling::axleForces",
}
GAME_NATIVES.update(HANDLING_NATIVES)

# A car's engine, gears and driver's inputs, native whole, in
# nfs3hp::drivetrain (native_drivetrain.cpp): the pedals and steering eased
# (or the computer's), the gears changed by hand or by the automatic box,
# the engine's revs and its force at the wheels, the wheels' grip.
# tools/game_checks compares them with their generated code.
DRIVETRAIN_NATIVES = {
    0x4a83d3: "drivetrain::computerDriver",
    0x4a8a99: "drivetrain::engineTorque",
    0x4a90a0: "drivetrain::automaticGears",
    0x4a9769: "drivetrain::gearLimit",
    0x4a97cb: "drivetrain::autoReverse",
    0x4a9bc4: "drivetrain::driverInputs",
    0x4aab41: "drivetrain::wheelGrip",
    0x4aaed1: "drivetrain::engineForce",
}
GAME_NATIVES.update(DRIVETRAIN_NATIVES)



# The menus' screens that are native whole, no generated code behind them:
# each address is a handler of native_frontend_main.cpp, in nfs3hp::frontend,
# that the screens' table at 0x555c48 or a button hands to the menu loop.
# The main menu in its three forms -- main, mainsplt, mainmult -- each as it
# opens, as it closes and every pass of the loop; the players' name buttons
# and their dialogs' answers; mainmult's race list and its Back's question.
# And what the main menu calls of the menu loop (native_frontend_loop.cpp)
# and of the dialogs (native_frontend_dialogs.cpp): a screen's items shown,
# the shown screen's name; a question, a message, a line to type in opened,
# and their layout.  tools/frontend_checks compares them with the game's
# code, made afresh (its generate.py); tools/game_checks leaves them out.
MENU_NATIVES = {
    0x43fcb0: "frontend::multiMenuLeaveAnswer",
    0x4400d0: "frontend::multiMenuOnBack",
    0x440160: "frontend::multiMenuApplyRaceList",
    0x440390: "frontend::multiMenuFollowRaceType",
    0x4403f0: "frontend::multiMenuOnFrame",
    0x440470: "frontend::multiMenuOnEnter",
    0x4405b0: "frontend::multiMenuOnExit",
    0x45cdd0: "frontend::mainMenuPlayerNameAnswer",
    0x45ce60: "frontend::splitMenuPlayer2NameAnswer",
    0x45cef0: "frontend::mainMenuOnPlayerName",
    0x45cf70: "frontend::splitMenuOnPlayer2Name",
    0x45cff0: "frontend::mainMenuOnFrame",
    0x45d050: "frontend::mainMenuOnEnter",
    0x45d2f0: "frontend::mainMenuOnExit",
    0x45d300: "frontend::splitMenuOnFrame",
    0x45d360: "frontend::splitMenuOnEnter",
    0x45d620: "frontend::splitMenuOnExit",
    0x44a960: "frontend::menuShowItems",
    0x44ae00: "frontend::menuCurrentName",
    0x443a90: "frontend::dialogLinesBox",
    0x443c00: "frontend::dialogButtonRowBox",
    0x443d20: "frontend::dialogPlaceButtons",
    0x444570: "frontend::dialogPointAtButton",
    0x4446d0: "frontend::dialogOpenQuestion",
    0x444a80: "frontend::dialogOpenMessage",
    0x444be0: "frontend::dialogMessageById",
    0x444c10: "frontend::dialogEditText",
    0x444c20: "frontend::dialogOpenEdit",
    0x445f00: "frontend::dialogFadedIn",
    # The controls' screens: the function keys', the hardware keys', the
    # controllers' (control1), their dead zones and force feedback.
    0x437600: "frontend::funkeysOnEnter",
    0x4377c0: "frontend::funkeysOnExit",
    0x4377d0: "frontend::hardkeysOnEnter",
    0x43d4d0: "frontend::controlsOnEnter",
    0x43d5f0: "frontend::controlsOnExit",
    0x43d3f0: "frontend::controlsCancelKey",
    0x43d460: "frontend::controlsResetClicked",
    0x43d410: "frontend::controlsResetAnswered",
    0x43d9a0: "frontend::deadZoneFillList",
    0x4432c0: "frontend::deadZoneOnEnter",
    0x443430: "frontend::deadZoneOnExit",
    0x442db0: "frontend::deadZoneCancelKey",
    0x443260: "frontend::deadZoneChooseKey",
    0x443290: "frontend::deadZoneChooseKeyInRace",
    0x443070: "frontend::deadZoneShowController",
    0x442e60: "frontend::deadZoneAxisIndex",
    0x442dd0: "frontend::deadZoneApplyAxis",
    0x442ef0: "frontend::deadZoneAxisMoved",
    0x442ff0: "frontend::deadZoneAxisDraw",
    0x447dd0: "frontend::forceOnEnter",
    0x4481c0: "frontend::forceOnExit",
    0x447b40: "frontend::forceCancelKey",
    0x447b60: "frontend::forceStrengthMoved",
    0x447c40: "frontend::forceRoadEffectsMoved",
    0x447c70: "frontend::forceCollisionMoved",
    0x447ca0: "frontend::forceEngineMoved",
    0x447cd0: "frontend::forceBodyRollMoved",
    0x447d50: "frontend::forceRoadGripMoved",
    0x442a40: "frontend::menuFindItem",
    0x44a660: "frontend::menuShownNow",
    0x4446c0: "frontend::dialogFocusedButton",
}
GAME_NATIVES.update(MENU_NATIVES)

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

# EA's SND library, rewritten as the port's own C++ (src/nfs3hp/port_snd.h):
# each address is the game's entry of that name in nfs3hp::port, first those
# of port_snd_voices.cpp -- the voices, their volume, pan and pitch, the 100
# Hz tick, the platform layer over the mixer.  EA's names where the game's
# messages give them.  tools/game_checks compares them with their generated
# code as well; then the register-level natives of the rest of the sound
# (nfs3hp::snd).
SND_NATIVES = {
    0x4e0d88: "port::eaRandom",
    0x4e257c: "port::soundIdle",
    0x4e25c0: "port::iSNDstop",
    0x4e8fd0: "port::SNDstatus",
    0x4e9010: "port::SNDstopall",
    0x4e9420: "port::SNDautovol",
    0x4e9540: "port::setSoundVolume",
    0x4e95fc: "port::SNDvol",
    0x4e9670: "port::SNDstop",
    0x4e9710: "port::setSoundBend",
    0x4e97e4: "port::SNDpitchbend",
    0x4e9850: "port::SNDpos3d",
    0x4e9950: "port::SNDpan",
    0x4e9b20: "port::SNDplaysetdef",
    0x4e9ba0: "port::SNDplay",
    0x4e9bf8: "port::playOptions",
    0x4ff840: "port::voicePicked",
    0x4ff86c: "port::iSNDallocchan",
    0x4ffb64: "port::iSNDfreechan",
    0x4ffc9c: "port::voiceOf",
    0x500604: "port::iSNDmixstop",
    0x500654: "port::setSendVolume",
    0x5006a4: "port::setMixVolume",
    0x500c80: "port::soundTick",
    0x500e20: "port::iSNDenteraudio",
    0x500e7c: "port::iSNDleaveaudio",
    0x500e94: "port::iSNDserveradd100hzclient",
    0x500ef0: "port::iSNDserverremove100hzclient",
    0x5014a0: "port::updateVoiceVolume",
    0x501540: "port::iSNDvol",
    0x501670: "port::soundVolume",
    0x501938: "port::newGroup",
    0x502cb0: "port::updateVoicePitch",
    0x502d30: "port::iSNDplatformdetune",
    0x502df0: "port::iSNDplatform3dpos",
    0x502ef0: "port::iSNDpan",
    0x5222f0: "port::panSplit",
    0x522320: "port::panSurround",
    0x5224b0: "port::panLawPositive",
    0x5224e0: "port::randomOffset",
    0x5229d0: "port::nextTag",
    0x522e90: "port::pitchFactor",
    0x522f10: "port::mixStep",
    0x522f50: "port::setMixStep",
    0x523310: "port::setVoiceSend",
    0x52b1c0: "port::panLaw",
    0x52b230: "port::readBigEndian",
    0x52b500: "port::setSendLevel",
    # port_snd_play.cpp: patches, banks, a sample started on a channel.
    0x4e73d0: "port::SNDmastervol",
    0x4e8bd0: "port::removeBankPatches",
    0x4e8c1c: "port::removeAllBanks",
    0x4e8c28: "port::SNDbankremove",
    0x4e8d20: "port::SNDbankadd",
    0x4e8db0: "port::SNDbankheadersize",
    0x4e8e20: "port::SNDbankheadercopy",
    0x4fb1e0: "port::SNDbankpatpresent",
    0x5000b8: "port::iSNDmixstart",
    0x5017c0: "port::timbreDefaults",
    0x5017d8: "port::resetTimbre",
    0x5018dc: "port::addTimbreDeltas",
    0x501978: "port::iSNDplaytaggedtimbre",
    0x501de8: "port::iSNDplaytaggedpatch",
    0x5021ac: "port::iSNDresolvetaggedpatch",
    0x5022d0: "port::unresolveTaggedPatch",
    0x502330: "port::iSNDextracthdrinfo",
    0x5024a0: "port::iSNDbankremovepat",
    0x502570: "port::bankUsable",
    0x5025b0: "port::iSNDbankalloc",
    0x502620: "port::iSNDdownloadbank",
    0x522510: "port::iSNDplatformplay",
    0x522a80: "port::iSNDplatformresolve",
    0x522d08: "port::platformUnresolve",
    0x523d94: "port::iSNDplatformpacketplay",
    0x523f90: "port::iSNDcheckplayopts",
    # native_snd_stream.cpp: the system tasks, the top-up's coordination, the
    # SND streamer.
    0x4e7520: "snd::addSystemTask",
    0x4e75e0: "snd::removeSystemTask",
    0x4e7630: "snd::runSystemTasks",
    0x4e7720: "snd::waitSystemTasks",
    0x4ff660: "snd::setTopupFunction",
    0x4ff670: "snd::topUpStream",
    0x4ff780: "snd::topupDone",
    0x4ff7b0: "snd::toppedUp",
    0x4ff7c0: "snd::topUpBeforeLoad",
    0x4ff7e0: "snd::topupReturn",
    0x4ff7f0: "snd::waitTopupStream",
    0x4ff700: "snd::waitTopupMain",
    0x4ff76e: "snd::waitTopupEvent",
    0x4ff820: "snd::loadBlockSize",
    0x4ff830: "snd::loadFlags",
    0x5016c0: "snd::iSNDclearchunk",
    0x5017b4: "snd::platformChunks",
    0x4e7470: "snd::SNDstreamautovol",
    0x4e74f0: "snd::SNDstreamgetvol",
    0x4e7750: "snd::SNDstreamsetup",
    0x4e784c: "snd::SNDstreamrestore",
    0x4e78a0: "snd::SNDstreamqueue",
    0x4e7a14: "snd::SNDstreaminterrupt",
    0x4e7b28: "snd::SNDstreampurge",
    0x4e7c58: "snd::SNDstreamchunksleft",
    0x4e7ce0: "snd::SNDstreambuftime",
    0x4e7dd0: "snd::streamToppedUp",
    0x4e7df4: "snd::iSNDstreamchecktopup",
    0x4e7e98: "snd::iSNDstreamsetbuftime",
    0x4e7f30: "snd::parseStreamChunk",
    0x4e7ff8: "snd::dropQueuedChunks",
    0x4e8078: "snd::queueDataChunk",
    0x4e80cc: "snd::iSNDparseheader",
    0x4e8258: "snd::queueLoopChunk",
    0x4e82c4: "snd::streamSeekChunk",
    0x4e82ec: "snd::streamEndChunk",
    0x4e8320: "snd::streamEndsSeen",
    0x4e8328: "snd::nextStreamChunk",
    0x4e85a8: "snd::iSNDstreamservice",
    0x4e8944: "snd::resetStreamer",
    0x4e89f8: "snd::iSNDstreamstart",
    0x4e8b60: "snd::SNDstreamvol",
    # native_snd_cdstream.cpp: the CD stream and its reader thread.
    0x4e4420: "snd::initStreamStruct",
    0x4e45d0: "snd::initStreamStructSecond",
    0x4e45e0: "snd::initStreamStructFirst",
    0x4e45f0: "snd::initStream",
    0x4e4780: "snd::initStreamSecond",
    0x4e4790: "snd::initStreamFirst",
    0x4e4a30: "snd::deleteStreamStruct",
    0x4e4b50: "snd::deleteStream",
    0x4e4c60: "snd::streamCommand",
    0x4e4d70: "snd::purgeStreamCommand",
    0x4e4ea0: "snd::streamOpen",
    0x4e4ec0: "snd::streamOpenQuietly",
    0x4e4ee0: "snd::streamOpenNext",
    0x4e4f00: "snd::streamOpenNextQuietly",
    0x4e4f20: "snd::streamContinue",
    0x4e4f40: "snd::streamContinueQuietly",
    0x4e4f60: "snd::streamSwitch",
    0x4e4f80: "snd::streamSwitchQuietly",
    0x4e4fa0: "snd::streamQueueFile",
    0x4e4fc0: "snd::streamQueueFileQuietly",
    0x4e4fe0: "snd::streamRestart",
    0x4e5000: "snd::streamRestartQuietly",
    0x4e5020: "snd::streamSeek",
    0x4e5040: "snd::streamSeekQuietly",
    0x4e5060: "snd::streamReadOn",
    0x4e5080: "snd::streamReadOnQuietly",
    0x4e50a0: "snd::streamStopAt",
    0x4e50c0: "snd::streamStopAtQuietly",
    0x4e53c0: "snd::streamReaderThread",
    0x4e6660: "snd::passFreedChunks",
    0x4e66e0: "snd::roomAhead",
    0x4e6710: "snd::roomToEnd",
    0x4e6720: "snd::roomAtStart",
    0x4e6740: "snd::getStreamChunk",
    0x4e68a0: "snd::freeStreamChunk",
    0x4e68c0: "snd::streamBytesRead",
    0x4e68e0: "snd::readerIdle",
    0x4e6950: "snd::readerWaits",
    0x4e69e0: "snd::chainCommandBlocks",
    0x4e6a20: "snd::freeCommandBlock",
    0x4e6a70: "snd::commandBlocksFree",
    0x4e6b30: "snd::takeCommandBlock",
    # native_snd_path.cpp: Pathfinder.
    0x4e6be0: "snd::pathStep",
    0x4e6d68: "snd::pathTask",
    0x4e6d94: "snd::pathHook",
    0x4e6dc8: "snd::SNDpathinit",
    0x4e6f0c: "snd::SNDpathstartstream",
    0x4e705c: "snd::SNDpathcontrol",
    0x4e70fc: "snd::SNDpathevent",
    0x4e7208: "snd::SNDpatheventinterrupt",
    0x4e7388: "snd::SNDpathrestore",
    # native_snd_strm.cpp: SNDSTRM (a movie's sound) and its packet player.
    0x503670: "snd::mul64",
    0x503760: "snd::div64",
    0x523d90: "snd::platformPacketSize",
    0x4f3aa4: "snd::findStream",
    0x4f3fd0: "snd::streamCount",
    0x510a10: "snd::findRequest",
    0x4f2f50: "snd::SNDSTRM_requeststatus",
    0x4f3a10: "snd::streamMemory",
    0x511210: "snd::playerMemory",
    0x4f3a60: "snd::SNDSTRM_createqueued",
    0x4f3a80: "snd::SNDSTRM_requestdata",
    0x4f3a90: "snd::SNDSTRM_restore",
    0x4f3ab8: "snd::removeRequest",
    0x4f3b44: "snd::packetFreed",
    0x4f3b60: "snd::framesPlayed",
    0x4f3ba4: "snd::iSNDstreamparseheader",
    0x4f3cc8: "snd::iSNDstreamparseloop",
    0x4f3d00: "snd::iSNDstreamparsedata",
    0x4f3dac: "snd::iSNDstreamparseend",
    0x4f3dc4: "snd::iSNDstreamparsechunk",
    0x4f3e1c: "snd::streamWaits",
    0x4f3ebc: "snd::iSNDstreamsystemtask",
    0x4f3fec: "snd::iSNDstreamcreate",
    0x4f4258: "snd::iSNDstreamrequest",
    0x4f43c0: "snd::SNDSTRM_destroy",
    0x4f4440: "snd::SNDSTRM_purge",
    0x511228: "snd::SNDPKTPLAY_create",
    0x5112d0: "snd::SNDPKTPLAY_start",
    0x5114d4: "snd::SNDPKTPLAY_submit",
    0x5115b8: "snd::SNDPKTPLAY_submitspace",
    0x51162c: "snd::framesOutstanding",
    0x511680: "snd::SNDPKTPLAY_framesoutstanding",
    0x511718: "snd::SNDPKTPLAY_purge",
    0x51181c: "snd::SNDPKTPLAY_stop",
    0x5118d0: "snd::SNDPKTPLAY_destroy",
    0x5118fc: "snd::nextPacket",
    0x511998: "snd::packetFramesPlayed",
    0x5119b0: "snd::patchDefaults",
    0x5119d8: "snd::iSNDpatchtohdr",
    0x511bf0: "snd::iSNDplatformcalcdatarate",
    0x511ca0: "snd::streamChunksAtOnce",
    0x4f3ab5: "snd::streamTaskSkipped",
    0x4f3b31: "snd::framesPlayedDone",
    0x4ff80f: "snd::waitTopupDone",
    # native_snd_driver.cpp: SNDinit, SNDrestore, the driver, the sound thread.
    0x4e217c: "snd::iSNDunloaddll",
    0x4e2228: "snd::SNDsetrate",
    0x4e1d1c: "snd::leaveAudioLocks",
    0x4e225c: "snd::iSNDmessageinit",
    0x4e2450: "snd::iSNDinit",
    0x4e253c: "snd::iSNDrestore",
    0x4e2754: "snd::iSNDverifymode",
    0x4e2630: "snd::SNDinit",
    0x4e26b4: "snd::SNDrestore",
    0x48ec40: "snd::soundThread",
    0x48ec80: "snd::setSoundServer",
    # native_snd_fx.cpp: the effects, the reverb's start, the mixer's start.
    0x523200: "snd::reverbLength",
    0x52325c: "snd::reverbInit",
    0x502ff0: "snd::iSNDwinsetfx",
    0x5030ac: "snd::setBusFx",
    0x5030c4: "snd::busLevelSet",
    0x5030d0: "snd::SNDfxlevel",
    0x4e9c70: "snd::SNDfxinitbus",
    0x4e9dfc: "snd::SNDfxmasterlevel",
    0x500008: "snd::iSNDmixreinit",
    0x4ffd84: "snd::mixFunctions",
    0x4fff18: "snd::iSNDmixinit",
    # native_mixer.cpp: the mix and a channel's ramp, on the native mixer.
    0x500864: "snd::mixerServe",
    0x5004c8: "snd::mixerRamp",
    # native_snd_mixsetup.cpp: what sets a mixer channel up, MMX set.
    0x5274b0: "snd::pcmOnceMono",
    0x527540: "snd::pcmOnceStereo",
    0x5276f0: "snd::pcmOnceStereo2",
    0x527780: "snd::pcmOnceQuad",
    0x5274d0: "snd::pcmLoopedMono",
    0x527560: "snd::pcmLoopedStereo",
    0x527710: "snd::pcmLoopedStereo2",
    0x5277a0: "snd::pcmLoopedQuad",
    0x527500: "snd::pcmStreamedMono",
    0x527590: "snd::pcmStreamedStereo",
    0x527740: "snd::pcmStreamedStereo2",
    0x5277d0: "snd::pcmStreamedQuad",
    0x52c9a0: "snd::pcmOnceSetup",
    0x52ca48: "snd::pcmLoopedSetup",
    0x52cb74: "snd::pcmStreamedSetup",
    0x529104: "snd::xaOnceSetup",
    0x529534: "snd::xaIntroSetup",
    0x52a354: "snd::xaStereoStreamSetup",
    0x52d160: "snd::packetPlayerOf",
    0x52a5b4: "snd::xaStereoFileSetup",
    0x51f750: "snd::volumeMonoSetup",
    0x51f850: "snd::volumeStereoSetup",
    0x5203a0: "snd::resampleMonoSetup",
    0x5207e4: "snd::resampleStereoSetup",
    0x5202fc: "snd::resampleMonoStep",
    0x520740: "snd::resampleStereoStep",
    0x521d80: "snd::pcmTablesFirst",
    0x521e60: "snd::pcmTablesSecond",
    0x521f30: "snd::xaFloatTable",
    0x521f7c: "snd::xaIntTable",
    0x521fc0: "snd::xaTables",
    0x5220a0: "snd::lastTables",
    0x5230b8: "snd::reverbStart",
    # The game's own sound: its music (native_snd_music.cpp), its effects and
    # the race's sound slots (port_sound_effects.cpp, rewritten as C++ of the port's own).
    0x40feb0: "snd::soundExit",
    0x40fed0: "snd::deleteMusicCopy",
    0x40ffd0: "snd::raceTuneOf",
    0x410030: "snd::raceMusicPrepare",
    0x410330: "snd::musicStreamMake",
    0x410370: "snd::musicStreamMakeOf",
    0x4103a0: "snd::musicAfterSetting",
    0x410460: "snd::musicMenuSix",
    0x4104f0: "snd::musicStart",
    0x4107c0: "snd::raceMusicStart",
    0x4109d0: "snd::musicStop",
    0x410aa0: "snd::musicStreamEnd",
    0x410ad0: "snd::banksFree",
    0x410b20: "snd::banksRemove",
    0x410b50: "snd::bankLoad",
    0x416f60: "port::slotStop",
    0x416fc0: "port::slotEffect",
    0x417080: "port::slotPlay",
    0x4181d0: "port::playMenuEffect",
    0x418280: "port::playCarEffectFive",
    0x4182b0: "port::playEffect",
    0x4184f0: "port::playSpeechEffect",
    0x4185e0: "port::panFromSide",
    0x418610: "port::masterSilent",
    0x418620: "port::masterBack",
    0x4186a0: "port::silenceForMenus",
    0x4186f0: "port::silenceForRace",
    0x418740: "port::busInit",
    0x418770: "port::busUp",
    0x418790: "port::busDown",
    0x4187a0: "port::slotsStop",
    0x4187e0: "port::musicMuteToggle",
    0x4e8f28: "port::SNDangle",
    0x5008a0: "snd::convert16",
    0x500910: "snd::convertToWords",
    0x500990: "snd::convertXaStereo",
    0x500b10: "snd::convert8",
    0x500b90: "snd::convertXaMono",
    0x52a610: "snd::framesPlayedCoded",
    0x52a618: "snd::codedToWords",
    0x52a668: "snd::codedDecode",
    0x52a790: "snd::codedSetup",
    0x52a7e0: "snd::codedStreamDecode",
    0x52a970: "snd::codedStreamSetup",
    0x52a9c0: "snd::codedPacketDecode",
    0x52ab70: "snd::codedPacketSetup",
    0x52d370: "snd::codedBits",
    0x52d3cc: "snd::codedSkip",
    0x52d428: "snd::codedPulses",
    0x52d5cc: "snd::codedInterpolate",
    0x52d618: "snd::codedFilter",
    0x52d6d8: "snd::codedSynthesis",
    0x52de94: "snd::codedStart",
    0x52df80: "snd::codedFrame",
    0x52a1a0: "snd::xaStereoStreamDecode",
    0x52a3a0: "snd::xaStereoPacketDecode",
    0x529cfc: "snd::xaStereoLoopDecode",
    0x529f24: "snd::xaStereoIntroDecode",
    0x52a144: "snd::xaStereoIntroSetup",
    0x529a50: "snd::xaStereoPlayed",
    0x529a54: "snd::xaStereoOnceDecode",
    0x529c2c: "snd::xaStereoOnceSetup",
    0x529c80: "snd::xaStereoKeptCopy",
    0x5297c0: "snd::xaPacketDecode",
    0x5299f4: "snd::xaPacketSetup",
    0x529384: "snd::xaIntroDecode",
    0x529590: "snd::xaStreamDecode",
    0x529778: "snd::xaStreamSetup",
    0x528f70: "snd::xaPlayed",
    0x528f74: "snd::xaOnceDecode",
    0x529140: "snd::xaKeptCopy",
    0x5291a8: "snd::xaLoopDecode",
    0x52c8f0: "snd::pcmPlayed",
    0x52c8f4: "snd::pcmOnceDecode",
    0x52c9d0: "snd::pcmLoopedDecode",
    0x52ca80: "snd::pcmStreamedDecode",
    0x52cba0: "snd::pcmFileDecode",
    0x52ccb8: "snd::pcmFileSetup",
    0x527520: "snd::pcmFileMono",
    0x5275b0: "snd::pcmFileStereo",
    0x527760: "snd::pcmFileStereo2",
    0x5277f0: "snd::pcmFileQuad",
    0x4ffce0: "snd::bufferPosition",
    0x51f520: "snd::panSides",
    0x51f580: "snd::volumeMonoPair",
    0x51f5a4: "snd::volumeMonoLevels",
    0x51f680: "snd::volumeStereoPair",
    0x51f6a4: "snd::volumeStereoLevels",
    0x51f774: "snd::volumeMonoLevelsMmx",
    0x51f874: "snd::volumeStereoLevelsMmx",
    0x51fc38: "snd::resample8MonoSetup",
    0x51fb94: "snd::resample8MonoStep",
    0x51f930: "snd::resample8MonoNeededDown",
    0x51f978: "snd::resample8MonoNeededSame",
    0x51f980: "snd::resample8MonoNeededUp",
    0x51fa80: "snd::resample8MonoSame",
    0x51f9ac: "snd::resample8MonoDown",
    0x51fa8c: "snd::resample8MonoUp",
    0x52002c: "snd::resample8StereoSetup",
    0x51ff88: "snd::resample8StereoStep",
    0x51fc80: "snd::resample8StereoNeededDown",
    0x51fcc8: "snd::resample8StereoNeededSame",
    0x51fcd0: "snd::resample8StereoNeededUp",
    0x51fe24: "snd::resample8StereoSame",
    0x51fcfc: "snd::resample8StereoDown",
    0x51fe30: "snd::resample8StereoUp",
    0x520070: "snd::resample16MonoNeededDown",
    0x5200b8: "snd::resample16MonoNeededSame",
    0x5200c0: "snd::resample16MonoNeededUp",
    0x5201d8: "snd::resample16MonoSame",
    0x5200ec: "snd::resample16MonoDown",
    0x5201e4: "snd::resample16MonoUp",
    0x5203f0: "snd::resample16StereoNeededDown",
    0x520438: "snd::resample16StereoNeededSame",
    0x520440: "snd::resample16StereoNeededUp",
    0x5205b0: "snd::resample16StereoSame",
    0x52046c: "snd::resample16StereoDown",
    0x5205bc: "snd::resample16StereoUp",
    0x4c8370: "snd::speechInit",
    0x4c8440: "snd::speechFree",
    0x4c85a0: "snd::speechLine",
    0x415210: "snd::scenerySounds",
    0x413bc0: "snd::raceBanksLoad",
    0x412d60: "snd::raceAnnouncer",
    0x410e30: "snd::trackSounds",
    0x4c8d10: "snd::coDriverTick",
    0x417390: "snd::carEngine",
    0x411e60: "snd::copCarSound",
    0x4117a0: "snd::playerCarSound",
    0x412220: "snd::copSourcesPick",
    0x411410: "snd::raceSoundTick",
    0x415050: "snd::zoneSound",
    0x413750: "snd::voiceBankLoad",
    0x4138e0: "snd::carBankLoad",
    0x4124d0: "snd::placeAhead",
    0x412620: "snd::placeAcross",
    0x4127c0: "snd::carRadio",
    0x412880: "snd::playerCopRadio",
    0x412be0: "snd::copLineFor",
    0x4121b0: "snd::copRemove",
    0x4127b0: "snd::carFlagTest",
    0x4129a0: "snd::raceValue",
    0x4129b0: "snd::soundNothing",
    0x414800: "snd::slotsEmpty",
    0x4136e0: "snd::raceBankLoad",
    0x4129c0: "snd::raceSoundInit",
    0x412b50: "snd::raceSoundEnd",
    0x411620: "snd::sourceReset",
    0x411680: "snd::sourcesReset",
    0x411750: "snd::copChaseSet",
    0x411c50: "snd::copSiren",
    0x411ca0: "snd::copSirenStop",
    0x411cb0: "snd::copEngine",
    0x411da0: "snd::copEngineStop",
    0x411db0: "snd::copDistance",
    0x411e20: "snd::copsCloseness",
    0x410c40: "snd::listenerMove",
    0x410cb0: "snd::sourceDistance",
    0x410d30: "snd::sourceAngle",
    0x410dc0: "snd::carAngle",
    0x4188a0: "snd::copBeepTick",
    0x418930: "snd::copBeepStart",
    0x418c30: "snd::copEffect",
    0x418c60: "snd::musicEventResume",
    0x418990: "snd::chaseLevel",
    0x4c9240: "snd::descriptionLoad",
    0x4c9340: "snd::descriptionSpeak",
    0x4c9380: "snd::descriptionTick",
    0x4c9490: "snd::descriptionStop",
    0x4c95e0: "snd::spokenStatus",
    0x4c99f0: "snd::spokenStatus",
    0x4c95f0: "snd::descriptionStart",
    0x4c9860: "snd::descriptionService",
    0x4c9890: "snd::raceVoiceLoad",
    0x4c9990: "snd::carLineSpeak",
    0x4c99d0: "snd::spokenStop",
    0x4c9a00: "snd::raceVoiceFree",
    0x4c86d0: "snd::speechTick",
    0x4c8810: "snd::radioTick",
    0x4c89b0: "snd::radioStart",
    0x4c8ac0: "snd::speechSaid",
    0x4c8b30: "snd::copRadio",
    0x4c8ca0: "snd::queueSpeechLine",
    0x4c8f90: "snd::queueRaceLine",
    0x4c9010: "snd::raceEventLine",
    0x4c9090: "snd::gapLine",
    0x4c91a0: "snd::lapTimeLine",
    0x414830: "snd::engineSoundsStart",
    0x414e10: "snd::farEffectAim",
    0x414ef0: "snd::farEffectPlay",
    0x414f60: "snd::farEffectTick",
    0x414f90: "snd::crowdEffect",
    0x415010: "snd::carEffectFifteen",
    0x414940: "snd::crashPitch",
    0x4149e0: "snd::crashEffect",
    0x414d70: "snd::scrapeEffect",
    0x416d90: "snd::carKnock",
    0x417b80: "snd::noiseByDistance",
    0x417c00: "snd::playerNoise",
    0x417c70: "snd::playerNoiseStop",
    0x417ca0: "snd::sirenIsOn",
    0x417cb0: "snd::sirenFirstTone",
    0x417db0: "snd::sirenSecondTone",
    0x417e00: "snd::sirenSteadyTone",
    0x417d00: "snd::sirenFirstDone",
    0x417e60: "snd::sirenSecondDone",
    0x417eb0: "snd::sirenStart",
    0x417f60: "snd::sirenStop",
    0x417fd0: "snd::sirenTick",
    0x4179d0: "snd::noiseBySpeed",
}
# EA SND's mixer code that never runs on the port: a stub each that stops the
# game (src/nfs3hp/native_snd_dead.inc, native_snd_dead.cpp), no code generated.
for _line in open(__import__("os").path.join(__import__("os").path.dirname(__import__("os").path.abspath(__file__)),
                                     "src/nfs3hp/native_snd_dead.inc")).read().splitlines():
    if _line.startswith("DEAD("):
        SND_NATIVES[int(_line[5:-1], 16)] = "snd::dead_%s" % _line[5:-1]
GAME_NATIVES.update(SND_NATIVES)

# The graphics code that never runs on the port's driver, voodoo2a: a stub each
# that stops the game (src/nfs3hp/native_graphics_dead.inc,
# native_graphics_dead.cpp), no code generated.
GRAPHICS_DEAD = {}
for _line in open(__import__("os").path.join(__import__("os").path.dirname(__import__("os").path.abspath(__file__)),
                                     "src/nfs3hp/native_graphics_dead.inc")).read().splitlines():
    if _line.startswith("DEAD("):
        GRAPHICS_DEAD[int(_line[5:-1], 16)] = "graphics::dead_%s" % _line[5:-1]
GAME_NATIVES.update(GRAPHICS_DEAD)

# Functions decompiled one at a time (src/nfs3hp/native_decompiled.cpp, and
# native_graphics.cpp for the graphics'): each
# address of src/nfs3hp/decompiled.json is the function of its name there, in
# nfs3hp::decompiled; tools/game_checks holds each against the game's code on
# made-up values of the globals the list names for it.
import json as _json
import os as _os


def decompiled_list():
    path = _os.path.join(_os.path.dirname(_os.path.abspath(__file__)), "src", "nfs3hp", "decompiled.json")
    with open(path, encoding="utf-8") as f:
        return _json.load(f)


def decompiled_name(entry):
    """An entry's function as the code calls it: in nfs3hp::decompiled, or in
    the namespace the entry names (graphics: native_graphics.cpp)."""
    return "%s::%s" % (entry.get("namespace", "decompiled"), entry["name"])


DECOMPILED_NATIVES = {int(entry["address"], 16): decompiled_name(entry) for entry in decompiled_list()}
GAME_NATIVES.update(DECOMPILED_NATIVES)

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
# functions that are a bare ret after another (THRASH_flushwindow, THRASH_idle),
# for the disassembly to find its way through it.
VOODOO2A_DATA_SEGMENTS = [(0xa83204, 0xa83210), (0xA86833, 0xA868A2)]
VOODOO2A_KNOWN_SUBROUTINES = [0xA847D0, 0xA84810]

# voodoo2a is the port's own: each export is the port's function of that name
# in src/nfs3hp/port_thrash.cpp, and none of its code is generated.  Of its own
# functions only one was handed out to be called: sub_a84360, which its
# THRASH_setvideomode gave the game's window thread to run on message 0x465.
# The port's driver hands it to nobody; the address stays bound all the same.
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
    # THRASH_about and measureModes in src/nfs3hp/port_thrash.cpp.

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

    # View Angle's third choice, 105 degrees, as the Modern Patch has it.
    from tools.apply_view_angle import apply as apply_view_angle
    apply_view_angle(Path(__file__).resolve().parent)


    # Text entry: the phone's keyboard comes up by itself while the game waits
    # for a name to be typed.
    from tools.apply_text_entry import apply as apply_text_entry
    apply_text_entry(Path(__file__).resolve().parent)

    # Force feedback: player one's car keeps its effects when the on-screen
    # controls are bound as keys, which leaves no axis on the pad to claim them.
    # tools/apply_force_feedback_car.py's change is in sub_4710f0's native now
    # (native_controls_race.cpp's forcePlayerCar).

    # Full colour: the Screen Size list shows the depth a race is drawn in (the
    # Voodoo2 driver's taking the game's 32-bit textures is port_thrash.cpp's).
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

    # The loading native: RefPack, the FSH textures' alpha scans, an FCE's
    # polygon records and a track's FRD.
    from tools.apply_native_loading import apply as apply_native_loading
    apply_native_loading(Path(__file__).resolve().parent)

    # The specs file's text native (sub_4b22d0), which nothing in the game calls.
    from tools.apply_native_specs_file import apply as apply_native_specs_file
    apply_native_specs_file(Path(__file__).resolve().parent)

    # The movies native: the MAD player, decoder and display (decomp/mad), after
    # apply_movie_tap's MovieSession.
    from tools.apply_native_movie import apply as apply_native_movie
    apply_native_movie(Path(__file__).resolve().parent)

    # The menus decompiled a screen at a time, the generated code kept behind
    # them: first the main menu.
    from tools.apply_native_frontend import apply as apply_native_frontend
    apply_native_frontend(Path(__file__).resolve().parent)
