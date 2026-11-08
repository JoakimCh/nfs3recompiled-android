#ifndef NFS_GAME_PRECISION_H
#define NFS_GAME_PRECISION_H

// CMake's NFS_GAME_PRECISION selects one policy for the whole binary.
// Direct compiler/check builds default to hardware double as well.
#ifndef NFS_GAME_SINGLE_PRECISION
#define NFS_GAME_SINGLE_PRECISION 0
#endif
#if NFS_GAME_SINGLE_PRECISION != 0 && NFS_GAME_SINGLE_PRECISION != 1
#error NFS_GAME_SINGLE_PRECISION must be 0 or 1
#endif
namespace nfs_precision {
inline constexpr bool single = NFS_GAME_SINGLE_PRECISION != 0;
inline constexpr const char* name = single ? "SINGLE" : "DOUBLE";
}
#endif
