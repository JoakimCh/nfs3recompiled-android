When I write to you about changes I want to make, then either:
* Discuss or plan the proposed changes.
* Make the changes, but stop before testing, building or publishing them to GitHub.

If I'm not explicit about which option to choose then ask me.

Only build a release / APK when I signal that I want you to and then do any relevant testing first.

If my own test was successful then ask whether to publish the changes or keep working. 
And if we have done a lot of changes then feel free to remind me that we should commit them to GitHub.

docs/fork/ is where you'll find further guidance and also where further guidance should be written if needed.

For Android workspace setup and tool versions, read docs/fork/BUILD.md and
docs/fork/WORKSPACE.md. Try the documented setup before declaring missing tools
a blocker. Setup alone does not authorize testing, building or publishing.


For a fresh context, read docs/fork/BUILD.md and docs/fork/BUILD_STATUS.md before
setting up tools. Once checks/builds are authorized, prefer the manual GitHub
workflow on the intended branch/commit: tests (default), check, or apk. Confirm
actual job/step results and the artifact's source/version; a skipped or old run
is not validation. GitHub signing secrets have been verified; never request their
values just to start a workflow. If current tools cannot dispatch, provide the
user the exact workflow link, branch and mode, then monitor their run. Do not
repeatedly probe unavailable dispatch/secret APIs or install a local SDK merely
to avoid that user click.

When a local workspace build is requested, use python3 tools/android.py rather
than reconstructing setup by hand. It bootstraps missing tools from the manifest
and applies documented proxy/CA/SDK fixes. It does not recover signing credentials;
keep those private and outside source/caches. Preserve compatible installed tools
and caches. The new automation still needs validation; see BUILD_STATUS.md. Record
newly verified runs and device feedback there and in docs/fork/releases/.
