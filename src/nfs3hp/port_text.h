#ifndef NFS3HP_PORT_TEXT_H
#define NFS3HP_PORT_TEXT_H

#include "port.h"

/* The menus' text and the 2D drawing under it, rewritten (port.h says how;
 * port_text.cpp): a line of the language's text by its number, the font a
 * text is measured and drawn in -- the 3D card's, a quad of the font's
 * texture a character, in a race's pause screens and the HUD; the 2D
 * screens' otherwise --, the fonts' quads queued and drawn, the text scale,
 * a text placed on the menus' 640 by 480 screen and on the screen's own, a
 * text wrapped into a box, the menus' key from the keyboard and the mouse.
 *
 * disassemble_nfs3hp.py binds each address to the adapter of that name here
 * (PORT_TEXT_NATIVES), and the generated code calls it by name; the other
 * natives call these adapters as the game's code would call the address. */
namespace nfs3hp
{
namespace port
{
namespace text
{

/* The adapters, under the game's functions' names. */
void textWidth(App* app, CPU& cpu);              // 0x452020
void selectFont(App* app, CPU& cpu);             // 0x452100
void measureText(App* app, CPU& cpu);            // 0x4d1430
void textWidthWithOverhang(App* app, CPU& cpu);  // 0x4d1480
void drawText(App* app, CPU& cpu);               // 0x4d1000
void drawCharacter(App* app, CPU& cpu);          // 0x4d06f0
void takeQuad(App* app, CPU& cpu);               // 0x49bcd0
void viewport(App* app, CPU& cpu);               // 0x4beb80
void toScreenX(App* app, CPU& cpu);              // 0x451400
void toScreenY(App* app, CPU& cpu);              // 0x451440
void specialText(App* app, CPU& cpu);            // 0x4d17b0
void languageText(App* app, CPU& cpu);           // 0x4d1850
void flushFonts(App* app, CPU& cpu);             // 0x4d1340
void setTextScale(App* app, CPU& cpu);           // 0x4d1390
void keepTextScale(App* app, CPU& cpu);          // 0x4d1400
void restoreTextScale(App* app, CPU& cpu);       // 0x4d1410
void characterWidth(App* app, CPU& cpu);         // 0x4d1540
void characterOverhang(App* app, CPU& cpu);      // 0x4d1590
void setTextColour(App* app, CPU& cpu);          // 0x4513c0
void screenToMenuX(App* app, CPU& cpu);          // 0x451480
void screenToMenuY(App* app, CPU& cpu);          // 0x4514c0
void readMenuMouse(App* app, CPU& cpu);          // 0x451500
void dimBackground(App* app, CPU& cpu);          // 0x451530
void drawTextAt(App* app, CPU& cpu);             // 0x451590
void drawMenuText(App* app, CPU& cpu);           // 0x452190
void flushQuads(App* app, CPU& cpu);             // 0x49be40
void joystickKey(App* app, CPU& cpu);            // 0x451700
void captureKeys(App* app, CPU& cpu);            // 0x451810
void scanCodeOfKey(App* app, CPU& cpu);          // 0x451840
void keyOfScanCode(App* app, CPU& cpu);          // 0x4518c0
void menuKey(App* app, CPU& cpu);                // 0x451960
void resetMenuKey(App* app, CPU& cpu);           // 0x451b20
void nextWord(App* app, CPU& cpu);               // 0x451b50
void drawWrappedText(App* app, CPU& cpu);        // 0x451cd0
void drawTextBox(App* app, CPU& cpu);            // 0x451fc0
void measureTextBox(App* app, CPU& cpu);         // 0x451ff0
void menusEnd(App* app, CPU& cpu);               // 0x452110
void queueQuad(App* app, CPU& cpu);              // 0x49bd30
void unqueueQuad(App* app, CPU& cpu);            // 0x49bdc0
void mouseMenuKey(App* app, CPU& cpu);           // 0x49c000
void loadLanguageText(App* app, CPU& cpu);       // 0x4d1750

}  // namespace text
}  // namespace port
}  // namespace nfs3hp

#endif
