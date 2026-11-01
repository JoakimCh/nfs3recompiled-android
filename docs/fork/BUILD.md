# Building and signing

The selected stable toolchain is recorded in [tools/android-toolchain.json](../../tools/android-toolchain.json):
JDK 25 LTS, Gradle 9.8.2, AGP 9.5.0, Kotlin/Compose compiler 2.4.10,
Android compile SDK 37.0, build-tools 37.0.0, NDK r30 LTS
(30.0.16248370), CMake 4.4.5 and SDL 3.4.18. Target SDK stays at 36;
minimum Android version stays at 8.0. This is the tv27 toolchain trial.

Prefer current stable tools and LTS releases. Keep exact versions for the
selected build, then update them deliberately with checks and a device trial.
Compatible installed JDK 26/27 may also be used with this Gradle, but JDK 25 is
the tested default. Do not replace working tools with an older version merely
to recreate a previous assistant's machine.

On a fresh Linux x86_64 workspace, install a JDK and Android command-line tools,
set JAVA_HOME and ANDROID_HOME, and accept the SDK licenses. Then run:

```sh
python3 tools/setup_android.py --cache-dir /path/to/persistent/nfs3-build-cache
cd android
bash ./gradlew testReleaseUnitTest -Parmv7Tv -PprofileNative
bash ./gradlew assembleRelease -Parmv7Tv -PprofileNative
```

Setup installs the selected SDK packages, reuses a matching CMake or downloads
its official Linux binary with checksum verification, and fetches the pinned
SDL source. It writes only machine-specific sdk.dir/cmake.dir settings to the
ignored android/local.properties. It does not build, test, sign or publish.
Use --update-sdl only after reviewing a clean existing SDL checkout.
When updating SDL, merge its matching Android Java files too, preserving the
fork's role filtering, quiet logging and activity-recreation hook.

Keep SDK/NDK installations, the setup cache and GRADLE_USER_HOME between builds
where the runner supports it. Keep android/app/.cxx for incremental native
builds. Finalize source edits and checks before starting the long APK build.
Never commit SDKs, build caches or signing credentials. Use the Gradle wrapper
instead of installing a separate system Gradle.

Environment troubleshooting: [WORKSPACE.md](WORKSPACE.md).

Omit `-Parmv7Tv` for ARM64. `-PprofileNative` permits shell profiling without
making the APK debuggable. Statistics and the overlay are off by default.

The manual [release workflow](../../.github/workflows/armv7-release.yml) builds,
signs and uploads APKs and native symbols separately. Launcher tests are optional.
It needs two Actions secrets: `ANDROID_KEYSTORE_BASE64` and
`ANDROID_KEYSTORE_PASSWORD`. Configure them privately before using the workflow.
The private recovery ZIP contains the original keystore and password; keep it
outside the repository. Its alias is `armv7-tv-release`.

For local signing, run `python3 tools/release/sign_android.py --help` from the
repository root. The helper checks the signing identity, package and resources.
The resource check catches the stale R-class mismatch that once crashed the
controller page. Clearing `android/app/build` resolves stale generated output;
`.cxx` can usually be kept.

Tests are available when relevant, rather than as a prerequisite for every build:

- Launcher: `cd android && ./gradlew testReleaseUnitTest -Parmv7Tv`.
- Controller routing: `tools/game_checks/gamepad/run.sh SDL_SOURCE WORK_DIR`.
- Math/rendering: the existing runners under `tools/game_checks` and
  `tools/render_batch_checks`.

Keep the exact native symbols with each released APK for crash decoding.
Actions artifacts expire; retain important releases elsewhere. The current
public certificate fingerprint is
`464eab8f658b68c234e80e85f5bcb6c5a79771600ac04c0f9d5458769c27b60e`.
