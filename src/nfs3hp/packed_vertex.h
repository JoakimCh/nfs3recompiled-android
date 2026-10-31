#pragma once
#include <array>
#include <cstring>

namespace nfs3hp {
// The original x86 format permits vertices at two-byte aligned addresses.
// Copy from byte storage so ARM cannot assume float alignment and emit VLDR.
inline std::array<float, 3> readPackedVertex(const void* source) {
    std::array<float, 3> result;
    std::memcpy(result.data(), source, sizeof(result));
    return result;
}
}
