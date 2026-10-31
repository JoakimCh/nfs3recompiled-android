# Project continuation

Read TESTING_POLICY.md and ARMV7_TV_BUILD.md before changing this fork.
Changes from the ARMv7 checkpoint are already applied; never reapply old patches.
Use focused existing checks for the affected behavior. Every delivered APK must
pass tools/game_checks/gamepad/check_apk_resources.py against its actual packaged
resources. Keep native symbols separate from source. Never commit private signing
keys, passwords, toolchains, build output, captures or game data supplied by users.
