#ifndef NFS3HP_PORT_LOOP_H
#define NFS3HP_PORT_LOOP_H

#include "port.h"

/* The menu loop and what it moves through, rewritten (port.h says how;
 * port_loop.cpp): the screen shown and the screens gone through, its items
 * shown, drawn and passed, the selection moved by the keys and the mouse, a
 * key handed to the item that has it, the race settings kept consistent, the
 * help box, the loop itself, and the answers of the dialogs it opens.
 *
 * disassemble_nfs3hp.py binds each address to the adapter of that name here
 * (PORT_LOOP_NATIVES): the generated code calls them by name, and the native
 * whole screens (native_frontend_*.cpp) and the widgets by address.  The
 * adapter takes the arguments from the registers and the stack and gives back
 * the result in eax, every other register as the caller had it. */
namespace nfs3hp
{
namespace port
{
namespace loop
{

/* The adapters, under the game's functions' names. */
void itemUsable(App* app, CPU& cpu);          // 0x4499b0
void keyAllowed(App* app, CPU& cpu);          // 0x4499f0
void drawHelp(App* app, CPU& cpu);            // 0x449aa0
void keysTaken(App* app, CPU& cpu);           // 0x449df0
void selectable(App* app, CPU& cpu);          // 0x449e50
void pointAtSelected(App* app, CPU& cpu);     // 0x449ea0
void selectPrevious(App* app, CPU& cpu);      // 0x449f30
void selectNext(App* app, CPU& cpu);          // 0x44a0c0
void escapeButton(App* app, CPU& cpu);        // 0x44a240
void handleKey(App* app, CPU& cpu);           // 0x44a2d0
void selectedIndex(App* app, CPU& cpu);       // 0x44a440
void selectItem(App* app, CPU& cpu);          // 0x44a470
void drawItems(App* app, CPU& cpu);           // 0x44a4f0
void releaseMouse(App* app, CPU& cpu);        // 0x44a690
void itemUnderMouse(App* app, CPU& cpu);      // 0x44a6b0
void itemsShown(App* app, CPU& cpu);          // 0x44a860
void passItems(App* app, CPU& cpu);           // 0x44a8b0
void hideItems(App* app, CPU& cpu);           // 0x44a9e0
void leaveScreen(App* app, CPU& cpu);         // 0x44aa30
void resetItems(App* app, CPU& cpu);          // 0x44aad0
void enterScreen(App* app, CPU& cpu);         // 0x44ab40
void menuByName(App* app, CPU& cpu);          // 0x44ae60
void currentMenu(App* app, CPU& cpu);         // 0x44aeb0
void popMenu(App* app, CPU& cpu);             // 0x44aec0
void pushMenu(App* app, CPU& cpu);            // 0x44af10
void setHistory(App* app, CPU& cpu);          // 0x44af50
void player1NameAnswer(App* app, CPU& cpu);   // 0x44af90
void player2NameAnswer(App* app, CPU& cpu);   // 0x44b040
void quitAnswer(App* app, CPU& cpu);          // 0x44b0f0
void waitWhileSuspended(App* app, CPU& cpu);  // 0x44b1a0
void menuLoop(App* app, CPU& cpu);            // 0x44b230
void fitRaceSettings(App* app, CPU& cpu);     // 0x44be60

}  // namespace loop
}  // namespace port
}  // namespace nfs3hp

#endif
