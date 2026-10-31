> Historical record, retained from the checkpoint migration. Statements about pending builds/tests describe that point in time. Read [current status](../README.md) first.

# Unreleased source update: Advanced cleanup

2026-10-31. Source only, no APK built. Last released APK remains tv21/versionCode98. Includes source-r1 RC600U classifier and source-r2 bonus unlock switches.

Performance collection and overlay now default false consistently in Advanced, game environment and PerformanceSession. Explicit saved choices remain honored. NFS3Activity only constructs PerformanceSession when at least one is enabled, avoiding the old unconditional nativeActive(true), handler thread and pause snapshot when both are off. Existing null-guarded lifecycle calls retained. Reset performance settings clears collection/overlay/opaque preferences: off/off/on. Opaque shader optimization stays on by default.

Removed Advanced controller diagnostics panel, Record controller input toggle, Controller input report action and duplicate Save input device report button. Removed InputDiagnostics.java, its activity lifecycle/event logging hooks, SDLActivity logging callbacks and its two JNI exports. Old saved input_diagnostics preference is inert. Gamepad routing statements remain unchanged. Internal native InputTrace and host regression helpers remain for development, without an Android recorder activation/export bridge; this is not a player-facing feature. Existing input report files are not automatically deleted.

ControllerSetupActivity still offers Save input device report, backed by InputDeviceReport.java; capability reports remain available from gamepad setup. Performance report sharing, crash report, debug options and bonus unlock switches retained.

Focused source inspection/checks passed: recorder references absent from Android code; JNI recorder exports absent; all performance defaults agree; tester report entry point exists; comparison with source-r2 shows input changes remove logging calls only, preserving routing. Source-r2 bonus checks unchanged and not rerun. Android UI/Java/native compilation and device checks were NOT run for this cleanup; no APK generated. On next release run targeted Advanced/performance disabled/enabled lifecycle validation, relevant existing input checks and mandatory final APK resource consistency gate. Avoid broad unrelated tests.

## Earlier source changes

# Unreleased source update: bonus content switches

2026-10-31. Source only; no APK built. Last released APK remains tv21 / versionCode 98. Retains source-r1 RC600U classification changes.

Advanced now shows two switches: all five bonus cars and Empire City. State is read from the active dataset's actual config.dat, not launcher preferences. Partial car unlocks display the count. Turning off clears that group's unlock flags, including earned unlocks (explicitly requested by user); race results and progress counters remain untouched.

BonusContent.java validates the 0x20f0-byte size and leading size marker. Car flag byte 0x1768 uses OR/AND mask 0x1f; track flag at 0x176c is little-endian uint32 1/0. Confirmed against upstream executable cheat handler and settings serializer. ControlProfile.settingsFile is now package-visible to reuse case-insensitive dataset lookup. No controller migration changes.

Writes use a unique temporary sibling, descriptor sync, reread/byte comparison, allowed-offset verification, upper car-bit preservation check, and original-file comparison before atomic replacement. No non-atomic fallback and no backup. The launcher blocks reads/toggles while GameProcess.running or an import/export is busy, refreshes on Advanced entry and resume, and displays errors without pretending settings changed. Missing config asks user to start then close game once.

Focused verification: BonusContent.java and BonusContentCheck.java compiled with Temurin 21 using --release 8. Standalone BonusContentCheck passed: independent on/off toggles, partial state, byte-for-byte preservation of unrelated data including controller tables and result counters, unknown upper bits, idempotence, invalid/missing files and no leftover backup/temp files on successful writes. The first host test invocation failed because this environment lacks /tmp; rerun with a writable java.io.tmpdir passed. No product code change for that environment issue. Android/Compose integration not compiled or device-tested in this session. No APK, native build, rendering/input suite or symbols generated.

Next release: restore toolchain using tools/tv21; bump versionCode/tag, run targeted Advanced page check and mandatory final APK resource consistency gate. A single hardware check should confirm visibility/loading/persistence. Avoid unrelated test campaigns. Checkpoint excludes downloaded JDK and test outputs.
