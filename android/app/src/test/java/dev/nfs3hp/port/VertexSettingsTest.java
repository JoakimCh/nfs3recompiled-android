package dev.nfs3hp.port;

import android.content.Intent;
import android.content.SharedPreferences;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
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
    @Test public void defaultsAndAbiSelectionPreserveTheRecommendedPaths() {
        assertEquals(VertexSettings.EXTENDED,VertexSettings.precision(p));
        assertEquals("1",VertexSettings.resolve(p,null,true).environment().get("NFS_FPU_EXTENDED"));
        p.edit().putBoolean(VertexSettings.FAST,true).commit();
        assertFalse(VertexSettings.resolve(p,null,true).fast);
        VertexSettings.select(p,VertexSettings.SINGLE);
        assertTrue(VertexSettings.resolve(p,null,true).fast);
        assertFalse(VertexSettings.resolve(p,null,false).fast);
        assertEquals("0",VertexSettings.resolve(p,null,false).environment().get("NFS_VERTEX_FAST"));
    }
    @Test public void selectingPrecisionClearsConflictsAndResetRestoresDefaults() {
        p.edit().putBoolean(DebugOptions.ENABLED,true).putBoolean("debug_fpu_double",true)
            .putBoolean("debug_fpu_float",true).putBoolean("debug_fpu_single_races",true)
            .putBoolean(VertexSettings.FAST,true).commit();
        VertexSettings.select(p,VertexSettings.SINGLE);
        assertFalse(p.contains("debug_fpu_double"));assertFalse(p.contains("debug_fpu_float"));
        assertFalse(p.contains("debug_fpu_single_races"));
        VertexSettings.Resolved v=VertexSettings.resolve(p,null,true);
        assertTrue(v.eligible);assertFalse(v.noRounding);assertFalse(v.allFloat);
        VertexSettings.reset(p);
        assertEquals(VertexSettings.EXTENDED,VertexSettings.precision(p));
        assertFalse(VertexSettings.resolve(p,null,true).fast);
        assertFalse(p.getBoolean(VertexSettings.FAST,false));
    }
    @Test public void debugOverridesAreEffectiveOnlyWhenEnabledAndIntentWins() {
        VertexSettings.select(p,VertexSettings.SINGLE);
        p.edit().putBoolean("debug_fpu_double",true).putBoolean(VertexSettings.FAST,true).commit();
        assertTrue(VertexSettings.resolve(p,null,true).fast);
        p.edit().putBoolean(DebugOptions.ENABLED,true).commit();
        assertFalse(VertexSettings.resolve(p,null,true).eligible);
        assertTrue(VertexSettings.resolve(p,null,true).description().contains("Debug override"));
        Intent launch=new Intent().putExtra("fpu_double",false).putExtra("fpu_single_races",false);
        assertTrue(VertexSettings.resolve(p,launch,true).extended);
        launch.putExtra("fpu_float",true);
        assertTrue(VertexSettings.resolve(p,launch,true).allFloat);
        assertTrue(VertexSettings.resolve(p,launch,true).fast);
        assertEquals("1",VertexSettings.resolve(p,launch,true).environment().get("NFS_FPU_FLOAT"));
    }
    @Test public void legacySinglePrecisionChoiceSurvivesUntilExplicitSelection() {
        p.edit().putBoolean(DebugOptions.ENABLED,true).putBoolean("debug_fpu_single_races",true).commit();
        assertEquals(VertexSettings.SINGLE,VertexSettings.precision(p));
        assertFalse(VertexSettings.resolve(p,null,true).extended);
        VertexSettings.select(p,VertexSettings.EXTENDED);
        assertTrue(VertexSettings.resolve(p,null,true).extended);
    }
    @Test public void backupsRoundTripNewSettingsAndOlderBackupsPreserveThem() throws Exception {
        VertexSettings.select(p,VertexSettings.SINGLE);
        p.edit().putBoolean(VertexSettings.FAST,true).commit();
        ByteArrayOutputStream bytes=new ByteArrayOutputStream();
        LauncherSettings.export(RuntimeEnvironment.getApplication(),bytes);
        assertEquals(5,new JSONObject(bytes.toString("UTF-8")).getInt("format"));
        p.edit().clear().commit();
        java.io.File root=RuntimeEnvironment.getApplication().getCacheDir();
        LauncherSettings.importFrom(RuntimeEnvironment.getApplication(),new ByteArrayInputStream(bytes.toByteArray()),root);
        assertTrue(VertexSettings.resolve(p,null,true).fast);
        for(int version=1;version<=4;version++) {
            JSONObject old=new JSONObject().put("format",version).put("settings",new JSONObject()
                .put(GamePreferences.FPS_CAP,new JSONObject().put("type","int").put("value",30)));
            LauncherSettings.importFrom(RuntimeEnvironment.getApplication(),new ByteArrayInputStream(old.toString().getBytes(StandardCharsets.UTF_8)),root);
            assertTrue(VertexSettings.resolve(p,null,true).fast);
        }
    }
    @Test public void overlayIncludesActualVertexPassCounters() {
        long[] before=new long[311],after=new long[311];
        after[1]=after[2]=2;after[3]=40_000_000;after[308]=4;after[309]=8;after[310]=2;
        assertTrue(PerformanceSession.describe(before,after).contains("fast 4.0 | compatible 2.0 | retry 1.0"));
    }
}
