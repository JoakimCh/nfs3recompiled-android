# Fork notes: start here

This directory is the continuation record for Joakim's fork. GitHub replaces the
old source checkpoint ZIPs. Read this index and WORKFLOW.md before changing code;
read the relevant decision/performance entry before revisiting an old approach.
These are maintained engineering notes, not a transcript of agent activity.

## Current state

- Main includes upstream alphaG0.78 plus the ARMv7/controller work. PR #1 was
  merged as `9554781dd3975b584cfbe90085348f683a5dfef2`.
- Latest APK: **tv23**, versionCode **100**, `0.78-armv7-tv23-profile`.
  Application source: `967523605b6e8809313283083c69906b52589d58`.
- The owner reported tv22 works and approved tv23's Advanced interface.
  Do not turn that into a claim of exhaustive racing, device or LAN validation.
- ARMv7 package: `dev.nfs3hp.port.armv7tv`. Default build remains upstream ARM64.
- Advanced has pinned Unlocks / Performance / Debug tabs, independent car
  toggles and Empire City. Performance stats/overlay default off; opaque shader
  optimization defaults on and is marked Experimental.
- Controller recording is removed. Capability reports remain in gamepad setup.
- Current checks: clean Android/Compose build, seven launcher tests, individual
  unlock-bit checks and final 296-field APK resource gate passed. Earlier
  controller/native/rendering checks are recorded in the integration history.
- No APK rebuild is needed for a documentation-only update like this one.

## Where to read

| File | Use |
| --- | --- |
| [CHANGELOG.md](CHANGELOG.md) | Short release history: what changed |
| [DECISIONS.md](DECISIONS.md) | Problems, reasoning, alternatives and constraints |
| [PERFORMANCE.md](PERFORMANCE.md) | Experiments, evidence, retained/rejected approaches |
| [WORKFLOW.md](WORKFLOW.md) | Build, focused validation, signing, releases and recovery |
| [history/INTEGRATION.md](history/INTEGRATION.md) | Detailed upstream integration and tv22/tv23 verification |
| [history/SOURCE_CHECKPOINTS.md](history/SOURCE_CHECKPOINTS.md) | Original source-r1/r2/r3 checkpoint-era notes |
| [Release identities](../../tools/release_checks/) | Source commit, APK SHA256, native BuildID and checks |

## Known limits and remaining setup

tv23's interface is owner-approved; additional device/racing coverage is not
established. LAN equivalence has not been physically validated. Host timing or
shader-policy checks are not device FPS measurements.

The manual Actions release workflow is prepared, but signing secrets have **not**
been installed through this session: the GitHub connector has no secrets-write
operation and the local CLI has no GitHub credentials. Complete the two secret
entries described in WORKFLOW.md before using it. No key material is in Git.
A 4.4 KiB standalone private signing-recovery ZIP was saved separately. Download
and keep an independent private copy; it contains the original key and password.

## Maintaining these notes

After a meaningful change, update the short changelog and current status. Add a
decision only when it explains a consequential choice. For performance changes,
record the device, settings, method, evidence, outcome and limits. Use commit
links and existing reports rather than duplicate raw logs. Move old detail into
history when the start page grows; keep this page short. Record unresolved work
honestly and distinguish source changes, built APKs and owner-tested behavior.

For upstream contributions, keep fork documentation in separate commits and
select the relevant code commits. Upstream does not need to adopt this folder.
