#ifndef NFS_INPUT_TRACE_H
#define NFS_INPUT_TRACE_H
#include <atomic>
#include <cstdint>
#include <deque>
#include <map>
#include <mutex>
#include <string>

namespace win32 {
// The game thread records SDL state. JNI only copies this buffer; it never
// dereferences a joystick or reads the slot table from the Android UI thread.
class InputTrace {
    std::atomic<bool> enabled_{false};
    mutable std::mutex mutex_;
    std::deque<std::string> lines_;
    std::map<std::string,std::string> last_;
    std::uint64_t sequence_=0, dropped_=0;
    void append(std::uint64_t ms,const std::string& text) {
        std::string clean;clean.reserve(text.size());
        for(char c:text.substr(0,4096)) { if(c=='\n')clean+="\\n";else if(c=='\r')clean+="\\r";else if(static_cast<unsigned char>(c)<32||static_cast<unsigned char>(c)>=127){static const char* hex="0123456789abcdef";clean+="\\x";clean+=hex[static_cast<unsigned char>(c)>>4];clean+=hex[static_cast<unsigned char>(c)&15];}else clean+=c; }
        lines_.push_back(std::to_string(++sequence_)+" sdl_ms="+std::to_string(ms)+" "+clean);
        if(lines_.size()>512){lines_.pop_front();++dropped_;}
    }
public:
    bool enabled() const { return enabled_.load(); }
    void active(bool value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(value){lines_.clear();last_.clear();sequence_=0;dropped_=0;}
        enabled_.store(value);
    }
    void note(std::uint64_t ms,const std::string& text) {
        if(!enabled())return;
        std::lock_guard<std::mutex> lock(mutex_);
        if(enabled())append(ms,text);
    }
    bool state(std::uint64_t ms,const std::string& channel,const std::string& signature,const std::string& detail) {
        if(!enabled())return false;
        std::lock_guard<std::mutex> lock(mutex_);
        if(!enabled())return false;
        auto old=last_.find(channel);
        if(old!=last_.end()&&old->second==signature)return false;
        last_[channel]=signature;append(ms,channel+" "+detail);return true;
    }
    std::string snapshot(std::uint64_t previous) const {
        std::lock_guard<std::mutex> lock(mutex_);
        if(sequence_==previous)return {};
        std::string out="version="+std::to_string(sequence_)+"\ndropped="+std::to_string(dropped_)+"\n";
        for(const auto& line:lines_)out+=line+'\n';
        return out;
    }
};
}
#endif
