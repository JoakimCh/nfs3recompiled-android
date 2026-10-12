#ifndef EACSND_H_
#define EACSND_H_
#include <x86.h>
#include <lib/winapp.h>
#include <lib/library.h>

/* eacsnd.dll is native: its exports are the port's functions
 * (disassemble_nfs3hp.py), and only its data is here, as it loads. */

namespace eacsnd
{

extern const x86::reg8 s_AUTOSegment[];
extern const x86::reg8 s__idataSegment[];
extern const x86::reg8 s_DGROUPSegment[];
extern const x86::reg8 s__edataSegment[];

extern win32::Library* s_registry;

}

#endif /* !EACSND_H_ */
