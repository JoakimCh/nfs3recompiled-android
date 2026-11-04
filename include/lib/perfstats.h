#ifndef LIB_PERFSTATS_H
#define LIB_PERFSTATS_H
#include <array>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <atomic>
#if defined(__linux__)
#include <time.h>
#endif

namespace win32::perf {
// Schema v3 appends fields; all 264 v1 columns retain their indices.
enum Field : size_t {
    RaceCalls=264, QueueCalls=267, FinishCalls=270, PresentCalls=273,
    SwapCalls=276, PaceCalls=279, GameCycleCalls=282,
    AdjacentPairs=285, IdenticalPairs=286, BreakTexture=287, BreakLevels=288,
    BreakFormat=289, BreakWrap=290, BreakDepth=291, BreakBlend=292,
    BreakCull=293, BreakChroma=294, BreakClip=295, BreakFog=296, BreakGamma=297,
    BoundaryElapsed=298, BoundaryCpu=299, GlIdleCalls=300, OpaqueDraws=303, OpaqueVertices=304, ShaderSwitches=305,
    OpaqueAvailable=306, DepthStepsActive=307, VertexCompatible=308, VertexFast=309, VertexRetry=310, FieldCount=311
};
// One GL-thread update per submission/frame; the UI takes a snapshot once/sec.
// Do not reuse the game's resettable DrawCounters or touch simulation state.
enum class Level { Off, Fps, Detailed };
inline Level level() {
    static const Level value=[] {
        const auto detail=std::getenv("NFS_PERF_STATS");
        if(detail&&*detail=='1')return Level::Detailed;
        const auto fps=std::getenv("NFS_FPS_COUNTER");
        return fps&&*fps=='1'?Level::Fps:Level::Off;
    }();
    return value;
}
// FPS-only deliberately leaves enabled() false: detailed callers do no work.
inline bool enabled(){return level()==Level::Detailed;}
inline bool fpsOnly(){return level()==Level::Fps;}
struct FpsStats {
    std::atomic<uint32_t> frames{0};
    std::atomic<bool> active{true};
};
static_assert(std::atomic<uint32_t>::is_always_lock_free && std::atomic<bool>::is_always_lock_free,
              "FPS state must be lock-free");
inline FpsStats& fpsState(){static FpsStats s;return s;}
inline bool opaqueEnabled(){static const bool v=[] {auto p=std::getenv("NFS_OPAQUE_SHADER");return !p||*p!='0';}();return v;}

inline uint64_t now() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
inline uint64_t cpuNow() {
#if defined(__linux__)
    timespec t{}; if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)==0) return uint64_t(t.tv_sec)*1000000000ULL+t.tv_nsec;
#endif
    return 0; // Unsupported hosts report zero; Android uses thread CPU time.
}
struct Stats {
    std::mutex mutex;
    std::array<uint64_t,FieldCount> values{};
    std::atomic<uint64_t> epoch{0};
    uint64_t lastFrame=0;
    bool active=true;
};
inline Stats& state() { static Stats s; return s; }
inline void active(bool value) {
    const auto selected=level();
    if(selected!=Level::Detailed) {
        if(selected==Level::Fps)fpsState().active.store(value,std::memory_order_relaxed);
        return;
    }
    auto& s=state();std::lock_guard<std::mutex> l(s.mutex);
    s.active=value;s.lastFrame=0;++s.epoch;
}
inline void timing(size_t field,uint64_t elapsed,uint64_t cpu,uint64_t epoch) {
    if(!enabled())return;
    auto& s=state(); std::lock_guard<std::mutex> l(s.mutex);
    if(!s.active || s.epoch.load()!=epoch)return;
    ++s.values[field];s.values[field+1]+=elapsed;s.values[field+2]+=cpu;
}
class Scope {
    size_t field; bool measuring; uint64_t start=0,cpu=0,epoch=0;
public:
    explicit Scope(size_t f,bool condition=true):field(f),measuring(condition&&enabled()) {
        if(measuring){epoch=state().epoch.load();start=now();cpu=cpuNow();}
    }
    ~Scope(){if(measuring)timing(field,now()-start,cpuNow()-cpu,epoch);}
    Scope(const Scope&)=delete;Scope& operator=(const Scope&)=delete;
};
struct Cycle {uint64_t start=0,cpu=0,epoch=0;};
inline Cycle& cycle(){static thread_local Cycle c;return c;}
inline void gameCycleBegin(){if(enabled()){auto& c=cycle();c.epoch=state().epoch.load();c.start=now();c.cpu=cpuNow();}}
inline void gameCycleEnd(){
    if(!enabled())return;auto& c=cycle();auto end=now();
    if(c.start&&end>=c.start&&end-c.start<=1000000000ULL)
        timing(GameCycleCalls,end-c.start,cpuNow()-c.cpu,c.epoch);
    c.start=0;
}
inline void boundaries(const std::array<uint64_t,13>& counts,uint64_t elapsed,uint64_t cpu,uint64_t epoch) {
    if(!enabled())return;
    auto& s=state();std::lock_guard<std::mutex> l(s.mutex);
    if(!s.active||s.epoch.load()!=epoch)return;
    for(size_t i=0;i<counts.size();++i)s.values[AdjacentPairs+i]+=counts[i];
    s.values[BoundaryElapsed]+=elapsed;s.values[BoundaryCpu]+=cpu;
}
inline void presented(uint64_t time, unsigned width, unsigned height) {
    const auto selected=level();
    if(selected!=Level::Detailed) {
        if(selected==Level::Fps) {
            auto& s=fpsState();
            if(s.active.load(std::memory_order_relaxed)) {
                // One GL-thread producer; no read/modify/write loop or shared mutex.
                s.frames.store(s.frames.load(std::memory_order_relaxed)+1,std::memory_order_relaxed);
            }
        }
        return;
    }
    auto& s=state(); std::lock_guard<std::mutex> l(s.mutex);
    if(!s.active)return;
    ++s.values[1]; s.values[11]=width; s.values[12]=height;
    if(s.lastFrame && time>s.lastFrame) {
        const auto dt=time-s.lastFrame;
        if(dt<=1000000000ULL) { ++s.values[2]; s.values[3]+=dt; ++s.values[13+std::min<uint64_t>(250,dt/1000000)]; }
        else ++s.values[10]; // Loading/background gap: not steady frame pacing.
    }
    s.lastFrame=time;
}
inline void submitted(uint64_t batches,uint64_t draws,uint64_t vertices,uint64_t elapsed,uint64_t cpu) {
    if(!enabled())return;
    auto& s=state(); std::lock_guard<std::mutex> l(s.mutex);
    if(!s.active)return;
    s.values[4]+=batches;s.values[5]+=draws;s.values[6]+=vertices;
    ++s.values[7];s.values[8]+=elapsed;s.values[9]+=cpu;
}
inline void rendererConfig(bool available,bool depth){if(!enabled())return;auto& s=state();std::lock_guard<std::mutex> l(s.mutex);s.values[OpaqueAvailable]=available;s.values[DepthStepsActive]=depth;}
inline void opaqueUsage(uint64_t draws,uint64_t vertices,uint64_t switches){if(!enabled())return;auto& s=state();std::lock_guard<std::mutex> l(s.mutex);if(!s.active)return;s.values[OpaqueDraws]+=draws;s.values[OpaqueVertices]+=vertices;s.values[ShaderSwitches]+=switches;}
inline void vertexPass(Field field) {
    if(!enabled())return;
    auto& s=state();std::lock_guard<std::mutex> l(s.mutex);
    if(s.active)++s.values[field];
}
// Sampling time is read once/second by the UI, never on the FPS-only frame path.
inline std::array<uint64_t,2> fpsSnapshot() {
    return {now(),fpsState().frames.load(std::memory_order_relaxed)};
}
inline std::array<uint64_t,FieldCount> snapshot() {
    auto& s=state(); std::lock_guard<std::mutex> l(s.mutex);
    auto v=s.values;v[0]=now();return v;
}
}
#endif
