#ifndef NFS3HP_PORT_SHAPES_H
#define NFS3HP_PORT_SHAPES_H

#include "port.h"

/* The game's shapes, rewritten (port.h says how): an FSH shape turned into a
 * texture's pixels -- its alpha scanned, a format the driver takes chosen,
 * its pixels converted and resized into it -- a shape made a texture of its
 * own, the menus' art cut into tiles of 32 pixels and each made a texture,
 * found by its name and drawn a tile at a time; the textures let go of.
 *
 * Each function is here twice: as C++ with arguments and a result, which the
 * others call, and as the game's entry by the name the game's code knows
 * (disassemble_nfs3hp.py's PORT_SHAPES_NATIVES binds its address to it), an
 * adapter around the first.  What they call that is not theirs -- the
 * driver's functions, the game's allocator, its render states, its trace --
 * they call by address, from where the game's stack had it. */
namespace nfs3hp
{
namespace port
{
namespace shapes
{

/* Shape `shape` turned into pixels at `target` + 0x10, the size kept at
 * `target` + 4 and + 6: at most `limit` a side (0 for its own size), in the
 * format at `format` -- kept if the driver takes it and it holds the
 * shape's alpha, else chosen and written there.  `flag` where the
 * converters say whether the pixels have alpha.  `esp` the game's at the
 * call (its return address).  The height. */
Result shapeToPixelsOf(App* app, CPU& cpu, reg32 esp, reg32 target, reg32 shape, reg32 flag, int32_t limit,
                       reg32 format);

/* The menus' shape named at `name` (4 characters): its record, found or made
 * from the menus' art; 0 for none. */
Result shapeNamed(App* app, CPU& cpu, reg32 esp, reg32 name);

/* Art record `record` drawn at `x`, `y` in `colour`, a tile at a time. */
Result drawArt(App* app, CPU& cpu, reg32 esp, int32_t record, int32_t x, int32_t y, reg32 colour);

/* The adapters the 2D drawing calls as the game's code does (port_draw2d.cpp). */
void resetTextures(App* app, CPU& cpu);  // 0x4d5c40
void shapeTexture(App* app, CPU& cpu);   // 0x4d6070

}  // namespace shapes
}  // namespace port
}  // namespace nfs3hp

#endif
