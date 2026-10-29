#ifndef NFS3HP_PORT_DIALOGS_H
#define NFS3HP_PORT_DIALOGS_H

#include "port.h"

/* The dialogs over the screens, rewritten (port.h says how; port_dialogs.cpp):
 * the dialog up and its kind, what it draws -- its box, its lines, its buttons,
 * the field typed in, a list's entries, the help box over it -- the pointer
 * on its buttons and entries, each kind's keys and its pass (a question, a
 * message, a line to type in, a list to tick), a list opened and its entries
 * laid out, and the dialog's own keys and pass, which hand an answer to its
 * callback.
 *
 * disassemble_nfs3hp.py binds each address to the adapter of that name here
 * (PORT_DIALOGS_NATIVES): the generated code calls them by name, the native
 * whole screens and the menu loop by address.  The adapter takes the
 * arguments from the registers and the stack and gives back the result in eax,
 * every other register as the caller had it.  What opens a question, a message
 * and a line to type in, and lays out their boxes, stays native whole
 * (native_frontend_dialogs.cpp, MENU_NATIVES). */
namespace nfs3hp
{
namespace port
{
namespace dialogs
{

/* The adapters, under the game's functions' names. */
void dialogShown(App* app, CPU& cpu);        // 0x4438b0
void dialogKind(App* app, CPU& cpu);         // 0x4438c0
void drawBox(App* app, CPU& cpu);            // 0x4438d0
void drawLines(App* app, CPU& cpu);          // 0x443f40
void drawButtons(App* app, CPU& cpu);        // 0x444000
void drawEditField(App* app, CPU& cpu);      // 0x444350
void buttonUnderMouse(App* app, CPU& cpu);   // 0x4445d0
void questionKey(App* app, CPU& cpu);        // 0x444910
void questionPass(App* app, CPU& cpu);       // 0x4449d0
void endMessage(App* app, CPU& cpu);         // 0x444a60
void messageKey(App* app, CPU& cpu);         // 0x444b20
void messagePass(App* app, CPU& cpu);        // 0x444b60
void editKey(App* app, CPU& cpu);            // 0x444f50
void editPass(App* app, CPU& cpu);           // 0x4450c0
void listFocus(App* app, CPU& cpu);          // 0x445150
void pointAtEntry(App* app, CPU& cpu);       // 0x445160
void entryUnderMouse(App* app, CPU& cpu);    // 0x4451d0
void placeEntries(App* app, CPU& cpu);       // 0x4452d0
void drawList(App* app, CPU& cpu);           // 0x445380
void listKey(App* app, CPU& cpu);            // 0x445520
void listPass(App* app, CPU& cpu);           // 0x445680
void openList(App* app, CPU& cpu);           // 0x445750
void drawDialogHelp(App* app, CPU& cpu);     // 0x445ac0
void loadDialogArt(App* app, CPU& cpu);      // 0x445de0
void dialogKey(App* app, CPU& cpu);          // 0x445e60
void closeDialog(App* app, CPU& cpu);        // 0x445f10
void dialogPass(App* app, CPU& cpu);         // 0x445f50

}  // namespace dialogs
}  // namespace port
}  // namespace nfs3hp

#endif
