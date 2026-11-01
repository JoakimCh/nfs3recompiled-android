package dev.nfs3hp.port;

import android.content.Context;
import android.content.SharedPreferences;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.Map;
import org.json.JSONObject;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;

@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, application=android.app.Application.class)
public class LauncherSettingsTest {
    private Context context;
    private SharedPreferences preferences;
    private File root;
    private final String hash = "0123456789abcdef".repeat(4);
    private final String profile = "controller_profile_" + hash + "_";

    @Before public void setup() throws Exception {
        context = RuntimeEnvironment.getApplication();
        preferences = GamePreferences.get(context);
        preferences.edit().clear().commit();
        root = Files.createTempDirectory(context.getCacheDir().toPath(), "launcher-backup-").toFile();
    }

    private byte[] snapshot() throws Exception {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        LauncherSettings.export(context, out);
        return out.toByteArray();
    }

    private String restore(byte[] bytes) throws Exception {
        return LauncherSettings.importFrom(context, new ByteArrayInputStream(bytes), root);
    }

    @Test public void roundTripRestoresDisconnectedControllerSetupAndKeepsLocalReferences() throws Exception {
        preferences.edit().putString(profile+"0", "a:0:-1:0.0:1.0")
            .putString(profile+"5", "k:97").putString(profile+"race_pause_modifier", "k:108")
            .putString("input_role_"+hash, InputDeviceRoles.CONTROLLER)
            .putBoolean(GamePreferences.TOUCH_SNAP, false)
            .putFloat("touch_position_fixture_dx", 123.5f)
            .putBoolean("touch_position_fixture_from_right", true)
            .putInt(GamePreferences.FPS_CAP, 90).commit();
        GamepadSlots.assign(preferences, 0, "disconnected-pad", "My controller");
        byte[] original = snapshot();
        preferences.edit().clear().putString(GamePreferences.UI_LANGUAGE, "sv")
            .putString(GamePreferences.ACTIVE_DATA_SET_ID, "local-files")
            .putInt(GamePreferences.FPS_CAP, 30).commit();
        String backup = restore(original);
        assertEquals("k:108", preferences.getString(profile+"race_pause_modifier", ""));
        assertEquals("a:0:-1:0.0:1.0", preferences.getString(profile+"0", ""));
        assertEquals(InputDeviceRoles.CONTROLLER, preferences.getString("input_role_"+hash, ""));
        assertFalse(preferences.getBoolean(GamePreferences.TOUCH_SNAP, true));
        assertEquals(123.5f, preferences.getFloat("touch_position_fixture_dx", 0), 0);
        assertTrue(preferences.getBoolean("touch_position_fixture_from_right", false));
        assertEquals(90, preferences.getInt(GamePreferences.FPS_CAP, 0));
        assertEquals("sv", preferences.getString(GamePreferences.UI_LANGUAGE, ""));
        assertEquals("local-files", preferences.getString(GamePreferences.ACTIVE_DATA_SET_ID, ""));
        assertEquals("My controller", GamepadSlots.assignedName(preferences, 0));
        GamepadSlots.Pad other = new GamepadSlots.Pad(1, "another-pad", "My controller");
        GamepadSlots.Pad[] slots = GamepadSlots.resolve(
            new String[]{GamepadSlots.assigned(preferences, 0), ""}, Arrays.asList(other));
        assertNull(slots[0]); // Same name must not replace the saved controller.
        assertSame(other, slots[1]);
        restore(Files.readAllBytes(new File(root, ".launcher-backups/"+backup).toPath()));
        assertEquals(30, preferences.getInt(GamePreferences.FPS_CAP, 0));
        assertFalse(preferences.contains(profile+"race_pause_modifier"));
    }

    @Test public void oldBackupDoesNotClearSettingsItNeverContained() throws Exception {
        preferences.edit().putString(profile+"5", "k:109")
            .putString("input_role_"+hash, InputDeviceRoles.REMOTE)
            .putBoolean(GamePreferences.TOUCH_SNAP, false)
            .putInt(GamePreferences.FPS_CAP, 90).commit();
        GamepadSlots.assign(preferences, 0, "saved-pad", "Saved");
        JSONObject old = new JSONObject().put("format", 1).put("settings", new JSONObject()
            .put(GamePreferences.TOUCH_ENABLED, new JSONObject().put("type", "boolean").put("value", false)));
        restore(old.toString().getBytes(StandardCharsets.UTF_8));
        assertEquals("k:109", preferences.getString(profile+"5", ""));
        assertEquals(InputDeviceRoles.REMOTE, preferences.getString("input_role_"+hash, ""));
        assertEquals("saved-pad", GamepadSlots.assigned(preferences, 0));
        assertFalse(preferences.getBoolean(GamePreferences.TOUCH_SNAP, true));
        assertFalse(preferences.contains(GamePreferences.FPS_CAP));
        assertFalse(preferences.getBoolean(GamePreferences.TOUCH_ENABLED, true));
    }

    @Test public void emptySnapshotRestoresDefaultsAndCanItselfBeUndone() throws Exception {
        byte[] defaults = snapshot();
        preferences.edit().putInt(GamePreferences.FPS_CAP, 90).commit();
        String backup = restore(defaults);
        assertFalse(preferences.contains(GamePreferences.FPS_CAP));
        restore(Files.readAllBytes(new File(root, ".launcher-backups/"+backup).toPath()));
        assertEquals(90, preferences.getInt(GamePreferences.FPS_CAP, 0));
        // Importing into a default setup must also write a restorable snapshot.
        preferences.edit().clear().commit();
        assertTrue(new File(root, ".launcher-backups/"+restore(defaults)).isFile());
    }

    @Test public void malformedKnownSettingsLeaveEverythingUnchanged() throws Exception {
        preferences.edit().putInt(GamePreferences.FPS_CAP, 60).commit();
        Map<String, ?> before = preferences.getAll();
        for (JSONObject settings : Arrays.asList(
            new JSONObject().put(GamePreferences.FPS_CAP,
                new JSONObject().put("type", "string").put("value", "ninety")),
            new JSONObject().put(profile+"race_pause_modifier",
                new JSONObject().put("type", "string").put("value", "a:0:1:0.0:1.0")))) {
            byte[] bytes = new JSONObject().put("format", 2).put("settings", settings)
                .toString().getBytes(StandardCharsets.UTF_8);
            assertThrows(IOException.class, () -> restore(bytes));
            assertEquals(before, preferences.getAll());
        }
    }

    @Test public void backupFailureAbortsImport() throws Exception {
        byte[] defaults = snapshot();
        preferences.edit().putInt(GamePreferences.FPS_CAP, 90).commit();
        assertTrue(new File(root, ".launcher-backups").createNewFile());
        assertThrows(IOException.class, () -> restore(defaults));
        assertEquals(90, preferences.getInt(GamePreferences.FPS_CAP, 0));
    }
}
