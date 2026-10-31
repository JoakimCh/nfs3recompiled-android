package dev.nfs3hp.port;

import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;

/** Exercise the actual launcher entry/resume path, not a second unlock implementation. */
@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, qualifiers="w960dp-h540dp-land", application=android.app.Application.class)
public class LauncherAdvancedTest {
    @Test public void advancedReadsWritesAndRefreshesSavedUnlocks() throws Exception {
        try (ActivityController<LauncherActivity> controller =
                Robolectric.buildActivity(LauncherActivity.class).setup()) {
            LauncherActivity activity = controller.get();
            File folder = new File(activity.dataRoot(), "fedata/config");
            assertTrue(folder.isDirectory() || folder.mkdirs());
            File file = new File(folder, "config.dat");
            byte[] bytes = new byte[0x20f0];
            ByteBuffer.wrap(bytes).order(ByteOrder.LITTLE_ENDIAN).putInt(bytes.length);
            Files.write(file.toPath(), bytes);
            activity.go(LauncherActivity.Screen.Advanced);
            assertNotNull(activity.getBonusContent());
            assertFalse(activity.getBonusContent().cars);
            assertFalse(activity.getBonusContent().track);
            activity.setBonusContent(true, true);
            assertTrue(activity.getBonusContent().cars);
            assertTrue(activity.getBonusContent().track);
            assertTrue(BonusContent.read(file).cars);
            controller.pause().stop();
            BonusContent.update(file, null, false);
            controller.restart().start().resume().visible();
            assertTrue(activity.getBonusContent().cars);
            assertFalse(activity.getBonusContent().track);
            assertEquals("", activity.getBonusContentMessage());
        }
    }
}
