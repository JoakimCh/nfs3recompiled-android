#ifndef LIB_TOUCH_INPUT_H
#define LIB_TOUCH_INPUT_H
#include <atomic>
#include <cstdint>

namespace win32::touchinput {
// One atomic word makes menu/capture/pause transitions clear held actions
// without a concurrent UI press being able to resurrect an old race input.
inline std::atomic<uint32_t>& state(){static std::atomic<uint32_t> value{0};return value;}
constexpr uint32_t Active=1u<<31, Actions=(1u<<13)-1, Generation=~(Active|Actions);
inline void active(bool racing){
    if(racing){state().fetch_or(Active);return;}
    auto old=state().load();
    for(;;){if(!(old&Active))return;auto value=(old+(1u<<13))&Generation;
        if(state().compare_exchange_weak(old,value))return;}
}
inline void set(unsigned action,bool down){
    if(action>=13)return;const auto bit=uint32_t(1)<<action;auto old=state().load();
    const auto generation=old&Generation;
    for(;;){if((old&Generation)!=generation || (down&&!(old&Active)))return;
        auto value=down?(old|bit):(old&~bit);if(state().compare_exchange_weak(old,value))return;}
}
inline uint32_t held(){auto value=state().load();return value&Active?value&Actions:0;}
inline uint32_t canonical(uint32_t binding){
    switch(binding&255){
    case 1:case 3:return binding; // Axis half / POV direction, device included.
    case 2:return (binding&0xf000ff00u)|2; // Device and button, not unused bits.
    case 4:return binding&0xff00u?(binding&0xff00u)|4:0; // DI scan, not display glyph.
    default:return 0;
    }
}
// Called on the game thread at the game's own binding evaluation points.
// The race's effective bindings already contain the game's applied edits. No
// disk cache, no fake SDL key, no device-state mutation or settings rewrite.
template<class Read32> bool matches(uint32_t binding,Read32 word){
    auto actions=held();if(!actions)return false;const auto wanted=canonical(binding);if(!wanted)return false;
    // Player one's 12 race slots plus camera/look-back function-key slots,
    // as bindPlayersControls/bindPlayerRest lay them out. The game handles
    // single/split settings selection before populating this runtime table.
    constexpr unsigned slots[13]={1,0,2,3,6,8,9,0x2e,7,0x2d,5,0xb,0xa};
    for(unsigned i=0;i<13;++i)if((actions&(1u<<i))&&canonical(word(0x79c340+4*slots[i]))==wanted)return true;
    return false;
}
}
#endif
