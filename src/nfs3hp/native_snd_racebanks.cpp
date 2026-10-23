#include "native_snd.h"

/* The race's banks loaded, native (native_snd.cpp says how): the players'
 * cars' (from the car's archive, or by its model the audio folder's file),
 * the race's own -- crashes, the cops' and their radio in the units'
 * folder, the track's ambience by its number (and the weather), the
 * speech's, the co-driver's -- the loading bar turned (0x4a33d0) after
 * each.  Names built as the code builds them: the inlined strcpy and
 * strcat, sprintf. */
namespace nfs3hp
{
namespace snd
{

namespace
{

constexpr reg32 kLoadBank = 0x410b50, kCarBank = 0x4138e0, kBar = 0x4a33d0, kSprintf = 0x4df690;
constexpr reg32 kAudioDir = 0x7a2ab4, kCarsDir = 0x7a28b4;

/* The bank file's ending for car model edx (as the menus number them). */
reg32 modelEnding(reg32 model)
{
    if (model == 0x25b)
        return 0x536aa0;
    if (i32(model) >= 0x258)
        return 0x536aa8;
    if (model == 0x3e || model == 0x35)
        return 0x536ab0;
    return 0x536ab8;
}

}  // namespace

/* 0x413bc0: the race's banks loaded. */
void raceBanksLoad(App* app, CPU& cpu)
{
    const Kept kept(cpu);
    const unsigned pushed = kEbx | kEcx | kEdx | kEsi | kEdi;
    const reg32 frame = kept.frame(6);
    cpu.esp = frame - 0xe4;
    cpu.ebp = frame - 0x9a;
    const reg32 b = cpu.ebp, name = b - 0x4a, units = b + 0x1a, unitNames = b + 0x7e;
    auto copy = [&](reg32 from) {
        cpu.edi = name;
        copyString(app, cpu, name, from);
        cpu.edi = name;
    };
    auto append = [&](reg32 from) {
        cpu.edi = name;
        appendString(app, cpu, name, from);
        cpu.edi = name;
    };
    auto load = [&](reg32 slot) {
        cpu.edx = slot;
        cpu.eax = name;
        cpu.ebx = 0;
        return call(app, cpu, kLoadBank);
    };
    auto bar = [&] { return call(app, cpu, kBar); };
    // The car of model edx from its archive ("<cars><model name>\" and
    // 0x536ac0), as player `player`'s (edx as the code has it when called).
    auto carArchive = [&](bool slotFirst, reg32 slot) {
        copy(kCarsDir);
        cpu.eax = name;
        if (!call(app, cpu, 0x4529a0))
            return false;
        cpu.eax = cpu.edx;
        cpu.edi = name;
        if (!call(app, cpu, 0x4392b0))
            return false;
        cpu.esi = cpu.eax;
        if (slotFirst)
            cpu.edx = slot;
        append(cpu.esi);
        if (!slotFirst)
            cpu.edx = slot;
        cpu.eax = name;
        cpu.esi = 0x536ac0;
        cpu.edi = name;
        if (!call(app, cpu, 0x4529a0))
            return false;
        append(0x536ac0);
        cpu.eax = name;
        return call(app, cpu, kCarBank);
    };
    // The units' names, the folder of the units in use.
    cpu.ecx = 7;
    cpu.edi = unitNames;
    cpu.esi = 0x41296c;
    cpu.eax = at(app, 0x6fbb4c);
    for (; cpu.ecx > 0; --cpu.ecx, cpu.esi += 4, cpu.edi += 4)
        put(app, cpu.edi, at(app, cpu.esi));
    static const reg32 folders[] = {0x7a2b34, 0x7a2bb4, 0x7a2c34, 0x7a2cb4, 0x7a2d34, 0x7a2b34};
    if (cpu.eax <= 5)
    {
        cpu.edi = units;
        copyString(app, cpu, units, folders[cpu.eax]);
        cpu.edi = units;
    }
    if (at(app, 0x6fd3b0) == 1)
    {
        // The split screen: each player's car (0x6fd540, 0x6fd5ac), into
        // banks 0 and 0x16; the third's (a cop's, 0x6fd684) next.
        for (const auto& [model, slot] : {std::pair<reg32, reg32>{0x6fd540, 0}, {0x6fd5ac, 0x16}})
        {
            cpu.edx = at(app, model);
            if (i32(cpu.edx) < 0 || i32(cpu.edx) > 0x31)
            {
                copy(kAudioDir);
                append(modelEnding(cpu.edx));
                if (slot == 0)
                {
                    cpu.eax = name;
                    cpu.ebx = 0;
                    cpu.edx = 0;
                    if (!call(app, cpu, kLoadBank))
                        return;
                }
                else if (!load(slot))
                    return;
            }
            else if (slot == 0)
            {
                // The code's order: edx 0 just before the ending.
                copy(kCarsDir);
                cpu.eax = name;
                if (!call(app, cpu, 0x4529a0))
                    return;
                cpu.eax = cpu.edx;
                cpu.edi = name;
                if (!call(app, cpu, 0x4392b0))
                    return;
                cpu.esi = cpu.eax;
                append(cpu.esi);
                cpu.edx = 0;
                cpu.eax = name;
                cpu.esi = 0x536ac0;
                cpu.edi = name;
                if (!call(app, cpu, 0x4529a0))
                    return;
                append(0x536ac0);
                cpu.eax = name;
                if (!call(app, cpu, kCarBank))
                    return;
            }
            else if (!carArchive(true, slot))
                return;
        }
        if (at(app, 0x6fd520) != 0)
        {
            cpu.edx = at(app, 0x6fd684);
            if (i32(cpu.edx) < 0 || i32(cpu.edx) > 0x31)
                cpu.edx = 0;
        }
        else
            cpu.edx = 0;
    }
    else
    {
        // The player's car: a cop's (0x6fd4fc's bit 2) by its own number
        // (0x6fd500), else by its model.
        cpu.edx = at(app, 0x6fd4f4) * 12;
        cpu.eax = cpu.edx;
        cpu.edx = at(app, cpu.edx + cpu.eax * 8 + 0x6fd540);
        if ((byte(app, 0x6fd4fc) & 2) != 0)
        {
            cpu.ecx = at(app, 0x6fd500);
            copy(kAudioDir);
            cpu.ecx += 0x32;
            reg32 ending;
            if (cpu.edx == 0x25b)
                ending = 0x536ac8;
            else if (i32(cpu.edx) >= 0x258)
                ending = 0x536ad0;
            else if (cpu.ecx == 0x3e || cpu.ecx == 0x35 || at(app, 0x6fd500) == 0x15)
                ending = 0x536ad8;
            else
                ending = 0x536ae0;
            append(ending);
            cpu.eax = name;
            cpu.ebx = 0;
            cpu.edx = 0;
            if (!call(app, cpu, kLoadBank))
                return;
        }
        else
        {
            copy(kCarsDir);
            cpu.eax = name;
            if (!call(app, cpu, 0x4529a0))
                return;
            cpu.eax = cpu.edx;
            cpu.edi = name;
            if (!call(app, cpu, 0x4392b0))
                return;
            cpu.esi = cpu.eax;
            append(cpu.esi);
            cpu.edx = 0;
            cpu.eax = name;
            cpu.esi = 0x536ac0;
            cpu.edi = name;
            if (!call(app, cpu, 0x4529a0))
                return;
            append(0x536ac0);
            cpu.eax = name;
            if (!call(app, cpu, kCarBank))
                return;
        }
        // The other car: the opponent's.
        cpu.edx = at(app, 0x6fd4f4) == 0 ? 1 : 0;
        cpu.eax = cpu.edx * 12;
        cpu.edx = at(app, cpu.eax + cpu.eax * 8 + 0x6fd540);
        if (i32(cpu.edx) < 0 || i32(cpu.edx) > 0x31)
            cpu.edx = 0;
    }
    // The other car's (or the cop's) bank, as player 1's.
    if (!carArchive(true, 1) || !bar())
        return;
    if (at(app, 0x6fd3b8) == 3)
    {
        // The pursuit: the cops' sounds and their radio.
        copy(kAudioDir);
        append(at(app, 0x5525a4) != 0 ? 0x536ae8 : 0x536af0);
        cpu.edx = 5;
        cpu.eax = name;
        cpu.esi = units;
        cpu.ebx = 0;
        cpu.edi = name;
        if (!call(app, cpu, kLoadBank) || !bar())
            return;
        copy(cpu.esi);
        cpu.esi = 0x536af8;
        cpu.edi = name;
        cpu.edx = 8;
        append(0x536af8);
        cpu.ebx = 0;
        cpu.eax = name;
        if (!call(app, cpu, kLoadBank) || !bar())
            return;
    }
    // The crashes, the race's voices.
    copy(kAudioDir);
    append(at(app, 0x5525a4) != 0 ? 0x536b00 : 0x536b08);
    cpu.edx = 2;
    cpu.eax = name;
    cpu.esi = units;
    cpu.ebx = 0;
    cpu.edi = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    copy(cpu.esi);
    append(0x536b0c);
    cpu.eax = at(app, 0x6fbb4c);
    cpu.edx = 6;
    cpu.edi = name;
    cpu.esi = at(app, b + cpu.eax * 4 + 0x7e);
    cpu.ebx = 0;
    append(cpu.esi);
    cpu.eax = name;
    cpu.esi = units;
    cpu.edi = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    copy(cpu.esi);
    append(0x536b10);
    cpu.eax = at(app, 0x6fbb4c);
    cpu.edx = 7;
    cpu.edi = name;
    cpu.esi = at(app, b + cpu.eax * 4 + 0x7e);
    cpu.ebx = 0;
    append(cpu.esi);
    cpu.eax = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    // The track's ambience: by its number, its weather and night.
    cpu.ecx = at(app, 0x6fd4ac);
    if (i32(cpu.ecx) < 9)
    {
        const reg32 format = at(app, 0x5525a4) != 0 ? 0x536b14 : 0x536b20;
        if (!call(app, cpu, kSprintf, {name, format, kAudioDir, cpu.ecx}))
            return;
        reg32 more = 0;
        if (at(app, 0x6fd4cc) != 0 && at(app, 0x6fd4c8) != 0)
            more = 0x536b2c;
        else if (at(app, 0x6fd4cc) != 0)
            more = 0x536b30;
        else if (at(app, 0x6fd4c8) != 0)
            more = 0x536b34;
        if (more != 0)
        {
            cpu.esi = more;
            append(more);
        }
    }
    else if (!call(app, cpu, kSprintf, {name, 0x536b38, kAudioDir, cpu.ecx}))
        return;
    cpu.edx = 3;
    cpu.eax = name;
    cpu.esi = kAudioDir;
    cpu.ebx = 0;
    cpu.edi = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    copy(cpu.esi);
    cpu.esi = 0x536b44;
    cpu.edi = name;
    cpu.edx = 4;
    append(0x536b44);
    cpu.ebx = 0;
    cpu.eax = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    if ((byte(app, 0x55eb2f) & 1) != 0)
        return leave(cpu, kept, pushed);
    // The speech of the track: its four banks, by the track's place in the
    // four (in the units' folder, or the audio one past 7).
    // `kind`: where the code holds the track's number -- eax (0), ecx (1)
    // or esi (2) -- and how it divides it.
    auto trackSpeech = [&](reg32 format, reg32 slot, bool audioPast7, int kind) {
        const reg32 track = at(app, 0x6fd4ac);
        reg32 folder = audioPast7 ? kAudioDir : units, value = track;
        if (kind == 0)
            cpu.eax = track;
        else if (kind == 1)
            cpu.ecx = track;
        else
            cpu.esi = track;
        if (i32(track) <= 7)
        {
            folder = units;
            cpu.eax = track;
            cpu.edx = track;
            cpu.ecx = 4;
            idiv(cpu, 4);
            value = cpu.edx;
        }
        cpu.eax = name;
        if (!call(app, cpu, kSprintf, {name, format, folder, value}))
            return false;
        return load(slot) && bar();
    };
    const reg8 mode = byte(app, 0x55eb2e);
    if (((mode & 0x10) != 0 || (mode & 0x20) != 0) && at(app, 0x6fd3b8) == 3)
    {
        if (!trackSpeech(0x536b4c, 0xb, true, 0) || !trackSpeech(0x536b58, 0xc, true, 1)
            || !trackSpeech(0x536b64, 0xd, true, 2) || !trackSpeech(0x536b70, 0xe, true, 0))
            return;
        return leave(cpu, kept, pushed);
    }
    cpu.esi = units;
    cpu.edi = name;
    cpu.edx = 0xa;
    copy(units);
    cpu.esi = 0x536b7c;
    cpu.edi = name;
    cpu.ebx = 0;
    append(0x536b7c);
    cpu.eax = name;
    if (!call(app, cpu, kLoadBank) || !bar())
        return;
    if (at(app, 0x6fd49c) != 0)
    {
        // The co-driver's.
        copy(units);
        append(0x536b84);
        cpu.eax = at(app, 0x6fbb4c);
        cpu.edx = 9;
        cpu.edi = name;
        cpu.esi = at(app, b + cpu.eax * 4 + 0x7e);
        cpu.ebx = 0;
        append(cpu.esi);
        cpu.eax = name;
        if (!call(app, cpu, kLoadBank) || !bar())
            return;
    }
    if (at(app, 0x6fd3b8) != 3)
        return leave(cpu, kept, pushed);
    if (!trackSpeech(0x536b4c, 0xb, false, 2) || !trackSpeech(0x536b58, 0xc, false, 0)
        || !trackSpeech(0x536b64, 0xd, false, 1) || !trackSpeech(0x536b70, 0xe, false, 2))
        return;
    leave(cpu, kept, pushed);
}

}  // namespace snd
}  // namespace nfs3hp
