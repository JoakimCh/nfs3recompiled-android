package dev.nfs3hp.port;

import android.content.SharedPreferences;
import android.os.Process;

/** Remove obsolete experimental preferences; arithmetic is selected at build time. */
final class VertexSettings {
    static boolean armv7() { return !Process.is64Bit(); }

    static void clearLegacy(SharedPreferences preferences) {
        preferences.edit().remove("race_precision").remove("vertex_fast")
            .remove("debug_fpu_single_races").remove("debug_fpu_double")
            .remove("debug_fpu_float").apply();
    }
}
