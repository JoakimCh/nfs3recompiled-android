#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_4e4ec0: native, nfs3hp::snd::streamOpenQuietly */

/* sub_4e4ee0: native, nfs3hp::snd::streamOpenNext */

/* sub_4e4f00: native, nfs3hp::snd::streamOpenNextQuietly */

/* sub_4e4f20: native, nfs3hp::snd::streamContinue */

/* sub_4e4f40: native, nfs3hp::snd::streamContinueQuietly */

/* sub_4e4f60: native, nfs3hp::snd::streamSwitch */

/* sub_4e4f80: native, nfs3hp::snd::streamSwitchQuietly */

/* sub_4e4fa0: native, nfs3hp::snd::streamQueueFile */

/* sub_4e4fc0: native, nfs3hp::snd::streamQueueFileQuietly */

/* sub_4e4fe0: native, nfs3hp::snd::streamRestart */

/* sub_4e5000: native, nfs3hp::snd::streamRestartQuietly */

/* sub_4e5020: native, nfs3hp::snd::streamSeek */

/* sub_4e5040: native, nfs3hp::snd::streamSeekQuietly */

/* sub_4e5060: native, nfs3hp::snd::streamReadOn */

/* sub_4e5080: native, nfs3hp::snd::streamReadOnQuietly */

/* sub_4e50a0: native, nfs3hp::snd::streamStopAt */

/* sub_4e50c0: native, nfs3hp::snd::streamStopAtQuietly */

/* sub_4e50e0: native, nfs3hp::dead::stub_0x4e50e0 */

/* sub_4e5140: native, nfs3hp::dead::stub_0x4e5140 */

/* sub_4e5250: native, nfs3hp::dead::stub_0x4e5250 */

/* sub_4e53c0: native, nfs3hp::snd::streamReaderThread */

/* sub_4e6660: native, nfs3hp::snd::passFreedChunks */

/* sub_4e66e0: native, nfs3hp::snd::roomAhead */

/* sub_4e6710: native, nfs3hp::snd::roomToEnd */

/* sub_4e6720: native, nfs3hp::snd::roomAtStart */

/* sub_4e6740: native, nfs3hp::snd::getStreamChunk */

/* sub_4e68a0: native, nfs3hp::snd::freeStreamChunk */

/* sub_4e68c0: native, nfs3hp::snd::streamBytesRead */

/* sub_4e68d0: native, nfs3hp::dead::stub_0x4e68d0 */

/* sub_4e68e0: native, nfs3hp::snd::readerIdle */

/* sub_4e6910: native, nfs3hp::dead::stub_0x4e6910 */

/* sub_4e6950: native, nfs3hp::snd::readerWaits */

/* sub_4e6960: native, nfs3hp::dead::stub_0x4e6960 */

/* sub_4e69a0: native, nfs3hp::dead::stub_0x4e69a0 */

/* sub_4e69c0: native, nfs3hp::dead::stub_0x4e69c0 */

/* sub_4e69e0: native, nfs3hp::snd::chainCommandBlocks */

/* sub_4e6a20: native, nfs3hp::snd::freeCommandBlock */

/* sub_4e6a70: native, nfs3hp::snd::commandBlocksFree */

/* sub_4e6ad0: native, nfs3hp::dead::stub_0x4e6ad0 */

/* sub_4e6b30: native, nfs3hp::snd::takeCommandBlock */

/* sub_4e6be0: native, nfs3hp::snd::pathStep */

/* sub_4e6d68: native, nfs3hp::snd::pathTask */

/* sub_4e6d94: native, nfs3hp::snd::pathHook */

/* sub_4e6dc8: native, nfs3hp::snd::SNDpathinit */

/* sub_4e6f0c: native, nfs3hp::snd::SNDpathstartstream */

/* sub_4e705c: native, nfs3hp::snd::SNDpathcontrol */

/* sub_4e70fc: native, nfs3hp::snd::SNDpathevent */

/* sub_4e7208: native, nfs3hp::snd::SNDpatheventinterrupt */

/* sub_4e7388: native, nfs3hp::snd::SNDpathrestore */

/* sub_4e73d0: native, nfs3hp::port::SNDmastervol */

/* sub_4e7470: native, nfs3hp::snd::SNDstreamautovol */

/* sub_4e74f0: native, nfs3hp::snd::SNDstreamgetvol */

/* sub_4e7520: native, nfs3hp::snd::addSystemTask */

/* sub_4e75e0: native, nfs3hp::snd::removeSystemTask */

/* sub_4e7630: native, nfs3hp::snd::runSystemTasks */

/* sub_4e7720: native, nfs3hp::snd::waitSystemTasks */

/* sub_4e7750: native, nfs3hp::snd::SNDstreamsetup */

/* sub_4e784c: native, nfs3hp::snd::SNDstreamrestore */

/* sub_4e78a0: native, nfs3hp::snd::SNDstreamqueue */

/* sub_4e7a14: native, nfs3hp::snd::SNDstreaminterrupt */

/* sub_4e7b28: native, nfs3hp::snd::SNDstreampurge */

/* sub_4e7c58: native, nfs3hp::snd::SNDstreamchunksleft */

/* sub_4e7ce0: native, nfs3hp::snd::SNDstreambuftime */

/* sub_4e7dd0: native, nfs3hp::snd::streamToppedUp */

/* sub_4e7df4: native, nfs3hp::snd::iSNDstreamchecktopup */

/* sub_4e7e98: native, nfs3hp::snd::iSNDstreamsetbuftime */

/* sub_4e7f30: native, nfs3hp::snd::parseStreamChunk */

/* sub_4e7ff8: native, nfs3hp::snd::dropQueuedChunks */

/* sub_4e8078: native, nfs3hp::snd::queueDataChunk */

/* sub_4e80cc: native, nfs3hp::snd::iSNDparseheader */

/* sub_4e8258: native, nfs3hp::snd::queueLoopChunk */

/* sub_4e82c4: native, nfs3hp::snd::streamSeekChunk */

/* sub_4e82ec: native, nfs3hp::snd::streamEndChunk */

/* sub_4e8320: native, nfs3hp::snd::streamEndsSeen */

/* sub_4e8328: native, nfs3hp::snd::nextStreamChunk */

/* sub_4e85a8: native, nfs3hp::snd::iSNDstreamservice */

/* sub_4e8944: native, nfs3hp::snd::resetStreamer */

/* sub_4e89f8: native, nfs3hp::snd::iSNDstreamstart */

/* sub_4e8b60: native, nfs3hp::snd::SNDstreamvol */

/* sub_4e8bd0: native, nfs3hp::port::removeBankPatches */

/* sub_4e8c1c: native, nfs3hp::port::removeAllBanks */

/* sub_4e8c28: native, nfs3hp::port::SNDbankremove */

/* sub_4e8d20: native, nfs3hp::port::SNDbankadd */

/* sub_4e8db0: native, nfs3hp::port::SNDbankheadersize */

/* sub_4e8e20: native, nfs3hp::port::SNDbankheadercopy */

/* sub_4e8f28: native, nfs3hp::port::SNDangle */

/* sub_4e8fd0: native, nfs3hp::port::SNDstatus */

/* sub_4e9010: native, nfs3hp::port::SNDstopall */

/* sub_4e9030: native, nfs3hp::watcom::update_buffer */

/* sub_4e9070: native, nfs3hp::watcom::reset_buffer */

/* sub_4e9088: native, nfs3hp::watcom::fseek */

/* sub_4e9200: native, nfs3hp::watcom::fread */

/* sub_4e9420: native, nfs3hp::port::SNDautovol */

/* sub_4e9540: native, nfs3hp::port::setSoundVolume */

/* sub_4e95fc: native, nfs3hp::port::SNDvol */

/* sub_4e9670: native, nfs3hp::port::SNDstop */

/* sub_4e9710: native, nfs3hp::port::setSoundBend */

/* sub_4e97e4: native, nfs3hp::port::SNDpitchbend */

/* sub_4e9850: native, nfs3hp::port::SNDpos3d */

/* sub_4e9950: native, nfs3hp::port::SNDpan */

}
