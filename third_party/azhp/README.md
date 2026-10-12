# AZHP — reference copy

Selected files of [AutoZone Hot Pursuit](https://github.com/americusmaximus/AZHP)
by Americus Maximus, MIT License (`LICENSE` here), taken at commit
`c9fd32b6c83700338c882a63443060f7094306aa` (2026-10-05) and left as they are.
They are not built: nothing in CMake or Gradle reads this folder. They are here
so the project never has to go back to AZHP.

## What AZHP is, and what it is not

AZHP reimplements the modules NFS III loads beside `nfs3.exe`: the renderers
behind the THRASH interface (the original Direct3D ones, the Modern Patch's
Direct3D 5–8 ones, a software one) and the sound driver behind iSNDdirect
(`eacsnd.dll`), on Windows and DirectX. Of `nfs3.exe` it has only the game's
side of those two interfaces, 13 functions: loading the drivers, the functions
handed to them, the sound's serve and focus handlers, the logger. There is no
Voodoo2 driver in it, and none of the game proper.

What it gave the port is names. `SYMBOLS.md` puts AZHP's names, and the EA
names it found, on the port's addresses: those 13 functions of `nfs3.exe`, 25
of eacsnd's and 42 of its globals, each checked against the generated code.
Every number AZHP names that the port uses was checked the same way against
voodoo2a and eacsnd, and the result is in two headers of the port's own:

- `src/nfs3hp/thrash.h` — the THRASH exports, `THRASH_setstate`'s states and
  values, the game's vertex, `THRASH_about`'s descriptor and its mode table, the
  window lock, the game's callbacks.
- `src/nfs3hp/isnd.h` — the iSNDdirect exports, the format and rate bits of
  caps and start, the results, eacsnd's data, the eight functions of the game
  `iSNDdirectsetfunctions` keeps.

Those headers are what the code uses. This folder is for reading.

## Where AZHP is wrong for this game

AZHP's code is a reading of the binaries, not the binaries. Where it and the
generated code disagree, the generated code is right. Found so far:

- `iSNDdirectstart`: AZHP takes the highest rate offered; eacsnd
  (`sub_a33150`) tries 22050 Hz first, then 16000, 32000, 44100 and 11025.
- `THRASH_setstate` 0x0a: AZHP's Direct3D drivers take it as blending off/on;
  voodoo2a takes it as chroma key and alpha test (`thrash.h`,
  `kTransparency*`).
- `THRASH_lockwindow`: AZHP's Direct3D 6 drivers keep a RECT after the five
  fields; voodoo2a keeps the buffer it locked there.
- The descriptor's dword at 0x74 is `TotalMemorySize` to AZHP; voodoo2a puts
  1 there.

## The files

| Path | What it is | What for |
|---|---|---|
| `AZX/RendererModule.Basic.hxx` | THRASH's constants and structures, for all of AZHP's games | The source of `thrash.h` |
| `AZX/RendererModule.Export.hxx` | The THRASH exports as AZHP declares them | Signatures |
| `AZX/RendererModule.Import.hxx` | The pointers the game keeps to them | How the game calls a driver |
| `AZX/RendererModule.Settings.hxx`, `AZX/Renderer.Basic.hxx`, `AZX/Graphics.Basic.hxx` | Pixel formats, the vertex (`RTLVX`), resolutions | The vertex and lock formats |
| `AZX/Sound.Basic.hxx`, `AZX/SoundModule.Basic.hxx`, `AZX/SoundModule.Export.hxx`, `AZX/SoundModule.Import.hxx` | iSNDdirect's constants, exports and the game's functions handed to the driver | The source of `isnd.h` |
| `AZX/Basic.hxx`, `AZX/Native.Basic.hxx`, `AZX/Mathematics.Basic.hxx` | AZHP's basic types (`u32`, `f32x3`, …) | Read the others |
| `AZX/RendererModule.cxx`, `AZX/SoundModule.cxx`, `AZX/Sound.cxx`, `AZX/AppWindow.cxx`, `AZX/Logger.cxx` and their headers | The 13 functions of `nfs3.exe` (`SYMBOLS.md`): `THRASH_opendll`, `iSNDloaddll`, the functions handed to eacsnd, `SNDcaps`, the serve and focus handlers, the window, the logger | Decompiling them in the game |
| `S.DirectSound.5.0/` | eacsnd, whole: slots, the 3D buffers, volume, rate, position, recording, serve | What eacsnd does with DirectSound, which the port's natives (`native_sound.cpp`, `native_isnd.cpp`) do without |
| `R.DirectX.5.0.A/` | `d3da.dll` 1998.08.10, the Direct3D driver NFS III shipped with | What THRASH means on the game's other driver, the seven THRASH exports the game does not call among it (`thrash.h`) |

`Sound.Module.Watcom.def` and `Renderer.Module.Watcom.def` give each export
its ordinal and its decorated name (`_THRASH_drawtri@12`).

## Left out

The Modern Patch's renderers (Direct3D 5 M, 6, 7, 8), the first Direct3D 5
driver (3DS), the software renderer (softtria, which Android does not load),
the Watcom export post-processor, JPEG, the
Visual Studio, Watcom and MSVC 6 projects, the DirectX SDK folders. None of it
reaches what the port runs; it is all at the commit above.
