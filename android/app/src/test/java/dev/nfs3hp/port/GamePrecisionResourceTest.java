package dev.nfs3hp.port;

import android.content.Context;
import android.content.pm.PackageManager;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;

@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, application=android.app.Application.class)
public class GamePrecisionResourceTest {
    @Test public void reportAndApkManifestAgreeOnBuildPolicy() throws Exception {
        Context context=RuntimeEnvironment.getApplication();
        String mode=context.getString(R.string.game_precision);
        assertTrue("DOUBLE".equals(mode)||"SINGLE".equals(mode));
        String embedded=context.getPackageManager().getApplicationInfo(
            context.getPackageName(),PackageManager.GET_META_DATA).metaData
            .getString("dev.nfs3hp.port.GAME_PRECISION");
        assertEquals(mode,embedded);
    }
}
