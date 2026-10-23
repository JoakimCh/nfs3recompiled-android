// The game's graphics code that never runs on the port, one DEAD(address) a
// function: native_graphics_dead.cpp makes each a stub that stops the game
// with its address, and disassemble_nfs3hp.py generates no code for it.
//
// Only what nothing calls: no call, jump or address of it in code that is
// still generated, and none in the game's data.  Code that only a branch the
// port never takes reaches (the software renderers, Direct3D) stays
// generated: sub_4bc980 calls sub_434b00 on every start, though it was
// thought to be called from nowhere.

// The software renderers' blend colour by mode (state 0x2bd).
DEAD(0x432440)
DEAD(0x4c0f60)
DEAD(0x524820)
