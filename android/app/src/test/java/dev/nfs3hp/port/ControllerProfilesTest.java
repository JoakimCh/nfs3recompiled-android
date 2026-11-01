package dev.nfs3hp.port;

import android.content.SharedPreferences;
import android.view.InputDevice;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowInputDevice;
import org.robolectric.util.ReflectionHelpers;
import static org.junit.Assert.*;

@RunWith(RobolectricTestRunner.class)
@Config(sdk=34,application=android.app.Application.class)
public class ControllerProfilesTest {
    @Test public void legacyShortcutMigratesOnceAndStaysIndependentOfMenuBack() {
        android.content.Context context=RuntimeEnvironment.getApplication();
        SharedPreferences prefs=GamePreferences.get(context);prefs.edit().clear().commit();
        InputDevice input=ShadowInputDevice.makeInputDeviceNamed("Legacy pause fixture");
        ReflectionHelpers.setField(input,"mDescriptor","pause-migration-fixture");
        ControllerProfile p=ControllerProfiles.load(context,input);
        p.assign(5,new ControllerProfile.Binding(109));ControllerProfiles.save(context,p);
        String menuKey=prefs.getAll().keySet().stream().filter(k->k.startsWith("controller_profile_")&&k.endsWith("_5")).findFirst().get();
        String prefix=menuKey.substring(0,menuKey.length()-1);
        prefs.edit().putString(prefix+"race_pause_modifier","k:108").commit();
        p=ControllerProfiles.load(context,input);
        assertEquals(109,p.racePauseFirst.code);assertEquals(108,p.racePauseSecond.code);
        assertFalse(prefs.contains(prefix+"race_pause_modifier"));
        assertEquals("k:109",prefs.getString(prefix+"race_pause_first",""));
        p.assign(5,new ControllerProfile.Binding(99));ControllerProfiles.save(context,p);
        p=ControllerProfiles.load(context,input);
        assertEquals(109,p.racePauseFirst.code);assertEquals(108,p.racePauseSecond.code);
        p.setRacePause(null,null);ControllerProfiles.save(context,p);
        assertFalse(ControllerProfiles.load(context,input).hasRacePause());
        assertFalse(prefs.contains(prefix+"race_pause_first"));assertFalse(prefs.contains(prefix+"race_pause_second"));
    }
}
