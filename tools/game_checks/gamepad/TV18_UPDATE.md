# Resume: ARMv7 tv18-profile — generic hats and single menu buttons

Version95 / 0.78-armv7-tv18-profile. Optimized non-debug ARMv7, shell-profileable,
original package and signing certificate. Install over tv17. Source already
patched; never reapply history patches. No rendering/math/performance changes.

User observed Zero2 reports valid Android HAT_X/Y in button mode and X/Y in axis
mode, plus correctly named buttons. Failure was SDL mapping omitting directions
after converting Android hats into raw buttons. Generic Android hat handling now
solves this without vendor-specific code. Upstream SDL database remains untouched.

ControllerProfile.axis observes nonzero standard Android HAT_X/Y (15/16). On first
actual hat movement it selects authoritative default hat handling for all4
canonical virtual D-pad directions10..13, including diagonals/releases, combined
with named Android D-pad keys. Neutral-only joystick reports do not prematurely
claim the route. Hat authority survives pause/release to reject delayed SDL
reports; held state clears. Explicit custom directions still replace defaults.
A source axis claimed for a different custom function is excluded from its former
default direction. Default hats do not disable X/Y menu navigation; custom axis
assignments retain source-direction suppression. No SDL raw index assumptions,
VID/PID guards or model-specific repairs. Default hat directions reach the same
menu/capture/race path as configured directions; game device shape stays stable.

One gamepad button per menu function: default Confirm BUTTON_A (96), Back BUTTON_B
(97). Start/Select/DPAD_CENTER/system-Back gamepad aliases are excluded from the
Android profile's menu defaults. Custom Confirm/Back each replace their one
default. Native defaults and Java environment no longer bind Select/Start in
menus; the former racing-Escape pause-menu special case is removed. Start still
has its existing racing pause fallback and Start/Select remain distinct remappable
buttons in Capture/Race. Touch, remote/system Back behavior remains independent.
Android face authority is established by actual key reports (or explicit face
configuration), retaining SDL normalized A/B fallback before such reports.

Controls -> Gamepad test and setup: Assign changes to Cancel on its own row
while waiting, then back to Assign after completion/cancellation. No separate
Cancel assignment button. Rows use Default and Reset this gamepad to defaults.
Default Confirm/Back show named Android button + numeric code; directions show
Default: D-pad / hat / X–Y. Custom buttons show code; custom axes show signed
axis. Conflicting default button claims are explicitly labeled as assigned to
another function. Per-controller VID/PID/descriptor profiles and old assignments
are preserved. Test/capture reserves only selected pad; operate page with touch
or TV remote. Bindings apply on next game launch; no game config overwritten.

Tests pass: pure production Java profile engine (neutral hats don't claim route,
automatic hats/diagonals/hysteresis/releases, simultaneous X/Y preview, named keys,
custom source reassignment, no menu aliases, single default/custom face buttons,
isolation, serialization); actual SDL production backend (default hats despite
missing mapping, preserved X/Y, all4 menus/capture, late/conflicting SDL reports,
Start/Select quiet in Menu/Pause but captured distinctly, existing A/B/remap/two
slot/touch/repeat regressions). Signed release build, ABI/nondebug/profileable,
16KB alignment/original certificate/BuildID/JNI checks pass. Latest Java hatSeen
field and setup strings verified in APK; native object newer than source.
No physical-device UI/play test available; do not claim hardware validation.

Rebuild tools/tv18/setup.py,build.py,finish.py,package.py; pinned JDK21,Gradle9.3.1,
SDK36/buildtools36,NDK28.2.13676358,CMake3.22.1,SDL3.4.2. Kotlin incremental off.
Keep source checkpoints lean (ARCHIVE_POLICY.md); APK and exact native symbols
separate. Preserve original confidential private signing material. User previously
verified tv13 two-pad split screen. Preserve existing touch live bindings,
renderer optimizations, precise math and ARM alignment fixes. Recorder defaults
off; enable Advanced Record controller input before a new report. Native trace
includes profile snapshot, plus Android/SDL source masks for routing diagnosis.

Profile snapshot: masks0..5, held8..13, direction source suppression16..31, menu
source suppression32..47, held custom direction axis48, automatic X/Y source
suppression49..52, default hat flags53..56. Native allowMenuAxis permits default
hat + X/Y while custom mappings suppress conflicting automatic directions.
