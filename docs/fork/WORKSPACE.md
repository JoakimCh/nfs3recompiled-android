# Android workspace setup

Read BUILD.md and tools/android-toolchain.json first. Reuse compatible installed
tools and existing caches. A missing JDK/SDK is a setup task, not by itself a
reason to stop an authorized build. Signing recovery stays private and outside
the repository.

The tv27 trial uses JDK 25, Gradle 9.8.2, AGP 9.5.0, NDK r30, CMake 4.4.5 and
SDL 3.4.18. tools/setup_android.py prepares SDK packages, CMake and SDL using
that manifest. It requires a JDK, curl, git and Android command-line tools.
The Gradle wrapper pins and verifies Gradle; no global Gradle is required.

These are conditional fixes observed in the restricted Linux workspace, not
requirements for ordinary development machines:

- If Java cannot load libjli.so, add JAVA_HOME/lib and JAVA_HOME/lib/server to
  LD_LIBRARY_PATH for the command. Do not downgrade Java for this loader issue.
- If /tmp is unavailable, create a workspace temp directory; set TMPDIR and
  -Djava.io.tmpdir to it. -XX:-UsePerfData avoids unused process-data files.
- Java may need the current HTTP_PROXY/HTTPS_PROXY host and port passed as
  http.proxyHost/http.proxyPort and https.proxyHost/https.proxyPort properties.
  Pass these to Gradle with -D as well as to SDK Manager. Use the configured CA
  trust store and IPv4 preference when needed; never disable TLS verification.
  Proxy ports are session-specific: never save their values in the repository.
- If an SDK install lacks source.properties at its package root, inspect its
  layout. This workspace sometimes left build-tools inside an extra android-*
  directory. Repair or reinstall that package, then validate it before building.
- After a Gradle upgrade, incompatible old test-result metadata can require
  deleting android/app/build/test-results and its test reports. Do not erase
  native .cxx or all dependency caches for a test-report format issue.
- Host GCC temporary assembler output was incomplete on one run. -pipe and
  rebuilding incomplete object files resolved it. Check compiler output before
  treating this as a source defect.

Use a modest native compilation job limit on constrained workers. The local
trial used CMAKE_JOB_POOLS=compile=2;link=1 with CMAKE_JOB_POOL_COMPILE=compile
and CMAKE_JOB_POOL_LINK=link. Adjust for available memory rather than assuming
all reported CPUs can safely compile generated game sources at once.

Run relevant checks before an authorized APK build. A compiler/toolchain
upgrade deserves controller and floating-point checks as well as the launcher
tests. On-device behavior remains a separate verification step. Keep the exact
unstripped symbols with each signed APK; tools/release/sign_android.py verifies
the certificate, ARMv7 package, resource IDs, alignment and matching BuildID.

The tv27 host vertex differential run found three trackVertices mismatches in
8,000 cases with Clang 21. The same cases and output values reproduce with the
previous NDK r28c Clang 19; this is not evidence of an r30 regression. Device
verification is still required, and this host check must not be reported as a
fully passing math suite.

The broader tv27 comparison checked 45 vertex functions, 100 cases per each of
8 FPU modes. Clang 19 and Clang 21 produced byte-for-byte identical test output:
44 functions pass, and trackVertices has the same pre-existing discrepancy.
The seven launcher tests and SDL 3.4.18 controller routing checks also passed.
These checks do not replace ARMv7 device verification.
