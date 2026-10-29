#ifndef NFS3HP_PORT_MENUS_H
#define NFS3HP_PORT_MENUS_H

#include "port.h"

/* The menu files and the screens they make, rewritten (port.h says how;
 * port_menus.cpp): FeData\Menus\<name>.mnu read into the table of screens and
 * the table of items, the keys of its sections looked up in the parser's
 * tables and stored into the items' fields by their kinds, a screen's
 * handlers found by its name, and the item lookup's codelink match; and the
 * path function they build the file's name with.
 *
 * disassemble_nfs3hp.py binds each address to the adapter of that name here
 * (PORT_MENUS_NATIVES): the generated code calls them by name, and the
 * native whole screens (native_frontend_*.cpp) by address.  The adapter takes
 * the arguments from the registers and the stack and gives back the result
 * in eax, every other register as the caller had it. */
namespace nfs3hp
{
namespace port
{
namespace menus
{

/* The adapters, under the game's functions' names. */
void codelinkMatches(App* app, CPU& cpu);   // 0x4429c0
void assignHandlers(App* app, CPU& cpu);    // 0x442b10
void keywordIndex(App* app, CPU& cpu);      // 0x448f00
void storeString(App* app, CPU& cpu);       // 0x448f50
void widgetType(App* app, CPU& cpu);        // 0x448fd0
void widgetName(App* app, CPU& cpu);        // 0x449020
void initItem(App* app, CPU& cpu);          // 0x449060
void sectionType(App* app, CPU& cpu);       // 0x4490e0
void parseInt(App* app, CPU& cpu);          // 0x449130
void parseLong(App* app, CPU& cpu);         // 0x449170
void parseFloat(App* app, CPU& cpu);        // 0x4491b0
void setField(App* app, CPU& cpu);          // 0x449240
void readEntry(App* app, CPU& cpu);         // 0x4493b0
void loadMenus(App* app, CPU& cpu);         // 0x449510
void checkMenuFile(App* app, CPU& cpu);     // 0x4498a0
void checkMenuFiles(App* app, CPU& cpu);    // 0x449960
void callOnLoad(App* app, CPU& cpu);        // 0x449990
void appendBackslash(App* app, CPU& cpu);   // 0x4529a0

}  // namespace menus
}  // namespace port
}  // namespace nfs3hp

#endif
