/* Included first into every SDL source (android/app/jni/CMakeLists.txt): SDL's
 * Android code writes to the system log directly, around SDL's own log
 * priorities, and with debug mode off the NFS III port writes nothing to the
 * log.  The header is read here, so its declarations stand; the calls after it
 * reach the log only while NFS_LOG, which the game's activity sets before SDL
 * is loaded, is not "0".  Inside its own macro the name is not expanded again,
 * so the call there is the real one. */
#ifndef NFS3HP_SDL_QUIET_H
#define NFS3HP_SDL_QUIET_H

#include <android/log.h>
#include <stdlib.h>
#include <string.h>

static inline int nfs3hp_sdl_log_on(void)
{
    static int on = -1;
    if (on < 0) {
        const char* value = getenv("NFS_LOG");
        on = !(value && strcmp(value, "0") == 0);
    }
    return on;
}

#define __android_log_print(...) (nfs3hp_sdl_log_on() ? __android_log_print(__VA_ARGS__) : 0)
#define __android_log_write(...) (nfs3hp_sdl_log_on() ? __android_log_write(__VA_ARGS__) : 0)

#endif
