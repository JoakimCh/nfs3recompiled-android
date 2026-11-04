// Run separately per instrumentation environment; cached flags match a game launch.
#include <lib/perfstats.h>
#include <cassert>
#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
    assert(argc == 2);
    const bool detailed = std::string(argv[1]) == "detailed";
    const bool fps = std::string(argv[1]) == "fps";
    using namespace win32::perf;
    assert(enabled() == detailed);
    assert(fpsOnly() == fps);
    if (detailed)
    {
        active(true);
        presented(1000000000, 640, 480);
        presented(1010000000, 640, 480);
        vertexPass(VertexCompatible);
        const auto a = snapshot();
        assert(a[1] == 2 && a[2] == 1 && a[3] == 10000000);
        assert(a[11] == 640 && a[12] == 480 && a[23] == 1);
        assert(a[VertexCompatible] == 1);
        const auto epoch = state().epoch.load();
        active(false);
        presented(1020000000, 640, 480);
        assert(snapshot()[1] == 2);
        active(true);
        timing(RaceCalls, 12, 3, epoch); // A scope spanning pause must be discarded.
        assert(snapshot()[RaceCalls] == 0);
        presented(2000000000, 640, 480);
        assert(snapshot()[1] == 3 && snapshot()[2] == 1);
    }
    else
    {
        // Prove FPS/disabled hooks never try to take the detailed collector's lock.
        // The Python caller applies a timeout so a regression fails, not hangs.
        auto& detail = state();
        std::lock_guard<std::mutex> held(detail.mutex);
        { Scope scope(RaceCalls); }
        gameCycleBegin(); gameCycleEnd();
        timing(RaceCalls, 10, 5, 0);
        submitted(2, 2, 6, 10, 5);
        std::array<uint64_t,13> counts{};counts.fill(1);
        boundaries(counts, 10, 5, 0);
        rendererConfig(true, true); opaqueUsage(2, 6, 1); vertexPass(VertexFast);
        presented(0, 640, 480);
        active(false); presented(0, 640, 480);
        active(true); presented(0, 640, 480);
        assert(fpsSnapshot()[1] == (fps ? 2u : 0u));
        for (auto value : detail.values) assert(value == 0);
        assert(detail.epoch.load() == 0);
        if (fps)
        {
            fpsState().frames.store(UINT32_MAX, std::memory_order_relaxed);
            presented(0, 640, 480);
            assert(fpsSnapshot()[1] == 0);
            std::thread producer([] { for (unsigned i = 0; i < 10000; ++i) presented(0, 640, 480); });
            for (unsigned i = 0; i < 1000; ++i) assert(fpsSnapshot()[1] <= 10000);
            producer.join();
            assert(fpsSnapshot()[1] == 10000);
        }
    }
    std::cout << "PASS " << argv[1] << '\n';
}
