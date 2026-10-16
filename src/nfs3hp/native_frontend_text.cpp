#include "native_guest.h"

#include <iterator>
#include <utility>

/* The menus' text: a line of the language's text by its number -- past the
 * language's own lines, a display mode's, a car's or a controller's name --
 * the checks of a player's name and of a line typed in, and the font a text
 * is measured and drawn in.  disassemble_nfs3hp.py binds each address to the
 * function of that name here (FRONTEND_NATIVES), and the generated code
 * calls it by name; the menus' decompiled screens call them by address.
 *
 * Written as their code is: each push and pop to the guest's stack, each call
 * with the return address's slot, the registers as the code leaves them --
 * every one kept but eax, but where noted; the x87's stack pushed and popped
 * a value at a time.  The cars' functions the names come from, the 2D
 * screens' text and the quads the characters are handed on as stay the
 * game's code, called by address.  tools/game_checks holds each against its
 * generated code. */
namespace nfs3hp
{
namespace watcom
{
void CHP(win32::WinApplication* app, x86::CPU& cpu);
}

namespace frontend
{

namespace
{

using guest::at;
using guest::byte;
using guest::put;
using x86::reg32;

constexpr reg32 kLanguageTexts = 0x563a80;  // the language's lines: offsets from this block's start, then the text
constexpr reg32 kLanguageLines = 0x7a7;     // how many lines it has; numbers past them are names
constexpr reg32 kNoText = 0x549430;         // ""
// Display modes (sub_448400): 0x114 bytes each, the name at 0x14.
constexpr reg32 kDisplayModes = 0x661220;
constexpr reg32 kModeBytes = 0x114;
constexpr reg32 kModeName = 0x14;
// The cars' names (still the game's code): whether a number is a car's, whether
// a car is a police car, a car's name.
constexpr reg32 kCarKnown = 0x439cc0, kCarIsPolice = 0x4396b0, kCarName = 0x439250;
constexpr reg32 kPoliceCarText = 0x1e3, kCivilianCarText = 0x1e4;
// Controllers: how many there are, 0x88 bytes each from 0x6fc970, a name at 4
// unless its byte is 0; the menu's rows of them, whether shown and their
// colour.
constexpr reg32 kControllerCount = 0x6fd204;
constexpr reg32 kControllers = 0x6fc970;
constexpr reg32 kControllerBytes = 0x88;
constexpr reg32 kControllerRowShown = 0x555668;  // int16 each
constexpr reg32 kControllerRowColour = 0x555688;
constexpr reg32 kControllerColour = 0xff649dfd;
constexpr reg32 kUnnamedControllerText = 0x54, kNoControllerText = 0x27;
constexpr reg32 kNameLength = 10;  // a player's name: 1 to 10 characters

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

void putHalf(win32::WinApplication* app, reg32 address, x86::reg16 value)
{
    app->getMemory<x86::reg16>(address) = value;
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

void storeFloat(win32::WinApplication* app, reg32 address, const x86::Float& value)
{
    app->getMemory<float>(address) = float(value);
}

/* fild of a dword, of a word. */
x86::Float integer(win32::WinApplication* app, reg32 address)
{
    return x86::Float(x86::sreg32(at(app, address)));
}

x86::Float halfInteger(win32::WinApplication* app, reg32 address)
{
    return x86::Float(x86::sreg16(app->getMemory<x86::reg16>(address)));
}

/* fistp: st(0) as the control word rounds it, popped. */
void storeInteger(win32::WinApplication* app, x86::CPU& cpu, reg32 address)
{
    put(app, address, reg32(cpu.fpu.toInteger<x86::sreg32>(cpu.fpu.st(0))));
    cpu.fpu.count -= 1;
}

void exchange(x86::CPU& cpu, int i)
{
    std::swap(cpu.fpu.st(0), cpu.fpu.st(i));
}

/* push ebp, mov ebp, esp after the registers named, and sub esp, `locals`;
 * leave it the other way round. */
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

/* repne scasb for the 0 at es:edi from ecx -1, not and dec: the string's
 * length in ecx, edi past its 0. */
void inlineLength(win32::WinApplication* app, x86::CPU& cpu)
{
    cpu.ecx = 0xffffffff;
    cpu.eax = 0;
    while (cpu.ecx != 0)
    {
        const x86::reg8 b = byte(app, cpu.ees + cpu.edi);
        cpu.edi += cpu.flags.df ? reg32(-1) : 1;
        --cpu.ecx;
        if (b == 0)
            break;
    }
    cpu.ecx = ~cpu.ecx - 1;
}

}  // namespace

/* 0x448400: display mode eax - 0x7a8's name. */
void displayModeName(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.eax = (cpu.eax - 0x7a8) * kModeBytes + kDisplayModes + kModeName;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

void languageText(win32::WinApplication* app, x86::CPU& cpu);

/* 0x43d9f0: controller eax's name -- "none" past the controllers there are,
 * a line of the language's for one without a name of its own -- its row of
 * the menu shown, in its colour. */
void controllerName(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    auto done = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.esp += 4;
    };
    if (x86::sreg32(cpu.eax) >= x86::sreg32(at(app, kControllerCount)))
    {
        cpu.ecx = 0;
        putHalf(app, kControllerRowShown + cpu.eax * 2, x86::reg16(cpu.ecx));
        cpu.eax = kNoControllerText;
        if (!direct(app, cpu, languageText))
            return;
        return done();
    }
    cpu.eax = cpu.edx * kControllerBytes;
    if (byte(app, cpu.eax + kControllers + 4) != 0)
        cpu.eax += kControllers + 4;
    else
    {
        cpu.eax = kUnnamedControllerText;
        if (!direct(app, cpu, languageText))
            return;
    }
    putHalf(app, kControllerRowShown + cpu.edx * 2, 1);
    put(app, kControllerRowColour + cpu.edx * 4, kControllerColour);
    done();
}

/* 0x4d17b0: the text of a number past the language's lines: a display
 * mode's name (0x7a8 to 0x7bc), a car's (0x7bd to 0x7ee: its name, or "police
 * car" or "car" for one the game knows only so), a controller's (0x855 to
 * 0x865), else "". */
void specialText(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    auto done = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.esp += 4;
    };
    const x86::sreg32 id = x86::sreg32(cpu.eax);
    if (id >= 0x7a8 && id <= 0x7bc)
    {
        if (!direct(app, cpu, displayModeName))
            return;
        return done();
    }
    if (id >= 0x7bd && id <= 0x7ee)
    {
        cpu.edx = cpu.eax - 0x7bd;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarKnown))
            return;
        if (cpu.eax != 0)
        {
            cpu.eax = cpu.edx;
            if (!byAddress(app, cpu, kCarIsPolice))
                return;
            cpu.eax = cpu.eax != 0 ? kPoliceCarText : kCivilianCarText;
            if (!direct(app, cpu, languageText))
                return;
            return done();
        }
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, kCarName))
            return;
        return done();
    }
    if (!(id >= 0x7ef && id <= 0x821) && id >= 0x855 && id <= 0x865)
    {
        cpu.eax -= 0x855;
        if (!direct(app, cpu, controllerName))
            return;
        return done();
    }
    cpu.eax = kNoText;
    done();
}

/* 0x4d1850: line eax of the language's text, or a name past them. */
void languageText(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    if (x86::sreg32(cpu.eax) >= x86::sreg32(kLanguageLines))
    {
        if (!direct(app, cpu, specialText))
            return;
    }
    else
    {
        cpu.edx = cpu.eax * 4;
        cpu.eax = at(app, kLanguageTexts);
        cpu.eax += at(app, cpu.edx + cpu.eax);
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4721f0: whether the name at eax will do for a player's: 1 to 10
 * characters.  0 for none. */
void nameValid(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    if (cpu.eax != 0)
    {
        cpu.edi = cpu.eax;
        inlineLength(app, cpu);
        bool valid = false;
        if (cpu.ecx >= 1)
        {
            cpu.edi = cpu.edx;
            inlineLength(app, cpu);
            valid = cpu.ecx <= kNameLength;
        }
        cpu.eax = valid ? 1 : 0;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edi = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* ---- The menus' font: a text measured and drawn a character at a time,
 * each character a quad of the font's texture.  [0x840184] is the font, two
 * of them; [0x84018c] how big it is drawn; a character's metrics are bytes
 * from 0x83f4e0 on, 0xe0 characters a font from the space. ---- */
namespace
{

constexpr reg32 kInRace = 0x559234;          // the menus are a race's pause screens: the 3D card draws them
constexpr reg32 kFont = 0x664650;            // the font of the 2D screens' text (sub_4da4a0)
constexpr reg32 kWidthScale = 0x5395f0;      // float 640: a text's width on a 640 wide screen ...
constexpr reg32 kScreenWidth = 0x7cdac8;     // ... from the screen's own
constexpr reg32 kTextColour = 0x561b34;
constexpr reg32 kMeasuring = 0x561b3c;       // nonzero: the text measured, not drawn
constexpr reg32 kTextFont = 0x840184;
constexpr reg32 kTextScale = 0x84018c;       // float
constexpr reg32 kMinusOne = 0x540bc0;        // double -1
constexpr reg32 kFontTextures = 0x83f6a8;    // 44 bytes a font: its texture's width and height, words
constexpr reg32 kFontQuads = 0x7f74c0;       // 0x24010 bytes a font: the quads its characters are drawn as
constexpr reg32 kCharacters = 0xe0;          // a font's characters, from the space
// A character's bytes.
constexpr reg32 kAdvance = 0x83f4e0;         // signed: how far the next one goes
constexpr reg32 kTextureY = 0x83f700;
constexpr reg32 kTextureX = 0x83f8c0;
constexpr reg32 kGlyphWidth = 0x83fc40;
constexpr reg32 kGlyphHeight = 0x83fe00;     // less one
constexpr reg32 kOffsetX = 0x83ffc0;         // signed
constexpr reg32 kOffsetY = 0x83fa80;         // signed
constexpr reg32 kDrawQuads = 0x49bd30;       // the font's quads, four of them, handed on to be drawn
constexpr reg32 kDrawText2D = 0x4da4a0;      // a text on a 2D screen, its width back

reg32 fontQuads(win32::WinApplication* app, x86::CPU& cpu)
{
    // mov edx, [0x840184]; lea eax, [edx*8]; add eax, edx; shl eax, 0xa;
    // add eax, edx; shl eax, 4; add eax, 0x7f74c0
    cpu.edx = at(app, kTextFont);
    cpu.eax = cpu.edx * 8 + cpu.edx;
    cpu.eax = (cpu.eax << 10) + cpu.edx;
    return (cpu.eax << 4) + kFontQuads;
}

}  // namespace

void measureText(win32::WinApplication* app, x86::CPU& cpu);
void textWidthWithOverhang(win32::WinApplication* app, x86::CPU& cpu);

/* 0x49bcd0: the next quad of the list at eax, from its end: its number to
 * [ebx], its address to [edx]; the list one shorter. */
void takeQuad(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ecx = cpu.edx;
    cpu.edx = at(app, cpu.eax + 4);
    cpu.eax += 0x10;
    put(app, cpu.ebx, cpu.edx);
    cpu.ebx = cpu.edx;
    --cpu.edx;
    cpu.ebx <<= 5;
    put(app, cpu.eax - 0xc, cpu.edx);
    cpu.eax += cpu.ebx;
    put(app, cpu.ecx, cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x4d06f0: character eax of the fonts at x [esp+4] (a float), y [esp+8]:
 * its quad -- its texture's square from edx, ebx, [esp+0xc] wide and
 * [esp+0x10] high, in colour [esp+0x14] -- unless it is a space, or
 * [esp+0x18] says the text is only measured, or it would be no pixel wide or
 * high.  x moves to the quad's left edge.  How far the next one goes onto the
 * x87's stack. */
void drawCharacter(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x5c);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.ecx = cpu.edx;
    cpu.edx = cpu.eax;
    cpu.edi = kCharacters;
    cpu.edx = reg32(x86::sreg32(cpu.edx) >> 31);
    {
        const std::int64_t dividend = std::int64_t(x86::sreg32(cpu.eax));
        cpu.eax = reg32(x86::sreg32(dividend / x86::sreg32(cpu.edi)));
        cpu.edx = reg32(x86::sreg32(dividend % x86::sreg32(cpu.edi)));
    }
    auto advance = [&] {
        cpu.ax = x86::reg16(x86::sreg16(x86::sreg8(byte(app, cpu.esi + kAdvance))));
        put(app, ebp - 4, cpu.eax);
        cpu.fpu.push(cpu.fpu.mul(halfInteger(app, ebp - 4), loadFloat(app, kTextScale)));
        leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x18);
    };
    if (cpu.edx == 0 || at(app, ebp + 0x28) != 0)
        return advance();
    cpu.edx = at(app, kTextFont);
    cpu.eax = cpu.edx * 4 - cpu.edx;
    cpu.eax = (cpu.eax << 2) - cpu.edx;
    cpu.edx = cpu.eax * 4;
    cpu.eax = 0;
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + kFontTextures);
    put(app, ebp - 0x10, cpu.eax);
    cpu.fpu.push(integer(app, ebp - 0x10));                        // fild: the texture's width
    cpu.fpu.push(1.0);                                             // fld1
    cpu.fpu.st(1) = cpu.fpu.div(cpu.fpu.st(0), cpu.fpu.st(1));     // fdivrp st(1)
    cpu.fpu.count -= 1;
    cpu.eax = 0;
    cpu.ax = app->getMemory<x86::reg16>(cpu.edx + kFontTextures + 2);
    put(app, ebp - 0x10, cpu.eax);
    cpu.eax = at(app, ebp + 0x18);
    put(app, ebp - 8, cpu.eax);
    cpu.eax = at(app, ebp + 0x1c);
    put(app, ebp - 0xc, cpu.eax);
    cpu.fpu.push(integer(app, ebp - 0xc));                         // fild: the width
    cpu.eax = at(app, ebp + 0x20);
    storeFloat(app, ebp - 0x1c, cpu.fpu.st(0));
    put(app, ebp - 0xc, cpu.eax);
    cpu.fpu.push(loadFloat(app, kTextScale));
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));     // fmul st(1)
    cpu.fpu.push(integer(app, ebp - 0xc));                         // fild: the height
    storeFloat(app, ebp - 0x24, cpu.fpu.st(0));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(2));     // fmul st(2)
    cpu.ax = x86::reg16(x86::sreg16(x86::sreg8(byte(app, cpu.esi + kOffsetX))));
    cpu.fpu.push(integer(app, ebp - 0x10));                        // fild: the texture's height
    put(app, ebp - 4, cpu.eax);
    cpu.fpu.push(1.0);
    cpu.fpu.push(halfInteger(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(5));     // fmul st(5)
    exchange(cpu, 1);
    cpu.fpu.st(2) = cpu.fpu.div(cpu.fpu.st(0), cpu.fpu.st(2));     // fdivrp st(2)
    cpu.fpu.count -= 1;
    cpu.ax = x86::reg16(x86::sreg16(x86::sreg8(byte(app, cpu.esi + kOffsetY))));
    cpu.fpu.push(integer(app, ebp - 8));                           // fild: y
    put(app, ebp - 4, cpu.eax);
    storeFloat(app, ebp - 0x14, cpu.fpu.pop());
    cpu.fpu.push(halfInteger(app, ebp - 4));
    cpu.fpu.st(5) = cpu.fpu.mul(cpu.fpu.st(5), cpu.fpu.st(0));     // fmulp st(5)
    cpu.fpu.count -= 1;
    put(app, ebp - 0xc, cpu.ecx);
    put(app, ebp - 8, cpu.ebx);
    cpu.fpu.push(integer(app, ebp - 0xc));
    storeFloat(app, ebp - 0x20, cpu.fpu.pop());
    cpu.fpu.push(integer(app, ebp - 8));
    storeFloat(app, ebp - 0x18, cpu.fpu.pop());
    exchange(cpu, 3);
    storeFloat(app, ebp - 0x34, cpu.fpu.pop());
    exchange(cpu, 2);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp + 0x14));
    exchange(cpu, 1);
    storeFloat(app, ebp - 0x38, cpu.fpu.pop());
    storeFloat(app, ebp + 0x14, cpu.fpu.st(0));
    cpu.fpu.push(cpu.fpu.st(0));
    if (!direct(app, cpu, watcom::CHP))
        return;
    exchange(cpu, 3);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x14));
    exchange(cpu, 3);
    storeInteger(app, cpu, ebp - 0x10);
    exchange(cpu, 2);
    storeFloat(app, ebp - 0x14, cpu.fpu.pop());
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x34));
    cpu.eax = at(app, ebp - 0x10);
    exchange(cpu, 2);
    storeFloat(app, ebp - 0x3c, cpu.fpu.pop());
    exchange(cpu, 1);
    storeFloat(app, ebp - 0x30, cpu.fpu.st(0));
    if (!direct(app, cpu, watcom::CHP))
        return;
    storeInteger(app, cpu, ebp - 0x10);
    cpu.ecx = at(app, ebp - 0x10);
    storeFloat(app, ebp - 0x2c, cpu.fpu.pop());
    if (cpu.eax == cpu.ecx)
        return advance();
    cpu.fpu.push(loadFloat(app, ebp - 0x14));
    cpu.fpu.push(cpu.fpu.st(0));
    if (!direct(app, cpu, watcom::CHP))
        return;
    storeInteger(app, cpu, ebp - 0x10);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x38));
    cpu.eax = at(app, ebp - 0x10);
    storeFloat(app, ebp - 0x28, cpu.fpu.st(0));
    if (!direct(app, cpu, watcom::CHP))
        return;
    storeInteger(app, cpu, ebp - 0x10);
    if (cpu.eax == at(app, ebp - 0x10))
        return advance();
    // Four quads from the font's list, their numbers to [ebp-0x5c] on and
    // their addresses to [ebp-0x4c] on.
    for (reg32 i = 0; i < 4; ++i)
    {
        cpu.eax = fontQuads(app, cpu);
        cpu.ebx = ebp - 0x5c + 4 * i;
        cpu.edx = ebp - 0x4c + 4 * i;
        if (!direct(app, cpu, takeQuad))
            return;
    }
    const auto corner = [&](reg32 i) { return at(app, ebp - 0x4c + 4 * i); };
    // The colour, the corners' places and their texture's.
    cpu.eax = corner(3);
    cpu.edx = at(app, ebp + 0x24);
    put(app, cpu.eax + 0x10, cpu.edx);
    cpu.eax = corner(3);
    cpu.edx = at(app, cpu.eax + 0x10);
    cpu.eax = corner(2);
    put(app, cpu.eax + 0x10, cpu.edx);
    cpu.eax = corner(2);
    cpu.edx = at(app, cpu.eax + 0x10);
    cpu.eax = corner(1);
    put(app, cpu.eax + 0x10, cpu.edx);
    cpu.eax = corner(1);
    cpu.edx = corner(0);
    cpu.eax = at(app, cpu.eax + 0x10);
    put(app, cpu.edx + 0x10, cpu.eax);
    cpu.edx = corner(3);
    cpu.eax = at(app, ebp + 0x14);
    put(app, cpu.edx, cpu.eax);
    cpu.eax = corner(3);
    cpu.fpu.push(loadFloat(app, cpu.eax));
    cpu.eax = corner(0);
    storeFloat(app, cpu.eax, cpu.fpu.pop());
    cpu.edx = corner(2);
    cpu.eax = at(app, ebp - 0x30);
    put(app, cpu.edx, cpu.eax);
    cpu.eax = corner(2);
    cpu.fpu.push(loadFloat(app, cpu.eax));
    cpu.eax = corner(1);
    storeFloat(app, cpu.eax, cpu.fpu.pop());
    cpu.edx = corner(1);
    cpu.eax = at(app, ebp - 0x14);
    put(app, cpu.edx + 4, cpu.eax);
    cpu.eax = corner(1);
    cpu.fpu.push(loadFloat(app, cpu.eax + 4));
    cpu.eax = corner(0);
    storeFloat(app, cpu.eax + 4, cpu.fpu.pop());
    cpu.edx = corner(3);
    cpu.eax = at(app, ebp - 0x28);
    put(app, cpu.edx + 4, cpu.eax);
    cpu.eax = corner(3);
    cpu.fpu.push(loadFloat(app, ebp - 0x20));
    cpu.fpu.push(cpu.fpu.st(0));
    cpu.fpu.push(loadFloat(app, cpu.eax + 4));
    cpu.eax = corner(2);
    exchange(cpu, 1);
    cpu.fpu.push(loadFloat(app, ebp - 0x3c));
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), cpu.fpu.st(1));     // fmul st(1)
    exchange(cpu, 2);
    storeFloat(app, cpu.eax + 4, cpu.fpu.pop());
    cpu.eax = corner(3);
    exchange(cpu, 1);
    storeFloat(app, cpu.eax + 0x18, cpu.fpu.pop());
    cpu.eax = corner(3);
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x1c));
    cpu.fpu.push(loadFloat(app, cpu.eax + 0x18));
    cpu.eax = corner(0);
    exchange(cpu, 1);
    cpu.fpu.st(2) = cpu.fpu.mul(cpu.fpu.st(2), cpu.fpu.st(0));     // fmulp st(2)
    cpu.fpu.count -= 1;
    storeFloat(app, cpu.eax + 0x18, cpu.fpu.pop());
    cpu.eax = corner(2);
    storeFloat(app, cpu.eax + 0x18, cpu.fpu.pop());
    cpu.eax = corner(2);
    cpu.fpu.push(loadFloat(app, ebp - 0x18));
    cpu.fpu.push(loadFloat(app, cpu.eax + 0x18));
    cpu.eax = corner(1);
    exchange(cpu, 1);
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp - 0x2c));
    exchange(cpu, 1);
    storeFloat(app, cpu.eax + 0x18, cpu.fpu.pop());
    cpu.eax = corner(1);
    storeFloat(app, cpu.eax + 0x1c, cpu.fpu.pop());
    cpu.eax = corner(1);
    cpu.fpu.push(loadFloat(app, cpu.eax + 0x1c));
    cpu.eax = corner(0);
    storeFloat(app, cpu.eax + 0x1c, cpu.fpu.pop());
    cpu.fpu.push(loadFloat(app, ebp - 0x18));
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0x24));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, ebp - 0x2c));
    cpu.eax = corner(3);
    storeFloat(app, cpu.eax + 0x1c, cpu.fpu.pop());
    cpu.eax = corner(3);
    cpu.fpu.push(loadFloat(app, cpu.eax + 0x1c));
    cpu.eax = corner(2);
    const reg32 to = cpu.eax;
    cpu.eax = fontQuads(app, cpu);
    storeFloat(app, to + 0x1c, cpu.fpu.pop());
    cpu.edi = at(app, ebp - 0x50);
    cpu.ecx = at(app, ebp - 0x54);
    cpu.ebx = at(app, ebp - 0x58);
    push(app, cpu, cpu.edi);
    cpu.edx = at(app, ebp - 0x5c);
    if (!byAddress(app, cpu, kDrawQuads))
        return;
    advance();
}

/* 0x4d1000: the text at eax at x edx, y ebx in colour [0x561b34], opaque --
 * its last character no further right than the screen's edge -- or only
 * measured, [0x561b3c] set.  How wide onto the x87's stack. */
void drawText(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi}, 0x18);
    const reg32 ebp = cpu.ebp;
    cpu.ecx = cpu.eax;
    cpu.esi = cpu.ebx;
    put(app, ebp - 4, cpu.edx);
    cpu.edi = at(app, kTextColour);
    cpu.fpu.push(integer(app, ebp - 4));
    cpu.edx = at(app, kMeasuring);
    storeFloat(app, ebp - 8, cpu.fpu.pop());
    cpu.eax = at(app, ebp - 8);
    cpu.edi |= 0xff000000;
    put(app, ebp - 0x10, cpu.eax);
    if (cpu.edx == 0)
    {
        cpu.eax = cpu.ecx;
        if (!direct(app, cpu, textWidthWithOverhang))
            return;
        cpu.fpu.push(loadFloat(app, ebp - 8));
        exchange(cpu, 1);
        storeFloat(app, ebp - 0xc, cpu.fpu.pop());
        cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 0xc));
        cpu.fpu.push(integer(app, kScreenWidth));
        storeFloat(app, ebp - 0x14, cpu.fpu.pop());
        cpu.fpu.compare(cpu.fpu.st(0), loadFloat(app, ebp - 0x14));    // fcomp, fnstsw ax, sahf
        cpu.ax = cpu.fpu.status.word;
        cpu.flags.lo = 0x02 | (cpu.ah & 0xd7);
        cpu.fpu.count -= 1;
        if (!cpu.flags.cf)
        {
            // Past the edge: moved back to end a pixel short of it.
            cpu.fpu.push(loadFloat(app, ebp - 0x14));
            cpu.fpu.st(0) = cpu.fpu.sub(cpu.fpu.st(0), loadFloat(app, ebp - 0xc));
            cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), x86::Float(app->getMemory<double>(kMinusOne)));
            storeFloat(app, ebp - 8, cpu.fpu.pop());
            cpu.eax = at(app, ebp - 8);
            put(app, ebp - 0x10, cpu.eax);
        }
    }
    cpu.eax = at(app, kTextFont);
    cpu.eax <<= 5;
    cpu.edx = cpu.eax;
    cpu.eax <<= 3;
    cpu.eax -= cpu.edx;
    put(app, ebp - 0x18, cpu.eax);
    cpu.eax = 0;
    for (;;)
    {
        cpu.al = byte(app, cpu.ecx);
        if (cpu.eax == 0)
            break;
        cpu.ebx = at(app, ebp - 0x18);
        cpu.eax -= 0x20;
        cpu.edx = at(app, kMeasuring);
        cpu.eax += cpu.ebx;
        push(app, cpu, cpu.edx);
        cpu.edx = byte(app, cpu.eax + kGlyphHeight);
        push(app, cpu, cpu.edi);
        ++cpu.edx;
        push(app, cpu, cpu.edx);
        cpu.edx = byte(app, cpu.eax + kGlyphWidth);
        push(app, cpu, cpu.edx);
        cpu.ebx = 0;
        push(app, cpu, cpu.esi);
        cpu.bl = byte(app, cpu.eax + kTextureY);
        cpu.edx = 0;
        push(app, cpu, at(app, ebp - 8));
        cpu.dl = byte(app, cpu.eax + kTextureX);
        ++cpu.ecx;
        if (!direct(app, cpu, drawCharacter))
            return;
        cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 8));
        cpu.eax = 0;
        storeFloat(app, ebp - 8, cpu.fpu.pop());
    }
    cpu.fpu.push(loadFloat(app, ebp - 8));
    cpu.fpu.st(0) = cpu.fpu.sub(cpu.fpu.st(0), loadFloat(app, ebp - 0x10));
    leave(app, cpu, {&cpu.ecx, &cpu.esi, &cpu.edi});
}

/* 0x4d1430: how wide the text at eax is, in whole pixels, onto the x87's
 * stack. */
void measureText(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx}, 8);
    const reg32 ebp = cpu.ebp;
    cpu.edx = 1;
    cpu.ecx = at(app, kMeasuring);
    cpu.ebx = 0;
    put(app, kMeasuring, cpu.edx);
    cpu.edx = 0;
    if (!direct(app, cpu, drawText) || !direct(app, cpu, watcom::CHP))
        return;
    storeInteger(app, cpu, ebp - 8);
    cpu.eax = at(app, ebp - 8);
    put(app, ebp - 4, cpu.eax);
    put(app, kMeasuring, cpu.ecx);
    cpu.fpu.push(integer(app, ebp - 4));
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.edx});
}

/* 0x4d1480: the text at eax measured, and its last character's own width
 * past where it goes on to, onto the x87's stack. */
void textWidthWithOverhang(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ecx, &cpu.edx, &cpu.edi}, 8);
    const reg32 ebp = cpu.ebp;
    cpu.edx = cpu.eax;
    if (!direct(app, cpu, measureText))
        return;
    cpu.edi = cpu.edx;
    storeFloat(app, ebp - 8, cpu.fpu.pop());
    inlineLength(app, cpu);
    cpu.eax = cpu.edx + cpu.ecx;
    cpu.al = byte(app, cpu.eax - 1);
    cpu.dl = cpu.al;
    cpu.al = byte(app, kTextFont);
    cpu.ah = 0xe0;
    cpu.ax = x86::reg16(cpu.al * cpu.ah);                          // mul ah
    cpu.dl -= 0x20;
    cpu.al += cpu.dl;
    cpu.eax &= 0xff;
    cpu.ecx = byte(app, cpu.eax + kGlyphWidth);
    cpu.edx = at(app, cpu.eax + kOffsetX - 3);
    cpu.eax = at(app, cpu.eax + kAdvance - 3);
    cpu.edx = reg32(x86::sreg32(cpu.edx) >> 24);
    cpu.eax = reg32(x86::sreg32(cpu.eax) >> 24);
    cpu.edx += cpu.ecx;
    cpu.edx -= cpu.eax;
    put(app, ebp - 4, cpu.edx);
    cpu.fpu.push(integer(app, ebp - 4));
    cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, kTextScale));
    cpu.fpu.st(0) = cpu.fpu.add(cpu.fpu.st(0), loadFloat(app, ebp - 8));
    leave(app, cpu, {&cpu.ecx, &cpu.edx, &cpu.edi});
}

/* 0x452100: the font of the 2D screens' text. */
void selectFont(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    put(app, kFont, cpu.eax);
    cpu.ebp = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x452020: how wide the text at eax is in font edx: on a 640 wide screen
 * when the 3D card draws the menus, else as the 2D screens draw it; 5 for
 * none. */
void textWidth(win32::WinApplication* app, x86::CPU& cpu)
{
    enter(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi}, 4);
    const reg32 ebp = cpu.ebp;
    cpu.esi = cpu.eax;
    cpu.eax = cpu.edx;
    if (cpu.esi == 0)
        put(app, ebp - 4, 5);
    else
    {
        if (!direct(app, cpu, selectFont))
            return;
        if (at(app, kInRace) != 0)
        {
            cpu.eax = cpu.esi;
            if (!direct(app, cpu, measureText))
                return;
            cpu.fpu.st(0) = cpu.fpu.mul(cpu.fpu.st(0), loadFloat(app, kWidthScale));
            cpu.fpu.push(integer(app, kScreenWidth));
            cpu.fpu.st(1) = cpu.fpu.div(cpu.fpu.st(1), cpu.fpu.st(0));     // fdivp st(1)
            cpu.fpu.count -= 1;
            if (!direct(app, cpu, watcom::CHP))
                return;
            storeInteger(app, cpu, ebp - 4);
        }
        else
        {
            cpu.ecx = 1;
            cpu.eax = cpu.esi;
            cpu.ebx = 0;
            cpu.edx = 0;
            if (!byAddress(app, cpu, kDrawText2D))
                return;
            put(app, ebp - 4, cpu.eax);
        }
    }
    cpu.eax = at(app, ebp - 4);
    leave(app, cpu, {&cpu.ebx, &cpu.ecx, &cpu.esi});
}

/* ---- What may be typed in a dialog's line: the checks of sub_443860's
 * modes. ---- */
namespace
{

constexpr reg32 kCharacterKinds = 0x564ef0;  // the runtime's table of each byte's kind, from -1
constexpr reg32 kLanguage = 0x6fbb4c;
constexpr reg32 kLanguageChecks = 0x558c80;  // 0x14 bytes a language: its checks of a line, by mode
constexpr reg32 kLanguageCheckBytes = 0x14;
constexpr reg32 kShortName = 8;

/* The language's check of a line at `offset` of its row, through its
 * pointer; 1 when it has none. */
void languageCheck(win32::WinApplication* app, x86::CPU& cpu, reg32 offset)
{
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.edx = cpu.eax;
    cpu.ecx = at(app, kLanguage);
    cpu.eax = (cpu.ecx * 4 + cpu.ecx) << 2;
    if (at(app, cpu.eax + kLanguageChecks + offset) == 0)
        cpu.al = 1;
    else
    {
        cpu.ecx = cpu.eax;
        cpu.eax = cpu.edx;
        if (!byAddress(app, cpu, at(app, cpu.ecx + kLanguageChecks + offset)))
            return;
    }
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.ecx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace

/* 0x443630: whether the character in al may be in a short name: a letter or
 * a digit, '_' or '-'.  ah is left al + 1. */
void shortNameCharacter(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.ah = cpu.al;
    cpu.edx = 0;
    ++cpu.ah;
    cpu.dl = cpu.ah;
    if (byte(app, cpu.edx + kCharacterKinds) & 0xe0)
        cpu.al = 1;
    else
        cpu.al = cpu.al == '_' || cpu.al == '-' ? 1 : 0;
    cpu.ebp = pop(app, cpu);
    cpu.edx = pop(app, cpu);
    cpu.esp += 4;
}

/* 0x443660: whether the text at eax is a short name: 0 to 8 of those. */
void shortNameValid(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ecx);
    push(app, cpu, cpu.edx);
    push(app, cpu, cpu.edi);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    auto done = [&] {
        cpu.ebp = pop(app, cpu);
        cpu.edi = pop(app, cpu);
        cpu.edx = pop(app, cpu);
        cpu.ecx = pop(app, cpu);
        cpu.ebx = pop(app, cpu);
        cpu.esp += 4;
    };
    cpu.edx = cpu.eax;
    if (cpu.eax == 0)
    {
        cpu.al = 0;
        return done();
    }
    cpu.edi = cpu.eax;
    inlineLength(app, cpu);
    cpu.ebx = cpu.ecx;
    if (x86::sreg32(cpu.ecx) < 0 || x86::sreg32(cpu.ecx) > x86::sreg32(kShortName))
    {
        cpu.al = 0;
        return done();
    }
    for (cpu.ecx = 0; x86::sreg32(cpu.ecx) < x86::sreg32(cpu.ebx); ++cpu.ecx)
    {
        cpu.eax = cpu.edx + cpu.ecx;
        cpu.al = byte(app, cpu.eax);
        cpu.eax &= 0xff;
        if (!direct(app, cpu, shortNameCharacter))
            return;
        if (cpu.al == 0)
            return done();
    }
    cpu.al = 1;
    done();
}

/* 0x443700, 0x443780: whether the language takes the line at eax as a
 * player's name (mode 1), as a file's (mode 2). */
void languageNameValid(win32::WinApplication* app, x86::CPU& cpu)
{
    languageCheck(app, cpu, 0);
}

void languageFileNameValid(win32::WinApplication* app, x86::CPU& cpu)
{
    languageCheck(app, cpu, 8);
}

/* 0x443860: whether the line at eax will do in mode edx: 0 a short name, 1
 * and 2 the language's checks; never an empty one, nor in another mode. */
void lineAllowed(win32::WinApplication* app, x86::CPU& cpu)
{
    push(app, cpu, cpu.ebx);
    push(app, cpu, cpu.ebp);
    cpu.ebp = cpu.esp;
    cpu.bl = 0;
    if (cpu.eax == 0 || byte(app, cpu.eax) == 0)
        cpu.al = 0;
    else
    {
        void (*check)(win32::WinApplication*, x86::CPU&) = cpu.edx == 0   ? shortNameValid
                                                             : cpu.edx == 1 ? languageNameValid
                                                             : cpu.edx == 2 ? languageFileNameValid
                                                                            : nullptr;
        if (check != nullptr)
        {
            if (!direct(app, cpu, check))
                return;
            cpu.bl = cpu.al;
        }
        cpu.al = cpu.bl;
    }
    cpu.ebp = pop(app, cpu);
    cpu.ebx = pop(app, cpu);
    cpu.esp += 4;
}

}  // namespace frontend
}  // namespace nfs3hp
