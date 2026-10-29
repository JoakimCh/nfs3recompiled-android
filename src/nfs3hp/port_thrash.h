#ifndef NFS3HP_PORT_THRASH_H
#define NFS3HP_PORT_THRASH_H

#include "port.h"

#include <vector>

/* The THRASH driver, the Voodoo2's (voodoo2a.dll), as the port's own C++
 * (port_thrash.cpp): the game's 34 THRASH_* calls, which
 * disassemble_nfs3hp.py binds, drawing straight through ThrashRenderer
 * (lib/thrashrenderer.h) -- no Glide under it, no DirectDraw, no Win32.  What
 * the game sees of the driver stays where voodoo2a has it: its descriptor and
 * mode table, its records and its variables, at their addresses in the DLL's
 * data.
 *
 * Here, besides, what the game layer (nfs3hp_main.cpp) asks of the picture
 * the driver draws. */
namespace nfs3hp
{
namespace port
{
namespace driver
{

/* A vertex as Glide had it: what the native vertex checks (NFS_NATIVE_CHECK,
 * native_vertices.cpp) trace of what the game hands the driver -- the fields
 * voodoo2a set, the others 0. */
struct GrTmuVertex
{
    float sow;
    float tow;
    float oow;
};

struct GrVertex
{
    float x, y, z;
    float r, g, b;
    float ooz;
    float a;
    float oow;
    GrTmuVertex tmuvtx[2];
};

/* While set, every triangle the driver draws is also appended here, three
 * vertices each, as the game's vertices made them; a line as its two ends and
 * the second again. */
void traceTriangles(std::vector<GrVertex>* trace);
/* Whether a trace is being taken: a check nested in another must not take it
 * over. */
bool tracingTriangles();

/* Called on the game thread after every buffer swap, with the guest context
 * held, so the game layer can look at the game's state once a frame.  One
 * observer; null removes it. */
using SwapObserver = void (*)(App* app);
void setSwapObserver(SwapObserver observer);

/* Where the game's picture sits inside the window, in window pixels, and the
 * size of the picture itself: the letterbox rectangle the frame is shown in,
 * which turns a touch on the screen into a pixel of the game.  False while no
 * window is open. */
bool screenRect(int& x, int& y, int& w, int& h, int& pictureWidth, int& pictureHeight);

/* 4:3 in the middle of a wider picture: while on, everything the game draws is
 * squeezed sideways into the 4:3 rectangle centred on the picture, as it would
 * have been drawn on a 4:3 screen.  For a screen the game only knows how to
 * stretch.  No effect on a picture no wider than 4:3. */
void fitFourThree(bool on);

/* While on, every triangle is narrowed by the same factor towards its own left
 * corner: a picture of its own, like a dialog's emblem, keeps its shape on a
 * wide screen while everything around it stays as the game stretched it. */
void squeezeToLeft(bool on);

/* The whole picture black, whatever clip window the game has set: the bars
 * beside a 4:3 rectangle, before it is drawn. */
void clearPicture(App* app, CPU& cpu);

/* Screen resolutions the Voodoo2 never had: the ids the game layer puts in the
 * driver's mode table, beside Glide's GR_RESOLUTION_* ids, and
 * THRASH_setvideomode opens.  Above every one of Glide 2's and 3's. */
constexpr reg32 kResolution1280x720 = 0x80;
constexpr reg32 kResolution1600x900 = 0x81;
constexpr reg32 kResolution1920x1080 = 0x82;
/* Dynamic Fullscreen: a size the game layer works out from the screen it runs
 * on and sets (setDynamicResolution) before the window opens. */
constexpr reg32 kResolutionDynamic = 0x83;
void setDynamicResolution(reg32 width, reg32 height);

/* A texture format the Voodoo2 never had: eight bits a channel, numbered as
 * Glide 3 numbers it for the Voodoo 4 and 5 (GR_TEXFMT_ARGB_8888), each texel
 * a little-endian 0xAARRGGBB.  THRASH_about maps the game's 32-bit format to
 * it (tools/apply_full_colour.py), and the texels reach the renderer as they
 * are.  Offered unless NFS_TEXTURES32 is 0 (fullColourTextures). */
constexpr reg32 kTexFmtArgb8888 = 0x12;
bool fullColourTextures();

}  // namespace driver
}  // namespace port
}  // namespace nfs3hp

#endif
