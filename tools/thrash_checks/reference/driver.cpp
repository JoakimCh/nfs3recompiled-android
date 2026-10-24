/* tools/thrash_checks' reference: src/nfs3hp/native_thrash.cpp as it was
 * before the driver became the port's own (port_thrash.cpp), frozen -- the
 * native voodoo2a, every export the port had, drawing through the port's
 * Glide (glide2x.cpp beside this).  Changed only where it has to be to build
 * beside the new driver: its namespace, the GrVertex it takes from
 * port_thrash.h, its unused ThrashRenderer::Corner, its NFS_THRASH_GL. */
#include <lib/winapp.h>
#include "native_thrash.h"
#include "port_thrash.h"
#include "thrash.h"
#include <lib/thrashrenderer.h>
#include "glide2x.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <cstring>
#include <initializer_list>

/* A product rounded to float straight from a fused multiply-add would round
 * once where voodoo2a's code rounds twice. */
#if defined(__clang__)
#pragma clang fp contract(off)
#elif defined(_MSC_VER)
#pragma fp_contract(off)
#endif

/* voodoo2a, the port's THRASH driver, in C++: all 34 of its exports (THRASH_*
 * at the end, which disassemble_nfs3hp.py binds them to), with voodoo2a's own
 * state in guest memory, where the game may read it, and its heap native
 * beside them (native_watcom_heap.cpp).  None of voodoo2a's code is generated;
 * tools/thrash_checks generates it afresh from the DLL and holds every export
 * against it.
 *
 * THRASH is the game's interface to its renderer DLLs -- voodoo2a, softtria and
 * the Direct3D one -- called through the pointers THRASH_opendll got from
 * GetProcAddress (native_game.cpp).  The game was built against all of them, so it relies on what
 * a stdcall function promises and nothing more: the stack cleaned up, ebx, esi,
 * edi and ebp kept, a result in eax where there is one.  That is what these keep,
 * and what tools/thrash_checks compares, with every call they make; the scratch
 * registers and flags voodoo2a happened to leave are nobody's business. */

namespace reference
{

namespace thrash = nfs3hp::thrash;
using nfs3hp::thrashMalloc;
using nfs3hp::thrashFree;

void thrashVertex(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale, win32::GrVertex& out);
void thrashBatchVertex(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale, win32::ThrashVertex& out);

namespace
{

/* voodoo2a's data, at its load address (RVA + 0xa82200). */
constexpr x86::reg32 kColourTable = 0xa93210;  // a colour byte as the float Glide takes, 256 of them
constexpr x86::reg32 kDepthScale = 0xa9235c;   // z to Glide's ooz
constexpr x86::reg32 kTexelScale = 0xa92358;   // w to the scale of s and t
/* The Glide entry points voodoo2a looked up (sub_a83220), and the ones its
 * drawing goes through: sub_a848e0 points these at the plain ones, or at its
 * two-pass and antialiased wrappers, as THRASH_setstate asks. */
constexpr x86::reg32 kGrDrawTriangle = 0xa936a8;
constexpr x86::reg32 kGrDrawLine = 0xa936ac;
constexpr x86::reg32 kTriangleDraw = 0xa93710;  // THRASH_drawtri, _drawtrimesh, _drawtrifan
constexpr x86::reg32 kQuadDraw = 0xa9370c;      // THRASH_drawquad, _drawquadmesh, two triangles each
constexpr x86::reg32 kLineDraw = 0xa93610;      // THRASH_drawline, _drawlinemesh
/* The game's vertex: x, y, z, w; colour bytes b, g, r, a at +0x10; u, v at +0x18. */
constexpr x86::reg32 kVertexSize = 0x20;

x86::reg32 at(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg32>(address);
}

bool drawsThrough(win32::WinApplication* app, x86::reg32 pointer, x86::reg32 plain)
{
    const x86::reg32 target = at(app, pointer);
    return target != 0 && target == at(app, plain);
}

void put(win32::WinApplication* app, x86::reg32 address, x86::reg32 value)
{
    app->getMemory<x86::reg32>(address) = value;
}

float asFloat(x86::reg32 bits)
{
    float value;
    std::memcpy(&value, &bits, sizeof value);
    return value;
}

/* What voodoo2a's drawing pointers hold besides Glide's own triangle and line
 * (drawPointers): its wrappers, which draw through the pointers after them. */
constexpr x86::reg32 kTwoPassTriangle = 0xa83930;  // sub_a83930: a triangle in two passes, through kPassTriangle
constexpr x86::reg32 kTwoPassQuad = 0xa839b0;      // sub_a839b0: half a quad in two passes, through kPassQuad
constexpr x86::reg32 kNoLine = 0xa83a30;           // sub_a83a30, a bare ret 8: no lines in two passes
constexpr x86::reg32 kSmoothTriangle = 0xa83a40;   // sub_a83a40: grAADrawTriangle, every edge smoothed
constexpr x86::reg32 kSmoothQuadHalf = 0xa83a60;   // sub_a83a60: all but the edge c a, a quad's diagonal
constexpr x86::reg32 kPassTriangle = 0xa93708;
constexpr x86::reg32 kPassQuad = 0xa93700;
/* Glide's functions voodoo2a's drawing calls straight from its table. */
constexpr x86::reg32 kGrLfbWriteRegion = 0xa936a0;
constexpr x86::reg32 kGrDrawPoint = 0xa936b0;
constexpr x86::reg32 kGrAADrawTriangle = 0xa936e0;

/* A GrVertex where voodoo2a's code builds one: the fields it sets, and only
 * those. */
void putVertex(win32::WinApplication* app, x86::reg32 to, const win32::GrVertex& v)
{
    const struct { x86::reg32 offset; float value; } fields[] = {
        { 0x00, v.x }, { 0x04, v.y }, { 0x0c, v.r }, { 0x10, v.g }, { 0x14, v.b }, { 0x18, v.ooz },
        { 0x1c, v.a }, { 0x20, v.oow }, { 0x24, v.tmuvtx[0].sow }, { 0x28, v.tmuvtx[0].tow },
    };
    for (const auto& field : fields)
        app->getMemory<float>(to + field.offset) = field.value;
}

/* A call voodoo2a's drawing makes to what has no native way here -- Glide's
 * antialiased triangle and line and its point, which the port's Glide does not
 * draw, or a pointer the game set itself: the vertices on the guest stack below
 * esp, as voodoo2a has them on its own, their addresses pushed, then `more`.
 * False when the game stopped in it. */
bool guestDraw(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 target,
               std::initializer_list<const win32::GrVertex*> vertices, std::initializer_list<x86::reg32> more = {})
{
    const x86::reg32 esp = cpu.esp;
    x86::reg32 vertex = esp - 0x3c * x86::reg32(vertices.size());
    x86::reg32 slot = vertex - 4 * x86::reg32(vertices.size() + more.size());
    cpu.esp = slot - 4;
    for (const win32::GrVertex* v : vertices)
    {
        putVertex(app, vertex, *v);
        put(app, slot, vertex);
        vertex += 0x3c;
        slot += 4;
    }
    for (const x86::reg32 argument : more)
    {
        put(app, slot, argument);
        slot += 4;
    }
    app->dynamic_call(target, cpu);
    cpu.esp = esp;
    return !cpu.terminate;
}

/* A triangle to what one of the drawing's pointers holds, as voodoo2a's call
 * through it draws it.  False when the game stopped. */
bool triangleThrough(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 target, const win32::GrVertex& a,
                     const win32::GrVertex& b, const win32::GrVertex& c)
{
    namespace gl = win32::glide2x::direct;
    if (target != 0 && target == at(app, kGrDrawTriangle))
    {
        win32::glide2x::drawTriangle(&a, &b, &c);
        return true;
    }
    switch (target)
    {
    case kTwoPassTriangle:
    case kTwoPassQuad:
    {
        // Trilinear mipmapping in two passes (THRASH_setstate 0xb): the
        // texture weighted by its LOD fraction, then by one less it, added on.
        const x86::reg32 pass = target == kTwoPassTriangle ? kPassTriangle : kPassQuad;
        gl::alphaBlendFunction(app, cpu, 4, 0, 0, 0);
        gl::texCombine(app, cpu, 0, 9, 5, 9, 5, 0, 0);
        if (!triangleThrough(app, cpu, at(app, pass), a, b, c))
            return false;
        gl::alphaBlendFunction(app, cpu, 4, 4, 0, 0);
        gl::texCombine(app, cpu, 0, 9, 0xd, 9, 0xd, 0, 0);
        return triangleThrough(app, cpu, at(app, pass), a, b, c);
    }
    case kSmoothTriangle:
    case kSmoothQuadHalf:
        return guestDraw(app, cpu, at(app, kGrAADrawTriangle), { &a, &b, &c },
                         { 1, 1, target == kSmoothTriangle ? 1u : 0u });
    default:
        return guestDraw(app, cpu, target, { &a, &b, &c });
    }
}

/* A line likewise: Glide's own, nothing in two passes, or a call --
 * grAADrawLine among them. */
bool lineThrough(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 target, const win32::GrVertex& a,
                 const win32::GrVertex& b)
{
    if (target != 0 && target == at(app, kGrDrawLine))
    {
        win32::glide2x::drawLine(&a, &b);
        return true;
    }
    if (target == kNoLine)
        return true;
    return guestDraw(app, cpu, target, { &a, &b });
}

/* The game's vertices as Glide's, with the two scales read once per call --
 * or, while ThrashRenderer may take them as they are (`direct`) and the
 * triangles go to Glide's own grDrawTriangle, straight into its batch, with no
 * GrVertex and no trip through glide2x between. */
struct Vertices
{
    win32::WinApplication* app;
    float zScale;
    float wScale;
    win32::ThrashRenderer* direct;

    explicit Vertices(win32::WinApplication* app)
        :   app(app)
        ,   zScale(app->getMemory<float>(kDepthScale))
        ,   wScale(app->getMemory<float>(kTexelScale))
        ,   direct(win32::glide2x::direct::thrashRenderer())
    {
    }

    win32::GrVertex operator()(x86::reg32 in) const
    {
        win32::GrVertex out = {};
        thrashVertex(app, in, zScale, wScale, out);
        return out;
    }

    /* Whether triangles drawn through `slot` may go into the batch. */
    bool batched(x86::reg32 slot) const
    {
        return direct && drawsThrough(app, slot, kGrDrawTriangle);
    }

    void batch(const win32::ThrashVertex& a, const win32::ThrashVertex& b, const win32::ThrashVertex& c) const
    {
        win32::ThrashVertex* out = direct->reserveTriangle();
        out[0] = a;
        out[1] = b;
        out[2] = c;
        direct->finishTriangle(out);
    }

    void batch(x86::reg32 in, win32::ThrashVertex& out) const
    {
        thrashBatchVertex(app, in, zScale, wScale, out);
    }

    /* The triangle a b c to Glide's own grDrawTriangle. */
    void plainTriangle(x86::reg32 a, x86::reg32 b, x86::reg32 c) const
    {
        if (direct)
        {
            win32::ThrashVertex* out = direct->reserveTriangle();
            batch(a, out[0]);
            batch(b, out[1]);
            batch(c, out[2]);
            direct->finishTriangle(out);
            return;
        }
        const win32::GrVertex vertices[3] = { (*this)(a), (*this)(b), (*this)(c) };
        win32::glide2x::drawTriangle(&vertices[0], &vertices[1], &vertices[2]);
    }

    /* The triangle a b c through the pointer at `slot`.  False when the game
     * stopped. */
    bool triangle(x86::CPU& cpu, x86::reg32 slot, x86::reg32 a, x86::reg32 b, x86::reg32 c) const
    {
        if (batched(slot))
        {
            plainTriangle(a, b, c);
            return true;
        }
        const win32::GrVertex va = (*this)(a), vb = (*this)(b), vc = (*this)(c);
        return triangleThrough(app, cpu, at(app, slot), va, vb, vc);
    }

    /* Triangles a b c and c d a, as Glide's quads go, each through kQuadDraw. */
    bool quad(x86::CPU& cpu, x86::reg32 a, x86::reg32 b, x86::reg32 c, x86::reg32 d) const
    {
        if (batched(kQuadDraw))
        {
            // the four once; each triangle's slots copied from them before rebasing
            win32::ThrashVertex v[4];
            batch(a, v[0]);
            batch(b, v[1]);
            batch(c, v[2]);
            batch(d, v[3]);
            batch(v[0], v[1], v[2]);
            batch(v[2], v[3], v[0]);
            return true;
        }
        const win32::GrVertex va = (*this)(a), vb = (*this)(b), vc = (*this)(c), vd = (*this)(d);
        return triangleThrough(app, cpu, at(app, kQuadDraw), va, vb, vc)
            && triangleThrough(app, cpu, at(app, kQuadDraw), vc, vd, va);
    }
};

/* THRASH_drawtri(a, b, c). */
void drawTriNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const Vertices convert(app);
    if (!convert.triangle(cpu, kTriangleDraw, at(app, esp + 4), at(app, esp + 8), at(app, esp + 0xc)))
        return;
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_drawquad(a, b, c, d): triangles a b c and c d a. */
void drawQuadNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const Vertices convert(app);
    if (!convert.quad(cpu, at(app, esp + 4), at(app, esp + 8), at(app, esp + 0xc), at(app, esp + 0x10)))
        return;
    cpu.esp = esp + 4 + 0x10;
}

/* THRASH_drawquadmesh(count, vertices, quads): each quad four vertex indices,
 * drawn as THRASH_drawquad draws its four. */
void drawQuadMeshNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    x86::reg32 quad = at(app, esp + 0xc);
    const Vertices convert(app);
    for (x86::sreg32 i = 0; i < count; ++i, quad += 0x10)
        if (!convert.quad(cpu, vertices + (at(app, quad) << 5), vertices + (at(app, quad + 4) << 5),
                          vertices + (at(app, quad + 8) << 5), vertices + (at(app, quad + 0xc) << 5)))
            return;
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_drawtrimesh(count, vertices, triangles): three indices each. */
void drawTriMeshNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    x86::reg32 triangle = at(app, esp + 0xc);
    const Vertices convert(app);
    for (x86::sreg32 i = 0; i < count; ++i, triangle += 0xc)
        if (!convert.triangle(cpu, kTriangleDraw, vertices + (at(app, triangle) << 5),
                              vertices + (at(app, triangle + 4) << 5), vertices + (at(app, triangle + 8) << 5)))
            return;
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_drawtrifan(count, vertices): count triangles around the first vertex,
 * the n-th of it, n + 1 and n + 2. */
void drawTriFanNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    const Vertices convert(app);
    if (count > 0 && convert.batched(kTriangleDraw))
    {
        win32::ThrashVertex centre, previous, next;
        convert.batch(vertices, centre);
        convert.batch(vertices + kVertexSize, previous);
        for (x86::sreg32 i = 0; i < count; ++i)
        {
            convert.batch(vertices + x86::reg32(i + 2) * kVertexSize, next);
            convert.batch(centre, previous, next);
            previous = next;
        }
    }
    else if (count > 0)
    {
        const win32::GrVertex centre = convert(vertices);
        win32::GrVertex previous = convert(vertices + kVertexSize);
        for (x86::sreg32 i = 0; i < count; ++i)
        {
            const win32::GrVertex next = convert(vertices + x86::reg32(i + 2) * kVertexSize);
            if (!triangleThrough(app, cpu, at(app, kTriangleDraw), centre, previous, next))
                return;
            previous = next;
        }
    }
    cpu.esp = esp + 4 + 8;
}

/* THRASH_drawtristrip(count, vertices): count triangles along the strip, the
 * n-th of vertices n, n + 1 and n + 2 -- every other one n, n + 2, n + 1, all
 * of them wound the same way.  voodoo2a's loop draws six at a time and keeps
 * where the next six start in the argument, which it leaves there. */
void drawTriStripNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    const Vertices convert(app);
    if (count > 0 && convert.batched(kTriangleDraw))
    {
        for (x86::sreg32 i = 0; i < count; ++i)
        {
            const x86::reg32 first = vertices + x86::reg32(i) * kVertexSize;
            const x86::reg32 second = first + kVertexSize, third = second + kVertexSize;
            if (i & 1)
                convert.plainTriangle(first, third, second);
            else
                convert.plainTriangle(first, second, third);
        }
        if (count >= 6)
            put(app, esp + 8, vertices + x86::reg32(count / 6) * 6 * kVertexSize);
    }
    else if (count > 0)
    {
        win32::GrVertex first = convert(vertices);
        win32::GrVertex second = convert(vertices + kVertexSize);
        for (x86::sreg32 i = 0; i < count; ++i)
        {
            const win32::GrVertex next = convert(vertices + x86::reg32(i + 2) * kVertexSize);
            const x86::reg32 target = at(app, kTriangleDraw);
            if (!((i & 1) ? triangleThrough(app, cpu, target, first, next, second)
                          : triangleThrough(app, cpu, target, first, second, next)))
                return;
            if (i % 6 == 5)
                put(app, esp + 8, vertices + x86::reg32(i + 1) * kVertexSize);
            first = second;
            second = next;
        }
    }
    cpu.esp = esp + 4 + 8;
}

/* THRASH_drawline(a, b). */
void drawLineNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const Vertices convert(app);
    const win32::GrVertex a = convert(at(app, esp + 4));
    const win32::GrVertex b = convert(at(app, esp + 8));
    if (!lineThrough(app, cpu, at(app, kLineDraw), a, b))
        return;
    cpu.esp = esp + 4 + 8;
}

/* THRASH_drawlinemesh(count, vertices, lines): two indices each. */
void drawLineMeshNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    x86::reg32 line = at(app, esp + 0xc);
    const Vertices convert(app);
    for (x86::sreg32 i = 0; i < count; ++i, line += 8)
    {
        const win32::GrVertex a = convert(vertices + (at(app, line) << 5));
        const win32::GrVertex b = convert(vertices + (at(app, line + 4) << 5));
        if (!lineThrough(app, cpu, at(app, kLineDraw), a, b))
            return;
    }
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_drawlinestrip(count, vertices): count lines, the n-th from vertex n
 * to n + 1. */
void drawLineStripNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    const Vertices convert(app);
    if (count > 0)
    {
        win32::GrVertex from = convert(vertices);
        for (x86::sreg32 i = 0; i < count; ++i)
        {
            const win32::GrVertex to = convert(vertices + x86::reg32(i + 1) * kVertexSize);
            if (!lineThrough(app, cpu, at(app, kLineDraw), from, to))
                return;
            from = to;
        }
    }
    cpu.esp = esp + 4 + 8;
}

/* THRASH_drawpoint(vertex): Glide's point, from voodoo2a's table. */
void drawPointNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const Vertices convert(app);
    const win32::GrVertex v = convert(at(app, esp + 4));
    if (!guestDraw(app, cpu, at(app, kGrDrawPoint), { &v }))
        return;
    cpu.esp = esp + 4 + 4;
}

/* THRASH_drawpointmesh(count, vertices, points): an index each. */
void drawPointMeshNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    x86::reg32 point = at(app, esp + 0xc);
    const Vertices convert(app);
    for (x86::sreg32 i = 0; i < count; ++i, point += 4)
    {
        const win32::GrVertex v = convert(vertices + (at(app, point) << 5));
        if (!guestDraw(app, cpu, at(app, kGrDrawPoint), { &v }))
            return;
    }
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_drawpointstrip(count, vertices): count points, one a vertex. */
void drawPointStripNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::sreg32 count = x86::sreg32(at(app, esp + 4));
    const x86::reg32 vertices = at(app, esp + 8);
    const Vertices convert(app);
    for (x86::sreg32 i = 0; i < count; ++i)
    {
        const win32::GrVertex v = convert(vertices + x86::reg32(i) * kVertexSize);
        if (!guestDraw(app, cpu, at(app, kGrDrawPoint), { &v }))
            return;
    }
    cpu.esp = esp + 4 + 8;
}

/* sub_a848e0: what voodoo2a's drawing goes through, from the two-pass flag
 * ([0xa91f24], THRASH_setstate 0xb) and the antialiasing one ([0xa91f20],
 * state 9) -- Glide's own triangle and line, its antialiased ones behind small
 * wrappers, or the two-pass wrappers. */
void drawPointers(win32::WinApplication* app, x86::reg32 twoPass, x86::reg32 antialiased)
{
    x86::reg32 triangle, line, quad;
    if (antialiased == 0)
    {
        triangle = at(app, kGrDrawTriangle);
        line = at(app, kGrDrawLine);
        quad = triangle;
    }
    else
    {
        quad = 0xa83a60;
        triangle = 0xa83a40;
        line = at(app, 0xa936e4);  // grAADrawLine
    }
    x86::reg32 lineDraw = line;
    if (twoPass == 0)
    {
        put(app, kTriangleDraw, triangle);
        put(app, kQuadDraw, quad);
    }
    else
    {
        put(app, kTriangleDraw, 0xa83930);
        put(app, kQuadDraw, 0xa839b0);
        lineDraw = 0xa83a30;  // ret 8: no lines in two passes
    }
    put(app, kLineDraw, lineDraw);
    put(app, 0xa93708, triangle);
    put(app, 0xa93704, line);
    put(app, 0xa93700, quad);
}

constexpr x86::reg32 kTextures = 0xa91f28;      // the last record THRASH_talloc made; each points at the one before
constexpr x86::reg32 kTextureNext = 0xa937a8;   // the next free address of texture memory
constexpr x86::reg32 kTexturing = 0xa92354;     // 1 while a texture is selected
constexpr x86::reg32 kCombineLocal = 0xa91f2c;  // THRASH_setstate 6

x86::reg8 byteAt(win32::WinApplication* app, x86::reg32 address)
{
    return app->getMemory<x86::reg8>(address);
}

/* log2 of a power of two, from the exponent of the float it converts to. */
x86::sreg32 exponentOf(x86::reg32 value)
{
    const float converted = float(double(x86::sreg32(value)));
    x86::reg32 bits;
    std::memcpy(&bits, &converted, sizeof bits);
    return x86::sreg32(bits - 0x3f800000) >> 23;
}

/* What THRASH_talloc(width, height, format, -, levels) works out before it
 * allocates: the record's Glide LODs, aspect and format, the memory it takes,
 * and where it starts -- moved to the next 2 MB bank if it would straddle one,
 * which `apply` writes back as voodoo2a does. */
struct TexturePlan
{
    x86::reg32 smallLod, largeLod, aspect, format, size, start;
    bool fits;
};

TexturePlan planTexture(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 esp, bool apply)
{
    namespace gl = win32::glide2x::direct;
    const x86::sreg32 widthLog = exponentOf(at(app, esp + 4));
    const x86::sreg32 heightLog = exponentOf(at(app, esp + 8));
    const x86::reg32 formatIndex = at(app, esp + 0xc);
    const x86::sreg32 levels = x86::sreg32(at(app, esp + 0x14));
    const x86::sreg32 largest = widthLog > heightLog ? widthLog : heightLog;
    x86::sreg32 smallest = largest - levels;
    if (smallest < 0)
        smallest = 0;
    TexturePlan plan;
    plan.largeLod = byteAt(app, 0xa92338 + x86::reg32(largest));
    plan.smallLod = byteAt(app, 0xa92338 + x86::reg32(smallest));
    plan.aspect = byteAt(app, 0xa92344 + x86::reg32(widthLog - heightLog));
    plan.format = byteAt(app, 0xa92348 + formatIndex);
    plan.size = gl::texCalcMemRequired(app, cpu, plan.smallLod, plan.largeLod, plan.aspect, plan.format);
    plan.start = at(app, kTextureNext);
    const x86::reg32 firstBank = (plan.start - gl::texMinAddress(app, cpu, 0)) & 0xffe00000;
    const x86::reg32 lastBank = (plan.size + plan.start - 1 - gl::texMinAddress(app, cpu, 0)) & 0xffe00000;
    if (lastBank != firstBank)
    {
        plan.start = gl::texMinAddress(app, cpu, 0) + lastBank;
        if (apply)
            put(app, kTextureNext, plan.start);
    }
    const x86::reg32 top = (gl::texMaxAddress(app, cpu, 0) + 0xf) & ~x86::reg32(0xf);
    plan.fits = x86::sreg32(top - plan.start) >= x86::sreg32(plan.size);
    return plan;
}

/* THRASH_talloc: a record of Glide's GrTexInfo -- small and large LOD, aspect,
 * format, texels -- then where it lies in texture memory, 3 (both halves of
 * the mipmap) and the record before; 0 when it does not fit.  The record comes
 * from voodoo2a's own malloc, which THRASH_treset gives them back to
 * (native_watcom_heap.cpp). */
void textureAllocateNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const TexturePlan plan = planTexture(app, cpu, esp, true);
    x86::reg32 record = 0;
    if (plan.fits)
    {
        record = thrashMalloc(app, cpu, 0x20);
        if (cpu.terminate)
            return;
    }
    if (record != 0)
    {
        put(app, record + 4, plan.largeLod);
        put(app, record, plan.smallLod);
        put(app, record + 8, plan.aspect);
        put(app, record + 0xc, byteAt(app, 0xa92348 + at(app, esp + 0xc)));
        put(app, record + 0x10, 0);
        put(app, record + 0x18, 3);
        put(app, record + 0x14, plan.start);
        put(app, kTextureNext, plan.start + plan.size);
        put(app, record + 0x1c, at(app, kTextures));
        put(app, kTextures, record);
    }
    cpu.eax = record;
    cpu.esp = esp + 4 + 0x14;
}

/* THRASH_treset: all of texture memory free again, every record given back. */
void resetTextures(win32::WinApplication* app, x86::CPU& cpu)
{
    win32::glide2x::direct::resetTextures();
    put(app, kTextureNext, win32::glide2x::direct::texMinAddress(app, cpu, 0));
    while (const x86::reg32 record = at(app, kTextures))
    {
        const x86::reg32 before = at(app, record + 0x1c);
        thrashFree(app, cpu, record);
        put(app, kTextures, before);
    }
}

void textureResetNative(win32::WinApplication* app, x86::CPU& cpu)
{
    resetTextures(app, cpu);
    cpu.eax = 1;
    cpu.esp += 4;
}

/* THRASH_tupdate(record, texels, palette): new texels for a record, downloaded;
 * a palette for a palettised one. */
void textureUpdateNative(win32::WinApplication* app, x86::CPU& cpu)
{
    namespace gl = win32::glide2x::direct;
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 record = at(app, esp + 4);
    const x86::reg32 texels = at(app, esp + 8);
    const x86::reg32 palette = at(app, esp + 0xc);
    if (texels != 0)
    {
        put(app, record + 0x10, texels);
        gl::texDownloadMipMap(app, cpu, 0, at(app, record + 0x14), at(app, record + 0x18), record);
    }
    if (palette != 0)
        gl::texDownloadTable(app, cpu, 0, 2, palette);
    cpu.eax = record;
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_settexture(record), and THRASH_setstate 1: the texture drawn with, or
 * none -- the colour and alpha combine follow, texture times vertex colour or
 * the vertex colour alone. */
void selectTexture(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 record)
{
    namespace gl = win32::glide2x::direct;
    if (record == 0)
    {
        if (at(app, kTexturing) != 0)
        {
            gl::colorCombine(app, cpu, 1, 0, at(app, kCombineLocal), 2, 0);
            gl::alphaCombine(app, cpu, 1, 0, at(app, kCombineLocal), 2, 0);
            put(app, kTexturing, 0);
        }
        return;
    }
    gl::texSource(app, cpu, 0, at(app, record + 0x14), at(app, record + 0x18), record);
    if (at(app, kTexturing) != 1)
    {
        gl::colorCombine(app, cpu, 3, 1, at(app, kCombineLocal), 1, 0);
        gl::alphaCombine(app, cpu, 3, 1, at(app, kCombineLocal), 1, 0);
        put(app, kTexturing, 1);
    }
}

void setTextureNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    selectTexture(app, cpu, at(app, esp + 4));
    cpu.eax = 1;
    cpu.esp = esp + 4 + 4;
}

constexpr x86::reg32 kBuffer = 0xa91f04;        // the buffer drawn into, THRASH_window's less one
constexpr x86::reg32 kClearColour = 0xa91efc;   // THRASH_setstate 3
constexpr x86::reg32 kClearDepth = 0xa91f00;    // set with the depth test, THRASH_setstate 4
constexpr x86::reg32 kSwapInterval = 0xa91f0c;  // THRASH_setstate 0x67
constexpr x86::reg32 kLockHook = 0xa91f38;      // the game's own function, told 1 before and 0 after a lock

/* The game's hook around the frame buffer's locks, when it has set one: a
 * stdcall of its own code with one argument.  False when the game stopped in
 * it. */
bool lockHook(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 locking)
{
    const x86::reg32 hook = at(app, kLockHook);
    if (hook == 0)
        return true;
    const x86::reg32 esp = cpu.esp;
    cpu.esp -= 4;
    put(app, cpu.esp, locking);
    cpu.esp -= 4;
    app->dynamic_call(hook, cpu);
    cpu.esp = esp;
    return !cpu.terminate;
}

/* THRASH_window(buffer): which buffer to draw into, counted from 1; 0 is 1. */
void windowNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    x86::reg32 buffer = at(app, esp + 4);
    if (buffer == 0)
        buffer = 1;
    put(app, kBuffer, buffer - 1);
    win32::glide2x::direct::renderBuffer(app, cpu, buffer - 1);
    cpu.eax = 1;
    cpu.esp = esp + 4 + 4;
}

/* THRASH_clearwindow: colour and depth cleared to what THRASH_setstate set. */
void clearWindowNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg16 depth = app->getMemory<x86::reg16>(kClearDepth);
    win32::glide2x::direct::bufferClear(app, cpu, at(app, kClearColour), 0, depth);
    cpu.eax = depth;
    cpu.esp += 4;
}

/* THRASH_flushwindow and THRASH_idle: nothing to do on a Voodoo2. */
void nothingNative(win32::WinApplication* app, x86::CPU& cpu)
{
    NFS2_USE(app);
    cpu.esp += 4;
}

/* THRASH_pageflip: once nothing is left pending -- or after four million
 * tries -- the buffers swapped, every THRASH_setstate 0x67 frames. */
void pageFlip(win32::WinApplication* app, x86::CPU& cpu)
{
    namespace gl = win32::glide2x::direct;
    x86::reg32 tries = 4000000;
    while (gl::bufferNumPending(app, cpu) != 0 && --tries != 0)
    {
    }
    gl::bufferSwap(app, cpu, at(app, kSwapInterval));
}

void pageFlipNative(win32::WinApplication* app, x86::CPU& cpu)
{
    pageFlip(app, cpu);
    cpu.esp += 4;
}

/* THRASH_sync(what): 0 waits for the card, 1 asks whether it is busy, 2 waits
 * for the start of a vertical retrace, 3 tells how much of the FIFO is free. */
void syncNative(win32::WinApplication* app, x86::CPU& cpu)
{
    namespace gl = win32::glide2x::direct;
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 what = at(app, esp + 4);
    x86::reg32 result = 0;
    switch (what)
    {
    case 0:
        gl::sstIdle(app, cpu);
        break;
    case 1:
        gl::sstIsBusy(app, cpu);
        result = 1;  // grSstIsBusy leaves eax as it found it: the 1 just read
        break;
    case 2:
    {
        // Out of the retrace there is now, then into the next one, four
        // million tries between the two.
        x86::reg32 tries = 4000000;
        while (gl::sstVRetraceOn(app, cpu) != 0)
            if (--tries == 0)
                break;
        while (gl::sstVRetraceOn(app, cpu) == 0)
            if (--tries == 0)
                break;
        break;
    }
    case 3:
        result = 0xffff - ((gl::sstStatus(app, cpu) >> 12) & 0xffff);
        break;
    default:
        break;
    }
    cpu.eax = result;
    cpu.esp = esp + 4 + 4;
}

/* THRASH_clip(minX, minY, maxX, maxY). */
void clipNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    win32::glide2x::direct::clipWindow(app, cpu, at(app, esp + 4), at(app, esp + 8), at(app, esp + 0xc),
                                       at(app, esp + 0x10));
    cpu.eax = 1;
    cpu.esp = esp + 4 + 0x10;
}

/* THRASH_lockwindow: the frame buffer locked for the game to write into, as
 * a record of voodoo2a's malloc -- the pointer, the stride, 4, two of
 * THRASH_setstate's values and the buffer -- or 0.  It then asks for a read
 * lock as well, which comes to nothing. */
void lockWindowNative(win32::WinApplication* app, x86::CPU& cpu)
{
    namespace gl = win32::glide2x::direct;
    const x86::reg32 esp = cpu.esp;
    if (!lockHook(app, cpu, 1))
        return;
    const x86::reg32 info = esp - 0x24;  // GrLfbInfo_t, where voodoo2a keeps it
    put(app, info, 0x14);
    x86::reg32 record = 0;
    if (gl::lfbLock(app, cpu, 1, at(app, kBuffer), 0xff, 0, 0, info) != 0)
    {
        const x86::reg32 pixels = at(app, info + 4);
        const x86::reg32 stride = at(app, info + 8);
        record = thrashMalloc(app, cpu, 0x18);
        if (cpu.terminate)
            return;
        if (record != 0)
        {
            put(app, record, pixels);
            put(app, record + 8, 4);
            put(app, record + 4, stride);
            put(app, record + 0xc, at(app, 0xa91f18));
            put(app, record + 0x10, at(app, 0xa91f1c));
            put(app, record + 0x14, at(app, kBuffer));
        }
    }
    put(app, info, 0x14);
    gl::lfbLock(app, cpu, 0, at(app, kBuffer), 0xff, 0, 0, info);
    if (record == 0 && !lockHook(app, cpu, 0))
        return;
    cpu.eax = record;
    cpu.esp = esp + 4;
}

/* THRASH_unlockwindow(record): both locks let go, the record freed. */
void unlockWindowNative(win32::WinApplication* app, x86::CPU& cpu)
{
    namespace gl = win32::glide2x::direct;
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 record = at(app, esp + 4);
    if (record != 0)
    {
        const x86::reg32 buffer = at(app, record + 0x14);
        gl::lfbUnlock(app, cpu, 1, buffer);
        gl::lfbUnlock(app, cpu, 0, buffer);
        thrashFree(app, cpu, record);
        if (!lockHook(app, cpu, 0))
            return;
    }
    cpu.eax = 1;
    cpu.esp = esp + 4 + 4;
}

/* THRASH_readrect(x, y, width, height, to): the buffer drawn into, read back
 * at two bytes a pixel. */
void readRectNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    if (!lockHook(app, cpu, 1))
        return;
    const x86::reg32 width = at(app, esp + 0xc);
    const x86::reg32 result = win32::glide2x::direct::lfbReadRegion(
        app, cpu, at(app, kBuffer), at(app, esp + 4), at(app, esp + 8), width, at(app, esp + 0x10), width * 2,
        at(app, esp + 0x14));
    if (!lockHook(app, cpu, 0))
        return;
    cpu.eax = result;
    cpu.esp = esp + 4 + 0x14;
}

/* A stdcall of a guest function -- the game's hooks, Win32 through voodoo2a's
 * import table, Glide through its table, DirectDraw's methods -- made the way
 * voodoo2a's code makes it.  Its result; cpu.terminate says whether the game
 * stopped in it, when the caller, like voodoo2a's code, goes no further. */
x86::reg32 stdcall(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 address,
                   std::initializer_list<x86::reg32> arguments)
{
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 first = esp - 4 * x86::reg32(arguments.size());
    x86::reg32 slot = first;
    for (const x86::reg32 argument : arguments)
    {
        put(app, slot, argument);
        slot += 4;
    }
    cpu.esp = first - 4;
    app->dynamic_call(address, cpu);
    cpu.esp = esp;
    return cpu.eax;
}

/* voodoo2a's imports and state for setting the card up. */
constexpr x86::reg32 kLoadLibrary = 0xa903ec, kGetProcAddress = 0xa903d8, kFreeLibrary = 0xa90390;
constexpr x86::reg32 kCreateEvent = 0xa90368, kCloseHandle = 0xa90364, kSetForegroundWindow = 0xa9035c;
constexpr x86::reg32 kPostMessage = 0xa90358, kWaitForSingleObject = 0xa90438, kSetEvent = 0xa90404;
constexpr x86::reg32 kDirectDrawCreate = 0xa90448;
constexpr x86::reg32 kGlideModule = 0xa91f50;
constexpr x86::reg32 kHardware = 0xa93714;      // GrHwConfiguration: boards, then the first one's type, memory...
constexpr x86::reg32 kInfo = 0xa91f54;          // what THRASH_about hands the game
constexpr x86::reg32 kModes = 0xa92018;         // 17 modes of 0x28 bytes: width, height, depth, ..., buffers
constexpr x86::reg32 kResolutions = 0xa922e8;   // each mode's GR_RESOLUTION
constexpr x86::reg32 kFlags = 0xa91ef4;         // 1 set up, 2 a window open
constexpr x86::reg32 kWindow = 0xa91f08;        // the game's window
constexpr x86::reg32 kModeEvent = 0xa91f40;
constexpr x86::reg32 kDirectDraw = 0xa91f48;
constexpr x86::reg32 kModeThread = 0xa92334;    // 1 while the window's thread is to set the mode
constexpr x86::reg32 kModeMessage = 0xa84360;   // sub_a84360, what the window's thread runs on message 0x465

x86::reg32 glide(win32::WinApplication* app, x86::reg32 entry)
{
    return at(app, entry);
}

/* sub_a83220: glide2x.dll loaded and its functions looked up into the table
 * from 0xa93614, the drawing pointed at the plain ones.  0 without it, or
 * when the game stopped. */
x86::reg32 loadGlide(win32::WinApplication* app, x86::CPU& cpu)
{
    static const x86::reg32 kNames[] = {
        0xa91210, 0xa91220, 0xa91238, 0xa9124c, 0xa91260, 0xa91270, 0xa91284, 0xa91298, 0xa912b0, 0xa912c4,
        0xa912e4, 0xa912fc, 0xa91310, 0xa91324, 0xa91334, 0xa91344, 0xa91358, 0xa91368, 0xa91378, 0xa9138c,
        0xa913a0, 0xa913b4, 0xa913d0, 0xa913e0, 0xa913f4, 0xa91404, 0xa91418, 0xa91430, 0xa91448, 0xa91464,
        0xa91474, 0xa91488, 0xa91498, 0xa914a8, 0xa914b8, 0xa914c8, 0xa914e0, 0xa914f4, 0xa91508, 0xa91518,
        0xa91528, 0xa91544, 0xa91558, 0xa9156c, 0xa91580, 0xa9159c, 0xa915b4, 0xa915c8, 0xa915dc, 0xa915ec,
        0xa91600, 0xa91618, 0xa91630, 0xa91640, 0xa9164c, 0xa91664, 0xa91678, 0xa91690, 0xa916a8,
    };
    if (at(app, 0xa91f34) == 0)
        put(app, 0xa91f34, 0xa83a80);
    const x86::reg32 module = stdcall(app, cpu, at(app, kLoadLibrary), { 0xa91204 });
    if (cpu.terminate)
        return 0;
    put(app, kGlideModule, module);
    if (module == 0)
        return 0;
    x86::reg32 entry = 0xa93614;
    for (const x86::reg32 name : kNames)
    {
        const x86::reg32 function = stdcall(app, cpu, at(app, kGetProcAddress), { at(app, kGlideModule), name });
        if (cpu.terminate)
            return 0;
        put(app, entry, function);
        entry += 4;
    }
    put(app, kTriangleDraw, at(app, kGrDrawTriangle));
    put(app, kQuadDraw, at(app, kGrDrawTriangle));
    put(app, kLineDraw, at(app, kGrDrawLine));
    return 1;
}

/* sub_a83800: glide2x.dll let go. */
void freeGlide(win32::WinApplication* app, x86::CPU& cpu)
{
    if (const x86::reg32 module = at(app, kGlideModule))
    {
        stdcall(app, cpu, at(app, kFreeLibrary), { module });
        if (cpu.terminate)
            return;
    }
    put(app, kGlideModule, 0);
}

/* sub_a83ac0: from the hardware found, how many colour and auxiliary buffers
 * each mode can have in the frame buffer's memory, and the info's card type
 * (+0x6c) and texture memory (+0x70). */
void measureModes(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 info)
{
    namespace gl = win32::glide2x::direct;
    x86::sreg32 memory = x86::sreg32(at(app, kHardware + 8) << 20);
    const x86::reg32 type = at(app, kHardware + 4);
    const x86::reg32 voodoo2 = type == 1 ? 1 : 0;
    put(app, 0xa91ef8, voodoo2);
    x86::reg32 sli = 0;
    if (voodoo2 == 0)
        sli = at(app, kHardware + 0x14);
    if (sli != 0)
        memory += memory;
    x86::reg32 mode = kModes + 0x28;
    for (int i = 1; i <= 16; ++i, mode += 0x28)
    {
        const x86::sreg32 pixels = x86::sreg32(at(app, mode) * at(app, mode + 4));
        const x86::sreg32 frame = (x86::sreg32(at(app, mode + 8)) >> 3) * pixels;
        put(app, mode + 0x14, x86::reg32(memory / frame));
        if (at(app, mode) == 0x3c0 && sli == 0)
            put(app, mode + 0x14, 0);
        if (x86::sreg32(at(app, mode)) > 0x320 && at(app, 0xa91ef8) != 0)
            put(app, mode + 0x14, 0);
        if (at(app, mode + 0x10) == 0 || x86::sreg32(at(app, mode + 0x14)) <= 0)
        {
            put(app, mode + 0x18, 0);
            put(app, mode + 0x14, 0);
            continue;
        }
        put(app, mode + 0x18, at(app, mode + 0x14) - 1);
        if (x86::sreg32(at(app, mode + 0x14)) > 3)
            put(app, mode + 0x14, 3);
        if (x86::sreg32(at(app, mode + 0x18)) > 3)
            put(app, mode + 0x18, 3);
    }
    put(app, info + 0x6c, type);
    if (type == 0)
    {
        const x86::reg32 revision = at(app, kHardware + 0xc);
        if ((x86::sreg32(revision) >> 8) == 1)
            put(app, info + 0x6c, 2);
        if ((x86::sreg32(revision) >> 12) == 1)
            put(app, info + 0x6c, 3);
        if (revision == 0 && x86::sreg32(at(app, kHardware + 8)) >= 6)
        {
            put(app, 0xa91f10, 0);
            put(app, info + 0x6c, 3);
        }
    }
    x86::reg32 texture = gl::texMaxAddress(app, cpu, 0);
    texture -= gl::texMinAddress(app, cpu, 0);
    texture -= gl::texMinAddress(app, cpu, 0);
    put(app, info + 0x70, texture);
    if (x86::sreg32(texture) > 0)
        put(app, info + 0x70, (texture + 0xf) & ~x86::reg32(0xf));
    put(app, info + 0x74, 1);
}

/* THRASH_about: the driver described, once -- its name, what it can do, its
 * texture formats (0xa91fd4) and its modes (0xa92018) -- from a look at the
 * card through Glide. */
void aboutNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    if (at(app, kInfo) == 0)
    {
        std::memset(&app->getMemory<x86::reg8>(kInfo), 0, 0x80);
        put(app, kInfo, 0x33444658);  // "XFD3"
        put(app, 0xa91f5c, 0x68);
        for (const x86::reg32 field : { 0xa91f64u, 0xa91f6cu, 0xa91f70u, 0xa91f78u, 0xa91f7cu })
            put(app, field, 1);
        put(app, 0xa91f58, 0x80);
        put(app, 0xa91f68, 0x100);
        put(app, 0xa91f88, 4);
        put(app, 0xa91f90, 0x10);
        put(app, 0xa91f94, kModes);
        put(app, 0xa91f74, 0x100);
        app->getMemory<x86::reg8>(0xa91f60) = x86::reg8((app->getMemory<x86::reg8>(0xa91f60) | 0xe) & 0xfe);
        put(app, 0xa91f8c, 0xa92000);
        put(app, 0xa91f80, 9);
        put(app, 0xa91f84, 0xa91fd4);
        if (win32::glide2x::fullColourTextures())
        {
            /* tools/apply_full_colour.py: THRASH format 6, ARGB 8888, taken,
             * and handed to Glide as such. */
            put(app, 0xa91fd4 + 6 * 4, 1);
            app->getMemory<x86::reg8>(0xa92348 + 6) = x86::reg8(win32::glide2x::kTexFmtArgb8888);
        }
        std::strcpy(&app->getMemory<char>(kInfo + 0x4c), &app->getMemory<char>(0xa916d4));
        put(app, 0xa91fc0, 0);
        if (app->getMemory<x86::reg8>(kFlags) & 1)
        {
            measureModes(app, cpu, kInfo);
        }
        else if (loadGlide(app, cpu) != 0)
        {
            if (at(app, 0xa93614) != 0 && at(app, 0xa9361c) != 0 && at(app, 0xa93618) != 0)
            {
                x86::sreg32 boards = x86::sreg32(stdcall(app, cpu, glide(app, 0xa9361c), { kHardware }));
                if (cpu.terminate)
                    return;
                if (boards != 0)
                    boards = x86::sreg32(at(app, kHardware));
                if (boards > 0)
                {
                    stdcall(app, cpu, glide(app, 0xa93614), {});
                    if (cpu.terminate)
                        return;
                    stdcall(app, cpu, glide(app, 0xa93618), { kHardware });
                    if (cpu.terminate)
                        return;
                    measureModes(app, cpu, kInfo);
                    stdcall(app, cpu, glide(app, 0xa93620), {});
                    if (cpu.terminate)
                        return;
                }
            }
            freeGlide(app, cpu);
        }
        if (cpu.terminate)
            return;
    }
    cpu.eax = kInfo;
    cpu.esp = esp + 4;
}

/* THRASH_selectdisplay(board). */
x86::reg32 selectDisplay(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 board)
{
    if (x86::sreg32(board) >= x86::sreg32(at(app, kHardware)))
        return 0;
    stdcall(app, cpu, glide(app, 0xa93624), { board });
    return 1;
}

void selectDisplayNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 selected = selectDisplay(app, cpu, at(app, esp + 4));
    if (cpu.terminate)
        return;
    cpu.eax = selected;
    cpu.esp = esp + 4 + 4;
}

/* THRASH_init: the colour table (a byte to Glide's float), the event the
 * window's thread signals, Glide up, board 0, the modes measured, and
 * THRASH_restore run at exit.  The number of boards, or 0. */
void initNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    x86::reg32 result = 0;
    if (!(app->getMemory<x86::reg8>(kFlags) & 1))
    {
        for (int i = 0; i < 0x100; ++i)
            app->getMemory<float>(kColourTable + 4 * x86::reg32(i)) = float(double(i));
        if (at(app, 0xa91f34) == 0)
            put(app, 0xa91f34, 0xa83a80);
        if (at(app, kModeEvent) == 0)
        {
            const x86::reg32 event = stdcall(app, cpu, at(app, kCreateEvent), { 0, 0, 0, 0 });
            if (cpu.terminate)
                return;
            put(app, kModeEvent, event);
        }
        const x86::reg32 loaded = loadGlide(app, cpu);
        if (cpu.terminate)
            return;
        if (loaded != 0)
        {
            stdcall(app, cpu, glide(app, 0xa93614), {});
            if (cpu.terminate)
                return;
            const x86::reg32 found = stdcall(app, cpu, glide(app, 0xa93618), { kHardware });
            if (cpu.terminate)
                return;
            const x86::reg32 selected = found != 0 ? selectDisplay(app, cpu, 0) : 0;
            if (cpu.terminate)
                return;
            if (selected != 0)
            {
                result = at(app, kHardware);
                measureModes(app, cpu, kInfo);
                if (result != 0)
                {
                    put(app, kFlags, 1);
                    // sub_a86c40, atexit: THRASH_restore (by way of sub_a83f40) when the game ends.
                    const x86::reg32 exits = at(app, 0xa93840);
                    if (x86::sreg32(exits) < 0x20)
                    {
                        put(app, 0xa937bc + (exits + 1) * 4, 0xa83f40);
                        put(app, 0xa93840, exits + 1);
                    }
                }
            }
        }
    }
    cpu.eax = result;
    cpu.esp = esp + 4;
}

/* sub_a84020: DirectDraw, on a card that shares the screen, for the game's
 * window to own it -- exclusive and full screen, or only exclusive. */
x86::reg32 takeScreen(win32::WinApplication* app, x86::CPU& cpu)
{
    if (at(app, kDirectDraw) != 0 || at(app, 0xa91ef8) != 0 || at(app, 0xa91f10) == 0)
        return 0;
    if (stdcall(app, cpu, at(app, kDirectDrawCreate), { 0, kDirectDraw, 0 }) != 0 || cpu.terminate)
        return 0;
    const x86::reg32 level = at(app, 0xa91f44) != 0 ? 0x10 : 0x11;
    const x86::reg32 object = at(app, kDirectDraw);
    const x86::reg32 refused = stdcall(app, cpu, at(app, at(app, object) + 0x50), { object, at(app, kWindow), level });
    if (cpu.terminate)
        return 0;
    if (refused == 0)
        return 1;
    const x86::reg32 refuser = at(app, kDirectDraw);  // read again, as voodoo2a does
    stdcall(app, cpu, at(app, at(app, refuser) + 8), { refuser });
    if (cpu.terminate)
        return 0;
    put(app, kDirectDraw, 0);
    return 0;
}

/* sub_a840b0: DirectDraw let go. */
void releaseScreen(win32::WinApplication* app, x86::CPU& cpu)
{
    if (const x86::reg32 object = at(app, kDirectDraw))
    {
        stdcall(app, cpu, at(app, at(app, object) + 8), { object });
        if (cpu.terminate)
            return;
        put(app, kDirectDraw, 0);
    }
}

/* The state THRASH_setstate sets, without a call of its own: an argument it
 * writes back to (state 0xb) goes to `slot`, or nowhere for 0. */
x86::reg32 applyState(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 state, x86::reg32 value, x86::reg32 slot);

/* sub_a84180(mode, buffers, auxiliary): the Glide window opened in that mode,
 * and the renderer's state set to its defaults.  A window already open is
 * closed first; no buffers at all only closes it, and gives back what ebx
 * held. */
x86::reg32 openMode(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 mode, x86::reg32 buffers,
                    x86::reg32 auxiliary)
{
    if (app->getMemory<x86::reg8>(kFlags) & 2)
    {
        stdcall(app, cpu, glide(app, 0xa93628), {});  // grSstWinClose
        if (cpu.terminate)
            return 0;
        app->getMemory<x86::reg8>(kFlags) = x86::reg8(app->getMemory<x86::reg8>(kFlags) & 0xfd);
    }
    if (buffers == 0)
        return cpu.ebx;
    x86::reg32 resolution = 0xff;
    if (at(app, 0xa91ef8) == 0 || at(app, 0xa91f44) == 0)
        resolution = at(app, kResolutions + mode * 4);
    const x86::reg32 entry = kModes + mode * 0x28;
    if (auxiliary != 0 && x86::sreg32(buffers) > x86::sreg32(at(app, entry + 0x18)))
        auxiliary = 0;
    x86::reg32 opened = stdcall(app, cpu, glide(app, 0xa9362c),
                                { at(app, kWindow), resolution, 0, 0, 0, buffers, auxiliary });
    if (cpu.terminate)
        return 0;
    if (opened == 0 && resolution == 0xff)
    {
        opened = stdcall(app, cpu, glide(app, 0xa9362c),
                         { at(app, kWindow), at(app, kResolutions + mode * 4), 0, 0, 0, buffers, auxiliary });
        if (cpu.terminate)
            return 0;
    }
    if (opened == 0)
        return 0;
    if (at(app, 0xa91ef8) == 0)
    {
        const x86::reg32 width = stdcall(app, cpu, glide(app, 0xa936f0), {});  // grSstScreenWidth
        if (cpu.terminate)
            return 0;
        const x86::reg32 height = stdcall(app, cpu, glide(app, 0xa936f4), {});  // grSstScreenHeight
        if (cpu.terminate)
            return 0;
        put(app, 0xa91f18, width);
        put(app, 0xa91f1c, height);
    }
    else
    {
        put(app, 0xa91f18, at(app, entry));
        put(app, 0xa91f1c, at(app, entry + 4));
    }
    resetTextures(app, cpu);
    stdcall(app, cpu, glide(app, 0xa93638), { 0x10 });                  // grAlphaTestReferenceValue
    if (cpu.terminate)
        return 0;
    win32::glide2x::direct::texCombine(app, cpu, 0, 1, 0, 1, 0, 0, 0);
    stdcall(app, cpu, glide(app, 0xa936e8), { 3, 1 });                 // grHints
    if (cpu.terminate)
        return 0;
    static const x86::reg32 kDefaults[][2] = {
        { 1, 0 }, { 2, 1 }, { 7, 1 }, { 6, 1 }, { 0xa, 2 }, { 0xb, 1 }, { 3, 0 }, { 0xc, 0 },
        { 5, 1 }, { 0xe, 0 }, { 0xf, 0xffffffff }, { 0x68, 0 }, { 0xd, 0 }, { 0x65, 0x3f800000 },
        { 0x18, 0 }, { 8, 0 },
    };
    for (const auto& pair : kDefaults)
        applyState(app, cpu, pair[0], pair[1], 0);
    applyState(app, cpu, 4, x86::sreg32(auxiliary) >= 1 ? 2 : 0, 0);
    app->getMemory<x86::reg8>(kFlags) = x86::reg8(app->getMemory<x86::reg8>(kFlags) | 2);
    return opened;
}

/* sub_a84360: what the game's window thread runs on message 0x465 -- the
 * mode the game thread asked for, opened there, the result in voodoo2a's
 * variable and the caller's, and the game thread let go. */
void windowThreadNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    if (at(app, kModeThread) != 0)
    {
        const x86::reg32 packed = at(app, esp + 0x14);
        // ebx holds the mode, which closing alone gives back
        const x86::reg32 ebx = cpu.ebx;
        cpu.ebx = at(app, esp + 0x10);
        const x86::reg32 opened = openMode(app, cpu, cpu.ebx, packed & 0xff, packed >> 8);
        cpu.ebx = ebx;
        if (cpu.terminate)
            return;
        put(app, 0xa91f14, opened);
        put(app, at(app, esp + 0x18), opened == 0 ? 1 : 0);
        if (const x86::reg32 event = at(app, kModeEvent))
        {
            stdcall(app, cpu, at(app, kSetEvent), { event });
            if (cpu.terminate)
                return;
        }
    }
    cpu.eax = 1;
    cpu.esp = esp + 4 + 0x18;
}

/* THRASH_setvideomode(mode, buffers, auxiliary): the game's window found, the
 * screen taken, the window brought forward, and the mode opened -- on the
 * window's own thread when the game hooked its messages, waiting for it. */
x86::reg32 setVideoMode(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 mode, x86::reg32 buffers,
                        x86::reg32 auxiliary)
{
    if (const x86::reg32 findWindow = at(app, 0xa91f30))
    {
        const x86::reg32 window = stdcall(app, cpu, findWindow, {});
        if (cpu.terminate)
            return 0;
        put(app, kWindow, window);
    }
    takeScreen(app, cpu);
    if (cpu.terminate)
        return 0;
    if (const x86::reg32 window = at(app, kWindow))
    {
        stdcall(app, cpu, at(app, kSetForegroundWindow), { window });
        if (cpu.terminate)
            return 0;
    }
    if (at(app, 0xa91f3c) != 0 && at(app, kWindow) != 0 && at(app, kModeEvent) != 0)
    {
        stdcall(app, cpu, at(app, 0xa91f3c), { 0x465, kModeMessage });
        if (cpu.terminate)
            return 0;
        put(app, kModeThread, 1);
        stdcall(app, cpu, at(app, kPostMessage), { at(app, kWindow), 0x465, mode, buffers + (auxiliary << 8) });
        if (cpu.terminate)
            return 0;
        stdcall(app, cpu, at(app, kWaitForSingleObject), { at(app, kModeEvent), 0xffffffff });
        if (cpu.terminate)
            return 0;
        put(app, kModeThread, 0);
        return at(app, 0xa91f14);
    }
    return openMode(app, cpu, mode, buffers, auxiliary);
}

void setVideoModeNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    const x86::reg32 opened = setVideoMode(app, cpu, at(app, esp + 4), at(app, esp + 8), at(app, esp + 0xc));
    if (cpu.terminate)
        return;
    cpu.eax = opened;
    cpu.esp = esp + 4 + 0xc;
}

/* THRASH_restore: everything let go -- the window and its mode, DirectDraw,
 * the event, Glide. */
void restoreNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    if (at(app, kFlags) != 0)
    {
        if (app->getMemory<x86::reg8>(kFlags) & 2)
        {
            setVideoMode(app, cpu, 0, 0, 0);
            if (cpu.terminate)
                return;
            releaseScreen(app, cpu);
            if (cpu.terminate)
                return;
        }
        if (at(app, 0xa91f3c) != 0)
            put(app, 0xa91f3c, 0);
        if (const x86::reg32 event = at(app, kModeEvent))
        {
            stdcall(app, cpu, at(app, kCloseHandle), { event });
            if (cpu.terminate)
                return;
            put(app, kModeEvent, 0);
        }
        stdcall(app, cpu, glide(app, 0xa93620), {});  // grGlideShutdown
        if (cpu.terminate)
            return;
        freeGlide(app, cpu);
        if (cpu.terminate)
            return;
        put(app, 0xa91f34, 0);
        put(app, kFlags, 0);
    }
    cpu.eax = 1;
    cpu.esp = esp + 4;
}

/* THRASH_writerect(x, y, width, height, pixels): 565 pixels written into the
 * buffer drawn into, the game's lock hook told around it. */
void writeRectNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    if (!lockHook(app, cpu, 1))
        return;
    const x86::reg32 width = at(app, esp + 0xc);
    const x86::reg32 result = stdcall(app, cpu, glide(app, kGrLfbWriteRegion),
                                      { at(app, kBuffer), at(app, esp + 4), at(app, esp + 8), 0, width,
                                        at(app, esp + 0x10), width * 2, at(app, esp + 0x14) });
    if (cpu.terminate || !lockHook(app, cpu, 0))
        return;
    cpu.eax = result;
    cpu.esp = esp + 4 + 0x14;
}

/* sub_a86ad0, getenv, on voodoo2a's own environment ([0xa93ea4]), which its
 * C library's start-up would have filled -- and which never runs on the port:
 * there is nothing to find. */
x86::reg32 environmentValue(win32::WinApplication* app)
{
    const x86::reg32 environment = at(app, 0xa93ea4);
    NFS2_ASSERT(environment == 0 && "voodoo2a's environment, never set up on the port");
    NFS2_USE(environment);
    return 0;
}

/* Watcom's character classes (_IsTable, 0xa92578), a byte's at its value + 1. */
x86::reg8 characterClass(win32::WinApplication* app, x86::reg8 c)
{
    return byteAt(app, 0xa92578 + x86::reg32(x86::reg8(c + 1)));
}

/* sub_a86be0, atoi. */
x86::reg32 toInteger(win32::WinApplication* app, x86::reg32 text)
{
    while (characterClass(app, byteAt(app, text)) & 2)
        ++text;
    const x86::reg8 sign = byteAt(app, text);
    if (sign == '+' || sign == '-')
        ++text;
    x86::reg32 value = 0;
    while (characterClass(app, byteAt(app, text)) & 0x20)
        value = value * 10 + byteAt(app, text++) - 0x30;
    return sign == '-' ? 0 - value : value;
}

/* sub_a86b30, strcmp: -1, 0 or 1. */
x86::sreg32 compareText(win32::WinApplication* app, x86::reg32 a, x86::reg32 b)
{
    for (;; ++a, ++b)
    {
        const x86::reg8 x = byteAt(app, a), y = byteAt(app, b);
        if (x != y)
            return x < y ? -1 : 1;
        if (x == 0)
            return 0;
    }
}

/* THRASH_is: how well voodoo2a would drive what there is -- VOODOO2_IS from
 * the environment when it is set; else, Glide loaded for a look, 0 for a Glide
 * older than 2.42, 100 up to 2.5 and 95 past it; without a board, the number
 * of them Glide gave. */
void isNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    // push ebx; sub esp, 0x50: grGlideGetVersion writes into the frame, and
    // what it does not write is what was on the stack.
    put(app, esp - 4, cpu.ebx);
    cpu.esp = esp - 0x54;
    const x86::reg32 version = cpu.esp;
    x86::reg32 result = 0;
    if (const x86::reg32 value = environmentValue(app))
    {
        result = toInteger(app, value);
    }
    else
    {
        const x86::reg32 loaded = loadGlide(app, cpu);
        if (cpu.terminate)
            return;
        if (loaded == 0)
        {
            cpu.eax = 0;
            cpu.esp = esp + 4;
            return;
        }
        if (glide(app, 0xa93614) != 0 && glide(app, 0xa9361c) != 0 && glide(app, 0xa93618) != 0)
        {
            x86::reg32 boards = stdcall(app, cpu, glide(app, 0xa9361c), { kHardware });
            if (cpu.terminate)
                return;
            if (boards != 0)
                boards = at(app, kHardware);
            result = boards;  // no board, or -1 of them, is what it says
            if (x86::sreg32(boards) > 0)
            {
                stdcall(app, cpu, glide(app, 0xa93614), {});
                if (cpu.terminate)
                    return;
                result = stdcall(app, cpu, glide(app, 0xa93618), { kHardware });
                if (cpu.terminate)
                    return;
                if (result != 0)
                {
                    stdcall(app, cpu, glide(app, 0xa936dc), { version });  // grGlideGetVersion
                    if (cpu.terminate)
                        return;
                    // From its first digit, or its end.
                    x86::reg32 number = version;
                    while (byteAt(app, number) != 0 && !(characterClass(app, byteAt(app, number)) & 0x20))
                        ++number;
                    if (compareText(app, number, 0xa916ec) < 0)        // "2.42"
                        result = 0;
                    else if (compareText(app, number, 0xa916f4) <= 0)  // "2.5"
                        result = 100;
                    else
                        result = 95;
                }
                stdcall(app, cpu, glide(app, 0xa93620), {});  // grGlideShutdown
                if (cpu.terminate)
                    return;
            }
        }
        freeGlide(app, cpu);
        if (cpu.terminate)
            return;
    }
    cpu.eax = result;
    cpu.esp = esp + 4;
}

/* sub_a83830 and sub_a83870: Glide's fog table for a density -- 1 - e^(-d w)
 * at each of its 64 w, scaled to 1 at the last, times 255 -- worked out as
 * voodoo2a's code works it out, x87 operation by operation in double.
 * w(i) = 2^(3 + i/4) / (8 - i%4), exact (Watcom's pow of 2 with a whole
 * exponent). */
double fogW(int i)
{
    return std::ldexp(1.0, 3 + (i >> 2)) / double(8 - (i & 3));
}

double fogExp(x86::CPU& cpu, double w, float density)
{
    const double x = -(w * double(density));
    const double t = 1.4426950408889634 * x;
    const double fraction = cpu.fpu.rem(t, 1.0);
    return cpu.fpu.scale(1.0 + cpu.fpu.f2xm1(fraction), t);
}

void fogTable(win32::WinApplication* app, x86::CPU& cpu, float density, x86::reg8 (&table)[64])
{
    const float scale = float(1.0 / (1.0 - fogExp(cpu, fogW(63), density)));
    for (int i = 0; i < 64; ++i)
    {
        float value = float((1.0 - fogExp(cpu, fogW(i), density)) * double(scale));
        x86::reg32 bits;
        std::memcpy(&bits, &value, sizeof bits);
        if (x86::sreg32(bits) > 0x3f800000)
            value = 1.0f;
        else if (0.0 > double(value))  // fcomp leaves a NaN as it is
            value = 0.0f;
        const double scaled = double(value) * double(app->getMemory<float>(0xa916cc));
        table[i] = x86::reg8(cpu.fpu.toInteger<x86::sreg32>(scaled));
    }
}

/* THRASH_setstate(state, value): one piece of the renderer's state, to Glide or
 * to voodoo2a's own variables.  1 for done, 0 for a state or value it does not
 * know. */
x86::reg32 applyState(win32::WinApplication* app, x86::CPU& cpu, x86::reg32 state, x86::reg32 value, x86::reg32 slot)
{
    namespace gl = win32::glide2x::direct;
    x86::reg32 result = 1;
    switch (state)
    {
    case thrash::kStateTexture:
        selectTexture(app, cpu, value);
        break;
    case thrash::kStateCull:
        gl::cullMode(app, cpu, value);
        break;
    case thrash::kStateClearColour:
        put(app, 0xa91efc, value);
        break;
    case thrash::kStateDepth:  // depth: off, or on, compared less-or-equal
        if (value == 0)
        {
            gl::depthBufferFunction(app, cpu, 7);
            gl::depthMask(app, cpu, 0);
        }
        else if (value == 1 || value == 2)
        {
            gl::depthBufferMode(app, cpu, value);
            gl::depthBufferFunction(app, cpu, 3);
            put(app, 0xa91f00, 0xffff);
            gl::depthMask(app, cpu, 1);
        }
        else
        {
            result = 0;
        }
        break;
    case thrash::kStateDither:
        gl::ditherMode(app, cpu, value != 0 ? 2 : 0);
        break;
    case thrash::kStateShade:  // the vertex colour alone, or modulating the texture
    {
        const x86::reg32 local = value == 0 ? 1 : 0;
        put(app, 0xa91f2c, local);
        if (at(app, 0xa92354) == 1)
        {
            gl::colorCombine(app, cpu, 3, 1, local, 1, 0);
            gl::alphaCombine(app, cpu, 3, 1, local, 1, 0);
        }
        else
        {
            gl::colorCombine(app, cpu, 1, 0, local, 2, 0);
            gl::alphaCombine(app, cpu, 1, 0, local, 2, 0);
        }
        break;
    }
    case thrash::kStateTextureFilter:
        gl::texFilterMode(app, cpu, 0, value, value);
        break;
    case thrash::kStateLodBias:
        gl::texLodBiasValue(app, cpu, 0, asFloat(value));
        break;
    case thrash::kStateAntiAlias:
        put(app, 0xa91f20, value);
        drawPointers(app, at(app, 0xa91f24), value);
        break;
    case thrash::kStateTransparency:  // chroma key and alpha test
        if (value == 0)
        {
            gl::chromakeyMode(app, cpu, 0);
            gl::alphaTestFunction(app, cpu, 7);
        }
        else if (value == 1 || value == 2)
        {
            gl::chromakeyMode(app, cpu, value == 1 ? 1 : 0);
            gl::alphaTestFunction(app, cpu, 4);
        }
        else
        {
            result = 0;
        }
        break;
    case thrash::kStateMipFilter:  // mipmapping; 3 is mode 1 drawn in two passes
    {
        x86::reg32 twoPass = 0;
        x86::reg32 mode = value;
        if (value == 3)
        {
            twoPass = 1;
            mode = 1;
            if (slot != 0)
                put(app, slot, 1);  // over the argument, as voodoo2a does
        }
        if (twoPass != at(app, 0xa91f24))
        {
            put(app, 0xa91f24, twoPass);
            gl::alphaBlendFunction(app, cpu, 1, 5, 4, 0);
            gl::texCombine(app, cpu, 0, 1, 0, 1, 0, 0, 0);
        }
        drawPointers(app, at(app, 0xa91f24), at(app, 0xa91f20));
        gl::texMipMapMode(app, cpu, 0, mode, at(app, 0xa91f24));
        break;
    }
    case thrash::kStateChromaKey:
        gl::chromakeyValue(app, cpu, value);
        break;
    case thrash::kStateTextureAddress:  // 0 clamps, anything else wraps
    {
        const x86::reg32 clamp = value == 0 ? 1 : 0;
        gl::texClampMode(app, cpu, 0, clamp, clamp);
        break;
    }
    case thrash::kStateFogDensity:  // fog by density -- 1 / value -- or off
        if (value == 0)
        {
            gl::fogMode(app, cpu, 0);
        }
        else
        {
            gl::fogMode(app, cpu, 2);
            x86::reg8 table[64];
            fogTable(app, cpu, float(1.0 / double(x86::sreg32(value))), table);
            gl::fogTable(app, cpu, table);
            result = 0;  // what voodoo2a gives back here
        }
        break;
    case thrash::kStateFogColour:
        gl::fogColorValue(app, cpu, value);
        break;
    case thrash::kStateWindowMode:
        put(app, 0xa91f44, value);
        break;
    case thrash::kStateLambdas:  // four of a record at once, or all four cleared
        if (value != 0)
        {
            put(app, 0xa91f30, at(app, value + thrash::kLambdaAcquireWindow));
            put(app, 0xa91f3c, at(app, value + thrash::kLambdaExecute));
            put(app, 0xa91f34, at(app, value + thrash::kLambdaLog));
            put(app, 0xa91f38, at(app, value + thrash::kLambdaLockWindow));
        }
        else
        {
            put(app, 0xa91f3c, 0);
            put(app, 0xa91f34, 0);
            put(app, 0xa91f38, 0);
            put(app, 0xa91f30, 0);
        }
        break;
    case thrash::kStateFog:  // fog mode
        if (value == 0)
            gl::fogMode(app, cpu, 0);
        else if (value == 1 || value == 2 || value == 4 || value == 8)
            gl::fogMode(app, cpu, 2);
        else
            result = 0;
        break;
    case thrash::kStateDepthBias:
    case thrash::kStateDepthBiasAlternative:
        gl::depthBiasLevel(app, cpu, x86::sreg16(value));
        break;
    case thrash::kStateWindow:
        put(app, 0xa91f08, value);
        break;
    case thrash::kStateLogLambda:
        put(app, 0xa91f34, value);
        break;
    case thrash::kStateExecuteLambda:
        put(app, 0xa91f3c, value);
        break;
    case thrash::kStateLockWindowLambda:
        put(app, 0xa91f38, value);
        break;
    case thrash::kStateGamma:
        gl::gammaCorrectionValue(app, cpu, asFloat(value));
        break;
    case thrash::kStateFlipRate:
        put(app, 0xa91f0c, value);
        break;
    case thrash::kStateBlend:  // blending
        switch (value)
        {
        case thrash::kBlendSourceAlpha: gl::alphaBlendFunction(app, cpu, 1, 5, 4, 0); break;
        case thrash::kBlendSourceAlphaOne: gl::alphaBlendFunction(app, cpu, 1, 4, 4, 0); break;
        case thrash::kBlendZeroInverseSourceAlpha: gl::alphaBlendFunction(app, cpu, 0, 5, 4, 0); break;
        case thrash::kBlendDestinationColourZero: gl::alphaBlendFunction(app, cpu, 2, 0, 4, 0); break;
        default: result = 0; break;
        }
        break;
    case thrash::kStateFogAlphas:  // fog from the game's own table, or off
        if (value == 0)
        {
            gl::fogMode(app, cpu, 0);
        }
        else
        {
            gl::fogMode(app, cpu, 2);
            gl::fogTable(app, cpu, &app->getMemory<x86::reg8>(value));
        }
        break;
    case thrash::kStateDepthWrite:
        gl::depthMask(app, cpu, value);
        break;
    case thrash::kState107:
        put(app, 0xa91f10, value);
        break;
    case thrash::kState108:
        if (at(app, 0xa91ef8) != 0)
            result = 0;
        else
            gl::sstControl(app, cpu, value != 0 ? 2 : 1);
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

void setStateNative(win32::WinApplication* app, x86::CPU& cpu)
{
    const x86::reg32 esp = cpu.esp;
    cpu.eax = applyState(app, cpu, at(app, esp + 4), at(app, esp + 8), esp + 8);
    cpu.esp = esp + 4 + 8;
}

}

/* The GrVertex THRASH_drawtri and the rest make of one of the game's vertices.
 * voodoo2a's code as the generator makes it does its x87 arithmetic in the
 * FPU's own type without the precision control's rounding (disasm/dll.py), so
 * this does too, operation by operation, in the same order: in plain double,
 * where each product of floats is exact and only the one of three factors and
 * the stores to float round; and under WITH_PEDANTIC_FPU in the x87's 80 bits,
 * which quiet a signalling NaN as they load it.  The colours are the table's
 * floats for the vertex's bytes (VertexColours). */
struct VertexFloats
{
    float x, y, ooz, sow, tow, oow;
};

inline VertexFloats vertexFloats(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale)
{
    typedef x86::Float F;
    const F zk = F(app->getMemory<float>(in + 8)) * F(zScale);
    const F wk = F(app->getMemory<float>(in + 0xc)) * F(wScale);
    VertexFloats out;
    out.x = float(F(app->getMemory<float>(in)));
    out.y = float(F(app->getMemory<float>(in + 4)));
    out.oow = app->getMemory<float>(in + 0xc);
    out.sow = float(F(app->getMemory<float>(in + 0x18)) * wk);
    out.tow = float(wk * F(app->getMemory<float>(in + 0x1c)));
    out.ooz = float(zk);
    return out;
}

inline float colourAt(win32::WinApplication* app, x86::reg32 in, x86::reg32 offset)
{
    return app->getMemory<float>(kColourTable + x86::reg32(app->getMemory<x86::reg8>(in + offset)) * 4);
}

void thrashVertex(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale, win32::GrVertex& out)
{
    const VertexFloats v = vertexFloats(app, in, zScale, wScale);
    out.x = v.x;
    out.y = v.y;
    const x86::reg32 w = app->getMemory<x86::reg32>(in + 0xc);
    std::memcpy(&out.oow, &w, sizeof w);
    out.a = colourAt(app, in, 0x13);
    out.r = colourAt(app, in, 0x12);
    out.g = colourAt(app, in, 0x11);
    out.b = colourAt(app, in, 0x10);
    out.tmuvtx[0].sow = v.sow;
    out.tmuvtx[0].tow = v.tow;
    out.ooz = v.ooz;
}

/* The same vertex straight into a slot of ThrashRenderer's batch: u and v
 * before finishTriangle brings far ones back. */
void thrashBatchVertex(win32::WinApplication* app, x86::reg32 in, float zScale, float wScale, win32::ThrashVertex& out)
{
    const VertexFloats v = vertexFloats(app, in, zScale, wScale);
    out.x = v.x;
    out.y = v.y;
    out.z = v.ooz;
    const x86::reg32 w = app->getMemory<x86::reg32>(in + 0xc);
    std::memcpy(&out.oow, &w, sizeof w);
    out.u = v.sow;
    out.v = v.tow;
    out.color = x86::reg32(x86::reg8(colourAt(app, in, 0x12))) | x86::reg32(x86::reg8(colourAt(app, in, 0x11))) << 8
              | x86::reg32(x86::reg8(colourAt(app, in, 0x10))) << 16
              | x86::reg32(x86::reg8(colourAt(app, in, 0x13))) << 24;
}

/* voodoo2a's exports as the port has them: each a stdcall the game makes
 * through the pointer GetProcAddress gave it (THRASH_opendll). */
void THRASH_about(win32::WinApplication* app, x86::CPU& cpu) { aboutNative(app, cpu); }
void THRASH_clearwindow(win32::WinApplication* app, x86::CPU& cpu) { clearWindowNative(app, cpu); }
void THRASH_clip(win32::WinApplication* app, x86::CPU& cpu) { clipNative(app, cpu); }
void THRASH_drawline(win32::WinApplication* app, x86::CPU& cpu) { drawLineNative(app, cpu); }
void THRASH_drawlinemesh(win32::WinApplication* app, x86::CPU& cpu) { drawLineMeshNative(app, cpu); }
void THRASH_drawlinestrip(win32::WinApplication* app, x86::CPU& cpu) { drawLineStripNative(app, cpu); }
void THRASH_drawpoint(win32::WinApplication* app, x86::CPU& cpu) { drawPointNative(app, cpu); }
void THRASH_drawpointmesh(win32::WinApplication* app, x86::CPU& cpu) { drawPointMeshNative(app, cpu); }
void THRASH_drawpointstrip(win32::WinApplication* app, x86::CPU& cpu) { drawPointStripNative(app, cpu); }
void THRASH_drawquad(win32::WinApplication* app, x86::CPU& cpu) { drawQuadNative(app, cpu); }
void THRASH_drawquadmesh(win32::WinApplication* app, x86::CPU& cpu) { drawQuadMeshNative(app, cpu); }
void THRASH_drawtri(win32::WinApplication* app, x86::CPU& cpu) { drawTriNative(app, cpu); }
void THRASH_drawtrifan(win32::WinApplication* app, x86::CPU& cpu) { drawTriFanNative(app, cpu); }
void THRASH_drawtrimesh(win32::WinApplication* app, x86::CPU& cpu) { drawTriMeshNative(app, cpu); }
void THRASH_drawtristrip(win32::WinApplication* app, x86::CPU& cpu) { drawTriStripNative(app, cpu); }
void THRASH_flushwindow(win32::WinApplication* app, x86::CPU& cpu) { nothingNative(app, cpu); }
void THRASH_idle(win32::WinApplication* app, x86::CPU& cpu) { nothingNative(app, cpu); }
void THRASH_init(win32::WinApplication* app, x86::CPU& cpu) { initNative(app, cpu); }
void THRASH_is(win32::WinApplication* app, x86::CPU& cpu) { isNative(app, cpu); }
void THRASH_lockwindow(win32::WinApplication* app, x86::CPU& cpu) { lockWindowNative(app, cpu); }
void THRASH_pageflip(win32::WinApplication* app, x86::CPU& cpu) { pageFlipNative(app, cpu); }
void THRASH_readrect(win32::WinApplication* app, x86::CPU& cpu) { readRectNative(app, cpu); }
void THRASH_restore(win32::WinApplication* app, x86::CPU& cpu) { restoreNative(app, cpu); }
void THRASH_selectdisplay(win32::WinApplication* app, x86::CPU& cpu) { selectDisplayNative(app, cpu); }
void THRASH_setstate(win32::WinApplication* app, x86::CPU& cpu) { setStateNative(app, cpu); }
void THRASH_settexture(win32::WinApplication* app, x86::CPU& cpu) { setTextureNative(app, cpu); }
void THRASH_setvideomode(win32::WinApplication* app, x86::CPU& cpu) { setVideoModeNative(app, cpu); }
void THRASH_sync(win32::WinApplication* app, x86::CPU& cpu) { syncNative(app, cpu); }
void THRASH_talloc(win32::WinApplication* app, x86::CPU& cpu) { textureAllocateNative(app, cpu); }
void THRASH_treset(win32::WinApplication* app, x86::CPU& cpu) { textureResetNative(app, cpu); }
void THRASH_tupdate(win32::WinApplication* app, x86::CPU& cpu) { textureUpdateNative(app, cpu); }
void THRASH_unlockwindow(win32::WinApplication* app, x86::CPU& cpu) { unlockWindowNative(app, cpu); }
void THRASH_window(win32::WinApplication* app, x86::CPU& cpu) { windowNative(app, cpu); }
void THRASH_writerect(win32::WinApplication* app, x86::CPU& cpu) { writeRectNative(app, cpu); }

/* sub_a84360, which THRASH_setvideomode hands the game to run on its window's
 * thread, message 0x465. */
void THRASH_modemessage(win32::WinApplication* app, x86::CPU& cpu) { windowThreadNative(app, cpu); }

}
