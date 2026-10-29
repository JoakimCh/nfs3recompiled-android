#ifndef NFS3HP_PORT_SND_MIXER_H
#define NFS3HP_PORT_SND_MIXER_H

#include "port_snd.h"

/* The mixer of EA's SND library and what starts it, rewritten (port.h says
 * how): the mixer's set-ups for a channel's decoder, volume and resampler, and
 * the tables of them (port_snd_mixsetup.cpp); the effect buses, the reverb's
 * start and the mixer's start (port_snd_fx.cpp); the mix itself, a block of
 * frames of every channel's decoded, resampled and added sound
 * (port_snd_mixer.cpp).  The game's entries are in each file's end. */
namespace nfs3hp
{
namespace port
{

/* The tables of the decoders' set-ups the mixer's start fills, by whether the
 * CPU has MMX (port_snd_mixsetup.cpp).  Without it the first table calls a
 * routine of the plain set (0x522100), which the port does not have. */
Result pickPcmFirstSetups(App* app, CPU& cpu, reg32 esp);
void pickPcmSecondSetups(App* app);
void pickXaSetups(App* app);
void pickLastSetups(App* app);

/* The mix (port_snd_mixer.cpp): `frames` frames mixed into the output at
 * `target`, a block of at most 256 at a time, the game's calls made from the
 * stack at `esp`; the bytes of the last block (`eax` where there was none),
 * as the code leaves them in eax.  And a channel's volume ramped towards its
 * target over at most `frames` frames, each mixed by itself: the frames it
 * took. */
reg32 mixFrames(App* app, CPU& cpu, reg32 esp, reg32 target, int32_t frames, reg32 eax);
reg32 rampChannel(App* app, CPU& cpu, reg32 esp, reg32 channel, reg32 frames);

}  // namespace port
}  // namespace nfs3hp

#endif
