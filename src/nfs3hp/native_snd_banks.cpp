#include "native_snd.h"

/* The race's banks from the game's archives, native (native_snd.h says
 * how): a bank read out of a .viv archive (0x43b830 opens one, 0x43b9d0
 * finds a file in it, 0x43b9b0 closes it) into memory and added to SND --
 * its header copied out where SND asks -- or, missing from the archive, the
 * bank file of the audio folder loaded instead (0x410b50).
 *
 * The game's state: 0x571124 the banks (12 bytes each: the handle, then at
 * +8 the memory it is in). */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kOpen = 0x43b830, kFind = 0x43b9d0, kClose = 0x43b9b0, kSprintf = 0x4df690;
constexpr reg32 kAllocate = 0x4e1620, kFree = 0x4e1890, kAllocName = 0x536a58;

/* The bank of size [size] at [offset] of archive file [file], memory for it
 * in esi, read in and added to SND (its header copied out for 7, into ecx's
 * memory): the memory left in esi, the handle at `handle`. */
bool readBank(App* app, CPU& cpu, reg32 file, reg32 offset, reg32 size, reg32 archive, reg32 handle)
{
    cpu.edx = at(app, offset);
    cpu.eax = at(app, file);
    cpu.ebx = 0;
    if (!call(app, cpu, 0x4e9088))
        return false;
    cpu.ecx = at(app, file);
    cpu.ebx = 1;
    cpu.edx = at(app, size);
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x4e9200))
        return false;
    cpu.edx = file;
    cpu.eax = at(app, archive);
    if (!call(app, cpu, kClose))
        return false;
    cpu.eax = handle;
    cpu.edx = cpu.esi;
    if (!call(app, cpu, 0x4e8d20))
        return false;
    if (cpu.eax != 7)
        return true;
    cpu.eax = at(app, handle);
    if (!call(app, cpu, 0x4e8db0))
        return false;
    cpu.ebx = 0;
    cpu.edx = cpu.eax;
    cpu.eax = kAllocName;
    if (!call(app, cpu, kAllocate))
        return false;
    cpu.edx = at(app, handle);
    cpu.ecx = cpu.eax;
    if (!call(app, cpu, 0x4e8e20))
        return false;
    cpu.eax = cpu.esi;
    if (!call(app, cpu, kFree))
        return false;
    cpu.esi = cpu.ecx;
    return true;
}

}  // namespace

/* 0x413750: the voice bank of archive eax -- or, no such archive, the
 * units' one (0x412950's names) of the audio folder -- for speaker edx (a
 * name of 0x412920's, now and then the plain one; all for 0x63) into bank
 * slot ebx. */
void voiceBankLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(4);
    cpu.esp = cpu.ebp - 0x16c;
    const reg32 name = cpu.ebp - 0x16c, speakers = cpu.ebp - 0x6c, units = cpu.ebp - 0x3c;
    put(app, cpu.ebp - 0xc, cpu.eax);
    put(app, cpu.ebp - 8, cpu.edx);
    put(app, cpu.ebp - 0x10, cpu.ebx);
    for (reg32 k = 0; k < 0xc; ++k)
        put(app, speakers + 4 * k, at(app, 0x412920 + 4 * k));
    for (reg32 k = 0; k < 7; ++k)
        put(app, units + 4 * k, at(app, 0x412950 + 4 * k));
    cpu.ecx = 0;
    cpu.esi = 0x412950 + 0x1c;
    cpu.edi = units + 0x1c;
    if (!call(app, cpu, 0x4e0e60))
        return;
    if (cpu.eax != 0)
    {
        cpu.edx = cpu.ebp - 0x14;
        cpu.eax = at(app, cpu.ebp - 0xc);
    }
    else
    {
        cpu.eax = at(app, 0x6fbb4c);
        cpu.edx = at(app, cpu.ebp + cpu.eax * 4 - 0x3c);
        if (!call(app, cpu, kSprintf, {name, 0x536a28, 0x7a2ab4, cpu.edx}))
            return;
        cpu.edx = cpu.ebp - 0x14;
        cpu.eax = name;
    }
    if (!call(app, cpu, kOpen))
        return;
    cpu.edi = cpu.eax;
    cpu.ecx = at(app, cpu.ebp - 8);
    bool plain = cpu.ecx == 0x63;
    if (!plain)
    {
        cpu.ebx = 0x64;
        cpu.edx = 0;
        if (!call(app, cpu, 0x4e0d88))
            return;
        udiv(cpu, cpu.ebx);
        plain = cpu.edx <= 0xf;
    }
    if (!plain)
    {
        cpu.ebx = at(app, cpu.ebp + cpu.ecx * 4 - 0x6c);
        if (!call(app, cpu, kSprintf, {name, 0x536a48, cpu.ebx}))
            return;
    }
    else if (!call(app, cpu, kSprintf, {name, 0x536a38}))
        return;
    cpu.ecx = cpu.ebp - 0x18;
    cpu.ebx = cpu.ebp - 0x1c;
    cpu.edx = name;
    cpu.eax = cpu.edi;
    if (!call(app, cpu, kFind))
        return;
    cpu.esi = at(app, cpu.ebp - 0x18);
    if (cpu.esi == 0)
    {
        cpu.edx = cpu.ebp - 0x14;
        cpu.eax = cpu.edi;
        if (!call(app, cpu, kClose))
            return;
        return leave(cpu, kept, pushed);
    }
    cpu.eax = kAllocName;
    cpu.edx = cpu.esi;
    cpu.ebx = 0;
    if (!call(app, cpu, kAllocate))
        return;
    cpu.esi = cpu.eax;
    put(app, cpu.ebp - 4, cpu.eax);
    // As readBank, but the archive is edi's here and the copy kept at [ebp-4].
    cpu.edx = at(app, cpu.ebp - 0x1c);
    cpu.eax = at(app, cpu.ebp - 0x14);
    cpu.ebx = 0;
    if (!call(app, cpu, 0x4e9088))
        return;
    cpu.ecx = at(app, cpu.ebp - 0x14);
    cpu.ebx = 1;
    cpu.edx = at(app, cpu.ebp - 0x18);
    cpu.eax = cpu.esi;
    if (!call(app, cpu, 0x4e9200))
        return;
    cpu.edx = cpu.ebp - 0x14;
    cpu.eax = cpu.edi;
    if (!call(app, cpu, kClose))
        return;
    cpu.eax = cpu.ebp - 0x20;
    cpu.edx = cpu.esi;
    if (!call(app, cpu, 0x4e8d20))
        return;
    if (cpu.eax == 7)
    {
        cpu.eax = at(app, cpu.ebp - 0x20);
        if (!call(app, cpu, 0x4e8db0))
            return;
        cpu.ebx = 0;
        cpu.edx = cpu.eax;
        cpu.eax = kAllocName;
        if (!call(app, cpu, kAllocate))
            return;
        cpu.edx = at(app, cpu.ebp - 0x20);
        cpu.ebx = cpu.eax;
        if (!call(app, cpu, 0x4e8e20))
            return;
        cpu.eax = cpu.esi;
        if (!call(app, cpu, kFree))
            return;
        put(app, cpu.ebp - 4, cpu.ebx);
    }
    cpu.edi = at(app, cpu.ebp - 0x10);
    cpu.ebx = cpu.edi * 12;
    cpu.eax = at(app, cpu.ebp - 0x20);
    put(app, cpu.ebx + 0x571124, cpu.eax);
    cpu.eax = at(app, cpu.ebp - 4);
    put(app, cpu.ebx + 0x57112c, cpu.eax);
    leave(cpu, kept, pushed);
}

/* 0x4138e0: player edx's car bank of archive eax -- the second player's in
 * the split screen, the first's, or another's (surround or not) -- or,
 * missing from the archive, the audio folder's bank file of that name. */
void carBankLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEsi | kEdi;
    cpu.ebp = kept.frame(5);
    cpu.esp = cpu.ebp - 0x11c;
    const reg32 name = cpu.ebp - 0x11c;
    put(app, cpu.ebp - 8, cpu.edx);
    cpu.edx = cpu.ebp - 0x10;
    if (!call(app, cpu, kOpen))
        return;
    cpu.edx = at(app, 0x6fd3b0);
    put(app, cpu.ebp - 0xc, cpu.eax);
    put(app, cpu.ebp - 4, cpu.eax);
    // The bank's name in the archive, and the file's ending without it.
    reg32 inArchive, ending;
    enum
    {
        kSecond,
        kFirst,
        kOther
    } which;
    if (cpu.edx == 1 && cpu.edx != at(app, cpu.ebp - 8))
    {
        which = kSecond;
        inArchive = 0x536a5c;
        ending = 0x536a68;
    }
    else if (at(app, cpu.ebp - 8) == 0)
    {
        which = kFirst;
        inArchive = 0x536a70;
        ending = 0x536a78;
        cpu.eax = at(app, cpu.ebp - 4);
    }
    else
    {
        which = kOther;
        inArchive = at(app, 0x5525a4) != 0 ? 0x536a80 : 0x536a8c;
        ending = 0x536a98;
        cpu.eax = at(app, cpu.ebp - 4);
    }
    cpu.ecx = cpu.ebp - 0x1c;
    cpu.ebx = cpu.ebp - 0x18;
    cpu.edx = inArchive;
    if (!call(app, cpu, kFind))
        return;
    const reg32 size = at(app, cpu.ebp - 0x1c);
    if (which == kSecond)
        cpu.ebx = size;
    else if (which == kFirst)
        cpu.edi = size;
    if (size != 0)
    {
        cpu.edx = size;
        cpu.eax = kAllocName;
        cpu.ebx = 0;
        if (!call(app, cpu, kAllocate))
            return;
        cpu.esi = cpu.eax;
        if (!readBank(app, cpu, cpu.ebp - 0x10, cpu.ebp - 0x18, cpu.ebp - 0x1c, cpu.ebp - 4, cpu.ebp - 0x14))
            return;
        cpu.edx = at(app, cpu.ebp - 8);
        cpu.eax = cpu.edx * 3;
        cpu.edx = cpu.eax * 4;
        cpu.eax = at(app, cpu.ebp - 0x14);
        put(app, cpu.edx + 0x57112c, cpu.esi);
        put(app, cpu.edx + 0x571124, cpu.eax);
        return leave(cpu, kept, pushed);
    }
    if (which != kSecond)
        cpu.edx = at(app, cpu.ebp - 8);
    copyString(app, cpu, name, 0x7a2ab4);
    if (which == kSecond)
        cpu.edx = at(app, cpu.ebp - 8);
    else
        cpu.ebx = 0;
    appendString(app, cpu, name, ending);
    cpu.edi = name;
    cpu.eax = name;
    if (!call(app, cpu, 0x410b50))
        return;
    cpu.edx = cpu.ebp - 0x10;
    cpu.eax = at(app, which == kSecond ? cpu.ebp - 0xc : cpu.ebp - 4);
    if (!call(app, cpu, kClose))
        return;
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
