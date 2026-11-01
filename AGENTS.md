When I write to you about changes I want to make, then either:
* Discuss or plan the proposed changes.
* Make the changes, but stop before testing, building or publishing them to GitHub.

If I'm not explicit about which option to choose then ask me.

Only build a release / APK when I signal that I want you to and then do any relevant testing first.

If my own test was successful then ask whether to publish the changes or keep working. 
And if we have done a lot of changes then feel free to remind me that we should commit them to GitHub.

docs/fork/ is where you'll find further guidance and also where further guidance should be written if needed.

For a fresh context or workspace:

* Read docs/fork/BUILD.md and docs/fork/BUILD_STATUS.md before setting up tools.
  See docs/fork/WORKSPACE.md for recovery and troubleshooting.
* Once checks/builds are authorized, prefer the manual GitHub workflow on the
  intended branch/commit: tests (default), check, or apk. APK mode includes tests.
  Confirm actual job/step results and the artifact's source/version; a skipped
  or old run is not validation.
* GitHub signing secrets are configured and verified. Never request their values
  just to start a workflow. If current tools cannot dispatch, give the exact
  workflow link, branch and mode, then monitor the run the user starts. Do not
  repeatedly probe unavailable APIs or install an SDK merely to avoid that click.
* For a requested local build, use python3 tools/android.py. Try its documented
  setup before declaring missing tools a blocker. Reuse installed tools/caches;
  do not reconstruct setup by hand. Keep signing credentials outside source/caches.
* Record verified runs and device feedback in docs/fork/BUILD_STATUS.md and release
  metadata in docs/fork/releases/. Download useful APKs and exact symbols before
  artifact expiry; the repository currently limits retention to one day.

Setup alone does not authorize tests, builds or publication. The shared runner
passed local tests/check/APK runs; the hosted APK workflow also passed. Consult
BUILD_STATUS.md for exact evidence and remaining checks rather than relying on
chat history.
