# Performance experiments and evidence

This is the record to consult before proposing another optimization. CPU sample
shares overlap and are not GPU execution times or predicted FPS gains. Separate
runs are not controlled A/B comparisons. Record retained/reverted decisions even
when an experiment was unsuccessful.

| Change / investigation | Outcome | Evidence and limits |
| --- | --- | --- |
| Unlocking the 30 FPS cap | Useful on the phone | Owner found the game ran well with the cap unlocked. This is a pacing setting, not a native-code speedup. |
| Adjacent identical batch merging (tv8–tv10) | Removed in tv11 | Mostly found merge opportunities while stationary; owner saw little FPS benefit in races, including TV. Synthetic draw-count reduction was not representative of racing. |
| Set immutable vertex attributes once | Retained | Avoids repeated VAO attribute setup. No isolated device FPS gain measured. |
| Opaque shader selection (tv11 onward) | Retained, default on, Experimental | Owner reported better TV frame rate. Conservative opacity proof, fallback and host policy checks protect correctness; measured improvement magnitude is unknown. |
| Direct-double eligible vector kernels | Retained | Differential checks passed under documented exceptions; reduces per-operation FPU dispatch. No isolated whole-game TV FPS gain established. |
| Original shorter/coarser mirror | Retained for ARMv7 | Reduces scene work with a visible quality trade-off. No isolated measured gain. |
| Packed vertex/guest float access fixes | Retained for stability | Phone/TV SIGBUS evidence. Not an FPS optimization. |
| Broad projection-loop accessor conversion | Reverted | Synthetic directed-rounding edge mismatch. Do not repeat without addressing the math contract. |
| Lower render resolution | Useful diagnostic/trade-off | Historical TV windows: 1080p 22.3 FPS versus 720p 37.9 FPS; swap elapsed 26.8 versus 9.9 ms. Workloads differed, so this is not a controlled speedup claim. |
| Additional phase/boundary instrumentation | Available, off by default | Separates some CPU/elapsed/pacing costs; it adds overhead and does not directly measure GPU time. |

## What the TV reports supported

The historical tv9 profile had 5,701 samples and zero lost samples. drawPending
was 30.35% inclusive, glDrawArrays 24.80%, quadList 8.96% and rotateVectors 0.67%.
These are overlapping CPU shares across game/GL threads, not percentages to add.
A separate TV counter run showed roughly 23 FPS at 1920x1080 and 531 draws/frame.
The phone's sustained recording was 2344x1080; a 640x480 menu must not be mistaken
for race resolution. See [tv10 measurement notes](../../tools/render_batch_checks/TV10_UPDATE.md).

Resolution sensitivity and the PowerVR discard-path rationale motivated the
opaque shader. They did not prove one precise GPU bottleneck. Long swap/queue
waits can include pacing, scheduling, synchronization or GPU work. Idle-worker
wait time is not GPU idle time. Do not sum overlapping phase timers to explain
a frame. See [opaque path](../../tools/render_batch_checks/TV11_UPDATE.md).

## How to record the next experiment

Include the code commit and native BuildID; device/Android/ABI; race, camera,
resolution, details, FPS cap and enabled diagnostics; baseline and changed runs;
measurement method and raw report location; correctness checks; outcome and
whether retained. Prefer one reversible hypothesis at a time. Owner impressions
are useful, but label them as impressions. Do not request more manual profiling
unless it resolves a concrete uncertainty worth the owner's time.

No new performance experiment was run for tv23's UI change or this notes update.
