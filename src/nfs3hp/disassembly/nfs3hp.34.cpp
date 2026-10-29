#include "nfs3hp.h"
#include <lib/thread.h>

namespace nfs3hp
{

/* sub_4e4ec0: native, nfs3hp::port::streamOpenQuietly */

/* sub_4e4ee0: native, nfs3hp::port::streamOpenNext */

/* sub_4e4f00: native, nfs3hp::port::streamOpenNextQuietly */

/* sub_4e4f20: native, nfs3hp::port::streamContinue */

/* sub_4e4f40: native, nfs3hp::port::streamContinueQuietly */

/* sub_4e4f60: native, nfs3hp::port::streamSwitch */

/* sub_4e4f80: native, nfs3hp::port::streamSwitchQuietly */

/* sub_4e4fa0: native, nfs3hp::port::streamQueueFile */

/* sub_4e4fc0: native, nfs3hp::port::streamQueueFileQuietly */

/* sub_4e4fe0: native, nfs3hp::port::streamRestart */

/* sub_4e5000: native, nfs3hp::port::streamRestartQuietly */

/* sub_4e5020: native, nfs3hp::port::streamSeek */

/* sub_4e5040: native, nfs3hp::port::streamSeekQuietly */

/* sub_4e5060: native, nfs3hp::port::streamReadOn */

/* sub_4e5080: native, nfs3hp::port::streamReadOnQuietly */

/* sub_4e50a0: native, nfs3hp::port::streamStopAt */

/* sub_4e50c0: native, nfs3hp::port::streamStopAtQuietly */

/* sub_4e50e0: native, nfs3hp::dead::stub_0x4e50e0 */

/* sub_4e5140: native, nfs3hp::dead::stub_0x4e5140 */

/* sub_4e5250: native, nfs3hp::dead::stub_0x4e5250 */

/* sub_4e53c0: native, nfs3hp::port::streamReaderThread */

/* sub_4e6660: native, nfs3hp::port::passFreedChunks */

/* sub_4e66e0: native, nfs3hp::port::roomAhead */

/* sub_4e6710: native, nfs3hp::port::roomToEnd */

/* sub_4e6720: native, nfs3hp::port::roomAtStart */

/* sub_4e6740: native, nfs3hp::port::getStreamChunk */

/* sub_4e68a0: native, nfs3hp::port::freeStreamChunk */

/* sub_4e68c0: native, nfs3hp::port::streamBytesRead */

/* sub_4e68d0: native, nfs3hp::dead::stub_0x4e68d0 */

/* sub_4e68e0: native, nfs3hp::port::readerIdle */

/* sub_4e6910: native, nfs3hp::dead::stub_0x4e6910 */

/* sub_4e6950: native, nfs3hp::port::readerWaits */

/* sub_4e6960: native, nfs3hp::dead::stub_0x4e6960 */

/* sub_4e69a0: native, nfs3hp::dead::stub_0x4e69a0 */

/* sub_4e69c0: native, nfs3hp::dead::stub_0x4e69c0 */

/* sub_4e69e0: native, nfs3hp::port::chainCommandBlocks */

/* sub_4e6a20: native, nfs3hp::port::freeCommandBlock */

/* sub_4e6a70: native, nfs3hp::port::commandBlocksFree */

/* sub_4e6ad0: native, nfs3hp::dead::stub_0x4e6ad0 */

/* sub_4e6b30: native, nfs3hp::port::takeCommandBlock */

/* sub_4e6be0: native, nfs3hp::port::pathStep */

/* sub_4e6d68: native, nfs3hp::port::pathTask */

/* sub_4e6d94: native, nfs3hp::port::pathHook */

/* sub_4e6dc8: native, nfs3hp::port::SNDpathinit */

/* sub_4e6f0c: native, nfs3hp::port::SNDpathstartstream */

/* sub_4e705c: native, nfs3hp::port::SNDpathcontrol */

/* sub_4e70fc: native, nfs3hp::port::SNDpathevent */

/* sub_4e7208: native, nfs3hp::port::SNDpatheventinterrupt */

/* sub_4e7388: native, nfs3hp::port::SNDpathrestore */

/* sub_4e73d0: native, nfs3hp::port::SNDmastervol */

/* sub_4e7470: native, nfs3hp::port::SNDstreamautovol */

/* sub_4e74f0: native, nfs3hp::port::SNDstreamgetvol */

/* sub_4e7520: native, nfs3hp::port::addSystemTask */

/* sub_4e75e0: native, nfs3hp::port::removeSystemTask */

/* sub_4e7630: native, nfs3hp::port::runSystemTasks */

/* sub_4e7720: native, nfs3hp::port::waitSystemTasks */

/* sub_4e7750: native, nfs3hp::port::SNDstreamsetup */

/* sub_4e784c: native, nfs3hp::port::SNDstreamrestore */

/* sub_4e78a0: native, nfs3hp::port::SNDstreamqueue */

/* sub_4e7a14: native, nfs3hp::port::SNDstreaminterrupt */

/* sub_4e7b28: native, nfs3hp::port::SNDstreampurge */

/* sub_4e7c58: native, nfs3hp::port::SNDstreamchunksleft */

/* sub_4e7ce0: native, nfs3hp::port::SNDstreambuftime */

/* sub_4e7dd0: native, nfs3hp::port::streamToppedUp */

/* sub_4e7df4: native, nfs3hp::port::iSNDstreamchecktopup */

/* sub_4e7e98: native, nfs3hp::port::iSNDstreamsetbuftime */

/* sub_4e7f30: native, nfs3hp::port::parseStreamChunk */

/* sub_4e7ff8: native, nfs3hp::port::dropQueuedChunks */

/* sub_4e8078: native, nfs3hp::port::queueDataChunk */

/* sub_4e80cc: native, nfs3hp::port::iSNDparseheader */

/* sub_4e8258: native, nfs3hp::port::queueLoopChunk */

/* sub_4e82c4: native, nfs3hp::port::streamSeekChunk */

/* sub_4e82ec: native, nfs3hp::port::streamEndChunk */

/* sub_4e8320: native, nfs3hp::port::streamEndsSeen */

/* sub_4e8328: native, nfs3hp::port::nextStreamChunk */

/* sub_4e85a8: native, nfs3hp::port::iSNDstreamservice */

/* sub_4e8944: native, nfs3hp::port::resetStreamer */

/* sub_4e89f8: native, nfs3hp::port::iSNDstreamstart */

/* sub_4e8b60: native, nfs3hp::port::SNDstreamvol */

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
