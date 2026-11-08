#pragma once
namespace win32 { class ThrashRenderer; }
namespace win32::capture {
struct Access;
bool enabled();
void install();
void started();
void swapped(ThrashRenderer& renderer);
int replayMain(int argc, char** argv);
}
