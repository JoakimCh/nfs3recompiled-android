package dev.nfs3hp.port;

import android.content.SharedPreferences;
import java.io.ByteArrayInputStream;
import java.nio.charset.StandardCharsets;
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
public class VertexSettingsTest {
    private SharedPreferences p;
    @Before public void setup() {
        p=GamePreferences.get(RuntimeEnvironment.getApplication());
        p.edit().clear().commit();
    }
    @Test public void retiredArithmeticPreferencesAreClearedWithoutChangingOtherSettings() {
        p.edit().putString("race_precision","extended").putBoolean("vertex_fast",true)
            .putBoolean("debug_fpu_double",true).putBoolean("debug_fpu_float",true)
            .putBoolean("debug_fpu_single_races",true).putBoolean(DebugOptions.ENABLED,true).commit();
        VertexSettings.clearLegacy(p);
        for (String key : new String[]{"race_precision","vertex_fast","debug_fpu_double",
                "debug_fpu_float","debug_fpu_single_races"}) assertFalse(p.contains(key));
        assertTrue(p.getBoolean(DebugOptions.ENABLED,false));
    }
    @Test public void oldBackupCannotReactivateRetiredArithmeticSettings() throws Exception {
        JSONObject settings=new JSONObject()
            .put(GamePreferences.FPS_CAP,new JSONObject().put("type","int").put("value",60))
            .put("race_precision",new JSONObject().put("type","string").put("value","extended"))
            .put("vertex_fast",new JSONObject().put("type","boolean").put("value",true));
        JSONObject backup=new JSONObject().put("format",5).put("settings",settings);
        LauncherSettings.importFrom(RuntimeEnvironment.getApplication(),
            new ByteArrayInputStream(backup.toString().getBytes(StandardCharsets.UTF_8)),
            RuntimeEnvironment.getApplication().getCacheDir());
        assertEquals(60,p.getInt(GamePreferences.FPS_CAP,30));
        assertFalse(p.contains("race_precision"));
        assertFalse(p.contains("vertex_fast"));
    }
    @Test public void overlayIncludesActualVertexPassCounters() {
        long[] before=new long[311],after=new long[311];
        after[0]=40_000_000;after[1]=after[2]=2;after[3]=40_000_000;after[308]=4;after[309]=8;after[310]=2;
        assertTrue(PerformanceSession.describe(before,after,"SINGLE").contains("float 4.0 | fallback 2.0 | retry 1.0"));
    }
}
