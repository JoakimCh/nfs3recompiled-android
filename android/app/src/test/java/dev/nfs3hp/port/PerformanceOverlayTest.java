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
        p.edit().putBoolean(PerformanceSession.COLLECT,true).putBoolean("perf_opaque_shader",false).commit();
        PerformanceSession.reset(p);
        assertEquals(PerformanceSession.DISABLED,PerformanceSession.overlayMode(p));
        assertEquals(PerformanceSession.OFF_LEVEL,PerformanceSession.instrumentationLevel(p));
        assertFalse(p.contains("perf_opaque_shader"));
    }
    @Test public void fpsUsesSamplingTimeForBothLightAndRecordedSnapshotsAndHandlesWrap() {
        assertEquals("60.0 FPS",PerformanceSession.describeFps(new long[]{1_000_000_000L,10},new long[]{2_000_000_000L,70}));
        long[] before=new long[311],after=new long[311];
        before[0]=1_000_000_000L;before[1]=10;after[0]=2_000_000_000L;after[1]=70;
        assertEquals("60.0 FPS",PerformanceSession.describeFps(before,after));
        assertEquals("0.0 FPS",PerformanceSession.describeFps(new long[]{1,20},new long[]{1_000_000_001L,20}));
        assertEquals("3.0 FPS",PerformanceSession.describeFps(new long[]{1,0xfffffffeL},new long[]{1_000_000_001L,1}));
    }
    @Test public void obsoleteOpaquePreferenceIsRemovedWithoutChangingCollection() {
        p.edit().putBoolean("perf_opaque_shader",false).putBoolean(PerformanceSession.COLLECT,true).commit();
        PerformanceSession.clearLegacySettings(p);
        assertFalse(p.contains("perf_opaque_shader"));
        assertTrue(p.getBoolean(PerformanceSession.COLLECT,false));
    }
    @Test public void verboseUsesRealWindowFpsAndNamesDoublePasses() {
        long[] a=new long[311],b=new long[311];
        a[0]=1_000_000_000L;b[0]=3_000_000_000L;
        b[1]=60;b[2]=60;b[3]=1_000_000_000L;b[13+16]=60;
        b[5]=600;b[303]=450;b[306]=1;b[308]=120;
        b[11]=1280;b[12]=720;
        String text=PerformanceSession.describe(a,b,"DOUBLE");
        assertTrue(text.startsWith("30.0 FPS | frame 16.7 ms | p95 <17 ms"));
        assertTrue(text.contains("10 draws/frame | opaque 75% | 1280×720"));
        assertTrue(text.contains("DOUBLE | vertex double passes 2.0/frame"));
        assertFalse(text.contains("retry"));
        assertFalse(text.contains("compatible"));
    }
    @Test public void verboseHandlesIdleAndShowsActualShaderAndSingleRetryState() {
        long[] a=new long[311],b=new long[311];a[0]=1;b[0]=1_000_000_001L;
        assertTrue(PerformanceSession.describe(a,b,"DOUBLE").startsWith("0.0 FPS | frame timing unavailable"));
        b[1]=30;b[2]=30;b[3]=990_000_000L;b[13+33]=30;b[308]=30;
        String single=PerformanceSession.describe(a,b,"SINGLE");
        assertTrue(single.contains("opaque shader unavailable"));
        assertTrue(single.contains("vertex compatible passes 1.0/frame"));
        b[309]=60;b[310]=30;
        assertTrue(PerformanceSession.describe(a,b,"SINGLE").contains("float 2.0 | fallback 1.0 | retry 1.0"));
        assertEquals("Performance statistics unavailable",PerformanceSession.describe(new long[2],b,"DOUBLE"));
    }

}
