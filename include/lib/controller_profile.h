#pragma once
#include <cstdint>
namespace win32::controllerprofile {
// One atomic snapshot: function mask[0..5], held[8..13], direction source
// buttons[16..31], menu source buttons[32..47], held axis direction[48],
// automatic axis source suppression[49..52], observed default hats[53..56].
inline int button(std::uint64_t state,unsigned index,bool menu) {
    if(index>=10 && index<=13 && (state & (1ull<<(index-10))))
        return int((state>>(8+index-10))&1);
    if(menu && (state&0x30)) {
        if(index==0)return int((state>>12)&1);
        if(index==1)return int((state>>13)&1);
        if(index==8 || index==9 || ((state>>(32+index))&1))return 0;
    }
    if((state>>(16+index))&1)return 0;
    return -1;
}
inline bool allowMenuAxis(std::uint64_t state,unsigned direction) {
    return !((state&(1ull<<direction)) && !(state&(1ull<<(53+direction))))
        && !(state&(1ull<<(49+direction)));
}
inline bool axisHeld(std::uint64_t state) { return (state&(1ull<<48))!=0; }
}
