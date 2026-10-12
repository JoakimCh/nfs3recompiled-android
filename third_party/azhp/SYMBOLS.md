# AZHP's names at the port's addresses

What AZHP names, put at the addresses of the port's generated code
(`src/nfs3hp/disassembly`). Every row was checked: the function starts there in
the generated code, or the data is read or written there by it. AZHP comments
an address on each function and global it reimplements; the EA names in the
last column are the ones it found in the binaries ("a.k.a.").

Generated from AZHP at `c9fd32b6c83700338c882a63443060f7094306aa` and the
port at 0.77; the status column is the port's at that point.

## nfs3.exe

AZHP's `AZX` folder is the game's side of the two interfaces: these are
functions of `nfs3.exe`, at the same addresses, so the build AZHP read is the
port's.  All thirteen are native in the port, with no generated code
(`src/nfs3hp/native_game.cpp`), under EA's names where the game's messages
give them; so are the four other functions `iSNDloaddll` hands eacsnd with
AZHP's three -- `sub_4e1a34`, `sub_4e1a64`, `sub_4e1adc` and `sub_4e1ae4`,
which AZHP leaves as `FUN_` or passes unnamed: `PrintSoundLambda`,
`TraceSoundLambda`, `TickSoundLambda` and `iSNDconvertsample` (EA's).

| Address | AZHP | EA name | AZHP file | Port |
|---|---|---|---|---|
| `sub_4f8390` | `InitializeRendererModule` | `THRASH_opendll` | `AZX/RendererModule.cxx` | native (`THRASH_opendll`) |
| `sub_4e1a00` | `StopSoundBufferLambda` |  | `AZX/SoundModule.cxx` | native (`StopSoundBufferLambda`) |
| `sub_4e1a0c` | `AcquireSoundBufferPositionLambda` |  | `AZX/SoundModule.cxx` | native (`AcquireSoundBufferPositionLambda`) |
| `sub_4e1a24` | `AcquireSoundDataLambda` |  | `AZX/SoundModule.cxx` | native (`AcquireSoundDataLambda`) |
| `sub_4e1a88` | `LogSoundLambda` | `abortmessagewrapper` | `AZX/SoundModule.cxx` | native (`abortmessagewrapper`) |
| `sub_4e1dd4` | `InitializeSoundModule` | `iSNDloaddll` | `AZX/SoundModule.cxx` | native (`iSNDloaddll`) |
| `sub_40faf0` | `Is3DSoundAvailable` |  | `AZX/Sound.cxx` | native (`Is3DSoundAvailable`) |
| `sub_4e1d48` | `SoundWindowHandler` | `audiofocushandler` | `AZX/Sound.cxx` | native (`audiofocushandler`) |
| `sub_4e21b0` | `AcquireSoundCapabilities` | `SNDcaps` | `AZX/Sound.cxx` | native (`SNDcaps`) |
| `sub_4e2234` | `SoundServeHandler` |  | `AZX/Sound.cxx` | native (`SoundServeHandler`) |
| `sub_4eba70` | `AcquireWindow` |  | `AZX/AppWindow.cxx` | native (`AcquireWindow`) |
| `sub_401010` | `Error` |  | `AZX/Logger.cxx` | native (`Error`) |
| `sub_4df6c0` | `Message` |  | `AZX/Logger.cxx` | native (`Message`) |

## eacsnd.dll

AZHP's `S.DirectSound.5.0` is eacsnd built at 0x400000; the port loads it at
0xa32800, so an AZHP address is the port's less 0x631800.  eacsnd has no
generated code in the port: its sixteen exports are the port's functions of
the same names, and the addresses are where its code was.

### Functions

| Address | AZHP | EA name | Port |
|---|---|---|---|
| `sub_a328e0` | `Message` |  | no code: eacsnd is native |
| `sub_a32948` | `AcquireAvailableSoundSlotIndex` |  | no code: eacsnd is native |
| `sub_a3297c` | `InitializeSoundSlot` | `iSNDcreateslot` | no code: eacsnd is native |
| `sub_a32b44` | `InitializeSoundSlots` |  | no code: eacsnd is native |
| `sub_a32b5c` | `InitializeSoundBuffers` |  | no code: eacsnd is native |
| `sub_a32bc4` | `AcquireVersion` | `iSNDdllversion` | native (`iSNDdllversion`) |
| `sub_a32bd8` | `SelectLambdas` | `iSNDdirectsetfunctions` | native (`iSNDdirectsetfunctions`) |
| `sub_a32c28` | `AcquireCapabilities` | `iSNDdirectcaps` | native (`iSNDdirectcaps`) |
| `sub_a33150` | `InitializeSounds` | `iSNDdirectstart, iSNDstartbuffer` | no code: eacsnd is native |
| `sub_a3382c` | `Start` | `iSNDdirectstart` | native (`iSNDdirectstart`) |
| `sub_a3387c` | `Stop` | `iSNDdirectstop` | native (`iSNDdirectstop`) |
| `sub_a338fc` | `StartRecording` | `iSNDdirectrecordstart` | native (`iSNDdirectrecordstart`) |
| `sub_a33904` | `PacketRecording` | `iSNDdirectrecordpacket` | native (`iSNDdirectrecordpacket`) |
| `sub_a3390c` | `StopRecording` | `iSNDdirectrecordstop` | native (`iSNDdirectrecordstop`) |
| `sub_a33910` | `AcquireSoundData` |  | no code: eacsnd is native |
| `sub_a339e4` | `AcquireSoundPosition` |  | no code: eacsnd is native |
| `sub_a33b24` | `Serve` | `iSNDdirectserve` | native (`iSNDdirectserve`) |
| `sub_a33dc8` | `StopSoundBuffers` |  | no code: eacsnd is native |
| `sub_a33e18` | `VolumeSoundBuffer` | `iSNDdirectvol` | native (`iSNDdirectvol`) |
| `sub_a33e68` | `PositionSoundBuffer` | `iSNDdirectpos3d` | native (`iSNDdirectpos3d`) |
| `sub_a33f0c` | `RateSoundBuffer` | `iSNDdirectrate` | native (`iSNDdirectrate`) |
| `sub_a33f4c` | `CreateSoundBuffer` | `iSNDdirectcreate3dbuf` | native (`iSNDdirectcreate3dbuf`) |
| `sub_a33fc0` | `RemoveSoundBuffer` | `iSNDdirectremovebuf` | native (`iSNDdirectremovebuf`) |
| `sub_a34014` | `PlaySoundBuffer` | `iSNDdirectplay3d` | native (`iSNDdirectplay3d`) |
| `sub_a341b0` | `StopSoundBuffer` | `iSNDdirectstopbuf` | native (`iSNDdirectstopbuf`) |

### Data

| Address | AZHP | Type | Generated code's references |
|---|---|---|---|
| `0xa3c09c` | `Instance` | `IDirectSound*` | 58 |
| `0xa3c0a0` | `Main` | `IDirectSoundBuffer*` | 42 |
| `0xa3c0a4` | `Software` | `IDirectSoundBuffer*` | 4 |
| `0xa3c0a8` | `Active` | `IDirectSoundBuffer*` | 58 |
| `0xa3c0ac` | `Listener` | `IDirectSound3DListener*` | 2 |
| `0xa3c0b0` | `IsInit` | `bool` | 28 |
| `0xa3c0b1` | `IsActive` | `bool` | 10 |
| `0xa3c0b2` | `IsLive` | `bool` | 16 |
| `0xa3c0b3` | `BlockAlignBits` | `u8` | 8 |
| `0xa3c0b4` | `BlockAlignBytes` | `u8` | 26 |
| `0xa3c0b5` | `IsEmulated` | `bool` | 12 |
| `0xa3c0b7` | `Is3D` | `bool` | 16 |
| `0xa3c0b8` | `Unk01` | `u32` | 20 |
| `0xa3c0bc` | `Unk02` | `u32` | 10 |
| `0xa3c0c0` | `CurrentWrite` | `DWORD` | 20 |
| `0xa3c0c4` | `MinimumWrite` | `DWORD` | 10 |
| `0xa3c0c8` | `Unk05` | `u32` | 12 |
| `0xa3c0cc` | `MaximumPlay` | `s32` | 38 |
| `0xa3c0d0` | `MinimumPlay` | `s32` | 4 |
| `0xa3c0d8` | `BufferSize` | `u32` | 18 |
| `0xa3c0dc` | `Unk09` | `u32` | 12 |
| `0xa3c0e0` | `Unk10` | `u32` | 10 |
| `0xa3c0e4` | `Unk11` | `u32` | 14 |
| `0xa3c0e8` | `Unk12` | `u32` | 10 |
| `0xa3c0ec` | `Unk13` | `u32` | 8 |
| `0xa3c0f0` | `Data` | `void*` | 18 |
| `0xa3c0f4` | `Size` | `DWORD` | 6 |
| `0xa3c0f8` | `Unk16` | `s32` | 22 |
| `0xa3c0fc` | `Capabilities` | `u32` | 8 |
| `0xa3c100` | `Frequency` | `u32` | 26 |
| `0xa3c104` | `AcquireData` | `SOUNDMODULEACQUIREDATALAMBDA` | 4 |
| `0xa3c108` | `StopBuffer` | `SOUNDMODULESTOPSOUNDBUFFERLAMBDA` | 6 |
| `0xa3c10c` | `Log` | `SOUNDMODULELOGMESSAGELAMBDA` | 6 |
| `0xa3c110` | `Lambda4` | `SOUNDMODULEUNKNOWN4LAMBDA` | 6 |
| `0xa3c114` | `Lambda5` | `SOUNDMODULEUNKNOWN5LAMBDA` | 4 |
| `0xa3c118` | `Lambda6` | `SOUNDMODULEUNKNOWN6LAMBDA` | 6 |
| `0xa3c11c` | `AcquireSoundBufferPosition` | `SOUNDMODULEACQUIRESOUNDBUFFERPOSITIONLAMBDA` | 4 |
| `0xa3c120` | `ConvertSoundSample` | `SOUNDMODULECONVERTSOUNDSAMPLELAMBDA` | 4 |
| `0xa3c124` | `Buffers[MAX_SOUND_BUFFER_COUNT]` | `SoundBuffer` | 16 |
| `0xa3c2a4` | `Slots[MAX_SOUND_SLOT_COUNT]` | `SoundSlot` | 10 |
| `0xa3cac4` | `Unknown1` | `u32` | 6 |
| `0xa3cac8` | `Unknown2` | `u32` | 4 |

`0xa3c0b0` is the one the port's comments call the DirectSound flag
(`isnd::kDirectSoundMade`); `0xa3c0fc`, `0xa3c100` and `0xa3c104..0xa3c120`
are `isnd::kCapsKept`, `isnd::kRate` and `isnd::kFunction*`.
