#ifdef NFS_RENDER_BENCHMARK
#include <lib/replaybench.h>
#include <lib/rendercapture.h>
#include <lib/winapp.h>
#include <lib/glcompat.h>
#include <game_precision.h>
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

namespace win32::benchmark {
namespace {
std::atomic<bool> ready{false};
std::atomic<unsigned> replayClock{0};
std::atomic<unsigned> carCount{0};
unsigned setting(const char* key, unsigned fallback) {
    const char* value = SDL_getenv(key);
    return value ? unsigned(SDL_strtoul(value, nullptr, 10)) : fallback;
}
std::string jsonString(const char* value) {
    std::string out = "\"";
    for (const unsigned char c : std::string(value ? value : "")) {
        if (c == '\\' || c == '"') out += '\\';
        if (c >= 32) out += char(c);
    }
    return out + "\"";
}
[[noreturn]] void fail(const char* reason) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[BENCH] %s", reason);
    std::fflush(nullptr);
    std::_Exit(3);
}
}

bool enabled() {
    static const bool on = [] {
        const char* value = SDL_getenv("NFS_BENCHMARK");
        return value && SDL_strcmp(value, "1") == 0;
    }();
    return on;
}

void replayTick(WinApplication* app) {
    if (!enabled()) return;
    replayClock.store(app->getMemory<x86::reg32>(0x7d3684), std::memory_order_relaxed);
    carCount.store(app->getMemory<x86::reg32>(0x6fd510), std::memory_order_relaxed);
    if (ready.load(std::memory_order_relaxed)) return;
    if (app->getMemory<x86::reg32>(0x6fd3a0) == 2
        && app->getMemory<x86::reg32>(0x6fd510) > 0
        && app->getMemory<x86::reg32>(0x7d3684) > 0) {
        SDL_Log("[BENCH] replay running; beginning frame warmup");
        ready.store(true, std::memory_order_release);
        capture::started();
    }
}

void presented(int width, int height) {
    if (capture::enabled()) return;
    if (!enabled() || !ready.load(std::memory_order_acquire)) return;
    static const unsigned warmup = setting("NFS_BENCH_WARMUP", 300);
    static const unsigned target = setting("NFS_BENCH_FRAMES", 300);
    static const bool finish = [] {
        const char* value = SDL_getenv("NFS_BENCH_SYNC");
        return !value || SDL_strcmp(value, "finish") == 0;
    }();
    static unsigned seen = 0;
    static Uint64 last = 0;
    static unsigned startClock = 0;
    static std::vector<double> samples = [] {
        std::vector<double> values;
        values.reserve(target);
        return values;
    }();
    if (target == 0 || width <= 0 || height <= 0) fail("invalid benchmark frame settings");
    if (finish) glFinish();
    const Uint64 now = SDL_GetTicksNS();
    ++seen;
    if (seen <= warmup || last == 0) {
        last = now;
        startClock = replayClock.load(std::memory_order_relaxed);
        return;
    }
    samples.push_back(double(now - last) / 1e6);
    last = now;
    if (samples.size() < target) return;

    // Readback and all report I/O happen after the final timing sample.
    const char* image = SDL_getenv("NFS_BENCH_IMAGE");
    std::vector<unsigned char> pixels(size_t(width) * size_t(height) * 3);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    if (glGetError() != GL_NO_ERROR) fail("OpenGL error during benchmark/readback");
    size_t lit = 0;
    for (size_t p = 0; p < pixels.size(); p += 3)
        lit += pixels[p] > 8 || pixels[p + 1] > 8 || pixels[p + 2] > 8;
    if (lit == 0) fail("benchmark produced an entirely black image");
    if (!image) fail("NFS_BENCH_IMAGE is required");
    std::ofstream picture(image, std::ios::binary);
    picture << "P6\n" << width << ' ' << height << "\n255\n";
    for (int y = height - 1; y >= 0; --y)
        picture.write(reinterpret_cast<const char*>(pixels.data() + size_t(y) * width * 3), width * 3);
    picture.close();
    if (!picture) fail("cannot write benchmark image");

    double total = 0;
    for (double sample : samples) total += sample;
    auto sorted = samples;
    std::sort(sorted.begin(), sorted.end());
    const char* path = SDL_getenv("NFS_BENCH_REPORT");
    if (!path) fail("NFS_BENCH_REPORT is required");
    std::ofstream report(path);
    report << std::setprecision(10)
        << "{\n  \"schema\": 1,\n  \"status\": \"complete\",\n"
        << "  \"workload\": \"live-replay\",\n  \"precision\": " << jsonString(nfs_precision::name) << ",\n"
        << "  \"sync\": " << jsonString(finish ? "finish" : "submit") << ",\n"
        << "  \"audio\": \"disabled\",\n  \"vsync_requested\": false,\n"
        << "  \"gl_renderer\": " << jsonString(reinterpret_cast<const char*>(glGetString(GL_RENDERER))) << ",\n"
        << "  \"gl_version\": " << jsonString(reinterpret_cast<const char*>(glGetString(GL_VERSION))) << ",\n"
        << "  \"width\": " << width << ",\n  \"height\": " << height << ",\n"
        << "  \"warmup_frames\": " << warmup << ",\n  \"measured_frames\": " << samples.size() << ",\n"
        << "  \"race_clock_start\": " << startClock << ",\n"
        << "  \"race_clock_end\": " << replayClock.load(std::memory_order_relaxed) << ",\n"
        << "  \"race_cars\": " << carCount.load(std::memory_order_relaxed) << ",\n"
        << "  \"mean_frame_ms\": " << total / samples.size() << ",\n"
        << "  \"min_frame_ms\": " << sorted.front() << ",\n  \"max_frame_ms\": " << sorted.back() << ",\n"
        << "  \"p50_frame_ms\": " << sorted[(sorted.size() - 1) / 2] << ",\n"
        << "  \"p95_frame_ms\": " << sorted[(sorted.size() * 95 + 99) / 100 - 1] << ",\n"
        << "  \"mean_fps\": " << samples.size() * 1000.0 / total << ",\n"
        << "  \"lit_pixels\": " << lit << ",\n  \"frame_ms\": [";
    for (size_t i = 0; i < samples.size(); ++i) report << (i ? "," : "") << samples[i];
    report << "]\n}\n";
    report.close();
    if (!report) fail("cannot write benchmark report");
    SDL_Log("[BENCH] complete: %zu frames, %.2f FPS", samples.size(), samples.size() * 1000.0 / total);
    // This bounded diagnostic process owns worker threads; bypass their static
    // destruction after closing output files, rather than racing their shutdown.
    std::fflush(nullptr);
    std::_Exit(0);
}
}
#endif
