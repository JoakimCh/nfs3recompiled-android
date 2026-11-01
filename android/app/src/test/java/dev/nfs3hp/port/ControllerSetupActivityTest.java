package dev.nfs3hp.port;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;
@RunWith(RobolectricTestRunner.class)
@Config(sdk={34,36},qualifiers="w960dp-h540dp-land",application=android.app.Application.class)
public class ControllerSetupActivityTest {
    @Test
    @Config(qualifiers="en-rUS-w960dp-h540dp-land")
    public void controllerPageUsesChosenLanguageInsteadOfSystemLanguage() {
        android.content.SharedPreferences preferences = GamePreferences.get(
            org.robolectric.RuntimeEnvironment.getApplication());
        preferences.edit().putString(GamePreferences.UI_LANGUAGE, "sv").commit();
        try (ActivityController<ControllerSetupActivity> controller =
                Robolectric.buildActivity(ControllerSetupActivity.class).setup()) {
            ControllerSetupActivity activity = controller.get();
            assertEquals("sv", activity.getResources().getConfiguration().getLocales().get(0).getLanguage());
            assertEquals("Handkontroller", activity.getString(R.string.controls_gamepad));
            assertEquals("Knappkombination för paus", activity.getString(R.string.controller_pause_title));
            View root = activity.getWindow().getDecorView();
            layout(root);
            assertNotNull(find(root, "Välj en handkontroll för varje spelare."));
        } finally {
            preferences.edit().remove(GamePreferences.UI_LANGUAGE).commit();
        }
    }
    private TextView find(View root,String text) {
        if(root instanceof TextView && ((TextView)root).getText().toString().contains(text))return (TextView)root;
        if(root instanceof ViewGroup)for(int i=0;i<((ViewGroup)root).getChildCount();i++){
            TextView found=find(((ViewGroup)root).getChildAt(i),text);if(found!=null)return found;
        }
        return null;
    }
    private android.widget.Button findButton(View root,String label) {
        if(root instanceof android.widget.Button && ((android.widget.Button)root).getText().toString().equals(label))
            return (android.widget.Button)root;
        if(root instanceof ViewGroup)for(int i=0;i<((ViewGroup)root).getChildCount();i++) {
            android.widget.Button found=findButton(((ViewGroup)root).getChildAt(i),label);
            if(found!=null)return found;
        }
        return null;
    }
    private String texts(View root) {
        StringBuilder out=new StringBuilder();if(root instanceof TextView)out.append(((TextView)root).getText()).append(" | ");
        if(root instanceof ViewGroup)for(int i=0;i<((ViewGroup)root).getChildCount();i++)out.append(texts(((ViewGroup)root).getChildAt(i)));
        return out.toString();
    }
    private void layout(View root) {
        int width=root.getResources().getDisplayMetrics().widthPixels,height=root.getResources().getDisplayMetrics().heightPixels;
        root.measure(View.MeasureSpec.makeMeasureSpec(width,View.MeasureSpec.EXACTLY),View.MeasureSpec.makeMeasureSpec(height,View.MeasureSpec.EXACTLY));
        root.layout(0,0,width,height);
        org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idle();
    }
    @Test public void opensWithButtonOnlyControllerAndAssignsInput() {
        android.app.Application app=org.robolectric.RuntimeEnvironment.getApplication();InputDeviceRoles.initialize(app);
        android.view.InputDevice input=org.robolectric.shadows.ShadowInputDevice.makeInputDeviceNamed("Button-only test pad");
        org.robolectric.util.ReflectionHelpers.setField(input,"mId",40);
        org.robolectric.util.ReflectionHelpers.setField(input,"mDescriptor","controller-fixture");
        org.robolectric.util.ReflectionHelpers.setField(input,"mSources",android.view.InputDevice.SOURCE_GAMEPAD);
        org.robolectric.shadows.ShadowInputManager manager=org.robolectric.Shadows.shadowOf((android.hardware.input.InputManager)app.getSystemService(android.content.Context.INPUT_SERVICE));
        manager.addInputDevice(input);manager.addInputDeviceKeys(40,new int[]{96,97,99});InputDeviceRoles.changed(40);
        assertTrue(InputDeviceRoles.isController(input));
        try(ActivityController<ControllerSetupActivity> controller=Robolectric.buildActivity(ControllerSetupActivity.class).setup()) {
            View root=controller.get().getWindow().getDecorView();layout(root);layout(root);
            assertNotNull(find(root,"Button-only test pad"));
            findButton(root,"Start test").performClick();
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(1,1,0,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(1,2,1,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            findButton(root,"Stop test").performClick();findButton(root,"Assign").performClick();assertNotNull(find(root,"Cancel"));
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(10,10,0,99,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(10,11,1,99,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            assertNotNull(ControllerProfiles.load(controller.get(),input).bindings[0]);
            assertEquals(99,ControllerProfiles.load(controller.get(),input).bindings[0].code);layout(root);
            assertNull(ControllerProfiles.load(controller.get(),input).racePauseModifier);
            findButton(root,"Assign extra button").performClick();
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(20,20,0,97,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            assertNull(ControllerProfiles.load(controller.get(),input).racePauseModifier);
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(20,21,1,97,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(30,30,0,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(30,31,1,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            assertEquals(96,ControllerProfiles.load(controller.get(),input).racePauseModifier.code);
            assertEquals(99,ControllerProfiles.load(controller.get(),input).bindings[0].code);
            findButton(root,"Disable").performClick();
            assertNull(ControllerProfiles.load(controller.get(),input).racePauseModifier);
            View scrolling=find(root,"Input device report");
            while(!(scrolling instanceof android.widget.ScrollView)) scrolling=(View)scrolling.getParent();
            android.widget.ScrollView scroll=(android.widget.ScrollView)scrolling;
            assertTrue(scroll.getClipToOutline());
            int[] before=new int[2];scroll.getLocationOnScreen(before);
            assertTrue(before[1]>0);assertTrue(scroll.getHeight()<root.getHeight());
            scroll.fullScroll(View.FOCUS_DOWN);
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idle();
            int[] after=new int[2];scroll.getLocationOnScreen(after);
            assertArrayEquals(before,after);assertTrue(scroll.getScrollY()>0);

            controller.get().onBackPressed();
            assertNotNull(find(root,"Start test"));
        } finally {manager.removeInputDevice(40);InputDeviceRoles.changed(40);}
    }
    @Test public void packagesSavedLauncherJavaException() throws Exception {
        try(ActivityController<ControllerSetupActivity> controller=Robolectric.buildActivity(ControllerSetupActivity.class).setup()) {
            java.io.File dir=new java.io.File(controller.get().getFilesDir(),"crash-reports/java");
            java.util.concurrent.atomic.AtomicBoolean delegated=new java.util.concurrent.atomic.AtomicBoolean();
            JavaCrashLog.handler(dir,"Version: fixture\nProcess: launcher",(thread,error)->delegated.set(true))
                .uncaughtException(Thread.currentThread(),new IllegalStateException("launcher stack fixture"));
            assertTrue(delegated.get());assertTrue(CrashReports.collectJava(controller.get()));
            java.io.File report=new java.io.File(controller.get().getFilesDir(),"crash-reports/nfs3-crash-report.zip");
            try(java.util.zip.ZipFile zip=new java.util.zip.ZipFile(report)) {
                assertTrue(new String(zip.getInputStream(zip.getEntry("java-stack-1.txt")).readAllBytes(),java.nio.charset.StandardCharsets.UTF_8).contains("launcher stack fixture"));
            }
            assertFalse(CrashReports.collectJava(controller.get()));
        }
    }
    @Test public void opensWithoutControllerAndSurvivesPauseResume() {
        try(ActivityController<ControllerSetupActivity> controller=Robolectric.buildActivity(ControllerSetupActivity.class).setup()) {
            View root=controller.get().getWindow().getDecorView();layout(root);
            assertNotNull(find(root,"No game controller detected"));layout(root);
            TextView report=find(root,"Input device report");assertNotNull(report);
            assertTrue(((android.widget.LinearLayout.LayoutParams)report.getLayoutParams()).topMargin>0);
            TextView others=find(root,"Remotes and other inputs");assertNotNull(others);others.performClick();
            controller.pause().stop().restart().start().resume().visible();
            assertNotNull(find(root,"No game controller detected"));layout(root);
        }
    }
}
