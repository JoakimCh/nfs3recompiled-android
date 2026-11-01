# Workspace recovery and local setup

Start with [BUILD.md](BUILD.md) and [BUILD_STATUS.md](BUILD_STATUS.md). The source
repository and toolchain manifest are authoritative; chat history and a temporary
workspace are not required to reconstruct the process.

## After losing context or a workspace

1. Read AGENTS.md, these guides, and the selected branch's Git status. Preserve
   unrelated local files and edits. Identify the requested source commit.
2. For authorized checks/builds, prefer the manual GitHub workflow. Inspect current
   dispatch capabilities; if unavailable, provide the exact run link/branch/mode
   for the user. Match the completed run to the requested commit before downloading.
3. For an explicitly requested local run, invoke `python3 tools/android.py MODE`.
   The script bootstraps missing tools from the manifest and applies the fixes below.
   Keep its chosen cache between runs where possible.
4. Inspect the final summary and output reports. Preserve the signed APK, release
   metadata and matching symbols outside the disposable workspace.
5. Record a newly verified build in `docs/fork/releases/` and update BUILD_STATUS.md.
   Record device feedback separately from automated checks. Never include credentials.

## Bootstrap behavior

`tools/setup_android.py` owns installation; `tools/android.py` owns execution.
Setup by itself never authorizes tests, builds, signing or publication. The
bootstrap handles installed-tool discovery, downloads and the environment fixes
below; inspect its diagnostics before reconstructing setup manually.

- Prefer compatible installed JDKs and complete SDK/CMake installations. Otherwise
  fetch the selected JDK from Adoptium, SDK installer from Google and CMake/Ninja
  from their upstream releases. Verify the published checksums. Reuse cached tools.
- Fresh launcher tests install only Java, the SDK platform/build-tools/platform-tools
  and Gradle dependencies. `launcherTestsOnly` disables native Gradle configuration.
  Check/APK modes additionally install the NDK, selected CMake/Ninja and pinned SDL.
- Current command-line tools 23 bootstrap a native Android CLI that needs
  `/proc/self/exe`. When unavailable, use the known compatible Java installer 22.
  This fallback does not downgrade the selected SDK, build-tools, NDK or compiler.
- Keep exact selected versions in `tools/android-toolchain.json`. The Gradle wrapper
  pins and verifies Gradle. No global Gradle installation is needed.

## Observed restricted-workspace fixes

- A downloaded JDK may need its `lib` and `lib/server` in `LD_LIBRARY_PATH` to load
  `libjli.so`. Use the selected Java installation rather than switching to Java 17.
- Use a writable cache temp directory, `TMPDIR`, `-Djava.io.tmpdir` and
  `-XX:-UsePerfData` when system temporary/proc locations are unavailable.
- Derive HTTP/HTTPS proxy host and port from the current environment every time.
  Pass properties explicitly with `-D` to Gradle as well as to Java.
  Never commit ports.
- Copy the JDK trust store and import configured public CA certificates when the
  environment supplies `SSL_CERT_FILE` or `REQUESTS_CA_BUNDLE`. Keep TLS verification
  enabled. The cache holds public certificates, not signing credentials.
- If the Gradle wrapper cannot download its distribution through the Java proxy,
  fetch the exact `distributionUrl` from `android/gradle/wrapper/gradle-wrapper.properties`
  with `curl` and verify `distributionSha256Sum`. Put the verified ZIP in the
  wrapper's existing `GRADLE_USER_HOME/wrapper/dists/<distribution>/<URL hash>/`
  directory, leaving its lock files alone. The wrapper then verifies and unpacks
  it normally.
- Some SDK installs put files inside an extra `android-*` directory. Flatten only
  an unambiguous package directory with `source.properties`, refuse collisions,
  preserve root `package.xml`, then check the expected tool files.
- A separately downloaded CMake needs Ninja beside it. Use the manifest-selected
  Ninja version and checksum.
- Limit native compilation using CMake/Ninja job pools. The wrapper defaults to two
  compilation jobs and one link job; choose a larger limit only with enough memory.
- After Gradle upgrades, incompatible old test-result metadata may require removing
  `android/app/build/test-results` and corresponding test reports. Do not erase
  native `.cxx` state or all dependency caches for a report-format problem.
- Host GCC temporary assembler output was incomplete on one earlier run. `-pipe`
  and rebuilding incomplete object files resolved it; inspect diagnostics first.

## Compiler and native checks

- After Kotlin compilation reports conflicting overloads despite a single source
  declaration, inspect generated outputs and try clearing only
  `android/app/build/kotlin` and `android/app/build/intermediates/built_in_kotlinc`.
  This recovered stale compilation state without removing native caches.
- For toolchain/native math changes, run the existing gamepad and floating-point
  checks when authorized. The known `trackVertices` discrepancy and validation
  limits are recorded in BUILD_STATUS.md and releases/tv27.json.
