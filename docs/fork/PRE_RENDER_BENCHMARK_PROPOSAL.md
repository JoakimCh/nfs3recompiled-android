# Earlier-stage rendering benchmarks — proposal

Status: discussion only. The existing fixed-command benchmark works; this
document proposes extensions without committing to an implementation.

## Goal

Measure changes to vertex processing and batching without repeatedly running
physics, AI, replay simulation or frontend code. Run a trusted game build once
to capture representative inputs, then replay those inputs through the same
production functions used by the game.

Keep the current benchmark: it isolates later renderer work and provides a
useful control when an earlier-stage optimization changes performance or images.

## Where to capture

| Boundary | Work included in replay | Main limitation |
| --- | --- | --- |
| Existing: prepared vertices and batches | Production draw submission, shaders, clears and recorded texture uploads | Vertex calculations and batch construction are already baked in |
| Before renderer batching | Renderer state handling, vertex ingestion, batch construction and downstream rendering | Game-side vertex calculations remain baked in |
| Before selected vertex helpers | Transformations and related clipping/shading work performed by those helpers | Requires their game-memory inputs and side effects; isolated calls alone do not reproduce a whole frame |
| Connected earlier-stage frame replay | Captured vertex work, subsequent batching and rendering | Most integration work; the required state boundary must be established first |

These are possible stages, not interchangeable modes that already exist.
Batching is partly in our renderer wrapper, rather than entirely in game code.
Opaque handling also spans stages: texture/vertex opacity facts are gathered
earlier, while final shader eligibility is evaluated during draw submission.

## Reuse production code

Link or invoke the real implementations instead of maintaining a separate
“pre-renderer” copy. A renderer edit should automatically affect its benchmark.
Small adapters can supply captured inputs and collect outputs; they should not
duplicate transformation, batching or shader logic.

For example, `trackVerticesWith` in `src/nfs3hp/native_vertices.cpp` reads a
camera matrix, position, colours, clipping distances, vertex data and per-vertex
records through guest memory/register state. It writes intermediate records and
updates execution state. Capturing just a vertex array would be insufficient.
Other helpers need their own dependency audit; this example does not establish
a complete input list for them.

Capture stable assets once, and record changing state and call order separately
where practical. Restore relevant memory, CPU/FPU state and resource state before
each repetition, outside the measured section. Include inputs that are both read
and written. Preserve pointer relationships and guest addresses, or explicitly
reconstruct them. Missing state must cause rejection rather than silently using
whatever the previous iteration left behind.

A broad memory snapshot could help establish feasibility, but may be large and
hide dependencies. A compact explicit format is preferable once the boundary is
understood. Neither approach should require a second implementation of the game.

## Performance and correctness

Measure CPU preparation separately from completed rendering, then measure them
together when a connected frame replay is available. Exclude capture, state
restoration, reference comparison and file I/O from the timed region. Include
allocations or conversions that the production path normally performs. Record
the workload, binary, arithmetic policy, device and timing method with results.

Use two complementary correctness checks:

- **Intermediate results:** compare transformed vertices, clipping results and
  relevant side effects. Use exact checks for discrete state and explicit
  tolerances where numerical differences are acceptable.
- **Rendered images:** retain reference/candidate images, difference images and
  error metrics. An intentional approximation needs a declared tolerance and
  visual review before acceptance.

Do not require identical batch boundaries when testing a batching optimization:
different submissions can produce equivalent output. Conversely, a matching
image alone may miss a broken intermediate result that this scene never uses.
Keep independent synthetic checks alongside recorded workloads.

Use several race sections and relevant effects rather than only the current
opening frames. Tiny isolated calls can expose arithmetic costs but may distort
cache behavior and call overhead; confirm promising results on connected frames
and eventually in the real game on ARMv7/ARM64 hardware.

## Suggested progression and open decisions

1. Capture renderer entry calls before batching, retaining the current downstream
   image checks. This expands coverage with a relatively contained boundary.
2. Audit one expensive vertex helper and build a recorded-input CPU benchmark.
   Verify that state restoration makes repeated execution independent.
3. Connect earlier work to full-frame rendering only if the isolated results
   justify the added complexity.

Before implementation, decide which optimization we want to investigate first,
which helper or API boundary exposes it, whether isolated calls are sufficient,
and which target device will supply meaningful performance measurements.
Image tolerances and the human review process remain policy decisions, not
settled quality thresholds.

Captured data can contain game assets and stays outside tracked source, as with
the existing frame captures. The main risk is expanding the harness until it
recreates most of the game. Stop at boundaries that answer a concrete performance
question, and use the live replay harness for broader effects.

See [the existing benchmark guide](RENDERER_BENCHMARK.md) for implemented tools,
commands and measurement limits.
