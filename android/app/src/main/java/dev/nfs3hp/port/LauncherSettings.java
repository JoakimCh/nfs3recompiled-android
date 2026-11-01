package dev.nfs3hp.port;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.Uri;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Map;

/** Import/export of the launcher's own configuration as a single JSON file.
 *
 *  What travels is everything that describes how the player set the launcher up
 *  -- the touch layout down to each control's position, the control mappings,
 *  vibration, orientation, frame cap and per-controller setup. Controller
 *  identities travel unchanged: disconnected controllers keep their setup,
 *  and unrelated controllers never inherit it through a name/model guess.
 *  Installed game-data references and the interface language stay local.
 *
 *  Control positions are stored as fractions of the play area rather than
 *  pixels, so a layout built on one screen lands correctly on another -- which
 *  is what makes carrying them worth doing at all. */
final class LauncherSettings {
    private LauncherSettings() {}

    /** Bumped only if the meaning of the contents changes, not their spelling. */
    private static final int FORMAT = 3;
    private static final String FORMAT_KEY = "format", SETTINGS_KEY = "settings";
    private static final String TYPE = "type", VALUE = "value";

    /** Settings carried one by one. */
    // Version 1's whitelist stays separate so old imports do not clear new
    // controller settings or editor options that those exports never carried.
    private static final String[] KEYS = {
        GamePreferences.ORIENTATION, GamePreferences.FPS_CAP, GamePreferences.GAMMA,
        GamePreferences.BRIGHTNESS, GamePreferences.CONTRAST,
        GamePreferences.TOUCH_ENABLED, GamePreferences.TOUCH_MODE, GamePreferences.TOUCH_LAYOUT,
        GamePreferences.TOUCH_POINTER,
        GamePreferences.TOUCH_OPACITY, GamePreferences.TOUCH_SIZE,
        GamePreferences.TOUCH_AUTO_HIDE, GamePreferences.TOUCH_EDGE,
        GamePreferences.TOUCH_HIDE_SECONDS,
        // Still read from a file exported before Force Feedback had a screen of its own.
        GamePreferences.TOUCH_VIBRATION,
        GamePreferences.FORCE_FEEDBACK,
        GamePreferences.SAVES_INCLUDE_SETTINGS,
        GamePreferences.NETWORK_PORT,
    };

    /** Legacy touch geometry, retained for version 1 imports. */
    private static final String[] PREFIXES = {
        "touch_position_",
    };

    private static boolean carried(String key, int format) {
        for (String known : KEYS) if (known.equals(key)) return true;
        for (String prefix : PREFIXES) if (key.startsWith(prefix)) return true;
        if(format<3 && (key.endsWith("_race_pause_first") || key.endsWith("_race_pause_second")))return false;
        return format >= 2 && (GamePreferences.TOUCH_SNAP.equals(key)
            || controllerSetting(key));
    }

    private static boolean controllerSetting(String key) {
        return GamepadSlots.assignmentPreference(key)
            || key.matches("input_role_[0-9a-f]{64}")
            || key.matches("controller_profile_[0-9a-f]{64}_([0-5]|race_pause_modifier|race_pause_first|race_pause_second)");
    }

    static int export(Context context, Uri uri) throws IOException {
        OutputStream raw = context.getContentResolver().openOutputStream(uri, "wt");
        if (raw == null) throw new IOException(context.getString(R.string.launcher_file_open_failed));
        try (OutputStream out = raw) { return export(context, out); }
    }

    static int export(Context context, OutputStream out) throws IOException {
        JSONObject settings = new JSONObject();
        int count = 0;
        try {
            for (Map.Entry<String, ?> entry : GamePreferences.get(context).getAll().entrySet()) {
                if (!carried(entry.getKey(), FORMAT)) continue;
                JSONObject typed = describe(entry.getValue());
                if (typed == null) continue;
                settings.put(entry.getKey(), typed);
                count++;
            }
            JSONObject root = new JSONObject();
            root.put(FORMAT_KEY, FORMAT);
            root.put(SETTINGS_KEY, settings);
            out.write(root.toString(2).getBytes(StandardCharsets.UTF_8));
        } catch (JSONException malformed) {
            throw new IOException(malformed);
        }
        // An empty snapshot is useful too: importing it restores defaults.
        return count;
    }

    /** SharedPreferences keeps types, and JSON on its own cannot tell an int
     *  from a float, so each value carries its own. */
    private static JSONObject describe(Object value) throws JSONException {
        JSONObject typed = new JSONObject();
        if (value instanceof Boolean) typed.put(TYPE, "boolean").put(VALUE, value);
        else if (value instanceof Integer) typed.put(TYPE, "int").put(VALUE, value);
        else if (value instanceof Long) typed.put(TYPE, "long").put(VALUE, value);
        else if (value instanceof Float) typed.put(TYPE, "float").put(VALUE, ((Float) value).doubleValue());
        else if (value instanceof String) typed.put(TYPE, "string").put(VALUE, value);
        else return null;
        return typed;
    }

    static String importFrom(Context context, Uri uri, File dataRoot) throws IOException {
        InputStream raw = context.getContentResolver().openInputStream(uri);
        if (raw == null) throw new IOException(context.getString(R.string.launcher_file_open_failed));
        try (InputStream in = raw) { return importFrom(context, in, dataRoot); }
    }

    static String importFrom(Context context, InputStream raw, File dataRoot) throws IOException {
        JSONObject settings;
        int format;
        try {
            JSONObject root = new JSONObject(readAll(raw));
            Object version = root.opt(FORMAT_KEY);
            format = version instanceof Number ? ((Number) version).intValue() : -1;
            if (format < 1 || format > FORMAT || ((Number) version).doubleValue() != format)
                throw new IOException(context.getString(R.string.launcher_wrong_format));
            settings = root.optJSONObject(SETTINGS_KEY);
        } catch (JSONException malformed) {
            throw new IOException(context.getString(R.string.launcher_wrong_format));
        }
        if (settings == null || (format == 1 && settings.length() == 0))
            throw new IOException(context.getString(R.string.launcher_wrong_format));

        SharedPreferences preferences = GamePreferences.get(context);
        SharedPreferences.Editor edit = preferences.edit();
        /* Replace rather than merge: what the device carries afterwards is
         * exactly what the file describes, so everything carried is cleared
         * first.  Keys outside the whitelist -- the active data set, the
         * language -- are never touched either way. */
        for (String key : preferences.getAll().keySet())
            if (carried(key, format) || (format>=2 && controllerSetting(key))) edit.remove(key);

        int applied = 0;
        for (java.util.Iterator<String> keys = settings.keys(); keys.hasNext(); ) {
            String key = keys.next();
            // Only the selected schema's preferences are restored. Controller
            // hashes/descriptors are preserved exactly, including absent pads.
            if (!carried(key, format)) continue;
            JSONObject typed = settings.optJSONObject(key);
            if (typed == null || !valid(key, typed) || !apply(edit, key, typed))
                throw new IOException(context.getString(R.string.launcher_wrong_format));
            applied++;
        }
        if (applied == 0 && settings.length() != 0)
            throw new IOException(context.getString(R.string.launcher_wrong_format));

        for(java.util.Iterator<String> keys=settings.keys();keys.hasNext();) {
            String key=keys.next();
            if(format<3 || !controllerSetting(key) || !key.endsWith("_race_pause_first") && !key.endsWith("_race_pause_second"))continue;
            String prefix=key.substring(0,key.lastIndexOf("race_pause_"));
            JSONObject first=settings.optJSONObject(prefix+"race_pause_first"),second=settings.optJSONObject(prefix+"race_pause_second");
            if(first==null || second==null)throw new IOException(context.getString(R.string.launcher_wrong_format));
            String a=first.optString(VALUE),b=second.optString(VALUE);
            if(a.isEmpty() && b.isEmpty())continue;
            ControllerProfile.Binding x=ControllerProfile.Binding.decode(a),y=ControllerProfile.Binding.decode(b);
            if(x==null || y==null || x.axis || y.axis || ControllerProfile.samePauseButton(x.code,y.code))
                throw new IOException(context.getString(R.string.launcher_wrong_format));
        }
        String backup = writeBackup(context, dataRoot);
        if (!edit.commit()) throw new IOException(context.getString(R.string.launcher_restore_failed));
        InputDeviceRoles.initialize(context);
        return backup;
    }

    private static boolean valid(String key, JSONObject typed) {
        String expected;
        if (controllerSetting(key) || key.equals(GamePreferences.ORIENTATION)
                || key.equals(GamePreferences.TOUCH_MODE) || key.equals(GamePreferences.TOUCH_LAYOUT)
                || key.equals(GamePreferences.TOUCH_POINTER) || key.equals(GamePreferences.FORCE_FEEDBACK))
            expected = "string";
        else if (key.equals(GamePreferences.TOUCH_ENABLED) || key.equals(GamePreferences.TOUCH_AUTO_HIDE)
                || key.equals(GamePreferences.TOUCH_VIBRATION) || key.equals(GamePreferences.TOUCH_SNAP)
                || key.equals(GamePreferences.SAVES_INCLUDE_SETTINGS)
                || key.endsWith("_from_right") || key.endsWith("_from_bottom"))
            expected = "boolean";
        else expected = key.startsWith("touch_position_") ? "float" : "int";
        if (!expected.equals(typed.optString(TYPE))) return false;
        Object value = typed.opt(VALUE);
        if (expected.equals("boolean")) return value instanceof Boolean;
        if (expected.equals("int")) {
            if (!(value instanceof Number)) return false;
            double number = ((Number)value).doubleValue();
            return Double.isFinite(number) && number >= Integer.MIN_VALUE
                && number <= Integer.MAX_VALUE && number == Math.rint(number);
        }
        if (expected.equals("float"))
            return value instanceof Number && Float.isFinite(((Number)value).floatValue());
        if (!(value instanceof String)) return false;
        String text = (String)value;
        if (key.startsWith("input_role_"))
            return InputDeviceRoles.DEFAULT.equals(text) || InputDeviceRoles.CONTROLLER.equals(text)
                || InputDeviceRoles.REMOTE.equals(text);
        if (key.startsWith("controller_profile_")) {
            if (text.isEmpty()) return true; // Explicit default in older preferences.
            ControllerProfile.Binding binding = ControllerProfile.Binding.decode(text);
            if (binding == null) return false;
            boolean buttonOnly = key.endsWith("_4") || key.endsWith("_5")
                || key.endsWith("_race_pause_modifier") || key.endsWith("_race_pause_first") || key.endsWith("_race_pause_second");
            return !buttonOnly || !binding.axis;
        }
        return true;
    }

    /** Store only values already validated against their preference type. */
    private static boolean apply(SharedPreferences.Editor edit, String key, JSONObject typed) {
        String type = typed.optString(TYPE, "");
        switch (type) {
        case "boolean": edit.putBoolean(key, typed.optBoolean(VALUE)); return true;
        case "int":     edit.putInt(key, typed.optInt(VALUE)); return true;
        case "long":    edit.putLong(key, typed.optLong(VALUE)); return true;
        case "float":   edit.putFloat(key, clamp(key, (float) typed.optDouble(VALUE, 0))); return true;
        case "string":
            String value = typed.optString(VALUE, null);
            if (value == null) return false;
            edit.putString(key, value); return true;
        default: return false;
        }
    }

    /** Control geometry is bounded by construction -- positions are distances
     *  from the edges in layout units (fractions of the play area in older
     *  files) and sizes are multipliers -- so a file claiming otherwise is
     *  corrected rather than allowed to put a control off screen; the overlay
     *  keeps a control inside the area whatever its distance says. */
    private static float clamp(String key, float value) {
        if (Float.isNaN(value)) return 0;
        if (key.endsWith("_x") || key.endsWith("_y")) return Math.max(0f, Math.min(1f, value));
        if (key.endsWith("_dx") || key.endsWith("_dy")) return Math.max(0f, Math.min(4096f, value));
        // _hit came from a file written when a control had a touch zone of its own.
        if (key.endsWith("_size") || key.endsWith("_hit")) return Math.max(.1f, Math.min(10f, value));
        return value;
    }

    /** The launcher is also the tool used to undo a bad import, so the previous
     *  settings are written out before anything is replaced. */
    private static String writeBackup(Context context, File dataRoot) throws IOException {
        File folder = new File(dataRoot, ".launcher-backups");
        if (!folder.isDirectory() && !folder.mkdirs())
            throw new IOException(context.getString(R.string.launcher_backup_failed),
                new IOException("Could not create " + folder));
        // Defaults are a valid snapshot too, so the first import can be undone.
        String stamp = new SimpleDateFormat("yyyyMMdd-HHmmss", Locale.ROOT).format(new Date());
        File file = new File(folder, stamp + ".json");
        for (int suffix = 1; file.exists(); ++suffix) file = new File(folder, stamp + "-" + suffix + ".json");
        try (OutputStream out = new java.io.FileOutputStream(file)) { export(context, out); }
        catch (IOException failure) {
            // Never replace preferences after a failed backup write.
            if (!file.delete()) file.deleteOnExit();
            throw new IOException(context.getString(R.string.launcher_backup_failed), failure);
        }
        return file.getName();
    }

    private static String readAll(InputStream in) throws IOException {
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        byte[] chunk = new byte[16 * 1024];
        int n, total = 0;
        while ((n = in.read(chunk)) >= 0) {
            total += n;
            // A settings file is a few kilobytes; anything vastly larger is not one.
            if (total > 4 * 1024 * 1024) throw new IOException("Settings file is too large");
            buffer.write(chunk, 0, n);
        }
        return new String(buffer.toByteArray(), StandardCharsets.UTF_8);
    }
}
