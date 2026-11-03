package dev.nfs3hp.port;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Looper;
import java.io.ByteArrayOutputStream;
import java.lang.reflect.Method;
import java.nio.charset.StandardCharsets;
import org.json.JSONObject;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowActivity.IntentForResult;
import static org.junit.Assert.*;
import static org.robolectric.Shadows.shadowOf;

/** Exercise the actual registry, including saved request codes and cancellation. */
@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, qualifiers="w960dp-h540dp-land", application=android.app.Application.class)
public class DocumentPickersTest {
    private static void launch(Activity activity, String name) throws Exception {
        Method method = activity.getClass().getDeclaredMethod(name);
        method.setAccessible(true);
        method.invoke(activity);
    }

    @Test public void launcherPreservesIntentOptionsAndAllowsRetryAfterCancellation() throws Exception {
        String[][] actions = {
            {"launchFolderPicker", Intent.ACTION_OPEN_DOCUMENT_TREE, null},
            {"launchZipPicker", Intent.ACTION_OPEN_DOCUMENT, "application/zip"},
            {"launchImagePicker", Intent.ACTION_OPEN_DOCUMENT, "*/*"},
            {"launchSaveImport", Intent.ACTION_OPEN_DOCUMENT, "application/zip"},
            {"launchSaveExport", Intent.ACTION_CREATE_DOCUMENT, "application/zip"},
            {"launchLauncherImport", Intent.ACTION_OPEN_DOCUMENT, "*/*"},
            {"launchLauncherExport", Intent.ACTION_CREATE_DOCUMENT, "application/json"},
        };
        try (ActivityController<LauncherActivity> controller = Robolectric.buildActivity(LauncherActivity.class).setup()) {
            LauncherActivity activity = controller.get();
            for (String[] action : actions) {
                launch(activity, action[0]);
                IntentForResult request = shadowOf(activity).getNextStartedActivityForResult();
                assertNotNull(action[0], request);
                assertEquals(action[1], request.intent.getAction());
                assertEquals(action[2], request.intent.getType());
                int permission = Intent.ACTION_CREATE_DOCUMENT.equals(action[1])
                    ? Intent.FLAG_GRANT_WRITE_URI_PERMISSION : Intent.FLAG_GRANT_READ_URI_PERMISSION;
                assertNotEquals(0, request.intent.getFlags() & permission);
                if (Intent.ACTION_OPEN_DOCUMENT_TREE.equals(action[1]))
                    assertNotEquals(0, request.intent.getFlags() & Intent.FLAG_GRANT_PERSISTABLE_URI_PERMISSION);
                else
                    assertTrue(request.intent.hasCategory(Intent.CATEGORY_OPENABLE));
                // A second press while Android's picker is open must not launch another.
                launch(activity, action[0]);
                assertNull(shadowOf(activity).getNextStartedActivityForResult());
                assertTrue(activity.getActivityResultRegistry().dispatchResult(request.requestCode, Activity.RESULT_CANCELED, null));
                launch(activity, action[0]);
                IntentForResult retry = shadowOf(activity).getNextStartedActivityForResult();
                assertNotNull(retry);
                // Providers sometimes return RESULT_OK without a URI; treat that as cancellation.
                assertTrue(activity.getActivityResultRegistry().dispatchResult(retry.requestCode, Activity.RESULT_OK, new Intent()));
                assertFalse(activity.getBusy());
            }
        }
    }

    @Test public void pendingSettingsExportSurvivesRecreationAndWritesTheSelectedDocument() throws Exception {
        try (ActivityController<LauncherActivity> controller = Robolectric.buildActivity(LauncherActivity.class).setup()) {
            LauncherActivity activity = controller.get();
            activity.launchLauncherExport();
            IntentForResult request = shadowOf(activity).getNextStartedActivityForResult();
            controller.recreate();
            activity = controller.get();
            activity.launchLauncherExport();
            assertNull(shadowOf(activity).getNextStartedActivityForResult());
            Uri uri = Uri.parse("content://picker-test/launcher.json");
            ByteArrayOutputStream output = new ByteArrayOutputStream();
            shadowOf(activity.getContentResolver()).registerOutputStream(uri, output);
            assertTrue(activity.getActivityResultRegistry().dispatchResult(request.requestCode,
                Activity.RESULT_OK, new Intent().setData(uri)));
            long deadline = System.nanoTime() + 5_000_000_000L;
            while (activity.getBusy() && System.nanoTime() < deadline) {
                shadowOf(Looper.getMainLooper()).idle();
                Thread.sleep(10);
            }
            shadowOf(Looper.getMainLooper()).idle();
            assertFalse("settings export did not finish", activity.getBusy());
            JSONObject saved = new JSONObject(output.toString(StandardCharsets.UTF_8.name()));
            assertEquals(5, saved.getInt("format"));
            assertTrue(saved.has("settings"));
        }
    }

    @Test public void splashPickerCancellationSurvivesRecreation() throws Exception {
        for (String method : new String[]{"launchFolderPicker", "launchZipPicker", "launchImagePicker"}) {
            try (ActivityController<SplashActivity> controller = Robolectric.buildActivity(SplashActivity.class).setup()) {
                SplashActivity activity = controller.get();
                launch(activity, method);
                IntentForResult request = shadowOf(activity).getNextStartedActivityForResult();
                assertNotNull(method, request);
                controller.recreate();
                activity = controller.get();
                launch(activity, method);
                assertNull(shadowOf(activity).getNextStartedActivityForResult());
                assertTrue(activity.getActivityResultRegistry().dispatchResult(request.requestCode, Activity.RESULT_CANCELED, null));
                launch(activity, method);
                IntentForResult retry = shadowOf(activity).getNextStartedActivityForResult();
                assertNotNull(retry);
                assertTrue(activity.getActivityResultRegistry().dispatchResult(retry.requestCode, Activity.RESULT_OK, new Intent()));
            }
        }
    }
}
