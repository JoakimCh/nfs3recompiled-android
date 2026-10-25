#include "native_guest.h"

#include <iterator>
#include <utility>

/* The menus' drawing: their 3D and 2D, text and shapes.  The sliders -- a
 * value of 0 to 1 dragged along a track, its thumb and the arrows either side
 * of it (0x469xxx) -- and the two-axis sliders (0x46axxx-0x46cxxx), each a
 * record of the menus' controls with its parts' rectangles, its values and
 * the function called when one changes: found under the pointer, moved by the
 * mouse, drawn from the art of their kind (the tables at 0x55a4de, 0x55a4ec,
 * 0x55a96c and 0x678aae).  A menu item's place and size worked out from its
 * text (0x4613e0).  A .qfs loaded by its name (0x4956f0).  The fonts' text
 * scale and the widths of their characters, the fonts' quads flushed
 * (0x4d1340-0x4d1590); a menu shape found by its name, loaded if it is not
 * yet (0x4d5db0); the screen's quads clipped (0x4d5840); rectangles and
 * frames (0x4d8550-0x4d8930); a 2D screen's text and its characters
 * (0x4d9320-0x4da4a0); a quad and a frame of quads in 640 by 480 measure
 * scaled to the screen (0x4db000, 0x4db380).
 *
 * disassemble_nfs3hp.py binds each address to the function of that name here
 * (FRONTEND_DRAW_NATIVES), and the generated code calls it by name.  Written
 * as their code is: each push and pop to the guest's stack, each call with
 * the return address's slot, the frame's locals where the code keeps them,
 * the registers as the code leaves them; the x87's stack pushed and popped a
 * value at a time.  What the menus' other code and the graphics' natives do
 * is called by address, and so is what of this file has a stand-in in
 * tools/game_checks, which holds each against its generated code. */
namespace nfs3hp
{
namespace frontend
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using guest::putByte;
using x86::reg32;
using x86::sreg32;

// The pointer, on a 640 by 480 screen.
constexpr reg32 kPointerX = 0x55e5e4, kPointerY = 0x55e5e8;
// The menus' clock, in ticks.
constexpr reg32 kClock = 0x79c1a4;
// The sliders' kinds: their parts' count (a word each, at 0x55a4e0 + 2 * kind),
// their parts' colours and those of a part under the pointer (0xc0 bytes a
// kind, 0x20 a part), their parts' shapes (0x18 bytes a kind, 4 a part).
constexpr reg32 kSliderParts = 0x55a4de;
constexpr reg32 kPartColours = 0x55a4ec, kHotPartColours = 0x55a96c;
constexpr reg32 kPartShapes = 0x678aae;
// What the menus' code and the graphics' natives do.
constexpr reg32 kChop = 0x4dfd56;            // __CHP: st(0) rounded toward 0
constexpr reg32 kFloor = 0x4f1c30;           // floor of the double on the stack
constexpr reg32 kStrcmp = 0x4ee310, kStrncmp = 0x4eb390, kStrncpy = 0x4e0e30, kToupper = 0x4eede0;
constexpr reg32 kSprintf = 0x4df690;
constexpr reg32 kRenderState = 0x431900;     // graphics::setRenderState: state eax to edx
constexpr reg32 kViewport = 0x4beb80, kSetClip = 0x4bebe0;
constexpr reg32 kDrawArtShape = 0x4d7160, kArtShapeTextures = 0x4d6390;
constexpr reg32 kShadedRectangle = 0x4d81b0;
constexpr reg32 kClipQuad = 0x4c12e0;        // the quad of the four vertices at eax, edx, ebx, ecx clipped and drawn
constexpr reg32 kTextWidth = 0x452020, kLanguageText = 0x4d1850, kSelectFont = 0x452100;
constexpr reg32 kTickWait = 0x4c9860;
// The menus' code of frontend_glue's and the formats': a list's line, a text
// scale for the 2D screens, a 2D screen's text, the quads of a font drawn,
// whether the mouse holds a control, a shape of an .fsh by its name, a .qfs
// file loaded.
constexpr reg32 kListLine = 0x442c80, kScreenTextScale = 0x451530, kScreenText = 0x452190;
constexpr reg32 kDrawQuads = 0x49be40, kMouseHolds = 0x49c080;
constexpr reg32 kFshShape = 0x4ef270, kLoadQfsFile = 0x4f2e20;
// This file's functions with a stand-in of their own: called by address.
constexpr reg32 kSetSliderValue = 0x469480, kTextScale = 0x4d1390, kShapeByName = 0x4d5db0;
constexpr reg32 kDrawScreenText = 0x4da4a0;
// The screen's size, and its clip's outcodes' bounds (graphics).
constexpr reg32 kScreenWidth = 0x7cdac8, kScreenHeight = 0x7cdacc;
constexpr reg32 kClipFar = 0x7d34f8, kClipLeft = 0x7d34fc, kClipBottom = 0x7d3500, kClipTop = 0x7d3504;
constexpr reg32 kClipRight = 0x7d350c;
// The renderer's state bits: 2 for a 3D card's alpha.
constexpr reg32 kRenderFlags = 0x7a3a58;
// The menus' text in the fonts' quads rather than on the 2D screens (not 0).
constexpr reg32 kMenu3d = 0x559234;

void push(win32::WinApplication* app, x86::CPU& cpu, reg32 value)
{
    cpu.esp -= 4;
    put(app, cpu.esp, value);
}

reg32 pop(win32::WinApplication* app, x86::CPU& cpu)
{
    const reg32 value = at(app, cpu.esp);
    cpu.esp += 4;
    return value;
}

x86::reg16 half(win32::WinApplication* app, reg32 address)
{
    return app->getMemory<x86::reg16>(address);
}

void putHalf(win32::WinApplication* app, reg32 address, x86::reg16 value)
{
    app->getMemory<x86::reg16>(address) = value;
}

/* mov r, [address]; sar r, 0x10: the word at address + 2, signed. */
reg32 high(win32::WinApplication* app, reg32 address)
{
    return reg32(sreg32(at(app, address)) >> 16);
}

/* mov eax, v; sar edx, 0x1f; sub eax, edx; sar eax, 1 -- with v in edx: v
 * halved toward 0 in eax, its sign in edx. */
void halve(x86::CPU& cpu, reg32 v)
{
    cpu.edx = reg32(sreg32(v) >> 31);
    cpu.eax = reg32(sreg32(v - cpu.edx) >> 1);
}

/* A call as the code makes it: the return address's slot, and esp as the
 * callee leaves it.  False when the game stopped in it. */
bool direct(win32::WinApplication* app, x86::CPU& cpu, void (*function)(win32::WinApplication*, x86::CPU&))
{
    cpu.esp -= 4;
    function(app, cpu);
    return !cpu.terminate;
}

bool byAddress(win32::WinApplication* app, x86::CPU& cpu, reg32 target)
{
    cpu.esp -= 4;
    app->dynamic_call(target, cpu);
    return !cpu.terminate;
}

x86::Float loadFloat(win32::WinApplication* app, reg32 address)
{
    return x86::Float(app->getMemory<float>(address));
}

x86::Float loadDouble(win32::WinApplication* app, reg32 address)
{
    return x86::Float(app->getMemory<double>(address));
}

void storeFloat(win32::WinApplication* app, reg32 address, const x86::Float& value)
{
    app->getMemory<float>(address) = float(value);
}

void storeDouble(win32::WinApplication* app, reg32 address, const x86::Float& value)
{
    app->getMemory<double>(address) = double(value);
}

/* fild of a dword, of a word. */
x86::Float integer(win32::WinApplication* app, reg32 address)
{
    return x86::Float(sreg32(at(app, address)));
}

x86::Float halfInteger(win32::WinApplication* app, reg32 address)
{
    return x86::Float(x86::sreg16(half(app, address)));
}

/* fistp: st(0) as the control word rounds it, popped. */
void storeInteger(win32::WinApplication* app, x86::CPU& cpu, reg32 address)
{
    put(app, address, reg32(cpu.fpu.toInteger<sreg32>(cpu.fpu.st(0))));
    cpu.fpu.count -= 1;
}

void exchange(x86::CPU& cpu, int i)
{
    std::swap(cpu.fpu.st(0), cpu.fpu.st(i));
}

/* fmul st(i) and the like: st(0) = st(0) op st(i); fmulp st(i) and the like:
 * st(i) = st(i) op st(0), popped. */
void mulTop(x86::CPU& cpu, int i)
{
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(i));
}

void mulPop(x86::CPU& cpu, int i)
{
    cpu.fpu.st(i) = cpu.fpu.mul(cpu.fpu.st(i), cpu.fpu.st(0));
    cpu.fpu.count -= 1;
}

void addPop(x86::CPU& cpu, int i)
{
    cpu.fpu.st(i) = cpu.fpu.add(cpu.fpu.st(i), cpu.fpu.st(0));
    cpu.fpu.count -= 1;
}

void divPop(x86::CPU& cpu, int i)
{
    cpu.fpu.st(i) = cpu.fpu.div(cpu.fpu.st(i), cpu.fpu.st(0));
    cpu.fpu.count -= 1;
}

/* fcomp with `with`, fnstsw ax, sahf: popped. */
void comparePop(x86::CPU& cpu, const x86::Float& with)
{
    cpu.fpu.compare(cpu.fpu.st(0), with);
    cpu.ax = cpu.fpu.status.word;
    cpu.fpu.count -= 1;
}

/* fcompp, fnstsw ax, sahf. */
void compareTwo(x86::CPU& cpu)
{
    cpu.fpu.compare(cpu.fpu.st(0), cpu.fpu.st(1));
    cpu.ax = cpu.fpu.status.word;
    cpu.fpu.count -= 2;
}

/* What sahf makes of the compare: jb, jbe. */
bool below(const x86::CPU& cpu)
{
    return cpu.fpu.status.c0;
}

bool belowOrEqual(const x86::CPU& cpu)
{
    return cpu.fpu.status.c0 || cpu.fpu.status.c3;
}

/* push ebp, mov ebp, esp after the registers named, and sub esp, `locals`;
 * leave it the other way round, ret `popped`. */
void enter(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 locals)
{
    for (reg32* r : saved)
        push(app, cpu, *r);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.esp -= locals;
}

void leave(win32::WinApplication* app, x86::CPU& cpu, std::initializer_list<reg32*> saved, reg32 popped = 0)
{
    cpu.esp = cpu.ebp;
    cpu.ebp = pop(app, cpu);
    for (auto r = std::rbegin(saved); r != std::rend(saved); ++r)
        **r = pop(app, cpu);
    cpu.esp += 4 + popped;
}

/* Signed division of edx:eax by `divisor`, as idiv. */
void idiv(x86::CPU& cpu, reg32 divisor)
{
    const std::int64_t dividend = std::int64_t(std::uint64_t(cpu.edx) << 32 | cpu.eax);
    cpu.eax = reg32(dividend / sreg32(divisor));
    cpu.edx = reg32(dividend % sreg32(divisor));
}

/* rep movsd: ecx dwords from esi to edi. */
void copyDwords(win32::WinApplication* app, x86::CPU& cpu)
{
    for (; cpu.ecx != 0; --cpu.ecx)
    {
        put(app, cpu.edi, at(app, cpu.esi));
        cpu.esi += 4;
        cpu.edi += 4;
    }
}

/* repne scasb: edi past the first al within ecx bytes, ecx counted down. */
void scanBytes(win32::WinApplication* app, x86::CPU& cpu)
{
    while (cpu.ecx != 0)
    {
        const x86::reg8 b = byte(app, cpu.ees + cpu.edi);
        cpu.edi += 1;
        --cpu.ecx;
        if (b == cpu.al)
            break;
    }
}

/* The code's own strcpy of esi to edi, two bytes a turn: esi and edi past
 * the 0's pair, al the last byte copied. */
void copyPairs(win32::WinApplication* app, x86::CPU& cpu)
{
    for (;;)
    {
        cpu.al = byte(app, cpu.esi);
        putByte(app, cpu.edi, cpu.al);
        if (cpu.al == 0)
            break;
        cpu.al = byte(app, cpu.esi + 1);
        cpu.esi += 2;
        putByte(app, cpu.edi + 1, cpu.al);
        cpu.edi += 2;
        if (cpu.al == 0)
            break;
    }
}

/* That copy with edi kept across it (push edi ... pop edi). */
void inlineCopy(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    copyPairs(app, cpu);
    cpu.edi = pop(app, cpu);
}

/* And its strcat of esi onto the text at edi: push edi; sub ecx, ecx; dec ecx;
 * mov al, 0; repne scasb; dec edi -- the copy from there, pop edi. */
void inlineAppend(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edi);
    cpu.ecx = 0xffffffff;
    cpu.al = 0;
    scanBytes(app, cpu);
    cpu.edi -= 1;
    copyPairs(app, cpu);
    cpu.edi = pop(app, cpu);
}

/* The clip's outcode of the vertex at esi into the byte at edi: 0x10 behind
 * the eye, else 8 above, 4 below, 1 left of the clip, 2 right of it -- ebx
 * the code, eax, ecx and edx as the bounds' compares leave them. */
void outcode(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.eax = at(app, cpu.esi + 0xc);
    cpu.ecx = at(app, kClipFar);
    if ((cpu.eax & 0x80000000) != 0 || sreg32(cpu.eax) >= sreg32(cpu.ecx))
    {
        cpu.ebx = 0x10;
    }
    else
    {
        cpu.eax = at(app, cpu.esi + 4);
        cpu.ebx = 0;
        cpu.ecx = at(app, kClipTop);
        cpu.edx = at(app, kClipBottom);
        if ((cpu.eax & 0x80000000) != 0 || sreg32(cpu.eax) < sreg32(cpu.ecx))
            cpu.ebx |= 8;
        else if (sreg32(cpu.eax) > sreg32(cpu.edx))
            cpu.ebx |= 4;
        cpu.eax = at(app, cpu.esi);
        cpu.ecx = at(app, kClipLeft);
        cpu.edx = at(app, kClipRight);
        if ((cpu.eax & 0x80000000) != 0 || sreg32(cpu.eax) < sreg32(cpu.ecx))
            cpu.ebx |= 1;
        else if (sreg32(cpu.eax) > sreg32(cpu.edx))
            cpu.ebx |= 2;
    }
    putByte(app, cpu.edi, cpu.bl);
}

}  // namespace

void sliderThumbPlace(win32::WinApplication* app, x86::CPU& cpu);
void snapToStep(win32::WinApplication* app, x86::CPU& cpu);
void dragSliderTo(win32::WinApplication* app, x86::CPU& cpu);
void twoAxisThumbPlace(win32::WinApplication* app, x86::CPU& cpu);
void dragTwoAxisTo(win32::WinApplication* app, x86::CPU& cpu);
void trackSlider(win32::WinApplication* app, x86::CPU& cpu);
void gradientRectangle(win32::WinApplication* app, x86::CPU& cpu);
void filledRectangle(win32::WinApplication* app, x86::CPU& cpu);
void frame(win32::WinApplication* app, x86::CPU& cpu);
void accentedCharacter(win32::WinApplication* app, x86::CPU& cpu);
void drawScreenCharacter(win32::WinApplication* app, x86::CPU& cpu);
void drawTexturedQuad(win32::WinApplication* app, x86::CPU& cpu);
void drawShadedQuad(win32::WinApplication* app, x86::CPU& cpu);
void sliderPartUnderPointer(win32::WinApplication* app, x86::CPU& cpu);

/* 0x4692c0: the part of the slider at eax under the pointer, or -1. */
void sliderPartUnderPointer(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    cpu.ecx = 0xffffffff;
    cpu.ebx = cpu.eax;
    cpu.eax = 0;
    for (;;)
    {
        cpu.edx = high(app, cpu.ebx + 0x40);
        cpu.edx = high(app, cpu.edx * 2 + kSliderParts);
        if (sreg32(cpu.eax) >= sreg32(cpu.edx))
            break;
        cpu.edx = cpu.eax * 8 + cpu.ebx;
        cpu.esi = high(app, cpu.edx + 0x7c);
        cpu.edi = at(app, kPointerX);
        if (sreg32(cpu.esi) < sreg32(cpu.edi))
        {
            cpu.edi = high(app, cpu.edx + 0x7e);
            cpu.esi += cpu.edi;
            if (sreg32(cpu.esi) > sreg32(at(app, kPointerX)))
            {
                cpu.esi = high(app, cpu.edx + 0x7a);
                cpu.edi = at(app, kPointerY);
                if (sreg32(cpu.esi) < sreg32(cpu.edi))
                {
                    cpu.edx = high(app, cpu.edx + 0x80);
                    cpu.esi += cpu.edx;
                    if (sreg32(cpu.esi) > sreg32(cpu.edi))
                    {
                        cpu.ecx = cpu.eax;
                        break;
                    }
                }
            }
        }
        cpu.eax += 1;
    }
    cpu.eax = cpu.ecx;
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x469340: where the thumb of the slider at eax may go -- its track's start
 * (the track's left and half the thumb's width) to the word at ebx, its end to
 * [ecx], the length between to [[esp+4]], and the thumb's place along it,
 * the length times the value, to [[esp+8]]. */
void sliderThumbPlace(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.edi = at(app, ebp + 0x10);
    cpu.esi = cpu.eax;
    halve(cpu, high(app, cpu.eax + 0x7e));
    cpu.edx = high(app, cpu.esi + 0x84);
    cpu.eax += cpu.edx;
    putHalf(app, cpu.ebx, cpu.ax);
    halve(cpu, high(app, cpu.esi + 0x7e));
    cpu.edx = high(app, cpu.esi + 0x86);
    cpu.edx -= cpu.eax;
    cpu.eax = high(app, cpu.esi + 0x84);
    cpu.eax += cpu.edx;
    putHalf(app, cpu.ecx, cpu.ax);
    cpu.edx = cpu.eax;
    cpu.dx = x86::reg16(cpu.dx - half(app, cpu.ebx));
    cpu.eax = cpu.edi;
    putHalf(app, cpu.edi, cpu.dx);
    cpu.fpu.push(halfInteger(app, cpu.eax));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, cpu.esi + 0x54));
    cpu.edx = at(app, ebp + 0x14);
    if (!byAddress(app, cpu, kChop))
        return;
    storeInteger(app, cpu, ebp - 4);
    cpu.eax = at(app, ebp - 4);
    putHalf(app, cpu.edx, cpu.ax);
    leave(app, cpu, {&cpu.esi, &cpu.edi}, 8);
}

/* 0x4693c0: the value [esp+8] snapped to the step [esp+4] -- to the step
 * below it, or the one above where it is past [0x53ae50] of the way -- and
 * kept within 0 and 1, onto the x87's stack.  A step past 1 is 1, one below 0
 * none. */
void snapToStep(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.eax, &cpu.ebx}, 0x10);
    const reg32 ebp = cpu.ebp;
    bool snap = true;
    if (sreg32(at(app, ebp + 0x10)) > sreg32(0x3f800000))
    {
        put(app, ebp + 0x10, 0x3f800000);
    }
    else
    {
        cpu.fpu.push(0.0);
        comparePop(cpu, loadFloat(app, ebp + 0x14));
        if (!belowOrEqual(cpu))
        {
            cpu.ebx = 0;
            put(app, ebp + 0x10, cpu.ebx);
        }
        snap = (at(app, ebp + 0x10) & 0x7fffffff) != 0;
    }
    if (snap)
    {
        cpu.fpu.push(loadFloat(app, ebp + 0x14));
        cpu.fpu.st(0) = cpu.fpu.div(cpu.fpu.st(0), loadFloat(app, ebp + 0x10));
        cpu.esp -= 8;
        storeFloat(app, ebp - 0x10, cpu.fpu.st(0));
        storeDouble(app, cpu.esp, cpu.fpu.pop());
        if (!byAddress(app, cpu, kFloor))
            return;
        cpu.fpu.push(loadFloat(app, ebp - 0x10));
        exchange(cpu, 1);
        storeFloat(app, ebp - 8, cpu.fpu.pop());
        cpu.fpu.st(0) = cpu.fpu.sub(cpu.fpu.st(0), loadFloat(app, ebp - 8));
        cpu.fpu.st(0) = cpu.fpu.abs(cpu.fpu.st(0));
        storeFloat(app, ebp - 0xc, cpu.fpu.pop());
        if ((at(app, ebp - 0xc) & 0x7fffffff) != 0)
        {
            cpu.fpu.push(loadFloat(app, ebp - 0xc));
            comparePop(cpu, loadFloat(app, 0x53ae50));
            if (!below(cpu))
            {
                cpu.fpu.push(1.0);
                cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 8));
            }
            else
            {
                cpu.fpu.push(loadFloat(app, ebp - 8));
            }
            cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x10));
            storeFloat(app, ebp - 4, cpu.fpu.pop());
        }
        else
        {
            cpu.eax = at(app, ebp + 0x14);
            put(app, ebp - 4, cpu.eax);
        }
    }
    else
    {
        cpu.eax = at(app, ebp + 0x14);
        put(app, ebp - 4, cpu.eax);
    }
    if (sreg32(at(app, ebp - 4)) > sreg32(0x3f800000))
    {
        put(app, ebp - 4, 0x3f800000);
    }
    else
    {
        cpu.fpu.push(0.0);
        comparePop(cpu, loadFloat(app, ebp - 4));
        if (!belowOrEqual(cpu))
        {
            cpu.ebx = 0;
            put(app, ebp - 4, cpu.ebx);
        }
    }
    cpu.fpu.push(loadFloat(app, ebp - 4));
    leave(app, cpu, {&cpu.eax, &cpu.ebx}, 8);
}

/* 0x469480: the slider at eax set to the value [esp+4], within 0 and 1 and
 * snapped to its step: its thumb moved there, and its function told. */
void setSliderValue(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 0x18);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.fpu.push(loadFloat(app, ebp + 0x18));
    cpu.fpu.push(1.0);
    exchange(cpu, 1);
    storeDouble(app, ebp - 0x18, cpu.fpu.pop());
    comparePop(cpu, loadDouble(app, ebp - 0x18));
    if (below(cpu))
    {
        put(app, ebp + 0x18, 0x3f800000);
    }
    else
    {
        cpu.fpu.push(0.0);
        comparePop(cpu, loadDouble(app, ebp - 0x18));
        if (!belowOrEqual(cpu))
        {
            cpu.ecx = 0;
            put(app, ebp + 0x18, cpu.ecx);
        }
    }
    push(app, cpu, at(app, ebp + 0x18));
    push(app, cpu, at(app, cpu.esi + 0x44));
    if (!direct(app, cpu, snapToStep))
        return;
    storeFloat(app, ebp + 0x18, cpu.fpu.pop());
    cpu.eax = at(app, ebp + 0x18);
    put(app, cpu.esi + 0x54, cpu.eax);
    cpu.eax = ebp - 4;
    cpu.ecx = ebp - 0xc;
    push(app, cpu, cpu.eax);
    cpu.eax = ebp - 8;
    cpu.ebx = ebp - 0x10;
    push(app, cpu, cpu.eax);
    cpu.edx = 0;
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, sliderThumbPlace))
        return;
    halve(cpu, high(app, cpu.esi + 0x7e));
    cpu.ecx = high(app, ebp - 0x12);
    cpu.edx = high(app, ebp - 6);
    cpu.edx += cpu.ecx;
    cpu.edx -= cpu.eax;
    cpu.ebx = at(app, cpu.esi + 0x78);
    putHalf(app, cpu.esi + 0x7e, cpu.dx);
    if (cpu.ebx != 0)
    {
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, at(app, cpu.esi + 0x78)))
            return;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi}, 8);
}

/* 0x469520: the value of the slider at eax, onto the x87's stack. */
void sliderStoredValue(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.fpu.push(loadFloat(app, cpu.eax + 0x54));
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x469590: the slider at eax dragged to dx along its track: its value that
 * far of the track's length, snapped to its step, its thumb moved there and
 * its function told. */
void dragSliderTo(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x1c);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    cpu.eax = ebp - 4;
    cpu.ecx = ebp - 8;
    push(app, cpu, cpu.eax);
    cpu.eax = ebp - 0x18;
    cpu.ebx = ebp - 0x14;
    push(app, cpu, cpu.eax);
    cpu.edx = 0;
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, sliderThumbPlace))
        return;
    if (x86::sreg16(cpu.di) < 0)
    {
        cpu.edx = 0;
        putHalf(app, ebp - 4, cpu.dx);
    }
    else
    {
        cpu.eax = high(app, ebp - 0x1a);
        cpu.edx = reg32(x86::sreg16(cpu.di));
        if (sreg32(cpu.edx) > sreg32(cpu.eax))
        {
            cpu.eax = at(app, ebp - 0x18);
            putHalf(app, ebp - 4, cpu.ax);
        }
        else
        {
            putHalf(app, ebp - 4, cpu.di);
        }
    }
    cpu.eax = at(app, ebp - 4);
    put(app, ebp - 0x10, cpu.eax);
    cpu.eax = at(app, ebp - 0x18);
    put(app, ebp - 0xc, cpu.eax);
    cpu.fpu.push(halfInteger(app, ebp - 0x10));
    cpu.fpu.push(halfInteger(app, ebp - 0xc));
    divPop(cpu, 1);
    storeFloat(app, ebp - 0x1c, cpu.fpu.pop());
    push(app, cpu, at(app, ebp - 0x1c));
    push(app, cpu, at(app, cpu.esi + 0x44));
    if (!direct(app, cpu, snapToStep))
        return;
    storeFloat(app, ebp - 0x1c, cpu.fpu.pop());
    cpu.eax = at(app, ebp - 0x1c);
    put(app, cpu.esi + 0x54, cpu.eax);
    cpu.eax = ebp - 4;
    cpu.ecx = ebp - 8;
    push(app, cpu, cpu.eax);
    cpu.eax = ebp - 0x18;
    cpu.ebx = ebp - 0x14;
    push(app, cpu, cpu.eax);
    cpu.edx = 0;
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, sliderThumbPlace))
        return;
    halve(cpu, high(app, cpu.esi + 0x7e));
    cpu.ebx = high(app, ebp - 0x16);
    cpu.edx = high(app, ebp - 6);
    cpu.edx += cpu.ebx;
    cpu.edx -= cpu.eax;
    putHalf(app, cpu.esi + 0x7e, cpu.dx);
    if (at(app, cpu.esi + 0x78) != 0)
    {
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, at(app, cpu.esi + 0x78)))
            return;
    }
    leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x46afd0: value edx of the two-axis slider at eax, onto the x87's stack. */
void twoAxisValue(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.fpu.push(loadFloat(app, cpu.eax + cpu.edx * 4 + 0x54));
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4956f0: the .qfs file named at eax loaded (the formats' 0x4f2e20,
 * eax its result): the name copied into the frame, [0x55e544]'s extension put
 * after it where it has none of its own. */
void loadQfs(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0x200);
    cpu.ebp -= 0x27e;
    const reg32 name = cpu.ebp + 0x7e;
    cpu.edi = name;
    cpu.esi = cpu.eax;
    inlineCopy(app, cpu);
    cpu.edi = name;
    cpu.ecx = 0xffffffff;
    cpu.eax = 0;
    scanBytes(app, cpu);
    cpu.ecx = ~cpu.ecx - 1;
    cpu.eax = name + cpu.ecx;
    // Back from its end to a '.', ':', '/' or '\\', or its start.
    for (;;)
    {
        cpu.eax -= 1;
        cpu.ecx = name;
        if (cpu.eax <= cpu.ecx)
            break;
        cpu.bl = byte(app, cpu.eax);
        if (cpu.bl == '.' || cpu.bl == ':' || cpu.bl == '/' || cpu.bl == '\\')
            break;
    }
    if (byte(app, cpu.eax) != '.')
    {
        cpu.edi = name;
        cpu.esi = at(app, 0x55e544);
        inlineAppend(app, cpu);
    }
    cpu.eax = name;
    if (!byAddress(app, cpu, kLoadQfsFile))
        return;
    cpu.esp = cpu.ebp + 0x27e;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4d1340: the fonts' quads (0x7f74c0, 0x81b4d0) drawn, render state 0x2bf
 * on for them on a card with alpha. */
void flushFonts(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.edx}, 0);
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.edx = 1;
        cpu.eax = 0x2bf;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    cpu.eax = 0x7f74c0;
    if (!byAddress(app, cpu, kDrawQuads))
        return;
    cpu.eax = 0x81b4d0;
    if (!byAddress(app, cpu, kDrawQuads))
        return;
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.eax = 0x2bf;
        cpu.edx = 0;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    leave(app, cpu, {&cpu.edx});
}

/* 0x4d1390: the fonts' text scale [0x840190] set to the float [esp+4], the
 * one before onto the x87's stack.  The size the characters are drawn at
 * [0x84018c] follows it: where the fonts are scaled to the screen
 * ([0x840188]), the screen's width times [0x540bc8] -- the small font
 * ([0x840184] 1) below a scale of 1 -- else the scale itself. */
void setTextScale(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.eax, &cpu.edx, &cpu.esi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.eax = at(app, 0x840190);
    put(app, ebp - 4, cpu.eax);
    cpu.eax = at(app, ebp + 0x14);
    cpu.edx = at(app, 0x840188);
    put(app, 0x840190, cpu.eax);
    if (cpu.edx != 0)
    {
        if (sreg32(cpu.eax) < sreg32(0x3f800000))
        {
            put(app, 0x840184, 1);
        }
        else
        {
            cpu.esi = 0;
            put(app, 0x840184, cpu.esi);
        }
        cpu.fpu.push(integer(app, kScreenWidth));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x540bc8));
        storeFloat(app, 0x84018c, cpu.fpu.pop());
    }
    else
    {
        put(app, 0x84018c, cpu.eax);
    }
    cpu.fpu.push(loadFloat(app, ebp - 4));
    leave(app, cpu, {&cpu.eax, &cpu.edx, &cpu.esi}, 4);
}

/* 0x4d1400: the text scale kept ([0x561b40]), eax it. */
void keepTextScale(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = at(app, 0x840190);
    put(app, 0x561b40, cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4d1410: the text scale kept put back. */
void restoreTextScale(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    push(app, cpu, at(app, 0x561b40));
    if (!byAddress(app, cpu, kTextScale))
        return;
    cpu.fpu.pop();
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4d1540, 0x4d1590: character al's width in the font [0x840184] (its byte
 * at 0x83fde0, 0xe0 a font), and its overhang (a signed byte at 0x83fa60):
 * times the characters' size, whole pixels toward 0, in eax. */
void characterWidth(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.edx}, 8);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = 0;
    cpu.cl = cpu.al;
    cpu.eax = at(app, 0x840184) << 5;
    cpu.edx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.edx;
    cpu.edx = cpu.ecx + cpu.eax;
    cpu.eax = 0;
    cpu.al = byte(app, cpu.edx + 0x83fde0);
    put(app, ebp - 4, cpu.eax);
    cpu.fpu.push(halfInteger(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x84018c));
    if (!byAddress(app, cpu, kChop))
        return;
    storeInteger(app, cpu, ebp - 8);
    cpu.eax = at(app, ebp - 8);
    leave(app, cpu, {&cpu.ecx, &cpu.edx});
}

void characterOverhang(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.edx}, 8);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = 0;
    cpu.cl = cpu.al;
    cpu.eax = at(app, 0x840184) << 5;
    cpu.edx = cpu.eax;
    cpu.eax = (cpu.eax << 3) - cpu.edx;
    cpu.ax = x86::reg16(x86::sreg8(byte(app, cpu.ecx + cpu.eax + 0x83fa60)));
    put(app, ebp - 4, cpu.eax);
    cpu.fpu.push(halfInteger(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x84018c));
    if (!byAddress(app, cpu, kChop))
        return;
    storeInteger(app, cpu, ebp - 8);
    cpu.eax = at(app, ebp - 8);
    leave(app, cpu, {&cpu.ecx, &cpu.edx});
}

/* 0x4d5840: the clip's outcodes of the four vertices of each of eax quads --
 * four indices each, 0x10 bytes, from ebx -- of the vertices at edx (0x20
 * bytes each, the code at 0x14). */
void quadOutcodes(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    put(app, ebp - 0x10, cpu.eax);
    put(app, ebp - 8, cpu.edx);
    put(app, ebp - 4, cpu.ebx);
    cpu.edx = 0;
    put(app, ebp - 0xc, cpu.edx);
    for (;;)
    {
        cpu.eax = at(app, ebp - 0xc);
        if (sreg32(cpu.eax) >= sreg32(at(app, ebp - 0x10)))
            break;
        // Each corner's vertex, the code holding the vertices' address in
        // another register each time.
        reg32* const held[] = {&cpu.ebx, &cpu.edi, &cpu.eax, &cpu.edx};
        for (reg32 corner = 0; corner < 4; ++corner)
        {
            cpu.eax = at(app, ebp - 4);
            cpu.esi = at(app, cpu.eax + 4 * corner);
            *held[corner] = at(app, ebp - 8);
            cpu.esi = (cpu.esi << 5) + *held[corner];
            cpu.edi = cpu.esi + 0x14;
            outcode(app, cpu);
        }
        cpu.ecx = at(app, ebp - 0xc) + 1;
        cpu.ebx = at(app, ebp - 4) + 0x10;
        put(app, ebp - 0xc, cpu.ecx);
        put(app, ebp - 4, cpu.ebx);
    }
    leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x4d5db0: the menus' shape named at eax (4 characters): its number among
 * the shapes known (0x8b48c0, 0x14 bytes each, the name at 0x10; [0x8b7628]
 * of them); else, after a tick, found in the menus' art [0x559228] and its
 * textures made -- its number then, its name kept -- or 0. */
void shapeByName(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0);
    cpu.ecx = cpu.eax;
    cpu.esi = 0;
    cpu.edi = 0;
    for (;;)
    {
        if (sreg32(cpu.esi) >= sreg32(at(app, 0x8b7628)))
        {
            if (!byAddress(app, cpu, kTickWait))
                return;
            cpu.eax = at(app, 0x559228);
            cpu.edx = cpu.ecx;
            if (!byAddress(app, cpu, kFshShape))
                return;
            if (cpu.eax != 0)
            {
                cpu.edx = 0;
                if (!byAddress(app, cpu, kArtShapeTextures))
                    return;
                cpu.edi = cpu.eax;
                if (cpu.eax != 0)
                {
                    cpu.eax = ((cpu.eax << 2) + cpu.edi) << 2;
                    cpu.ebx = 4;
                    cpu.eax += 0x8b48c0;
                    cpu.edx = cpu.ecx;
                    cpu.eax += 0x10;
                    if (!byAddress(app, cpu, kStrncpy))
                        return;
                }
            }
            cpu.eax = cpu.edi;
            break;
        }
        cpu.eax = ((cpu.esi * 4 + cpu.esi) << 2) + 0x8b48c0;
        cpu.ebx = 4;
        cpu.edx = cpu.ecx;
        cpu.eax += 0x10;
        if (!byAddress(app, cpu, kStrncmp))
            return;
        if (cpu.eax == 0)
        {
            cpu.eax = cpu.esi;
            break;
        }
        cpu.esi += 1;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi});
}

/* 0x4d7990: the art shape eax drawn at edx, ebx, opaque (ecx -1). */
void drawShape(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx}, 0);
    cpu.ecx = 0xffffffff;
    if (!byAddress(app, cpu, kDrawArtShape))
        return;
    leave(app, cpu, {&cpu.ecx});
}

/* 0x4d8550: the rectangle eax, edx to ebx, ecx shaded from the colour
 * [esp+4] to [esp+8] and back (graphics::drawShadedRectangle's corners). */
void gradientRectangle(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0);
    const reg32 ebp = cpu.ebp;
    cpu.edi = at(app, ebp + 0x10);
    cpu.esi = at(app, ebp + 0x14);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.edi);
    if (!byAddress(app, cpu, kShadedRectangle))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 8;
}

/* 0x4d8910: the rectangle at eax, edx, ebx wide and ecx high, in the colour
 * [esp+4]. */
void filledRectangle(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi}, 0);
    cpu.esi = at(app, cpu.ebp + 0xc);
    push(app, cpu, cpu.esi);
    push(app, cpu, cpu.esi);
    cpu.ecx += cpu.edx;
    cpu.ebx += cpu.eax;
    if (!direct(app, cpu, gradientRectangle))
        return;
    cpu.ebp = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 4;
}

/* 0x4d8930: a frame a pixel wide around the rectangle at eax, edx, ebx wide
 * and ecx high, in the colour [esp+4] -- render state 6 on for it on a card
 * with alpha. */
void frame(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0x18);
    const reg32 ebp = cpu.ebp;
    put(app, ebp - 8, cpu.eax);
    put(app, ebp - 4, cpu.edx);
    put(app, ebp - 0xc, cpu.ebx);
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.edx = 1;
        cpu.eax = 6;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    // Its left.
    cpu.edx = at(app, ebp + 0x10);
    cpu.eax = at(app, ebp - 4);
    cpu.edi = at(app, ebp - 4);
    cpu.esi = at(app, ebp - 8);
    cpu.ebx = at(app, ebp - 8);
    push(app, cpu, cpu.edx);
    cpu.edi -= 1;
    cpu.esi -= 1;
    cpu.eax += cpu.ecx;
    push(app, cpu, cpu.edx);
    put(app, ebp - 0x18, cpu.eax);
    cpu.eax += 1;
    cpu.edx = cpu.edi;
    put(app, ebp - 0x14, cpu.eax);
    cpu.ecx = cpu.eax;
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, gradientRectangle))
        return;
    // Its right.
    cpu.eax = at(app, ebp + 0x10);
    push(app, cpu, cpu.eax);
    cpu.ecx = at(app, ebp - 0xc);
    push(app, cpu, cpu.eax);
    cpu.eax = at(app, ebp - 8) + cpu.ecx;
    cpu.ecx = cpu.eax + 1;
    cpu.edx = cpu.edi;
    put(app, ebp - 0x10, cpu.ecx);
    cpu.ecx = at(app, ebp - 0x14);
    cpu.ebx = at(app, ebp - 0x10);
    if (!direct(app, cpu, gradientRectangle))
        return;
    // Its top.
    cpu.ebx = at(app, ebp + 0x10);
    push(app, cpu, cpu.ebx);
    cpu.ecx = at(app, ebp - 4);
    cpu.edx = cpu.edi;
    push(app, cpu, cpu.ebx);
    cpu.eax = cpu.esi;
    cpu.ebx = at(app, ebp - 0x10);
    if (!direct(app, cpu, gradientRectangle))
        return;
    // Its bottom.
    cpu.edx = at(app, ebp + 0x10);
    push(app, cpu, cpu.edx);
    cpu.ecx = at(app, ebp - 0x14);
    cpu.ebx = at(app, ebp - 0x10);
    push(app, cpu, cpu.edx);
    cpu.eax = cpu.esi;
    cpu.edx = at(app, ebp - 0x18);
    if (!direct(app, cpu, gradientRectangle))
        return;
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.eax = 6;
        cpu.edx = 0;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    leave(app, cpu, {&cpu.esi, &cpu.edi}, 4);
}

/* 0x4d9320: where character al is among the 2D screens' accented ones (the
 * text at [0x564180]): 0xe0 and its place, or 0xe0 where it is not.  Upper
 * case first -- the characters from 0xe0 by taking 0x20 off, the others by
 * toupper; in French ([0x6fbb4c] 2) an e acute is an E. */
void accentedCharacter(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx}, 0);
    cpu.ecx = 0xe0;
    cpu.ebx = at(app, 0x6fbb4c);
    cpu.edx = at(app, 0x564180);
    bool upper = true;
    if (cpu.ebx == 2 && (cpu.al == 0xc9 || cpu.al == 0xe9))
        cpu.al = 0x65;
    else if (cpu.al >= 0xe0)
    {
        cpu.al -= 0x20;
        upper = false;
    }
    if (upper)
    {
        cpu.eax &= 0xff;
        if (!byAddress(app, cpu, kToupper))
            return;
    }
    for (;;)
    {
        cpu.ah = byte(app, cpu.edx);
        if (cpu.ah == 0)
        {
            cpu.eax = 0xe0;
            break;
        }
        if (cpu.al == cpu.ah)
        {
            cpu.eax = cpu.ecx;
            break;
        }
        cpu.edx += 1;
        cpu.ecx += 1;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4da4a0: the text at eax drawn on a 2D screen at x edx, y ebx, ecx the
 * height of its characters: each character's square of the font (its
 * tables at 0x8b763c, 0x8b774a, 0x8b7858, 0x8b7966) drawn, the next where
 * that one's width leaves it -- the text's width in eax, or 0 on the 3D card.
 * The colour is [0x563aa4] | [0x559434]; in the accented font ([0x664650]
 * 0x24) a character is found among the accented ones. */
void drawScreenText(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    cpu.edi = cpu.eax;
    cpu.esi = cpu.edx;
    put(app, ebp - 0xc, cpu.ebx);
    put(app, ebp - 8, cpu.ecx);
    put(app, ebp - 0x10, cpu.edx);
    if (at(app, kMenu3d) != 0)
    {
        cpu.eax = 0;
    }
    else
    {
        cpu.eax = at(app, 0x563aa4) | at(app, 0x559434);
        cpu.edx = at(app, 0x8b7624);
        put(app, ebp - 4, cpu.eax);
        cpu.eax = 1;
        if (!byAddress(app, cpu, kRenderState))
            return;
        for (;;)
        {
            cpu.ah = byte(app, cpu.edi);
            if (cpu.ah == 0)
                break;
            cpu.ebx = at(app, 0x664650);
            cpu.dl = cpu.ah;
            if (cpu.ebx == 0x24)
            {
                cpu.eax = 0;
                cpu.al = cpu.dl;
                if (!direct(app, cpu, accentedCharacter))
                    return;
            }
            else
            {
                cpu.eax = 0;
                cpu.al = cpu.dl;
                cpu.eax -= 0x20;
            }
            cpu.ebx = at(app, ebp - 8);
            cpu.ecx = 0;
            push(app, cpu, cpu.ebx);
            cpu.cl = byte(app, cpu.eax + 0x8b7966);
            cpu.edx &= 0xff;
            push(app, cpu, cpu.edx);
            cpu.edx = at(app, ebp - 4);
            push(app, cpu, cpu.edx);
            cpu.edx = 0;
            cpu.dl = byte(app, cpu.eax + 0x8b763c);
            push(app, cpu, cpu.edx);
            cpu.edx = 0;
            push(app, cpu, cpu.ecx);
            cpu.dl = byte(app, cpu.eax + 0x8b774a);
            cpu.al = byte(app, cpu.eax + 0x8b7858);
            cpu.ecx = at(app, ebp - 0xc);
            cpu.eax &= 0xff;
            cpu.ebx = cpu.esi;
            if (!direct(app, cpu, drawScreenCharacter))
                return;
            cpu.edi += 1;
            cpu.esi += cpu.eax;
        }
        cpu.ecx = at(app, ebp - 0x10);
        cpu.eax = cpu.esi - cpu.ecx;
    }
    leave(app, cpu, {&cpu.esi, &cpu.edi});
}

void keepTextScale(win32::WinApplication* app, x86::CPU& cpu);
void restoreTextScale(win32::WinApplication* app, x86::CPU& cpu);
void characterWidth(win32::WinApplication* app, x86::CPU& cpu);
void characterOverhang(win32::WinApplication* app, x86::CPU& cpu);

namespace
{

/* The height of a line of the fonts' text on the 3D card, from an 'A': its
 * width and its overhang each times [0x53a9f4] over the screen's height,
 * whole pixels toward 0, to the item at ebx's word 0x20. */
bool fontLineHeight(win32::WinApplication* app, x86::CPU& cpu)
{
    const reg32 ebp = cpu.ebp;
    cpu.eax = 0x41;
    if (!direct(app, cpu, characterWidth))
        return false;
    put(app, ebp - 4, cpu.eax);
    cpu.fpu.push(integer(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53a9f4));
    cpu.fpu.push(integer(app, kScreenHeight));
    divPop(cpu, 1);
    cpu.eax = 0x41;
    storeDouble(app, ebp - 0x14, cpu.fpu.pop());
    if (!direct(app, cpu, characterOverhang))
        return false;
    put(app, ebp - 4, cpu.eax);
    cpu.fpu.push(integer(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53a9f4));
    cpu.fpu.push(integer(app, kScreenHeight));
    divPop(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadDouble(app, ebp - 0x14));
    if (!byAddress(app, cpu, kChop))
        return false;
    storeInteger(app, cpu, ebp - 4);
    cpu.eax = at(app, ebp - 4);
    putHalf(app, cpu.ebx + 0x20, cpu.ax);
    return true;
}

}  // namespace

/* 0x4613e0: the place and size of the menu item at eax (its x and y at 0x1c
 * and 0x1a, its width and height at 0x1e and 0x20) from its kind's
 * (0x40 bytes a kind at 0x559fe8) and its own, and from its text: the text
 * at 0x3c -- with " ..." after it (0x53a9c0, or 0x53a9c8 in German) where it
 * opens a list (0x40, without 0x58) or names the controls' or the
 * graphics' screen (0x44, 0x53a5fc or 0x53a65c) -- measured in the 2D
 * screens' font, a line of the fonts high on the 3D card; a title (kind 3)
 * in their text scale 0.6, a list (kind 0xf) as wide as its line's text.
 * Then placed by its alignment (0x56): to the left of x, about it, or right
 * of it -- a title on the 3D card with a margin. */
void layoutMenuItem(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0x114);
    const reg32 ebp = cpu.ebp;
    const reg32 text = ebp - 0x114;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    cpu.edx = cpu.eax;
    cpu.ecx = 0x40;
    cpu.edi = text;
    cpu.esi = 0x45ccd0;
    copyDwords(app, cpu);
    cpu.ecx = 0;
    put(app, ebp - 0xc, cpu.ecx);
    cpu.esi = high(app, cpu.eax + 0x46);
    cpu.ebx = cpu.eax;
    put(app, ebp - 8, cpu.ecx);
    cpu.esi <<= 6;
    cpu.edi = at(app, cpu.edx + 0x46);
    cpu.ax = half(app, cpu.esi + 0x559fe8);
    cpu.cx = half(app, cpu.esi + 0x55a014);
    cpu.si = half(app, cpu.edx + 6);
    cpu.eax += cpu.ecx;
    cpu.edi = reg32(sreg32(cpu.edi) >> 16);
    cpu.eax += cpu.esi;
    cpu.edi <<= 6;
    putHalf(app, cpu.edx + 0x1c, cpu.ax);
    cpu.ax = x86::reg16(half(app, cpu.edi + 0x559fec) + half(app, cpu.edi + 0x55a018));
    cpu.si = half(app, cpu.edx + 8);
    cpu.eax += cpu.esi;
    putHalf(app, cpu.edx + 0x1a, cpu.ax);
    cpu.eax = high(app, cpu.edx + 0x46) << 6;
    cpu.ax = half(app, cpu.eax + 0x55a01c);
    putHalf(app, cpu.edx + 0x1e, cpu.ax);
    cpu.eax = high(app, cpu.edx + 0x46) << 6;
    cpu.ax = half(app, cpu.eax + 0x55a020);
    cpu.esi = at(app, cpu.edx + 0x3c);
    putHalf(app, cpu.edx + 0x20, cpu.ax);
    if (cpu.esi != 0)
    {
        cpu.edi = text;
        inlineCopy(app, cpu);
        bool more = false;
        if (at(app, cpu.edx + 0x40) != 0 && at(app, cpu.edx + 0x58) == 0)
        {
            more = true;
        }
        else
        {
            cpu.ecx = at(app, cpu.ebx + 0x44);
            if (cpu.ecx != 0)
            {
                cpu.edx = 0x53a5fc;
                cpu.eax = cpu.ecx;
                if (!byAddress(app, cpu, kStrcmp))
                    return;
                if (cpu.eax == 0)
                {
                    more = true;
                }
                else
                {
                    cpu.edx = 0x53a65c;
                    cpu.eax = at(app, cpu.ebx + 0x44);
                    if (!byAddress(app, cpu, kStrcmp))
                        return;
                    more = cpu.eax == 0;
                }
            }
        }
        if (more)
        {
            cpu.esi = at(app, 0x6fbb4c) == 1 ? 0x53a9c0 : 0x53a9c8;
            cpu.edi = text;
            inlineAppend(app, cpu);
        }
    }
    else
    {
        cpu.ah = 0;
        putByte(app, text, cpu.ah);
    }
    // Its size, by its kind.
    cpu.ax = half(app, cpu.ebx + 0x48);
    if (cpu.ax == 3)
    {
        if (at(app, kMenu3d) != 0)
        {
            if (!direct(app, cpu, keepTextScale))
                return;
            push(app, cpu, 0x3f19999a);
            if (!byAddress(app, cpu, kScreenTextScale))
                return;
            cpu.di = half(app, cpu.ebx + 0x1a);
            cpu.edx = 0x12;
            cpu.edi -= 1;
            cpu.eax = text;
            putHalf(app, cpu.ebx + 0x1a, cpu.di);
            if (!byAddress(app, cpu, kTextWidth))
                return;
            cpu.eax += 0xa;
            put(app, ebp - 4, cpu.eax);
            cpu.fpu.push(integer(app, ebp - 4));
            cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, 0x53a9f0));
            putHalf(app, cpu.ebx + 0x20, 0x16);
            if (!byAddress(app, cpu, kChop))
                return;
            storeInteger(app, cpu, ebp - 4);
            cpu.eax = at(app, ebp - 4);
            putHalf(app, cpu.ebx + 0x1e, cpu.ax);
            if (!direct(app, cpu, restoreTextScale))
                return;
        }
    }
    else if (cpu.ax <= 2 || cpu.ax == 0xf)
    {
        if (cpu.ax == 0)
        {
            cpu.edx = 0x12;
            cpu.eax = text;
            if (!byAddress(app, cpu, kTextWidth))
                return;
            putHalf(app, cpu.ebx + 0x1e, cpu.ax);
        }
        if (at(app, kMenu3d) != 0 && !fontLineHeight(app, cpu))
            return;
    }
    // Its place.
    if (half(app, cpu.ebx + 0x48) == 0xf)
    {
        cpu.esi = high(app, cpu.ebx + 0x1c);
        cpu.edx = at(app, cpu.ebx + 0x58);
        if (cpu.edx == 0)
            return done();
        cpu.eax = cpu.edx;
        if (byte(app, cpu.edx) == 0)
            return done();
        cpu.edx = ebp - 0xc;
        if (!byAddress(app, cpu, kListLine))
            return;
        if (cpu.eax != 0)
        {
            cpu.edx = at(app, at(app, ebp - 0xc));
            cpu.eax = reg32(x86::sreg16(half(app, cpu.eax + cpu.edx * 2)));
            if (!byAddress(app, cpu, kLanguageText))
                return;
            if (cpu.eax != 0)
            {
                cpu.edx = 0x12;
                if (!byAddress(app, cpu, kTextWidth))
                    return;
                put(app, ebp - 8, cpu.eax);
            }
        }
        cpu.edx = x86::sreg16(half(app, cpu.ebx + 0x5e)) > 0 ? high(app, cpu.ebx + 0x5c) : 0x32;
        cpu.al = byte(app, cpu.ebx + 0x5c);
        if (cpu.al == 1)
        {
            cpu.eax = at(app, ebp - 8) + cpu.edx;
            putHalf(app, cpu.ebx + 0x1e, cpu.ax);
        }
        else if (cpu.al != 2)
        {
            cpu.ax = half(app, cpu.ebx + 6);
            cpu.eax -= cpu.edx;
            cpu.edx += cpu.esi;
            putHalf(app, cpu.ebx + 0x1c, cpu.ax);
            putHalf(app, cpu.ebx + 0x1e, cpu.dx);
        }
        return done();
    }
    cpu.ax = half(app, cpu.ebx + 0x56);
    if (cpu.ax == 1)
    {
        if (half(app, cpu.ebx + 0x48) != 3 || at(app, kMenu3d) == 0)
        {
            cpu.cx = half(app, cpu.ebx + 0x1c);
            cpu.ax = half(app, cpu.ebx + 0x1e);
            cpu.ecx -= cpu.eax;
            putHalf(app, cpu.ebx + 0x1c, cpu.cx);
            return done();
        }
        cpu.eax = high(app, cpu.ebx + 0x1a);
        cpu.edx = high(app, cpu.ebx + 0x1c);
        cpu.eax = cpu.eax - cpu.edx + 5;
        put(app, ebp - 4, cpu.eax);
        cpu.fpu.push(integer(app, ebp - 4));
        cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, 0x53a9fc));
    }
    else if (cpu.ax == 2)
    {
        halve(cpu, high(app, cpu.ebx + 0x1c));
        cpu.edx = high(app, cpu.ebx + 0x1a) - cpu.eax;
        putHalf(app, cpu.ebx + 0x1c, cpu.dx);
        return done();
    }
    else
    {
        if (half(app, cpu.ebx + 0x48) != 3 || at(app, kMenu3d) == 0)
            return done();
        cpu.eax = high(app, cpu.ebx + 0x1a) - 5;
        put(app, ebp - 4, cpu.eax);
        cpu.fpu.push(integer(app, ebp - 4));
        cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, 0x53aa00));
    }
    if (!byAddress(app, cpu, kChop))
        return;
    storeInteger(app, cpu, ebp - 4);
    cpu.eax = at(app, ebp - 4);
    putHalf(app, cpu.ebx + 0x1c, cpu.ax);
    done();
}

namespace
{

/* mov edx, v; mov eax, v; sar edx, 0x1f; shl edx, 2; sbb eax, edx; sar eax, 2:
 * v quartered toward 0 in eax, edx -4 for a v below 0, else 0. */
void quarter(x86::CPU& cpu, reg32 v)
{
    const reg32 borrow = sreg32(v) < 0 ? 1 : 0;
    cpu.edx = reg32(sreg32(v) >> 31) << 2;
    cpu.eax = reg32(sreg32(v - cpu.edx - borrow) >> 2);
}

}  // namespace

/* 0x4d95c0: a character of a 2D screen's font drawn as a quad of the
 * screen (0x563ab0, its four vertices): its square of the font's texture at
 * eax, edx, [esp+4] wide and [esp+8] high, at x ebx, y ecx, in the colour
 * [esp+0xc] -- unless [esp+0x14], which only measures it.  How far on the
 * next character goes in eax: its width, less in the fonts that overlap
 * their characters -- the accented font (0x24) with its own shadowed colour
 * for the menus' highlight (0xffe440) where the line [0x7a1b98] crosses it,
 * the fonts 0x10 and 0xd at half and three quarters.  Nothing on the 3D card
 * ([0x559234]), where it is as wide as it is.  On a card with alpha, render
 * state 0x2bf on for it unless [0x563aa0]; drawn twice to stand out on one
 * without, but in the accented font. */
void drawScreenCharacter(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0x34);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.esi, &cpu.edi}, 0x14); };
    cpu.esi = at(app, ebp + 0x10);
    cpu.edi = cpu.eax;
    put(app, ebp - 0x18, cpu.edx);
    put(app, ebp - 0x20, cpu.ebx);
    cpu.ebx = cpu.ecx;
    cpu.ecx = at(app, ebp + 0x14);
    cpu.edx = 0x3b800000;
    cpu.eax = at(app, ebp + 0x18);
    put(app, ebp - 0x10, cpu.edx);
    put(app, ebp - 0xc, cpu.edx);
    put(app, ebp - 0x1c, cpu.eax);
    cpu.edx = at(app, kMenu3d);
    put(app, ebp - 0x24, cpu.eax);
    if (cpu.edx != 0)
    {
        cpu.eax = cpu.esi;
        return done();
    }
    if (at(app, 0x664650) == 0x24)
    {
        cpu.edx = at(app, ebp + 0x18);
        cpu.eax = cpu.esi - 1;
        cpu.edx &= 0xffffff;
        cpu.edi += 1;
        put(app, ebp - 8, cpu.edx);
        cpu.edx = at(app, ebp - 0x18);
        cpu.ebx += 4;
        cpu.edx += 3;
        put(app, ebp - 0x14, cpu.eax);
        put(app, ebp - 0x18, cpu.edx);
        cpu.edx = at(app, ebp - 8);
        cpu.eax = cpu.ecx - 1;
        if (cpu.edx == 0xffe440)
        {
            put(app, ebp - 0x1c, 0xfffff180);
            put(app, ebp - 0x24, 0xffd0ae28);
            cpu.edx = at(app, 0x7a1b98);
            if (sreg32(cpu.edx) > sreg32(at(app, ebp - 0x20)))
            {
                cpu.edx = at(app, ebp - 0x20) + at(app, ebp - 0x14);
                put(app, ebp - 8, cpu.edx);
                cpu.edx = at(app, 0x7a1b98);
                if (sreg32(cpu.edx) < sreg32(at(app, ebp - 8)))
                {
                    cpu.edx = 0xffffffff;
                    put(app, ebp - 0x24, cpu.edx);
                    put(app, ebp - 0x1c, cpu.edx);
                }
            }
        }
    }
    else
    {
        halve(cpu, cpu.ecx);
        put(app, ebp - 0x30, cpu.eax);
        halve(cpu, cpu.esi);
        put(app, ebp - 0x2c, cpu.eax);
        cpu.eax = at(app, 0x664650);
        if (cpu.eax == 0x10)
        {
            cpu.eax = at(app, ebp - 0x2c);
            cpu.edx = at(app, ebp - 0x18);
            cpu.edi += 1;
            cpu.ebx += 3;
            put(app, ebp - 0x14, cpu.eax);
            cpu.edx += 4;
            cpu.eax = at(app, ebp - 0x30);
            put(app, ebp - 0x18, cpu.edx);
        }
        else if (cpu.eax == 0xd)
        {
            quarter(cpu, cpu.esi);
            cpu.edx = at(app, ebp - 0x2c) + cpu.eax;
            put(app, ebp - 0x14, cpu.edx);
            quarter(cpu, cpu.ecx);
            cpu.eax += at(app, ebp - 0x30);
        }
        else
        {
            cpu.eax = cpu.ecx;
            put(app, ebp - 0x14, cpu.esi);
        }
    }
    if (sreg32(cpu.eax) < 1)
    {
        cpu.eax = at(app, ebp - 0x14);
        return done();
    }
    // The texture's corners, a 256th of the texture a texel.
    put(app, ebp - 8, cpu.edi);
    cpu.edx = at(app, ebp - 0x18);
    cpu.fpu.push(integer(app, ebp - 8));
    cpu.edi = at(app, ebp + 0x20);
    put(app, ebp - 8, cpu.edx);
    storeFloat(app, ebp - 0x28, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp - 8));
    storeFloat(app, ebp - 0x34, cpu.fpu.pop());
    if (cpu.edi != 0)
    {
        cpu.eax = at(app, ebp - 0x14);
        return done();
    }
    // The quad's corners: its depth (0x563aa8, 0x563aac), places and colours.
    cpu.fpu.push(loadFloat(app, 0x563aa8));
    cpu.fpu.push(loadFloat(app, 0x563aac));
    cpu.edx = at(app, ebp - 0x1c);
    cpu.edi = at(app, ebp - 0x14);
    exchange(cpu, 1);
    storeFloat(app, 0x563b18, cpu.fpu.pop());
    storeFloat(app, 0x563b1c, cpu.fpu.pop());
    put(app, ebp - 8, cpu.ebx);
    cpu.eax += cpu.ebx;
    cpu.fpu.push(integer(app, ebp - 8));
    cpu.fpu.push(loadFloat(app, 0x563b1c));
    cpu.ebx = at(app, 0x563b18);
    put(app, 0x563af8, cpu.ebx);
    storeFloat(app, 0x563afc, cpu.fpu.pop());
    put(app, 0x563ae0, cpu.edx);
    put(app, 0x563ac0, cpu.edx);
    put(app, ebp - 8, cpu.eax);
    storeFloat(app, 0x563ad4, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp - 8));
    cpu.fpu.push(loadFloat(app, 0x563af8));
    cpu.fpu.push(loadFloat(app, 0x563afc));
    cpu.fpu.push(loadFloat(app, 0x563ad4));
    cpu.edx = at(app, ebp - 0x24);
    cpu.ah = byte(app, kRenderFlags);
    exchange(cpu, 2);
    storeFloat(app, 0x563ad8, cpu.fpu.pop());
    storeFloat(app, 0x563adc, cpu.fpu.pop());
    storeFloat(app, 0x563ab4, cpu.fpu.pop());
    storeFloat(app, 0x563b14, cpu.fpu.pop());
    cpu.fpu.push(loadFloat(app, 0x563ad8));
    cpu.fpu.push(loadFloat(app, 0x563adc));
    cpu.fpu.push(loadFloat(app, 0x563b14));
    exchange(cpu, 2);
    storeFloat(app, 0x563ab8, cpu.fpu.pop());
    put(app, 0x563b20, cpu.edx);
    put(app, 0x563b00, cpu.edx);
    cpu.edx = at(app, ebp - 0x20);
    storeFloat(app, 0x563abc, cpu.fpu.pop());
    put(app, ebp - 8, cpu.edx);
    storeFloat(app, 0x563af4, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp - 8));
    storeFloat(app, 0x563b10, cpu.fpu.pop());
    cpu.edx += cpu.edi;
    cpu.fpu.push(loadFloat(app, 0x563b10));
    put(app, ebp - 8, cpu.edx);
    storeFloat(app, 0x563ab0, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp - 8));
    storeFloat(app, 0x563af0, cpu.fpu.st(0));
    storeFloat(app, 0x563ad0, cpu.fpu.pop());
    if ((cpu.ah & 2) != 0)
    {
        cpu.eax = 0;
        put(app, 0x563aa0, cpu.eax);
    }
    // The texture's.
    cpu.fpu.push(loadFloat(app, ebp - 0xc));
    cpu.fpu.push(loadFloat(app, ebp - 0x28));
    mulTop(cpu, 1);
    cpu.fpu.push(loadFloat(app, ebp - 0x34));
    cpu.fpu.push(cpu.fpu.st(0));
    cpu.fpu.push(loadFloat(app, ebp - 0x10));
    exchange(cpu, 1);
    mulTop(cpu, 1);
    put(app, ebp - 8, cpu.esi);
    put(app, ebp - 4, cpu.ecx);
    cpu.fpu.push(integer(app, ebp - 4));
    cpu.fpu.push(integer(app, ebp - 8));
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x28));
    exchange(cpu, 1);
    addPop(cpu, 4);
    mulPop(cpu, 5);
    exchange(cpu, 2);
    mulPop(cpu, 1);
    cpu.fpu.push(integer(app, 0x563aa0));
    cpu.fpu.push(loadFloat(app, 0x563ab0));
    cpu.fpu.push(loadFloat(app, 0x563ad0));
    cpu.dl = byte(app, kRenderFlags);
    exchange(cpu, 2);
    storeFloat(app, ebp - 8, cpu.fpu.pop());
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 8));
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 8));
    exchange(cpu, 4);
    storeFloat(app, 0x563b28, cpu.fpu.pop());
    exchange(cpu, 2);
    storeFloat(app, 0x563aec, cpu.fpu.pop());
    cpu.fpu.push(loadFloat(app, 0x563b28));
    cpu.fpu.push(loadFloat(app, 0x563aec));
    exchange(cpu, 3);
    storeFloat(app, 0x563ab0, cpu.fpu.pop());
    exchange(cpu, 3);
    storeFloat(app, 0x563ad0, cpu.fpu.pop());
    exchange(cpu, 2);
    storeFloat(app, 0x563ac8, cpu.fpu.pop());
    storeFloat(app, 0x563acc, cpu.fpu.pop());
    exchange(cpu, 1);
    storeFloat(app, 0x563b08, cpu.fpu.pop());
    storeFloat(app, 0x563b2c, cpu.fpu.st(0));
    cpu.eax = at(app, 0x563b08);
    put(app, 0x563ae8, cpu.eax);
    storeFloat(app, 0x563b0c, cpu.fpu.pop());
    const bool alpha = (cpu.dl & 2) != 0 && at(app, 0x563aa0) == 0;
    if (alpha)
    {
        cpu.edx = 1;
        cpu.eax = 0x2bf;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    for (reg32 vertex = 0x563ab0; vertex < 0x563b30; vertex += 0x20)
    {
        cpu.edi = vertex + 0x14;
        cpu.esi = vertex;
        outcode(app, cpu);
    }
    for (int pass = 0; pass < 2; ++pass)
    {
        if (pass == 1 && ((byte(app, kRenderFlags) & 2) != 0 || at(app, 0x664650) == 0x24))
            break;
        cpu.ecx = 0x563b10;
        cpu.ebx = 0x563af0;
        cpu.edx = 0x563ad0;
        cpu.eax = 0x563ab0;
        if (!byAddress(app, cpu, kClipQuad))
            return;
    }
    if ((byte(app, kRenderFlags) & 2) != 0 && at(app, 0x563aa0) == 0)
    {
        cpu.eax = 0x2bf;
        cpu.edx = 0;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    // The quad's texture as it was.
    cpu.ecx = 0x3f800000;
    cpu.esi = 0;
    cpu.eax = at(app, ebp - 0x14);
    put(app, 0x563aec, cpu.esi);
    put(app, 0x563acc, cpu.esi);
    put(app, 0x563ac8, cpu.esi);
    put(app, 0x563b2c, cpu.ecx);
    put(app, 0x563b0c, cpu.ecx);
    put(app, 0x563b08, cpu.ecx);
    put(app, 0x563ae8, cpu.ecx);
    put(app, 0x563b28, cpu.esi);
    done();
}

/* 0x4db000: a quad of the menus' art in 640 by 480 measure, scaled to the
 * screen: its corners at eax, edx; ebx, ecx; [esp+4], [esp+8]; [esp+0xc],
 * [esp+0x10] -- their texture's at [esp+0x14] to [esp+0x30] -- of the
 * texture [esp+0x34], in the colour [esp+0x38]; clipped and drawn, on the 3D
 * card only.  Its vertices start as 0x4d5740 has them. */
void drawTexturedQuad(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0xb0);
    cpu.ebp -= 0x4a;
    const reg32 ebp = cpu.ebp;
    put(app, ebp + 0x2a, cpu.eax);
    put(app, ebp + 0x42, cpu.edx);
    cpu.edx = at(app, ebp + 0x8e);
    cpu.eax = cpu.ecx;
    cpu.ecx = 0x20;
    cpu.edi = ebp - 0x66;
    cpu.esi = 0x4d5740;
    copyDwords(app, cpu);
    if (at(app, kMenu3d) != 0)
    {
        put(app, ebp + 0x46, cpu.ebx);
        cpu.fpu.push(integer(app, kScreenWidth));
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
        cpu.fpu.push(integer(app, kScreenHeight));
        put(app, ebp + 0x46, cpu.eax);
        cpu.ecx = at(app, ebp + 0x2a);
        cpu.fpu.push(integer(app, ebp + 0x46));
        put(app, ebp + 0x46, cpu.ecx);
        exchange(cpu, 1);
        storeFloat(app, ebp + 0x36, cpu.fpu.pop());
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x36));
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(3));
        cpu.eax = at(app, ebp + 0x5a);
        exchange(cpu, 2);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496ec));
        put(app, ebp + 0x46, cpu.eax);
        exchange(cpu, 1);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496f4));
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(4));
        cpu.ecx = at(app, ebp + 0x42);
        exchange(cpu, 3);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496ec));
        put(app, ebp + 0x46, cpu.ecx);
        cpu.eax = at(app, ebp + 0x5e);
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x36));
        put(app, ebp + 0x46, cpu.eax);
        exchange(cpu, 4);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496ec));
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x36));
        exchange(cpu, 5);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496f4));
        cpu.eax = at(app, ebp + 0x62);
        exchange(cpu, 5);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496f4));
        put(app, ebp + 0x46, cpu.eax);
        exchange(cpu, 2);
        storeFloat(app, ebp + 0x2e, cpu.fpu.pop());
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.eax = at(app, ebp + 0x66);
        cpu.fpu.st(6) = cpu.fpu.mul(cpu.fpu.st(6), cpu.fpu.st(0));
        cpu.fpu.count -= 1;
        put(app, ebp + 0x46, cpu.eax);
        exchange(cpu, 5);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496ec));
        cpu.fpu.push(integer(app, ebp + 0x46));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x36));
        cpu.eax = at(app, ebp + 0x2e);
        exchange(cpu, 5);
        storeFloat(app, ebp + 0x32, cpu.fpu.pop());
        put(app, ebp - 0x66, cpu.eax);
        cpu.eax = at(app, ebp + 0x32);
        exchange(cpu, 4);
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496f4));
        put(app, ebp - 0x62, cpu.eax);
        cpu.eax = at(app, ebp + 0x6a);
        put(app, ebp - 0x4e, cpu.eax);
        cpu.eax = at(app, ebp + 0x6e);
        exchange(cpu, 3);
        storeFloat(app, ebp + 0x1a, cpu.fpu.pop());
        put(app, ebp - 0x4a, cpu.eax);
        cpu.eax = at(app, ebp + 0x1a);
        exchange(cpu, 1);
        storeFloat(app, ebp + 0x22, cpu.fpu.pop());
        put(app, ebp - 0x46, cpu.eax);
        cpu.eax = at(app, ebp + 0x22);
        put(app, ebp - 0x42, cpu.eax);
        cpu.eax = at(app, ebp + 0x72);
        cpu.edi = ebp - 0x52;
        put(app, ebp - 0x2e, cpu.eax);
        cpu.eax = at(app, ebp + 0x76);
        exchange(cpu, 3);
        storeFloat(app, ebp + 0x26, cpu.fpu.pop());
        put(app, ebp - 0x2a, cpu.eax);
        cpu.eax = at(app, ebp + 0x26);
        exchange(cpu, 2);
        storeFloat(app, ebp + 0x3a, cpu.fpu.pop());
        put(app, ebp - 0x26, cpu.eax);
        cpu.eax = at(app, ebp + 0x3a);
        put(app, ebp - 0x56, cpu.edx);
        put(app, ebp - 0x22, cpu.eax);
        cpu.eax = at(app, ebp + 0x7a);
        put(app, ebp - 0x36, cpu.edx);
        put(app, ebp - 0xe, cpu.eax);
        cpu.eax = at(app, ebp + 0x7e);
        storeFloat(app, ebp + 0x3e, cpu.fpu.pop());
        put(app, ebp - 0xa, cpu.eax);
        cpu.eax = at(app, ebp + 0x3e);
        storeFloat(app, ebp + 0x1e, cpu.fpu.pop());
        put(app, ebp - 6, cpu.eax);
        cpu.eax = at(app, ebp + 0x1e);
        put(app, ebp - 0x16, cpu.edx);
        put(app, ebp - 2, cpu.eax);
        cpu.eax = at(app, ebp + 0x82);
        put(app, ebp + 0xa, cpu.edx);
        put(app, ebp + 0x12, cpu.eax);
        cpu.eax = at(app, ebp + 0x86);
        cpu.edx = at(app, ebp + 0x8a);
        put(app, ebp + 0x16, cpu.eax);
        cpu.eax = 0x1;
        cpu.esi = ebp - 0x66;
        if (!byAddress(app, cpu, kRenderState))
            return;
        for (reg32 vertex = ebp - 0x66; vertex != ebp + 0x1a; vertex += 0x20)
        {
            cpu.edi = vertex + 0x14;
            cpu.esi = vertex;
            outcode(app, cpu);
        }
        cpu.ecx = ebp - 6;
        cpu.ebx = ebp - 0x26;
        cpu.edx = ebp - 0x46;
        cpu.eax = ebp - 0x66;
        if (!byAddress(app, cpu, kClipQuad))
            return;
    }
    cpu.esp = ebp + 0x4a;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 0x38;
}

/* 0x4db380: a quad in 640 by 480 measure, scaled to the screen: its
 * corners at eax, edx; ebx, ecx; [esp+4], [esp+8]; [esp+0xc], [esp+0x10] --
 * each in its own colour, [esp+0x14] to [esp+0x20] -- untextured (render
 * state 1 to 0), clipped and drawn; render state 6 on for it on a card with
 * alpha.  Its vertices start as 0x4d57c0 has them, at a depth of their own
 * on the 3D card, else at the 2D screens' (0x563aa8, 0x563aac). */
void drawShadedQuad(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 0xb4);
    cpu.ebp -= 0x62;
    const reg32 ebp = cpu.ebp;
    put(app, ebp + 0x5a, cpu.eax);
    put(app, ebp + 0x52, cpu.edx);
    put(app, ebp + 0x56, cpu.ebx);
    cpu.ebx = cpu.ecx;
    cpu.ecx = 0x20;
    cpu.edi = ebp - 0x52;
    cpu.esi = 0x4d57c0;
    cpu.edx = at(app, kMenu3d);
    copyDwords(app, cpu);
    if (cpu.edx != 0)
    {
        cpu.esi = 0x3f7fff00;
        cpu.ecx = 0x37800080;
        put(app, ebp - 0x46, cpu.esi);
        put(app, ebp - 0x2a, cpu.ecx);
        put(app, ebp - 0x26, cpu.esi);
        put(app, ebp - 0xa, cpu.ecx);
        put(app, ebp - 6, cpu.esi);
        put(app, ebp + 0x16, cpu.ecx);
        put(app, ebp + 0x1a, cpu.esi);
        put(app, ebp - 0x4a, cpu.ecx);
    }
    else
    {
        cpu.eax = at(app, 0x563aa8);
        put(app, ebp - 0x4a, cpu.eax);
        cpu.eax = at(app, 0x563aac);
        put(app, ebp - 0x46, cpu.eax);
        cpu.eax = at(app, ebp - 0x4a);
        put(app, ebp - 0x2a, cpu.eax);
        cpu.eax = at(app, ebp - 0x46);
        put(app, ebp - 0x26, cpu.eax);
        cpu.eax = at(app, ebp - 0x4a);
        put(app, ebp - 0xa, cpu.eax);
        cpu.eax = at(app, ebp - 0x46);
        put(app, ebp - 6, cpu.eax);
        cpu.eax = at(app, ebp - 0x4a);
        put(app, ebp + 0x16, cpu.eax);
        cpu.eax = at(app, ebp - 0x46);
        put(app, ebp + 0x1a, cpu.eax);
    }
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.edx = 1;
        cpu.eax = 6;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    cpu.fpu.push(integer(app, kScreenHeight));
    put(app, ebp + 0x5e, cpu.ebx);
    cpu.eax = at(app, ebp + 0x5a);
    cpu.fpu.push(integer(app, ebp + 0x5e));
    exchange(cpu, 1);
    storeFloat(app, ebp + 0x4a, cpu.fpu.pop());
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x4a));
    put(app, ebp + 0x5e, cpu.eax);
    cpu.fpu.push(integer(app, kScreenWidth));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
    cpu.eax = at(app, ebp + 0x52);
    exchange(cpu, 2);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x549704));
    put(app, ebp + 0x5e, cpu.eax);
    exchange(cpu, 2);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496fc));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.eax = at(app, ebp + 0x56);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x4a));
    put(app, ebp + 0x5e, cpu.eax);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x549704));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.eax = at(app, ebp + 0x72);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(3));
    put(app, ebp + 0x5e, cpu.eax);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496fc));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.eax = at(app, ebp + 0x76);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(4));
    put(app, ebp + 0x5e, cpu.eax);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496fc));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x4a));
    cpu.eax = at(app, ebp + 0x7a);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x549704));
    put(app, ebp + 0x5e, cpu.eax);
    exchange(cpu, 4);
    storeFloat(app, ebp + 0x36, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.eax = at(app, ebp + 0x7e);
    cpu.fpu.st(5) = cpu.fpu.mul(cpu.fpu.st(5), cpu.fpu.st(0));
    cpu.fpu.count -= 1;
    put(app, ebp + 0x5e, cpu.eax);
    exchange(cpu, 4);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x5496fc));
    cpu.fpu.push(integer(app, ebp + 0x5e));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp + 0x4a));
    cpu.eax = at(app, ebp + 0x36);
    exchange(cpu, 3);
    storeFloat(app, ebp + 0x2e, cpu.fpu.pop());
    put(app, ebp - 0x52, cpu.eax);
    cpu.eax = at(app, ebp + 0x2e);
    exchange(cpu, 2);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x549704));
    put(app, ebp - 0x4e, cpu.eax);
    cpu.eax = at(app, ebp + 0x82);
    exchange(cpu, 1);
    storeFloat(app, ebp + 0x42, cpu.fpu.pop());
    put(app, ebp - 0x42, cpu.eax);
    cpu.eax = at(app, ebp + 0x42);
    exchange(cpu, 4);
    storeFloat(app, ebp + 0x46, cpu.fpu.pop());
    put(app, ebp - 0x32, cpu.eax);
    cpu.eax = at(app, ebp + 0x46);
    put(app, ebp - 0x2e, cpu.eax);
    cpu.eax = at(app, ebp + 0x86);
    exchange(cpu, 2);
    storeFloat(app, ebp + 0x3a, cpu.fpu.pop());
    put(app, ebp - 0x22, cpu.eax);
    cpu.eax = at(app, ebp + 0x3a);
    storeFloat(app, ebp + 0x32, cpu.fpu.pop());
    put(app, ebp - 0x12, cpu.eax);
    cpu.eax = at(app, ebp + 0x32);
    put(app, ebp - 0xe, cpu.eax);
    cpu.eax = at(app, ebp + 0x8a);
    storeFloat(app, ebp + 0x3e, cpu.fpu.pop());
    put(app, ebp - 2, cpu.eax);
    cpu.eax = at(app, ebp + 0x3e);
    storeFloat(app, ebp + 0x4e, cpu.fpu.pop());
    put(app, ebp + 0xe, cpu.eax);
    cpu.eax = at(app, ebp + 0x4e);
    cpu.edi = ebp - 0x3e;
    put(app, ebp + 0x12, cpu.eax);
    cpu.eax = at(app, ebp + 0x8e);
    cpu.edx = 0;
    put(app, ebp + 0x1e, cpu.eax);
    cpu.eax = 0x1;
    cpu.esi = ebp - 0x52;
    if (!byAddress(app, cpu, kRenderState))
        return;
    for (reg32 vertex = ebp - 0x52; vertex != ebp + 0x2e; vertex += 0x20)
    {
        cpu.edi = vertex + 0x14;
        cpu.esi = vertex;
        outcode(app, cpu);
    }
    cpu.ecx = ebp + 0xe;
    cpu.ebx = ebp - 0x12;
    cpu.edx = ebp - 0x32;
    cpu.eax = ebp - 0x52;
    if (!byAddress(app, cpu, kClipQuad))
        return;
    if ((byte(app, kRenderFlags) & 2) != 0)
    {
        cpu.eax = 6;
        cpu.edx = 0;
        if (!byAddress(app, cpu, kRenderState))
            return;
    }
    cpu.esp = ebp + 0x62;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.esp += 4 + 0x20;
}

/* 0x46ac40: where the thumb ebx of the two-axis slider at eax may go along
 * axis edx -- for axis 0 or 1 parts 0 to 3 across its area (0xa6, 0xa8 wide),
 * parts 0 and 1 from its left, 2 and 3 from its middle; for another axis
 * part 4 down its bar -- the start to the word at ecx, the end to [[esp+4]],
 * the length between to [[esp+8]], and the thumb's place along it, the length
 * times the axis's value, to [[esp+0xc]]. */
void twoAxisThumbPlace(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.esi, &cpu.edi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.edi = cpu.edx;
    if (cpu.edx == 0 || cpu.edx == 1)
    {
        if (cpu.ebx > 3)
            return leave(app, cpu, {&cpu.esi, &cpu.edi}, 0xc);
        if (cpu.ebx < 2)
        {
            halve(cpu, high(app, cpu.esi + cpu.ebx * 8 + 0x7e));
            cpu.edx = high(app, cpu.esi + 0xa4);
            cpu.eax += cpu.edx;
            putHalf(app, cpu.ecx, cpu.ax);
            halve(cpu, high(app, cpu.esi + cpu.ebx * 8 + 0x7e));
            const reg32 width = high(app, cpu.esi + 0xa6);
            cpu.ebx = cpu.eax;
            halve(cpu, width);
            cpu.edx = at(app, cpu.esi + 0xa4);
            cpu.eax -= cpu.ebx;
            cpu.edx = reg32(sreg32(cpu.edx) >> 16);
            cpu.eax += cpu.edx;
            cpu.edx = at(app, ebp + 0x10);
            putHalf(app, cpu.edx, cpu.ax);
            cpu.edx = cpu.eax;
            cpu.bx = half(app, cpu.ecx);
            cpu.eax = at(app, ebp + 0x14);
            cpu.edx -= cpu.ebx;
        }
        else
        {
            halve(cpu, high(app, cpu.esi + 0xa6));
            cpu.edx = high(app, cpu.esi + 0xa4) + cpu.eax;
            put(app, ebp - 4, cpu.edx);
            halve(cpu, high(app, cpu.esi + cpu.ebx * 8 + 0x7e));
            cpu.eax += at(app, ebp - 4);
            putHalf(app, cpu.ecx, cpu.ax);
            halve(cpu, high(app, cpu.esi + cpu.ebx * 8 + 0x7e));
            cpu.edx = high(app, cpu.esi + 0xa6) - cpu.eax;
            cpu.eax = cpu.edx;
            cpu.edx = high(app, cpu.esi + 0xa4);
            cpu.eax += cpu.edx;
            cpu.edx = at(app, ebp + 0x10);
            putHalf(app, cpu.edx, cpu.ax);
            cpu.edx = cpu.eax;
            cpu.dx = x86::reg16(cpu.dx - half(app, cpu.ecx));
            cpu.eax = at(app, ebp + 0x14);
        }
    }
    else
    {
        if (cpu.ebx != 4)
            return leave(app, cpu, {&cpu.esi, &cpu.edi}, 0xc);
        cpu.dx = half(app, cpu.eax + 0xa6);
        cpu.bx = half(app, cpu.eax + 0x80);
        cpu.edx += cpu.ebx;
        putHalf(app, cpu.ecx, cpu.dx);
        cpu.dx = x86::reg16(half(app, cpu.eax + 0xa6) + half(app, cpu.eax + 0xa8));
        cpu.ax = half(app, cpu.esi + 0x90);
        cpu.edx -= cpu.eax;
        cpu.eax = at(app, ebp + 0x10);
        putHalf(app, cpu.eax, cpu.dx);
        cpu.dx = x86::reg16(cpu.dx - half(app, cpu.ecx));
        cpu.eax = at(app, ebp + 0x14);
    }
    putHalf(app, cpu.eax, cpu.dx);
    cpu.edx = cpu.eax;
    cpu.fpu.push(halfInteger(app, cpu.edx));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, cpu.esi + cpu.edi * 4 + 0x54));
    cpu.edx = at(app, ebp + 0x18);
    if (!byAddress(app, cpu, kChop))
        return;
    storeInteger(app, cpu, ebp - 4);
    cpu.eax = at(app, ebp - 4);
    putHalf(app, cpu.edx, cpu.ax);
    leave(app, cpu, {&cpu.esi, &cpu.edi}, 0xc);
}

namespace
{

/* The two-axis slider at esi's thumb `part` placed along axis edi, as
 * twoAxisThumbPlace's callers hand it their frame's words: the place to
 * [esp+0xc], the length to [esp+8], the end to [esp+4], the start to ecx. */
bool placeTwoAxisThumb(win32::WinApplication* app, x86::CPU& cpu, reg32 place, reg32 length, reg32 end,
                       reg32 start, reg32 part)
{
    push(app, cpu, place);
    push(app, cpu, length);
    push(app, cpu, end);
    cpu.ecx = start;
    cpu.edx = cpu.edi;
    cpu.ebx = part;
    cpu.eax = cpu.esi;
    return direct(app, cpu, twoAxisThumbPlace);
}

/* The thumb's place along its track, the start (the word at `start`) and the
 * place (at `place`) less half its width (the word after word `left` of the
 * slider at esi), to its left. */
void moveThumb(win32::WinApplication* app, x86::CPU& cpu, reg32 left, reg32 start, reg32 place, reg32& scratch)
{
    halve(cpu, high(app, cpu.esi + left));
    scratch = high(app, start - 2);
    cpu.edx = high(app, place - 2);
    cpu.edx += scratch;
    cpu.edx -= cpu.eax;
    putHalf(app, cpu.esi + left, cpu.dx);
}

/* The place from the track's far end: the length (the word at `length`)
 * less the place, to the place's word. */
void fromFarEnd(win32::WinApplication* app, x86::CPU& cpu, reg32 length, reg32 place, reg32& scratch)
{
    cpu.eax = at(app, length);
    scratch = at(app, place);
    cpu.eax -= scratch;
    putHalf(app, place, cpu.ax);
}

}  // namespace

/* 0x46add0: axis [esp+8] of the two-axis slider at eax set to the value
 * [esp+4], within 0 and 1 and snapped to its step: its thumbs moved there
 * -- across, parts 0 and 2 (the second from the far side); up, parts 1 (from
 * the far side) and 3; for axis 2 part 4 -- and its function told. */
void setTwoAxisValue(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    cpu.edi = at(app, ebp + 0x20);
    cpu.esi = cpu.eax;
    if (sreg32(at(app, ebp + 0x1c)) > sreg32(0x3f800000))
    {
        put(app, ebp + 0x1c, 0x3f800000);
    }
    else
    {
        cpu.fpu.push(0.0);
        comparePop(cpu, loadFloat(app, ebp + 0x1c));
        if (!belowOrEqual(cpu))
        {
            cpu.ebx = 0;
            put(app, ebp + 0x1c, cpu.ebx);
        }
    }
    push(app, cpu, at(app, ebp + 0x1c));
    push(app, cpu, at(app, cpu.esi + 0x44));
    if (!direct(app, cpu, snapToStep))
        return;
    storeFloat(app, ebp + 0x1c, cpu.fpu.pop());
    cpu.edx = at(app, ebp + 0x1c);
    put(app, cpu.esi + cpu.edi * 4 + 0x54, cpu.edx);
    if (cpu.edi == 0)
    {
        if (!placeTwoAxisThumb(app, cpu, ebp - 4, ebp - 0x10, ebp - 8, ebp - 0xc, 0))
            return;
        moveThumb(app, cpu, 0x7e, ebp - 0xc, ebp - 4, cpu.ecx);
        if (!placeTwoAxisThumb(app, cpu, ebp - 4, ebp - 0x10, ebp - 8, ebp - 0xc, 2))
            return;
        fromFarEnd(app, cpu, ebp - 0x10, ebp - 4, cpu.edx);
        moveThumb(app, cpu, 0x8e, ebp - 0xc, ebp - 4, cpu.ecx);
    }
    else if (cpu.edi == 1)
    {
        if (!placeTwoAxisThumb(app, cpu, ebp - 4, ebp - 0x10, ebp - 8, ebp - 0xc, 1))
            return;
        fromFarEnd(app, cpu, ebp - 0x10, ebp - 4, cpu.ebx);
        moveThumb(app, cpu, 0x86, ebp - 0xc, ebp - 4, cpu.ecx);
        if (!placeTwoAxisThumb(app, cpu, ebp - 4, ebp - 0x10, ebp - 8, ebp - 0xc, 3))
            return;
        moveThumb(app, cpu, 0x96, ebp - 0xc, ebp - 4, cpu.ecx);
    }
    else if (cpu.edi == 2)
    {
        if (!placeTwoAxisThumb(app, cpu, ebp - 4, ebp - 0x10, ebp - 8, ebp - 0xc, 4))
            return;
        fromFarEnd(app, cpu, ebp - 0x10, ebp - 4, cpu.ecx);
        // Half its width by idiv, the axis being 2.
        cpu.eax = high(app, cpu.esi + 0x9e);
        cpu.edx = reg32(sreg32(cpu.eax) >> 31);
        idiv(cpu, cpu.edi);
        cpu.ecx = high(app, ebp - 0xe);
        cpu.edx = high(app, ebp - 6);
        cpu.edx += cpu.ecx;
        cpu.edx -= cpu.eax;
        putHalf(app, cpu.esi + 0x9e, cpu.dx);
    }
    if (at(app, cpu.esi + 0x78) != 0)
    {
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, at(app, cpu.esi + 0x78)))
            return;
    }
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 8);
}

/* 0x46b040: axis ebx (0 across, 1 up) of the two-axis slider at eax dragged
 * to dx along its track: each of its thumbs on that axis placed, the axis's
 * value that far of the track's length snapped to its step, the thumb moved
 * there -- the second thumb's from the far end -- and its function told. */
void dragTwoAxisTo(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x20);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    putHalf(app, ebp - 8, cpu.dx);
    cpu.edi = cpu.ebx;
    auto place = [&](reg32 part) {
        return placeTwoAxisThumb(app, cpu, ebp - 0x10, ebp - 0x18, ebp - 0x14, ebp - 0x1c, part);
    };
    // The place dragged to, within 0 and the track's length: `held` the
    // place's word, `zero` cleared where it is below 0.
    auto clamp = [&](reg32& held, reg32& zero) {
        held = at(app, ebp - 8);
        if (x86::sreg16(x86::reg16(held)) < 0)
        {
            zero = 0;
            putHalf(app, ebp - 0x10, x86::reg16(zero));
            return;
        }
        cpu.eax = high(app, ebp - 0x1a);
        cpu.edx = high(app, ebp - 0xa);
        if (sreg32(cpu.edx) > sreg32(cpu.eax))
        {
            cpu.eax = at(app, ebp - 0x18);
            putHalf(app, ebp - 0x10, cpu.ax);
        }
        else
        {
            putHalf(app, ebp - 0x10, x86::reg16(held));
        }
    };
    // The axis's value, the place over the length, snapped to the step.
    auto snapValue = [&](reg32 value) {
        cpu.eax = at(app, ebp - 0x10);
        put(app, ebp - 4, cpu.eax);
        cpu.eax = at(app, ebp - 0x18);
        put(app, ebp - 0xc, cpu.eax);
        cpu.fpu.push(halfInteger(app, ebp - 4));
        cpu.fpu.push(halfInteger(app, ebp - 0xc));
        divPop(cpu, 1);
        storeFloat(app, ebp - 0x20, cpu.fpu.pop());
        push(app, cpu, at(app, ebp - 0x20));
        push(app, cpu, at(app, cpu.esi + 0x44));
        if (!direct(app, cpu, snapToStep))
            return false;
        storeFloat(app, ebp - 0x20, cpu.fpu.pop());
        cpu.eax = at(app, ebp - 0x20);
        put(app, cpu.esi + value, cpu.eax);
        return true;
    };
    if (cpu.ebx == 0)
    {
        if (!place(0))
            return;
        if (x86::sreg16(half(app, ebp - 8)) < 0)
        {
            cpu.ebx = 0;
            putHalf(app, ebp - 0x10, cpu.bx);
        }
        else
        {
            cpu.eax = high(app, ebp - 0x1a);
            cpu.edx = high(app, ebp - 0xa);
            cpu.eax = sreg32(cpu.edx) > sreg32(cpu.eax) ? at(app, ebp - 0x18) : at(app, ebp - 8);
            putHalf(app, ebp - 0x10, cpu.ax);
        }
        if (!snapValue(0x54) || !place(0))
            return;
        moveThumb(app, cpu, 0x7e, ebp - 0x1c, ebp - 0x10, cpu.ebx);
        if (!place(2))
            return;
        clamp(cpu.ecx, cpu.eax);
        if (!snapValue(0x54) || !place(2))
            return;
        fromFarEnd(app, cpu, ebp - 0x18, ebp - 0x10, cpu.edx);
        moveThumb(app, cpu, 0x8e, ebp - 0x1c, ebp - 0x10, cpu.ebx);
    }
    else if (cpu.ebx == 1)
    {
        if (!place(1))
            return;
        clamp(cpu.ebx, cpu.ecx);
        if (!snapValue(0x58) || !place(1))
            return;
        fromFarEnd(app, cpu, ebp - 0x18, ebp - 0x10, cpu.edx);
        moveThumb(app, cpu, 0x86, ebp - 0x1c, ebp - 0x10, cpu.ebx);
        if (!place(3))
            return;
        clamp(cpu.ebx, cpu.ecx);
        if (!snapValue(0x58) || !place(3))
            return;
        moveThumb(app, cpu, 0x96, ebp - 0x1c, ebp - 0x10, cpu.ebx);
    }
    if (at(app, cpu.esi + 0x78) != 0)
    {
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, at(app, cpu.esi + 0x78)))
            return;
    }
    leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x46a5f0: the slider at eax as the mouse works it, while it holds the
 * control (frontend_glue's 0x49c080): the part under the pointer hot (0x5
 * bit 4) -- the thumb (0) taken up (0xb0), an arrow (2, 3) starting its
 * repeat (0xb4, its clock at 0xac) -- the thumb taken up dragged to the
 * pointer, and an arrow held stepping the value down or up every 0x20 ticks
 * by its step (0x44, or 0x48 where that is not within 0 and 1).  Let go, the
 * thumb is put down and the repeat stopped. */
void trackSlider(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0x14);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    cpu.edx = cpu.eax;
    cpu.esi = cpu.eax;
    if (!byAddress(app, cpu, kMouseHolds))
        return;
    if (cpu.eax == 0)
    {
        putHalf(app, cpu.edx + 0xb0, 0);
        cpu.bl = byte(app, cpu.edx + 5);
        putByte(app, cpu.edx + 0xb4, 0xff);
        cpu.bl &= 0xfb;
        putByte(app, cpu.edx + 5, cpu.bl);
        return done();
    }
    cpu.eax = cpu.edx;
    if (!direct(app, cpu, sliderPartUnderPointer))
        return;
    cpu.edi = cpu.eax;
    if (cpu.eax == 0)
    {
        cpu.ah = byte(app, cpu.edx + 5);
        putHalf(app, cpu.edx + 0xb0, 1);
        cpu.ah |= 4;
        putByte(app, cpu.edx + 5, cpu.ah);
    }
    else if (cpu.eax == 2 && byte(app, cpu.edx + 0xb4) != 2)
    {
        cpu.eax = at(app, kClock);
        putByte(app, cpu.edx + 0xb4, 2);
        cpu.bh = byte(app, cpu.edx + 5);
        put(app, cpu.edx + 0xac, cpu.eax);
        cpu.bh |= 4;
        putByte(app, cpu.edx + 5, cpu.bh);
    }
    else if (cpu.edi == 3 && byte(app, cpu.esi + 0xb4) != 3)
    {
        cpu.eax = at(app, kClock);
        putByte(app, cpu.esi + 0xb4, 3);
        cpu.ch = byte(app, cpu.esi + 5);
        put(app, cpu.esi + 0xac, cpu.eax);
        cpu.ch |= 4;
        putByte(app, cpu.esi + 5, cpu.ch);
    }
    // The thumb taken up, after the pointer.
    if (half(app, cpu.esi + 0xb0) != 0)
    {
        if (sreg32(cpu.edi) >= 0
            && sreg32(cpu.edi) < sreg32(high(app, high(app, cpu.esi + 0x40) * 2 + kSliderParts)))
        {
            push(app, cpu, ebp - 4);
            cpu.ecx = ebp - 8;
            push(app, cpu, ebp - 0xc);
            cpu.ebx = ebp - 0x10;
            cpu.edx = 0;
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, sliderThumbPlace))
                return;
            cpu.eax = high(app, ebp - 0xa);
            cpu.edx = at(app, kPointerX);
            if (sreg32(cpu.eax) < sreg32(cpu.edx))
            {
                cpu.eax = at(app, ebp - 0xc);
            }
            else
            {
                cpu.eax = high(app, ebp - 0x12);
                if (sreg32(cpu.eax) > sreg32(cpu.edx))
                {
                    cpu.eax = 0;
                }
                else
                {
                    cpu.ebx = at(app, ebp - 0x10);
                    cpu.ax = half(app, kPointerX);
                    cpu.eax -= cpu.ebx;
                }
            }
            if (cpu.ax != half(app, ebp - 4))
            {
                cpu.edx = reg32(x86::sreg16(cpu.ax));
                cpu.ebx = 0;
                cpu.eax = cpu.esi;
                if (!direct(app, cpu, dragSliderTo))
                    return;
            }
        }
        else
        {
            putHalf(app, cpu.esi + 0xb0, 0);
        }
    }
    // The step: its own, or 0x48 where it is not within 0 and 1.
    cpu.fpu.push(0.0);
    comparePop(cpu, loadFloat(app, cpu.esi + 0x44));
    bool own = false;
    if (below(cpu))
    {
        cpu.ebx = at(app, cpu.esi + 0x44);
        own = sreg32(cpu.ebx) <= sreg32(0x3f800000);
    }
    if (own)
    {
        put(app, ebp - 0x14, cpu.ebx);
    }
    else
    {
        cpu.eax = at(app, cpu.esi + 0x48);
        put(app, ebp - 0x14, cpu.eax);
    }
    // An arrow held: a step every 0x20 ticks.
    const x86::reg8 repeat = byte(app, cpu.esi + 0xb4);
    if ((repeat == 2 && cpu.edi == 2) || (repeat == 3 && cpu.edi == 3))
    {
        cpu.eax = at(app, kClock) - at(app, cpu.esi + 0xac);
        if (cpu.eax == 0)
            cpu.eax = 0 - cpu.eax;
        if (cpu.eax < 0x20)
            return done();
        cpu.fpu.push(loadFloat(app, cpu.esi + 0x54));
        if (repeat == 2)
        {
            cpu.fpu.st(0) = cpu.fpu.sub(cpu.fpu.st(0), loadFloat(app, ebp - 0x14));
            storeFloat(app, cpu.esi + 0x54, cpu.fpu.st(0));
            cpu.fpu.push(0.0);
            compareTwo(cpu);
            if (!belowOrEqual(cpu))
                put(app, cpu.esi + 0x54, 0);
        }
        else
        {
            cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x14));
            storeFloat(app, cpu.esi + 0x54, cpu.fpu.st(0));
            cpu.fpu.push(1.0);
            compareTwo(cpu);
            if (below(cpu))
                put(app, cpu.esi + 0x54, 0x3f800000);
        }
        push(app, cpu, 0);
        cpu.eax = cpu.esi;
        push(app, cpu, at(app, cpu.esi + 0x54));
        if (!byAddress(app, cpu, kSetSliderValue))
            return;
        cpu.eax = at(app, kClock);
        put(app, cpu.esi + 0xac, cpu.eax);
        return done();
    }
    putByte(app, cpu.esi + 0xb4, 0xff);
    done();
}

/* 0x46c320: the two-axis slider at eax as the mouse works it, while it
 * holds the control: the part under the pointer taken up (0xb0) and hot,
 * then dragged to the pointer along its axis -- parts 0 and 2 across, 1 and
 * 3 up, 1 and 2 from the far end.  Let go, it is put down. */
void trackTwoAxis(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}, 0x10);
    const reg32 ebp = cpu.ebp;
    auto done = [&] { leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx, &cpu.esi, &cpu.edi}); };
    cpu.edx = cpu.eax;
    cpu.edi = 0xffffffff;
    cpu.esi = cpu.eax;
    if (!byAddress(app, cpu, kMouseHolds))
        return;
    if (cpu.eax == 0)
    {
        if (half(app, cpu.edx + 0xb0) != 0xffff)
        {
            cpu.ah = byte(app, cpu.edx + 5);
            putHalf(app, cpu.edx + 0xb0, 0xffff);
            cpu.ah &= 0xfb;
            putByte(app, cpu.edx + 5, cpu.ah);
        }
        return done();
    }
    if (half(app, cpu.edx + 0xb0) == 0xffff)
    {
        cpu.eax = cpu.edx;
        if (!direct(app, cpu, sliderPartUnderPointer))
            return;
        cpu.edx = cpu.eax;
        if (cpu.eax <= 3)
        {
            cpu.bl = byte(app, cpu.esi + 5);
            putHalf(app, cpu.esi + 0xb0, cpu.dx);
            cpu.bl |= 4;
            putByte(app, cpu.esi + 5, cpu.bl);
        }
    }
    cpu.ax = half(app, cpu.esi + 0xb0);
    if (cpu.ax == 0xffff || x86::sreg16(cpu.ax) < 0)
        return done();
    cpu.eax = high(app, cpu.esi + 0x40);
    cpu.edx = high(app, cpu.esi + 0xae);
    cpu.eax = high(app, cpu.eax * 2 + kSliderParts);
    if (sreg32(cpu.edx) >= sreg32(cpu.eax))
        return done();
    // The axis of the part: 0 across (parts 0 and 2), 1 up (1 and 3).
    cpu.ax = half(app, cpu.esi + 0xb0);
    if (cpu.ax <= 3)
    {
        cpu.eax &= 0xffff;
        cpu.edi = cpu.eax & 1;
    }
    cpu.ax = half(app, cpu.esi + 0xb0);
    if (cpu.ax > 3)
        return done();
    cpu.eax &= 0xffff;
    push(app, cpu, ebp - 8);
    cpu.ecx = ebp - 4;
    push(app, cpu, ebp - 0xc);
    cpu.edx = cpu.edi;
    push(app, cpu, ebp - 0x10);
    cpu.ebx = high(app, cpu.esi + 0xae);
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, twoAxisThumbPlace))
        return;
    cpu.eax = high(app, ebp - 0x12);
    cpu.edx = at(app, kPointerX);
    if (sreg32(cpu.eax) < sreg32(cpu.edx))
    {
        cpu.eax = at(app, ebp - 0xc);
    }
    else
    {
        cpu.eax = high(app, ebp - 6);
        if (sreg32(cpu.eax) > sreg32(cpu.edx))
        {
            cpu.eax = 0;
        }
        else
        {
            cpu.ebx = at(app, ebp - 4);
            cpu.ax = half(app, kPointerX);
            cpu.eax -= cpu.ebx;
        }
    }
    if (cpu.ax == half(app, ebp - 8))
        return done();
    cpu.dx = half(app, cpu.esi + 0xb0);
    if (cpu.dx == 2 || cpu.dx == 1)
    {
        cpu.edx = at(app, ebp - 0xc) - cpu.eax;
        cpu.ebx = cpu.edi;
        cpu.edx = reg32(x86::sreg16(cpu.dx));
    }
    else
    {
        cpu.edx = reg32(x86::sreg16(cpu.ax));
        cpu.ebx = cpu.edi;
    }
    cpu.eax = cpu.esi;
    if (!direct(app, cpu, dragTwoAxisTo))
        return;
    done();
}

/* 0x469680: the slider at eax drawn, in the menus' art of its kind, its
 * parts from the last: its arrows and thumb (0, 2, 3) as shapes of their own
 * on a 2D screen or quads of the art on the 3D card, in its colours or, the
 * part under the pointer where edx asks for it, its hot ones; its track (1)
 * shaded between two frames, the 2D screens' clipped to it -- a part without
 * art a rectangle, the hot one framed.  Not drawn while the 2D screens are
 * drawn ([0x559c60], not on the 3D card) or its screen ([0xb2]) is not the
 * one shown ([0xa]).  Then its texts in the 2D screens' font: its labels
 * (0x68 by it, 0x6c and 0x70 beside its track), its title (0x60) placed by
 * its alignment (0x75), slid in along its screen; and its value as a
 * percentage (0x3c 1).  The colours of its text: kept (4 bit 0), its own
 * where the mouse may take it (0xffe440), or the menus'.  eax 0. */
void drawSlider(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0xc4);
    cpu.ebp -= 0x82;
    const reg32 ebp = cpu.ebp;
    put(app, ebp + 0x6e, cpu.eax);
    put(app, ebp + 0x22, cpu.edx);
    cpu.ecx = 0x8;
    cpu.edi = ebp - 0x42;
    cpu.edx = 0xe;
    cpu.esi = 0x469020;
    cpu.ebx = at(app, 0x559c60);
    cpu.ah = 0;
    copyDwords(app, cpu);  // rep movsd dword ptr es:[edi], dword ptr [esi]
    putByte(app, ebp + 0x7e, x86::reg8(cpu.ah));
    cpu.ecx = 0xffffffff;
    put(app, ebp + 0x52, cpu.edx);
    put(app, ebp + 0xe, cpu.ecx);
    cpu.eax = cpu.ebx != 0 && at(app, kMenu3d) == 0 ? 1 : 0;
    cpu.dl = byte(app, 0x55eb2e);
    put(app, ebp + 0x32, cpu.eax);
    // Greyed where the menus grey their controls but this one (0x18).
    const x86::reg8 menus = cpu.dl;
    bool kept = (menus & 0x20) != 0 && (byte(app, at(app, ebp + 0x6e) + 0x18) & 1) != 0;
    if ((menus & 0x20) != 0)
        cpu.eax = at(app, ebp + 0x6e);
    if (!kept)
    {
        if ((byte(app, 0x55eb2e) & 0x10) != 0)
        {
            cpu.eax = at(app, ebp + 0x6e);
            kept = half(app, cpu.eax + 0x18) != 0;
        }
        if (!kept)
        {
            cpu.bh = byte(app, 0x55eb2e);
            if ((cpu.bh & 0x30) != 0)
            {
                cpu.eax = at(app, ebp + 0x6e);
                putByte(app, cpu.eax + 4, byte(app, cpu.eax + 4) | 1);
            }
        }
    }
    cpu.eax = at(app, ebp + 0x6e);
    if ((byte(app, cpu.eax + 4) & 1) != 0)
    {
        put(app, ebp + 0x46, 0x908080);
    }
    else if (at(app, ebp + 0x22) != 0)
    {
        cpu.eax = at(app, ebp + 0x6e);
        cpu.edx = 0xffe440;
        if (!direct(app, cpu, sliderPartUnderPointer))
            return;
        put(app, ebp + 0xe, cpu.eax);
        put(app, ebp + 0x46, cpu.edx);
    }
    else
    {
        put(app, ebp + 0x46, 0xff649dfd);
    }
    // Its parts, from the last.
    auto drawPart = [&]() -> bool {
        cpu.eax = at(app, ebp + 0x6e);
        cpu.esi = at(app, cpu.eax + 0x40);
        cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
        cpu.ecx = cpu.esi * 4;
        cpu.ecx = reg32(cpu.ecx - cpu.esi);
        cpu.edx = at(app, ebp + 0x6a);
        cpu.eax = cpu.ecx * 8;
        if (half(app, cpu.eax + cpu.edx * 4 + 0x678ab2) == 0xffff && at(app, kMenu3d) == 0)
        {
            // No art: a rectangle in its kind's colour (0x55adec), the hot part framed.
            cpu.ecx = cpu.esi * 4;
            cpu.ecx = reg32(cpu.ecx - cpu.esi);
            cpu.eax = cpu.edx * 8;
            cpu.ecx = reg32(cpu.ecx << 4);
            cpu.edx = cpu.ecx + cpu.eax;
            cpu.edx = at(app, cpu.edx + 0x55adec);
            cpu.ecx = at(app, ebp + 0x6e);
            cpu.edx = reg32(cpu.edx | 0xff000000);
            cpu.eax = reg32(cpu.eax + cpu.ecx);
            push(app, cpu, cpu.edx);
            cpu.ecx = at(app, cpu.eax + 0x7c);
            cpu.edi = at(app, cpu.eax + 0x7e);
            cpu.esi = at(app, cpu.eax + 0x80);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.edi = reg32(sreg32(cpu.edi) >> 0x10);
            put(app, ebp - 2, cpu.ecx);
            cpu.ecx = at(app, cpu.eax + 0x7a);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.ebx = cpu.edi;
            put(app, ebp + 6, cpu.ecx);
            cpu.eax = at(app, ebp - 2);
            cpu.edx = at(app, ebp + 6);
            cpu.ecx = cpu.esi;
            if (!byAddress(app, cpu, 0x4d8910)) return false;  //
            if (at(app, ebp + 0x22) == 0)
                return true;
            cpu.eax = at(app, ebp + 0x6a);
            if (cpu.eax != at(app, ebp + 0xe))
                return true;
            cpu.ecx = at(app, ebp + 0x6a);
            if (cpu.ecx != 0 && cpu.ecx != 2 && cpu.ecx != 3)
                return true;
            push(app, cpu, 0xffffe440);
            cpu.edx = at(app, ebp + 6);
            cpu.eax = at(app, ebp - 2);
            cpu.ecx = cpu.esi;
            cpu.ebx = cpu.edi;
            if (!byAddress(app, cpu, 0x4d8930)) return false;  //
            return true;
        }
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, ebp + 0x6e);
        cpu.eax = reg32(cpu.eax << 3);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        cpu.esi = at(app, cpu.eax + 0x7c);
        cpu.edi = at(app, cpu.eax + 0x7a);
        cpu.edx = at(app, cpu.eax + 0x7e);
        cpu.ebx = at(app, cpu.eax + 0x80);
        cpu.eax = at(app, ebp + 0x6e);
        cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
        cpu.edi = reg32(sreg32(cpu.edi) >> 0x10);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.cl = byte(app, cpu.eax + 0x3e);
        cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
        if (cpu.cl != 0 && (byte(app, kRenderFlags) & 2) == 0)
        {
            cpu.ecx = at(app, ebp + 0x6e);
            cpu.eax = 0;
            cpu.al = byte(app, cpu.ecx + 0x3f);
            cpu.eax = reg32(cpu.eax << 0x18);
            cpu.eax = reg32(cpu.eax | 0xffffff);
            put(app, ebp + 0x66, cpu.eax);
        }
        else
        {
            put(app, ebp + 0x66, 0xffffffff);
        }
        cpu.eax = at(app, ebp + 0x6a);
        if (cpu.eax > 3)
            return true;
        if (cpu.eax == 1)
        {
            // The track.
            if (at(app, kMenu3d) != 0)
            {
                cpu.eax = cpu.edx;
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                cpu.edx = at(app, ebp + 0x6e);
                put(app, ebp - 0xe, cpu.eax);
                cpu.eax = reg32(cpu.eax + cpu.esi);
                cpu.edx = at(app, cpu.edx + 0x40);
                put(app, ebp + 0x76, cpu.eax);
                cpu.eax = cpu.edi + cpu.ebx;
                cpu.ebx = at(app, ebp + 0x66);
                put(app, ebp + 0x72, cpu.eax);
                cpu.eax = at(app, 0x749a38);
                push(app, cpu, cpu.ebx);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                push(app, cpu, cpu.eax);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp + 0x6a);
                cpu.eax = reg32(cpu.eax << 6);
                cpu.edx = reg32(cpu.edx << 5);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                push(app, cpu, at(app, cpu.eax + 0x55a508));
                push(app, cpu, at(app, cpu.eax + 0x55a504));
                push(app, cpu, at(app, cpu.eax + 0x55a500));
                push(app, cpu, at(app, cpu.eax + 0x55a4fc));
                push(app, cpu, at(app, cpu.eax + 0x55a4f8));
                push(app, cpu, at(app, cpu.eax + 0x55a4f4));
                push(app, cpu, at(app, cpu.eax + 0x55a4f0));
                cpu.ecx = at(app, ebp + 0x72);
                push(app, cpu, at(app, cpu.eax + 0x55a4ec));
                push(app, cpu, cpu.ecx);
                push(app, cpu, cpu.esi);
                put(app, ebp + 0x7a, cpu.edx);
                cpu.eax = at(app, ebp + 0x76);
                push(app, cpu, cpu.ecx);
                cpu.edx = cpu.edi;
                cpu.ebx = cpu.eax;
                push(app, cpu, cpu.eax);
                cpu.ecx = cpu.edi;
                cpu.eax = cpu.esi;
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                cpu.ebx = at(app, ebp + 0x76);
                cpu.eax = at(app, ebp - 0xe);
                cpu.edx = cpu.ebx + cpu.eax;
                cpu.ecx = at(app, ebp + 0x66);
                put(app, ebp + 0x76, cpu.edx);
                cpu.edx = at(app, ebp + 0x6e);
                push(app, cpu, cpu.ecx);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.eax = at(app, 0x749a38);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                push(app, cpu, cpu.eax);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp + 0x7a);
                cpu.eax = reg32(cpu.eax << 6);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                push(app, cpu, at(app, cpu.eax + 0x55a508));
                push(app, cpu, at(app, cpu.eax + 0x55a504));
                push(app, cpu, at(app, cpu.eax + 0x55a500));
                push(app, cpu, at(app, cpu.eax + 0x55a4fc));
                push(app, cpu, at(app, cpu.eax + 0x55a4f8));
                push(app, cpu, at(app, cpu.eax + 0x55a4f4));
                push(app, cpu, at(app, cpu.eax + 0x55a4f0));
                cpu.ecx = at(app, ebp + 0x72);
                push(app, cpu, at(app, cpu.eax + 0x55a4ec));
                push(app, cpu, cpu.ecx);
                cpu.eax = at(app, ebp + 0x76);
                push(app, cpu, cpu.eax);
                push(app, cpu, cpu.ecx);
                push(app, cpu, cpu.ebx);
                cpu.edx = cpu.edi;
                cpu.ecx = cpu.edi;
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                cpu.eax = at(app, ebp + 0x6e);
                cpu.eax = at(app, cpu.eax + 0x84);
                cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                cpu.edx = cpu.eax + 0x10;
                put(app, ebp + 0x4e, cpu.edx);
                cpu.edx = at(app, ebp + 0x6e);
                cpu.ecx = at(app, cpu.edx + 0x82);
                cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
                cpu.edx = cpu.ecx + 2;
                put(app, ebp + 0x5e, cpu.edx);
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x86);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.edx = reg32(cpu.edx + cpu.eax);
                cpu.ebx = cpu.edx - 0x10;
                cpu.edx = reg32(cpu.edx - 1);
                put(app, ebp + 0x56, cpu.edx);
                cpu.edx = at(app, ebp + 0x6e);
                cpu.eax = reg32(cpu.eax + 1);
                cpu.edx = at(app, cpu.edx + 0x88);
                put(app, ebp + 0x5a, cpu.ebx);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                put(app, ebp + 0x4a, cpu.eax);
                cpu.edx = reg32(cpu.edx + cpu.ecx);
                cpu.ebx = at(app, ebp + 0x5e);
                cpu.edx = reg32(cpu.edx - 0x2);
                cpu.eax = at(app, ebp + 0x6e);
                put(app, ebp + 0x62, cpu.edx);
                put(app, ebp + 0x36, cpu.edx);
                cpu.dl = byte(app, cpu.eax + 0x3e);
                put(app, ebp + 0x3a, cpu.ebx);
                if (cpu.dl != 0 && (byte(app, kRenderFlags) & 2) == 0)
                {
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.eax = 0;
                    cpu.al = byte(app, cpu.edx + 0x3f);
                    cpu.eax = reg32(cpu.eax << 0x18);
                    cpu.edx = cpu.eax;
                    cpu.edx = reg32(cpu.edx | 0x15052d);
                    cpu.ax = x86::reg16(cpu.ax | 0xff40);
                    put(app, ebp + 0x2a, cpu.edx);
                    put(app, ebp + 0x12, cpu.eax);
                    put(app, ebp + 2, cpu.eax);
                    put(app, ebp - 6, cpu.edx);
                }
                else
                {
                    cpu.ebx = 0xff00ff40;
                    cpu.ecx = 0xff15052d;
                    put(app, ebp + 0x12, cpu.ebx);
                    put(app, ebp + 2, cpu.ebx);
                    put(app, ebp - 6, cpu.ecx);
                    put(app, ebp + 0x2a, cpu.ecx);
                }
                cpu.ecx = ebp - 0x16;
                cpu.ebx = ebp - 0x1a;
                cpu.edx = ebp - 0x12;
                cpu.eax = ebp - 0x1e;
                if (!byAddress(app, cpu, 0x4beb80)) return false;  //
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x7e);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx;
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x7c);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.edx = reg32(cpu.edx + cpu.eax);
                cpu.ebx = at(app, kScreenWidth);
                cpu.edx = reg32(cpu.edx - cpu.esi);
                cpu.edx = cpu.edx * cpu.ebx;
                cpu.eax = at(app, ebp + 0x6e);
                cpu.eax = at(app, cpu.eax + 0x88);
                cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                cpu.ecx = at(app, kScreenHeight);
                cpu.eax = reg32(cpu.eax + 0x4);
                cpu.eax = cpu.eax * cpu.ecx;
                put(app, ebp + 0x7a, cpu.eax);
                cpu.eax = cpu.edi - 2;
                cpu.eax = cpu.eax * cpu.ecx;
                put(app, ebp + 0x72, cpu.eax);
                cpu.eax = cpu.ebx;
                cpu.eax = cpu.eax * cpu.esi;
                put(app, ebp + 0x76, cpu.edx);
                cpu.fpu.push(loadDouble(app, 0x53ae68));
                cpu.fpu.push(integer(app, ebp + 0x76));
                cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                cpu.fpu.push(loadDouble(app, 0x53ae60));
                cpu.fpu.push(integer(app, ebp + 0x7a));
                cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                cpu.fpu.push(integer(app, ebp + 0x72));
                cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));
                cpu.fpu.count -= 1;
                put(app, ebp + 0x72, cpu.eax);
                cpu.fpu.push(integer(app, ebp + 0x72));
                cpu.fpu.st(4) = cpu.fpu.mul(cpu.fpu.st(4), cpu.fpu.st(0));
                cpu.fpu.count -= 1;
                exchange(cpu, 2);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                exchange(cpu, 1);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x76);
                cpu.ecx = at(app, ebp + 0x76);
                cpu.ebx = at(app, ebp + 0x72);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                cpu.edx = at(app, ebp + 0x72);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                cpu.eax = at(app, ebp + 0x72);
                if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                cpu.eax = at(app, ebp - 6);
                push(app, cpu, cpu.eax);
                cpu.edx = at(app, ebp + 2);
                push(app, cpu, cpu.edx);
                cpu.ecx = at(app, ebp + 0x12);
                push(app, cpu, cpu.ecx);
                cpu.ebx = at(app, ebp + 0x2a);
                push(app, cpu, cpu.ebx);
                cpu.esi = at(app, ebp + 0x36);
                push(app, cpu, cpu.esi);
                cpu.edi = at(app, ebp + 0x4a);
                push(app, cpu, cpu.edi);
                cpu.eax = at(app, ebp + 0x62);
                cpu.edx = at(app, ebp + 0x56);
                push(app, cpu, cpu.eax);
                cpu.ecx = at(app, ebp + 0x3a);
                cpu.ebx = at(app, ebp + 0x5a);
                push(app, cpu, cpu.edx);
                cpu.eax = at(app, ebp + 0x4e);
                cpu.edx = at(app, ebp + 0x5e);
                if (!byAddress(app, cpu, 0x4db380)) return false;  //
            }
            else
            {
                cpu.eax = cpu.edi - 2;
                put(app, ebp + 0xa, cpu.eax);
                cpu.eax = at(app, ebp + 0x6a);
                cpu.eax = reg32(cpu.eax << 2);
                cpu.bl = byte(app, kRenderFlags);
                put(app, ebp + 0x26, cpu.eax);
                if ((cpu.bl & 2) != 0)
                {
                    cpu.eax = at(app, ebp + 0x6e);
                    cpu.eax = at(app, cpu.eax + 0x84);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                    cpu.edx = cpu.eax + 0x10;
                    put(app, ebp + 0x4e, cpu.edx);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.ecx = at(app, cpu.edx + 0x82);
                    cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
                    cpu.edx = cpu.ecx + 2;
                    put(app, ebp + 0x5e, cpu.edx);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x86);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.edx = reg32(cpu.edx + cpu.eax);
                    cpu.ebx = cpu.edx - 0x10;
                    cpu.edx = reg32(cpu.edx - 1);
                    put(app, ebp + 0x56, cpu.edx);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x88);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.edx = reg32(cpu.edx + cpu.ecx);
                    cpu.edx = reg32(cpu.edx - 0x2);
                    put(app, ebp + 0x62, cpu.edx);
                    put(app, ebp + 0x36, cpu.edx);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x40);
                    cpu.eax = reg32(cpu.eax + 1);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    put(app, ebp + 0x4a, cpu.eax);
                    cpu.eax = cpu.edx * 4;
                    cpu.eax = reg32(cpu.eax - cpu.edx);
                    cpu.ecx = at(app, ebp + 0x26);
                    cpu.eax = reg32(cpu.eax << 3);
                    cpu.eax = reg32(cpu.eax + cpu.ecx);
                    put(app, ebp + 0x5a, cpu.ebx);
                    cpu.ebx = at(app, ebp + 0x5e);
                    cpu.dx = half(app, cpu.eax + 0x678ab2);
                    put(app, ebp + 0x3a, cpu.ebx);
                    if (cpu.dx == 0xffff)
                        return true;
                    cpu.ecx = at(app, ebp + 0x66);
                    cpu.ebx = cpu.edi;
                    cpu.eax = at(app, cpu.eax + 0x678ab0);
                    cpu.edx = cpu.esi;
                    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                    if (!byAddress(app, cpu, 0x4d7160)) return false;  //
                    cpu.ecx = ebp - 0x16;
                    cpu.ebx = ebp - 0x1a;
                    cpu.edx = ebp - 0x12;
                    cpu.eax = ebp - 0x1e;
                    if (!byAddress(app, cpu, 0x4beb80)) return false;  //
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x7e);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.eax = cpu.edx;
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                    cpu.eax = reg32(cpu.eax - cpu.edx);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x7c);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.edx = reg32(cpu.edx + cpu.eax);
                    cpu.edi = at(app, kScreenWidth);
                    cpu.edx = reg32(cpu.edx - cpu.esi);
                    cpu.edx = cpu.edx * cpu.edi;
                    cpu.eax = at(app, ebp + 0x6e);
                    cpu.eax = at(app, cpu.eax + 0x88);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                    cpu.ebx = at(app, kScreenHeight);
                    cpu.eax = reg32(cpu.eax + 0x4);
                    cpu.eax = cpu.eax * cpu.ebx;
                    put(app, ebp + 0x72, cpu.eax);
                    cpu.eax = at(app, ebp + 0xa);
                    cpu.eax = cpu.eax * cpu.ebx;
                    put(app, ebp + 0x76, cpu.eax);
                    cpu.eax = cpu.edi;
                    cpu.eax = cpu.eax * cpu.esi;
                    put(app, ebp + 0x7a, cpu.edx);
                    cpu.fpu.push(loadDouble(app, 0x53ae68));
                    cpu.fpu.push(integer(app, ebp + 0x7a));
                    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                    cpu.fpu.push(loadDouble(app, 0x53ae60));
                    cpu.fpu.push(integer(app, ebp + 0x72));
                    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                    cpu.fpu.push(integer(app, ebp + 0x76));
                    cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));
                    cpu.fpu.count -= 1;
                    put(app, ebp + 0x76, cpu.eax);
                    cpu.fpu.push(integer(app, ebp + 0x76));
                    cpu.fpu.st(4) = cpu.fpu.mul(cpu.fpu.st(4), cpu.fpu.st(0));
                    cpu.fpu.count -= 1;
                    exchange(cpu, 2);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    exchange(cpu, 1);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x76);
                    cpu.ecx = at(app, ebp + 0x76);
                    cpu.ebx = at(app, ebp + 0x72);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.edx = at(app, ebp + 0x72);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.eax = at(app, ebp + 0x72);
                    if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                    push(app, cpu, 0xff15052d);
                    push(app, cpu, 0xff00ff40);
                    push(app, cpu, 0xff00ff40);
                    push(app, cpu, 0xff15052d);
                    cpu.ecx = at(app, ebp + 0x62);
                    push(app, cpu, cpu.ecx);
                    cpu.ebx = at(app, ebp + 0x4a);
                    push(app, cpu, cpu.ebx);
                    cpu.edi = at(app, ebp + 0x56);
                    push(app, cpu, cpu.ecx);
                    cpu.eax = at(app, ebp + 0x4e);
                    cpu.ecx = at(app, ebp + 0x5e);
                    push(app, cpu, cpu.edi);
                    cpu.ebx = at(app, ebp + 0x5a);
                    cpu.edx = cpu.ecx;
                    if (!byAddress(app, cpu, 0x4db380)) return false;  //
                    cpu.ecx = at(app, ebp - 0x16);
                    cpu.ebx = at(app, ebp - 0x1a);
                    cpu.edx = at(app, ebp - 0x12);
                    cpu.eax = at(app, ebp - 0x1e);
                    if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                    return true;
                }
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp + 0x26);
                cpu.eax = reg32(cpu.eax << 3);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                if (half(app, cpu.eax + 0x678ab0) != 0xffff)
                {
                    cpu.ecx = ebp - 0x16;
                    cpu.ebx = ebp - 0x1a;
                    cpu.edx = ebp - 0x12;
                    cpu.eax = ebp - 0x1e;
                    if (!byAddress(app, cpu, 0x4beb80)) return false;  //
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x7e);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.eax = cpu.edx;
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                    cpu.eax = reg32(cpu.eax - cpu.edx);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x7c);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.edx = reg32(cpu.edx + cpu.eax);
                    cpu.eax = at(app, ebp + 0x6a);
                    cpu.ecx = at(app, ebp + 0x6e);
                    cpu.eax = reg32(cpu.eax << 3);
                    cpu.eax = reg32(cpu.eax + cpu.ecx);
                    cpu.eax = at(app, cpu.eax + 0x80);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                    cpu.ebx = at(app, kScreenHeight);
                    cpu.eax = reg32(cpu.eax + 0x4);
                    cpu.eax = cpu.eax * cpu.ebx;
                    cpu.edx = reg32(cpu.edx - cpu.esi);
                    put(app, ebp + 0x7a, cpu.eax);
                    cpu.edx = cpu.edx * at(app, kScreenWidth);
                    cpu.eax = at(app, ebp + 0xa);
                    cpu.eax = cpu.eax * cpu.ebx;
                    put(app, ebp + 0x76, cpu.eax);
                    cpu.eax = at(app, kScreenWidth);
                    cpu.eax = cpu.eax * cpu.esi;
                    cpu.fpu.push(loadDouble(app, 0x53ae60));
                    cpu.fpu.push(integer(app, ebp + 0x7a));
                    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                    put(app, ebp + 0x7a, cpu.edx);
                    cpu.fpu.push(loadDouble(app, 0x53ae68));
                    cpu.fpu.push(integer(app, ebp + 0x7a));
                    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                    cpu.fpu.push(integer(app, ebp + 0x76));
                    cpu.fpu.st(4) = cpu.fpu.mul(cpu.fpu.st(4), cpu.fpu.st(0));
                    cpu.fpu.count -= 1;
                    put(app, ebp + 0x76, cpu.eax);
                    cpu.fpu.push(integer(app, ebp + 0x76));
                    cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));
                    cpu.fpu.count -= 1;
                    exchange(cpu, 2);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.ecx = at(app, ebp + 0x72);
                    exchange(cpu, 1);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.ebx = at(app, ebp + 0x72);
                    exchange(cpu, 1);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.edx = at(app, ebp + 0x72);
                    if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                    storeInteger(app, cpu, ebp + 0x72);
                    cpu.eax = at(app, ebp + 0x72);
                    if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                    cpu.edx = at(app, ebp + 0x6e);
                    cpu.edx = at(app, cpu.edx + 0x40);
                    cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                    cpu.eax = cpu.edx * 4;
                    cpu.eax = reg32(cpu.eax - cpu.edx);
                    cpu.ecx = at(app, ebp + 0x26);
                    cpu.eax = reg32(cpu.eax << 3);
                    cpu.eax = reg32(cpu.eax + cpu.ecx);
                    cpu.ebx = cpu.edi;
                    cpu.edx = cpu.esi;
                    cpu.eax = at(app, cpu.eax + 0x678aae);
                    cpu.ecx = at(app, ebp + 0x66);
                    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                    if (!byAddress(app, cpu, 0x4d7160)) return false;  //
                    cpu.ecx = at(app, ebp - 0x16);
                    cpu.ebx = at(app, ebp - 0x1a);
                    cpu.edx = at(app, ebp - 0x12);
                    cpu.eax = at(app, ebp - 0x1e);
                    if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                }
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp + 0x6a);
                cpu.eax = reg32(cpu.eax << 3);
                cpu.edx = reg32(cpu.edx << 2);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                cpu.cx = half(app, cpu.eax + 0x678ab2);
                put(app, ebp - 0xa, cpu.edx);
                if (cpu.cx == 0xffff)
                    return true;
                cpu.ecx = ebp - 0x16;
                cpu.ebx = ebp - 0x1a;
                cpu.edx = ebp - 0x12;
                cpu.eax = ebp - 0x1e;
                if (!byAddress(app, cpu, 0x4beb80)) return false;  //
                cpu.eax = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.eax + 0x7e);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx;
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                cpu.edx = cpu.eax;
                cpu.eax = at(app, ebp + 0x6e);
                cpu.eax = at(app, cpu.eax + 0x7c);
                cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                cpu.ecx = at(app, ebp + 0x6e);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                cpu.edx = at(app, ebp + 0x6e);
                cpu.ecx = at(app, cpu.ecx + 0x86);
                cpu.edx = at(app, cpu.edx + 0x84);
                cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.edx = reg32(cpu.edx + cpu.ecx);
                cpu.edx = reg32(cpu.edx - cpu.eax);
                cpu.ecx = cpu.edx - 1;
                cpu.edx = at(app, ebp + 0x6a);
                cpu.ebx = at(app, ebp + 0x6e);
                cpu.edx = reg32(cpu.edx << 3);
                cpu.edx = reg32(cpu.edx + cpu.ebx);
                cpu.edx = at(app, cpu.edx + 0x80);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.ebx = at(app, kScreenHeight);
                cpu.edx = reg32(cpu.edx + 0x4);
                cpu.edx = cpu.edx * cpu.ebx;
                put(app, ebp + 0x76, cpu.edx);
                cpu.edx = at(app, kScreenWidth);
                cpu.edx = cpu.edx * cpu.ecx;
                put(app, ebp + 0x7a, cpu.edx);
                cpu.edx = cpu.edi - 2;
                cpu.edx = cpu.edx * cpu.ebx;
                cpu.eax = cpu.eax * at(app, kScreenWidth);
                cpu.fpu.push(loadDouble(app, 0x53ae60));
                cpu.fpu.push(integer(app, ebp + 0x76));
                cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                cpu.fpu.push(loadDouble(app, 0x53ae68));
                cpu.fpu.push(integer(app, ebp + 0x7a));
                cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
                put(app, ebp + 0x7a, cpu.edx);
                cpu.fpu.push(integer(app, ebp + 0x7a));
                cpu.fpu.st(4) = cpu.fpu.mul(cpu.fpu.st(4), cpu.fpu.st(0));
                cpu.fpu.count -= 1;
                put(app, ebp + 0x7a, cpu.eax);
                cpu.fpu.push(integer(app, ebp + 0x7a));
                cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));
                cpu.fpu.count -= 1;
                exchange(cpu, 2);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                cpu.ecx = at(app, ebp + 0x72);
                exchange(cpu, 1);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x76);
                exchange(cpu, 1);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                cpu.edx = at(app, ebp + 0x72);
                cpu.ebx = at(app, ebp + 0x76);
                if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
                storeInteger(app, cpu, ebp + 0x72);
                cpu.eax = at(app, ebp + 0x72);
                if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp - 0xa);
                cpu.eax = reg32(cpu.eax << 3);
                cpu.eax = reg32(cpu.eax + cpu.edx);
                cpu.ecx = at(app, ebp + 0x66);
                cpu.ebx = cpu.edi;
                cpu.eax = at(app, cpu.eax + 0x678ab0);
                cpu.edx = cpu.esi;
                cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
                if (!byAddress(app, cpu, 0x4d7160)) return false;  //
            }
            cpu.ecx = at(app, ebp - 0x16);
            cpu.ebx = at(app, ebp - 0x1a);
            cpu.edx = at(app, ebp - 0x12);
            cpu.eax = at(app, ebp - 0x1e);
            if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
            return true;
        }
        // An arrow or the thumb.
        if (at(app, kMenu3d) != 0)
        {
            put(app, ebp + 0x4e, cpu.esi);
            put(app, ebp + 0x5e, cpu.edi);
            cpu.eax = cpu.esi + cpu.edx;
            put(app, ebp + 0x3a, cpu.edi);
            put(app, ebp + 0x5a, cpu.eax);
            put(app, ebp + 0x56, cpu.eax);
            put(app, ebp + 0x4a, cpu.esi);
            cpu.eax = cpu.edi + cpu.ebx;
            cpu.ebx = at(app, ebp + 0x6a);
            put(app, ebp + 0x62, cpu.eax);
            put(app, ebp + 0x36, cpu.eax);
            if (cpu.ebx == 3)
            {
                cpu.eax = at(app, ebp + 0x5a);
                put(app, ebp + 0x5a, cpu.esi);
                put(app, ebp + 0x4e, cpu.eax);
                cpu.eax = at(app, ebp + 0x56);
                put(app, ebp + 0x56, cpu.esi);
                put(app, ebp + 0x4a, cpu.eax);
            }
        }
        cpu.eax = at(app, ebp + 0x6a);
        if (cpu.eax == at(app, ebp + 0xe) && at(app, ebp + 0x22) != 0)
        {
            if (at(app, kMenu3d) != 0)
            {
                cpu.edx = at(app, ebp + 0x6e);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.esi = at(app, ebp + 0x66);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                push(app, cpu, cpu.esi);
                cpu.eax = cpu.edx * 4;
                cpu.edi = at(app, 0x749a38);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                push(app, cpu, cpu.edi);
                cpu.edx = cpu.eax;
                cpu.eax = at(app, ebp + 0x6a);
                cpu.edx = reg32(cpu.edx << 6);
                cpu.eax = reg32(cpu.eax << 5);
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a988));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a984));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a980));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a97c));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a978));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a974));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a970));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a96c));
                cpu.eax = at(app, ebp + 0x36);
                push(app, cpu, cpu.eax);
                cpu.edx = at(app, ebp + 0x4a);
                push(app, cpu, cpu.edx);
                cpu.ecx = at(app, ebp + 0x62);
                cpu.ebx = at(app, ebp + 0x56);
                push(app, cpu, cpu.ecx);
                cpu.eax = at(app, ebp + 0x4e);
                cpu.edx = at(app, ebp + 0x5e);
                push(app, cpu, cpu.ebx);
                cpu.ecx = at(app, ebp + 0x3a);
                cpu.ebx = at(app, ebp + 0x5a);
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                return true;
            }
            cpu.edx = at(app, ebp + 0x6e);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = cpu.edx * 4;
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.edx = at(app, ebp + 0x6a);
            cpu.eax = reg32(cpu.eax << 3);
            cpu.edx = reg32(cpu.edx << 2);
            cpu.eax = reg32(cpu.eax + cpu.edx);
            if (half(app, cpu.eax + 0x678ab0) == 0xffff)
                return true;
            cpu.ecx = at(app, ebp + 0x66);
            cpu.ebx = cpu.edi;
            cpu.eax = at(app, cpu.eax + 0x678aae);
            cpu.edx = cpu.esi;
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            if (!byAddress(app, cpu, 0x4d7160)) return false;  //
            return true;
        }
        if (at(app, kMenu3d) != 0)
        {
            cpu.edx = at(app, ebp + 0x66);
            push(app, cpu, cpu.edx);
            cpu.edx = at(app, ebp + 0x6e);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = cpu.edx * 4;
            cpu.ecx = at(app, 0x749a38);
            cpu.eax = reg32(cpu.eax - cpu.edx);
            push(app, cpu, cpu.ecx);
            cpu.edx = cpu.eax;
            cpu.eax = at(app, ebp + 0x6a);
            cpu.edx = reg32(cpu.edx << 6);
            cpu.eax = reg32(cpu.eax << 5);
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a508));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a504));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a500));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4fc));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f8));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f4));
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f0));
            cpu.ebx = at(app, ebp + 0x36);
            push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4ec));
            push(app, cpu, cpu.ebx);
            cpu.esi = at(app, ebp + 0x4a);
            push(app, cpu, cpu.esi);
            cpu.edi = at(app, ebp + 0x62);
            cpu.ecx = at(app, ebp + 0x3a);
            push(app, cpu, cpu.edi);
            cpu.eax = at(app, ebp + 0x56);
            cpu.edx = at(app, ebp + 0x5e);
            push(app, cpu, cpu.eax);
            cpu.ebx = at(app, ebp + 0x5a);
            cpu.eax = at(app, ebp + 0x4e);
            if (!byAddress(app, cpu, 0x4db000)) return false;  //
            return true;
        }
        cpu.edx = at(app, ebp + 0x6e);
        cpu.edx = at(app, cpu.edx + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.edx = cpu.eax * 8;
        cpu.eax = at(app, ebp + 0x6a);
        cpu.eax = reg32(cpu.eax << 2);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        if (half(app, cpu.eax + 0x678ab2) == 0xffff)
            return true;
        cpu.ecx = at(app, ebp + 0x66);
        cpu.ebx = cpu.edi;
        cpu.eax = at(app, cpu.eax + 0x678ab0);
        cpu.edx = cpu.esi;
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        if (!byAddress(app, cpu, 0x4d7160)) return false;  //
        return true;
    };
    if (at(app, ebp + 0x32) == 0)
    {
        cpu.edx = at(app, ebp + 0x6e);
        cpu.eax = at(app, ebp + 0x6e);
        cpu.bx = half(app, cpu.edx + 0xb2);
        if (cpu.bx == half(app, cpu.eax + 0xa))
        {
            cpu.eax = at(app, cpu.edx + 0x40);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            cpu.eax = at(app, cpu.eax * 2 + 0x55a4de);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            cpu.eax = reg32(cpu.eax - 1);
            put(app, ebp + 0x6a, cpu.eax);
            while (sreg32(at(app, ebp + 0x6a)) >= 0)
            {
                if (!drawPart())
                    return;
                put(app, ebp + 0x6a, at(app, ebp + 0x6a) - 1);
            }
        }
    }
    // Its texts.
    cpu.eax = at(app, ebp + 0x6e);
    cpu.eax = at(app, cpu.eax + 0x1a);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    put(app, ebp + 0x2e, cpu.eax);
    cpu.eax = at(app, ebp + 0x6e);
    cpu.eax = at(app, cpu.eax + 0x18);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    put(app, ebp + 0x3e, cpu.eax);
    cpu.eax = at(app, ebp + 0x6e);
    cpu.eax = at(app, cpu.eax + 0x1c);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    put(app, ebp + 0x16, cpu.eax);
    cpu.eax = at(app, ebp + 0x6e);
    cpu.edi = at(app, cpu.eax + 0x1e);
    cpu.eax = at(app, ebp + 0x16);
    cpu.edx = cpu.eax;
    cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
    cpu.eax = reg32(cpu.eax - cpu.edx);
    cpu.eax = reg32(sreg32(cpu.eax) >> 1);
    cpu.edx = at(app, ebp + 0x2e);
    cpu.edx = reg32(cpu.edx + cpu.eax);
    cpu.edi = reg32(sreg32(cpu.edi) >> 0x10);
    put(app, ebp + 0x1e, cpu.edx);
    cpu.edx = cpu.edi;
    cpu.eax = cpu.edi;
    cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
    cpu.eax = reg32(cpu.eax - cpu.edx);
    cpu.eax = reg32(sreg32(cpu.eax) >> 1);
    cpu.edx = at(app, ebp + 0x3e);
    cpu.edx = reg32(cpu.edx + cpu.eax);
    cpu.ecx = at(app, ebp + 0x32);
    put(app, ebp + 0x1a, cpu.edx);
    bool labels = false;
    if (cpu.ecx == 0)
    {
        cpu.eax = at(app, ebp + 0x6e);
        labels = at(app, cpu.eax + 0x68) != 0 || at(app, cpu.eax + 0x6c) != 0 || at(app, cpu.eax + 0x70) != 0;
    }
    if (labels)
    {
        cpu.eax = 0x12;
        if (!byAddress(app, cpu, 0x452100)) return;  //
        cpu.eax = at(app, ebp + 0x6e);
        cpu.bh = 0x1;
        cpu.al = byte(app, cpu.eax + 0x74);
        putByte(app, ebp + 0x7e, x86::reg8(cpu.bh));
        if (cpu.al != 0 && cpu.al == cpu.bh)
        {
            cpu.esi = at(app, ebp + 0x3e);
            cpu.esi = reg32(cpu.esi + cpu.edi);
        }
        else
        {
            cpu.esi = at(app, ebp + 0x3e);
            cpu.esi = reg32(cpu.esi - at(app, ebp + 0x52));
        }
        cpu.eax = at(app, ebp + 0x6e);
        if (at(app, cpu.eax + 0x68) != 0)
        {
            cpu.edx = at(app, cpu.eax + 0x8c);
            cpu.eax = at(app, ebp + 0x46);
            push(app, cpu, cpu.eax);
            cpu.ecx = 0x12;
            cpu.ebx = cpu.esi;
            push(app, cpu, 0x0);
            cpu.eax = at(app, ebp + 0x6e);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = at(app, cpu.eax + 0x68);
            if (!byAddress(app, cpu, 0x452190)) return;  //
        }
        cpu.eax = at(app, ebp + 0x6e);
        cpu.edx = at(app, cpu.eax + 0x6c);
        if (cpu.edx != 0)
        {
            cpu.ecx = at(app, ebp + 0x46);
            push(app, cpu, cpu.ecx);
            cpu.eax = cpu.edx;
            cpu.ebx = cpu.esi;
            push(app, cpu, 0x2);
            cpu.edx = at(app, ebp + 0x1e);
            cpu.ecx = 0x12;
            if (!byAddress(app, cpu, 0x452190)) return;  //
        }
        cpu.eax = at(app, ebp + 0x6e);
        if (at(app, cpu.eax + 0x70) != 0)
        {
            cpu.edx = at(app, ebp + 0x6e);
            cpu.eax = at(app, cpu.eax + 0x94);
            cpu.edx = at(app, cpu.edx + 0x96);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.edx = reg32(cpu.edx + cpu.eax);
            cpu.eax = at(app, ebp + 0x46);
            push(app, cpu, cpu.eax);
            cpu.ecx = 0x12;
            cpu.eax = at(app, ebp + 0x6e);
            push(app, cpu, 0x1);
            cpu.ebx = cpu.esi;
            cpu.eax = at(app, cpu.eax + 0x70);
            if (!byAddress(app, cpu, 0x452190)) return;  //
        }
    }
    cpu.eax = at(app, ebp + 0x6e);
    if (at(app, cpu.eax + 0x60) != 0)
    {
        // Its title, placed by its alignment.
        cpu.eax = 0x12;
        if (!byAddress(app, cpu, 0x452100)) return;  //
        cpu.eax = at(app, ebp + 0x6e);
        cpu.al = byte(app, cpu.eax + 0x75);
        x86::reg8 alignment = 0;
        if (cpu.al <= 4)
        {
            cpu.eax &= 0xff;
            alignment = cpu.al;
        }
        if (alignment == 3)
        {
            cpu.eax = at(app, ebp + 0x3e);
            cpu.cl = byte(app, ebp + 0x7e);
            cpu.eax = reg32(cpu.eax + cpu.edi);
            if (cpu.cl != 0)
            {
                cpu.edx = at(app, ebp + 0x6e);
                if (byte(app, cpu.edx + 0x74) == 1)
                    cpu.eax += at(app, ebp + 0x52);
            }
            cpu.ecx = 0x2;
            cpu.edx = at(app, ebp + 0x1e);
        }
        else if (alignment == 2)
        {
            cpu.eax = at(app, ebp + 0x3e);
            cpu.ebx = at(app, ebp + 0x52);
            cpu.dl = byte(app, ebp + 0x7e);
            cpu.eax = reg32(cpu.eax - cpu.ebx);
            if (cpu.dl != 0)
            {
                cpu.edx = at(app, ebp + 0x6e);
                if (byte(app, cpu.edx + 0x74) == 0)
                    cpu.eax -= at(app, ebp + 0x52);
            }
            cpu.ecx = 0x2;
            cpu.edx = at(app, ebp + 0x1e);
        }
        else if (alignment == 1)
        {
            cpu.eax = at(app, ebp + 0x52);
            cpu.edx = cpu.eax;
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.eax = reg32(sreg32(cpu.eax) >> 1);
            cpu.edx = at(app, ebp + 0x1a);
            cpu.edx = reg32(cpu.edx - cpu.eax);
            cpu.edi = at(app, ebp + 0x16);
            cpu.eax = cpu.edx;
            cpu.edx = at(app, ebp + 0x2e);
            cpu.edx = reg32(cpu.edx + cpu.edi);
            cpu.ecx = 0;
            cpu.edx = reg32(cpu.edx + 0xa);
        }
        else if (alignment == 4)
        {
            cpu.edx = at(app, ebp + 0x6e);
            cpu.eax = at(app, ebp + 0x6e);
            cpu.ecx = 0;
            cpu.edx = at(app, cpu.edx + 0x62);
            cpu.eax = at(app, cpu.eax + 0x64);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        }
        else
        {
            bool own = false;
            if (at(app, kMenu3d) == 0)
            {
                cpu.eax = at(app, ebp + 0x6e);
                own = byte(app, cpu.eax + 0x3d) != 0;
            }
            if (own)
            {
                cpu.edx = at(app, cpu.eax + 0x3e);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = at(app, cpu.edx * 4 + 0x559c94);
                cpu.edx = at(app, cpu.edx * 4 + 0x559c6c);
                cpu.ecx = 0;
                cpu.edx = reg32(cpu.edx + 0xb);
            }
            else
            {
                cpu.eax = at(app, ebp + 0x52);
                cpu.edx = cpu.eax;
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.eax = reg32(sreg32(cpu.eax) >> 1);
                cpu.edx = at(app, ebp + 0x1a);
                cpu.edx = reg32(cpu.edx - cpu.eax);
                cpu.eax = cpu.edx;
                cpu.edx = at(app, ebp + 0x2e);
                cpu.ecx = 0x1;
                cpu.edx = reg32(cpu.edx - 0xa);
            }
        }
        cpu.ebx = at(app, ebp + 0x6e);
        cpu.esi = at(app, ebp + 0x6e);
        cpu.bx = half(app, cpu.ebx + 0xb2);
        putHalf(app, cpu.esi + 0xa, x86::reg16(cpu.bx));
        if (at(app, ebp + 0x32) == 0 || byte(app, cpu.esi + 0x75) == 0)
        {
            cpu.edi = at(app, kMenu3d);
            cpu.esi = cpu.edx;
            if (cpu.edi == 0)
            {
                cpu.ebx = at(app, ebp + 0x6e);
                if (byte(app, cpu.ebx + 0x75) == 0)
                {
                    if (at(app, 0x559c60) != 0)
                    {
                        // Slid in from the right as its screen comes in.
                        cpu.ebx = at(app, ebp + 0x6e);
                        cpu.ebx = at(app, cpu.ebx + 6);
                        cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
                        cpu.edi = cpu.ebx;
                        cpu.edi = reg32(cpu.edi - at(app, 0x559c94));
                        cpu.edi = reg32(cpu.edi + at(app, 0x559c60));
                        cpu.edi = reg32(cpu.edi - 0x12c);
                        if (sreg32(cpu.edi) > 0x64)
                            cpu.esi = 0x280;
                        else if (sreg32(cpu.edi) > 0)
                            cpu.esi = cpu.edx + cpu.edi;
                        cpu.edx = at(app, ebp + 0x6e);
                        cpu.dx = half(app, cpu.edx + 0xb2);
                        cpu.ebx = at(app, ebp + 0x6e);
                        cpu.edx = reg32(cpu.edx + 0x2);
                        putHalf(app, cpu.ebx + 0xa, x86::reg16(cpu.dx));
                    }
                    else
                    {
                        cpu.edx = at(app, ebp + 0x6e);
                        if (half(app, cpu.edx + 0xb6) != 0)
                        {
                            // Slid in by its own count, 0x14 a frame.
                            cpu.dx = half(app, cpu.edx + 0xb2);
                            cpu.ebx = at(app, ebp + 0x6e);
                            cpu.edx = reg32(cpu.edx + 0x2);
                            putHalf(app, cpu.ebx + 0xa, x86::reg16(cpu.dx));
                            if ((byte(app, kRenderFlags) & 2) != 0)
                                putHalf(app, cpu.ebx + 0xb6, 0);
                            cpu.edx = at(app, ebp + 0x6e);
                            cpu.bx = half(app, cpu.edx + 0xb6);
                            cpu.ebx = reg32(cpu.ebx - 0x14);
                            putHalf(app, cpu.edx + 0xb6, x86::reg16(cpu.bx));
                            if (x86::sreg16(cpu.bx) <= 0)
                            {
                                if (x86::sreg16(cpu.bx) < 0)
                                    putHalf(app, cpu.edx + 0xb6, 0);
                                cpu.edx = at(app, ebp + 0x6e);
                                cpu.ebx = at(app, ebp + 0x6e);
                                cpu.dx = half(app, cpu.edx + 0xb2);
                                putHalf(app, cpu.ebx + 0xa, x86::reg16(cpu.dx));
                            }
                            cpu.edx = at(app, ebp + 0x6e);
                            if (x86::sreg16(half(app, cpu.edx + 0xb6)) < 0x64)
                                cpu.edx = high(app, cpu.edx + 0xb4);
                            else
                                cpu.edx = 0x64;
                            cpu.esi += cpu.edx;
                        }
                    }
                }
            }
            cpu.edi = at(app, ebp + 0x46);
            push(app, cpu, cpu.edi);
            cpu.edx = at(app, ebp + 0x6e);
            cpu.ebx = cpu.eax;
            push(app, cpu, cpu.ecx);
            cpu.edi = at(app, cpu.edx + 0x60);
            cpu.ecx = 0x12;
            cpu.edx = cpu.esi;
            cpu.eax = cpu.edi;
            if (!byAddress(app, cpu, 0x452190)) return;  //
        }
    }
    // Its value, as a percentage.
    if (at(app, ebp + 0x32) == 0)
    {
        cpu.eax = at(app, ebp + 0x6e);
        cpu.al = byte(app, cpu.eax + 0x3c);
        if (cpu.al == 1)
        {
            cpu.eax = at(app, ebp + 0x52);
            cpu.edx = cpu.eax;
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.eax = reg32(sreg32(cpu.eax) >> 1);
            cpu.ebx = at(app, ebp + 0x1a);
            cpu.ebx = reg32(cpu.ebx - cpu.eax);
            cpu.eax = at(app, ebp + 0x6e);
            cpu.eax = at(app, cpu.eax + 0x54);
            push(app, cpu, cpu.eax);
            cpu.ecx = at(app, ebp + 0x16);
            push(app, cpu, 0x3c23d70a);
            if (!byAddress(app, cpu, 0x4693c0)) return;  //
            cpu.fpu.st(0) = cpu.fpu.sub(loadFloat(app, 0x53ae70), cpu.fpu.st(0));
            cpu.edx = at(app, ebp + 0x2e);
            cpu.fpu.st(0) = -cpu.fpu.st(0);
            cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x53ae74));
            cpu.edx = reg32(cpu.edx + cpu.ecx);
            cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x53ae78));
            cpu.edx = reg32(cpu.edx + 0xa);
            cpu.ecx = 0;
            cpu.fpu.push(0.0);
            exchange(cpu, 1);
            storeFloat(app, ebp + 0x42, cpu.fpu.pop());
            comparePop(cpu, loadFloat(app, ebp + 0x42));
            cpu.fpu.push(loadFloat(app, ebp + 0x42));
            cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, belowOrEqual(cpu) ? 0x53ae80 : 0x53ae7c));
            storeFloat(app, ebp + 0x42, cpu.fpu.pop());
            cpu.fpu.push(loadFloat(app, ebp + 0x42));
            push(app, cpu, 0x25);
            if (!byAddress(app, cpu, 0x4dfd56)) return;  //
            storeInteger(app, cpu, ebp + 0x72);
            cpu.esi = at(app, ebp + 0x72);
            push(app, cpu, cpu.esi);
            push(app, cpu, 0x53ae54);
            cpu.eax = ebp - 0x42;
            push(app, cpu, cpu.eax);
            if (!byAddress(app, cpu, 0x4df690)) return;  //
            cpu.esp = reg32(cpu.esp + 0x10);
            cpu.edi = at(app, ebp + 0x46);
            push(app, cpu, cpu.edi);
            push(app, cpu, cpu.ecx);
            cpu.eax = ebp - 0x42;
            cpu.ecx = 0x12;
            if (!byAddress(app, cpu, 0x452190)) return;  //
        }
    }
    cpu.eax = 0;
    cpu.esp = ebp + 0x82;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}



/* 0x46b3a0: the two-axis slider at eax drawn, in the menus' art of its
 * kind, its parts from the last: its thumbs (0 to 3) and its bar's thumb (4)
 * as quads of the art on the 3D card or shapes on a 2D screen, in its colours
 * or the part under the pointer's hot ones where edx asks for it; its area
 * (5) as a frame of shaded quads -- the 2D screens' clipped to it, its art
 * drawn at each corner.  Then its title in the 2D screens' font, placed by its
 * alignment (0x75), and its values as percentages.  eax 0. */
void drawTwoAxis(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi, &cpu.edi}, 0xa0);
    cpu.ebp -= 0x82;
    const reg32 ebp = cpu.ebp;
    put(app, ebp + 0x6a, cpu.eax);
    cpu.ecx = 0xe;
    cpu.ebx = 0xffffffff;
    cpu.edi = ebp - 0x1e;
    cpu.esi = 0x469040;
    put(app, ebp + 0x3a, cpu.ecx);
    cpu.ecx = 0x10;
    cpu.ah = byte(app, 0x55eb2e);
    put(app, ebp + 0x46, cpu.ebx);
    copyDwords(app, cpu);
    // Greyed where the menus grey their controls but this one (0x18).
    const x86::reg8 menus = cpu.ah;
    bool kept = (menus & 0x20) != 0 && (byte(app, at(app, ebp + 0x6a) + 0x18) & 1) != 0;
    if ((menus & 0x20) != 0)
        cpu.eax = at(app, ebp + 0x6a);
    if (!kept)
    {
        if ((byte(app, 0x55eb2e) & 0x10) != 0)
        {
            cpu.eax = at(app, ebp + 0x6a);
            kept = half(app, cpu.eax + 0x18) != 0;
        }
        if (!kept)
        {
            cpu.cl = byte(app, 0x55eb2e);
            if ((cpu.cl & 0x30) != 0)
            {
                cpu.eax = at(app, ebp + 0x6a);
                putByte(app, cpu.eax + 4, byte(app, cpu.eax + 4) | 1);
            }
        }
    }
    if (cpu.edx != 0)
    {
        cpu.eax = at(app, ebp + 0x6a);
        cpu.esi = 0xffe440;
        if (!byAddress(app, cpu, 0x4692c0)) return;  //
        put(app, ebp + 0x46, cpu.eax);
        put(app, ebp + 0x3e, cpu.esi);
    }
    else
    {
        put(app, ebp + 0x3e, 0xff649dfd);
    }
    cpu.eax = at(app, ebp + 0x6a);
    cpu.eax = at(app, cpu.eax + 0x40);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    cpu.eax = at(app, cpu.eax * 2 + 0x55a4de);
    cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
    cpu.eax = reg32(cpu.eax - 1);
    put(app, ebp + 0x5e, cpu.eax);
    // Its parts, from the last.
    auto drawPart = [&]() -> bool {
        cpu.edx = at(app, ebp + 0x6a);
        cpu.eax = reg32(cpu.eax << 3);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        cpu.edx = at(app, cpu.eax + 0x7c);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        put(app, ebp + 0x62, cpu.edx);
        cpu.edx = at(app, cpu.eax + 0x7a);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.ecx = at(app, ebp + 0x5e);
        put(app, ebp + 0x66, cpu.edx);
        cpu.edx = at(app, cpu.eax + 0x7e);
        cpu.edi = at(app, cpu.eax + 0x80);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.edi = reg32(sreg32(cpu.edi) >> 0x10);
        put(app, ebp + 0x52, cpu.edx);
        if (cpu.ecx > 5)
            return true;
        cpu.esi = cpu.ecx * 4;
        if (cpu.ecx < 2)
        {
            // A thumb across.
            if (at(app, kMenu3d) != 0)
            {
                cpu.edx = at(app, ebp + 0x66);
                cpu.ecx = at(app, ebp + 0x5e);
                cpu.ebx = at(app, ebp + 0x62);
                cpu.esi = at(app, ebp + 0x52);
                cpu.eax = at(app, ebp + 0x46);
                cpu.ecx = reg32(cpu.ecx << 5);
                cpu.edx = reg32(cpu.edx + cpu.edi);
                cpu.edi = at(app, ebp + 0x5e);
                cpu.ebx = reg32(cpu.ebx + cpu.esi);
                if (cpu.eax == cpu.edi)
                {
                    push(app, cpu, 0xffffffff);
                    cpu.eax = at(app, 0x749a38);
                    push(app, cpu, cpu.eax);
                    cpu.eax = at(app, ebp + 0x6a);
                    cpu.esi = at(app, cpu.eax + 0x40);
                    cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
                    cpu.eax = cpu.esi * 4;
                    cpu.eax = reg32(cpu.eax - cpu.esi);
                    cpu.eax = reg32(cpu.eax << 6);
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a988));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a984));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a980));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a97c));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a978));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a974));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a970));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a96c));
                    push(app, cpu, cpu.edx);
                    cpu.ecx = at(app, ebp + 0x62);
                    push(app, cpu, cpu.ecx);
                    push(app, cpu, cpu.edx);
                    cpu.ecx = at(app, ebp + 0x66);
                    push(app, cpu, cpu.ebx);
                    cpu.eax = at(app, ebp + 0x62);
                }
                else
                {
                    push(app, cpu, 0xffffffff);
                    cpu.esi = at(app, 0x749a38);
                    cpu.eax = at(app, ebp + 0x6a);
                    push(app, cpu, cpu.esi);
                    cpu.esi = at(app, cpu.eax + 0x40);
                    cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
                    cpu.eax = cpu.esi * 4;
                    cpu.eax = reg32(cpu.eax - cpu.esi);
                    cpu.eax = reg32(cpu.eax << 6);
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a508));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a504));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a500));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a4fc));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a4f8));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a4f4));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a4f0));
                    push(app, cpu, at(app, cpu.ecx + cpu.eax + 0x55a4ec));
                    push(app, cpu, cpu.edx);
                    cpu.edi = at(app, ebp + 0x62);
                    push(app, cpu, cpu.edi);
                    push(app, cpu, cpu.edx);
                    cpu.ecx = at(app, ebp + 0x66);
                    push(app, cpu, cpu.ebx);
                    cpu.eax = cpu.edi;
                }
                cpu.edx = cpu.ecx;
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                return true;
            }
            cpu.edx = at(app, ebp + 0x5e);
            cpu.eax = at(app, ebp + 0x46);
            cpu.ecx = at(app, ebp + 0x5e);
            cpu.edx = reg32(cpu.edx << 2);
            if (cpu.eax == cpu.ecx)
            {
                cpu.eax = at(app, ebp + 0x6a);
                cpu.ebx = at(app, cpu.eax + 0x40);
                cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
                cpu.eax = cpu.ebx * 4;
                cpu.eax = reg32(cpu.eax - cpu.ebx);
                cpu.ax = half(app, cpu.edx + cpu.eax * 8 + 0x678ab0);
            }
            else
            {
                cpu.eax = at(app, ebp + 0x6a);
                cpu.ebx = at(app, cpu.eax + 0x40);
                cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
                cpu.eax = cpu.ebx * 4;
                cpu.eax = reg32(cpu.eax - cpu.ebx);
                cpu.ax = half(app, cpu.edx + cpu.eax * 8 + 0x678ab2);
            }
            if (cpu.ax == 0xffff)
                return true;
            cpu.edx = at(app, ebp + 0x5e);
            cpu.ebx = at(app, ebp + 0x6a);
            cpu.edx = reg32(cpu.edx << 3);
            cpu.edx = reg32(cpu.edx + cpu.ebx);
            cpu.ecx = at(app, cpu.edx + 0x7c);
            cpu.edx = at(app, cpu.edx + 0x7a);
            cpu.eax = reg32(x86::sreg16(cpu.ax));
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            put(app, ebp + 0x66, cpu.edx);
            cpu.ebx = cpu.edx;
            cpu.edx = cpu.ecx;
            put(app, ebp + 0x62, cpu.ecx);
            if (!byAddress(app, cpu, 0x4d7990)) return false;  //
            return true;
        }
        if (cpu.ecx < 4)
        {
            // A thumb up.
            if (at(app, kMenu3d) != 0)
            {
                cpu.ebx = at(app, ebp + 0x5e);
                cpu.esi = at(app, ebp + 0x62);
                cpu.eax = at(app, ebp + 0x52);
                cpu.edx = at(app, ebp + 0x66);
                cpu.ecx = at(app, ebp + 0x5e);
                cpu.ebx = reg32(cpu.ebx << 5);
                cpu.esi = reg32(cpu.esi + cpu.eax);
                cpu.eax = at(app, ebp + 0x46);
                cpu.edx = reg32(cpu.edx + cpu.edi);
                if (cpu.eax == cpu.ecx)
                {
                    push(app, cpu, 0xffffffff);
                    cpu.edi = at(app, 0x749a38);
                    cpu.eax = at(app, ebp + 0x6a);
                    push(app, cpu, cpu.edi);
                    cpu.edi = at(app, cpu.eax + 0x40);
                    cpu.edi = reg32(sreg32(cpu.edi) >> 0x10);
                    cpu.eax = cpu.edi * 4;
                    cpu.eax = reg32(cpu.eax - cpu.edi);
                    cpu.eax = reg32(cpu.eax << 6);
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a988));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a984));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a980));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a97c));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a978));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a974));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a970));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a96c));
                    push(app, cpu, cpu.edx);
                    push(app, cpu, cpu.esi);
                    cpu.eax = at(app, ebp + 0x62);
                    push(app, cpu, cpu.edx);
                    cpu.ecx = at(app, ebp + 0x66);
                    cpu.ebx = cpu.eax;
                    push(app, cpu, cpu.eax);
                    cpu.edx = cpu.ecx;
                    cpu.eax = cpu.esi;
                }
                else
                {
                    push(app, cpu, 0xffffffff);
                    cpu.ecx = at(app, 0x749a38);
                    cpu.eax = at(app, ebp + 0x6a);
                    push(app, cpu, cpu.ecx);
                    cpu.ecx = at(app, cpu.eax + 0x40);
                    cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
                    cpu.eax = cpu.ecx * 4;
                    cpu.eax = reg32(cpu.eax - cpu.ecx);
                    cpu.eax = reg32(cpu.eax << 6);
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a508));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a504));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a500));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a4fc));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a4f8));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a4f4));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a4f0));
                    push(app, cpu, at(app, cpu.ebx + cpu.eax + 0x55a4ec));
                    push(app, cpu, cpu.edx);
                    push(app, cpu, cpu.esi);
                    push(app, cpu, cpu.edx);
                    cpu.ebx = at(app, ebp + 0x62);
                    cpu.ecx = at(app, ebp + 0x66);
                    push(app, cpu, cpu.ebx);
                    cpu.eax = cpu.esi;
                    cpu.edx = cpu.ecx;
                }
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                return true;
            }
            cpu.ebx = at(app, ebp + 0x5e);
            cpu.eax = at(app, ebp + 0x46);
            cpu.esi = at(app, ebp + 0x5e);
            cpu.ebx = reg32(cpu.ebx << 2);
            if (cpu.eax == cpu.esi)
            {
                cpu.edx = at(app, ebp + 0x6a);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.ax = half(app, cpu.ebx + cpu.eax * 8 + 0x678ab0);
            }
            else
            {
                cpu.edx = at(app, ebp + 0x6a);
                cpu.edx = at(app, cpu.edx + 0x40);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.eax = cpu.edx * 4;
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.ax = half(app, cpu.ebx + cpu.eax * 8 + 0x678ab2);
            }
            if (cpu.ax == 0xffff)
                return true;
            cpu.edx = at(app, ebp + 0x5e);
            cpu.edi = at(app, ebp + 0x6a);
            cpu.edx = reg32(cpu.edx << 3);
            cpu.edx = reg32(cpu.edx + cpu.edi);
            cpu.ecx = at(app, cpu.edx + 0x7c);
            cpu.edx = at(app, cpu.edx + 0x7a);
            cpu.eax = reg32(x86::sreg16(cpu.ax));
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            put(app, ebp + 0x66, cpu.edx);
            cpu.ebx = cpu.edx;
            cpu.edx = cpu.ecx;
            put(app, ebp + 0x62, cpu.ecx);
            if (!byAddress(app, cpu, 0x4d7990)) return false;  //
            return true;
        }
        if (cpu.ecx == 4)
        {
            // The bar's thumb.
            if (at(app, kMenu3d) != 0)
            {
                cpu.ebx = at(app, ebp + 0x62);
                cpu.ebx = reg32(cpu.ebx + cpu.edx);
                cpu.edx = at(app, ebp + 0x6a);
                cpu.edx = at(app, cpu.edx + 0x40);
                push(app, cpu, 0xffffffff);
                cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
                cpu.esi = at(app, 0x749a38);
                cpu.eax = cpu.edx * 4;
                push(app, cpu, cpu.esi);
                cpu.eax = reg32(cpu.eax - cpu.edx);
                cpu.edx = at(app, ebp + 0x5e);
                cpu.eax = reg32(cpu.eax << 6);
                cpu.edx = reg32(cpu.edx << 5);
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a508));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a504));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a500));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4fc));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f8));
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f4));
                cpu.ecx = at(app, ebp + 0x66);
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4f0));
                cpu.edi = reg32(cpu.edi + cpu.ecx);
                push(app, cpu, at(app, cpu.edx + cpu.eax + 0x55a4ec));
                push(app, cpu, cpu.edi);
                cpu.eax = at(app, ebp + 0x62);
                push(app, cpu, cpu.eax);
                push(app, cpu, cpu.edi);
                push(app, cpu, cpu.ebx);
                cpu.edx = cpu.ecx;
                if (!byAddress(app, cpu, 0x4db000)) return false;  //
                return true;
            }
            cpu.edx = at(app, ebp + 0x6a);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = cpu.edx * 4;
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab2);
            if (cpu.ax == 0xffff)
                return true;
            cpu.ebx = at(app, ebp + 0x66);
            cpu.edx = at(app, ebp + 0x62);
            cpu.eax = reg32(x86::sreg16(cpu.ax));
            if (!byAddress(app, cpu, 0x4d7990)) return false;  //
            return true;
        }
        // The area.
        if (at(app, kMenu3d) != 0)
        {
            cpu.eax = at(app, ebp + 0x52);
            cpu.edx = cpu.eax;
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.eax = reg32(sreg32(cpu.eax) >> 1);
            cpu.esi = at(app, ebp + 0x62);
            push(app, cpu, 0xffffffff);
            cpu.edx = at(app, ebp + 0x6a);
            put(app, ebp + 0x72, cpu.eax);
            cpu.esi = reg32(cpu.esi + cpu.eax);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.eax = at(app, 0x749a38);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            push(app, cpu, cpu.eax);
            cpu.eax = cpu.edx * 4;
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.edx = cpu.ecx;
            cpu.eax = reg32(cpu.eax << 6);
            cpu.edx = reg32(cpu.edx << 5);
            cpu.eax = reg32(cpu.eax + cpu.edx);
            push(app, cpu, at(app, cpu.eax + 0x55a508));
            push(app, cpu, at(app, cpu.eax + 0x55a504));
            push(app, cpu, at(app, cpu.eax + 0x55a500));
            push(app, cpu, at(app, cpu.eax + 0x55a4fc));
            push(app, cpu, at(app, cpu.eax + 0x55a4f8));
            push(app, cpu, at(app, cpu.eax + 0x55a4f4));
            cpu.ebx = at(app, ebp + 0x66);
            push(app, cpu, at(app, cpu.eax + 0x55a4f0));
            cpu.edi = reg32(cpu.edi + cpu.ebx);
            push(app, cpu, at(app, cpu.eax + 0x55a4ec));
            push(app, cpu, cpu.edi);
            cpu.ecx = at(app, ebp + 0x62);
            push(app, cpu, cpu.ecx);
            put(app, ebp + 0x6e, cpu.edx);
            push(app, cpu, cpu.edi);
            cpu.eax = at(app, ebp + 0x62);
            cpu.ecx = cpu.ebx;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.edx = cpu.ecx;
            if (!byAddress(app, cpu, 0x4db000)) return false;  //
            push(app, cpu, 0xffffffff);
            cpu.edx = at(app, 0x749a38);
            push(app, cpu, cpu.edx);
            cpu.edx = at(app, ebp + 0x6a);
            cpu.eax = at(app, ebp + 0x72);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.ebx = cpu.esi;
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.esi = reg32(cpu.esi + cpu.eax);
            cpu.eax = cpu.edx * 4;
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.ecx = at(app, ebp + 0x6e);
            cpu.eax = reg32(cpu.eax << 6);
            cpu.eax = reg32(cpu.eax + cpu.ecx);
            push(app, cpu, at(app, cpu.eax + 0x55a508));
            push(app, cpu, at(app, cpu.eax + 0x55a504));
            push(app, cpu, at(app, cpu.eax + 0x55a500));
            push(app, cpu, at(app, cpu.eax + 0x55a4fc));
            push(app, cpu, at(app, cpu.eax + 0x55a4f8));
            push(app, cpu, at(app, cpu.eax + 0x55a4f4));
            push(app, cpu, at(app, cpu.eax + 0x55a4f0));
            push(app, cpu, at(app, cpu.eax + 0x55a4ec));
            push(app, cpu, cpu.edi);
            push(app, cpu, cpu.esi);
            push(app, cpu, cpu.edi);
            cpu.ecx = at(app, ebp + 0x66);
            push(app, cpu, cpu.ebx);
            cpu.edx = cpu.ecx;
            cpu.eax = cpu.esi;
            if (!byAddress(app, cpu, 0x4db000)) return false;  //
            cpu.eax = at(app, ebp + 0x6a);
            cpu.edx = at(app, ebp + 0x6a);
            push(app, cpu, 0x98900010);
            cpu.ecx = at(app, ebp + 0x6a);
            cpu.esi = at(app, ebp + 0x6a);
            push(app, cpu, 0x98900010);
            cpu.edx = at(app, cpu.edx + 0xa2);
            cpu.ecx = at(app, cpu.ecx + 0x7c);
            cpu.esi = at(app, cpu.esi + 0x7e);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            push(app, cpu, 0x98900010);
            cpu.esi = reg32(cpu.esi + cpu.ecx);
            cpu.ecx = at(app, ebp + 0x6a);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.ecx = at(app, cpu.ecx + 0xa8);
            cpu.edi = cpu.edx + 4;
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.eax = at(app, cpu.eax + 0xa4);
            cpu.edx = reg32(cpu.edx + cpu.ecx);
            push(app, cpu, 0x98900010);
            cpu.edx = reg32(cpu.edx - 0x4);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            push(app, cpu, cpu.edx);
            cpu.eax = reg32(cpu.eax + 0x10);
            cpu.esi = reg32(cpu.esi - 0x3);
            push(app, cpu, cpu.eax);
            cpu.ebx = cpu.esi;
            push(app, cpu, cpu.edx);
            cpu.ecx = cpu.edi;
            push(app, cpu, cpu.esi);
            put(app, ebp + 0x56, cpu.edx);
            cpu.edx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0x98186a02);
            cpu.ebx = at(app, ebp + 0x6a);
            cpu.ecx = at(app, ebp + 0x6a);
            push(app, cpu, 0x98186a02);
            cpu.ebx = at(app, cpu.ebx + 0x84);
            cpu.ecx = at(app, cpu.ecx + 0x86);
            push(app, cpu, 0x98186a02);
            cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            push(app, cpu, 0x98186a02);
            cpu.ecx = reg32(cpu.ecx + cpu.ebx);
            cpu.ebx = at(app, ebp + 0x56);
            push(app, cpu, cpu.ebx);
            cpu.eax = cpu.esi;
            push(app, cpu, cpu.eax);
            push(app, cpu, cpu.ebx);
            cpu.esi = cpu.ecx - 3;
            cpu.edx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ecx = cpu.edi;
            cpu.ebx = cpu.esi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0x98900010);
            push(app, cpu, 0x98900010);
            push(app, cpu, 0x98900010);
            cpu.ecx = at(app, ebp + 0x56);
            push(app, cpu, 0x98900010);
            cpu.eax = cpu.esi;
            cpu.esi = at(app, ebp + 0x6a);
            push(app, cpu, cpu.ecx);
            cpu.esi = at(app, cpu.esi + 0x94);
            push(app, cpu, cpu.eax);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            push(app, cpu, cpu.ecx);
            cpu.esi = reg32(cpu.esi + 0x3);
            cpu.edx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.ecx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0x98186a02);
            push(app, cpu, 0x98186a02);
            push(app, cpu, 0x98186a02);
            cpu.ecx = at(app, ebp + 0x56);
            push(app, cpu, 0x98186a02);
            cpu.eax = cpu.esi;
            cpu.esi = at(app, ebp + 0x6a);
            push(app, cpu, cpu.ecx);
            cpu.esi = at(app, cpu.esi + 0x8c);
            push(app, cpu, cpu.eax);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            push(app, cpu, cpu.ecx);
            cpu.esi = reg32(cpu.esi + 0x3);
            cpu.edx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.ecx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0x98900010);
            cpu.edx = at(app, ebp + 0x6a);
            cpu.eax = at(app, ebp + 0x6a);
            push(app, cpu, 0x98900010);
            cpu.ecx = at(app, cpu.edx + 0xa4);
            cpu.edx = at(app, cpu.edx + 0xa6);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            push(app, cpu, 0x98900010);
            cpu.edx = reg32(cpu.edx + cpu.ecx);
            cpu.eax = at(app, cpu.eax + 0x8c);
            cpu.esi = cpu.edx - 0x10;
            push(app, cpu, 0x98900010);
            cpu.edx = at(app, ebp + 0x56);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            push(app, cpu, cpu.edx);
            cpu.eax = reg32(cpu.eax + 0x3);
            push(app, cpu, cpu.eax);
            push(app, cpu, cpu.edx);
            cpu.ecx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.edx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            return true;
        }
        if ((byte(app, kRenderFlags) & 2) != 0)
        {
            cpu.edx = at(app, ebp + 0x6a);
            cpu.edx = at(app, cpu.edx + 0x40);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = cpu.edx * 4;
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.eax = reg32(cpu.eax << 3);
            cpu.eax = reg32(cpu.eax + cpu.esi);
            cpu.cx = half(app, cpu.eax + 0x678ab2);
            if (cpu.cx != 0xffff)
            {
                cpu.ebx = at(app, ebp + 0x66);
                cpu.edx = at(app, ebp + 0x62);
                cpu.eax = reg32(x86::sreg16(cpu.cx));
                if (!byAddress(app, cpu, 0x4d7990)) return false;  //
            }
            cpu.eax = at(app, ebp + 0x6a);
            cpu.edx = at(app, ebp + 0x6a);
            cpu.ebx = at(app, ebp + 0x6a);
            cpu.ecx = at(app, ebp + 0x6a);
            push(app, cpu, 0xff900010);
            cpu.ebx = at(app, cpu.ebx + 0x7c);
            cpu.ecx = at(app, cpu.ecx + 0x7e);
            cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            push(app, cpu, 0xff900010);
            cpu.ecx = reg32(cpu.ecx + cpu.ebx);
            cpu.edx = at(app, cpu.edx + 0xa2);
            cpu.esi = cpu.ecx - 3;
            push(app, cpu, 0xff900010);
            cpu.ecx = at(app, ebp + 0x6a);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.ecx = at(app, cpu.ecx + 0xa8);
            cpu.edi = cpu.edx + 3;
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.eax = at(app, cpu.eax + 0xa4);
            cpu.edx = reg32(cpu.edx + cpu.ecx);
            push(app, cpu, 0xff900010);
            cpu.edx = reg32(cpu.edx - 0x4);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            push(app, cpu, cpu.edx);
            cpu.eax = reg32(cpu.eax + 0x10);
            push(app, cpu, cpu.eax);
            cpu.ebx = cpu.esi;
            push(app, cpu, cpu.edx);
            cpu.ecx = cpu.edi;
            push(app, cpu, cpu.esi);
            put(app, ebp + 0x5a, cpu.edx);
            cpu.edx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0xff186a02);
            cpu.ecx = at(app, ebp + 0x6a);
            cpu.eax = cpu.esi;
            push(app, cpu, 0xff186a02);
            cpu.esi = at(app, ebp + 0x6a);
            cpu.ecx = at(app, cpu.ecx + 0x86);
            push(app, cpu, 0xff186a02);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            cpu.esi = at(app, cpu.esi + 0x84);
            push(app, cpu, 0xff186a02);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            cpu.esi = reg32(cpu.esi + cpu.ecx);
            cpu.ecx = at(app, ebp + 0x5a);
            push(app, cpu, cpu.ecx);
            push(app, cpu, cpu.eax);
            push(app, cpu, cpu.ecx);
            cpu.esi = reg32(cpu.esi - 0x3);
            cpu.edx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.ecx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0xff900010);
            push(app, cpu, 0xff900010);
            push(app, cpu, 0xff900010);
            cpu.ecx = at(app, ebp + 0x5a);
            push(app, cpu, 0xff900010);
            cpu.eax = cpu.esi;
            cpu.esi = at(app, ebp + 0x6a);
            push(app, cpu, cpu.ecx);
            cpu.esi = at(app, cpu.esi + 0x94);
            push(app, cpu, cpu.eax);
            cpu.esi = reg32(sreg32(cpu.esi) >> 0x10);
            push(app, cpu, cpu.ecx);
            cpu.esi = reg32(cpu.esi + 0x3);
            cpu.edx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.ecx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            push(app, cpu, 0xff186a02);
            cpu.edx = at(app, ebp + 0x6a);
            push(app, cpu, 0xff186a02);
            cpu.edx = at(app, cpu.edx + 0x8c);
            push(app, cpu, 0xff186a02);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = cpu.esi;
            cpu.esi = cpu.edx + 3;
            push(app, cpu, 0xff186a02);
            cpu.edx = at(app, ebp + 0x5a);
            push(app, cpu, cpu.edx);
            push(app, cpu, cpu.eax);
            push(app, cpu, cpu.edx);
            cpu.ecx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.ebx = cpu.esi;
            cpu.edx = cpu.edi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            cpu.eax = at(app, ebp + 0x6a);
            push(app, cpu, 0xff900010);
            cpu.edx = at(app, ebp + 0x6a);
            cpu.ebx = at(app, ebp + 0x5a);
            push(app, cpu, 0xff900010);
            cpu.eax = at(app, cpu.eax + 0x8c);
            cpu.ecx = at(app, cpu.edx + 0xa4);
            push(app, cpu, 0xff900010);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
            cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
            push(app, cpu, 0xff900010);
            cpu.edx = at(app, cpu.edx + 0xa6);
            cpu.eax = reg32(cpu.eax + 0x3);
            push(app, cpu, cpu.ebx);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            push(app, cpu, cpu.eax);
            cpu.edx = reg32(cpu.edx + cpu.ecx);
            push(app, cpu, cpu.ebx);
            cpu.esi = cpu.edx - 0x11;
            cpu.ecx = cpu.edi;
            push(app, cpu, cpu.esi);
            cpu.edx = cpu.edi;
            cpu.ebx = cpu.esi;
            if (!byAddress(app, cpu, 0x4db380)) return false;  //
            return true;
        }
        cpu.edx = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.eax = reg32(cpu.eax << 3);
        cpu.eax = reg32(cpu.eax + cpu.esi);
        if (half(app, cpu.eax + 0x678ab2) == 0xffff || half(app, cpu.eax + 0x678ab0) == 0xffff)
            return true;
        cpu.ecx = ebp + 0x36;
        cpu.ebx = ebp + 0x22;
        cpu.edx = ebp + 0x26;
        cpu.eax = ebp + 0x32;
        if (!byAddress(app, cpu, 0x4beb80)) return false;  //
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.eax + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab0);
        cpu.edx = at(app, ebp + 0x6a);
        putHalf(app, ebp + 0x7e, x86::reg16(cpu.ax));
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x7e);
        cpu.eax = at(app, cpu.eax + 0x7c);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        cpu.edi = reg32(cpu.edi + 0x4);
        cpu.edx = cpu.eax - 3;
        cpu.ebx = at(app, kScreenHeight);
        cpu.eax = cpu.edi;
        cpu.eax = cpu.eax * cpu.ebx;
        cpu.ecx = at(app, ebp + 0x62);
        put(app, ebp + 0x42, cpu.edi);
        cpu.edx = reg32(cpu.edx - cpu.ecx);
        cpu.edx = cpu.edx * at(app, kScreenWidth);
        put(app, ebp + 0x6e, cpu.eax);
        cpu.edi = at(app, ebp + 0x66);
        cpu.eax = cpu.ebx;
        cpu.edi = reg32(cpu.edi - 0x2);
        cpu.eax = cpu.eax * cpu.edi;
        put(app, ebp + 0x76, cpu.edx);
        cpu.edx = at(app, kScreenWidth);
        put(app, ebp + 0x72, cpu.eax);
        cpu.eax = cpu.ecx;
        cpu.eax = cpu.eax * cpu.edx;
        cpu.fpu.push(loadDouble(app, 0x53ae98));
        cpu.fpu.push(integer(app, ebp + 0x6e));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
        cpu.fpu.push(loadDouble(app, 0x53aea0));
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(4) = cpu.fpu.mul(cpu.fpu.st(4), cpu.fpu.st(0));
        cpu.fpu.count -= 1;
        put(app, ebp + 0x72, cpu.eax);
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));
        cpu.fpu.count -= 1;
        exchange(cpu, 2);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x72);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ebx = at(app, ebp + 0x6e);
        cpu.ecx = at(app, ebp + 0x72);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.edx = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.eax = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        cpu.eax = at(app, ebp + 0x7c);
        cpu.ebx = at(app, ebp + 0x66);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        if (!byAddress(app, cpu, 0x4d7990)) return false;  //
        cpu.edx = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab2);
        cpu.edx = at(app, ebp + 0x6a);
        putHalf(app, ebp + 0x7e, x86::reg16(cpu.ax));
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x7c);
        cpu.eax = at(app, cpu.eax + 0x7e);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        cpu.edx = at(app, ebp + 0x6a);
        cpu.ecx = at(app, cpu.edx + 0x84);
        cpu.edx = at(app, cpu.edx + 0x86);
        cpu.ecx = reg32(sreg32(cpu.ecx) >> 0x10);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.edx = reg32(cpu.edx + cpu.ecx);
        cpu.eax = reg32(cpu.eax - 0x3);
        cpu.edx = reg32(cpu.edx + 0x3);
        cpu.edx = reg32(cpu.edx - cpu.eax);
        cpu.ecx = at(app, ebp + 0x42);
        cpu.ebx = at(app, kScreenHeight);
        cpu.ecx = cpu.ecx * cpu.ebx;
        put(app, ebp + 0x72, cpu.ecx);
        cpu.ecx = at(app, kScreenWidth);
        cpu.edx = cpu.edx * cpu.ecx;
        cpu.eax = cpu.eax * cpu.ecx;
        put(app, ebp + 0x76, cpu.edx);
        cpu.edx = cpu.ebx;
        cpu.edx = cpu.edx * cpu.edi;
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        put(app, ebp + 0x72, cpu.eax);
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        put(app, ebp + 0x72, cpu.edx);
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        exchange(cpu, 3);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ecx = at(app, ebp + 0x6e);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        storeInteger(app, cpu, ebp + 0x72);
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ebx = at(app, ebp + 0x72);
        cpu.eax = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.edx = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        cpu.eax = at(app, ebp + 0x7c);
        cpu.ebx = at(app, ebp + 0x66);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.ecx = at(app, ebp + 0x42);
        if (!byAddress(app, cpu, 0x4d7990)) return false;  //
        cpu.ebx = at(app, kScreenHeight);
        cpu.ecx = cpu.ecx * cpu.ebx;
        cpu.edx = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab0);
        cpu.edx = at(app, ebp + 0x6a);
        putHalf(app, ebp + 0x7e, x86::reg16(cpu.ax));
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x84);
        cpu.eax = at(app, cpu.eax + 0x86);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.eax = reg32(cpu.eax + cpu.edx);
        cpu.edx = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x94);
        put(app, ebp + 0x72, cpu.ecx);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = reg32(cpu.eax - 0x3);
        cpu.edx = reg32(cpu.edx + 0x3);
        cpu.ecx = at(app, kScreenWidth);
        cpu.edx = reg32(cpu.edx - cpu.eax);
        cpu.edx = cpu.edx * cpu.ecx;
        cpu.eax = cpu.eax * cpu.ecx;
        put(app, ebp + 0x76, cpu.edx);
        cpu.edx = cpu.ebx;
        cpu.edx = cpu.edx * cpu.edi;
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        put(app, ebp + 0x72, cpu.eax);
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        put(app, ebp + 0x72, cpu.edx);
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        exchange(cpu, 3);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ecx = at(app, ebp + 0x6e);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        storeInteger(app, cpu, ebp + 0x72);
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ebx = at(app, ebp + 0x72);
        cpu.eax = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.edx = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        cpu.eax = at(app, ebp + 0x7c);
        cpu.ebx = at(app, ebp + 0x66);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        if (!byAddress(app, cpu, 0x4d7990)) return false;  //
        cpu.ecx = at(app, ebp + 0x42);
        cpu.ebx = at(app, kScreenHeight);
        cpu.ecx = cpu.ecx * cpu.ebx;
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.eax + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab2);
        cpu.edx = at(app, ebp + 0x6a);
        putHalf(app, ebp + 0x7a, x86::reg16(cpu.ax));
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x8c);
        put(app, ebp + 0x72, cpu.ecx);
        cpu.eax = at(app, cpu.eax + 0x94);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.edx = reg32(cpu.edx + 0x3);
        cpu.eax = reg32(cpu.eax + 0x3);
        cpu.ecx = at(app, kScreenWidth);
        cpu.edx = reg32(cpu.edx - cpu.eax);
        cpu.edx = cpu.edx * cpu.ecx;
        cpu.eax = cpu.eax * cpu.ecx;
        put(app, ebp + 0x76, cpu.edx);
        cpu.edx = cpu.ebx;
        cpu.edx = cpu.edx * cpu.edi;
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        put(app, ebp + 0x72, cpu.eax);
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        put(app, ebp + 0x72, cpu.edx);
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        exchange(cpu, 3);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ecx = at(app, ebp + 0x6e);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        storeInteger(app, cpu, ebp + 0x72);
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ebx = at(app, ebp + 0x72);
        cpu.eax = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.edx = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        cpu.eax = at(app, ebp + 0x78);
        cpu.ebx = at(app, ebp + 0x66);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.ecx = at(app, ebp + 0x42);
        if (!byAddress(app, cpu, 0x4d7990)) return false;  //
        cpu.ebx = at(app, kScreenHeight);
        cpu.ecx = cpu.ecx * cpu.ebx;
        cpu.edx = at(app, ebp + 0x6a);
        cpu.edx = at(app, cpu.edx + 0x40);
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
        cpu.eax = cpu.edx * 4;
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.ax = half(app, cpu.esi + cpu.eax * 8 + 0x678ab0);
        putHalf(app, ebp + 0x7a, x86::reg16(cpu.ax));
        cpu.eax = at(app, ebp + 0x6a);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = at(app, cpu.eax + 0x8c);
        cpu.esi = at(app, ebp + 0x52);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        cpu.edx = reg32(cpu.edx + cpu.esi);
        cpu.eax = reg32(cpu.eax + 0x3);
        cpu.esi = at(app, kScreenWidth);
        cpu.edx = reg32(cpu.edx - cpu.eax);
        cpu.edx = cpu.edx * cpu.esi;
        cpu.eax = cpu.eax * cpu.esi;
        put(app, ebp + 0x72, cpu.edx);
        cpu.edx = cpu.ebx;
        cpu.edx = cpu.edx * cpu.edi;
        put(app, ebp + 0x76, cpu.ecx);
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        put(app, ebp + 0x76, cpu.eax);
        cpu.fpu.push(integer(app, ebp + 0x72));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53aea0));
        put(app, ebp + 0x76, cpu.edx);
        cpu.fpu.push(integer(app, ebp + 0x76));
        cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadDouble(app, 0x53ae98));
        exchange(cpu, 3);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ecx = at(app, ebp + 0x6e);
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        exchange(cpu, 1);
        storeInteger(app, cpu, ebp + 0x72);
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.ebx = at(app, ebp + 0x72);
        cpu.eax = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4dfd56)) return false;  //
        storeInteger(app, cpu, ebp + 0x6e);
        cpu.edx = at(app, ebp + 0x6e);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        cpu.eax = at(app, ebp + 0x78);
        cpu.ebx = at(app, ebp + 0x66);
        cpu.edx = at(app, ebp + 0x62);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        if (!byAddress(app, cpu, 0x4d7990)) return false;  //
        cpu.ecx = at(app, ebp + 0x36);
        cpu.ebx = at(app, ebp + 0x22);
        cpu.edx = at(app, ebp + 0x26);
        cpu.eax = at(app, ebp + 0x32);
        if (!byAddress(app, cpu, 0x4bebe0)) return false;  //
        return true;
    };
    for (;;)
    {
        cpu.eax = at(app, ebp + 0x5e);
        if (sreg32(cpu.eax) < 0)
            break;
        if (!drawPart())
            return;
        put(app, ebp + 0x5e, at(app, ebp + 0x5e) - 1);
    }
    // Its title.
    cpu.eax = at(app, ebp + 0x6a);
    if (at(app, cpu.eax + 0x60) != 0)
    {
        cpu.eax = at(app, cpu.eax + 0x1a);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        put(app, ebp + 0x62, cpu.eax);
        cpu.eax = at(app, ebp + 0x6a);
        cpu.eax = at(app, cpu.eax + 0x18);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        put(app, ebp + 0x66, cpu.eax);
        cpu.eax = at(app, ebp + 0x6a);
        cpu.eax = at(app, cpu.eax + 0x1c);
        cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        put(app, ebp + 0x52, cpu.eax);
        cpu.eax = at(app, ebp + 0x6a);
        cpu.ebx = at(app, cpu.eax + 0x1e);
        cpu.eax = at(app, ebp + 0x52);
        cpu.edx = cpu.eax;
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.eax = reg32(sreg32(cpu.eax) >> 1);
        cpu.ebx = reg32(sreg32(cpu.ebx) >> 0x10);
        cpu.esi = at(app, ebp + 0x62);
        cpu.edx = cpu.ebx;
        cpu.esi = reg32(cpu.esi + cpu.eax);
        cpu.eax = cpu.ebx;
        cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
        cpu.eax = reg32(cpu.eax - cpu.edx);
        cpu.eax = reg32(sreg32(cpu.eax) >> 1);
        cpu.ecx = at(app, ebp + 0x66);
        cpu.ecx = reg32(cpu.ecx + cpu.eax);
        cpu.eax = 0x12;
        if (!byAddress(app, cpu, 0x452100)) return;  //
        cpu.eax = at(app, ebp + 0x6a);
        cpu.al = byte(app, cpu.eax + 0x75);
        x86::reg8 alignment = 0;
        if (cpu.al <= 4)
        {
            cpu.eax &= 0xff;
            alignment = cpu.al;
        }
        if (alignment == 3)
        {
            cpu.eax = at(app, ebp + 0x66);
            cpu.edx = cpu.esi;
            cpu.eax = reg32(cpu.eax + cpu.ebx);
            cpu.ebx = 0x2;
        }
        else if (alignment == 2)
        {
            cpu.eax = at(app, ebp + 0x66);
            cpu.ecx = at(app, ebp + 0x3a);
            cpu.ebx = 0x2;
            cpu.edx = cpu.esi;
            cpu.eax = reg32(cpu.eax - cpu.ecx);
        }
        else if (alignment == 4)
        {
            cpu.edx = at(app, ebp + 0x6a);
            cpu.eax = at(app, ebp + 0x6a);
            cpu.ebx = 0;
            cpu.edx = at(app, cpu.edx + 0x62);
            cpu.eax = at(app, cpu.eax + 0x64);
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x10);
            cpu.eax = reg32(sreg32(cpu.eax) >> 0x10);
        }
        else
        {
            cpu.eax = at(app, ebp + 0x3a);
            cpu.edx = cpu.eax;
            cpu.edx = reg32(sreg32(cpu.edx) >> 0x1f);
            cpu.eax = reg32(cpu.eax - cpu.edx);
            cpu.eax = reg32(sreg32(cpu.eax) >> 1);
            cpu.ebx = 0x1;
            cpu.ecx = reg32(cpu.ecx - cpu.eax);
            cpu.edx = at(app, ebp + 0x62);
            cpu.eax = cpu.ecx;
            cpu.edx = reg32(cpu.edx - 0xa);
        }
        cpu.esi = at(app, ebp + 0x3e);
        push(app, cpu, cpu.esi);
        cpu.esi = at(app, ebp + 0x6a);
        cpu.ecx = 0x12;
        push(app, cpu, cpu.ebx);
        cpu.esi = at(app, cpu.esi + 0x60);
        cpu.ebx = cpu.eax;
        cpu.eax = cpu.esi;
        if (!byAddress(app, cpu, 0x452190)) return;  //
    }
    // Its values, as percentages.
    cpu.eax = at(app, ebp + 0x6a);
    cpu.eax = at(app, cpu.eax + 0x54);
    push(app, cpu, cpu.eax);
    push(app, cpu, 0x3c23d70a);
    if (!byAddress(app, cpu, 0x4693c0)) return;  //
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x53aea8));
    cpu.fpu.push(0.0);
    exchange(cpu, 1);
    storeFloat(app, ebp + 0x4a, cpu.fpu.pop());
    comparePop(cpu, loadFloat(app, ebp + 0x4a));
    cpu.fpu.push(loadFloat(app, ebp + 0x4a));
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, belowOrEqual(cpu) ? 0x53aeb0 : 0x53aeac));
    storeFloat(app, ebp + 0x4a, cpu.fpu.pop());
    cpu.eax = at(app, ebp + 0x6a);
    cpu.eax = at(app, cpu.eax + 0x58);
    push(app, cpu, cpu.eax);
    push(app, cpu, 0x3c23d70a);
    if (!byAddress(app, cpu, 0x4693c0)) return;  //
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, 0x53aea8));
    cpu.fpu.push(0.0);
    exchange(cpu, 1);
    storeFloat(app, ebp + 0x4e, cpu.fpu.pop());
    comparePop(cpu, loadFloat(app, ebp + 0x4e));
    cpu.fpu.push(loadFloat(app, ebp + 0x4e));
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, belowOrEqual(cpu) ? 0x53aeb0 : 0x53aeac));
    storeFloat(app, ebp + 0x4e, cpu.fpu.pop());
    cpu.fpu.push(loadFloat(app, ebp + 0x4a));
    push(app, cpu, 0x25);
    if (!byAddress(app, cpu, 0x4dfd56)) return;  //
    storeInteger(app, cpu, ebp + 0x6e);
    cpu.edi = at(app, ebp + 0x6e);
    cpu.fpu.push(loadFloat(app, ebp + 0x4e));
    push(app, cpu, cpu.edi);
    if (!byAddress(app, cpu, 0x4dfd56)) return;  //
    push(app, cpu, 0x25);
    storeInteger(app, cpu, ebp + 0x6e);
    cpu.eax = at(app, ebp + 0x6e);
    push(app, cpu, cpu.eax);
    push(app, cpu, 0x53ae84);
    cpu.eax = ebp - 0x1e;
    push(app, cpu, cpu.eax);
    cpu.edx = at(app, ebp + 0x3e);
    if (!byAddress(app, cpu, 0x4df690)) return;  //
    cpu.esp = reg32(cpu.esp + 0x18);
    cpu.ecx = at(app, ebp + 0x52);
    cpu.ebx = at(app, ebp + 0x66);
    push(app, cpu, cpu.edx);
    cpu.eax = ebp - 0x1e;
    cpu.edx = at(app, ebp + 0x62);
    push(app, cpu, 0x0);
    cpu.edx = reg32(cpu.edx + cpu.ecx);
    cpu.ecx = 0x12;
    cpu.edx = reg32(cpu.edx + 0xa);
    if (!byAddress(app, cpu, 0x452190)) return;  //
    cpu.eax = 0;
    cpu.esp = ebp + 0x82;
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.esi = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}




}  // namespace frontend
}  // namespace nfs3hp
