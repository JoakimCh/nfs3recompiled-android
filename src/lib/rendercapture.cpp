#ifdef NFS_RENDER_BENCHMARK
#include <lib/rendercapture.h>
#include <lib/thrashrenderer.h>
#include <lib/renderer.h>
#include <lib/window.h>
#include <lib/glthread.h>
#include <lib/glcompat.h>
#include <lib/glfuncs.h>
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace win32::capture {
namespace {
using Bytes = std::vector<uint8_t>;
using U = uint32_t;
constexpr size_t maxFile = 256u * 1024 * 1024;
enum Type : U { Clear = 1, Draw = 2, Upload = 3, Release = 4, Buffer = 5 };
struct Texture { U index = 0, size = 0, levels = 0, format = 0; bool fresh = true; Bytes data; };
struct Command {
    U type = 0;
    U words[5] = {};
    Texture texture;
    std::vector<U> indices;
    std::vector<ThrashVertex> vertices;
    ThrashDraw draw{};
};
struct Frame {
    U width = 0, height = 0, number = 0;
    std::string sourceRenderer;
    std::vector<Texture> textures;
    std::vector<Command> commands;
    Bytes reference;
};
[[noreturn]] void error(const std::string& message) { throw std::runtime_error(message); }
void littleEndian() {
    const U test = 1;
    if (*reinterpret_cast<const uint8_t*>(&test) != 1 || sizeof(float) != 4)
        error("Capture v1 requires a little-endian host and 32-bit floats");
}
struct Writer {
    Bytes data;
    void raw(const void* p, size_t n) {
        if (data.size() + n > maxFile) error("Capture exceeds 256 MiB");
        if (n) { const auto* b = static_cast<const uint8_t*>(p); data.insert(data.end(), b, b + n); }
    }
    void u(U x) { raw(&x, 4); }
    void f(float x) { raw(&x, 4); }
    void bytes(const Bytes& b) { u(U(b.size())); raw(b.data(), b.size()); }
    void text(const std::string& s) { u(U(s.size())); raw(s.data(), s.size()); }
};
struct Reader {
    Bytes data;
    size_t at = 0;
    void raw(void* p, size_t n) {
        if (n > data.size() - at) error("Truncated capture");
        if (n) std::memcpy(p, data.data() + at, n);
        at += n;
    }
    U u() { U x; raw(&x, 4); return x; }
    float f() { float x; raw(&x, 4); return x; }
    U count(U maximum) { U n = u(); if (n > maximum) error("Capture count exceeds limit"); return n; }
    Bytes bytes() { Bytes b(count(U(maxFile))); raw(b.data(), b.size()); return b; }
    std::string text() { std::string s(count(4096), '\0'); raw(s.data(), s.size()); return s; }
};
void texture(Writer& w, const Texture& t) {
    w.u(t.index); w.u(t.size); w.u(t.levels); w.u(t.format); w.u(t.fresh); w.bytes(t.data);
}
Texture texture(Reader& r) {
    Texture t;
    t.index = r.count(65535); t.size = r.count(4096); t.levels = r.count(13); t.format = r.count(3);
    t.fresh = r.count(1) != 0; t.data = r.bytes();
    if (!t.size || (t.size & (t.size - 1)) || !t.levels) error("Invalid texture dimensions");
    size_t texels = 0; U side = t.size;
    for (U i = 0; i < t.levels; ++i) { if (!side) error("Invalid mip count"); texels += size_t(side) * side; side >>= 1; }
    if (texels * (t.format == TF_ARGB_8888 ? 4 : 2) != t.data.size()) error("Invalid texture byte count");
    return t;
}
void batch(Writer& w, const ThrashRenderer::Batch& b) {
    w.u(b.end); w.u(b.texture); w.u(b.levels); w.u(U(b.format));
    w.u(U(b.wrapS) | U(b.wrapT) << 1 | U(b.zTest) << 2 | U(b.zTestAlways) << 3 |
        U(b.zBuffer) << 4 | U(b.alphaBlend) << 5 | U(b.cull) << 6 | U(b.chromaKey) << 7 | U(b.opaqueAlpha) << 8);
    w.u(b.cullMode); w.u(b.clipMinX); w.u(b.clipMinY); w.u(b.clipMaxX); w.u(b.clipMaxY);
    w.f(b.gamma); w.u(U(b.fogTable));
}
ThrashRenderer::Batch batch(Reader& r) {
    ThrashRenderer::Batch b{};
    b.end = r.u(); b.texture = r.count(65535); b.levels = r.count(13); b.format = int(r.count(3));
    const U flags = r.count(511);
    b.wrapS = flags & 1; b.wrapT = flags & 2; b.zTest = flags & 4; b.zTestAlways = flags & 8;
    b.zBuffer = flags & 16; b.alphaBlend = flags & 32; b.cull = flags & 64; b.chromaKey = flags & 128;
    b.opaqueAlpha = flags & 256;
    b.cullMode = r.u(); b.clipMinX = r.u(); b.clipMinY = r.u(); b.clipMaxX = r.u(); b.clipMaxY = r.u();
    b.gamma = r.f(); b.fogTable = int(r.u());
    return b;
}
void draw(Writer& w, const Command& c) {
    const auto& d = c.draw;
    w.u(U(c.vertices.size())); w.raw(c.vertices.data(), c.vertices.size() * sizeof(ThrashVertex));
    w.u(U(d.batches.size())); for (const auto& b : d.batches) batch(w, b);
    w.u(U(d.fogTables.size())); for (const auto& table : d.fogTables) w.raw(table.data(), 64 * sizeof(float));
    for (float f : d.fogColor) w.f(f);
    w.f(d.alphaTestRef); w.u(d.chromaKeyColor); w.u(d.width); w.u(d.height);
}
void draw(Reader& r, Command& c, const Frame& frame) {
    c.vertices.resize(r.count(ThrashRenderer::s_maxVertices));
    r.raw(c.vertices.data(), c.vertices.size() * sizeof(ThrashVertex));
    auto& d = c.draw;
    const U batches = r.count(128000);
    for (U i = 0; i < batches; ++i) d.batches.push_back(batch(r));
    d.fogTables.resize(r.count(128000));
    for (auto& table : d.fogTables) r.raw(table.data(), 64 * sizeof(float));
    for (float& f : d.fogColor) f = r.f();
    d.alphaTestRef = r.f(); d.chromaKeyColor = r.u(); d.width = r.u(); d.height = r.u();
    if (d.width != frame.width || d.height != frame.height || c.vertices.size() % 3) error("Invalid draw dimensions");
    U first = 0;
    for (const auto& b : d.batches) {
        if (b.end < first || b.end > c.vertices.size() || b.end % 3 ||
            b.fogTable < 0 || size_t(b.fogTable) >= d.fogTables.size()) error("Invalid batch range or fog index");
        first = b.end;
    }
    if (first != c.vertices.size()) error("Incomplete draw batches");
    d.vertexCount = U(c.vertices.size());
}
void save(const Frame& f, const std::filesystem::path& path) {
    littleEndian(); Writer w; w.raw("NFRCP001", 8);
    w.u(f.width); w.u(f.height); w.u(f.number); w.text(f.sourceRenderer);
    w.u(U(f.textures.size())); for (const auto& t : f.textures) texture(w, t);
    w.u(U(f.commands.size()));
    for (const auto& c : f.commands) {
        w.u(c.type);
        switch (c.type) {
        case Clear: for (U v : c.words) w.u(v); break;
        case Draw: draw(w, c); break;
        case Upload: texture(w, c.texture); break;
        case Release: w.u(U(c.indices.size())); for (U index : c.indices) w.u(index); break;
        case Buffer: w.u(c.words[0]); break;
        default: error("Unknown capture command");
        }
    }
    w.bytes(f.reference);
    std::ofstream out(path, std::ios::binary); out.write(reinterpret_cast<const char*>(w.data.data()), std::streamsize(w.data.size()));
    out.close(); if (!out) error("Cannot write capture: " + path.string());
}
Frame load(const std::filesystem::path& path) {
    littleEndian(); Reader r;
    const auto n = std::filesystem::file_size(path);
    if (n > maxFile || n < 28) error("Invalid capture file size");
    r.data.resize(size_t(n)); std::ifstream in(path, std::ios::binary);
    in.read(reinterpret_cast<char*>(r.data.data()), std::streamsize(n)); if (!in) error("Cannot read capture");
    char magic[8]; r.raw(magic, 8); if (std::memcmp(magic, "NFRCP001", 8)) error("Unsupported capture version");
    Frame f; f.width = r.count(4096); f.height = r.count(4096); f.number = r.u(); f.sourceRenderer = r.text();
    if (!f.width || !f.height) error("Invalid capture dimensions");
    const U textures = r.count(8192); for (U i = 0; i < textures; ++i) f.textures.push_back(texture(r));
    const U commands = r.count(100000); f.commands.reserve(commands);
    for (U i = 0; i < commands; ++i) {
        Command c; c.type = r.u();
        switch (c.type) {
        case Clear: for (U& v : c.words) v = r.u(); break;
        case Draw: draw(r, c, f); break;
        case Upload: c.texture = texture(r); break;
        case Release: { const U count = r.count(8192); for (U k = 0; k < count; ++k) c.indices.push_back(r.count(65535)); break; }
        case Buffer: c.words[0] = r.count(2); break;
        default: error("Unknown capture command");
        }
        f.commands.push_back(std::move(c));
    }
    f.reference = r.bytes();
    if (f.reference.size() != size_t(f.width) * f.height * 4 || r.at != r.data.size()) error("Invalid reference image or trailing data");
    return f;
}
bool fullClear(const Frame& f) {
    bool cleared = false;
    for (const auto& c : f.commands) {
        if (c.type == Draw) return cleared;
        if (c.type == Clear && ((c.words[3] <= c.words[1] || c.words[4] <= c.words[2]) ||
            (!c.words[1] && !c.words[2] && c.words[3] >= f.width && c.words[4] >= f.height))) cleared = true;
    }
    return false;
}
void resources(const Frame& f) {
    std::map<U, bool> live;
    for (const auto& t : f.textures) {
        if (live.count(t.index)) error("Duplicate initial texture index");
        live[t.index] = true;
    }
    for (const auto& c : f.commands) {
        if (c.type == Upload) live[c.texture.index] = true;
        if (c.type == Release) for (U index : c.indices) live.erase(index);
        if (c.type == Draw) for (const auto& b : c.draw.batches)
            if (!live.count(b.texture)) error("Draw references a missing texture");
    }
}
void ppm(const std::filesystem::path& path, const Bytes& rgba, U width, U height) {
    std::ofstream out(path, std::ios::binary); out << "P6\n" << width << ' ' << height << "\n255\n";
    // The production blit flips GL's texture: row zero is the game's top row.
    for (size_t i = 0; i < rgba.size(); i += 4) out.write(reinterpret_cast<const char*>(rgba.data() + i), 3);
    out.close(); if (!out) error("Cannot write image: " + path.string());
}
U option(const char* name, U fallback) { const char* s = SDL_getenv(name); return s ? U(SDL_strtoul(s, nullptr, 10)) : fallback; }
std::atomic<bool> running{false};
struct Capture : ThrashRenderer::Watcher {
    std::map<U, Texture> live;
    Frame frame;
    bool recording = false;
    U seen = 0, saved = 0;
    void drawn(const ThrashDraw& d) override {
        if (!recording) return;
        Command c; c.type = Draw; c.draw = d; c.draw.vertices = nullptr;
        c.vertices.assign(d.vertices, d.vertices + d.vertexCount);
        frame.width = d.width; frame.height = d.height;
        frame.commands.push_back(std::move(c));
    }
    void uploaded(U index, U size, U levels, TextureFormat format, bool fresh, const Bytes& data) override {
        Texture t{index, size, levels, U(format), fresh, data}; live[index] = t;
        if (recording) { Command c; c.type = Upload; c.texture = std::move(t); frame.commands.push_back(std::move(c)); }
    }
    void cleared(U color, U x, U y, U xx, U yy) override {
        if (recording) { Command c; c.type = Clear; c.words[0] = color; c.words[1] = x; c.words[2] = y;
            c.words[3] = xx; c.words[4] = yy; frame.commands.push_back(std::move(c)); }
    }
    void swapped() override {}
    void rendered(U buffer) override {
        if (recording) { Command c; c.type = Buffer; c.words[0] = buffer; frame.commands.push_back(std::move(c)); }
    }
    void released(const std::vector<U>& indices) override {
        for (U index : indices) live.erase(index);
        if (recording) { Command c; c.type = Release; c.indices = indices; frame.commands.push_back(std::move(c)); }
    }
} recorder;
}

// This benchmark-only adapter calls the actual production upload/draw/clear
// implementation; it does not contain another renderer or shader copy.
struct Access {
    static Bytes read(ThrashRenderer& renderer, U width, U height, std::string* sourceRenderer = nullptr) {
        Bytes pixels(size_t(width) * height * 4);
        bool failed = false;
        glthread::post(renderer.m_renderer, [&] {
            glBindFramebuffer(GL_FRAMEBUFFER, renderer.m_framebuffer);
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { failed = true; return; }
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
            if (sourceRenderer) *sourceRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
            failed = glGetError() != GL_NO_ERROR;
        });
        glthread::finish();
        if (failed) error("OpenGL error reading render target");
        return pixels;
    }
    static void release(ThrashRenderer& r, const std::vector<U>& indices) {
        for (U index : indices) if (index < r.m_glTextures.size() && r.m_glTextures[index]) {
            glDeleteTextures(1, &r.m_glTextures[index]); r.m_glTextures[index] = 0;
        }
    }
    static void upload(ThrashRenderer& r, Texture& t, bool fresh) {
        if (fresh) release(r, {t.index});
        r.upload(t.index, t.size, t.levels, TextureFormat(t.format), t.data);
    }
    static void restore(ThrashRenderer& r, Frame& f) {
        r.m_renderer->setCurrent();
        for (auto& t : f.textures) upload(r, t, true);
        glFinish();
    }
    static void execute(ThrashRenderer& r, Frame& f) {
        for (auto& c : f.commands) switch (c.type) {
        case Clear: r.clearFrame(c.words[0], c.words[1], c.words[2], c.words[3], c.words[4]); break;
        case Draw: c.draw.vertices = c.vertices.data(); r.drawPending(c.draw); break;
        case Upload: upload(r, c.texture, c.texture.fresh); break;
        case Release: release(r, c.indices); break;
        case Buffer: r.render(c.words[0]); break;
        }
    }
    static U opaque(ThrashRenderer& r, U value) { U old = r.m_opaqueProgram; r.m_opaqueProgram = value; return old; }
};

bool enabled() { const char* value = SDL_getenv("NFS_CAPTURE_DIR"); return value && *value; }
void install() { if (enabled()) { littleEndian(); ThrashRenderer::watch(&recorder); } }
void started() { running.store(true, std::memory_order_release); }
void swapped(ThrashRenderer& renderer) {
    if (!enabled()) return;
    try {
        const U count = option("NFS_CAPTURE_FRAMES", 3), stride = option("NFS_CAPTURE_STRIDE", 120);
        if (!count || count > 100 || !stride) error("Invalid capture selection");
        auto& c = recorder;
        const std::filesystem::path folder(SDL_getenv("NFS_CAPTURE_DIR"));
        if (c.recording) {
            if (!fullClear(c.frame)) error("Captured frame does not begin with a full color/depth clear");
            resources(c.frame);
            c.frame.reference = Access::read(renderer, c.frame.width, c.frame.height, &c.frame.sourceRenderer);
            const std::string name = "frame-" + std::to_string(c.saved) + ".nfrc";
            save(c.frame, folder / name);
            ppm(folder / ("frame-" + std::to_string(c.saved) + ".reference.ppm"), c.frame.reference, c.frame.width, c.frame.height);
            ++c.saved; c.recording = false;
            SDL_Log("[CAPTURE] saved %s: %u x %u, %zu commands", name.c_str(), c.frame.width, c.frame.height, c.frame.commands.size());
            if (c.saved == count) {
                std::ofstream index(folder / "capture-index.json");
                index << "{\"schema\":1,\"frames\":[";
                for (U i = 0; i < count; ++i) index << (i ? "," : "") << "\"frame-" << i << ".nfrc\"";
                index << "]}\n"; index.close(); if (!index) error("Cannot write capture index");
                std::fflush(nullptr); std::_Exit(0);
            }
        }
        if (running.load(std::memory_order_acquire)) {
            if (c.seen >= option("NFS_BENCH_WARMUP", 300) && (c.seen - option("NFS_BENCH_WARMUP", 300)) % stride == 0) {
                c.frame = Frame{}; c.frame.number = c.seen;
                // copied texels are already in GL-ready order (including 1555).
                for (const auto& pair : c.live) c.frame.textures.push_back(pair.second);
                c.recording = true;
            }
            ++c.seen;
        }
    } catch (const std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[CAPTURE] %s", e.what()); std::fflush(nullptr); std::_Exit(3);
    }
}

int replayMain(int argc, char** argv) {
    try {
        std::string input, prefix, shader = "auto";
        U warmup = 10, iterations = 50;
        for (int i = 1; i < argc; ++i) {
            const std::string arg(argv[i]);
            if (arg == "--help") {
                std::puts("nfs_render_replay --capture FILE --output-prefix PATH [--warmup N] [--iterations N] [--shader auto|general]");
                return 0;
            }
            if (++i == argc) error("Missing option value");
            if (arg == "--capture") input = argv[i];
            else if (arg == "--output-prefix") prefix = argv[i];
            else if (arg == "--shader") shader = argv[i];
            else if (arg == "--warmup" || arg == "--iterations") {
                char* end = nullptr; const unsigned long n = std::strtoul(argv[i], &end, 10);
                if (!*argv[i] || *end || argv[i][0] == '-' || n > 100000) error("Invalid iteration count");
                (arg == "--warmup" ? warmup : iterations) = U(n);
            } else error("Unknown option: " + arg);
        }
        if (input.empty() || prefix.empty() || !iterations || (shader != "auto" && shader != "general")) error("Invalid capture, output or shader options");
        Frame frame = load(input);
        if (!fullClear(frame)) error("Frame lacks a full initial clear");
        resources(frame);
        const auto parent = std::filesystem::path(prefix).parent_path(); if (!parent.empty()) std::filesystem::create_directories(parent);
        for (const char* suffix : {".json", ".reference.ppm", ".candidate.ppm"})
            if (std::filesystem::exists(prefix + suffix)) error("Output exists; choose a new prefix");
        SDL_SetEnvironmentVariable(SDL_GetEnvironment(), "NFS_GL_THREAD", "0", true);
        SDL_SetHint(SDL_HINT_ASSERT, "always_abort");
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) error(SDL_GetError());
        MemMap::init(0, {});
        {
            Window window("NFS renderer capture", 0, 0, int(frame.width), int(frame.height));
            Renderer target(nullptr, &window); target.setVideoMode(frame.width, frame.height, 16); glthread::finish();
            ThrashRenderer renderer(&target);
            const U originalOpaque = shader == "general" ? Access::opaque(renderer, 0) : 0;
            target.setCurrent();
            const std::string device(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
            const std::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
            std::vector<double> complete, submit; complete.reserve(iterations); submit.reserve(iterations);
            for (U i = 0; i < warmup + iterations; ++i) {
                Access::restore(renderer, frame);
                const Uint64 start = SDL_GetTicksNS();
                Access::execute(renderer, frame);
                const Uint64 queued = SDL_GetTicksNS(); glFinish(); const Uint64 done = SDL_GetTicksNS();
                if (glGetError() != GL_NO_ERROR) error("OpenGL error replaying capture");
                if (i >= warmup) { complete.push_back(double(done - start) / 1e6); submit.push_back(double(queued - start) / 1e6); }
            }
            const auto pixels = Access::read(renderer, frame.width, frame.height);
            size_t different = 0; for (size_t i = 0; i < pixels.size(); ++i) different += pixels[i] != frame.reference[i];
            ppm(prefix + ".reference.ppm", frame.reference, frame.width, frame.height);
            ppm(prefix + ".candidate.ppm", pixels, frame.width, frame.height);
            double total = 0, cpuTotal = 0; for (double v : complete) total += v; for (double v : submit) cpuTotal += v;
            auto sorted = complete; std::sort(sorted.begin(), sorted.end());
            std::ofstream report(prefix + ".json");
            size_t vertices = 0, batches = 0, uploads = 0, clears = 0;
            for (const auto& c : frame.commands) {
                vertices += c.vertices.size(); batches += c.draw.batches.size();
                uploads += c.type == Upload; clears += c.type == Clear;
            }
            report << std::setprecision(10) << "{\n\"schema\":1,\"workload\":\"fixed-render-commands\",\"shader\":\"" << shader
                << "\",\"iterations\":" << iterations << ",\"warmup\":" << warmup << ",\"width\":" << frame.width
                << ",\"height\":" << frame.height << ",\"commands\":" << frame.commands.size()
                << ",\"vertices\":" << vertices << ",\"batches\":" << batches << ",\"uploads\":" << uploads << ",\"clears\":" << clears
                << ",\"gl_renderer\":" << std::quoted(device) << ",\"gl_version\":" << std::quoted(version)
                << ",\"reference_renderer\":" << std::quoted(frame.sourceRenderer)
                << ",\"initial_texture_restore_timed\":false,\"presentation_timed\":false"
                << ",\"mean_completed_ms\":" << total / iterations << ",\"mean_submit_ms\":" << cpuTotal / iterations
                << ",\"p95_completed_ms\":" << sorted[(sorted.size() * 95 + 99) / 100 - 1]
                << ",\"rgba_mismatch_bytes\":" << different << ",\"completed_ms\":[";
            for (size_t i = 0; i < complete.size(); ++i) report << (i ? "," : "") << complete[i];
            report << "]}\n"; report.close(); if (!report) error("Cannot write replay report");
            std::printf("%u iterations: %.3f ms completed, %.3f ms submitted; %zu RGBA byte differences\n", iterations, total / iterations, cpuTotal / iterations, different);
            if (shader == "general") Access::opaque(renderer, originalOpaque);
            target.clearCurrent();
        }
        glthread::release(); MemMap::fini(); SDL_Quit(); return 0;
    } catch (const std::exception& e) { std::fprintf(stderr, "Render replay failed: %s\n", e.what()); return 1; }
}
}
#endif
