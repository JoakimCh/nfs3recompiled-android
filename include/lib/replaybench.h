#pragma once

namespace win32 { class WinApplication; }
namespace win32::benchmark {
bool enabled();
void replayTick(WinApplication* app);
void presented(int width, int height);
}
