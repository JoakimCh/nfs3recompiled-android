// game_checks.cpp's parts for EA's SND library and the game's sound (port_snd_*.cpp,
// native_snd_*.cpp, port_sound_effects.cpp), included in each table with the macro naming the part.
#if defined(SOUND_WINDOWS)
// {from, to}, -- what the functions write, compared
// The voices, the platform's voices, the mixer's channels and the library's
// globals; the arena the worlds' tables, patches and options are in; the
// system tasks; the CD streams' arena, their rings and command blocks.
{0x9ef600, 0x9ef900}, {0x9f6a00, 0xa0a400}, {0xc00000, 0xc20000},
// The jump tables the stream worlds give the game's code (its code segment's).
{0x4e5000, 0x4e6000}, {0x4e8000, 0x4e9000},
// SNDSTRM's streams and the packet players, their arena.
{0x9f2000, 0x9f3000}, {0xa0b000, 0xa0b100}, {0xc20000, 0xc30000},
// SND's banks.
{0xc30000, 0xc31000},
// The sound thread's server and event, and EA's timer (port_timer.cpp): its state, its busy and
// attempt counts, its rate (0x5643d8) and the function Error stops it with (0x56441c).
{0x79c000, 0x79d000}, {0x55e2c0, 0x55e2e0}, {0x5643d0, 0x5643e0}, {0x564418, 0x564424},
// The reverb's delay lines and their state.
{0xa0d000, 0xa19000},
// The mixer's XA tables.
{0xa0b100, 0xa0c100},
// The game's sound: its slots and banks.
{0x570000, 0x572000},
// The jump tables its worlds give the game's sound's code (the code segment's).
{0x40f000, 0x410000}, {0x414000, 0x415000}, {0x417000, 0x418000},
// The speech's state and its radio's.
{0x560000, 0x561000}, {0x7dd000, 0x7de000},
{0x4c9000, 0x4ca000},
// The voice banks' names (the code segment's).
{0x412000, 0x414000},
// The rest of the game's data its sound reads: the cars and the track,
// the race's state, the folders' names.
{0x553000, 0x554000}, {0x556000, 0x557000}, {0x55c000, 0x55e000}, {0x55f000, 0x560000},
{0x565000, 0x566000}, {0x5dd000, 0x5de000}, {0x5e1000, 0x5e2000}, {0x5ea000, 0x5eb000},
{0x5ef000, 0x5f5000}, {0x604000, 0x605000}, {0x660000, 0x661000}, {0x6ff000, 0x700000},
{0x749000, 0x74a000}, {0x792000, 0x793000}, {0x7a2000, 0x7a3000}, {0x7d3000, 0x7d4000},
{0x7dc000, 0x7dd000}, {0x8b4000, 0x8b5000}, {0x8b8000, 0x8ba000},
#elif defined(SOUND_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// (SND's functions: the registers each reads on entry, by the original's code.)
{0x4f9070, "a surface locked", kWatcom, 0, 0, kEax, -1, 0, kMainThread},
{0x5004c8, "a channel's volume ramped", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// The streams' threads, events, locks, files and strings.
{0x4dfb00, "an event made", kWatcom, 0, 0, kEax, -1, 0, kEvent},
{0x4dfb20, "an event set", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4dfb70, "an event waited for", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4dfc00, "a handle closed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4df8e0, "a sleep", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4df7a0, "a thread made", kStdcall, 4, 1, kEax, -1, 0, kSucceed},
{0x4df870, "a thread removed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4eb2e0, "a lock made", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4eb360, "a lock freed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x5011a0, "pages touched", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x501270, "a file opened by blocks", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x5013a0, "a file by blocks closed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x5013b0, "blocks read", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x501450, "a file by blocks sought", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// The movies' file streamer SNDSTRM reads its chunks with.
{0x4cfa80, "a file streamer made", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x4cfd30, "a file streamer gone", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4cfdd0, "a file streamer's chunks at once", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4cfef0, "a file streamer's request", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4cffb0, "a file streamer's request whole", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4d0220, "a file streamer emptied", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4d0300, "a file streamer's next chunk", kWatcom, 2, 0, kEax, -1, 0, kSoundChunk},
{0x4d03c0, "a file streamer's chunk given back", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4d0460, "a file streamer's bytes", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4d0490, "a file streamer's state", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4d0500, "a file streamer's block", kWatcom, 0, 0, kEax, -1, 0, kNothing},
// The game's message thread and focus handler, its exit list.
{0x4cc7c0, "a message sent", kWatcom, 4, 0, kEax, -1, 0, kThreadsMessageSent},
{0x4cc860, "the focus handler set", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4f2a78, "a function run at exit", kWatcom, 1, 0, kEax, -1, 0, kNothing},
// The mixer's buffer cleared, its reverb run (through its tables' pointers).
{0x5209a0, "the mixer's buffer cleared (MMX)", kCdecl, 0, 2, kScratch, -1, 0, kNothing},
{0x521c90, "the mixer's buffer cleared", kCdecl, 0, 2, kScratch, -1, 0, kNothing},
{0x5230b8, "the reverb run", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// SND's interface as the game's own sound calls it (none of the library's
// code does): its four registers logged, SNDplay's options too.
{0x4e9ba0, "SNDplay", kWatcom, 1, 0, kEax, 0, 4, kNothing},
{0x4e73d0, "SNDmastervol", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e8b60, "SNDstreamvol", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e97e4, "SNDpitchbend", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4e9850, "SNDpos3d", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x4e9950, "SNDpan", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4e9c70, "SNDfxinitbus", kStdcall, 4, 1, kEax, -1, 0, kNothing},
{0x4e26b4, "SNDrestore", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4e4790, "a CD stream made", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4e4b50, "a CD stream deleted", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4e6dc8, "SNDpathinit", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e6f0c, "SNDpathstartstream", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x4e705c, "SNDpathcontrol", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e70fc, "SNDpathevent", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4e7208, "SNDpatheventinterrupt", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e7388, "SNDpathrestore", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0x4e7470, "SNDstreamautovol", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0x4e74f0, "SNDstreamgetvol", kWatcom, 0, 0, kEax, -1, 0, kNothing},
// The banks removed: SNDbankremove of eax (edx pushed and popped around it).
{0x4e8c1c, "the banks removed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x4e8d20, "SNDbankadd", kWatcom, 2, 0, kEax, -1, 0, kBankAdd},
{0x4e8db0, "SNDbankheadersize", kWatcom, 1, 0, kEax, -1, 0, kNothing},
// The file a bank is read from, by the game's C library.
{0x4e9088, "fseek", kWatcom, 3, 0, kEax, -1, 0, kNothing},
{0x4e9200, "fread", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0x4e8e20, "SNDbankheadercopy", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// A file loaded whole: a buffer of the harness's low memory, or none.
{0x4e0ec0, "a file loaded", kWatcom, 4, 0, kEax, -1, 0, kLoad},
// A track's name, as the description's name is made of it: a string of the
// harness's low memory.
{0x4392b0, "a track's name", kWatcom, 1, 0, kEax, -1, 0, kLoad},
// The game's dot product of the vectors at eax and edx: a float onto the x87's
// stack.
{0x4e01f0, "a dot product", kWatcom, 2, 0, kEax, 0, 3, kMathResult},
#elif defined(SOUND_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// The mixer's channels' functions, the end of a channel, the tick's clients:
// slots of the harness's own, as kByDword's.
{0xfff300, "a channel's step set", kCdecl, 0, 2, kScratch, -1, 0, kNothing},
{0xfff304, "a channel's volume set", kCdecl, 0, 3, kScratch, -1, 0, kNothing},
{0xfff308, "a channel ended", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0xfff30c, "emms", kWatcom, 0, 0, kEax, -1, 0, kNothing},
{0xfff310, "a tick's client", kWatcom, 1, 0, kEax, -1, 0, kNothing},
// A channel's decoder set up: registers and 4 words, which it takes; its volume
// functions' and its resampler's, cdecl.
{0xfff314, "a decoder set up", kStdcall, 4, 4, kScratch, -1, 0, kNothing},
{0xfff318, "volume functions set up", kCdecl, 0, 3, kScratch, -1, 0, kNothing},
{0xfff31c, "a resampler set up", kCdecl, 0, 4, kScratch, -1, 0, kNothing},
// A system task, the stream's top-up function, Pathfinder's top-up hook.
{0xfff320, "a system task", kWatcom, 2, 0, kEax, -1, 0, kNothing},
{0xfff324, "the top-up function", kWatcom, 4, 0, kEax, -1, 0, kNothing},
{0xfff328, "Pathfinder's top-up hook", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// A system task that always gives something back.
{0xfff32c, "a system task with a result", kWatcom, 2, 0, kEax, -1, 0, kSomething},
// A packet player's callbacks: a packet freed, frames played.
{0xfff330, "a packet freed", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0xfff334, "frames played", kWatcom, 2, 0, kEax, -1, 0, kNothing},
// eacsnd's check, start, end and volume where the driver keeps them; a
// restore of the library's; FreeLibrary's slot.
{0xfff338, "eacsnd's check", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0xfff33c, "eacsnd's start", kStdcall, 0, 2, kScratch, -1, 0, kNothing},
{0xfff340, "eacsnd's end", kStdcall, 0, 0, kScratch, -1, 0, kNothing},
{0xfff344, "eacsnd's volume", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0xfff348, "a restore", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0x5344dc, "FreeLibrary", kStdcall, 0, 1, kScratch, -1, 0, kSucceed},
// EA's timer (port_timer.cpp): Windows' multimedia timer, by its imports' slots.
{0x534568, "timeGetTime", kStdcall, 0, 0, kScratch, -1, 0, kThreadsClock},
{0x534660, "timeSetEvent", kStdcall, 0, 5, kScratch, -1, 0, kSucceed},
{0x53465c, "timeKillEvent", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x534650, "timeBeginPeriod", kStdcall, 0, 1, kScratch, -1, 0, kThreadsMmResult},
{0x534654, "timeEndPeriod", kStdcall, 0, 1, kScratch, -1, 0, kNothing},
{0x534658, "timeGetDevCaps", kStdcall, 0, 2, kScratch, -1, 0, kThreadsMmResult},
#elif defined(SOUND_PROMISES)
// {"snd::name", watcom, result, arguments, fpu, heap, liveOnly, unread},
// unread: the scratch registers SND's rewrite (port::, eax and nothing else
// changed) leaves otherwise up through the game's sound code, which no caller
// reads after the call -- by liveness on the original x86 of each call site,
// the values passed up followed to the callers' callers (2026-10-25: sourceAngle's
// callers read ecx, carAngle's ebx, carLineSpeak's ecx, copBeepStart's ebx and
// ecx, crowdEffect's ebx; those stay compared).
// EA's SND library, rewritten (port_snd_voices.cpp, port_snd_play.cpp).
{"port::voiceOf", true, true, 1},
{"port::iSNDfreechan", true, true, 1},
{"port::voicePicked", true, true, 2},
{"port::iSNDallocchan", true, true, 4},
{"port::iSNDenteraudio", true, true, 0},
{"port::iSNDleaveaudio", true, true, 0},
{"port::iSNDserveradd100hzclient", true, true, 1},
// Its result past an error is Error's eax, which is nobody's.
{"port::iSNDserverremove100hzclient", true, false, 1},
{"port::eaRandom", true, true, 0},
{"port::randomOffset", true, true, 1},
{"port::readBigEndian", true, true, 2},
{"port::nextTag", true, true, 4},
// The pans: their sides into [ebx] and [ecx]; eax as the code leaves it nobody's.
{"port::panSplit", true, false, 4},
{"port::panLaw", true, false, 4},
{"port::panLawPositive", true, false, 4},
{"port::panSurround", true, false, 4},
{"port::setSendVolume", true, true, 1},
{"port::setMixVolume", true, true, 3},
{"port::setSendLevel", true, true, 2},
{"port::setVoiceSend", true, true, 3},
{"port::updateVoiceVolume", true, true, 1},
{"port::iSNDvol", true, true, 2},
{"port::updateVoicePitch", true, true, 1},
{"port::pitchFactor", true, true, 1, true},
// The rewrite keeps the x87's values in its own: the registers past the stack
// as they were, where the game's code popped its own.
{"port::mixStep", true, true, 3, true, kNoHeap, true},
{"port::setMixStep", true, true, 2},
{"port::iSNDplatformdetune", true, true, 2, true, kNoHeap, true},
{"port::iSNDplatform3dpos", true, true, 3},
{"port::iSNDpan", true, true, 2},
{"port::iSNDmixstop", true, true, 1},
{"port::iSNDstop", true, true, 1},
{"port::soundIdle", true, true, 0},
{"port::soundTick", true, false, 0},
{"port::SNDstop", true, true, 1},
{"port::SNDstatus", true, true, 1},
{"port::SNDstopall", true, true, 0},
{"port::SNDautovol", true, true, 0},
{"port::setSoundVolume", true, true, 2},
{"port::SNDvol", true, true, 0},
{"port::setSoundBend", true, true, 2},
{"port::SNDpitchbend", true, true, 2},
{"port::SNDpos3d", true, true, 3},
{"port::SNDpan", true, true, 2},
{"port::SNDplaysetdef", true, true, 1},
{"port::playOptions", true, true, 2},
{"port::SNDplay", true, true, 1},
{"port::soundVolume", true, true, 1},
{"port::newGroup", true, true, 0},
{"port::timbreDefaults", true, true, 1},
{"port::resetTimbre", true, true, 2},
{"port::addTimbreDeltas", true, true, 2},
{"port::iSNDplaytaggedtimbre", true, true, 4},
{"port::iSNDplaytaggedpatch", true, true, 2},
{"port::iSNDresolvetaggedpatch", true, true, 3},
{"port::unresolveTaggedPatch", true, true, 2},
{"port::iSNDextracthdrinfo", true, true, 2},
{"port::bankUsable", true, true, 1},
{"port::iSNDbankremovepat", true, true, 3},
{"port::iSNDbankalloc", true, true, 0},
{"port::iSNDdownloadbank", true, true, 2},
{"port::iSNDplatformresolve", true, true, 2},
{"port::platformUnresolve", true, true, 2},
{"port::iSNDmixstart", true, true, 4},
{"port::iSNDplatformplay", true, true, 4},
{"port::iSNDplatformpacketplay", true, true, 4},
// Its result past an error is Error's eax, which is nobody's.
{"port::iSNDcheckplayopts", true, false, 1},
{"port::removeBankPatches", true, true, 2},
// edx as the code leaves it is iSNDbankremovepat's ebx or its own count.
{"port::SNDbankremove", true, true, 2},
{"port::removeAllBanks", true, true, 1},
{"port::SNDbankadd", true, true, 2},
{"port::SNDbankheadersize", true, true, 1},
{"port::SNDbankheadercopy", true, true, 2},
{"port::SNDbankpatpresent", true, true, 2},
{"port::SNDmastervol", true, true, 1},
// native_snd_stream.cpp, native_snd_cdstream.cpp.
{"port::addSystemTask", true, true, 3},
{"port::removeSystemTask", true, true, 1},
{"port::runSystemTasks", true, true, 1},
{"port::waitSystemTasks", true, true, 1},
{"port::setTopupFunction", true, true, 1},
{"port::topUpStream", true, true, 1},
{"port::topupDone", true, true, 0},
{"port::toppedUp", true, true, 0},
{"port::topUpBeforeLoad", true, true, 1},
{"port::topupReturn", true, true, 0},
{"port::waitTopupStream", true, true, 0},
{"port::waitTopupMain", true, true, 0},
{"port::waitTopupEvent", true, true, 0},
{"port::loadBlockSize", true, true, 0},
{"port::loadFlags", true, true, 0},
{"port::iSNDclearchunk", true, true, 3},
{"port::platformChunks", true, true, 1},
{"port::SNDstreamautovol", true, true, 2},
{"port::SNDstreamgetvol", true, true, 0},
{"port::resetStreamer", true, true, 0},
{"port::SNDstreamsetup", true, true, 2},
{"port::SNDstreamrestore", true, true, 0},
{"port::SNDstreamqueue", true, true, 2},
{"port::SNDstreaminterrupt", true, true, 2},
{"port::SNDstreampurge", true, true, 0},
{"port::SNDstreamchunksleft", true, true, 0},
{"port::SNDstreambuftime", true, true, 0},
{"port::streamToppedUp", true, true, 1},
{"port::iSNDstreamchecktopup", true, true, 0},
{"port::iSNDstreamsetbuftime", true, true, 1},
{"port::parseStreamChunk", true, true, 1},
{"port::dropQueuedChunks", true, true, 0},
{"port::queueDataChunk", true, true, 1},
{"port::iSNDparseheader", true, true, 1},
{"port::queueLoopChunk", true, true, 1},
{"port::streamSeekChunk", true, true, 1},
{"port::streamEndChunk", true, true, 1},
{"port::streamEndsSeen", true, true, 0},
{"port::nextStreamChunk", true, true, 2},
{"port::iSNDstreamservice", true, true, 0},
{"port::iSNDstreamstart", true, true, 0},
{"port::SNDstreamvol", true, true, 1},
{"port::freeStreamChunk", true, true, 2},
{"port::streamBytesRead", true, true, 1},
{"port::readerIdle", true, true, 0},
{"port::readerWaits", true, true, 1},
{"port::passFreedChunks", true, true, 1},
{"port::roomAhead", true, true, 1},
{"port::roomToEnd", true, true, 1},
{"port::roomAtStart", true, true, 1},
{"port::getStreamChunk", true, true, 1},
{"port::chainCommandBlocks", true, true, 2},
{"port::freeCommandBlock", true, true, 1},
{"port::commandBlocksFree", true, true, 1},
{"port::takeCommandBlock", true, true, 1},
{"port::streamCommand", true, true, 4},
{"port::purgeStreamCommand", true, true, 4},
{"port::streamOpen", true, true, 2},
{"port::streamOpenQuietly", true, true, 2},
{"port::streamOpenNext", true, true, 2},
{"port::streamOpenNextQuietly", true, true, 2},
{"port::streamContinue", true, true, 2},
{"port::streamContinueQuietly", true, true, 2},
{"port::streamSwitch", true, true, 2},
{"port::streamSwitchQuietly", true, true, 2},
{"port::streamQueueFile", true, true, 2},
{"port::streamQueueFileQuietly", true, true, 2},
{"port::streamRestart", true, true, 2},
{"port::streamRestartQuietly", true, true, 2},
{"port::streamSeek", true, true, 2},
{"port::streamSeekQuietly", true, true, 2},
{"port::streamReadOn", true, true, 2},
{"port::streamReadOnQuietly", true, true, 2},
{"port::streamStopAt", true, true, 2},
{"port::streamStopAtQuietly", true, true, 2},
{"port::initStreamStruct", true, true, 4},
{"port::initStreamStructSecond", true, true, 3},
{"port::initStreamStructFirst", true, true, 3},
{"port::initStream", true, true, 4},
{"port::initStreamSecond", true, true, 3},
{"port::initStreamFirst", true, true, 3},
{"port::deleteStreamStruct", true, true, 1},
{"port::deleteStream", true, true, 1},
{"port::streamReaderThread", true, true, 0},
// port_snd_path.cpp.
{"port::pathStep", true, true, 0},
{"port::pathTask", true, true, 2},
{"port::pathHook", true, true, 1},
{"port::SNDpathinit", true, true, 1},
{"port::SNDpathstartstream", true, true, 3},
{"port::SNDpathcontrol", true, true, 1},
{"port::SNDpathevent", true, true, 2},
{"port::SNDpatheventinterrupt", true, true, 1},
{"port::SNDpathrestore", true, true, 0},
// port_snd_strm.cpp.
{"port::mul64", true, true, 2},
{"port::div64", true, true, 0},
{"port::platformPacketSize", true, true, 0},
{"port::findStream", true, true, 1},
{"port::streamCount", true, true, 0},
{"port::findRequest", true, true, 1},
{"port::SNDSTRM_requeststatus", true, true, 2},
{"port::streamMemory", true, true, 2},
{"port::playerMemory", true, true, 1},
{"port::SNDSTRM_createqueued", true, true, 4},
{"port::SNDSTRM_requestdata", true, true, 3},
{"port::SNDSTRM_restore", true, true, 0},
{"port::removeRequest", true, true, 1},
{"port::packetFreed", true, true, 1},
{"port::framesPlayed", true, true, 2},
{"port::iSNDstreamparseheader", true, true, 2},
{"port::iSNDstreamparseloop", true, true, 2},
{"port::iSNDstreamparsedata", true, true, 2},
{"port::iSNDstreamparseend", true, true, 2},
{"port::iSNDstreamparsechunk", true, true, 2},
{"port::streamWaits", true, true, 1},
{"port::iSNDstreamsystemtask", true, true, 0},
{"port::iSNDstreamcreate", true, true, 4},
{"port::iSNDstreamrequest", true, true, 4},
{"port::SNDSTRM_destroy", true, true, 1},
{"port::SNDSTRM_purge", true, true, 1},
{"port::SNDPKTPLAY_create", true, true, 4},
{"port::SNDPKTPLAY_start", true, true, 4},
{"port::SNDPKTPLAY_submit", true, true, 2},
{"port::SNDPKTPLAY_submitspace", true, true, 1},
{"port::framesOutstanding", true, true, 1},
{"port::SNDPKTPLAY_framesoutstanding", true, true, 1},
{"port::SNDPKTPLAY_purge", true, true, 3},
{"port::SNDPKTPLAY_stop", true, true, 1},
{"port::SNDPKTPLAY_destroy", true, true, 1},
{"port::nextPacket", true, true, 2},
{"port::packetFramesPlayed", true, true, 2},
{"port::patchDefaults", true, true, 1},
{"port::iSNDpatchtohdr", true, true, 4},
{"port::iSNDplatformcalcdatarate", true, true, 1},
{"port::streamChunksAtOnce", true, true, 2},
{"port::streamTaskSkipped", true, true, 0},
{"port::framesPlayedDone", true, true, 0},
{"port::waitTopupDone", true, true, 0},
// port_snd_driver.cpp.
{"port::iSNDunloaddll", true, true, 0},
{"port::SNDsetrate", true, true, 1},
{"port::leaveAudioLocks", true, true, 0},
{"port::iSNDmessageinit", true, true, 0},
{"port::iSNDinit", true, true, 1},
{"port::iSNDrestore", true, true, 0},
{"port::iSNDverifymode", true, true, 2},
{"port::SNDinit", true, true, 2},
{"port::SNDrestore", true, true, 0},
{"port::soundThread", true, true, 0},
{"port::setSoundServer", true, true, 1},
// port_timer.cpp.
{"port::timerThread", true, true, 0},
{"port::clearTimerCallbacks", true, true, 0},
{"port::timerTick", true, true, 0},
{"port::addTimerCallback", true, true, 1},
{"port::removeTimerCallback", true, true, 1},
{"port::stopTimer", true, true, 1},
{"port::startTimer", true, true, 1},
// port_snd_fx.cpp.
{"port::reverbLength", true, true, 1, true, kNoHeap, true},
{"port::reverbInit", true, true, 1, true, kNoHeap, true},
{"port::iSNDwinsetfx", true, true, 1},
{"port::setBusFx", true, true, 2},
{"port::busLevelSet", true, true, 0},
{"port::SNDfxlevel", true, true, 3},
{"port::SNDfxinitbus", true, true, 4},
{"port::SNDfxmasterlevel", true, true, 2},
{"port::iSNDmixreinit", true, true, 1},
{"port::mixFunctions", true, true, 0},
{"port::iSNDmixinit", true, true, 2},
// port_snd_mixsetup.cpp.
{"port::pcmOnceMono", true, true, 4},
{"port::pcmOnceStereo", true, true, 4},
{"port::pcmOnceStereo2", true, true, 4},
{"port::pcmOnceQuad", true, true, 4},
{"port::pcmLoopedMono", true, true, 4},
{"port::pcmLoopedStereo", true, true, 4},
{"port::pcmLoopedStereo2", true, true, 4},
{"port::pcmLoopedQuad", true, true, 4},
{"port::pcmStreamedMono", true, true, 4},
{"port::pcmStreamedStereo", true, true, 4},
{"port::pcmStreamedStereo2", true, true, 4},
{"port::pcmStreamedQuad", true, true, 4},
{"port::pcmOnceSetup", true, true, 4},
{"port::pcmLoopedSetup", true, true, 4},
{"port::pcmStreamedSetup", true, true, 3},
{"port::xaOnceSetup", true, true, 4},
{"port::xaIntroSetup", true, true, 4},
{"port::xaStereoStreamSetup", true, true, 4},
{"port::packetPlayerOf", true, true, 1},
{"port::xaStereoFileSetup", true, true, 4},
{"port::volumeMonoSetup", true, true, 0},
{"port::volumeStereoSetup", true, true, 0},
{"port::resampleMonoSetup", true, true, 0},
{"port::resampleStereoSetup", true, true, 0},
{"port::resampleMonoStep", true, true, 0},
{"port::resampleStereoStep", true, true, 0},
{"port::pcmTablesFirst", true, true, 0},
{"port::pcmTablesSecond", true, true, 0},
{"port::xaFloatTable", true, true, 0, true, kNoHeap, true},
{"port::xaIntTable", true, true, 0},
{"port::xaTables", true, true, 0, true, kNoHeap, true},
{"port::lastTables", true, true, 0},
{"port::reverbStart", true, true, 0},
// native_snd_music.cpp, native_snd_effects.cpp: every register.
{"port::soundExit", true, true, 0},
{"port::deleteMusicCopy", true, true, 0},
{"port::raceTuneOf", true, true, 0},
{"port::raceMusicPrepare", true, true, 0},
{"port::musicStreamMake", true, true, 0},
{"port::musicStreamMakeOf", true, true, 0},
{"port::musicAfterSetting", true, true, 0},
{"port::musicMenuSix", true, true, 0},
{"port::musicStart", true, true, 0},
{"port::raceMusicStart", true, true, 0},
{"port::musicStop", true, true, 0},
{"port::musicStreamEnd", true, true, 0},
{"port::banksFree", true, true, 0},
{"port::banksRemove", true, true, 0},
{"port::bankLoad", true, true, 0},
{"port::slotStop", true, true, 0},
{"port::slotEffect", true, true, 0},
{"port::slotPlay", true, true, 0},
{"port::playMenuEffect", true, true, 0},
{"port::playCarEffectFive", true, true, 0},
{"port::playEffect", true, true, 0},
{"port::playSpeechEffect", true, true, 0},
{"port::panFromSide", true, true, 0},
{"port::masterSilent", true, true, 0},
{"port::masterBack", true, true, 0},
{"port::silenceForMenus", true, true, 0},
{"port::silenceForRace", true, true, 0},
{"port::busInit", true, true, 0},
{"port::busUp", true, true, 0},
{"port::busDown", true, true, 0},
{"port::slotsStop", true, true, 0},
{"port::musicMuteToggle", true, true, 0},
{"port::SNDangle", true, true, 0},
// native_snd_mixfuncs.cpp: every register.
{"port::bufferPosition", true, true, 3},
{"port::panSides", true, true, 3},
{"port::volumeMonoPair", true, true, 0},
{"port::volumeMonoLevels", true, true, 0},
{"port::volumeStereoPair", true, true, 0},
{"port::volumeStereoLevels", true, true, 0},
{"port::volumeMonoLevelsMmx", true, true, 0},
{"port::volumeStereoLevelsMmx", true, true, 0},
{"port::resample8MonoSetup", true, true, 0},
{"port::resample8MonoStep", true, true, 0},
{"port::resample8MonoNeededDown", true, true, 0},
{"port::resample8MonoNeededSame", true, true, 0},
{"port::resample8MonoNeededUp", true, true, 0},
{"port::resample8MonoSame", true, true, 0},
{"port::resample8MonoDown", true, true, 0},
{"port::resample8MonoUp", true, true, 0},
{"port::resample8StereoSetup", true, true, 0},
{"port::resample8StereoStep", true, true, 0},
{"port::resample8StereoNeededDown", true, true, 0},
{"port::resample8StereoNeededSame", true, true, 0},
{"port::resample8StereoNeededUp", true, true, 0},
{"port::resample8StereoSame", true, true, 0},
{"port::resample8StereoDown", true, true, 0},
{"port::resample8StereoUp", true, true, 0},
{"port::resample16MonoNeededDown", true, true, 0},
{"port::resample16MonoNeededSame", true, true, 0},
{"port::resample16MonoNeededUp", true, true, 0},
{"port::resample16MonoSame", true, true, 0},
{"port::resample16MonoDown", true, true, 0},
{"port::resample16MonoUp", true, true, 0},
{"port::resample16StereoNeededDown", true, true, 0},
{"port::resample16StereoNeededSame", true, true, 0},
{"port::resample16StereoNeededUp", true, true, 0},
{"port::resample16StereoSame", true, true, 0},
{"port::resample16StereoDown", true, true, 0},
{"port::resample16StereoUp", true, true, 0},
{"port::pcmPlayed", true, true, 1},
{"port::pcmOnceDecode", true, true, 3},
{"port::pcmLoopedDecode", true, true, 3},
{"port::pcmStreamedDecode", true, true, 3},
{"port::pcmFileDecode", true, true, 3},
{"port::pcmFileSetup", true, true, 4},
{"port::pcmFileMono", true, true, 2},
{"port::pcmFileStereo", true, true, 2},
{"port::pcmFileStereo2", true, true, 2},
{"port::pcmFileQuad", true, true, 2},
{"port::xaPlayed", true, true, 1},
{"port::xaOnceDecode", true, true, 3},
{"port::xaKeptCopy", true, true, 4},
{"port::xaLoopDecode", true, true, 3},
{"port::xaIntroDecode", true, true, 3},
{"port::xaStreamDecode", true, true, 3},
{"port::xaStreamSetup", true, true, 4},
{"port::xaPacketDecode", true, true, 3},
{"port::xaPacketSetup", true, true, 4},
{"port::xaStereoPlayed", true, true, 1},
{"port::xaStereoOnceDecode", true, true, 3},
{"port::xaStereoOnceSetup", true, true, 4},
{"port::xaStereoKeptCopy", true, true, 4},
{"port::xaStereoLoopDecode", true, true, 3},
{"port::xaStereoIntroDecode", true, true, 3},
{"port::xaStereoIntroSetup", true, true, 4},
{"port::xaStereoStreamDecode", true, true, 3},
{"port::xaStereoPacketDecode", true, true, 3},
{"port::framesPlayedCoded", true, true, 1},
{"port::codedToWords", true, true, 3},
{"port::codedDecode", true, true, 3},
{"port::codedSetup", true, true, 4},
{"port::codedStreamDecode", true, true, 3},
{"port::codedStreamSetup", true, true, 2},
{"port::codedPacketDecode", true, true, 3},
{"port::codedPacketSetup", true, true, 2},
{"port::codedBits", true, true, 2},
{"port::codedSkip", true, true, 2},
{"port::codedPulses", true, false, 4},
{"port::codedInterpolate", true, true, 1},
{"port::codedFilter", true, true, 2},
{"port::codedSynthesis", true, true, 4},
{"port::codedStart", true, true, 2},
{"port::codedFrame", true, true, 2},
{"port::convert16", true, true, 0},
{"port::convertToWords", true, true, 0},
{"port::convertXaStereo", true, true, 0},
{"port::convert8", true, true, 0},
{"port::convertXaMono", true, true, 0},
// MIXFUNCS PROMISES
{"port::speechInit", true, true, 0},
{"port::speechFree", true, true, 0},
{"port::speechLine", true, true, 0},
{"port::scenerySounds", true, true, 0},
{"port::raceBanksLoad", true, true, 0},
{"port::raceAnnouncer", true, true, 0},
{"port::trackSounds", true, true, 0},
{"port::coDriverTick", true, true, 0},
{"port::carEngine", true, true, 0},
{"port::copCarSound", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::playerCarSound", true, true, 0},
{"port::copSourcesPick", true, true, 0},
{"port::raceSoundTick", true, true, 0},
{"port::zoneSound", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::voiceBankLoad", true, true, 0},
{"port::carBankLoad", true, true, 0},
{"port::placeAhead", true, true, 0},
{"port::placeAcross", true, true, 0},
{"port::carRadio", true, true, 0},
{"port::playerCopRadio", true, true, 0},
{"port::copLineFor", true, true, 0},
{"port::copRemove", true, true, 0},
{"port::carFlagTest", true, true, 0},
{"port::raceValue", true, true, 0},
{"port::soundNothing", true, true, 0},
{"port::slotsEmpty", true, true, 0},
{"port::raceBankLoad", true, true, 0},
{"port::raceSoundInit", true, true, 0},
{"port::raceSoundEnd", true, true, 0},
{"port::sourceReset", true, true, 0},
{"port::sourcesReset", true, true, 0},
{"port::copChaseSet", true, true, 0},
{"port::copSiren", true, true, 0},
{"port::copSirenStop", true, true, 0},
{"port::copEngine", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::copEngineStop", true, true, 0},
{"port::copDistance", true, true, 0},
{"port::copsCloseness", true, true, 0},
{"port::listenerMove", true, true, 0},
{"port::sourceDistance", true, true, 0},
{"port::sourceAngle", true, true, 0, false, kNoHeap, false, "ebx edx"},
{"port::carAngle", true, true, 0, false, kNoHeap, false, "ecx edx"},
{"port::copBeepTick", true, true, 0},
{"port::copBeepStart", true, true, 0, false, kNoHeap, false, "edx"},
{"port::copEffect", true, true, 0},
{"port::musicEventResume", true, true, 0},
{"port::chaseLevel", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"snd::descriptionLoad", true, true, 0},
{"port::descriptionSpeak", true, true, 0},
{"port::descriptionTick", true, true, 0},
{"port::descriptionStop", true, true, 0},
{"port::spokenStatus", true, true, 0},
{"port::descriptionStart", true, true, 0},
{"port::descriptionService", true, true, 0},
{"port::raceVoiceLoad", true, true, 0},
{"port::carLineSpeak", true, true, 0, false, kNoHeap, false, "ebx edx"},
{"port::spokenStop", true, true, 0},
{"port::raceVoiceFree", true, true, 0},
{"port::speechTick", true, true, 0},
// edx as the code leaves it is SND's from its last call, which the port's rewrite
// of SND does not leave; none of its callers' code reads it.
{"port::radioTick", true, true, 2},
{"port::radioStart", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::speechSaid", true, true, 0},
{"port::copRadio", true, true, 0},
{"port::queueSpeechLine", true, true, 0},
{"port::queueRaceLine", true, true, 0},
{"port::raceEventLine", true, true, 0},
{"port::gapLine", true, true, 0},
{"port::lapTimeLine", true, true, 0},
{"port::engineSoundsStart", true, true, 0},
{"port::farEffectAim", true, true, 0, true, kNoHeap, true},
{"port::farEffectPlay", true, true, 0},
{"port::farEffectTick", true, true, 0},
{"port::crowdEffect", true, true, 0, false, kNoHeap, false, "ecx edx"},
{"port::carEffectFifteen", true, true, 0},
{"port::crashPitch", true, true, 0},
{"port::crashEffect", true, true, 0},
{"port::scrapeEffect", true, true, 0},
{"port::carKnock", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::noiseByDistance", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::playerNoise", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
{"port::playerNoiseStop", true, true, 0},
{"port::sirenIsOn", true, true, 0},
{"port::sirenFirstTone", true, true, 0},
{"port::sirenSecondTone", true, true, 0},
{"port::sirenSteadyTone", true, true, 0},
{"port::sirenFirstDone", true, true, 0},
{"port::sirenSecondDone", true, true, 0},
{"port::sirenStart", true, true, 0},
{"port::sirenStop", true, true, 0},
{"port::sirenTick", true, true, 0},
{"port::noiseBySpeed", true, true, 0, false, kNoHeap, false, "ebx ecx edx"},
#elif defined(SOUND_ARGUMENTS)
/* The arena: tables (curves, envelopes, LFOs), patches' tag streams, play
 * options, what a function writes through a pointer. */
constexpr x86::reg32 kSoundArena = 0xc00000, kSoundArenaEnd = 0xc10000;
constexpr x86::reg32 kSoundTables = kSoundArena + 0x100;      // 0x40 tables of 0x100 bytes
constexpr x86::reg32 kSoundTags = kSoundArena + 0x8000;       // a tag stream
constexpr x86::reg32 kSoundOut = kSoundArena + 0xc000;        // pointers' targets
constexpr x86::reg32 kSoundPlays = kSoundArena + 0xd000;    // a play's options
// The banks out of the way of the game's sound's world, which lays its cars and
// lists on the arena's top (kSoundOut's).
constexpr x86::reg32 kSoundBanks = 0xc30000;                   // banks
constexpr x86::reg32 kSoundPatches = kSoundArena + 0x4800;    // 8 patches of 0x600
constexpr x86::reg32 kSoundSamples = kSoundArena + 0xa000;    // a sample's tags
constexpr x86::reg32 kSoundTimbre = kSoundArena + 0xb000;     // a timbre's settings, its data's places

x86::reg32 aSoundTable();

/* A tag of a patch's: its byte, its length, its number (big-endian). */
x86::reg32 putSoundTag(CheckApp& g, x86::reg32 at, x86::reg32 tag, x86::reg32 length, x86::reg32 number)
{
    g.getMemory<x86::reg8>(at++) = x86::reg8(tag);
    g.getMemory<x86::reg8>(at++) = x86::reg8(length);
    for (x86::reg32 k = length; k > 0; --k)
        g.getMemory<x86::reg8>(at++) = x86::reg8(k <= 4 ? number >> (8 * (k - 1)) : 0);
    return at;
}

/* A sample's tags, after 0xfd: its place, length, bits, channels, rate,
 * compression, loop, priority, 3D method and buffer -- each now and then. */
x86::reg32 makeSoundSample(CheckApp& g, x86::reg32 at, bool threeD = true)
{
    if (chance(90))
        at = putSoundTag(g, at, 0x8a, 4, random32());
    if (chance(80))
        at = putSoundTag(g, at, 0x85, 4, below(0x10000));
    if (chance(80))
        at = putSoundTag(g, at, 0x81, 1, chance(80) ? 0x10 : 8);
    if (chance(80))
        at = putSoundTag(g, at, 0x82, 1, 1 + below(2));
    if (chance(70))
        at = putSoundTag(g, at, 0x84, 2, chance(60) ? 22050 : 8000 + below(40000));
    if (chance(60))
        at = putSoundTag(g, at, 0x83, 1, chance(40) ? 0 : chance(50) ? 7 : chance(80) ? 9 : below(0x10));
    if (chance(30))
        at = putSoundTag(g, at, 0x86, 4, chance(80) ? below(0x1000) : random32());
    if (chance(30))
        at = putSoundTag(g, at, 0x87, 4, chance(80) ? below(0x2000) : random32());
    if (chance(30))
        at = putSoundTag(g, at, 0x91, 1, below(0x80));
    // A 3D method with its buffer's place: a sample has the one with the other.
    // A patch's never eacsnd's (3): letting it go writes 2 past the method's tag,
    // into the tag after it -- the port's eacsnd never makes one.
    if (chance(20))
    {
        at = putSoundTag(g, at, 0x92, 1, chance(50) || !threeD ? below(3) : chance(80) ? 3 : 2);
        at = putSoundTag(g, at, 0x93, 4, random32());
    }
    if (chance(5))
        g.getMemory<x86::reg8>(at++) = 0xfc;
    g.getMemory<x86::reg8>(at++) = 0xfe;
    return at;
}

/* A patch: 'PT', its platform, its flags; timbres of safe tags (their
 * numbers small where they are places, none that divides), each with its
 * sample. */
void makeSoundPatch(CheckApp& g, x86::reg32 at)
{
    g.getMemory<x86::reg16>(at) = x86::reg16(chance(95) ? 0x5450 : random32());
    g.getMemory<x86::reg8>(at + 2) = x86::reg8(chance(95) ? 0 : 1);
    g.getMemory<x86::reg8>(at + 3) = x86::reg8(chance(50) ? 0 : chance(50) ? 2 : below(4));
    x86::reg32 p = at + ((g.getMemory<x86::reg8>(at + 3) & 2) ? 8 : 4);
    static const x86::reg8 tags[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11, 0x12,
                                     0x13, 0x15, 0x17, 0x1b, 0x1c, 0x1d, 0x20, 0x22, 0x24, 0x25};
    const x86::reg32 timbres = 1 + below(3);
    for (x86::reg32 t = 0; t < timbres; ++t)
    {
        for (x86::reg32 n = below(8); n > 0; --n)
        {
            const x86::reg8 tag = tags[below(sizeof tags)];
            x86::reg32 number = below(0x80);
            if (tag == 0xb)
                number = 1 + below(3);
            else if (tag == 2 || tag == 4)
                number = 0x40 + below(0x40);
            else if (tag == 1 || tag == 3 || tag == 0x12 || tag == 0x15 || tag == 0x17 || tag == 0x1d || tag == 0x20)
                number = below(0x40);
            p = putSoundTag(g, p, tag, 1 + below(2), number);
        }
        // The first timbre has its sample: one without plays the sample before it,
        // and the first would play from where the caller left ebp.
        if (t == 0 || chance(90))
        {
            g.getMemory<x86::reg8>(p++) = 0xfd;
            p = makeSoundSample(g, p, false);
        }
        else
            g.getMemory<x86::reg8>(p++) = 0xfe;
    }
    g.getMemory<x86::reg8>(p) = 0xff;
}

/* A bank: its id, version 2 or 4, its patches (at most 0x10) and its header's
 * size; its table of patches -- addresses, or offsets from their slots as a
 * bank is before SNDbankadd. */
void makeSoundBank(CheckApp& g, x86::reg32 bank, bool offsets)
{
    g.word(bank) = chance(95) ? 0x6c4b4e42 : random32();
    g.getMemory<x86::reg8>(bank + 4) = x86::reg8(chance(50) ? 4 : chance(90) ? 2 : below(8));
    const x86::reg32 count = chance(90) ? below(0x11) : below(0x30);
    g.getMemory<x86::reg16>(bank + 6) = x86::reg16(count);
    g.word(bank + 8) = below(0x100);
    const x86::reg32 table = bank + (g.getMemory<x86::reg8>(bank + 4) == 4 ? 0x14 : 0xc);
    for (x86::reg32 i = 0; i < 0x30; ++i)
    {
        const x86::reg32 patch = i < 0x10 && chance(80) ? kSoundPatches + 0x600 * below(8) : 0;
        g.word(table + 4 * i) = offsets && patch != 0 ? patch - table - 4 * i : patch;
    }
}

/* A timbre's settings as iSNDplaytaggedtimbre gets them: its voices few,
 * its places in the arena, its envelope's ticks never 0, its LFOs' lengths
 * not 0. */
void makeSoundTimbre(CheckApp& g, x86::reg32 t)
{
    for (x86::reg32 i = 0; i < 0x98; i += 4)
        g.word(t + i) = random32();
    for (x86::reg32 i = 0; i < 0x98; i += 4)
        g.word(t + 0x200 + i) = chance(70) ? 0 : below(0x40);
    g.word(t + 0x14) = chance(50) ? 0xffff : random32();
    g.word(t + 0x18) = below(0x80);
    g.word(t + 0x1c) = below(0x80);
    g.word(t + 0x2c) = 1 + below(3);
    g.word(t + 0x30) = below(0x90);
    g.word(t + 0x34) = chance(60) ? 0 : below(0x2000);
    g.word(t + 0x38) = below(0x90);
    g.word(t + 0x3c) = chance(60) ? 0 : below(0x2000);
    g.word(t + 0x40) = below(0x4000);
    g.word(t + 0x44) = chance(60) ? 0 : below(0x2000);
    // Places as a patch's tags give them: none, or an offset that its data's
    // place, added, makes a table's.
    for (const x86::reg32 at : {0x48u, 0x54u, 0x5cu, 0x74u, 0x80u})
    {
        const bool there = chance(50);
        g.word(t + at) = there ? below(0x40) : 0;
        g.word(t + 0x200 + at) = there ? aSoundTable() - 0x40 - g.word(t + at) : 0;
    }
    const x86::reg32 envelope = kSoundTables + 0x100 * below(0x40);
    g.word(t + 0x64) = envelope;
    g.word(t + 0x264) = 0;
    g.word(envelope) = chance(80) ? 1 + below(0x40) : 0x80000000 | random32();
    g.word(t + 0x70) = below(0x80);
    g.word(t + 0x78) = 1 + below(0x40);
    g.word(t + 0x84) = 1 + below(0x40);
    g.word(t + 0x7c) = chance(50) ? 0 : 1;
    g.word(t + 0x8c) = chance(50) ? 0 : 1;
    g.word(t + 0x90) = chance(50) ? 0 : 1;
    g.word(t + 0x94) = below(4);
}

/* A table of the arena's, its middle -- a byte index either way stays in it. */
x86::reg32 aSoundTable()
{
    return kSoundTables + 0x100 * below(0x40) + 0x80;
}

/* A sound's handle: of a voice mostly, as allocVoices makes them. */
x86::reg32 aSoundHandle(CheckApp& g)
{
    if (chance(85))
    {
        const x86::reg32 h = g.word(0xa09b3c + 0x60 * below(16));
        if (x86::sreg32(h) >= 0 || chance(20))
            return h;
    }
    return chance(50) ? (random32() & 0x7fffffe0) | below(16) : random32();
}

/* A volume, pan or bend: 0..127 mostly, now and then past either end. */
x86::reg32 aSoundLevel()
{
    return chance(90) ? below(0x80) : chance(50) ? x86::reg32(-1 - x86::sreg32(below(4))) : 0x80 + below(0x100);
}

/* A tag stream of a patch's: tags with up to 4 bytes of data, now and then a
 * pad or a long length, ended by 0xff. */
void makeSoundTags(CheckApp& g, x86::reg32 at)
{
    for (x86::reg32 i = 0; i < 0x40 && at < kSoundTags + 0x3f00; ++i)
    {
        if (chance(8))
        {
            g.getMemory<x86::reg8>(at++) = 0xfc;
            continue;
        }
        const x86::reg8 tag = x86::reg8(chance(10) ? 0xfd + below(2) : below(0xfc));
        g.getMemory<x86::reg8>(at++) = tag;
        if (tag >= 0xfd)
            continue;
        x86::reg32 length = chance(85) ? below(5) : 5 + below(8);
        if (chance(5))
        {
            g.getMemory<x86::reg8>(at++) = 0xff;
            for (x86::reg32 k = 0; k < 4; ++k)
                g.getMemory<x86::reg8>(at++) = x86::reg8(k == 3 ? length : 0);
        }
        else
            g.getMemory<x86::reg8>(at++) = x86::reg8(length);
        for (x86::reg32 k = 0; k < length; ++k)
            g.getMemory<x86::reg8>(at++) = x86::reg8(random32());
    }
    g.getMemory<x86::reg8>(at) = 0xff;
}

/* The library's world: inited mostly; its voices as the game leaves them --
 * free, playing, in groups, with envelopes and curves in the arena; the
 * platform's view of them, played by the mixer mostly; the channels'
 * functions stand-ins; eacsnd's 3D functions stand-ins of their words. */
void makeSoundWorld(CheckApp& g)
{
    for (x86::reg32 at = kSoundArena; at < kSoundArenaEnd; at += 4)
        g.word(at) = random32();
    makeSoundTags(g, kSoundTags);
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    auto halfAt = [&](x86::reg32 at) { return g.getMemory<x86::reg16>(at); };
    byteAt(0xa09af4) = x86::reg8(chance(92) ? 1 : 0);
    byteAt(0xa09af5) = x86::reg8(below(0x80));
    byteAt(0xa09af6) = x86::reg8(chance(80) ? 0x10 : below(0x11));
    byteAt(0xa09af7) = x86::reg8(chance(70) ? 0 : 1);
    byteAt(0xa09af8) = x86::reg8(below(3));
    byteAt(0xa09af9) = x86::reg8(below(7));
    g.word(0xa09afc) = random32();
    for (x86::reg32 i = 0; i < 6; ++i)
        g.word(0xa09b0c + 4 * i) = standInFor(0xfff310);
    byteAt(0x5678b0) = x86::reg8(random32());
    g.word(0x56786c) = chance(90) ? (random32() & 0x7fffffe0) : 0x7fffffe0 + below(0x20);
    for (x86::reg32 i = 0; i < 0x10; ++i)
        byteAt(0x9f6a54 + i) = x86::reg8(chance(80) ? below(16) : random32());
    g.word(0x9ef614) = (chance(80) ? 0 : below(0x40) << 16) | (chance(80) ? 22050 : 11025 + below(33075));
    for (x86::reg32 at = 0x5644e0; at < 0x5644f8; at += 4)
        g.word(at) = chance(5) ? 0xffffffff : random32();
    // eacsnd's functions where the game keeps them, as stdcall stand-ins of their words.
    static const char* const direct[] = {"_iSNDdirectcreate3dbuf@28", "_iSNDdirectremovebuf@4",
                                         "_iSNDdirectplay3d@28", "_iSNDdirectpos3d@12", "_iSNDdirectvol@8",
                                         "_iSNDdirectrate@8", "_iSNDdirectstopbuf@4"};
    for (x86::reg32 i = 0; i < 7; ++i)
        g.word(0x9ef638 + 4 * i) = namedStandIn(direct[i]);
    g.word(0x9f6b1c) = standInFor(0xfff308);
    g.word(0x9f6b24) = standInFor(0xfff30c);
    // The groups the voices share: a few, so that groups have several.
    const x86::reg8 groups[] = {0, 0, 0, x86::reg8(1 + below(255)), x86::reg8(1 + below(255))};
    for (x86::reg32 i = 0; i < 16; ++i)
    {
        const x86::reg32 v = 0xa09b3c + 0x60 * i;
        for (x86::reg32 at = v; at < v + 0x60; at += 4)
            g.word(at) = random32();
        g.word(v) = chance(70) ? (random32() & 0x7fffffe0) | i : chance(60) ? 0xffffffff : random32();
        byteAt(v + 0xc) = x86::reg8(chance(55) ? 1 : chance(60) ? 0 : chance(80) ? 2 : random32());
        byteAt(v + 0xe) = x86::reg8(chance(70) ? below(0x80) : random32());
        g.word(v + 0x14) = chance(30) ? g.word(0xa09afc) - below(0x100) : random32();
        g.word(v + 0x18) = chance(40) ? 0 : x86::reg32(x86::sreg32(below(0x40000)) - 0x20000);
        g.word(v + 0x1c) = chance(20) ? x86::reg32(-1 - x86::sreg32(below(0x10000))) : below(0x80) << 16;
        g.word(v + 0x20) = chance(80) ? below(0x80) << 16 | below(0x10000) : random32();
        g.word(v + 0x24) = chance(50) ? 0 : x86::reg32(x86::sreg32(below(0x20000)) - 0x10000);
        g.word(v + 0x28) = below(0x80) << 16 | below(0x10000);
        g.word(v + 0x2c) = chance(40) ? 0 : chance(90) ? below(0x40) : random32();
        byteAt(v + 0x34) = x86::reg8(chance(80) ? 1 + below(8) : random32());
        byteAt(v + 0x35) = x86::reg8(below(8));
        byteAt(v + 0x37) = x86::reg8(chance(60) ? 1 : below(4));
        byteAt(v + 0x3a) = x86::reg8(chance(70) ? 0 : 1);
        byteAt(v + 0x3b) = groups[below(5)];
        byteAt(v + 0x3c) = x86::reg8(1 + below(0x40));
        byteAt(v + 0x3d) = x86::reg8(1 + below(0x40));
        byteAt(v + 0x3e) = x86::reg8(below(0x40));
        byteAt(v + 0x3f) = x86::reg8(below(0x40));
        byteAt(v + 0x44) = x86::reg8(below(16));
        // The envelope: 8 segments of (ticks, level) -- a level of 0..127,
        // ticks of 1 and up mostly, none, or for ever (negative).
        const x86::reg32 envelope = kSoundTables + 0x100 * below(0x40);
        for (x86::reg32 s = 0; s < 0x20; ++s)
        {
            g.word(envelope + 8 * s) = chance(80) ? 1 + below(0x40) : chance(50) ? 0x80000000 | random32() : 1;
            g.word(envelope + 8 * s + 4) = below(0x80);
        }
        g.word(v + 0x48) = envelope;
        for (const x86::reg32 at : {0x4cu, 0x50u, 0x54u, 0x58u, 0x5cu})
            g.word(v + at) = chance(55) ? 0 : aSoundTable();
        const x86::reg32 p = 0x9ef658 + 0x10 * i;
        for (x86::reg32 at = p; at < p + 0x10; at += 4)
            g.word(at) = random32();
        halfAt(p) = x86::reg16(chance(70) ? 22050 : 8000 + below(40000));
        // How it is played: never past 3 -- iSNDplatformplay sets no other, and past it
        // the code reads its frame's locals unset.
        byteAt(p + 5) = x86::reg8(chance(85) ? below(3) : 3);
        byteAt(p + 6) = x86::reg8(chance(50) ? 0 : 1);
        byteAt(p + 8) = x86::reg8(below(0x100) - 0x80);
        byteAt(p + 9) = x86::reg8(below(0x100) - 0x80);
        const x86::reg32 c = 0x9fbcb4 + 0xde4 * i;
        for (x86::reg32 at = c; at < c + 0x10; at += 4)
            g.word(at) = random32();
        byteAt(c + 3) = x86::reg8(chance(50) ? 0 : below(0x80));
        g.word(c + 0xdb0) = standInFor(0xfff300);
        g.word(c + 0xdbc) = standInFor(0xfff304);
        g.word(c + 0xddc) = standInFor(0xfff304);
    }
    // The mixer's set-up functions by format: stand-ins, now and then none.
    for (x86::reg32 at = 0x9f6a6c; at < 0x9f6adc; at += 4)
        g.word(at) = chance(95) ? standInFor(0xfff314) : 0;
    for (x86::reg32 at = 0x9f6adc; at < 0x9f6aec; at += 4)
        g.word(at) = chance(95) ? standInFor(0xfff318) : 0;
    for (x86::reg32 at = 0x9f6aec; at < 0x9f6b0c; at += 4)
        g.word(at) = chance(95) ? standInFor(0xfff31c) : 0;
    for (x86::reg32 i = 0; i < 8; ++i)
        makeSoundPatch(g, kSoundPatches + 0x600 * i);
    // The banks: 24 handles, a bank of the arena's or none, being loaded or not.
    for (x86::reg32 b = 0; b < 24; ++b)
    {
        const x86::reg32 at = 0xa0a13c + 12 * b;
        g.word(at) = chance(70) ? kSoundBanks + 0x100 * below(0x10) : 0;
        g.word(at + 4) = random32();
        g.word(at + 8) = chance(80) ? 0 : 1;
    }
    for (x86::reg32 k = 0; k < 0x10; ++k)
        makeSoundBank(g, kSoundBanks + 0x100 * k, false);
}

/* The CD streams' arena: the first stream, its command blocks, a second and a
 * third stream; their rings; names and buffers. */
constexpr x86::reg32 kStreamArena = 0xc10000;
constexpr x86::reg32 kStreamFirst = kStreamArena, kStreamSecond = kStreamArena + 0xc00, kStreamThird = kStreamArena + 0xd00;
constexpr x86::reg32 kStreamRing = kStreamArena + 0x1000, kStreamRingSecond = kStreamArena + 0x8000;
constexpr x86::reg32 kStreamNames = kStreamArena + 0xe00;     // file names, 0x40 apart
constexpr x86::reg32 kStreamBuffer = kStreamArena + 0xf000;   // a buffer of silence
constexpr x86::reg32 kStreamBlocks = 8;

/* A stream's chunk ids, as the ring holds them (the file's bytes): data,
 * header, loop, seek, end. */
constexpr x86::reg32 kStreamIds[] = {0x6c444353, 0x6c484353, 0x6c434353, 0x6c4c4353, 0x6c454353};

/* A header chunk's patch at `at`, 0x5c bytes at most: 'PT', a few safe tags,
 * one sample.  Its length. */
x86::reg32 makeStreamHeader(CheckApp& g, x86::reg32 at)
{
    const x86::reg32 start = at;
    g.getMemory<x86::reg16>(at) = 0x5450;
    g.getMemory<x86::reg8>(at + 2) = 0;
    g.getMemory<x86::reg8>(at + 3) = 0;
    at += 4;
    static const x86::reg8 tags[] = {5, 6, 7, 8, 9, 0xa, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11};
    for (x86::reg32 n = below(4); n > 0; --n)
        at = putSoundTag(g, at, tags[below(sizeof tags)], 1, below(0x80));
    g.getMemory<x86::reg8>(at++) = 0xfd;
    if (chance(80))
        at = putSoundTag(g, at, 0x85, 4, below(0x10000));
    if (chance(80))
        at = putSoundTag(g, at, 0x81, 1, chance(80) ? 0x10 : 8);
    if (chance(80))
        at = putSoundTag(g, at, 0x82, 1, 1 + below(2));
    if (chance(70))
        at = putSoundTag(g, at, 0x84, 2, chance(60) ? 22050 : 8000 + below(40000));
    if (chance(60))
        at = putSoundTag(g, at, 0x83, 1, chance(40) ? 0 : chance(50) ? 7 : 9);
    g.getMemory<x86::reg8>(at++) = 0xfe;
    g.getMemory<x86::reg8>(at++) = 0xff;
    return at - start;
}

/* A stream's ring filled with chunks end to end -- data, headers, loops,
 * seeks, ends, given back, dropped, now and then a wrap or junk -- its ends
 * where the chunks are: what was freed, read, the chunk being written and
 * where the reader writes in it.  The chunks' places. */
std::vector<x86::reg32> makeStreamRing(CheckApp& g, x86::reg32 s, x86::reg32 ring, x86::reg32 size)
{
    std::vector<x86::reg32> chunks;
    x86::reg32 p = ring;
    while (p + 0x100 < ring + size)
    {
        chunks.push_back(p);
        x86::reg32 id = kStreamIds[below(5)];
        if (chance(15))
            id = chance(60) ? 0xfffffffe : chance(70) ? 0xfffffffd : chance(50) ? 0xffffffff : random32();
        x86::reg32 length = 8 + 4 * below(0x30);
        // The file's bytes small: where the reader takes them for a chunk's
        // header, a length it takes on with -- one past the ring an error the
        // game stops at, and the harness goes on from.
        for (x86::reg32 at = p + 8; at < p + length; at += 4)
            g.word(at) = below(0x100);
        if (id == kStreamIds[1])
            length = (8 + makeStreamHeader(g, p + 8) + 3) & ~3u;
        else if (id == kStreamIds[0])
            g.word(p + 8) = below(0x100);
        else if (id == kStreamIds[2])
            g.word(p + 8) = x86::reg32(x86::sreg32(below(8)) - 2);
        if (chance(3))
            length = 1 + random32() % 0xff;  // never 0: a chunk given back of none is passed over for ever
        g.word(p) = id;
        g.word(p + 4) = length;
        p += length < 8 ? 8 : length;
    }
    const auto pick = [&](x86::reg32 from) { return from + below(x86::reg32(chunks.size()) - from); };
    const x86::reg32 freed = pick(0), read = pick(freed), written = pick(read);
    for (x86::reg32 i = freed; i < read; ++i)
        if (chance(70))
            g.word(chunks[i]) = 0xfffffffe;
    g.word(s + 4) = ring;
    g.word(s + 8) = ring + size;
    g.word(s + 0x3c) = size;
    g.word(s + 0x84) = size;
    g.word(s + 0x88) = ring;
    g.word(s + 0x18) = chunks[freed];
    g.word(s + 0x14) = chunks[read];
    g.word(s + 0x10) = chunks[written];
    g.word(s + 0xc) = chunks[written] + (chance(50) ? 0 : 4 * below(0x10));
    return chunks;
}

/* A file's name in the arena. */
x86::reg32 aStreamName(CheckApp& g)
{
    const x86::reg32 name = kStreamNames + 0x40 * below(4);
    const x86::reg32 length = 4 + below(0x20);
    for (x86::reg32 i = 0; i < 0x40; ++i)
        g.getMemory<x86::reg8>(name + i) = x86::reg8(i < length ? 'a' + below(26) : 0);
    return name;
}

struct StreamWorld
{
    std::vector<x86::reg32> chunks, second, blocks;
};

/* The streams' world: the first CD stream with its ring, command blocks
 * (free and queued) and reader's state, a second taking some of the chunks,
 * now and then a third; the system tasks; the top-up's coordination; the SND
 * streamer's state on the first, its queue of the ring's chunks. */
StreamWorld makeStreamWorld(CheckApp& g, bool spinFree)
{
    StreamWorld w;
    // The jump tables the game's code dispatches the streamer's service and
    // the reader thread by, in its code segment (which the harness does not
    // load): nfs3.exe's words.
    static const x86::reg32 service[] = {0x4e85d1, 0x4e85dc, 0x4e8769, 0x4e87ef, 0x4e8840};
    static const x86::reg32 reader[] = {0x4e5448, 0x4e5877, 0x4e5af5, 0x4e53ee, 0x4e53ee, 0x4e53ee, 0x4e54c3,
                                        0x4e5572, 0x4e53ee, 0x4e53ee, 0x4e57e8, 0x4e53ee, 0x4e56f2, 0x4e53ee,
                                        0x4e53ee, 0x4e5877, 0x4e5448, 0x4e5448, 0x4e5448, 0x4e56f2};
    for (x86::reg32 i = 0; i < 5; ++i)
        g.word(0x4e8594 + 4 * i) = service[i];
    for (x86::reg32 i = 0; i < 20; ++i)
        g.word(0x4e5364 + 4 * i) = reader[i];
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    for (x86::reg32 at = kStreamArena; at < kStreamArena + 0x10000; at += 4)
        g.word(at) = below(0x100);
    const x86::reg32 s = kStreamFirst, t = kStreamSecond;
    w.chunks = makeStreamRing(g, s, kStreamRing, chance(70) ? 0x4000 : 0x1000 + 0x400 * below(0x18));
    w.second = makeStreamRing(g, t, kStreamRingSecond, chance(70) ? 0x4000 : 0x1000 + 0x400 * below(0x18));
    // The third's ring, small: the reader writes through every stream's ends.
    makeStreamRing(g, kStreamThird, kStreamArena + 0xec00, 0x400);
    static const x86::reg32 states[] = {1, 2, 3, 7, 7, 7, 8, 0xb, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13, 0x14};
    for (const x86::reg32 at : {s, t, kStreamThird})
    {
        g.word(at + 0x20) = chance(95) ? states[below(sizeof states / sizeof *states)] : random32() % 0x20;
        g.word(at + 0x24) = chance(60) ? 0 : chance(40) ? 8 : chance(50) ? 0xf : below(0x20);
        g.word(at + 0x28) = spinFree || chance(70) ? 0 : 1;
        g.word(at + 0x1c) = chance(80) ? 0x7100 + 4 * below(0x40) : 0;
        g.word(at + 0x2c) = chance(50) ? 1 : 0;
        g.word(at + 0x40) = chance(60) ? 0x800 : 0x100 * (1 + below(0x20));
        g.word(at + 0x44) = x86::reg32(x86::sreg32(below(0x400)) - 0x100);
        g.word(at + 0x48) = 8 + below(0x200);
        g.word(at + 0x4c) = below(0x40);
        g.word(at + 0x50) = below(0x10000);
        g.word(at + 0x54) = g.word(at + 0x50) + below(0x40000);
        g.word(at + 0x58) = below(0x40000);
        g.word(at + 0x5c) = g.word(at + 0x50) + below(0x40000);
        g.word(at + 0x60) = below(0x10000);
        // The chunks it takes: a mask and an id of the big-endian ids.
        g.word(at + 0x6c) = chance(50) ? 0xffffffff : 0xffffff00;
        g.word(at + 0x68) = chance(80) ? 0x5343446c & g.word(at + 0x6c) : random32();
        g.word(at + 0x78) = 0;
        g.word(at + 0x7c) = 0;
        g.word(at + 0x74) = 0;
        g.word(at + 0xa0) = 1 + below(4);
        g.word(at + 0xa4) = 0x7400 + 4 * below(0x40);
        g.word(at + 0xa8) = 0x7400 + 4 * below(0x40);
        g.word(at + 0xac) = 0x7500 + 4 * below(0x40);
        g.word(at + 0xb0) = below(0x40);
        g.word(at + 0xb4) = chance(50) ? 1 : 0;
        g.word(at + 0xb8) = below(0x10000);
        g.word(at + 0xbc) = below(0x10000);
    }
    // The chain of streams: the first, the second, now and then a third.
    g.word(s + 0x70) = chance(60) ? t : 0;
    g.word(t + 0x70) = chance(20) ? kStreamThird : 0;
    g.word(kStreamThird + 0x70) = 0;
    // The command blocks: free ones chained, queued ones with their commands.
    static const x86::reg32 commands[] = {1, 2, 0xb, 0xd, 0x10, 0x11, 0x12, 0x13, 0x14, 0x17};
    for (x86::reg32 i = 0; i < kStreamBlocks; ++i)
    {
        const x86::reg32 b = s + 0xc0 + 0x9c * i;
        w.blocks.push_back(b);
        const x86::reg32 length = 2 + below(0x20);
        for (x86::reg32 k = 0; k < 0x90; ++k)
            byteAt(b + k) = x86::reg8(k < length ? 'a' + below(26) : 0);
        g.word(b + 0x90) = below(0x10000);
        g.word(b + 0x94) = chance(95) ? commands[below(10)] : below(0x20);
        g.word(b + 0x98) = 0;
        const x86::reg32 list = chance(50) ? 0x74 : 0x78;
        if (chance(80))
        {
            g.word(b + 0x98) = g.word(s + list);
            g.word(s + list) = b;
            if (list == 0x78 && g.word(b + 0x98) == 0)
                g.word(s + 0x7c) = b;
        }
    }
    g.word(s + 0x80) = w.blocks[below(kStreamBlocks)];
    g.word(0x5645a4) = 1 + below(kStreamBlocks);
    g.word(0x5645b8) = chance(92) ? s : 0;
    g.word(0x5645bc) = chance(50) ? s : chance(50) ? t : 0;
    // The system tasks: stand-ins, due or not, running or not.
    g.word(0x79c1a0) = random32() % 0x10000;
    g.word(0x79c1a4) = random32() % 0x10000;
    g.word(0x564670) = below(3);
    g.word(0x564674) = chance(30) ? g.word(0x79c1a0) : random32();
    g.word(0x56466c) = chance(50) ? 1 : 0;
    g.word(0x5643bc) = 0;  // no rdtsc: the counter is the machine's, every run's own
    for (x86::reg32 i = 0; i < 16; ++i)
    {
        const x86::reg32 task = 0x9ef7e8 + 0x10 * i;
        g.word(task) = chance(40) ? standInFor(0xfff320) : 0;
        g.word(task + 4) = below(10);
        g.word(task + 8) = g.word(0x79c1a0) + below(8) - 4;
        g.word(task + 0xc) = chance(85) ? 0 : 1;
    }
    // The top-up's coordination.
    g.word(0x9f6a50) = chance(60) ? standInFor(0xfff324) : 0;
    g.word(0x567864) = chance(70) ? 0x7400 + 4 * below(0x40) : 0;
    g.word(0x56785c) = chance(50) ? 1 : 0;
    g.word(0x564480) = 0x7500 + 4 * below(0x40);
    g.word(0x5643d8) = chance(80) ? 1 : 0;
    // The streamer: on the first stream, its queue of the ring's chunks.
    g.word(0xa09b30) = chance(90) ? 0x4e784c : 0;
    g.word(0x56467c) = chance(95) ? s : t;
    g.word(0x564680) = 0;
    g.word(0x564684) = 0;
    if (chance(80))
    {
        x86::reg32 at = below(x86::reg32(w.chunks.size()));
        for (x86::reg32 n = 1 + below(6); n > 0 && at < w.chunks.size(); --n, at += 1 + below(3))
        {
            const x86::reg32 c = w.chunks[at];
            if (g.word(0x564680) == 0)
                g.word(0x564680) = c;
            else
                g.word(g.word(0x564684)) = c;
            g.word(0x564684) = c;
        }
        g.word(g.word(0x564684)) = chance(30) ? 0xffffffff : 0;
    }
    g.word(0x564688) = chance(60) ? w.chunks[below(x86::reg32(w.chunks.size()))] : 0;
    g.word(0x564690) = aSoundHandle(g);
    // The stream's patch: the last header's, which a header of another format
    // restarts the stream on before its own is copied.
    makeStreamHeader(g, 0x5646a0);
    g.word(0x564694) = below(0x100);
    g.word(0x564698) = below(0x20);
    g.word(0x56469c) = below(0x10000);
    byteAt(0x5646fc) = x86::reg8(chance(50) ? 1 : 0);
    byteAt(0x5646fd) = x86::reg8(below(5));  // past 4 the service jumps through its table past its end
    byteAt(0x5646fe) = x86::reg8(chance(50) ? 1 : 0);
    byteAt(0x5646ff) = x86::reg8(1 + below(8));  // never 0: SNDstreambuftime divides by it past its error
    byteAt(0x564700) = x86::reg8(chance(50) ? 1 : 0);
    byteAt(0x564701) = x86::reg8(below(16));
    byteAt(0x564702) = x86::reg8(below(0x80));
    byteAt(0x564703) = x86::reg8(below(0x80));
    byteAt(0x564704) = x86::reg8(below(0x80));
    byteAt(0x564705) = x86::reg8(below(0x80));
    g.getMemory<x86::reg16>(0x564706) = x86::reg16(chance(90) ? below(0x10) : 0x2700 + below(0x20));
    byteAt(0x564708) = x86::reg8(chance(50) ? 1 : 0);
    byteAt(0x564709) = x86::reg8(below(0x14));
    byteAt(0x56470a) = x86::reg8(below(0x14));
    byteAt(0x56470b) = x86::reg8(chance(50) ? 0xff : below(4));
    byteAt(0x56470c) = x86::reg8(chance(50) ? 1 : 0);
    byteAt(0x56470d) = x86::reg8(below(3));
    byteAt(0x56470e) = x86::reg8(below(0x14));
    byteAt(0x56470f) = x86::reg8(below(0x14));
    g.word(0x564710) = below(0x14);
    g.word(0x564714) = below(0x14);
    g.word(0x564718) = chance(20) ? 0xffffffff : below(0x10000);
    for (x86::reg32 i = 0; i < 0x14; ++i)
        g.word(0x56471c + 4 * i) = x86::reg32(x86::sreg32(below(8)) - 2);
    g.word(0x56476c) = chance(30) ? 0 : below(0x2000);
    g.word(0x564770) = g.word(0x79c1a4) + below(0x200) - 0x100;
    for (x86::reg32 i = 0; i < 0x18; ++i)
        byteAt(0x564774 + i) = x86::reg8(chance(80) ? below(2) : random32());
    const x86::reg32 named = below(0x20);
    for (x86::reg32 i = 0; i < 0x80; ++i)
        byteAt(0x56478c + i) = x86::reg8(i < named ? 'a' + below(26) : 0);
    g.word(0x564678) = below(0x10);
    g.word(0x56480c) = chance(30) ? standInFor(0xfff328) : 0;
    return w;
}

/* Pathfinder's map: 'PFDx', version 0, its start, nodes, events and rows,
 * the nodes with their branches, the rows of nodes by event, the nodes'
 * offsets (big-endian). */
constexpr x86::reg32 kPathMap = kStreamArena + 0xf800;

/* Pathfinder's world: its map, set up mostly, the node playing, the events
 * waiting, the controller.  The map's events. */
x86::reg32 makePathWorld(CheckApp& g)
{
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    const x86::reg32 m = kPathMap;
    const x86::reg32 nodes = 1 + below(8), events = 1 + below(8), rows = 1 + below(4);
    g.word(m) = chance(95) ? 0x78444650 : random32();
    byteAt(m + 4) = x86::reg8(chance(95) ? 0 : 1 + below(3));
    byteAt(m + 5) = x86::reg8(below(nodes));
    byteAt(m + 6) = x86::reg8(nodes);
    byteAt(m + 7) = x86::reg8(events);
    byteAt(m + 0xb) = x86::reg8(rows);
    for (x86::reg32 n = 0; n < nodes; ++n)
    {
        const x86::reg32 node = m + 0xc + 0x1c * n;
        for (x86::reg32 i = 0; i < 0x1c; ++i)
            byteAt(node + i) = x86::reg8(random32());
        byteAt(node) = x86::reg8(below(rows));
        byteAt(node + 1) = x86::reg8(below(9));
        for (x86::reg32 b = 0; b < 8; ++b)
        {
            const x86::sreg32 low = x86::sreg32(below(0x100)) - 0x40;
            byteAt(node + 4 + 3 * b) = x86::reg8(low);
            byteAt(node + 5 + 3 * b) = x86::reg8(low + x86::sreg32(below(0x40)));
            byteAt(node + 6 + 3 * b) = x86::reg8(below(nodes));
        }
    }
    const x86::reg32 table = m + 0xc + 0x1c * nodes;
    for (x86::reg32 i = 0; i < rows * events; ++i)
        byteAt(table + i) = x86::reg8(below(nodes));
    const x86::reg32 offsets = table + rows * events;
    for (x86::reg32 n = 0; n < nodes; ++n)
        g.word(offsets + 4 * n) = random32();
    const bool set = chance(85);
    g.word(0x56465c) = set ? m : 0;
    g.word(0x564660) = m + 0xc;
    g.word(0x5645cc) = table;
    g.word(0x5645d0) = offsets;
    g.word(0xa09b2c) = set || chance(20) ? 0x4e7388 : 0;
    g.getMemory<x86::reg16>(0x5645c0) = x86::reg16(below(2000));
    g.getMemory<x86::reg16>(0x5645c2) = x86::reg16(below(2000));
    g.getMemory<x86::reg16>(0x5645c4) = x86::reg16(below(nodes));
    byteAt(0x5645c6) = x86::reg8(random32());
    g.word(0x5645c8) = below(0x10);
    g.getMemory<x86::reg16>(0x564654) = x86::reg16(chance(50) ? 0xffff : below(events));
    g.getMemory<x86::reg16>(0x564656) = x86::reg16(below(3));
    g.getMemory<x86::reg16>(0x564658) = x86::reg16(chance(50) ? 0xffff : below(events));
    g.getMemory<x86::reg16>(0x56465a) = x86::reg16(below(3));
    const x86::reg32 named = 4 + below(0x20);
    for (x86::reg32 i = 0; i < 0x40; ++i)
        byteAt(0x5645d4 + i) = x86::reg8(i < named ? 'a' + below(26) : 0);
    return events;
}

/* SNDSTRM's arena: 16 streams of 0x800 (their requests after them), 16
 * packet players of 0x200, chunks of 0x40 -- 0x10 submitted as packets (their
 * first word a request's handle), 0x10 the queue hands out -- memory for a
 * stream made. */
constexpr x86::reg32 kStrmArena = 0xc20000;
constexpr x86::reg32 kStrmStreams = kStrmArena, kStrmPlayers = kStrmArena + 0x8000;
constexpr x86::reg32 kStrmChunks = kStrmArena + 0xc000, kStrmMemory = kStrmArena + 0xd000;

struct StrmWorld
{
    std::vector<x86::reg32> streams;   // the indices there are
    std::vector<x86::reg32> handles;   // their requests' handles
};

/* A header as the packet player takes one: its rate, its channels and
 * representation (byte 2), never a rate of 0 (the status divides by it). */
void makeStrmHeader(CheckApp& g, x86::reg32 at)
{
    static const x86::reg8 representations[] = {0, 8, 0xc, 0x10, 0x18};
    g.getMemory<x86::reg16>(at) = x86::reg16(chance(70) ? 22050 : 8000 + below(40000));
    g.getMemory<x86::reg8>(at + 2) = x86::reg8(representations[below(5)] | (1 + below(2)));
    g.getMemory<x86::reg8>(at + 3) = x86::reg8(chance(90) ? 0 : random32());
}

/* SNDSTRM's world: streams now and then, each with its requests, its packet
 * player (one of the 16) and the player's stream in the byte table; packet
 * players with their rings of packets, the callbacks the streams give them
 * or none; the queue's chunks, each of a stream's, its id one of the five. */
StrmWorld makeStrmWorld(CheckApp& g)
{
    StrmWorld w;
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    auto halfAt = [&](x86::reg32 at) { return g.getMemory<x86::reg16>(at); };
    for (x86::reg32 at = kStrmArena; at < kStrmArena + 0x10000; at += 4)
        g.word(at) = random32();
    for (x86::reg32 i = 0; i < 0x10; ++i)
    {
        g.word(0x9f254c + 4 * i) = 0;
        g.word(0xa0b044 + 4 * i) = 0;
    }
    // The players first: the streams take theirs from them.
    std::vector<x86::reg32> players;
    // Player 0 and stream 0 always: the packets' callbacks need a stream.
    for (x86::reg32 i = 0; i < 0x10; ++i)
    {
        if (i != 0 && !chance(60))
            continue;
        players.push_back(i);
        const x86::reg32 p = kStrmPlayers + 0x200 * i;
        g.word(0xa0b044 + 4 * i) = p;
        const x86::reg32 capacity = 2 + below(15);
        g.word(p) = chance(85) ? aSoundHandle(g) : 0xffffffff;
        g.word(p + 4) = below(0x100);
        halfAt(p + 8) = x86::reg16(capacity);
        halfAt(p + 0xa) = x86::reg16(below(capacity));
        halfAt(p + 0xc) = x86::reg16(chance(40) ? 0xffff : below(capacity));
        halfAt(p + 0xe) = x86::reg16(below(capacity));
        g.word(p + 0x10) = below(0x10000);
        g.word(p + 0x14) = below(0x10000);
        g.word(p + 0x1c) = chance(40) ? 0x4f3b44 : chance(50) ? standInFor(0xfff330) : 0;
        g.word(p + 0x20) = chance(40) ? 0x4f3b60 : chance(50) ? standInFor(0xfff334) : 0;
        for (x86::reg32 k = 0; k < capacity; ++k)
        {
            const x86::reg32 e = p + 0x28 + 0xc * k;
            g.word(e) = below(0x100);
            g.word(e + 4) = below(0x800);
            g.word(e + 8) = kStrmChunks + 0x40 * below(0x10) + 0xc;
        }
    }
    for (x86::reg32 i = 0; i < 0x10; ++i)
        byteAt(0x9f258c + i) = 0;
    for (x86::reg32 i = 0; i < 0x10; ++i)
    {
        if (i != 0 && !chance(60))
            continue;
        w.streams.push_back(i);
        const x86::reg32 s = kStrmStreams + 0x800 * i;
        g.word(0x9f254c + 4 * i) = s;
        const x86::reg32 most = 1 + below(8), count = i == 0 ? 1 + below(most) : below(most + 1);
        const x86::reg32 player = players[below(x86::reg32(players.size()))];
        g.word(s) = s + 0x4c;
        g.word(s + 4) = 0x7600 + 4 * below(0x40);
        g.word(s + 8) = chance(50) ? 0xffffffff : below(0x100);
        g.word(s + 0xc) = player;
        byteAt(0x9f258c + player) = x86::reg8(i);
        g.word(s + 0x10) = chance(95) ? below(0x10000) << 8 : 0x7fffff00;
        byteAt(s + 0x14) = x86::reg8(below(3));
        byteAt(s + 0x15) = x86::reg8(most);
        byteAt(s + 0x16) = x86::reg8(count);
        byteAt(s + 0x17) = x86::reg8(below(count + 1));
        byteAt(s + 0x18) = x86::reg8(chance(50) ? 1 : 0);
        makeStrmHeader(g, s + 0x1c);
        makeStrmHeader(g, s + 0x20);
        if (chance(20))
            halfAt(s + 0x1c) = 0;
        if (chance(30))
            g.word(s + 0x20) = g.word(s + 0x1c);
        for (x86::reg32 k = 0; k < 0xc; ++k)
            byteAt(s + 0x24 + k) = byteAt(s + 0x30 + k) = x86::reg8(below(0x80));
        if (chance(40))
            byteAt(s + 0x30 + below(0xc)) = x86::reg8(below(0x80));
        for (x86::reg32 k = 0; k < 0x10; ++k)
            byteAt(s + 0x3c + k) = x86::reg8(below(0x80));
        for (x86::reg32 k = 0; k < most; ++k)
        {
            const x86::reg32 r = s + 0x4c + 0x2c * k;
            const x86::reg32 handle = (below(0x100) << 8) | i;
            w.handles.push_back(handle);
            g.word(r) = kStrmChunks + 0x40 * (0x10 + below(0x10));
            g.word(r + 4) = handle;
            g.word(r + 8) = chance(50) ? 0xffffffff : below(0x10);
            g.word(r + 0xc) = chance(50) ? 0xffffffff : below(0x10);
            g.word(r + 0x10) = chance(80) ? 0x1000 + below(0x40000) : 0;
            g.word(r + 0x14) = below(0x4000);
            g.word(r + 0x18) = g.word(r + 0x14) + below(0x4000);
            g.word(r + 0x1c) = below(0x4000);
            g.word(r + 0x20) = below(0x10);
            g.word(r + 0x24) = below(4);
            halfAt(r + 0x28) = x86::reg16(chance(30) ? 0 : chance(20) ? 0xffff : below(0x400));
        }
    }
    // The packets' chunks, a request's handle first; the queue's: data, header
    // (its patch after its frames), loop, end or another.
    static const x86::reg32 ids[] = {0x6c444353, 0x6c484353, 0x6c434353, 0x6c454353, 0x6c4c4353};
    for (x86::reg32 k = 0; k < 0x20; ++k)
    {
        const x86::reg32 c = kStrmChunks + 0x40 * k;
        const x86::reg32 id = ids[below(5)];
        g.word(c) = k < 0x10 ? w.handles[below(x86::reg32(w.handles.size()))] : id;
        g.word(c + 4) = 0x40;
        g.word(c + 8) = below(0x800);
        if (k >= 0x10 && id == ids[1])
            makeStreamHeader(g, c + 8);
    }
    return w;
}

/* SNDSTRM's functions' arguments, on its world; false for another's. */
bool makeStrmArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "mul64", "div64", "platformPacketSize", "findStream", "streamCount", "findRequest",
        "SNDSTRM_requeststatus", "streamMemory", "playerMemory", "SNDSTRM_createqueued", "SNDSTRM_requestdata",
        "SNDSTRM_restore", "removeRequest", "packetFreed", "framesPlayed", "iSNDstreamparseheader",
        "iSNDstreamparseloop", "iSNDstreamparsedata", "iSNDstreamparseend", "iSNDstreamparsechunk",
        "streamWaits", "iSNDstreamsystemtask", "iSNDstreamcreate", "iSNDstreamrequest", "SNDSTRM_destroy",
        "SNDSTRM_purge", "SNDPKTPLAY_create", "SNDPKTPLAY_start", "SNDPKTPLAY_submit", "SNDPKTPLAY_submitspace",
        "framesOutstanding", "SNDPKTPLAY_framesoutstanding", "SNDPKTPLAY_purge", "SNDPKTPLAY_stop",
        "SNDPKTPLAY_destroy", "nextPacket", "packetFramesPlayed", "patchDefaults", "iSNDpatchtohdr",
        "iSNDplatformcalcdatarate", "streamChunksAtOnce"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    g_mostCalls = 300 + below(300);
    const StrmWorld w = makeStrmWorld(g);
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    // A stream there is (its index; any when none is), a player there is.
    const auto aStream = [&] {
        return !w.streams.empty() && chance(90) ? w.streams[below(x86::reg32(w.streams.size()))] : below(0x12);
    };
    const auto aPlayer = [&] {
        for (int tries = 0; tries < 20; ++tries)
        {
            const x86::reg32 i = below(0x10);
            if (g.word(0xa0b044 + 4 * i) != 0)
                return i;
        }
        return below(0x10);
    };
    const auto aHandle = [&] {
        return !w.handles.empty() && chance(85) ? w.handles[below(x86::reg32(w.handles.size()))]
                                                : chance(50) ? x86::reg32(-1 - x86::sreg32(below(4))) : random32();
    };
    // A chunk of the arena's, its stream's index in its id's place where the
    // packet's data points past it.
    const auto aChunk = [&](x86::reg32 id) {
        const x86::reg32 c = kStrmChunks + 0x40 * (0x10 + below(0x10));
        if (id != 0)
            g.word(c) = id;
        if (id == 0x6c484353)
            makeStreamHeader(g, c + 8);
        return c;
    };
    // Every stream's players there: a stream whose player is none writes
    // through address 0 and on.
    const auto aLiveStream = [&] {
        const x86::reg32 i = aStream();
        const x86::reg32 s = g.word(0x9f254c + 4 * (i & 0xf));
        if (s != 0 && byteAt(s + 0x16) == 0)
            byteAt(s + 0x16) = 1;
        return i;
    };
    if (name == "mul64")
    {
        cpu.eax = random32();
        cpu.edx = chance(50) ? 1000 : random32();
        cpu.esi = kSoundOut;
    }
    else if (name == "div64")
    {
        stack[0] = random32();
        stack[1] = chance(70) ? below(0x400) : random32();
        stack[2] = chance(90) ? 1 + below(0x10000) : random32();
    }
    else if (name == "findStream" || name == "SNDSTRM_destroy" || name == "SNDSTRM_purge"
             || name == "streamChunksAtOnce")
    {
        cpu.eax = chance(90) ? aStream() : x86::reg32(x86::sreg32(below(0x20)) - 8);
        cpu.edx = below(0x40);
    }
    else if (name == "findRequest" || name == "removeRequest")
    {
        cpu.eax = aHandle();
        if (name == "removeRequest")
            cpu.eax = (cpu.eax & ~0xffu) | (aStream() & 0xf);
        if (name == "removeRequest" && g.word(0x9f254c + 4 * (cpu.eax & 0xff)) == 0)
            cpu.eax = (cpu.eax & ~0xffu) | (w.streams.empty() ? 0 : w.streams[0]);
    }
    else if (name == "SNDSTRM_requeststatus")
    {
        // The rates it divides by never 0.
        for (const x86::reg32 i : w.streams)
            for (const x86::reg32 at : {0x1cu, 0x20u})
                if (g.getMemory<x86::reg16>(kStrmStreams + 0x800 * i + at) == 0)
                    g.getMemory<x86::reg16>(kStrmStreams + 0x800 * i + at) = 22050;
        cpu.eax = aHandle();
        cpu.edx = kSoundOut;
    }
    else if (name == "streamMemory")
    {
        cpu.eax = below(0x80);
        cpu.edx = below(0x40);
    }
    else if (name == "playerMemory")
        cpu.eax = below(0x40);
    else if (name == "SNDSTRM_createqueued" || name == "iSNDstreamcreate")
    {
        const x86::reg32 options = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
            byteAt(options + i) = x86::reg8(below(0x80));
        const x86::reg32 requests = chance(95) ? 1 + below(0x7f) : below(0x90);
        const x86::reg32 packets = below(0x40);
        const x86::reg32 memory = chance(97) ? kStrmMemory : 0;
        const x86::reg32 size = chance(70) ? 0x2000 + below(0x8000) : below(0x2000);
        if (name == "SNDSTRM_createqueued")
        {
            cpu.eax = 0x7600 + 4 * below(0x40);
            cpu.edx = options;
            cpu.ebx = requests;
            cpu.ecx = packets;
            stack[0] = memory;
            stack[1] = size;
        }
        else
        {
            cpu.eax = options;
            cpu.edx = requests;
            cpu.ebx = packets;
            cpu.ecx = memory;
            stack[0] = size;
            stack[1] = 0x7600 + 4 * below(0x40);
            stack[2] = chance(50) ? 1 : 0;
        }
    }
    else if (name == "SNDSTRM_requestdata" || name == "iSNDstreamrequest")
    {
        cpu.eax = aStream();
        cpu.edx = chance(30) ? 0 : below(0x400);
        cpu.ebx = below(0x10000);
        cpu.ecx = kStrmChunks + 0x40 * below(0x20);
        stack[0] = below(3);
    }
    else if (name == "packetFreed")
        cpu.eax = kStrmChunks + 0x40 * below(0x10) + 0xc;
    else if (name == "framesPlayed")
    {
        // A player's stream with a request: the frames played no more than it
        // has submitted (past them the code goes round for ever).
        const x86::reg32 player = below(0x10);
        const x86::reg32 i = w.streams[below(x86::reg32(w.streams.size()))];
        byteAt(0x9f258c + player) = x86::reg8(i);
        const x86::reg32 s = g.word(0x9f254c + 4 * i);
        if (byteAt(s + 0x16) == 0)
            byteAt(s + 0x16) = 1;
        cpu.eax = player;
        cpu.edx = below(g.word(g.word(s) + 0x1c) + 1);
    }
    else if (name == "iSNDstreamparseheader" || name == "iSNDstreamparseloop" || name == "iSNDstreamparsedata"
             || name == "iSNDstreamparseend" || name == "iSNDstreamparsechunk" || name == "streamWaits")
    {
        const x86::reg32 i = aLiveStream();
        x86::reg32 s = g.word(0x9f254c + 4 * (i & 0xf));
        if (s == 0)
            s = kStrmStreams + 0x800 * (w.streams.empty() ? 0 : w.streams[0]);
        cpu.eax = s;
        const x86::reg32 id = name == "iSNDstreamparseheader" ? 0x6c484353
                            : name == "iSNDstreamparseloop" ? 0x6c434353
                            : name == "iSNDstreamparsedata" ? 0x6c444353
                            : name == "iSNDstreamparseend" ? 0x6c454353 : 0;
        cpu.edx = aChunk(id);
    }
    else if (name == "SNDPKTPLAY_create")
    {
        cpu.eax = kStrmMemory;
        cpu.edx = 0x34 + below(0x400);
        cpu.ebx = chance(50) ? 0x4f3b44 : standInFor(0xfff330);
        cpu.ecx = chance(50) ? 0x4f3b60 : standInFor(0xfff334);
    }
    else if (name == "SNDPKTPLAY_start")
    {
        const x86::reg32 settings = kSoundOut + 0x40, options = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
        {
            byteAt(settings + i) = x86::reg8(below(0x80));
            byteAt(options + i) = x86::reg8(chance(90) ? below(0x80) : random32());
        }
        g.word(settings) = chance(50) ? 0xffff : random32();
        cpu.eax = aPlayer();
        cpu.edx = kSoundOut + 0x80;
        makeStrmHeader(g, cpu.edx);
        cpu.ebx = settings;
        cpu.ecx = options;
    }
    else if (name == "SNDPKTPLAY_submit")
    {
        cpu.eax = aPlayer();
        cpu.edx = kSoundOut + 0x80;
        g.word(cpu.edx + 4) = below(0x800);
        g.word(cpu.edx + 0xc) = aChunk(0) + 0xc;
    }
    else if (name == "SNDPKTPLAY_submitspace" || name == "framesOutstanding" || name == "SNDPKTPLAY_framesoutstanding"
             || name == "SNDPKTPLAY_stop" || name == "SNDPKTPLAY_destroy")
        cpu.eax = aPlayer();
    else if (name == "SNDPKTPLAY_purge")
    {
        cpu.eax = aPlayer();
        cpu.edx = chance(30) ? 0 : below(0x100);
        cpu.ebx = chance(30) ? 0x7fffffff : below(0x100);
    }
    else if (name == "nextPacket" || name == "packetFramesPlayed")
    {
        cpu.eax = aPlayer();
        cpu.edx = name == "nextPacket" ? kSoundOut : below(0x800);
        if (name == "packetFramesPlayed")
        {
            // Its frames callback's stream: one with a request, the frames
            // within what it submitted.
            const x86::reg32 p = g.word(0xa0b044 + 4 * cpu.eax);
            const x86::reg32 t = g.word(0x9f254c + 4 * byteAt(0x9f258c + cpu.eax));
            if (p != 0 && g.word(p + 0x20) == 0x4f3b60)
                cpu.edx = below(g.word(g.word(t) + 0x1c) + 1);
        }
    }
    else if (name == "patchDefaults")
        cpu.eax = kSoundOut;
    else if (name == "iSNDpatchtohdr")
    {
        cpu.eax = kSoundTags;
        makeStreamHeader(g, cpu.eax);
        cpu.edx = kSoundOut;
        cpu.ebx = kSoundOut + 0x20;
        cpu.ecx = kSoundOut + 0x40;
    }
    else if (name == "iSNDplatformcalcdatarate")
    {
        cpu.eax = kSoundOut;
        makeStrmHeader(g, cpu.eax);
        if (chance(5))
            g.getMemory<x86::reg16>(cpu.eax + 2) = x86::reg16(random32());
    }
    return true;
}

/* The mixer's set-ups' arguments: a channel's state and slots in the arena,
 * the sound's data and lengths made up; false for another's. */
bool makeMixSetupArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "pcmOnceMono", "pcmOnceStereo", "pcmOnceStereo2", "pcmOnceQuad", "pcmLoopedMono", "pcmLoopedStereo",
        "pcmLoopedStereo2", "pcmLoopedQuad", "pcmStreamedMono", "pcmStreamedStereo", "pcmStreamedStereo2",
        "pcmStreamedQuad", "pcmOnceSetup", "pcmLoopedSetup", "pcmStreamedSetup", "xaOnceSetup", "xaIntroSetup",
        "xaStereoStreamSetup", "packetPlayerOf", "xaStereoFileSetup", "volumeMonoSetup", "volumeStereoSetup",
        "resampleMonoSetup", "resampleStereoSetup", "resampleMonoStep", "resampleStereoStep", "pcmTablesFirst",
        "pcmTablesSecond", "xaFloatTable", "xaIntTable", "xaTables", "lastTables", "reverbStart"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    // The MMX set always: the plain set's tables call its dead code.
    g.word(0x5643b4) = 1;
    g.word(0x9f6a5c) = 0x5209a0;
    const x86::reg32 state = kSoundOut + 0x200, slots = kSoundOut + 0x300;
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(slots + 4 * i) = random32();
    if (name == "packetPlayerOf" || name == "xaStereoFileSetup")
        makeStrmWorld(g);
    cpu.eax = below(0x10);
    cpu.edx = state;
    cpu.ebx = random32();
    cpu.ecx = chance(70) ? below(5) : random32();
    stack[0] = random32();
    stack[1] = random32();
    stack[2] = slots;
    stack[3] = slots + 4;
    if (name == "pcmOnceSetup" || name == "pcmLoopedSetup")
    {
        // As the entries call them: the state in eax, the two words the slots (or
        // the frame's bytes and a slot).
        cpu.eax = state;
        stack[0] = name == "pcmOnceSetup" ? slots : below(5);
        stack[1] = slots + 4;
    }
    else if (name == "pcmStreamedSetup")
    {
        cpu.eax = state;
        cpu.edx = below(5);
        cpu.ebx = slots;
    }
    else if (name == "volumeMonoSetup" || name == "volumeStereoSetup")
    {
        stack[0] = state;
        stack[1] = slots;
        stack[2] = slots + 4;
    }
    else if (name == "resampleMonoSetup" || name == "resampleStereoSetup")
    {
        stack[0] = state;
        stack[1] = slots;
        stack[2] = slots + 4;
        stack[3] = slots + 8;
    }
    else if (name == "resampleMonoStep" || name == "resampleStereoStep")
    {
        static const x86::reg32 steps[] = {0x8000, 0x10000, 0x18000, 0x10000, 0xffff, 0x10001};
        for (x86::reg32 at = state; at < state + 0x24; at += 4)
            g.word(at) = random32();
        g.word(state + 8) = chance(90) ? steps[below(6)] : random32();
        for (const x86::reg32 at : {0x18u, 0x1cu, 0x20u})
            g.word(state + at) = slots + 4 * below(6);
        stack[0] = state;
        stack[1] = chance(90) ? steps[below(6)] : random32();
    }
    return true;
}

/* The mixer's own functions (native_snd_mixfuncs.cpp): a channel's state
 * (a resampler's: its frame, fraction, step, kept frames and flags), its
 * slots, a source of random frames with room before it for the kept ones,
 * a target; the arguments as the mixer hands them.  False for another's. */
bool makeMixFuncArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
"bufferPosition", "panSides", "volumeMonoPair", "volumeMonoLevels", "volumeStereoPair", "volumeStereoLevels", "volumeMonoLevelsMmx", "volumeStereoLevelsMmx", "resample8MonoSetup", "resample8MonoStep", "resample8MonoNeededDown", "resample8MonoNeededSame", "resample8MonoNeededUp", "resample8MonoSame", "resample8MonoDown", "resample8MonoUp", "resample8StereoSetup", "resample8StereoStep", "resample8StereoNeededDown", "resample8StereoNeededSame", "resample8StereoNeededUp", "resample8StereoSame", "resample8StereoDown", "resample8StereoUp", "resample16MonoNeededDown", "resample16MonoNeededSame", "resample16MonoNeededUp", "resample16MonoSame", "resample16MonoDown", "resample16MonoUp", "resample16StereoNeededDown", "resample16StereoNeededSame", "resample16StereoNeededUp", "resample16StereoSame", "resample16StereoDown", "resample16StereoUp",
"pcmPlayed", "pcmOnceDecode", "pcmLoopedDecode", "pcmStreamedDecode", "pcmFileDecode", "pcmFileSetup", "pcmFileMono", "pcmFileStereo", "pcmFileStereo2", "pcmFileQuad",
"xaPlayed", "xaOnceDecode", "xaKeptCopy", "xaLoopDecode",
"xaIntroDecode", "xaStreamDecode", "xaStreamSetup",
"xaPacketDecode", "xaPacketSetup",
"xaStereoPlayed", "xaStereoOnceDecode", "xaStereoOnceSetup", "xaStereoKeptCopy",
"xaStereoLoopDecode", "xaStereoIntroDecode", "xaStereoIntroSetup",
"xaStereoStreamDecode", "xaStereoPacketDecode",
"framesPlayedCoded", "codedToWords", "codedDecode", "codedSetup", "codedStreamDecode", "codedStreamSetup", "codedPacketDecode", "codedPacketSetup", "codedBits", "codedSkip", "codedPulses", "codedInterpolate", "codedFilter", "codedSynthesis", "codedStart", "codedFrame",
"convert16", "convertToWords", "convertXaStereo", "convert8", "convertXaMono",
        "MIXFUNCS NAMES"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    g.word(0x5643b4) = 1;
    const x86::reg32 state = kSoundOut + 0x200, slots = kSoundOut + 0x300, source = kSoundOut + 0x480,
                     target = kSoundOut + 0x800;
    for (x86::reg32 at = kSoundOut + 0x200; at < kSoundOut + 0xc00; at += 4)
        g.word(at) = random32();
    static const x86::reg32 steps[] = {0x8000, 0x10000, 0x18000, 0x10000, 0xffff, 0x10001, 0x5555, 0x1c000};
    const auto aStep = [] { return chance(90) ? steps[below(8)] : 0x1000 + below(0x1f000); };
    g.word(state) = below(8);
    g.word(state + 4) = chance(90) ? below(0x10000) : random32();
    g.word(state + 8) = aStep();
    for (const x86::reg32 flag : {0xdu, 0xeu, 0xfu, 0x10u, 0x11u, 0x12u, 0x14u, 0x15u, 0x16u})
        if (chance(70))
            g.getMemory<x86::reg8>(state + flag) = x86::reg8(chance(60) ? below(2) : below(4) - 2);
    for (const x86::reg32 at : {0x14u, 0x18u, 0x1cu})
        g.word(state + at) = slots + 4 * below(6);
    g.word(slots + 0x20) = target;
    const auto level = [] { return chance(80) ? below(0x80) : random32(); };
    const auto wanted = [] { return chance(90) ? below(0x40) : x86::reg32(-x86::sreg32(below(3))); };
    if (name.rfind("pcm", 0) == 0)
    {
        cpu.eax = state;
        cpu.edx = wanted();
        cpu.ebx = target;
        if (name == "pcmPlayed")
            return true;
        if (name == "pcmOnceDecode")
        {
            g.word(state) = source;
            g.word(state + 4) = below(0x30);
            g.word(state + 8) = below(0x30);
            g.word(state + 0xc) = below(3);
            cpu.edx = below(0x30);
        }
        else if (name == "pcmLoopedDecode")
        {
            const x86::reg32 last = 1 + below(0x20);
            g.word(state) = source;
            g.word(state + 4) = below(last + 1);
            g.word(state + 8) = below(last + 1);
            g.word(state + 0xc) = last;
            g.word(state + 0x10) = below(3);
        }
        else if (name == "pcmStreamedDecode")
        {
            g.word(state) = chance(90) ? source : 0;
            g.word(state + 4) = 1 + below(0x20);
            g.word(state + 8) = below(g.word(state + 4) + 2);
            g.word(state + 0xc) = below(3);
            g.word(0x5678b4) = standInFor(0xfff320);
        }
        else
        {
            // A packet player's packets, each a frame long at least.
            makeStrmWorld(g);
            for (x86::reg32 i = 0; i < 0x10; ++i)
            {
                const x86::reg32 p = g.word(0xa0b044 + 4 * i);
                if (p != 0)
                    for (x86::reg32 k = 0; k < g.getMemory<x86::reg16>(p + 8); ++k)
                        g.word(p + 0x28 + 0xc * k + 4) = 1 + below(0x7ff);
            }
            g.word(state) = source;
            g.word(state + 4) = 1 + below(0x20);
            g.word(state + 8) = below(g.word(state + 4) + 2);
            g.word(state + 0xc) = 0;
            g.getMemory<x86::reg16>(state + 0x10) = x86::reg16(below(3));
            g.getMemory<x86::reg16>(state + 0x12) = x86::reg16(chance(50) ? 0 : below(0x40));
            if (name != "pcmFileDecode")
            {
                cpu.eax = chance(80) ? aSoundHandle(g) : random32();
                cpu.edx = state;
                cpu.ebx = below(5);
                cpu.ecx = slots;
                stack[2] = slots;
                stack[3] = slots + 4;
            }
        }
        return true;
    }
    if (name.rfind("convert", 0) == 0)
    {
        // iSNDconvertsample's: 16- and 8-bit samples, stereo floats, XA's
        // state with its history (floats of a sound's size) and data.
        const x86::reg32 xs = kSoundArena + 0xd000, data = kSoundArena + 0x9000;
        for (x86::reg32 at = data; at < data + 0x1000; at += 4)
            g.word(at) = random32();
        const auto aFloat = [](float range) { return range * (float(below(0x10000)) / 32768.0f - 1.0f); };
        if (name == "convertToWords")
            for (x86::reg32 at = source; at < source + 0x200; at += 4)
                g.getMemory<float>(at) = chance(90) ? aFloat(40000.0f) : aFloat(1e7f);
        const x86::reg32 count = chance(90) ? below(0x40) : x86::reg32(-x86::sreg32(below(3)));
        stack[0] = count;
        stack[1] = source;
        stack[2] = target;
        if (name == "convertXaStereo" || name == "convertXaMono")
        {
            g.word(xs) = chance(90) ? 0x1c * below(4) : x86::reg32(-x86::sreg32(below(3)));
            for (x86::reg32 at = xs + 4; at < xs + 0x14; at += 4)
                g.getMemory<float>(at) = aFloat(30000.0f);
            g.word(xs + (name == "convertXaStereo" ? 0x14 : 0xc)) = data + below(0x100);
            g.word(xs + (name == "convertXaStereo" ? 0x18 : 0x10)) = target - 0x400;
            stack[0] = xs;
        }
        return true;
    }
    if (name.rfind("coded", 0) == 0 || name == "framesPlayedCoded")
    {
        // A frame-coded sound's state of its own (0xd58 bytes): the bit
        // reader on random data, the header's scales, the coefficients, the
        // filter's ring, the excitation -- floats of a sound's size.
        const x86::reg32 cs = kSoundArena + 0xd000, data = kSoundArena + 0x9000;
        for (x86::reg32 at = data; at < data + 0x1000; at += 4)
            g.word(at) = random32();
        const auto aFloat = [](float range) { return range * (float(below(0x10000)) / 32768.0f - 1.0f); };
        for (x86::reg32 at = cs; at < cs + 0xd60; at += 4)
            g.getMemory<float>(at) = aFloat(1000.0f);
        for (x86::reg32 at = cs + 0x114; at < cs + 0x144; at += 4)
            g.getMemory<float>(at) = aFloat(0.9f);
        for (x86::reg32 at = cs + 0x14; at < cs + 0x114; at += 4)
            g.getMemory<float>(at) = 1.0f + aFloat(0.5f) + 0.5f;
        g.word(cs) = data + below(0x100);
        g.word(cs + 4) = random32();
        g.word(cs + 8) = 8 + below(24);
        g.word(cs + 0xc) = below(2);
        g.word(cs + 0x10) = below(0x40);
        g.word(0x9f6b24) = standInFor(0xfff30c);
        g.word(0x5678b4) = standInFor(0xfff320);
        cpu.eax = cs;
        cpu.edx = wanted();
        cpu.ebx = target;
        if (name == "codedDecode")
        {
            g.word(cs + 0xd44) = 1 + below(0x400);
            g.word(cs + 0xd48) = below(0x1b1);
            g.word(cs + 0xd4c) = below(g.word(cs + 0xd44) + 0x10);
        }
        else if (name == "codedStreamDecode")
        {
            g.word(cs + 0xd44) = chance(10) ? 0 : data + below(0x100);
            g.word(cs + 0xd48) = 1 + below(0x200);
            g.word(cs + 0xd4c) = below(g.word(cs + 0xd48) + 2);
            g.word(cs + 0xd50) = below(0x1b1);
        }
        else if (name == "codedPacketDecode" || name == "codedPacketSetup")
        {
            makeStrmWorld(g);
            for (x86::reg32 i = 0; i < 0x10; ++i)
            {
                const x86::reg32 p = g.word(0xa0b044 + 4 * i);
                if (p != 0)
                    for (x86::reg32 k = 0; k < g.getMemory<x86::reg16>(p + 8); ++k)
                        g.word(p + 0x28 + 0xc * k + 4) = 1 + below(0x7ff);
            }
            g.word(cs + 0xd44) = data + below(0x100);
            g.word(cs + 0xd48) = 1 + below(0x200);
            g.word(cs + 0xd4c) = 0;
            g.word(cs + 0xd50) = chance(50) ? 0 : below(0x40);
            g.getMemory<x86::reg16>(cs + 0xd54) = x86::reg16(below(g.word(cs + 0xd48) + 2));
            g.getMemory<x86::reg16>(cs + 0xd56) = x86::reg16(below(0x1b1));
        }
        if (name == "codedSetup" || name == "codedStreamSetup" || name == "codedPacketSetup")
        {
            cpu.eax = chance(80) ? aSoundHandle(g) : random32();
            cpu.ebx = data + below(0x100);
            cpu.ecx = 1 + below(0x400);
            cpu.edx = cs;
            stack[2] = slots;
            stack[3] = slots + 4;
        }
        else if (name == "codedStart")
        {
            cpu.eax = data + below(0x100);
            cpu.edx = cs;
        }
        else if (name == "codedFrame")
            cpu.edx = below(2);
        else if (name == "codedSynthesis")
        {
            const x86::reg32 blocks = 1 + below(36);
            cpu.edx = 12 * below(37 - blocks);
            cpu.ebx = blocks;
            cpu.ecx = below(2);
        }
        else if (name == "codedFilter")
        {
            cpu.eax = cs + 0x114;
            cpu.edx = slots;
        }
        else if (name == "codedInterpolate")
            cpu.eax = cs + 0x700 + 4 * below(2);
        else if (name == "codedPulses")
        {
            cpu.edx = below(2);
            cpu.ebx = cs + 0x684;
            cpu.ecx = 1 + below(2);
        }
        else if (name == "codedBits" || name == "codedSkip")
            cpu.edx = 1 + below(0x10);
        else if (name == "codedToWords")
        {
            cpu.eax = cs + 0x684;
            cpu.edx = target;
            cpu.ebx = chance(90) ? below(0x40) : x86::reg32(-x86::sreg32(below(3)));
            for (x86::reg32 at = cs + 0x684; at < cs + 0x784; at += 4)
                g.word(at) = chance(50) ? below(0x20000) : random32();
        }
        return true;
    }
    if (name.rfind("xa", 0) == 0)
    {
        // An XA sound's: its data, frame and length, the frames it keeps (a
        // block's at most), the loop's start inside it.
        const x86::reg32 length = 0x1c + below(0x1e4);
        g.word(state + 0x10) = source;
        g.word(state + 0x14) = chance(80) ? 1 + below(0x200) : below(0x200);
        g.word(state + 0x18) = below(length);
        g.word(state + 0x1c) = below(length);
        g.word(state + 0x20) = length;
        g.getMemory<x86::reg16>(state + 0x1c) = x86::reg16(below(0x1c));
        if (name == "xaLoopDecode")
        {
            // Its loop two blocks from the end at least, as a sound's is.
            g.word(state + 0x20) = 0x38 + below(0x1c8);
            g.word(state + 0x18) = below(g.word(state + 0x20));
            g.word(state + 0x1c) = below(g.word(state + 0x20) - 0x37);
            g.getMemory<x86::reg16>(state + 0x24) = x86::reg16(below(0x1c));
        }
        if (name == "xaIntroDecode")
        {
            const x86::reg32 length = 0x38 + below(0x1c8), loop = below(length - 0x37);
            g.word(state + 0x20) = length;
            g.word(state + 0x1c) = loop;
            g.word(state + 0x18) = below(loop + 0x1c);
            g.getMemory<x86::reg16>(state + 0x24) = x86::reg16(below(0x1c));
            g.word(state + 0x98) = slots + 0x24;
        }
        else if (name == "xaPacketDecode" || name == "xaPacketSetup")
        {
            // Player 0's packets, each a frame long at least.
            makeStrmWorld(g);
            for (x86::reg32 i = 0; i < 0x10; ++i)
            {
                const x86::reg32 p = g.word(0xa0b044 + 4 * i);
                if (p != 0)
                    for (x86::reg32 k = 0; k < g.getMemory<x86::reg16>(p + 8); ++k)
                        g.word(p + 0x28 + 0xc * k + 4) = 1 + below(0x7ff);
            }
            g.word(state + 0x10) = source;
            g.word(state + 0x14) = 1 + below(0x80);
            g.word(state + 0x18) = below(g.word(state + 0x14) + 2);
            g.word(state + 0x1c) = 0;
            g.word(state + 0x20) = chance(50) ? 0 : below(0x40);
            g.getMemory<x86::reg16>(state + 0x24) = x86::reg16(below(0x1c));
        }
        else if (name == "xaStreamDecode" || name == "xaStreamSetup")
        {
            g.word(state + 0x10) = chance(10) ? 0 : chance(10) ? 1 : source;
            g.word(state + 0x14) = 1 + below(0x80);
            g.word(state + 0x18) = below(g.word(state + 0x14) + 2);
            g.word(0x5678b4) = standInFor(0xfff320);
        }
        if (name.rfind("xaStereo", 0) == 0)
        {
            // Stereo's: where at +0x10, the data, length and frame after it,
            // the samples it keeps (two a frame, a block's at most) at +0x20.
            g.word(state + 0x14) = source;
            g.word(state + 0x18) = chance(80) ? 1 + below(0x200) : below(0x200);
            g.word(state + 0x1c) = below(0x200);
            g.getMemory<x86::reg16>(state + 0x20) = x86::reg16(2 * below(0x1c));
        }
        if (name == "xaStereoStreamDecode")
        {
            g.word(state + 0x14) = chance(10) ? 0 : chance(10) ? 1 : source;
            g.word(state + 0x18) = 1 + below(0x80);
            g.word(state + 0x1c) = below(g.word(state + 0x18) + 2);
            g.word(state + 0x20) = below(0x1c);
            g.word(0x5678b4) = standInFor(0xfff320);
        }
        if (name == "xaStereoPacketDecode")
        {
            makeStrmWorld(g);
            for (x86::reg32 i = 0; i < 0x10; ++i)
            {
                const x86::reg32 p = g.word(0xa0b044 + 4 * i);
                if (p != 0)
                    for (x86::reg32 k = 0; k < g.getMemory<x86::reg16>(p + 8); ++k)
                        g.word(p + 0x28 + 0xc * k + 4) = 1 + below(0x7ff);
            }
            g.word(state + 0x14) = source;
            g.word(state + 0x18) = 1 + below(0x80);
            g.word(state + 0x1c) = below(g.word(state + 0x18) + 2);
            g.word(state + 0x20) = below(0x1c);
            g.word(state + 0x24) = 0;
            g.word(state + 0x28) = chance(50) ? 0 : below(0x40);
        }
        if (name == "xaStereoLoopDecode" || name == "xaStereoIntroDecode")
        {
            const x86::reg32 length = 0x38 + below(0x1c8), loop = below(length - 0x37);
            g.word(state + 0x24) = length;
            g.word(state + 0x20) = loop;
            g.word(state + 0x1c) = name == "xaStereoLoopDecode" ? below(length) : below(loop + 0x1c);
            g.getMemory<x86::reg16>(state + 0x28) = x86::reg16(below(0x1c));
            g.word(state + 0x110) = slots + 0x24;
        }
        cpu.eax = state;
        cpu.edx = wanted();
        cpu.ebx = target;
        if (name == "xaPacketSetup")
        {
            cpu.eax = chance(80) ? aSoundHandle(g) : random32();
            cpu.edx = state;
            cpu.ecx = random32();
            stack[2] = slots;
            stack[3] = slots + 4;
        }
        if (name == "xaStreamSetup")
        {
            cpu.edx = state;
            cpu.ecx = random32();
            stack[2] = slots;
            stack[3] = slots + 4;
        }
        if (name == "xaStereoIntroSetup")
        {
            cpu.edx = state;
            cpu.ebx = source;
            cpu.ecx = random32();
            stack[0] = below(0x200);
            stack[1] = below(0x200);
            stack[2] = slots;
            stack[3] = slots + 4;
        }
        if (name == "xaStereoOnceSetup")
        {
            cpu.edx = state;
            cpu.ebx = source;
            cpu.ecx = random32();
            stack[2] = slots;
            stack[3] = slots + 4;
        }
        if (name == "xaStereoKeptCopy")
        {
            cpu.eax = below(0x1c);
            cpu.edx = state + 0x24;
            cpu.ebx = below(0x40);
            cpu.ecx = slots + 0x20;
        }
        if (name == "xaKeptCopy")
        {
            cpu.eax = below(0x1c);
            cpu.edx = state + 0x26;
            cpu.ebx = below(0x40);
            cpu.ecx = slots + 0x20;
        }
        return true;
    }
    stack[0] = state;
    if (name.find("Setup") != std::string::npos)
    {
        stack[1] = slots;
        stack[2] = slots + 4;
        stack[3] = slots + 8;
    }
    else if (name.find("Pair") != std::string::npos)
    {
        stack[1] = slots;
        stack[2] = slots + 4;
    }
    else if (name.find("Levels") != std::string::npos)
    {
        stack[1] = level();
        stack[2] = level();
    }
    else if (name.find("Step") != std::string::npos)
        stack[1] = aStep();
    else if (name.find("Needed") != std::string::npos)
        stack[1] = chance(90) ? 1 + below(0x40) : random32() % 0x200;
    else if (name == "panSides" || name == "bufferPosition")
    {
        cpu.eax = chance(80) ? below(0x10000) : random32();
        cpu.edx = name == "panSides" ? slots : (chance(80) ? below(0x10000) : random32());
        cpu.ebx = name == "panSides" ? slots + 4 : slots + 0x10;
    }
    else
    {
        // A block: up to 0x30 frames out, at most 0x30 * 1.75 + 2 in.
        stack[1] = 1 + below(0x30);
        stack[2] = source;
        stack[3] = slots + 0x20;
    }
    return true;
}

/* The game's own sound's functions (native_snd_music.cpp,
 * native_snd_effects.cpp): its globals made up as the decompiled functions'
 * are, those it indexes with kept in their tables; its slots and banks; the
 * arguments as its callers hand them.  False for another's. */
bool makeGameSoundArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "soundExit", "deleteMusicCopy", "raceTuneOf", "raceMusicPrepare", "musicStreamMake", "musicStreamMakeOf",
        "musicAfterSetting", "musicMenuSix", "musicStart", "raceMusicStart", "musicStop", "musicStreamEnd",
        "banksFree", "banksRemove", "bankLoad", "slotStop", "slotEffect", "slotPlay", "playMenuEffect",
        "playCarEffectFive", "playEffect", "playSpeechEffect", "panFromSide", "masterSilent", "masterBack",
        "silenceForMenus", "silenceForRace", "busInit", "busUp", "busDown", "slotsStop", "musicMuteToggle",
        "SNDangle", "speechInit", "speechFree", "speechLine", "scenerySounds", "raceBanksLoad", "raceAnnouncer", "trackSounds", "coDriverTick", "carEngine", "copCarSound", "playerCarSound", "copSourcesPick", "raceSoundTick", "zoneSound", "voiceBankLoad", "carBankLoad", "placeAhead", "placeAcross", "carRadio", "playerCopRadio", "copLineFor", "copRemove", "carFlagTest", "raceValue", "soundNothing", "slotsEmpty", "raceBankLoad", "raceSoundInit", "raceSoundEnd", "sourceReset", "sourcesReset", "copChaseSet", "copSiren", "copSirenStop", "copEngine", "copEngineStop", "copDistance", "copsCloseness", "listenerMove", "sourceDistance", "sourceAngle", "carAngle", "copBeepTick", "copBeepStart", "copEffect", "musicEventResume", "chaseLevel", "descriptionLoad", "descriptionSpeak", "descriptionTick", "descriptionStop", "spokenStatus", "descriptionStart", "descriptionService", "raceVoiceLoad", "carLineSpeak", "spokenStop", "raceVoiceFree", "speechTick", "radioTick", "radioStart", "speechSaid", "copRadio", "queueSpeechLine", "queueRaceLine", "raceEventLine", "gapLine", "lapTimeLine", "engineSoundsStart", "farEffectAim", "farEffectPlay", "farEffectTick", "crowdEffect", "carEffectFifteen", "crashPitch", "crashEffect", "scrapeEffect", "carKnock", "noiseByDistance", "playerNoise", "playerNoiseStop", "sirenIsOn", "sirenFirstTone", "sirenSecondTone", "sirenSteadyTone", "sirenFirstDone", "sirenSecondDone", "sirenStart", "sirenStop", "sirenTick", "noiseBySpeed"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    auto value = [] {
        const x86::reg32 kind = below(100);
        return kind < 25 ? 0 : kind < 35 ? 1 : kind < 45 ? 0xffffffff : kind < 60 ? below(16)
             : kind < 70 ? below(0x100) : kind < 75 ? 0x80000000 | below(16) : random32();
    };
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    // The game's flags, modes and volumes.
    const std::pair<x86::reg32, x86::reg32> ranges[] = {
        {0x552580, 0x552a00}, {0x559230, 0x559240}, {0x6fbb40, 0x6fbc10}, {0x6fd3b0, 0x6fd4b0}, {0x55e88c, 0x55e890}};
    for (const auto& range : ranges)
        for (x86::reg32 at = range.first; at < range.second; at += 4)
            g.word(at) = value();
    for (const x86::reg32 at : {0x6fbbf0u, 0x6fbbf4u, 0x6fbbf8u, 0x6fbbfcu, 0x6fbbe8u})
        g.word(at) = chance(90) ? below(0x80) : value();
    for (x86::reg32 at = 0x5525d0; at < 0x5525f8; at += 4)
        g.word(at) = chance(90) ? below(0x80) : value();
    byteAt(0x55eb2e) = x86::reg8(chance(70) ? 0 : random32());
    byteAt(0x55eb2f) = x86::reg8(chance(70) ? 0 : random32());
    g.word(0x6fd4ac) = below(8);
    g.word(0x5525f8) = below(10);
    // The jump tables its code dispatches by, in the code segment (which the
    // harness does not load): nfs3.exe's words.
    static const std::pair<x86::reg32, std::vector<x86::reg32>> tables[] = {
        {0x40ffa4, {0x40ffe9, 0x40ffe9, 0x40ffef, 0x40ffef, 0x40fff8, 0x40fff8, 0x410001, 0x410001, 0x41000a,
                    0x41000a}},
        {0x417040, {0x417114, 0x41711b, 0x417106, 0x41711b, 0x41711b, 0x41711b, 0x41711b, 0x41711b, 0x41711b,
                    0x41711b, 0x41710d, 0x41710d, 0x4170fa}},
        {0x4e8f71, {0x4e8f98, 0x4e8f91, 0x4e8f9b, 0x4e8fa5, 0x4e8fad, 0x4e8fb2, 0x4e8fba, 0x4e8fc2}},
        {0x4149ac, {0x414ac0, 0x414d50, 0x414bf0, 0x414d3e}},
        {0x4149bc, {0x414d50, 0x414d55, 0x414d35, 0x414d55, 0x414cd7, 0x414d55, 0x414d55, 0x414d08}},
        {0x4c9874, {0x4c98b7, 0x4c98be, 0x4c98c5, 0x4c98cc, 0x4c98d3, 0x4c98b7}},
        {0x417348, {0x417591, 0x41764c, 0x41764c, 0x41764c, 0x41764c, 0x4175c7, 0x41764c, 0x41764c, 0x417591,
                    0x417591, 0x4175ae, 0x417591, 0x41764c, 0x41764c, 0x4175c7, 0x4175c7}},
        {0x412d14, {0x413435, 0x41344c, 0x41345c, 0x41346c, 0x41347c, 0x41347c, 0x41347c, 0x41347c}},
        {0x412d34, {0x4134c3, 0x413492, 0x4134a9, 0x4134ba, 0x4134b2, 0x4134b2, 0x4134b2, 0x4134c7}},
    };
    for (const auto& table : tables)
        for (x86::reg32 i = 0; i < table.second.size(); ++i)
            g.word(table.first + 4 * i) = table.second[i];
    // The sirens: on, their tone, their tones' ticks and the ticks gone.
    for (x86::reg32 i = 0; i < 5; ++i)
    {
        g.word(0x552d90 + 4 * i) = below(2);
        g.word(0x552da4 + 4 * i) = below(2);
        g.word(0x552db8 + 4 * i) = below(0x10);
        g.word(0x552dcc + 4 * i) = chance(20) ? 0xffffffff : below(0x10);
        g.word(0x552de0 + 4 * i) = below(0x10);
    }
    g.word(0x570e68) = chance(40) ? 0xffffffff : aSoundHandle(g);
    // The tunes' names: strings of the arena's.
    for (x86::reg32 i = 0; i < 10; ++i)
        g.word(0x5525a8 + 4 * i) = kSoundOut + 0x40 * i;
    // The slots (0x33 of them), their banks' indexes, the banks' handles.
    for (x86::reg32 s = 0; s < 0x33; ++s)
    {
        g.word(0x570de8 + 8 * s) = chance(40) ? 0xffffffff : aSoundHandle(g);
        g.word(0x570dec + 8 * s) = chance(30) ? 0xffffffff : below(0x10);
        byteAt(0x552798 + 4 * s) = x86::reg8(below(0x17));
    }
    for (x86::reg32 at = 0x571124; at < 0x571240; at += 4)
        g.word(at) = chance(10) ? 0 : chance(50) ? kSoundBanks + 0x100 * below(0x10) : random32() & 0xfffff;
    // A bank's handle, one of those the effects compare with mostly.
    const auto aBank = [&] { return chance(60) ? g.word(0x571124 + 12 * below(0x17)) : random32() & 0xfffff; };
    g.word(0x571118) = chance(80) ? 6 + below(2) + (chance(50) ? 0xa : 0) : value();
    g.word(0x552934) = chance(60) ? 0xffffffff : chance(50) ? below(3) : value();
    g.word(0x6fd4cc) = below(2);
    for (x86::reg32 s = 0; s < 0x40; ++s)
        byteAt(0x571244 + s) = x86::reg8(below(0x80));
    // The player's car: its place, floats of a track's size.
    g.word(0x6fd4f4) = below(8);
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x5efa48 + 4 * i) = kSoundOut + 0x800 + 0x100 * i;
    for (x86::reg32 i = 0; i < 8; ++i)
        for (const x86::reg32 at : {0x98u, 0x9cu, 0xa0u})
        {
            const float f = float(x86::sreg32(below(0x2000000)) - 0x1000000) / 16.0f;
            std::memcpy(&g.word(kSoundOut + 0x800 + 0x100 * i + at), &f, 4);
        }
    // The speech's state: each player's lines, queues, radio and the
    // description's.
    for (x86::reg32 at = 0x7dd330; at < 0x7dd860; at += 4)
        g.word(at) = below(2);
    for (const x86::reg32 at : {0x7dd350u, 0x7dd354u, 0x7dd370u, 0x7dd374u, 0x7dd390u, 0x7dd394u, 0x7dd82cu})
        g.word(at) = chance(80) ? aSoundHandle(g) : value();
    g.word(0x7dd378) = below(8);
    g.word(0x7dd37c) = below(8);
    g.word(0x7dd358) = chance(50) ? 0 : below(6);
    g.word(0x7dd35c) = chance(50) ? 0 : below(6);
    g.word(0x7dd834) = below(0x10);
    g.word(0x7dd83c) = chance(80) ? 0x32 + below(3) : value();
    g.word(0x7dd844) = below(24);  // a bank handle: SND's index
    g.word(0x7dd84c) = chance(50) ? 0 : kSoundOut + 0x40 * below(0x10);
    for (x86::reg32 at = 0x7dd398; at < 0x7dd818; at += 4)
        g.word(at) = random32();
    // The queued lines: a player and a bank each, as lines have them.
    for (x86::reg32 at = 0x7dd398; at + 0x24 <= 0x7dd818; at += 0x24)
    {
        g.word(at + 0x10) = chance(90) ? below(24) : random32();
        g.word(at + 0x14) = below(2);
        g.word(at + 0x18) = below(6);
    }
    g.word(0x560ac4) = below(10);
    g.word(0x560ac8) = 0x10 + below(0x14);
    g.word(0x560af8) = below(2);
    g.word(0x7d3684) = chance(80) ? below(0x400) : value();
    g.word(0x6fd3a0) = chance(80) ? 0 : value();
    // The strings the descriptions' and voices' names are made of: the
    // folders, the tables' names, what a file's name comes back as.
    const auto aString = [&](x86::reg32 at, x86::reg32 length) {
        for (x86::reg32 i = 0; i < length; ++i)
            byteAt(at + i) = x86::reg8('a' + below(26));
        byteAt(at + length) = 0;
    };
    for (const x86::reg32 at : {0x7a28b4u, 0x7a2b34u, 0x7a2bb4u, 0x7a2c34u, 0x7a2cb4u, 0x7a2d34u})
        aString(at, below(0x18));
    for (x86::reg32 i = 0; i < 7; ++i)
    {
        g.word(0x560afc + 4 * i) = kSoundOut + 0x1800 + 0x20 * i;
        g.word(0x560b18 + 4 * i) = kSoundOut + 0x1900 + 0x20 * i;
        aString(kSoundOut + 0x1800 + 0x20 * i, below(0x10));
        aString(kSoundOut + 0x1900 + 0x20 * i, below(0x10));
    }
    for (x86::reg32 i = 0; i < 4; ++i)
    {
        g.word(0x560b50 + 4 * i) = kSoundOut + 0x1a00 + 0x20 * i;
        aString(kSoundOut + 0x1a00 + 0x20 * i, below(0x10));
    }
    for (x86::reg32 at = 0; at < 0x100; at += 0x10)
        aString(at, below(0xc));
    for (x86::reg32 at = 0x7700; at < 0x7800; at += 0x10)
        aString(at, below(0xc));
    // The cars: their places in the race.
    g.word(0x5efda0) = below(8);
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        const x86::reg32 car = kSoundOut + 0x1c00 + 0x300 * i;
        g.word(0x5efc48 + 4 * i) = car;
        g.word(car + 8) = below(2);
        byteAt(car + 0x200) = x86::reg8(below(2));
        g.word(car + 0x2bc) = below(2);
        g.word(car + 0x2c4) = below(5);
    }
    // The chase: each player's level and beeps, the music's level.
    for (x86::reg32 i = 0; i < 2; ++i)
    {
        g.word(0x552844 + 4 * i) = below(6);
        g.word(0x55283c + 4 * i) = below(4);
        g.word(0x571110 + 4 * i) = chance(80) ? aSoundHandle(g) : value();
    }
    static const x86::reg32 musicLevels[] = {0xffffffff, 0, 0x64};
    g.word(0x552838) = chance(90) ? musicLevels[below(3)] : value();
    g.word(0x55284c) = below(2);
    g.word(0x552910) = chance(80) ? 1 : 0;
    g.word(0x552914) = chance(70) ? 1 : 0;
    g.word(0x6fbb54) = chance(80) ? 0 : 1;
    g.word(0x6fbbf0) = chance(80) ? 1 + below(0x7f) : 0;
    byteAt(0x552590) = x86::reg8(chance(80) ? 0 : 1);
    // Places and a listener's axes: floats of a track's size and unit axes.
    const auto aFloat = [&](x86::reg32 at, float range) {
        const float f = (float(below(0x10000)) / 32768.0f - 1.0f) * range;
        std::memcpy(&g.word(at), &f, 4);
    };
    for (x86::reg32 at = kSoundOut + 0x2000; at < kSoundOut + 0x2400; at += 4)
        aFloat(at, chance(80) ? 4000.0f : 1.0f);
    for (x86::reg32 i = 0; i < 4; ++i)
        for (x86::reg32 k = 0; k < 3; ++k)
            aFloat(0x570a60 + 12 * i + 4 * k, 4000.0f);
    // The cop cars' sources: a car each mostly (of the cars above), its model
    // (+0x220's +0x14) and flags; the players' sources.
    g.word(0x5efda4) = below(9);
    for (x86::reg32 i = 0; i < 8; ++i)
    {
        const x86::reg32 car = kSoundOut + 0x800 + 0x100 * i, model = kSoundOut + 0x1600 + 0x20 * i;
        g.word(car + 0x220) = model;
        g.word(model + 0x14) = 0x32 + below(0x16);
        byteAt(car + 0x200) = x86::reg8(random32());
    }
    for (x86::reg32 i = 0; i < 4; ++i)
    {
        const x86::reg32 s = 0x570b78 + 0x38 * i;
        for (x86::reg32 at = s; at < s + 0x38; at += 4)
            g.word(at) = value();
        g.word(s) = chance(80) ? kSoundOut + 0x800 + 0x100 * below(8) : 0;
    }
    for (x86::reg32 at = 0x570ad8; at < 0x570b78; at += 4)
        g.word(at) = value();
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x552744 + 4 * i) = random32();
    for (x86::reg32 i = 0; i < 0x20; ++i)
        byteAt(0x55276c + i) = x86::reg8(random32());
    // A car whose radio speaks: its place, its player (+0x624, itself here)
    // and the player's side (+0x1f0).
    {
        const x86::reg32 car = kSoundOut + 0x3400;
        for (const x86::reg32 at : {0x98u, 0x9cu, 0xa0u, 0xa4u, 0xa8u, 0xacu})
            aFloat(car + at, 4000.0f);
        g.word(car + 0x624) = car;
        g.word(car + 0x1f0) = below(2);
    }
    g.word(0x6fd4b4) = 1 + below(8);
    for (x86::reg32 at = 0x552864; at < 0x552904; at += 4)
        g.word(at) = random32();
    if (name == "carRadio" || name == "playerCopRadio")
    {
        cpu.eax = kSoundOut + 0x3400;
        cpu.ebx = below(5);
    }
    else if (name == "placeAhead" || name == "placeAcross")
    {
        cpu.eax = kSoundOut + 0x2000 + 4 * below(0x40);
        cpu.edx = chance(30) ? 0 : kSoundOut + 0x2000 + 4 * below(0x40);
        g.word(0x570dcc) = chance(50) ? 0 : kSoundOut + 0x2000 + 4 * below(0x40);
        if (name == "placeAcross")
        {
            cpu.edx = kSoundOut + 0x2800;
            for (x86::reg32 k = 0; k < 3; ++k)
                g.word(cpu.edx + 4 * k) = x86::reg32(x86::sreg32(below(0x2000000)) - 0x1000000);
            cpu.ebx = kSoundOut + 0x2900;
        }
        if (chance(50))
            cpu.fpu.setControl(0x7f);
    }
    else if (name == "voiceBankLoad" || name == "carBankLoad")
    {
        // The speakers' and the units' names, in the code segment.
        for (x86::reg32 k = 0; k < 0xc; ++k)
            g.word(0x412920 + 4 * k) = 0x536980 + 4 * k;
        for (x86::reg32 k = 0; k < 7; ++k)
            g.word(0x412950 + 4 * k) = k < 5 ? 0x5369b0 + 4 * k : 0x5369b0;
        cpu.eax = kSoundOut + 0x1b00;
        aString(cpu.eax, below(0x20));
        cpu.edx = name == "carBankLoad" ? below(3) : chance(20) ? 0x63 : below(0xc);
        cpu.ebx = below(0x17);
    }
    else if (name == "copSourcesPick" || name == "raceSoundTick")
    {
        // The cars on the road: the speech's cars, placed about the listener.
        g.word(0x5efd9c) = below(9);
        for (x86::reg32 i = 0; i < 8; ++i)
        {
            const x86::reg32 c = kSoundOut + 0x1c00 + 0x300 * i;
            g.word(0x5efac8 + 4 * i) = c;
            byteAt(c + 0x200) = x86::reg8(random32());
            byteAt(c + 0x89) = x86::reg8(below(2));
            g.word(c + 0x1f0) = below(2);
            for (const x86::reg32 at : {0x98u, 0x9cu, 0xa0u})
                aFloat(c + at, 400.0f);
        }
        for (x86::reg32 k = 0; k < 3; ++k)
            aFloat(0x570a78 + 4 * k, 400.0f);
        cpu.eax = below(2);
        cpu.ebx = 1 + below(4);
        cpu.edx = below(5 - cpu.ebx);
        g.word(0x570af0) = kSoundOut + 0x3400;
        g.word(0x570b40) = kSoundOut + 0x3400;
        g.word(0x55fe30) = below(2);
        for (x86::reg32 at = 0x7a3d1c; at < 0x7a3d7c; at += 4)
            aFloat(at, 400.0f);
        if (chance(50))
            cpu.fpu.setControl(0x7f);
    }
    // (A chain of its own: the race's tick takes the player's car too.)
    if (name == "playerCarSound" || name == "copCarSound" || name == "carEngine" || name == "raceAnnouncer"
        || name == "scenerySounds" || name == "raceSoundTick")
    {
        // The player's car: its cell, its up, its engine's numbers, its
        // knocks (24 bytes each from +0x7e0), its flags.
        const x86::reg32 c = kSoundOut + 0x3400, model = kSoundOut + 0x1700, engine = kSoundOut + 0x1780;
        cpu.eax = below(2);
        g.word(0x570ad8 + 0x18 + 0x50 * cpu.eax) = chance(95) ? c : 0;
        g.word(0x5dd948) = kSoundOut + 0x1000;
        g.word(c + 0x1c) = below(0x10);
        for (const x86::reg32 at : {0xd8u, 0xdcu, 0xe0u, 0x178u, 0x17cu, 0x180u})
            aFloat(c + at, 1.0f);
        byteAt(c + 0x200) = x86::reg8(random32());
        g.word(c + 0x2c4) = below(5);
        g.getMemory<x86::reg16>(c + 0x164) = x86::reg16(below(8));
        g.word(c + 0x8d4) = below(2);
        g.word(c + 0x998) = chance(50) ? 0x40 * below(3) - 1 : below(0xa0);
        g.word(c + 0x220) = model;
        g.word(model + 0x1c) = below(3);
        g.word(c + 0x528) = engine;
        g.word(engine + 0x1c4) = below(0x2000);
        g.word(c + 0x590) = below(0x4000);
        g.word(c + 0x7dc) = below(4);
        for (x86::reg32 k = 0; k < 3; ++k)
        {
            const x86::reg32 e = c + 0x7e0 + 24 * k;
            g.word(e) = below(7);
            g.word(e + 4) = chance(30) ? 0xffffffff : chance(30) ? 8 + 2 * below(2) : below(0x25);
            g.word(e + 8) = below(8);
            g.word(e + 0xc) = below(0x14);
            g.word(e + 0x10) = below(0x200000);
        }
        byteAt(c + 0x710) = x86::reg8(random32());
        byteAt(c + 0x50e) = x86::reg8(below(2));
        g.word(c + 0x1f0) = below(2);
        g.word(0x5e10b8) = chance(50) ? 0 : kSoundOut + 0x1790;
        g.word(0x5e10bc) = chance(50) ? 0 : kSoundOut + 0x1790;
        g.word(0x5e10b0) = chance(50) ? 0 : kSoundOut + 0x1794;
        g.word(0x5e10b4) = chance(50) ? 0 : kSoundOut + 0x1794;
        g.word(kSoundOut + 0x1790) = below(4);
        g.word(kSoundOut + 0x1794) = below(4);
        byteAt(0x6fd4fc) = x86::reg8(below(4));
        g.word(0x6fd4c0) = below(2);
        if (name == "carEngine")
        {
            // The engine: its revs, ground, speed and load; the load's curve.
            aFloat(c + 0x4f4, 12.0f);
            g.word(c + 0x7c) = below(4);
            g.word(c + 0x18c) = below(0x14);
            g.word(c + 0x15c) = chance(50) ? 0x3e000000 : 0x3f000000;
            g.word(c + 0x99c) = below(2);
            aFloat(c + 0x10c, 100.0f);
            aFloat(c + 0xb8, 100.0f);
            byteAt(c + 0x508) = x86::reg8(random32());
            for (x86::reg32 i = 0; i < 2; ++i)
                g.word(0x571078 + 4 * i) = below(0x140);
            for (x86::reg32 i = 0; i < 0x90; ++i)
                byteAt(0x552a38 + i) = x86::reg8(random32());
            byteAt(0x552d8c) = x86::reg8(random32());
            byteAt(0x552930) = x86::reg8(below(2));
            g.word(0x6fd3a0) = below(3);
            g.word(0x6fd4ac) = below(10);
            for (const x86::reg32 at : {0x570e48u, 0x570e50u, 0x570de8u, 0x570df0u, 0x570df8u, 0x570e00u})
                g.word(at) = aSoundHandle(g);
            cpu.eax = c;
            cpu.edx = below(0x1800);
            cpu.ebx = below(0x20000);
            cpu.ecx = below(0x20000);
            stack[0] = below(0x10000);
            stack[1] = below(0x10000);
        }
        if (name == "raceAnnouncer" || name == "scenerySounds" || name == "carEngine" || name == "playerCarSound"
            || name == "raceSoundTick")
        {
            if (name == "raceAnnouncer" || name == "scenerySounds")
            {
                cpu.eax = c;
                cpu.edx = below(0x10000);
            }
            // The scenery's repeating calls, the rain, the code segment's place.
            for (x86::reg32 at = 0x570f70; at < 0x570fa8; at += 4)
                g.word(at) = below(4);
            for (x86::reg32 i = 0; i < 2; ++i)
            {
                g.word(0x564288 + 4 * i) = below(3) * 0x30;
                byteAt(0x570de0 + i) = x86::reg8(below(2));
                byteAt(0x570f40 + i) = x86::reg8(below(2));
                byteAt(0x570f48 + i) = x86::reg8(below(2));
                g.word(0x570f20 + 4 * i) = below(0x80);
                g.word(0x571050 + 4 * i) = below(0x80);
                g.word(0x570f50 + 4 * i) = aSoundHandle(g);
            }
            g.word(0x571120) = below(0x200);
            g.word(0x57111c) = below(0x200);
            for (x86::reg32 k = 0; k < 3; ++k)
                g.word(0x412988 + 4 * k) = below(0x100000);
            for (x86::reg32 i = 0; i < 10; ++i)
                g.word(0x552d54 + 4 * i) = 0;
            g.word(c + 0x1c) = below(0x600);
            g.word(c + 0x638) = below(12);
            g.word(c + 0x18c) = chance(50) ? 0xa : below(0x10);
            g.getMemory<x86::reg16>(c + 0x74) = x86::reg16(below(2));
            g.word(0x6fd4ac) = below(9);
            g.word(0x552d84) = below(2);
            g.word(0x552d88) = below(2);
            g.word(0x552c38) = below(3);
            g.word(0x552c34) = below(10);
        }
        if (name == "raceAnnouncer" || name == "carEngine" || name == "playerCarSound" || name == "raceSoundTick")
        {
            // The race: the cars in order (0x5efac8, +0x2bc their places),
            // the car's laps and the clock, the voice's settings.
            for (x86::reg32 i = 0; i < 8; ++i)
            {
                g.word(0x5efac8 + 4 * i) = c;
                g.word(kSoundOut + 0x1c00 + 0x300 * i + 0x2bc) = below(8);
            }
            g.word(0x5efacc) = kSoundOut + 0x1c00;
            g.word(c + 0x2bc) = below(8);
            g.word(c + 0x2c) = chance(70) ? kSoundOut + 0x1798 : 0;
            g.word(c + 0x204) = below(9);
            g.word(c + 0x238) = below(0x10000);
            g.word(c + 0x628) = chance(70) ? kSoundOut + 0x17a0 : 0;
            g.word(kSoundOut + 0x17a0 + 0x2c) = x86::reg32(x86::sreg32(below(5)) - 2);
            g.word(c + 0x8a0) = chance(30) ? 0 : below(0x400);
            g.word(c + 0x998) = below(2);
            g.word(c + 0x1f0) = below(2);
            g.word(0x6fd4b4) = 1 + below(8);
            for (x86::reg32 i = 0; i < 2; ++i)
            {
                byteAt(0x5710c8 + i) = x86::reg8(below(9));
                g.word(0x5710d0 + 4 * i) = below(0x10000);
                g.word(0x5710f0 + 4 * i) = below(0x10000);
            }
            g.word(0x7d3684) = below(0x20000);
            g.word(0x7d36b0) = below(0x400);
            g.word(0x552904) = below(0x10000);
            for (const x86::reg32 at : {0x6fd3b8u, 0x6fd520u, 0x6fd50cu, 0x6fbc68u, 0x6fbb4cu})
                g.word(at) = below(4);
            g.word(0x552860) = x86::reg32(x86::sreg32(below(10)) - 1);
            g.word(0x55285c) = below(9);
            byteAt(0x552834) = x86::reg8(below(8));
            byteAt(0x552850) = x86::reg8(chance(50) ? 0x32 * below(3) : random32());
            byteAt(0x552d7c) = x86::reg8(below(2));
            g.word(0x571238) = below(8);
            g.word(0x571240) = below(8);
        }
        if (name == "carEngine" || name == "playerCarSound" || name == "raceSoundTick")
        {
            // The co-driver quiet: its calls' frames would leave the stack
            // the announcer's line reads unset (+0x1c) other than the
            // generated code's.
            g.word(0x6fd49c) = 0;
            // Nothing being said, a line held back: the announcer's lines
            // (two of whose words the code leaves unset) never queued.
            if (name == "raceSoundTick")
            {
                g.word(0x7dd348) = 0;
                g.word(0x7dd34c) = 0;
                g.word(0x560118) = 1;  // and held back while one is being said
            }
        }
        if (name == "copCarSound")
        {
            // A cop source with the player's car as its own, a horn's ticks.
            cpu.edx = below(4);
            const x86::reg32 s = 0x570b78 + 0x38 * cpu.edx;
            g.word(s) = chance(95) ? c : 0;
            g.word(s + 0x20) = x86::reg32(x86::sreg32(below(5)) - 2);
            g.word(s + 0x24) = below(3);
            g.word(s + 0x28) = below(3);
            g.word(s + 0x2c) = below(3);
            g.word(0x570af0 + 0x50 * cpu.eax) = c;
            g.word(model + 0x14) = 0x32 + below(0x16);
            aFloat(c + 0x7c0, 100.0f);
            aFloat(c + 0x7c4, 100.0f);
            g.word(0x570dcc) = below(2);
        }
        if (chance(50))
            cpu.fpu.setControl(0x7f);
    }
    else if (name == "coDriverTick")
    {
        // The script of calls: (place, lead), its calls, -1 -- and -2 at the
        // end.
        const x86::reg32 script = kSoundOut + 0x3a00;
        x86::reg32 at = script, place = below(0x100);
        for (x86::reg32 n = 1 + below(5); n > 0; --n)
        {
            g.word(at) = place;
            g.word(at + 4) = chance(80) ? below(0x20) : 0x11;
            at += 8;
            for (x86::reg32 k = below(3); k > 0; --k, at += 4)
                g.word(at) = chance(20) ? 0xf : chance(20) ? 0xc : below(0x14);
            g.word(at) = 0xffffffff;
            at += 4;
            place += below(0x100);
        }
        g.word(at) = 0xfffffffe;
        g.word(0x7dd828) = script;
        cpu.eax = below(2);
        g.word(0x7dd380 + 4 * cpu.eax) = chance(90) ? script + 4 * below((at - script) / 4) : 0;
        g.word(0x7dd360 + 4 * cpu.eax) = below(3);
        g.word(0x6fd49c) = chance(90) ? 1 : 0;
        g.word(0x5dd940) = below(0x1000);
        const x86::reg32 c = kSoundOut + 0x3400;
        g.word(0x5efa48 + 4 * cpu.eax) = c;
        g.word(0x5efa48 + 4 * g.word(0x6fd4f4)) = c;
        aFloat(c + 0x7c0, 100.0f);
        aFloat(c + 0x4f4, 12.0f);
        g.word(c + 0x224) = below(0x400);
        g.word(c + 0x998) = chance(80) ? 0 : 1;
        g.word(c + 0x204) = below(3);
        for (x86::reg32 i = 0; i < 0x40; ++i)
            byteAt(0x560ac9 + i) = x86::reg8(below(0x40));
        g.word(0x6fd4c4) = below(2);
        g.word(0x6fd4c0) = below(2);
        if (chance(50))
            cpu.fpu.setControl(0x7f);
    }
    else if (name == "speechLine")
    {
        // A line: effect, volume, pitch, pan, bank, player, kind, the game's.
        cpu.eax = kSoundOut + 0x1f00;
        for (x86::reg32 k = 0; k < 9; ++k)
            g.word(cpu.eax + 4 * k) = below(0x80);
        g.word(cpu.eax + 0x10) = chance(80) ? below(24) : random32();
        g.word(cpu.eax + 0x14) = below(3);
        g.word(cpu.eax + 0x18) = below(6);
        g.word(0x7dd378) = chance(80) ? below(0x10) : 0x10;
        g.word(0x7dd37c) = chance(80) ? below(0x10) : 0x10;
        g.word(0x560118) = chance(70) ? 0 : 1;
    }
    else if (name == "raceBanksLoad")
    {
        // The units' names (the code segment's), the units, the cars.
        for (x86::reg32 k = 0; k < 7; ++k)
            g.word(0x41296c + 4 * k) = k < 5 ? 0x5369c4 + 4 * k : 0x5369c4;
        g.word(0x413ba8) = 0;
        g.word(0x6fbb4c) = below(6);
        static const x86::reg32 folders[] = {0x413bf4, 0x413bfb, 0x413c02, 0x413c09, 0x413c10, 0x413bf4};
        for (x86::reg32 k = 0; k < 6; ++k)
            g.word(0x413ba8 + 4 * k) = folders[k];
        for (const x86::reg32 at : {0x6fd540u, 0x6fd5acu, 0x6fd684u, 0x6fd5acu + 0x6c, 0x6fd540u + 0x6c})
            g.word(at) = chance(70) ? below(0x32) : chance(50) ? 0x258 + below(5) : value();
        for (const x86::reg32 at : {0x6fd520u, 0x6fd4f4u, 0x6fd500u, 0x6fd4ccu, 0x6fd4c8u, 0x6fd49cu, 0x6fd3b8u})
            g.word(at) = below(4);
        byteAt(0x6fd4fc) = x86::reg8(below(4));
        g.word(0x6fd4ac) = below(12);
    }
    else if (name == "trackSounds")
    {
        // The sound table (18 bytes an object: range, effect, stretch from
        // +4 to +0xa, more effects at +0xc and +0xe) and the sections' lists
        // of records (a length word, the kind a byte at +2: 3 a sound).
        const x86::reg32 table = kSoundOut + 0x3c00, lists = kSoundOut + 0x3e00, sections = kSoundOut + 0x3e40;
        g.word(0x570dd0) = chance(95) ? table : 0;
        for (x86::reg32 k = 0; k < 8; ++k)
        {
            const x86::reg32 o = table + 18 * k;
            g.getMemory<x86::reg16>(o) = x86::reg16(1 + below(0x400));
            static const x86::reg16 thirds[] = {0xfffe, 0xfffd, 0xffff};
            for (x86::reg32 at = 2; at < 0xe; at += 2)
                g.getMemory<x86::reg16>(o + at) = x86::reg16(chance(20) ? 0xffff : below(8));
            g.getMemory<x86::reg16>(o + 0xe) = chance(50) ? thirds[below(3)] : x86::reg16(below(8));
            // Its stretch: four places in order (laps for some), never 0 apart.
            x86::reg32 place = below(4);
            for (x86::reg32 at = 4; at <= 0xa; at += 2, place += 1 + below(4))
                g.getMemory<x86::reg16>(o + at) = x86::reg16(place);
        }
        x86::reg32 at = sections;
        for (x86::reg32 s = 0; s < 2; ++s)
        {
            g.word(0x552600 + 4 * s) = lists + 4 * s;
            g.word(lists + 4 * s) = chance(80) ? at : 0;
            const x86::reg32 n = below(4);
            g.getMemory<x86::reg16>(at + 6) = x86::reg16(n);
            at += 8;
            for (x86::reg32 r = 0; r < n; ++r, at += 0xc)
            {
                g.getMemory<x86::reg16>(at) = 0xc;
                byteAt(at + 2) = x86::reg8(chance(70) ? 3 : below(5));
            }
        }
        g.word(0x552608) = 0;
        g.word(0x570dd4) = below(4);
        g.word(0x570dd8) = below(4);
        cpu.eax = below(2);
        if (chance(50))
            cpu.fpu.setControl(0x7f);
    }
    else if (name == "zoneSound")
    {
        // The zones: a few of 6 words, in order along the track, then -1.
        const x86::reg32 zones = kSoundOut + 0x3c00;
        x86::reg32 at = zones, place = below(0x40);
        for (x86::reg32 n = below(5); n > 0; --n, at += 0x18)
        {
            for (x86::reg32 k = 0; k < 4; ++k)
            {
                g.word(at + 4 * k) = place;
                place += below(0x40);
            }
            g.word(at + 0x10) = below(0xd);
            g.word(at + 0x14) = chance(70) ? x86::reg32(x86::sreg32(below(3)) - 1) : value();
        }
        g.word(at) = 0xffffffff;
        const x86::reg32 car = kSoundOut + 0x3400;
        g.word(car + 0x1c) = below(place + 0x40);
        g.word(0x6fd4f8) = chance(90) ? g.word(0x6fd4f4) : below(8);
        cpu.eax = below(0x25);
        cpu.edx = car;
        cpu.ecx = chance(95) ? zones : 0;
        cpu.ebx = below(0x10000);
    }
    else if (name == "carFlagTest")
        cpu.eax = kSoundOut + 0x3400;
    else if (name == "copLineFor")
        cpu.eax = below(6);
    else if (name == "copRemove")
    {
        cpu.eax = below(4);
        cpu.edx = below(2);
    }
    else if (name == "raceSoundInit")
        g.word(0x6fd4ac) = chance(80) ? below(0xa) : below(0x10);
    else if (name == "sourceReset")
    {
        cpu.eax = kSoundOut + 0x2400;
        cpu.edx = chance(50) ? 0 : random32();
    }
    else if (name == "copChaseSet")
    {
        cpu.eax = g.word(0x570b78 + 0x38 * below(4));
        cpu.ebx = value();
        cpu.ecx = value();
        cpu.edx = value();
    }
    else if (name == "copSiren" || name == "copEngine" || name == "copSirenStop" || name == "copEngineStop"
             || name == "copDistance")
    {
        cpu.eax = below(4);
        if (name == "copEngine")
            g.word(0x570b78) = kSoundOut + 0x800;
        if (name == "copEngine" && g.word(0x570b78 + 0x38 * cpu.eax) == 0)
            g.word(0x570b78 + 0x38 * cpu.eax) = kSoundOut + 0x900;
        cpu.ecx = below(0x1800);
        cpu.ebx = below(0x8000);
        cpu.edx = below(0x10000);
    }
    else if (name == "copsCloseness")
    {
        cpu.eax = below(5);
        cpu.edx = below(4 - (cpu.eax < 4 ? cpu.eax : 4) + 1);
    }
    else if (name == "copBeepTick" || name == "copBeepStart" || name == "copEffect" || name == "chaseLevel")
    {
        cpu.eax = name == "copBeepTick" ? below(2) : below(6);
        cpu.edx = below(2);
    }
    else if (name == "listenerMove")
    {
        cpu.eax = below(4);
        cpu.edx = kSoundOut + 0x2000 + 4 * below(0x40);
    }
    else if (name == "sourceDistance" || name == "sourceAngle" || name == "carAngle")
    {
        cpu.eax = kSoundOut + 0x2000 + 4 * below(0x40);
        cpu.edx = kSoundOut + 0x2000 + 4 * below(0x40);
        if (name == "carAngle")
            cpu.edx = kSoundOut + 0x2000 + 4 * below(0x40) - 0x13c + 0x100;
        g.word(0x6fd4c4) = below(2);
        if (chance(50))
            cpu.fpu.setControl(0x7f);  // the race's single precision
    }
    else if (name == "speechTick" || name == "speechSaid" || name == "copRadio" || name == "raceEventLine"
        || name == "lapTimeLine")
    {
        cpu.eax = chance(90) ? below(2) : below(3);
        cpu.edx = name == "lapTimeLine" ? below(0x180) : below(0x10);
        cpu.ebx = below(0x1800);
    }
    else if (name == "radioTick" || name == "radioStart")
    {
        cpu.eax = below(8);
        g.word(0x7dd818) = chance(50) ? cpu.eax : below(8);
        cpu.ecx = below(0x1800);
        cpu.ebx = below(0x8000);
        cpu.edx = below(0x10000);
        stack[0] = below(2);
    }
    else if (name == "queueSpeechLine" || name == "queueRaceLine")
    {
        cpu.eax = below(0x50);
        cpu.edx = below(2);
        cpu.ebx = below(5);
    }
    else if (name == "gapLine")
    {
        cpu.eax = kSoundOut + 0x1c00 + 0x300 * below(8);
        cpu.edx = below(2);
        cpu.ebx = below(2);
    }
    else if (name == "raceVoiceFree")
    {
        // SND removes the banks the code names, real: handles it has.
        g.word(0x571130) = below(24);
        g.word(0x57113c) = below(24);
    }
    else if (name == "descriptionLoad")
    {
        cpu.eax = kSoundOut + 0x1b00;
        aString(cpu.eax, below(0x20));
    }
    else if (name == "descriptionStart")
    {
        cpu.eax = chance(90) ? below(0x32) : value();
        cpu.edx = chance(90) ? 0x32 + below(3) : value();
        cpu.ebx = below(7);
    }
    else if (name == "descriptionSpeak" || name == "carLineSpeak" || name == "raceVoiceLoad")
    {
        cpu.eax = name == "raceVoiceLoad" ? below(2) : below(0x10);
        cpu.edx = below(0x10);
        g.word(0x6fbb4c) = below(6);  // past 5 the name is the stack's
    }
    else if (name == "crashPitch" || name == "crashEffect" || name == "scrapeEffect" || name == "carKnock")
    {
        static const x86::reg32 kinds[] = {5, 6, 0xd, 0, 1};
        cpu.eax = name == "carKnock" ? (chance(40) ? 0xffffffff : below(0x25))
                : name == "crashEffect" ? below(0x80) : below(0x25);
        cpu.edx = name == "crashPitch" ? (chance(60) ? 0x28 + below(8) : below(0x30)) : kinds[below(5)];
        cpu.ebx = name == "crashPitch" ? below(0x200000) : below(0x14);
        cpu.ecx = chance(80) ? below(0x200000) : value();
        stack[0] = chance(80) ? below(0x1000) : value();
        stack[1] = below(0x10000);
        if (chance(30))
            g.word(0x552d80) = 0x1d + below(9);
    }
    else if (name == "farEffectAim")
    {
        cpu.eax = x86::reg32(x86::sreg32(below(0x2000000)) - 0x1000000);
        cpu.edx = x86::reg32(x86::sreg32(below(0x2000000)) - 0x1000000);
    }
    else if (name == "crowdEffect" || name == "carEffectFifteen")
    {
        cpu.eax = below(2);
        cpu.edx = chance(50) ? 0xffffffff : below(0x10);
    }
    else if (name.compare(0, 5, "siren") == 0)
    {
        cpu.eax = below(5);
        cpu.edx = chance(80) ? below(0x80) : value();
        cpu.ecx = chance(80) ? below(0x10000) : value();
        cpu.ebx = chance(80) ? below(0x8000) : value();
    }
    else if (name == "noiseByDistance" || name == "noiseBySpeed" || name == "playerNoise"
             || name == "playerNoiseStop")
    {
        cpu.eax = chance(90) ? below(0x25) : chance(50) ? 0xffffffff : below(2);
        cpu.edx = name == "noiseBySpeed" ? (chance(80) ? below(3) : value())
                : name == "playerNoise" ? below(0x2000) : below(0xd);
        cpu.ecx = chance(80) ? below(0x20000) : value();
        cpu.ebx = chance(80) ? below(0x20000) : value();
        stack[0] = chance(80) ? below(0x2000) : value();
        stack[1] = below(0x10000);
        stack[2] = chance(80) ? x86::reg32(x86::sreg32(below(0x800000)) - 0x400000) : value();
        g.word(0x55260c) = chance(80) ? 1 + below(0x2000) : 0;
    }
    else if (name == "slotStop")
        cpu.eax = chance(95) ? below(0x25) : 0xffffffff;
    else if (name == "slotEffect" || name == "slotPlay")
    {
        cpu.eax = below(0x25);
        cpu.edx = chance(90) ? below(0xd) : below(0x20);
        cpu.ecx = chance(80) ? below(0x80) : value();
        cpu.ebx = name == "slotEffect" ? (chance(80) ? below(0x20000) : value())
                                       : (chance(80) ? below(0x80) : value());
        stack[0] = name == "slotEffect" ? below(0x80) : below(0x10000);
        stack[1] = chance(80) ? below(0x10000) : value();
        stack[2] = below(2);
        if (chance(30))
            g.word(0x570dec + 8 * cpu.eax) = cpu.edx;
    }
    else if (name == "playEffect" || name == "playSpeechEffect")
    {
        cpu.eax = aBank();
        cpu.edx = chance(80) ? below(0x30) : value();
        cpu.ecx = chance(80) ? below(0x80) : value();
        cpu.ebx = chance(80) ? below(0x10000) : value();
        stack[0] = below(0x80);
    }
    else if (name == "playMenuEffect")
    {
        cpu.eax = below(0x30);
        cpu.edx = chance(80) ? below(0x80) : value();
    }
    else if (name == "panFromSide")
    {
        cpu.eax = below(0x80);
        cpu.edx = value();
    }
    else if (name == "SNDangle")
    {
        // Within a quarter of the range either way: the code's divide
        // overflows past it, the game's vectors never come near.
        const auto component = [] { return x86::reg32(x86::sreg32(below(0x80000000)) - 0x40000000); };
        cpu.eax = chance(10) ? 0 : component();
        cpu.edx = chance(10) ? cpu.eax : chance(10) ? 0u - cpu.eax : component();
    }
    else if (name == "raceMusicPrepare" || name == "musicAfterSetting")
        cpu.eax = chance(90) ? below(0xc) : value() & 0xff;
    else if (name == "musicStart" || name == "raceMusicStart")
    {
        static const x86::reg32 tunes[] = {0x63, 0x16, 0x17, 0x18};
        cpu.eax = chance(60) ? below(0xa) : chance(80) ? tunes[below(4)] : below(0x30);
        cpu.edx = below(0x80);
        cpu.ebx = below(2);
        byteAt(0x5525fc) = x86::reg8(below(8));
    }
    else if (name == "musicStreamMakeOf")
        cpu.eax = below(0x400);
    else if (name == "bankLoad")
    {
        cpu.eax = kSoundOut + 0x400;
        for (x86::reg32 i = 0; i < 0x20; ++i)
            byteAt(cpu.eax + i) = x86::reg8(i < 0x1f ? 'a' + below(26) : 0);
        cpu.edx = below(0x17);
    }
    if (name == "raceMusicPrepare" || name == "musicStart" || name == "raceMusicStart" || name == "raceTuneOf"
        || name == "musicAfterSetting")
        g.word(0x6fbbe4) = chance(90) ? below(0xd) : value();
    return true;
}

/* The effects' and the mixer's start's arguments; false for another's. */
bool makeFxArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {"reverbLength", "reverbInit", "iSNDwinsetfx", "setBusFx", "busLevelSet",
                                        "SNDfxlevel", "SNDfxinitbus", "SNDfxmasterlevel", "iSNDmixreinit",
                                        "mixFunctions", "iSNDmixinit"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    const auto aRate = [] { return chance(70) ? 22050u : 8000 + below(40000); };
    const auto aType = [] {
        static const x86::reg32 types[] = {0, 5, 10, 20, 30, 40, 50, 100, 110, 120};
        return chance(90) ? types[below(10)] : below(0x100);
    };
    g.getMemory<x86::reg16>(0x9ef614) = x86::reg16(aRate());
    for (x86::reg32 i = 0; i < 8; ++i)
        g.getMemory<float>(0x56ae2c + 4 * i) = float(below(1000)) / 1000.0f;
    g.word(0xa0a25c) = aType();
    g.word(0xa0a260) = chance(90) ? below(0x80) : random32();
    g.word(0x5643b4) = chance(50) ? 1 : 0;
    g.word(0x9f6a60) = chance(50) ? 0x5230b8 : 0;
    g.word(0x9f6a5c) = chance(50) ? 0x5209a0 : 0x521c90;
    if (name == "reverbLength")
    {
        cpu.eax = chance(90) ? aRate() : below(4);
        const float time = chance(90) ? float(1 + below(300)) / 1000.0f : float(below(4)) / 1000.0f;
        std::memcpy(&stack[0], &time, 4);
    }
    else if (name == "reverbInit")
        cpu.eax = aRate();
    else if (name == "iSNDwinsetfx")
        cpu.eax = aType();
    else if (name == "setBusFx")
        cpu.edx = aType();
    else if (name == "SNDfxlevel" || name == "SNDfxmasterlevel")
    {
        cpu.eax = name == "SNDfxlevel" ? aSoundHandle(g) : (chance(95) ? 0 : below(3));
        cpu.edx = name == "SNDfxlevel" ? (chance(95) ? 0 : below(3)) : aSoundLevel();
        cpu.ebx = aSoundLevel();
    }
    else if (name == "SNDfxinitbus")
    {
        cpu.eax = chance(95) ? 0 : below(3);
        cpu.edx = aSoundLevel();
        cpu.ebx = aType();
        cpu.ecx = chance(30) ? 0xffffffff : aSoundLevel();
        stack[0] = chance(30) ? 0xffffffff : aSoundLevel();
    }
    else if (name == "iSNDmixreinit" || name == "iSNDmixinit")
    {
        cpu.eax = (chance(90) ? 1u << below(4) : below(0x100)) | below(0x100) << 8;
        cpu.edx = random32();
    }
    return true;
}

/* The driver's functions' arguments, on its world: its flags, eacsnd's
 * functions stand-ins, the restores registered or not, the sound thread's
 * server and event; false for another's. */
bool makeDriverArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {"iSNDunloaddll", "SNDsetrate", "leaveAudioLocks", "iSNDmessageinit",
                                        "iSNDinit", "iSNDrestore", "iSNDverifymode", "SNDinit", "SNDrestore",
                                        "soundThread", "setSoundServer"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    g_mostCalls = 100 + below(200);
    auto byteAt = [&](x86::reg32 at) { return g.getMemory<x86::reg8>(at); };
    // A mode: a format (1, 2, 4, 8), a rate (its second byte), stereo now and then.
    const auto aMode = [] {
        return chance(10) ? 0xffffffff : (chance(90) ? 1u << below(4) : below(0x100))
                                             | (chance(90) ? 1u << below(6) : below(0x100)) << 8
                                             | (chance(50) ? 0x20000u : 0);
    };
    g.word(0x9ef600) = chance(50) ? 0x7700 + 0x10 * below(0x10) : 0;
    for (x86::reg32 at = 0x9ef604; at < 0x9ef608; ++at)
        byteAt(at) = x86::reg8(chance(50) ? 1 : 0);
    g.word(0x9ef610) = aMode();
    g.word(0x9ef61c) = standInFor(0xfff338);
    g.word(0x9ef620) = standInFor(0xfff33c);
    g.word(0x9ef624) = standInFor(0xfff340);
    g.word(0x9ef654) = chance(70) ? standInFor(0xfff344) : 0;
    for (x86::reg32 at = 0xa09b24; at <= 0xa09b38; at += 4)
        g.word(at) = chance(40) ? standInFor(0xfff348) : 0;
    g.word(0xa09b08) = chance(50) ? 0 : 0x500c80;
    g.word(0x5643d8) = chance(85) ? 1 : 0;
    g.word(0x79c150) = chance(50) ? standInFor(0xfff348) : 0;
    // The mixer's start (eacsnd's start before it) runs the reverb and clears
    // the buffer through these.
    g.word(0x9f6a60) = chance(50) ? 0x5230b8 : 0;
    g.word(0x5643b4) = chance(50) ? 1 : 0;
    g.word(0x79c168) = chance(50) ? 0x7400 + 4 * below(0x40) : 0;
    if (name == "SNDsetrate")
        cpu.eax = random32();
    else if (name == "iSNDmessageinit")
    {
        for (x86::reg32 i = 0; i < 6; ++i)
            stack[i] = random32();
        stack[1] = chance(90) ? 0x7700 + 4 * below(0x40) : 0;
        stack[4] = chance(70) ? 0 : 1;
    }
    else if (name == "iSNDinit" || name == "iSNDverifymode" || name == "SNDinit")
    {
        cpu.eax = aMode();
        cpu.edx = random32();
    }
    else if (name == "setSoundServer")
        cpu.eax = chance(50) ? 0 : standInFor(0xfff348);
    return true;
}

/* EA's timer's functions' arguments (port_timer.cpp): the clock's state as it is when stopped, running,
 * or half started, the callbacks' table of the game's tick clients or empty; false for another's. */
bool makeTimerArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {"timerThread", "clearTimerCallbacks", "timerTick", "addTimerCallback",
                                        "removeTimerCallback", "stopTimer", "startTimer"};
    bool ours = false;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    // The loops that wait on the clock or a thread end where the cap stops them.
    g_mostCalls = 60 + below(150);
    const x86::reg32 client = standInFor(0xfff310);
    const bool callable = name == "timerThread" || name == "timerTick";
    // The callbacks: a run of clients, then none; or any now and then (never called but by the thread).
    const x86::reg32 filled = chance(20) ? 0 : chance(40) ? 8 : below(9);
    for (x86::reg32 i = 0; i < 8; ++i)
        g.word(0x79c130 + 4 * i) = (i < filled || chance(10)) ? (callable || chance(70) ? client : 0x400000 + 0x10 * below(4))
                                                              : 0;
    if (callable && chance(10))
        g.word(0x79c130 + 4 * below(8)) = 0;
    const bool running = chance(65);
    g.word(0x79c19c) = running ? 1 : 0;
    g.word(0x5643d8) = running && chance(85) ? 1 + below(200) : chance(10) ? 1 : 0;
    g.word(0x79c17c) = chance(65) ? 0x7400 + 4 * below(0x40) : 0;
    g.word(0x79c168) = chance(50) ? 0x7500 + 4 * below(0x40) : 0;
    g.word(0x79c194) = chance(65) ? 1 + below(100) : 0;
    g.word(0x79c174) = chance(80) ? 1 : below(6);
    g.word(0x79c170) = chance(85) ? 0x3e80000 / (1 + below(1000)) : random32();
    g.word(0x79c198) = chance(85) ? below(0x10000) : random32();
    g.word(0x79c178) = chance(10) ? 0 : random32();
    g.word(0x79c16c) = random32();
    g.word(0x79c1a0) = random32();
    g.word(0x79c1a4) = random32();
    g.word(0x55e2c4) = chance(70) ? 0 : below(3);
    g.word(0x55e2d0) = chance(80) ? below(4) : random32();
    g.word(0x55e2d4) = chance(65) ? 0 : below(4);
    g.word(0x56441c) = chance(50) ? 0x48ed00 : 0;
    if (name == "addTimerCallback" || name == "removeTimerCallback")
    {
        // A function in the table, or another, or none.
        cpu.eax = chance(55) ? g.word(0x79c130 + 4 * below(8)) : chance(10) ? 0 : chance(50) ? client : 0x400000 + 0x10 * below(6);
    }
    else if (name == "startTimer")
        cpu.eax = chance(55) ? 1 + below(200) : chance(10) ? 0 : chance(40) ? 10000 + below(3) : chance(50) ? below(20000) : random32();
    return true;
}

/* The stream's functions' arguments, on their world; false for another's. */
bool makeStreamArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    static const char* const names[] = {
        "addSystemTask", "removeSystemTask", "runSystemTasks", "waitSystemTasks", "setTopupFunction",
        "topUpStream", "topupDone", "toppedUp", "topUpBeforeLoad", "topupReturn", "waitTopupStream", "waitTopupMain", "waitTopupEvent",
        "loadBlockSize", "loadFlags", "iSNDclearchunk", "platformChunks", "SNDstreamautovol", "SNDstreamgetvol",
        "resetStreamer", "SNDstreamsetup", "SNDstreamrestore", "SNDstreamqueue", "SNDstreaminterrupt",
        "SNDstreampurge", "SNDstreamchunksleft", "SNDstreambuftime", "streamToppedUp", "iSNDstreamchecktopup",
        "iSNDstreamsetbuftime", "parseStreamChunk", "dropQueuedChunks", "queueDataChunk", "iSNDparseheader",
        "queueLoopChunk", "streamSeekChunk", "streamEndChunk", "streamEndsSeen", "nextStreamChunk",
        "iSNDstreamservice", "iSNDstreamstart", "SNDstreamvol", "freeStreamChunk", "streamBytesRead",
        "readerIdle", "readerWaits", "passFreedChunks", "roomAhead", "roomToEnd", "roomAtStart",
        "getStreamChunk", "chainCommandBlocks", "freeCommandBlock", "commandBlocksFree", "takeCommandBlock",
        "streamCommand", "purgeStreamCommand", "initStreamStruct", "initStreamStructSecond",
        "initStreamStructFirst", "initStream", "initStreamSecond", "initStreamFirst", "deleteStreamStruct",
        "deleteStream", "streamReaderThread", "pathStep", "pathTask", "pathHook", "SNDpathinit",
        "SNDpathstartstream", "SNDpathcontrol", "SNDpathevent", "SNDpatheventinterrupt", "SNDpathrestore"};
    // The commands' wrappers: streamOpen, streamSeekQuietly, ...
    static const char* const wrappers[] = {"streamOpen", "streamContinue", "streamSwitch", "streamQueueFile",
                                           "streamRestart", "streamSeek", "streamReadOn", "streamStopAt"};
    bool wrapper = false;
    for (const char* n : wrappers)
        if (name == n || name == std::string(n) + "Quietly" || name == std::string(n) + "Next"
            || name == std::string(n) + "NextQuietly")
            wrapper = true;
    bool ours = wrapper;
    for (const char* n : names)
        ours = ours || name == n;
    if (!ours)
        return false;
    // The loops that wait on a thread or the clock end where the cap stops them.
    g_mostCalls = 200 + below(400);
    const StreamWorld w = makeStreamWorld(g, name == "deleteStreamStruct" || name == "deleteStream");
    const x86::reg32 events = makePathWorld(g);
    const auto aStream = [&] { return chance(80) ? kStreamFirst : kStreamSecond; };
    const auto aChunk = [&] { return w.chunks[below(x86::reg32(w.chunks.size()))]; };
    const auto liveQueue = [&] {
        if (g.word(0x564680) == 0)
        {
            g.word(0x564680) = w.chunks[0];
            g.word(0x564684) = w.chunks[0];
        }
        g.word(g.word(0x564684)) = 0;
    };
    if (wrapper)
    {
        cpu.eax = aStream();
        const bool named = name.find("Seek") == std::string::npos && name.find("ReadOn") == std::string::npos
                           && name.find("StopAt") == std::string::npos;
        cpu.edx = named ? aStreamName(g) : below(0x10000);
    }
    else if (name == "addSystemTask")
    {
        cpu.eax = chance(30) ? g.word(0x9ef7e8 + 0x10 * below(16)) : standInFor(0xfff320) + 0x10 * below(2);
        cpu.edx = below(10);
        cpu.ebx = below(10);
    }
    else if (name == "removeSystemTask")
        cpu.eax = chance(70) ? g.word(0x9ef7e8 + 0x10 * below(16)) : random32();
    else if (name == "waitTopupMain" || name == "waitTopupEvent")
    {
        // Entered by a jump with ebp and edx pushed: here the return address's
        // slot and the first word are what it pops.
        cpu.edx = name == "waitTopupEvent" ? g.word(0x567864) : random32();
    }
    else if (name == "waitSystemTasks")
    {
        // Its wait ends by the timer's thread: here, with the timer still, only
        // when a task due gives something back -- each case's one run of them.
        cpu.eax = below(4);
        if (cpu.eax != 0)
        {
            g.word(0x564674) = g.word(0x79c1a0) - 1;
            g.word(0x9ef7e8) = standInFor(0xfff32c);
            g.word(0x9ef7e8 + 8) = g.word(0x79c1a0);
            g.word(0x9ef7e8 + 0xc) = 0;
        }
    }
    else if (name == "iSNDclearchunk")
    {
        const x86::reg32 p = 0x9ef658 + 0x10 * below(16);
        g.getMemory<x86::reg8>(p + 2) = x86::reg8(chance(50) ? 0x10 : chance(80) ? 8 : below(0x20));
        g.getMemory<x86::reg8>(p + 3) = x86::reg8(chance(95) ? 1 + below(2) : below(4));
        g.getMemory<x86::reg8>(p + 4) = x86::reg8(chance(95) ? (chance(40) ? 0 : chance(50) ? 7 : 9) : below(0x10));
        cpu.eax = kStreamBuffer;
        cpu.edx = chance(90) ? below(0x200) : x86::reg32(-x86::sreg32(below(0x10)));
        cpu.ebx = (p - 0x9ef658) / 0x10;
    }
    else if (name == "SNDstreamautovol")
    {
        cpu.eax = below(100);
        cpu.edx = aSoundLevel();
    }
    else if (name == "SNDstreamvol")
        cpu.eax = aSoundLevel();
    else if (name == "SNDstreamsetup")
    {
        const x86::reg32 options = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
            g.getMemory<x86::reg8>(options + i) = x86::reg8(below(0x80));
        cpu.eax = aStream();
        cpu.edx = options;
    }
    else if (name == "SNDstreamqueue" || name == "SNDstreaminterrupt")
    {
        // An interrupt walks the queue past the voice's chunks and frees
        // the rest: a queue there is, its last one not the end's mark (-1).
        if (name == "SNDstreaminterrupt")
            liveQueue();
        cpu.eax = aStreamName(g);
        cpu.edx = chance(50) ? 0 : below(0x10000);
    }
    else if (name == "streamToppedUp")
        cpu.eax = below(3);
    else if (name == "iSNDstreamsetbuftime")
        cpu.eax = chance(90) ? below(5000) : x86::reg32(-x86::sreg32(below(4)));
    else if (name == "parseStreamChunk" || name == "queueDataChunk" || name == "queueLoopChunk"
             || name == "streamSeekChunk" || name == "streamEndChunk" || name == "iSNDparseheader")
    {
        cpu.eax = aChunk();
        // A header's patch always: on another's bytes the tags it reads run off
        // anywhere, in the game's code too.
        if (name == "iSNDparseheader")
        {
            g.word(cpu.eax) = kStreamIds[1];
            g.word(cpu.eax + 4) = 8 + makeStreamHeader(g, cpu.eax + 8);
            if (chance(5))
                g.word(cpu.eax + 4) += 4 * below(0x10);  // past what it holds: copied whole, and past 0x5c the error
        }
    }
    else if (name == "nextStreamChunk")
    {
        cpu.eax = kSoundOut;
        cpu.edx = kSoundOut + 4;
    }
    else if (name == "freeStreamChunk")
    {
        cpu.eax = aStream();
        cpu.edx = aChunk();
    }
    else if (name == "streamBytesRead")
        cpu.eax = chance(90) ? aStream() : 0;
    else if (name == "readerWaits" || name == "passFreedChunks" || name == "roomAhead" || name == "roomToEnd"
             || name == "roomAtStart")
        cpu.eax = aStream();
    else if (name == "getStreamChunk")
        cpu.eax = chance(95) ? aStream() : 0;
    else if (name == "chainCommandBlocks")
    {
        cpu.eax = kStreamFirst + 0xc0;
        cpu.edx = chance(95) ? 1 + below(kStreamBlocks) : 0;
    }
    else if (name == "freeCommandBlock")
        cpu.eax = w.blocks[below(kStreamBlocks)];
    else if (name == "commandBlocksFree")
        cpu.eax = below(10);
    else if (name == "takeCommandBlock")
        cpu.eax = chance(50) ? 1 : 0;
    else if (name == "streamCommand" || name == "purgeStreamCommand")
    {
        static const x86::reg32 commands[] = {1, 2, 0xb, 0xd, 0x10, 0x11, 0x12, 0x13, 0x14};
        cpu.eax = aStream();
        cpu.edx = aStreamName(g);
        cpu.ebx = commands[below(9)];
        cpu.ecx = below(0x10000);
        stack[0] = chance(50) ? 1 : 0;
        stack[1] = chance(50) ? 1 : 0;
    }
    else if (name.compare(0, 16, "initStreamStruct") == 0)
    {
        cpu.eax = kStreamFirst;
        cpu.edx = below(0x1000);
        cpu.ebx = chance(80) ? 0x2000 * (1 + below(4)) : 0x100 * below(0x20);
        cpu.ecx = chance(50) ? 1 : 0;
    }
    else if (name.compare(0, 10, "initStream") == 0)
    {
        cpu.eax = chance(50) ? 0x1000 * (1 + below(8)) : below(0x8000);
        cpu.edx = chance(80) ? 0x2000 * (1 + below(4)) : 0x100 * below(0x20);
        cpu.ebx = random32();
        cpu.ecx = chance(50) ? 1 : 0;
    }
    else if (name == "deleteStreamStruct" || name == "deleteStream")
        cpu.eax = chance(70) ? kStreamFirst : chance(50) ? kStreamSecond : kStreamThird;
    else if (name == "streamReaderThread")
        g.word(0x5645b8) = kStreamFirst;  // its thread runs while the first stream is
    else if (name == "pathHook")
        cpu.eax = chance(30) ? 0 : below(2000);
    else if (name == "SNDpathinit")
    {
        if (chance(90))
            g.word(0x56465c) = 0;
        cpu.eax = chance(95) ? kPathMap : kSoundArena + below(0x100);
    }
    else if (name == "SNDpathstartstream")
    {
        cpu.eax = aStream();
        cpu.edx = aStreamName(g);
        cpu.ebx = below(2000);
    }
    else if (name == "SNDpathcontrol")
        cpu.eax = aSoundLevel();
    else if (name == "SNDpathevent" || name == "SNDpatheventinterrupt")
    {
        if (name == "SNDpatheventinterrupt")
            liveQueue();
        cpu.eax = chance(90) ? below(events) : x86::reg32(x86::sreg32(below(events + 4)) - 2);
        cpu.edx = below(3);
    }
    return true;
}

void makeSoundArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    makeSoundWorld(g);
    // The x87 as the game has it outside a race: 53 bits, round to nearest
    // (the generated __CHP sets the control word back, the native leaves it).
    cpu.fpu.setControl(0x27f);
    if (makeGameSoundArguments(g, name, cpu, stack) || makeStreamArguments(g, name, cpu, stack)
        || makeStrmArguments(g, name, cpu, stack)
        || makeDriverArguments(g, name, cpu, stack) || makeTimerArguments(g, name, cpu, stack)
        || makeFxArguments(g, name, cpu, stack)
        || makeMixSetupArguments(g, name, cpu, stack) || makeMixFuncArguments(g, name, cpu, stack))
        return;
    const auto anIndex = [] { return chance(95) ? below(16) : below(0x20); };
    const auto aChannel = [&] { return 0x9fbcb4 + 0xde4 * below(16); };
    if (name == "voiceOf" || name == "SNDstop" || name == "SNDstatus" || name == "soundVolume")
        cpu.eax = aSoundHandle(g);
    else if (name == "iSNDfreechan" || name == "updateVoiceVolume" || name == "updateVoicePitch"
             || name == "iSNDmixstop" || name == "iSNDstop")
        cpu.eax = below(16);
    else if (name == "voicePicked")
    {
        cpu.eax = chance(90) ? below(16) : random32();
        cpu.edx = chance(90) ? below(17) : random32() % 0x40;
    }
    else if (name == "iSNDallocchan")
    {
        cpu.eax = chance(50) ? 0xffff : random32();
        cpu.edx = chance(90) ? 1 + below(4) : below(17);
        cpu.ebx = below(0x80);
        cpu.ecx = kSoundOut + 4 * below(0x10);
    }
    else if (name == "iSNDserveradd100hzclient" || name == "iSNDserverremove100hzclient")
        cpu.eax = chance(70) ? g.word(0xa09b0c + 4 * below(6)) : random32();
    else if (name == "randomOffset")
        cpu.eax = chance(80) ? below(0x12000) : random32();
    else if (name == "readBigEndian")
    {
        cpu.eax = kSoundArena + below(0x8000);
        cpu.edx = below(5);
    }
    else if (name == "nextTag")
    {
        // The place, the tag, the number, the data's place: words of the arena's.
        g.word(kSoundOut) = kSoundTags + below(0x80);
        cpu.eax = kSoundOut;
        cpu.edx = kSoundOut + 4;
        cpu.ebx = kSoundOut + 8;
        cpu.ecx = kSoundOut + 12;
    }
    else if (name == "panSplit" || name == "panLaw" || name == "panLawPositive" || name == "panSurround")
    {
        cpu.eax = name == "panSplit" ? aSoundLevel() : chance(80) ? below(0x10000) : random32();
        cpu.edx = aSoundLevel();
        cpu.ebx = kSoundOut + 4 * below(8);
        cpu.ecx = kSoundOut + 0x20 + 4 * below(8);
        stack[0] = chance(70) ? x86::reg32(x86::sreg32(below(0x100)) - 0x80) : random32();
        stack[1] = chance(70) ? x86::reg32(x86::sreg32(below(0x100)) - 0x80) : random32();
    }
    else if (name == "setSendVolume")
        cpu.eax = aChannel();
    else if (name == "setMixVolume" || name == "setSendLevel" || name == "setVoiceSend")
    {
        cpu.eax = below(16);
        cpu.edx = x86::reg32(x86::sreg32(below(0x100)) - 0x80);
        cpu.ebx = x86::reg32(x86::sreg32(below(0x100)) - 0x80);
    }
    else if (name == "iSNDvol" || name == "iSNDpan")
    {
        cpu.eax = below(16);
        cpu.edx = aSoundLevel();
    }
    else if (name == "pitchFactor")
        cpu.eax = chance(90) ? x86::reg32(x86::sreg32(below(0x8000)) - 0x4000) : x86::reg32(x86::sreg32(below(0x20000)) - 0x10000);
    else if (name == "mixStep")
    {
        cpu.eax = chance(50) ? 8000 + below(40000) : below(0x10000);
        cpu.edx = chance(50) ? 11025 + below(40000) : below(0x10000);
        cpu.ebx = chance(50) ? x86::reg32(x86::sreg32(below(0x6000)) - 0x3000) : x86::reg32(x86::sreg32(x86::sreg16(random32())));
    }
    else if (name == "setMixStep")
    {
        cpu.eax = below(16);
        cpu.edx = chance(80) ? below(0x80000) : random32();
    }
    else if (name == "iSNDplatformdetune")
    {
        cpu.eax = below(16);
        cpu.edx = x86::reg32(x86::sreg32(below(0x6000)) - 0x3000);
    }
    else if (name == "iSNDplatform3dpos" || name == "SNDpos3d")
    {
        cpu.eax = name == "SNDpos3d" ? aSoundHandle(g) : below(16);
        cpu.edx = random32();
        cpu.ebx = chance(80) ? x86::reg32(x86::sreg32(below(0x10000)) - 0x8000) : random32();
    }
    else if (name == "SNDautovol")
    {
        cpu.eax = aSoundHandle(g);
        cpu.edx = chance(80) ? below(0x100) : x86::reg32(-x86::sreg32(below(4)));
        cpu.ebx = chance(90) ? below(0x80) : x86::reg32(x86::sreg32(below(8)) - 4);
    }
    else if (name == "setSoundVolume" || name == "SNDvol" || name == "setSoundBend" || name == "SNDpitchbend"
             || name == "SNDpan")
    {
        cpu.eax = aSoundHandle(g);
        cpu.edx = aSoundLevel();
    }
    else if (name == "timbreDefaults")
        cpu.eax = kSoundTimbre;
    else if (name == "resetTimbre" || name == "addTimbreDeltas")
    {
        makeSoundTimbre(g, kSoundTimbre);
        cpu.eax = kSoundTimbre;
        cpu.edx = kSoundTimbre + 0x200;
    }
    else if (name == "iSNDplaytaggedtimbre")
    {
        makeSoundTimbre(g, kSoundTimbre);
        const x86::reg32 options = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
            g.getMemory<x86::reg8>(options + i) = x86::reg8(chance(90) ? below(0x80) : random32());
        makeSoundSample(g, kSoundSamples);
        cpu.edx = kSoundSamples;
        cpu.ebx = options;
        cpu.ecx = kSoundTimbre;
        stack[0] = kSoundTimbre + 0x200;
        stack[1] = below(0x80);
        stack[2] = below(0x80);
        stack[3] = below(0x1000);
    }
    else if (name == "iSNDplaytaggedpatch" || name == "iSNDresolvetaggedpatch" || name == "unresolveTaggedPatch"
             || name == "iSNDextracthdrinfo")
    {
        const x86::reg32 options = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
            g.getMemory<x86::reg8>(options + i) = x86::reg8(chance(90) ? below(0x80) : random32());
        cpu.eax = kSoundPatches + 0x600 * below(8);
        if (name == "iSNDplaytaggedpatch" && chance(3))
            cpu.eax = 0;
        cpu.edx = name == "iSNDplaytaggedpatch" ? options
                : name == "iSNDextracthdrinfo" ? kSoundOut : kSoundArena + below(0x100);
        cpu.ebx = kSoundOut + 0x100;
        // A stream's header now and then: its patch as the streamer has it.
        if (name == "iSNDextracthdrinfo" && chance(40))
            makeStreamHeader(g, cpu.eax);
    }
    else if (name == "bankUsable")
        cpu.eax = chance(90) ? below(0x1a) : random32();
    else if (name == "iSNDbankremovepat" || name == "removeBankPatches")
    {
        cpu.eax = below(24);
        cpu.edx = chance(90) ? below(0x12) : random32() % 0x30;
        cpu.ebx = kSoundOut;
    }
    else if (name == "iSNDdownloadbank" || name == "SNDbankadd")
    {
        const x86::reg32 bank = kSoundBanks + 0x100 * below(0x10);
        makeSoundBank(g, bank, true);
        cpu.eax = name == "SNDbankadd" ? kSoundOut : bank;
        cpu.edx = name == "SNDbankadd" ? bank : kSoundArena + below(0x100);
    }
    else if (name == "iSNDplatformresolve" || name == "platformUnresolve")
    {
        makeSoundSample(g, kSoundSamples);
        cpu.eax = kSoundSamples;
        cpu.edx = name == "platformUnresolve" ? kSoundOut : kSoundArena + below(0x100);
    }
    else if (name == "iSNDmixstart")
    {
        static const x86::reg32 formats[] = {1, 2, 4, 8, 0};
        cpu.eax = below(16);
        // A format the mixer has (none would take a decoder from where the stack left edi).
        cpu.edx = formats[below(4)];
        cpu.ebx = chance(50) ? 0 : chance(40) ? 7 : chance(80) ? 9 : below(0x10);
        cpu.ecx = chance(95) ? below(3) : below(8);
        for (x86::reg32 i = 0; i < 9; ++i)
            stack[i] = random32();
        stack[3] = chance(50) ? 0xffffffff : below(0x1000);
        stack[4] = below(0x80);
        stack[5] = below(0x80);
        stack[6] = chance(80) ? below(0x80000) : random32();
        stack[7] = below(0x64);
        stack[8] = below(0x80);
    }
    else if (name == "iSNDplatformplay")
    {
        makeSoundSample(g, kSoundSamples);
        cpu.eax = kSoundSamples;
        cpu.edx = chance(90) ? below(3) : random32();
        cpu.ebx = below(16);
        cpu.ecx = below(0x80);
        stack[0] = below(0x80);
        stack[1] = x86::reg32(x86::sreg32(below(0x6000)) - 0x3000);
        stack[2] = below(0x80);
        stack[3] = below(0x10000);
        stack[4] = x86::reg32(x86::sreg32(below(0x8000)) - 0x4000);
        stack[5] = chance(50) ? 1 : 0;
    }
    else if (name == "iSNDplatformpacketplay")
    {
        const x86::reg32 sample = kSoundOut + 0x80;
        static const x86::reg16 representations[] = {0, 8, 0xc, 0x10};
        g.getMemory<x86::reg16>(sample) = x86::reg16(chance(70) ? 22050 : 8000 + below(40000));
        g.getMemory<x86::reg16>(sample + 2) =
            x86::reg16((chance(95) ? representations[below(4)] : random32()) | below(4));
        cpu.edx = below(16);
        cpu.ebx = below(0x80);
        cpu.ecx = below(0x80);
        stack[0] = x86::reg32(x86::sreg32(below(0x6000)) - 0x3000);
        stack[1] = below(0x80);
        stack[2] = chance(90) ? below(0x80) : random32();
        stack[3] = sample;
    }
    else if (name == "iSNDcheckplayopts")
    {
        cpu.eax = kSoundPlays + 0x10 * below(0x10);
        for (x86::reg32 i = 0; i < 0x10; ++i)
            g.getMemory<x86::reg8>(cpu.eax + i) = x86::reg8(chance(85) ? below(0x80) : random32());
    }
    else if (name == "SNDbankremove" || name == "removeAllBanks")
        cpu.eax = chance(20) ? 0xffffffff : chance(90) ? below(24) : random32() % 0x30;
    else if (name == "SNDbankheadersize")
        cpu.eax = below(24);
    else if (name == "SNDbankheadercopy")
    {
        cpu.eax = chance(95) ? kSoundOut + 0x400 : 0;
        cpu.edx = below(24);
    }
    else if (name == "SNDbankpatpresent")
    {
        // A bank of the 24: below them the code checks bank 1 and reads the voices as one.
        cpu.eax = below(24);
        // A patch at or past the first: before it the code reads before a bank it never checked.
        cpu.edx = below(0x12);
    }
    else if (name == "SNDmastervol")
        cpu.eax = aSoundLevel();
    else if (name == "SNDplaysetdef" || name == "SNDplay" || name == "playOptions")
    {
        const x86::reg32 options = kSoundPlays + 0x10 * below(0x10);
        g.word(options) = chance(80) ? below(0x20) : random32();
        g.getMemory<x86::reg8>(options + 4) = x86::reg8(below(24));
        cpu.eax = chance(95) ? options : 0;
        cpu.edx = random32();
    }
}
#endif
