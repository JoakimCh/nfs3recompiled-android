package dev.nfs3hp.port;

import android.content.SharedPreferences;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;

@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, application=android.app.Application.class)
public class PerformanceOverlayTest {
    private SharedPreferences p;
    @Before public void setup() {
        p=GamePreferences.get(RuntimeEnvironment.getApplication());
        p.edit().clear().commit();
    }
    @Test public void displayAndRecordingResolveToTheRequiredInstrumentation() {
        String[] modes={PerformanceSession.DISABLED,PerformanceSession.FPS,PerformanceSession.VERBOSE};
        int[] levels={PerformanceSession.OFF_LEVEL,PerformanceSession.FPS_LEVEL,PerformanceSession.DETAILED_LEVEL};
        for(int i=0;i<modes.length;i++) {
            PerformanceSession.setOverlayMode(p,modes[i]);
            p.edit().putBoolean(PerformanceSession.COLLECT,false).commit();
            assertEquals(levels[i],PerformanceSession.instrumentationLevel(p));
            p.edit().putBoolean(PerformanceSession.COLLECT,true).commit();
            assertEquals(PerformanceSession.DETAILED_LEVEL,PerformanceSession.instrumentationLevel(p));
        }
    }
    @Test public void legacyOverlayMigratesAndResetDisablesCollectionAndDisplay() {
        assertEquals(PerformanceSession.DISABLED,PerformanceSession.overlayMode(p));
        p.edit().putBoolean(PerformanceSession.OVERLAY,true).commit();
        assertEquals(PerformanceSession.VERBOSE,PerformanceSession.overlayMode(p));
        PerformanceSession.setOverlayMode(p,PerformanceSession.FPS);
        assertFalse(p.contains(PerformanceSession.OVERLAY));
        p.edit().putBoolean(PerformanceSession.COLLECT,true).putBoolean(PerformanceSession.OPAQUE,false).commit();
        PerformanceSession.reset(p);
        assertEquals(PerformanceSession.DISABLED,PerformanceSession.overlayMode(p));
        assertEquals(PerformanceSession.OFF_LEVEL,PerformanceSession.instrumentationLevel(p));
        assertTrue(p.getBoolean(PerformanceSession.OPAQUE,true));
    }
    @Test public void fpsUsesSamplingTimeForBothLightAndRecordedSnapshotsAndHandlesWrap() {
        assertEquals("60.0 FPS",PerformanceSession.describeFps(new long[]{1_000_000_000L,10},new long[]{2_000_000_000L,70}));
        long[] before=new long[311],after=new long[311];
        before[0]=1_000_000_000L;before[1]=10;after[0]=2_000_000_000L;after[1]=70;
        assertEquals("60.0 FPS",PerformanceSession.describeFps(before,after));
        assertEquals("0.0 FPS",PerformanceSession.describeFps(new long[]{1,20},new long[]{1_000_000_001L,20}));
        assertEquals("3.0 FPS",PerformanceSession.describeFps(new long[]{1,0xfffffffeL},new long[]{1_000_000_001L,1}));
    }
}
