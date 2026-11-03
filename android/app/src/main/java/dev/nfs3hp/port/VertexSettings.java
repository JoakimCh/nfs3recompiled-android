package dev.nfs3hp.port;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Process;
import java.util.LinkedHashMap;
import java.util.Map;

/** Resolve launch settings once, shared by the launcher, native environment and reports. */
final class VertexSettings {
    static final String PRECISION = "race_precision";
    static final String FAST = "vertex_fast";
    static final String EXTENDED = "extended", SINGLE = "single";

    static boolean armv7() { return !Process.is64Bit(); }

    static String precision(SharedPreferences p) {
        String selected = p.getString(PRECISION, null);
        if (SINGLE.equals(selected) || EXTENDED.equals(selected)) return selected;
        // Preserve the old Debug choice until the player selects a precision explicitly.
        return DebugOptions.enabled(p, null) && p.getBoolean("debug_fpu_single_races", false)
            ? SINGLE : EXTENDED;
    }

    static void select(SharedPreferences p, String precision) {
        p.edit().putString(PRECISION, SINGLE.equals(precision) ? SINGLE : EXTENDED)
            .remove("debug_fpu_single_races").remove("debug_fpu_double")
            .remove("debug_fpu_float").apply();
    }

    static void reset(SharedPreferences p) {
        p.edit().remove(PRECISION).remove(FAST).remove("debug_fpu_single_races")
            .remove("debug_fpu_double").remove("debug_fpu_float").apply();
    }

    private static boolean debugValue(SharedPreferences p, Intent launch, String name) {
        return launch != null && launch.hasExtra(name) ? launch.getBooleanExtra(name, false)
            : p.getBoolean("debug_" + name, false);
    }

    static Resolved resolve(SharedPreferences p, Intent launch, boolean armv7) {
        boolean debug = DebugOptions.enabled(p, launch);
        boolean allFloat = debug && debugValue(p, launch, "fpu_float");
        boolean noRounding = debug && debugValue(p, launch, "fpu_double");
        boolean single = p.contains(PRECISION) ? SINGLE.equals(precision(p))
            : debug && debugValue(p, launch, "fpu_single_races");
        if (debug && launch != null && launch.hasExtra("fpu_single_races"))
            single = launch.getBooleanExtra("fpu_single_races", false);
        boolean extended = !single && !allFloat;
        boolean eligible = allFloat || (!extended && !noRounding);
        return new Resolved(extended, noRounding, allFloat,
            armv7 && eligible && p.getBoolean(FAST, false), eligible);
    }

    static final class Resolved {
        final boolean extended, noRounding, allFloat, fast, eligible;
        Resolved(boolean extended, boolean noRounding, boolean allFloat, boolean fast, boolean eligible) {
            this.extended=extended; this.noRounding=noRounding; this.allFloat=allFloat;
            this.fast=fast; this.eligible=eligible;
        }
        String description() {
            if (allFloat) return "Float everywhere (Debug override)";
            if (noRounding) return "Single-precision rounding disabled (Debug override)";
            return extended ? "Extended" : "Original single precision";
        }
        Map<String,String> environment() {
            Map<String,String> values=new LinkedHashMap<>();
            values.put("NFS_FPU_EXTENDED", extended ? "1" : "0");
            values.put("NFS_FPU_SINGLE", noRounding ? "0" : "1");
            values.put("NFS_FPU_FLOAT", allFloat ? "1" : "0");
            values.put("NFS_VERTEX_FAST", fast ? "1" : "0");
            return values;
        }
    }
}
