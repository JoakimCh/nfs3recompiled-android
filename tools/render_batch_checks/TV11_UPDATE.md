# tv11-profile: proven-opaque shader path; merging removed

Version88,0.78-armv7-tv11-profile, same package/certificate. Install over tv10,
retaining game data, controls, FPS0/unlocked and the user's selected resolution.
Optimized non-debug ARMv7 release, shell-profileable. User wants normal play,
not more test/profiling rounds. No measured TV speedup is claimed for tv11.

Evidence: TV tv10 at1080p averaged22.3FPS, at720p37.9FPS in separate race windows,
with swap elapsed26.8ms->9.9ms. Workloads differ, so not all improvement can be
attributed to resolution. This supports pixel/rendering cost as a target. The
PowerVR guide explains discard can impede hidden-surface/depth processing:
https://docs.imgtec.com/starter-guides/powervr-architecture/html/topics/rules/do-not-use-discard.html
This is a candidate optimization, not proof this exact path dominated TV time.

## Eligibility proof

Track whether every supplied mip texel has alpha one at texture upload, before
1555 rotation/swizzles. RGB565 is implicitly opaque;1555 checks bit15;4444
checks top nibble;8888 checks byte3. Byte reads are unaligned-safe. Unknown or
empty data is not accepted. When a bound texture changes, its property changes
with it, respecting existing flush/upload job ordering.

At finishTriangle, after existing coordinate rebasing and combine assignment,
accumulate a batch flag: every vertex alpha255; alpha combine0 (ignores texture
alpha) or combine1 with proven texture alpha one; finite positions/UV/oow and
conservatively bounded UV/oow. Once a batch fails, further vertices need not be
classified. Reset proof at each real batch flush; vertex flags never become
guest state and Watcher/snapshot output is unchanged.

At drawPending also require chromakey OFF, valid uploaded GL texture, alpha
reference in[0,0.99], normal SRC_ALPHA/ONE_MINUS_SRC_ALPHA blend mode, and a
successfully linked opaque program. NaN/reference extremes and all uncertain
cases remain on the general program. This is intentionally conservative.

## Shader and GL state

Compile a second program from the existing shader with NFS_OPAQUE. Preprocessing
removes chromakey/manual filter and alpha-test discard instructions entirely.
Color/fog/gamma/texture math stays; output alpha explicitly1 under the proof.
For these normal-blend/alpha1 draws, disable GL_BLEND: this exactly replaces
destination as the old normal blend would. Additive and uncertain draws use
the original program and blend behavior. Restore GL_BLEND at submission end.
No transparent geometry reorder, depth/precision change or shader-depth
quantization removal. Both variants use the same selected NFS_DEPTH16 define.

Use explicit attribute locations0position/1color/2texCoord/3combine so the
immutable VAO layout works across both programs. Each program has its own
uniform locations and initialized sampler/fog-W. Per-submission uniforms are
set for each program, and program-dependent batch uniforms refreshed when
switching. Global texture/sampler/depth/cull/scissor/blend caches retain draw
order. If optional shader linking fails, use general program automatically.

Batch merging/run-selection/equality code and NFS_MERGE_BATCHES removed. One
glDrawArrays per original saved batch, as pre-tv8. Old unused preference may
remain on disk but has no effect. Keep tv8's one-time attribute setup. Boundary
diagnostic differenceMask remains for reports; no geometry is combined.

## Controls and report schema

Advanced's batching toggle replaced with Opaque shader optimization, default
ON, independent of Debug mode, applies next launch. Reset experiments restores
this default. Existing collection/overlay switches remain. Overlay removes the
merge count and appends opaque draw percentage. User can simply play normally;
no new report is requested as a condition of use.

Schema nfs3-performance-v3,308 fields: first303 fields preserved, including raw
adjacency diagnostics. Append303opaque_draws,304opaque_vertices,305shader_switches,
306opaque_program_available,307depth_steps_active. First3 are cumulative counts;
last2 are current flags, not counters. shader_switches counts per-batch program
activations (including first batch), excludes per-submission uniform setup calls.
metadata opaque_shader records requested toggle; merge_batches fixedfalse for
compatibility. Actual coverage requires report counters, not guessing from a
draw's texture format. Disabled optional shader can mean toggleoff/linkfallback;
metadata distinguishes toggleoff. Report timing categories still overlap.

## Checks

UBSan host classifier test covers1million randomized inputs, byte alignment,
all texture alpha formats including a failing last mip texel, vertex/texture
alpha combine, unknown/NaN/Inf/coordinate bounds, alpha-ref/chroma/blend/texture
fallbacks, and boundary reasons. Every accepted randomized input has alpha1
and passes the original alpha test. Counter/phase/lifecycle/disabled/concurrent
tests retained, plus new308field counters/flags. Actual Java formatter arithmetic
and308native/JNI/CSV index correspondence checked. Active merge references gone.

gles_check.py generates a focused C++ harness from VERBATIM production initGl,
compileShaders, drawPending and shader sources, using real EGL/GLES3 on Mesa
llvmpipe. It uses a small renderer holder and externally supplied synthetic
batches/vertices/textures rather than running the whole game.320 paired scenes/640 submissions,
with optimization enabled/disabled, compare bit-exact RGBA over1,310,720 pixels.
Actual optimized draw counters are checked, including zero fast draws when disabled.
Includes program switching, fog/gamma, blend/depth/scissor/wrap, chroma and alpha
fallbacks, and depth-quantization ON/OFF. No GL errors. This validates exercised
host GL paths, not TV-driver accuracy or performance. CPU policy checks and GL
tests complement each other; no full in-game device run was available.

Run from source (Linux Mesa EGL surfaceless,g++,GLES headers):
 python3 tools/render_batch_checks/gles_check.py /path/to/ndk/sysroot/usr/include
System GLES headers can be used by omitting the argument if installed.

Android release compiled, signed/aligned and package/version/nondebug/profileable/
ARMv7/certificate checked separately. Incremental AGP compileReleaseArtProfile
initially failed; deleting generated dex/ART intermediates and rebuilding fixed
it, no build-setting workaround or source behavior change required. Full native
symbols must match tv11's new BuildID. Source/keys/symbols preserved in checkpoint.

Limitations: fast-path coverage and net performance on actual TV are unknown;
per-vertex proofs, texture scans, extra program and switching introduce costs.
Conservative fallback may limit benefit. Keep simulation precision and working
packed-memory/controller fixes unchanged. Install and use normally; optional
existing report later can show actual opaque coverage without CPU profiling.
