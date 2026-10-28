#ifndef NFS3HP_PORT_FIELDS_H
#define NFS3HP_PORT_FIELDS_H

#include "port.h"

/* The menus' widgets that hold a value, rewritten (port.h says how;
 * port_fields.cpp): the fields typed into -- a text (edstring), a whole number
 * (edint), a byte (edchar), a float (edfloat), a 16.16 fixed number (edfixed)
 * --, the list of lines (List), the sliders single and two-axis (slider), the
 * car's colours (carclrselect) and the car records' colours they show and
 * set, with what they draw a field's text and its cursor with.
 *
 * Each is an adapter under the game's function's name, which
 * disassemble_nfs3hp.py binds to its address (PORT_FIELDS_NATIVES); the
 * generated code calls it by name, the widget table (0x557a84) and the other
 * natives through the address. */
namespace nfs3hp
{
namespace port
{
namespace fields
{

/* ---- The car records' colours ---- */
void carColourCount(App* app, CPU& cpu);          // 0x439760
void carCustomColour(App* app, CPU& cpu);         // 0x439780
void carColour(App* app, CPU& cpu);               // 0x439790
void carColourName(App* app, CPU& cpu);           // 0x4397c0
void setCarColour(App* app, CPU& cpu);            // 0x4397d0
void carColourRgb(App* app, CPU& cpu);            // 0x439810
void setCarCustomColour(App* app, CPU& cpu);      // 0x4398c0
void carText(App* app, CPU& cpu);                 // 0x439ab0
void saveCarColours(App* app, CPU& cpu);          // 0x43b7f0
void wheelFromCarColour(App* app, CPU& cpu);      // 0x43dbe0
void wheelForPlayer(App* app, CPU& cpu);          // 0x43dd50
void refreshCustomColours(App* app, CPU& cpu);    // 0x472360

/* ---- A field's text and cursor ---- */
void setCursorColour(App* app, CPU& cpu);         // 0x4513e0
void drawFieldText(App* app, CPU& cpu);           // 0x4515e0
void drawFieldLine(App* app, CPU& cpu);           // 0x452220
void drawSpacedText(App* app, CPU& cpu);          // 0x4522c0
void drawCursorText3d(App* app, CPU& cpu);        // 0x4d11f0
void drawCursor(App* app, CPU& cpu);              // 0x4da560
void drawCursorText(App* app, CPU& cpu);          // 0x4da8c0

/* ---- The car's colours (carclrselect) ---- */
void colourListWidth(App* app, CPU& cpu);         // 0x4569a0
void colourListRefresh(App* app, CPU& cpu);       // 0x456a20
void drawColourLine(App* app, CPU& cpu);          // 0x456b50
void drawColourList(App* app, CPU& cpu);          // 0x456ce0
void colourListShown(App* app, CPU& cpu);         // 0x456ea0
void pointAtColour(App* app, CPU& cpu);           // 0x456f10
void openColourList(App* app, CPU& cpu);          // 0x456f50
void closeColourList(App* app, CPU& cpu);         // 0x456f70
void chooseColour(App* app, CPU& cpu);            // 0x456f90
void colourListKey(App* app, CPU& cpu);           // 0x457030
void layoutColourList(App* app, CPU& cpu);        // 0x4571e0
void colourListHidden(App* app, CPU& cpu);        // 0x457250
void drawFrameAt(App* app, CPU& cpu);             // 0x4d8aa0

/* ---- The fields typed into ---- */
void editKey(App* app, CPU& cpu);                 // 0x457ae0
void drawIntField(App* app, CPU& cpu);            // 0x457c40
void intRangeMessage(App* app, CPU& cpu);         // 0x457df0
void intFieldKey(App* app, CPU& cpu);             // 0x457e30
void layoutIntField(App* app, CPU& cpu);          // 0x457f70
void intFieldShown(App* app, CPU& cpu);           // 0x458010
void intFieldHidden(App* app, CPU& cpu);          // 0x458050
void bindIntField(App* app, CPU& cpu);            // 0x458080
void drawStringField(App* app, CPU& cpu);         // 0x4580b0
void stringFieldKey(App* app, CPU& cpu);          // 0x4581f0
void layoutStringField(App* app, CPU& cpu);       // 0x458340
void stringFieldShown(App* app, CPU& cpu);        // 0x4583b0
void stringFieldHidden(App* app, CPU& cpu);       // 0x458410
void drawCharField(App* app, CPU& cpu);           // 0x458480
void charRangeMessage(App* app, CPU& cpu);        // 0x458640
void charFieldKey(App* app, CPU& cpu);            // 0x458690
void layoutCharField(App* app, CPU& cpu);         // 0x4587e0
void charFieldShown(App* app, CPU& cpu);          // 0x4588a0
void charFieldHidden(App* app, CPU& cpu);         // 0x4588e0
void bindCharField(App* app, CPU& cpu);           // 0x458910
void drawFloatField(App* app, CPU& cpu);          // 0x458940
void floatRangeMessage(App* app, CPU& cpu);       // 0x458b20
void floatFieldKey(App* app, CPU& cpu);           // 0x458b80
void layoutFloatField(App* app, CPU& cpu);        // 0x458ce0
void floatFieldShown(App* app, CPU& cpu);         // 0x458d90
void floatFieldHidden(App* app, CPU& cpu);        // 0x458dd0
void bindFloatField(App* app, CPU& cpu);          // 0x458e00
void drawFixedField(App* app, CPU& cpu);          // 0x458e30
void fixedRangeMessage(App* app, CPU& cpu);       // 0x459020
void fixedFieldKey(App* app, CPU& cpu);           // 0x459090
void layoutFixedField(App* app, CPU& cpu);        // 0x459210
void fixedFieldShown(App* app, CPU& cpu);         // 0x4592b0
void fixedFieldHidden(App* app, CPU& cpu);        // 0x4592f0
void bindFixedField(App* app, CPU& cpu);          // 0x459320

/* ---- The list of lines (List) ---- */
void drawListBox(App* app, CPU& cpu);             // 0x465500
void pointAtListBoxLine(App* app, CPU& cpu);      // 0x465880
void listBoxDown(App* app, CPU& cpu);             // 0x4658f0
void listBoxUp(App* app, CPU& cpu);               // 0x465950
void listBoxPartAt(App* app, CPU& cpu);           // 0x4659a0
void listBoxArrowAt(App* app, CPU& cpu);          // 0x465a10
void listBoxKey(App* app, CPU& cpu);              // 0x465a30
void layoutListBox(App* app, CPU& cpu);           // 0x465ba0
void listBoxShown(App* app, CPU& cpu);            // 0x465c10
void listBoxHidden(App* app, CPU& cpu);           // 0x465c60
void listBoxChooseAt(App* app, CPU& cpu);         // 0x465ca0
void drawShadedTriangle(App* app, CPU& cpu);      // 0x4d8570

/* ---- The sliders ---- */
void sliderPartSizes(App* app, CPU& cpu);         // 0x469080
void sliderPartUnderPointer(App* app, CPU& cpu);  // 0x4692c0
void sliderThumbPlace(App* app, CPU& cpu);        // 0x469340
void snapToStep(App* app, CPU& cpu);              // 0x4693c0
void setSliderValue(App* app, CPU& cpu);          // 0x469480
void setSliderStep(App* app, CPU& cpu);           // 0x469530
void dragSliderTo(App* app, CPU& cpu);            // 0x469590
void drawSlider(App* app, CPU& cpu);              // 0x469680
void trackSlider(App* app, CPU& cpu);             // 0x46a5f0
void sliderKey(App* app, CPU& cpu);               // 0x46a860
void placeSliderParts(App* app, CPU& cpu);        // 0x46a980
void setUpSlider(App* app, CPU& cpu);             // 0x46ab10
void sliderBox(App* app, CPU& cpu);               // 0x46abb0
void twoAxisThumbPlace(App* app, CPU& cpu);       // 0x46ac40
void setTwoAxisValue(App* app, CPU& cpu);         // 0x46add0
void setTwoAxisStep(App* app, CPU& cpu);          // 0x46afe0
void dragTwoAxisTo(App* app, CPU& cpu);           // 0x46b040
void drawTwoAxis(App* app, CPU& cpu);             // 0x46b3a0
void trackTwoAxis(App* app, CPU& cpu);            // 0x46c320
void twoAxisKey(App* app, CPU& cpu);              // 0x46c4a0
void placeTwoAxisParts(App* app, CPU& cpu);       // 0x46c640
void setUpTwoAxis(App* app, CPU& cpu);            // 0x46c820
void twoAxisBox(App* app, CPU& cpu);              // 0x46c8b0
void sliderSetValue(App* app, CPU& cpu);          // 0x46c950
void sliderDraw(App* app, CPU& cpu);              // 0x46cae0
void sliderWidgetKey(App* app, CPU& cpu);         // 0x46cb80
void sliderWidgetLayout(App* app, CPU& cpu);      // 0x46cbe0
void sliderWidgetHidden(App* app, CPU& cpu);      // 0x46cc10
void sliderWidgetShown(App* app, CPU& cpu);       // 0x46cc50
void sliderShape(App* app, CPU& cpu);             // 0x4d5e40

}  // namespace fields
}  // namespace port
}  // namespace nfs3hp

#endif
