# Project continuation

Start with [docs/fork/README.md](docs/fork/README.md), then read
[WORKFLOW.md](docs/fork/WORKFLOW.md). Consult DECISIONS.md/PERFORMANCE.md before
revisiting old approaches. Keep the index and short changelog current; record
meaningful reasoning and experiment outcomes, not a transcript of every command.

The fork is the source checkpoint. Changes are already applied; do not reapply
old patches. Historical pending-test statements are not current status. Source,
build and device-test claims must remain distinct. Use the existing focused
validation policy, including the final packaged APK resource gate. Documentation
changes do not require rebuilding the APK. Keep exact symbols separate.

Never commit private signing keys, passwords, recovery ZIPs, toolchains, caches,
raw captures or user game data. Recover signing from configured Actions secrets
or an explicitly attached private recovery ZIP. Do not make new source checkpoint
ZIPs by default. Keep fork-note commits separate when preparing upstream changes.
