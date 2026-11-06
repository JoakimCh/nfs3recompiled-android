# Joakim's NFS III: Hot Pursuit Android fork

A fork of [nfs3recompiled-android](https://github.com/ZloiKILLER/nfs3recompiled-android/)
focused on Android TV, controller customization and launcher improvements.
I use AI to help develop these changes.

- Configurable gamepad menu controls, player assignment, input testing and
  per-controller two-button pause shortcuts.
- Touch controls that follow the game's racing bindings.
- A responsive launcher with Exit, optional intro skipping and individual
  bonus-content unlocks.
- Adjustable mirror detail, opaque-rendering optimization, lightweight FPS
  display and optional detailed performance reports.

This branch incorporates upstream 0.78's fixed single-precision arithmetic,
replay diagnostics and log export. The old selectable-precision and unchecked
fast-vertex experiments have been removed. See the [changelog](docs/fork/CHANGELOG.md)
and [performance notes](docs/fork/PERFORMANCE.md) for details.

Both upstream and this fork support ARMv7 and ARM64. Fork builds are available
for either architecture or as one universal APK, with a separate package and
signing identity. You need Android 8.0 or newer, OpenGL ES 3.0 and your own game data.

[Published downloads](https://github.com/JoakimCh/nfs3recompiled-android/releases) ·
[Fork documentation](docs/fork/README.md) · [Current build status](docs/fork/BUILD_STATUS.md)

---

Original upstream README:

# NFS III: Hot Pursuit — Android

Need for Speed III: Hot Pursuit, the 1998 PC game, running natively on Android
phones.

It is not an emulator. The original Windows executable is recompiled into
portable C++ — a static recompilation, built on
[motor-dev/nfs-recompiled](https://github.com/motor-dev/nfs-recompiled) — and
the Windows and DirectX calls it makes are reimplemented on SDL3 and OpenGL
ES, and its 3dfx driver is rewritten to draw with OpenGL ES itself. This
project makes it a phone game: a launcher, touch controls, two
gamepads with split screen, vibration, widescreen races and
full-colour textures.

Network races work: phone with phone over Wi-Fi (IPX or TCP/IP), and phone
with a PC original game over TCP/IP in both directions (host and client).

The game's data comes from your own disc: its folders, a ZIP of them, or an
image of the disc (ISO or BIN/CUE), which the launcher reads directly.

<img src="screenshots/title.jpg" alt="the title screen" width="49%">
<img src="screenshots/car-select.jpg" alt="choosing a car" width="49%">
<img src="screenshots/multiplayer.jpg" alt="two phones in a network race lobby" width="49%">
<img src="screenshots/race-widescreen.jpg" alt="a widescreen race" width="49%">
<img src="screenshots/race-touch.jpg" alt="racing on the touch controls" width="49%">
<img src="screenshots/pause-menu.jpg" alt="the pause menu over a race" width="49%">
<img src="screenshots/split-screen.jpg" alt="split screen for two players" width="49%">
<img src="screenshots/race-snow.jpg" alt="a snow track with the touch controls" width="49%">


## Playing

You need:

- a device with Android 8.0 or newer, ARMv7 and ARMv8 CPU, and OpenGL ES 3.0 graphics;
- the game's data from your own copy: the original ISO or BIN\CUE dump, or the `FEDATA` and `GAMEDATA` folders of
  the 1998 retail disc.

1. Copy image or both FEDATA and GAMEDATA folders to the phone, for example to `/sdcard/YOUR_FOLDER`.
2. Install the app, open it and import that folder, or the image's `.iso` or
   `.bin`.
3. Play.

How it works, building it, and every setting: [TECHNICAL.md](TECHNICAL.md).

Need for Speed III: Hot Pursuit is the property of Electronic Arts. This
repository contains no game content.
