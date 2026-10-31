#ifndef NFS_GAMEPAD_POLICY_H
#define NFS_GAMEPAD_POLICY_H
#include <cstdint>

namespace win32 { namespace padpolicy {
// Separate press/release thresholds prevent a noisy stick from chattering.
inline bool direction(int value, bool held) { return value > (held ? 10000 : 16000); }
// Only a joystick-button binding has type 2 in its low byte.
inline std::uint32_t boundButton(std::uint32_t binding, unsigned slot)
{
    const unsigned button = (binding >> 8) & 255;
    return (binding & 255) == 2 && (binding >> 28) == slot && button < 16
        ? std::uint32_t(1) << button : 0;
}
// Match the original Controls widget's on-key handler and capture row.
// The menu's selected index is relative to its first item.
template<class Read32, class Read16>
bool controlsCapture(std::uint32_t menu, Read32 word, Read16 half) {
    if (menu < 0x6040d0 || menu >= 0x604ee0 || (menu - 0x6040d0) % 0x24) return false;
    const int first = half(menu + 0x18), selected = half(menu + 0x1a);
    const int index = first + selected;
    if (first < 0 || selected < 0 || selected == 100 || index >= 2000) return false;
    const std::uint32_t item = 0x604ee0 + index * 0xbc;
    return word(item + 0x30) == 0x43cf80 && half(item + 0x3c) >= 0;
}
struct CaptureGate {
    bool active = false;
    std::uint32_t blocked = 0;
    std::uint32_t sample(std::uint32_t down, bool capture) {
        if (capture && !active) blocked = down;
        blocked &= down;  // A held confirm must be released before it can bind.
        active = capture;
        return down & ~blocked;
    }
};
}}
#endif
