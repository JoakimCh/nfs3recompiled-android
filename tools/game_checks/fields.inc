/* game_checks.cpp's parts for the menus' widgets that hold a value rewritten
 * (port::fields, src/nfs3hp/port_fields.cpp), included in each table with the
 * macro naming the part.  The world is the menus' drawing's
 * (frontend_draw.inc's makeFeDrawWorld): the port's text, 2D drawing and
 * shapes these call run for real on both sides.  Over it the cases' own: the
 * car records the car's record stand-in walks to (0x554f70, a list), the
 * widget's record, its texts, lines and the words its pointers point at. */
#if defined(FIELDS_WINDOWS)
// {from, to}, -- what the functions write, compared
// The sliders' parts' art sizes (0x678aa0 on), the car records (0x1f4000).
{0x678000, 0x679000},
#elif defined(FIELDS_GAME_FUNCTIONS)
// {address, "name", convention, registers, words, clobbers, through, deref, effect},
// What they call of the menu loop's and the dialogs' (MENU_NATIVES, which have
// no generated code here): whether an item is on the screen shown now (its
// type logged), a screen's item by its name (a block, its byte 0xb3 written),
// the dialog's question.
{0x44a660, "an item shown now", kWatcom, 2, 0, kEax, -1, 0, kSucceed},
{0x442a40, "a screen's item found", kWatcom, 2, 0, kEax, 1, 4, kBlock},
{0x4446d0, "a question put", kStdcall, 4, 4, kEax, -1, 0, kNothing},
#elif defined(FIELDS_POINTERS)
// {slot, "name", convention, registers, words, clobbers, through, deref, effect},
// A field's function, told of a change (eax the item); a list's, told of a
// line chosen (eax the item, edx the caller's, ebx the line).
{0xfff700, "a field's function", kWatcom, 1, 0, kEax, -1, 0, kNothing},
{0xfff704, "a list's function", kWatcom, 3, 0, kEax, -1, 0, kNothing},
#elif defined(FIELDS_PROMISES)
// {"port::fields::name", watcom, result, arguments, fpu, heap, liveOnly},
// eax, esi, edi, ebp, esp; the x87's stack, its live registers and its words.
{"port::fields::carColourCount", true, true, 0, true, kNoHeap, true},
{"port::fields::carCustomColour", true, true, 0, true, kNoHeap, true},
{"port::fields::carColour", true, true, 0, true, kNoHeap, true},
{"port::fields::carColourName", true, true, 0, true, kNoHeap, true},
{"port::fields::setCarColour", true, true, 0, true, kNoHeap, true},
{"port::fields::carColourRgb", true, true, 0, true, kNoHeap, true},
{"port::fields::setCarCustomColour", true, true, 0, true, kNoHeap, true},
{"port::fields::carText", true, true, 0, true, kNoHeap, true},
{"port::fields::saveCarColours", true, true, 0, true, kNoHeap, true},
{"port::fields::wheelFromCarColour", true, true, 0, true, kNoHeap, true},
{"port::fields::wheelForPlayer", true, true, 0, true, kNoHeap, true},
{"port::fields::refreshCustomColours", true, true, 0, true, kNoHeap, true},
{"port::fields::setCursorColour", true, true, 0, true, kNoHeap, true},
{"port::fields::drawFieldText", true, true, 0, true, kNoHeap, true},
{"port::fields::drawFieldLine", true, true, 0, true, kNoHeap, true},
{"port::fields::drawSpacedText", true, true, 0, true, kNoHeap, true},
{"port::fields::drawCursorText3d", true, true, 0, true, kNoHeap, true},
{"port::fields::drawCursor", true, true, 0, true, kNoHeap, true},
{"port::fields::drawCursorText", true, true, 0, true, kNoHeap, true},
{"port::fields::colourListWidth", true, true, 0, true, kNoHeap, true},
{"port::fields::colourListRefresh", true, true, 0, true, kNoHeap, true},
{"port::fields::drawColourLine", true, true, 0, true, kNoHeap, true},
{"port::fields::drawColourList", true, true, 0, true, kNoHeap, true},
{"port::fields::colourListShown", true, true, 0, true, kNoHeap, true},
{"port::fields::pointAtColour", true, true, 0, true, kNoHeap, true},
{"port::fields::openColourList", true, true, 0, true, kNoHeap, true},
{"port::fields::closeColourList", true, true, 0, true, kNoHeap, true},
{"port::fields::chooseColour", true, true, 0, true, kNoHeap, true},
{"port::fields::colourListKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutColourList", true, true, 0, true, kNoHeap, true},
{"port::fields::colourListHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::drawFrameAt", true, true, 0, true, kNoHeap, true},
{"port::fields::editKey", true, true, 0, true, kNoHeap, true},
{"port::fields::drawIntField", true, true, 0, true, kNoHeap, true},
{"port::fields::intRangeMessage", true, true, 0, true, kNoHeap, true},
{"port::fields::intFieldKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutIntField", true, true, 0, true, kNoHeap, true},
{"port::fields::intFieldShown", true, true, 0, true, kNoHeap, true},
{"port::fields::intFieldHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::bindIntField", true, true, 0, true, kNoHeap, true},
{"port::fields::drawStringField", true, true, 0, true, kNoHeap, true},
{"port::fields::stringFieldKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutStringField", true, true, 0, true, kNoHeap, true},
{"port::fields::stringFieldShown", true, true, 0, true, kNoHeap, true},
{"port::fields::stringFieldHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::drawCharField", true, true, 0, true, kNoHeap, true},
{"port::fields::charRangeMessage", true, true, 0, true, kNoHeap, true},
{"port::fields::charFieldKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutCharField", true, true, 0, true, kNoHeap, true},
{"port::fields::charFieldShown", true, true, 0, true, kNoHeap, true},
{"port::fields::charFieldHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::bindCharField", true, true, 0, true, kNoHeap, true},
{"port::fields::drawFloatField", true, true, 0, true, kNoHeap, true},
{"port::fields::floatRangeMessage", true, true, 0, true, kNoHeap, true},
{"port::fields::floatFieldKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutFloatField", true, true, 0, true, kNoHeap, true},
{"port::fields::floatFieldShown", true, true, 0, true, kNoHeap, true},
{"port::fields::floatFieldHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::bindFloatField", true, true, 0, true, kNoHeap, true},
{"port::fields::drawFixedField", true, true, 0, true, kNoHeap, true},
{"port::fields::fixedRangeMessage", true, true, 0, true, kNoHeap, true},
{"port::fields::fixedFieldKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutFixedField", true, true, 0, true, kNoHeap, true},
{"port::fields::fixedFieldShown", true, true, 0, true, kNoHeap, true},
{"port::fields::fixedFieldHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::bindFixedField", true, true, 0, true, kNoHeap, true},
{"port::fields::drawListBox", true, true, 0, true, kNoHeap, true},
{"port::fields::pointAtListBoxLine", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxDown", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxUp", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxPartAt", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxArrowAt", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxKey", true, true, 0, true, kNoHeap, true},
{"port::fields::layoutListBox", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxShown", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::listBoxChooseAt", true, true, 0, true, kNoHeap, true},
{"port::fields::drawShadedTriangle", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderPartSizes", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderPartUnderPointer", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderThumbPlace", true, true, 0, true, kNoHeap, true},
{"port::fields::snapToStep", true, true, 0, true, kNoHeap, true},
{"port::fields::setSliderValue", true, true, 0, true, kNoHeap, true},
{"port::fields::setSliderStep", true, true, 0, true, kNoHeap, true},
{"port::fields::dragSliderTo", true, true, 0, true, kNoHeap, true},
{"port::fields::drawSlider", true, true, 0, true, kNoHeap, true},
{"port::fields::trackSlider", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderKey", true, true, 0, true, kNoHeap, true},
{"port::fields::placeSliderParts", true, true, 0, true, kNoHeap, true},
{"port::fields::setUpSlider", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderBox", true, true, 0, true, kNoHeap, true},
{"port::fields::twoAxisThumbPlace", true, true, 0, true, kNoHeap, true},
{"port::fields::setTwoAxisValue", true, true, 0, true, kNoHeap, true},
{"port::fields::setTwoAxisStep", true, true, 0, true, kNoHeap, true},
{"port::fields::dragTwoAxisTo", true, true, 0, true, kNoHeap, true},
{"port::fields::drawTwoAxis", true, true, 0, true, kNoHeap, true},
{"port::fields::trackTwoAxis", true, true, 0, true, kNoHeap, true},
{"port::fields::twoAxisKey", true, true, 0, true, kNoHeap, true},
{"port::fields::placeTwoAxisParts", true, true, 0, true, kNoHeap, true},
{"port::fields::setUpTwoAxis", true, true, 0, true, kNoHeap, true},
{"port::fields::twoAxisBox", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderSetValue", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderDraw", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderWidgetKey", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderWidgetLayout", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderWidgetHidden", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderWidgetShown", true, true, 0, true, kNoHeap, true},
{"port::fields::sliderShape", true, true, 0, true, kNoHeap, true},
#elif defined(FIELDS_ARGUMENTS)
/* Where the fields' cases keep their own: the widget's record, the words its
 * pointers point at, texts, a list's lines and their texts, a field's value,
 * an edstring's buffer, the car records' text offsets; the car records. */
constexpr x86::reg32 kFdItem = 0x61e000, kFdWords = 0x61e100, kFdTexts = 0x61e200, kFdLines = 0x61e400;
constexpr x86::reg32 kFdLineTexts = 0x61e500, kFdValue = 0x61e900, kFdBuffer = 0x61ea00, kFdOffsets = 0x61eb00;
constexpr x86::reg32 kFdCars = 0x1f4000;

/* A text of digits as a field takes them: a sign, digits, a dot, now and
 * then a letter; `most` long at most. */
void aNumberText(CheckApp& g, x86::reg32 at, x86::reg32 most)
{
    x86::reg32 n = 0;
    const x86::reg32 length = below(most + 1);
    if (chance(20) && n < length)
        g.getMemory<x86::reg8>(at + n++) = '-';
    while (n < length)
        g.getMemory<x86::reg8>(at + n++) = x86::reg8(chance(85) ? '0' + below(10) : chance(50) ? '.' : 'a' + below(26));
    g.getMemory<x86::reg8>(at + n) = 0;
}

/* The car records, a list from 0x554f70 (as the car's record stand-in walks
 * it): their texts, chosen colours, colours, custom ones; the players' cars,
 * whether the custom colours are kept. */
void makeFieldsCars(CheckApp& g)
{
    for (x86::reg32 car = 0; car < 3; ++car)
    {
        const x86::reg32 rec = kFdCars + 0x400 * car;
        for (x86::reg32 at = rec; at < rec + 0x400; at += 4)
            g.word(at) = random32();
        g.word(rec) = car < 2 ? rec + 0x400 : 0;
        g.getMemory<x86::reg16>(rec + 4) = x86::reg16(chance(90) ? 0x20 + below(0x20) : below(0x40));
        g.word(rec + 8) = kFdTexts;
        g.word(rec + 0xc) = kFdOffsets;
        const x86::reg32 last = chance(90) ? below(12) : random32() % 40;
        g.word(rec + 0x334) = last;
        // The chosen colours: a colour of the car's (one past them leaves the bytes
        // read unset, which the code's frames and the port's hold otherwise).
        g.word(rec + 0x32c) = below(last + 1);
        g.word(rec + 0x330) = below(last + 1);
    }
    for (x86::reg32 i = 0; i < 0x40; ++i)
        g.word(kFdOffsets + 4 * i) = 0x40 * below(8);
    g.word(0x554f70) = kFdCars;
    g.word(0x6fd2bc) = chance(90) ? below(3) : below(5);
    g.word(0x6fd328) = chance(90) ? below(3) : below(5);
    g.word(0x6fd3a0) = chance(50) ? 0 : 1;
}

/* The world the fields' cases share: the menus' drawing, the 2D screens'
 * font, the fields' blanks the code copies (zeros, as nfs3.exe has them),
 * texts, the car records, the menus' state bits, the dialog's text. */
void makeFieldsWorld(CheckApp& g, x86::CPU& cpu)
{
    makeFeDrawWorld(g, cpu);
    makeDraw2dFont(g);
    for (x86::reg32 at = 0x4576e0; at < 0x457ae0; at += 4)
        g.word(at) = 0;
    for (x86::reg32 i = 0; i < 8; ++i)
        aMenuText(g, kFdTexts + 0x40 * i, 0x30);
    for (x86::reg32 at = kFdWords; at < kFdWords + 0x100; at += 4)
        g.word(at) = random32();
    makeFieldsCars(g);
    g.getMemory<x86::reg8>(0x55eb2d) = x86::reg8(random32());
    g.getMemory<x86::reg8>(0x55eb2f) = x86::reg8(random32());
    g.word(0x678a40) = chance(95) ? 8 + below(20) : 1 + below(100);
    g.word(0x561b38) = random32();
    g.word(0x559438) = random32();
    // The 3D card's fonts' lists with room for a text (text.inc), sscanf's float (the runtime's slot).
    saneQuadLists(g);
    for (x86::reg32 font = 0; font < 2; ++font)
        g.word(0x7f74c0 + 0x24010 * font + 4) = 0x180 + below(0x80);
    g.word(0x56ac68) = standInFor(0x56ac68);
}

/* A widget's record at kFdItem: random words, its place and box on the
 * screen, the pointer near the box now and then. */
void makeFieldsItem(CheckApp& g)
{
    for (x86::reg32 at = kFdItem; at < kFdItem + 0x100; at += 4)
        g.word(at) = random32();
    g.getMemory<x86::reg16>(kFdItem + 6) = x86::reg16(aScreenX());
    g.getMemory<x86::reg16>(kFdItem + 8) = x86::reg16(aScreenY());
    g.getMemory<x86::reg16>(kFdItem + 0x1a) = x86::reg16(aScreenY());
    g.getMemory<x86::reg16>(kFdItem + 0x1c) = x86::reg16(aScreenX());
    g.getMemory<x86::reg16>(kFdItem + 0x1e) = x86::reg16(chance(90) ? below(300) : random32());
    g.getMemory<x86::reg16>(kFdItem + 0x20) = x86::reg16(chance(90) ? below(200) : random32());
    g.getMemory<x86::reg8>(kFdItem + 4) = x86::reg8(random32());
    g.getMemory<x86::reg8>(kFdItem + 5) = x86::reg8(random32());
    if (chance(60))
    {
        g.word(0x55e5e4) = x86::reg32(g.getMemory<x86::sreg16>(kFdItem + 0x1c)) + below(320);
        g.word(0x55e5e8) = x86::reg32(g.getMemory<x86::sreg16>(kFdItem + 0x1a)) + below(220);
    }
    else
    {
        g.word(0x55e5e4) = aScreenX();
        g.word(0x55e5e8) = aScreenY();
    }
    g.word(kFdItem + 0x3c) = chance(20) ? 0 : kFdTexts + 0x40 * below(8);
}

/* A key: Enter, Escape, Backspace, Delete, the arrows, digits, a dot, a
 * minus, a letter, any. */
x86::reg32 aFieldsKey()
{
    static const x86::reg32 keys[] = {0xd, 0x1b, 8, 0x5300, 0x4800, 0x5000, 0x4b00, 0x4d00, '.', '-', 'a', ' '};
    const x86::reg32 key = chance(30) ? '0' + below(10) : chance(85) ? keys[below(12)] : random32() & 0xffff;
    return (random32() & 0xffff0000) | key;
}

/* An edint's, edchar's, edfloat's, edfixed's or edstring's record. */
void makeField(CheckApp& g, const std::string& kind)
{
    makeFieldsItem(g);
    const x86::reg32 item = kFdItem;
    g.getMemory<x86::reg16>(item + 0x40) = x86::reg16(chance(45) ? 0 : chance(90) ? 1 : below(4));
    if (kind == "String")
    {
        g.getMemory<x86::reg16>(item + 0x42) = x86::reg16(chance(90) ? below(0x1e) : random32());
        g.word(item + 0x44) = chance(20) ? 0 : kFdTexts + 0x40 * below(8);
        g.word(item + 0x48) = chance(10) ? 0 : kFdBuffer;
        aMenuText(g, kFdBuffer, 0x18);
        g.getMemory<x86::reg16>(item + 0x4c) = x86::reg16(1 + below(0x20));
        g.word(item + 0x50) = chance(50) ? 0 : standInFor(0xfff700);
        return;
    }
    const bool isChar = kind == "Char", isFloat = kind == "Float", isFixed = kind == "Fixed";
    g.getMemory<x86::reg8>(item + 0x42) = x86::reg8(chance(60) ? 1 : below(3));
    const x86::reg32 value = isChar ? 0x50 : 0x58, cursor = isChar ? 0x54 : 0x5c;
    const x86::reg32 typed = isChar ? 0x58 : isFloat || isFixed ? 0x64 : 0x60;
    const x86::reg32 size = isChar ? 5 : isFloat || isFixed ? 0xf : 0xc;
    const x86::reg32 changed = isChar ? 0x60 : isFloat || isFixed ? 0x74 : 0x6c;
    if (isChar)
    {
        g.getMemory<x86::reg8>(item + 0x43) = x86::reg8(below(100));
        g.getMemory<x86::reg8>(item + 0x44) = x86::reg8(100 + below(156));
        g.getMemory<x86::reg8>(item + 0x45) = x86::reg8(below(3));
        g.word(item + 0x48) = chance(30) ? 0 : kFdTexts + 0x40 * below(8);
        g.word(item + 0x4c) = chance(30) ? 0 : kFdTexts + 0x40 * below(8);
    }
    else
    {
        if (isFloat)
        {
            g.word(item + 0x44) = feFloat(float(x86::sreg32(below(2000)) - 1000) / 10.0f);
            g.word(item + 0x48) = feFloat(float(below(2000)) / 10.0f);
        }
        else
        {
            g.word(item + 0x44) = (below(2000) - 1000) << 12;
            g.word(item + 0x48) = below(2000) << 12;
        }
        if (chance(10))
            g.word(item + 0x44 + 4 * below(2)) = random32();
        g.getMemory<x86::reg8>(item + 0x4c) = x86::reg8(below(3));
        g.word(item + 0x50) = chance(30) ? 0 : kFdTexts + 0x40 * below(8);
        g.word(item + 0x54) = chance(30) ? 0 : kFdTexts + 0x40 * below(8);
        if (isFloat || isFixed)
            g.word(item + 0x60) = chance(80) ? below(8) : random32();
    }
    g.word(item + value) = chance(15) ? 0 : kFdValue;
    g.word(kFdValue) = isFloat ? feFloat(float(x86::sreg32(below(4000)) - 2000) / 7.0f)
                       : isFixed ? x86::reg32(x86::sreg32(below(0x2000000)) - 0x1000000)
                                 : chance(80) ? below(300) : random32();
    if (isFloat && chance(5))
        g.word(kFdValue) = random32();
    g.word(item + cursor) = chance(90) ? below(size + 2) : random32();
    aNumberText(g, item + typed, size);
    g.word(item + changed) = chance(50) ? 0 : standInFor(0xfff700);
}

/* A list's record: rows, its chosen and first line, its lines (texts, now and
 * then marked), its function. */
void makeListBox(CheckApp& g)
{
    makeFieldsItem(g);
    const x86::reg32 item = kFdItem;
    const x86::reg32 count = chance(90) ? below(16) : below(32);
    g.getMemory<x86::reg16>(item + 0x3c) = x86::reg16(chance(10) ? 0 : 100 + below(300));
    g.getMemory<x86::reg16>(item + 0x3e) = x86::reg16(chance(20) ? 1 : chance(10) ? 0 : 2 + below(8));
    g.getMemory<x86::reg16>(item + 0x40) = x86::reg16(chance(90) ? below(count + 2) : random32());
    g.getMemory<x86::reg16>(item + 0x42) = x86::reg16(chance(90) ? below(count + 1) : random32() % 40);
    g.word(item + 0x44) = chance(40) ? 0 : standInFor(0xfff704);
    g.word(item + 0x48) = kFdLines;
    g.getMemory<x86::reg16>(item + 0x4c) = x86::reg16(count);
    for (x86::reg32 i = 0; i < 32; ++i)
    {
        const x86::reg32 text = kFdLineTexts + 0x20 * (i % 32);
        aMenuText(g, text, 0x18);
        if (chance(20))
            g.getMemory<x86::reg8>(text) |= 0x80;
        g.word(kFdLines + 8 * i) = text;
        g.word(kFdLines + 8 * i + 4) = random32();
    }
    g.getMemory<x86::reg8>(item + 4) = x86::reg8(chance(80) ? random32() & ~4u : random32());
}

/* The car's colours' record: its player, its colours, its car's variable, its
 * shapes, whether it is open, the car it shows. */
void makeColourList(CheckApp& g)
{
    makeFieldsItem(g);
    const x86::reg32 item = kFdItem;
    g.getMemory<x86::reg16>(item + 0x40) = x86::reg16(chance(90) ? below(2) : random32());
    g.word(item + 0x44) = below(14);
    g.word(item + 0x48) = below(14);
    g.word(item + 0x4c) = chance(90) ? below(14) : random32() % 30;
    g.word(item + 0x54) = chance(10) ? 0 : chance(50) ? 0x6fd2bc : 0x6fd328;
    g.getMemory<x86::reg16>(item + 0x58) = x86::reg16(chance(50) ? 0 : chance(90) ? 1 : random32());
    g.getMemory<x86::reg16>(item + 0x5c) = x86::reg16(below(12));
    g.getMemory<x86::reg16>(item + 0x5e) = x86::reg16(below(12));
    const x86::reg32 car = g.word(item + 0x54);
    g.word(item + 0x60) = chance(60) && car != 0 ? g.word(car) : below(4);
}

bool makeFieldsArguments(CheckApp& g, const std::string& name, x86::CPU& cpu, x86::reg32* stack)
{
    // The sliders: the cases of those that were frontend::'s as frontend_draw.inc
    // makes them, the others on its world and slider (a two-axis one for the
    // two-axis functions); over it what they need more: the 3D card's fonts'
    // lists with room for a text, GetKeyState's slot, the menus' art's shapes
    // their parts' art is named by (so that each is found among them, or none
    // known: where the search runs out, the game's strncmp leaves ebx
    // otherwise than the port's, which EA's stand-ins log).
    static const char* const sliders[] = {
        "sliderPartSizes", "sliderPartUnderPointer", "sliderThumbPlace", "snapToStep", "setSliderValue",
        "setSliderStep", "dragSliderTo", "drawSlider", "trackSlider", "sliderKey", "placeSliderParts", "setUpSlider",
        "sliderBox", "twoAxisThumbPlace", "setTwoAxisValue", "setTwoAxisStep", "dragTwoAxisTo", "drawTwoAxis",
        "trackTwoAxis", "twoAxisKey", "placeTwoAxisParts", "setUpTwoAxis", "twoAxisBox", "sliderSetValue",
        "sliderDraw", "sliderWidgetKey", "sliderWidgetLayout", "sliderWidgetHidden", "sliderWidgetShown",
        "sliderShape"};
    if (std::find_if(std::begin(sliders), std::end(sliders), [&](const char* n) { return name == n; })
        != std::end(sliders))
    {
        static const char* const before[] = {"sliderPartUnderPointer", "sliderThumbPlace", "snapToStep",
                                             "setSliderValue", "dragSliderTo", "drawSlider", "trackSlider",
                                             "twoAxisThumbPlace", "setTwoAxisValue", "dragTwoAxisTo", "drawTwoAxis",
                                             "trackTwoAxis"};
        const bool shaped = name == "sliderPartSizes" || name == "sliderWidgetShown" || name == "sliderShape";
        if (shaped)
            makeShapesWorld(g, cpu, stack);
        const bool twoAxis = name.find("TwoAxis") != std::string::npos || name.find("twoAxis") != std::string::npos;
        if (std::find_if(std::begin(before), std::end(before), [&](const char* n) { return name == n; })
            != std::end(before))
            makeFeDrawArguments(g, name, cpu, stack);
        else
            makeFeDrawArguments(g, twoAxis ? "drawTwoAxis" : "drawSlider", cpu, stack);
        const x86::reg32 item = 0x61d000;  // frontend_draw.inc's kFeSlider
        saneQuadLists(g);
        for (x86::reg32 font = 0; font < 2; ++font)
            g.word(0x7f74c0 + 0x24010 * font + 4) = 0x180 + below(0x80);
        g.word(0x534738) = standInFor(0x534738);
        g.word(0x66296c) = chance(30) ? 9 : below(20);
        g.getMemory<x86::reg16>(item + 0x40) = x86::reg16(below(10));
        if (shaped)
        {
            // The art's shapes known: every part's art's name of every kind.
            g.word(0x8b762c) = below(0x300);
            static const x86::reg32 artFormats[] = {0x78, 0x7b, 0x7d, 0x7e};
            for (x86::reg32 block = 0; block < 8; ++block)
            {
                g.word(kBlocks + 0x400 * block) = artFormats[below(4)];
                g.word(kBlocks + 0x400 * block + 4) = (1 + below(15)) | (1 + below(15)) << 16;
            }
            x86::reg32 known = 0;
            for (const x86::reg32 table : {0x55af0cu, 0x55af9cu})
                for (x86::reg32 at = table; at < table + 0x18 * 6; at += 4)
                    if (g.word(at) != 0 && known < 100)
                        std::memcpy(&g.getMemory<char>(0x8b48c0 + 0x14 * known++ + 0x10), &g.getMemory<char>(g.word(at)), 4);
            g.word(0x8b7628) = known;
            // sliderShape's own: the shape entered at cpu.esp, EA's search of the art
            // (shapes.inc's formats where shapeToPixels reads them) when none is known.
            const x86::reg32 entry = name == "sliderShape" ? cpu.esp
                                     : name == "sliderPartSizes" ? cpu.esp - 0x18 - 4 - 4
                                                                 : cpu.esp - 8 - 4 - 0x18 - 4 - 4;
            plantAboutFormats(g, entry - 0x14 - 4 - 0x14 - 0x34 - 8);
            if (name == "sliderShape")
            {
                cpu.eax = g.word(0x55af0c + 4 * below(0x18 * 6 / 4));
                if (cpu.eax == 0 || chance(30))
                {
                    const x86::reg32 text = kFdTexts;
                    for (x86::reg32 c = 0; c < 4; ++c)
                        g.getMemory<x86::reg8>(text + c) = x86::reg8('a' + below(3));
                    g.getMemory<x86::reg8>(text + 4) = 0;
                    cpu.eax = text;
                    g.word(0x8b7628) = 0;
                }
            }
        }
        if (name == "sliderKey" || name == "twoAxisKey" || name == "sliderWidgetKey")
        {
            static const x86::reg32 keys[] = {0x4b00, 0x4d00, 0xd, 0x4800, 0x1b};
            const x86::reg32 key = (random32() & 0xffff0000) | (chance(90) ? keys[below(5)] : random32() & 0xffff);
            cpu.ebx = key;
            cpu.ecx = key;
        }
        else if (name == "setSliderStep" || name == "setTwoAxisStep" || name == "sliderSetValue")
        {
            stack[0] = name == "sliderSetValue" ? aSliderValue() : aStep();
            stack[1] = chance(90) ? below(3) : random32() % 5;
        }
        if (name.compare(0, 6, "slider") == 0 && name != "sliderPartUnderPointer" && name != "sliderThumbPlace"
            && name != "sliderShape")
        {
            static const x86::reg16 kinds[] = {0, 1, 2, 3, 4, 5, 7};
            // sliderPartSizes only of the kinds the art's tables have (7 reads past them).
            g.getMemory<x86::reg16>(item + 0x42) = kinds[below(name == "sliderPartSizes" ? 6 : 7)];
        }
        return true;
    }
    static const char* const keyed[] = {"colourListKey", "intFieldKey", "stringFieldKey", "charFieldKey",
                                        "floatFieldKey", "fixedFieldKey"};
    if (std::find_if(std::begin(keyed), std::end(keyed), [&](const char* n) { return name == n; })
        != std::end(keyed))
        makeSoundArguments(g, "playMenuEffect", cpu, stack);  // the menu's click
    // What finds a menu shape by its name (port::shapes::shapeByName, for real
    // on both sides) needs of the graphics' world and the art, as shapes.inc
    // makes them: the shapes known (none, or the names asked for among them),
    // the art's shapes small, the driver's formats where shapeToPixels reads
    // them without THRASH_about (`shapesAt`: shapeByName's own entry).
    const auto shapesWorld = [&](x86::reg32 shapesAt, std::initializer_list<const char*> names) {
        makeShapesWorld(g, cpu, stack);
        makeFieldsWorld(g, cpu);
        plantAboutFormats(g, shapesAt - 0x18 - 4 - 0x14 - 0x34 - 8);
        g.word(0x8b762c) = below(0x300);  // room for the tiles: the shapes' own cases try the Error
        static const x86::reg32 artFormats[] = {0x78, 0x7b, 0x7d, 0x7e};
        for (x86::reg32 block = 0; block < 8; ++block)
        {
            g.word(kBlocks + 0x400 * block) = artFormats[below(4)];
            g.word(kBlocks + 0x400 * block + 4) = (1 + below(15)) | (1 + below(15)) << 16;
        }
        // Every name asked for among them: where the search runs out, the game's
        // strncmp leaves ebx otherwise than the port's, and the tick's stand-in
        // logs it (shapes.inc).
        const x86::reg32 count = x86::reg32(names.size()) + below(10);
        g.word(0x8b7628) = count;
        x86::reg32 slot = below(count - x86::reg32(names.size()) + 1);
        for (const char* n : names)
            std::memcpy(&g.getMemory<char>(0x8b48c0 + 0x14 * slot++ + 0x10), n, 4);
    };
    if (name == "colourListShown")
        shapesWorld(cpu.esp - 0xc - 4, {"yar1", "bdd2"});
    else
        makeFieldsWorld(g, cpu);
    const auto ends = [&](const char* tail) {
        return name.size() >= std::strlen(tail) && name.compare(name.size() - std::strlen(tail), std::string::npos, tail) == 0;
    };
    const auto aCar = [] { return chance(90) ? below(4) : random32(); };
    const auto out = [&](x86::reg32 i) { return kFdWords + 4 * i; };
    if (name == "carColourCount" || name == "carCustomColour" || name == "saveCarColours")
        cpu.eax = aCar();
    else if (name == "carColour" || name == "carColourName" || name == "carText" || name == "setCarColour")
    {
        cpu.eax = aCar();
        cpu.edx = chance(80) ? below(name == "carColour" || name == "setCarColour" ? 3 : 0x30) : below(0x100) - 0x10;
        cpu.ebx = below(14);
    }
    else if (name == "carColourRgb" || name == "setCarCustomColour")
    {
        cpu.eax = aCar();
        cpu.edx = name == "carColourRgb" ? (chance(90) ? below(15) : below(40) - 2) : (chance(90) ? below(3) : random32());
        cpu.ebx = name == "carColourRgb" ? (chance(90) ? below(3) : random32()) : random32();
        cpu.ecx = name == "carColourRgb" ? out(0) : random32();
        stack[0] = name == "carColourRgb" ? out(1) : random32();
        stack[1] = name == "carColourRgb" ? out(2) : random32();
        stack[2] = out(3);
    }
    else if (name == "wheelFromCarColour" || name == "wheelForPlayer")
    {
        makeFieldsItem(g);
        g.word(kFdItem + 0x60) = chance(80) ? below(2) : random32();
        cpu.eax = kFdItem;
        cpu.edx = chance(80) ? below(2) : random32();
    }
    else if (name == "refreshCustomColours")
        ;
    else if (name == "setCursorColour")
        cpu.eax = random32();
    else if (name == "drawFieldText" || name == "drawFieldLine" || name == "drawCursorText3d" || name == "drawCursorText"
             || name == "drawSpacedText")
    {
        const x86::reg32 text = kFdTexts + 0x40 * below(8);
        cpu.eax = text;
        cpu.edx = aScreenX();
        cpu.ebx = aScreenY();
        x86::reg32 length = 0;
        while (g.getMemory<x86::reg8>(text + length) != 0)
            ++length;
        const x86::reg32 cursor = chance(90) ? below(length + 2) : random32();
        if (name == "drawFieldLine")
        {
            cpu.ecx = chance(80) ? 0x12 : below(0x30);
            stack[0] = chance(90) ? below(6) : random32();
            stack[1] = random32();
            stack[2] = cursor;
            stack[3] = chance(80) ? 3 : below(30);
            stack[4] = random32();
            stack[5] = chance(30) ? 0 : chance(90) ? 1 : random32();
        }
        else if (name == "drawSpacedText")
        {
            cpu.ecx = (random32() & 0xffff0000) | (chance(80) ? 0x12 : below(0x30));
            cpu.edx = (random32() & 0xffff0000) | (aScreenX() & 0xffff);
            stack[0] = (random32() & 0xffff0000) | (chance(90) ? below(6) : random32() & 0xffff);
            stack[1] = random32();
        }
        else if (name == "drawCursorText")
        {
            cpu.ecx = chance(80) ? 0 : 1;
            stack[0] = cursor;
            stack[1] = chance(80) ? 3 : below(30);
            stack[2] = chance(30) ? 0 : 1;
        }
        else
        {
            cpu.ecx = cursor;
            stack[0] = chance(80) ? 3 : below(30);
            stack[1] = chance(30) ? 0 : 1;
        }
    }
    else if (name == "drawCursor")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = chance(80) ? 3 : below(100);
        cpu.ecx = random32();
        stack[0] = random32();
    }
    else if (name == "drawFrameAt")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = below(300);
        cpu.ecx = below(200);
        stack[0] = random32();
    }
    else if (name == "drawShadedTriangle")
    {
        cpu.eax = aScreenX();
        cpu.edx = aScreenY();
        cpu.ebx = aScreenX();
        cpu.ecx = aScreenY();
        stack[0] = aScreenX();
        stack[1] = aScreenY();
        stack[2] = random32();
        stack[3] = random32();
        stack[4] = random32();
    }
    else if (name == "editKey")
    {
        const x86::reg32 size = chance(90) ? 4 + below(12) : below(4);
        aNumberText(g, kFdBuffer, size);
        cpu.eax = kFdBuffer;
        cpu.edx = size;
        cpu.ebx = out(0);
        g.word(out(0)) = chance(90) ? below(size + 2) : random32();
        cpu.ecx = (random32() & 0xffff0000) | (aFieldsKey() & 0xffff);
        stack[0] = chance(50) ? 0 : 1;
    }
    else if (name == "intRangeMessage" || name == "charRangeMessage" || name == "fixedRangeMessage")
    {
        cpu.eax = random32();
        cpu.edx = random32();
    }
    else if (name == "floatRangeMessage")
    {
        stack[0] = feFloat(float(x86::sreg32(below(2000)) - 1000) / 10.0f);
        stack[1] = chance(90) ? feFloat(float(below(2000)) / 10.0f) : random32();
    }
    else if (name.find("ColourList") != std::string::npos || name == "drawColourLine" || name == "pointAtColour"
             || name == "chooseColour" || name == "colourListWidth" || name == "colourListRefresh"
             || name == "colourListKey" || name == "colourListShown" || name == "colourListHidden")
    {
        makeColourList(g);
        cpu.eax = chance(3) && name == "colourListRefresh" ? 0 : kFdItem;
        cpu.edx = name == "drawColourLine" ? below(15) : chance(40) ? 0 : chance(80) ? 1 : random32();
        if (name == "colourListKey")
            cpu.ebx = aFieldsKey();
        else if (name == "drawColourLine")
        {
            cpu.ebx = aScreenX();
            cpu.ecx = aScreenY();
            stack[0] = chance(50) ? 0 : 1;
            stack[1] = chance(50) ? 0 : 1;
        }
    }
    else if (ends("ListBox") || name.compare(0, 7, "listBox") == 0 || name == "pointAtListBoxLine")
    {
        makeListBox(g);
        cpu.eax = kFdItem;
        cpu.edx = random32();
        cpu.ebx = name == "listBoxKey" ? aFieldsKey()
                  : name == "listBoxPartAt" || name == "listBoxArrowAt" || name == "listBoxChooseAt"
                      ? g.getMemory<x86::sreg16>(kFdItem + 0x1a) + below(220)
                      : chance(50) ? 0 : random32();
        if (name == "listBoxPartAt" || name == "listBoxArrowAt")
            cpu.edx = g.getMemory<x86::sreg16>(kFdItem + 0x1c) + below(320);
        if (name == "listBoxChooseAt")
        {
            cpu.ebx = aScreenX();
            cpu.ecx = g.getMemory<x86::sreg16>(kFdItem + 0x1a) + below(220);
            stack[0] = random32();
        }
    }
    else if (name.find("Field") != std::string::npos)
    {
        static const char* const kinds[] = {"Int", "String", "Char", "Float", "Fixed"};
        std::string lower = name, kind;
        for (char& c : lower)
            c = char(std::tolower(static_cast<unsigned char>(c)));
        for (const char* k : kinds)
        {
            std::string l = k;
            l[0] = char(std::tolower(static_cast<unsigned char>(l[0])));
            if (lower.find(l + "field") != std::string::npos)
                kind = k;
        }
        if (kind.empty())
            return false;
        makeField(g, kind);
        cpu.eax = kFdItem;
        cpu.edx = name.compare(0, 4, "bind") == 0 ? kFdValue : chance(50) ? 0 : 1;
        cpu.ebx = name.compare(0, 4, "bind") == 0 ? standInFor(0xfff700) : aFieldsKey();
    }
    else
        return false;
    return true;
}
#endif
