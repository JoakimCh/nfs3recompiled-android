# Building and signing

Use JDK 21, Gradle 9.3.1, Android SDK 36, build-tools 36.0.0,
NDK 28.2.13676358 and CMake 3.22.1.

```sh
git clone --depth 1 --branch release-3.4.2 https://github.com/libsdl-org/SDL.git third_party/SDL
cd android
./gradlew assembleRelease -Parmv7Tv -PprofileNative
```

Omit `-Parmv7Tv` for ARM64. `-PprofileNative` permits shell profiling without
making the APK debuggable. Statistics and the overlay are off by default.

The manual [release workflow](../../.github/workflows/armv7-release.yml) builds,
signs and uploads APKs and native symbols separately. Launcher tests are optional.
It needs two Actions secrets: `ANDROID_KEYSTORE_BASE64` and
`ANDROID_KEYSTORE_PASSWORD`. This session could not configure those secrets.
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
