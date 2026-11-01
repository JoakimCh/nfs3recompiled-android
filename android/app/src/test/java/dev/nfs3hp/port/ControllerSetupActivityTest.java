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
    private void send(ControllerSetupActivity activity,int key,boolean down) {
        activity.dispatchKeyEvent(new android.view.KeyEvent(40,40,down?0:1,key,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
    }
    @Test public void buttonOnlyAssignmentsRejectDirectionsAndAxes() {
        for(int code:new int[]{96,97,102,108,109,250})
            assertTrue(ControllerSetupActivity.assignableButton(new ControllerProfile.Binding(code)));
        for(int code:new int[]{19,20,21,22,23,198,199,200,201})
            assertFalse(ControllerSetupActivity.assignableButton(new ControllerProfile.Binding(code)));
        for(int axis:new int[]{0,1,15,16,17,18})
            assertFalse(ControllerSetupActivity.assignableButton(new ControllerProfile.Binding(axis,1,0,2)));
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
            View testing=root.findViewWithTag("gamepad-test-panel"),raw=root.findViewWithTag("gamepad-test-raw");
            assertEquals(View.GONE,testing.getVisibility());assertFalse(raw.isShown());
            assertNull(findButton(root,"Show input details"));assertNull(findButton(root,"Hide input details"));
            findButton(root,"Test gamepad").performClick();
            assertEquals(View.VISIBLE,testing.getVisibility());assertTrue(raw.isShown());
            assertNotNull(findButton(root,"Stop testing"));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(1,1,0,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(1,2,1,96,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            findButton(root,"Stop testing").performClick();
            assertEquals(View.GONE,testing.getVisibility());assertFalse(raw.isShown());
            assertNotNull(findButton(root,"Test gamepad"));
            findButton(root,"Test gamepad").performClick();
            send(controller.get(),99,true);findButton(root,"Stop testing").performClick();
            assertEquals(View.GONE,testing.getVisibility());
            assertTrue(org.robolectric.util.ReflectionHelpers.getField(controller.get(),"releaseGate"));
            send(controller.get(),99,false);
            assertFalse(org.robolectric.util.ReflectionHelpers.getField(controller.get(),"releaseGate"));
            findButton(root,"Test gamepad").performClick();controller.get().onBackPressed();
            assertEquals(View.GONE,testing.getVisibility());assertFalse(controller.get().isFinishing());
            findButton(root,"Assign").performClick();assertNotNull(find(root,"Cancel"));
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(10,10,0,99,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            controller.get().dispatchKeyEvent(new android.view.KeyEvent(10,11,1,99,0,0,40,0,0,android.view.InputDevice.SOURCE_GAMEPAD));
            assertNotNull(ControllerProfiles.load(controller.get(),input).bindings[0]);
            assertEquals(99,ControllerProfiles.load(controller.get(),input).bindings[0].code);layout(root);
            assertNotNull(findButton(root,"Test gamepad"));assertNull(findButton(root,"Stop testing"));
            assertEquals(View.GONE,testing.getVisibility());
            assertFalse(org.robolectric.util.ReflectionHelpers.getField(controller.get(),"releaseGate"));
            assertFalse(ControllerProfiles.load(controller.get(),input).hasRacePause());
            android.widget.Button[] assignments=org.robolectric.util.ReflectionHelpers.getField(controller.get(),"assignButtons");
            for(int action:new int[]{4,5}) {
                assignments[action].performClick();
                org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
                send(controller.get(),19,true);send(controller.get(),19,false);
                assertNull(ControllerProfiles.load(controller.get(),input).bindings[action]);
                assertEquals(action,(int)org.robolectric.util.ReflectionHelpers.getField(controller.get(),"waiting"));
                assertNotNull(find(root,controller.get().getString(R.string.controller_buttons_only)));
                controller.get().onBackPressed();
            }
            root.findViewWithTag("race-pause-assign").performClick();
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
            TextView pairValue=root.findViewWithTag("race-pause-value"),prompt=root.findViewWithTag("race-pause-prompt");
            assertEquals("… + …",pairValue.getText().toString());
            assertEquals(View.VISIBLE,prompt.getVisibility());
            assertEquals(controller.get().getString(R.string.controller_pause_first),prompt.getText().toString());
            send(controller.get(),22,true);send(controller.get(),22,false);
            assertEquals(controller.get().getString(R.string.controller_buttons_only),prompt.getText().toString());
            assertFalse(ControllerProfiles.load(controller.get(),input).hasRacePause());
            send(controller.get(),102,true);send(controller.get(),102,false);
            assertEquals(controller.get().getString(R.string.controller_pause_pair,ControllerProfiles.keyLabel(102),"…"),pairValue.getText().toString());
            assertEquals(controller.get().getString(R.string.controller_pause_second),prompt.getText().toString());
            assertEquals(View.VISIBLE,prompt.getVisibility());
            assertFalse(ControllerProfiles.load(controller.get(),input).hasRacePause());
            send(controller.get(),102,true);send(controller.get(),102,false); // Duplicate first button is rejected.
            assertEquals(controller.get().getString(R.string.controller_pause_different),prompt.getText().toString());
            assertFalse(ControllerProfiles.load(controller.get(),input).hasRacePause());
            send(controller.get(),108,true);send(controller.get(),108,false);
            ControllerProfile pair=ControllerProfiles.load(controller.get(),input);
            assertEquals(102,pair.racePauseFirst.code);assertEquals(108,pair.racePauseSecond.code);
            assertEquals(View.GONE,prompt.getVisibility());
            assertEquals(controller.get().getString(R.string.controller_pause_pair,ControllerProfiles.keyLabel(102),ControllerProfiles.keyLabel(108)),pairValue.getText().toString());
            assertEquals(99,pair.bindings[0].code);
            assertNotNull(findButton(root,"Test gamepad"));assertNull(findButton(root,"Stop testing"));
            assertEquals(View.GONE,testing.getVisibility());
            assertFalse(org.robolectric.util.ReflectionHelpers.getField(controller.get(),"releaseGate"));
            root.findViewWithTag("race-pause-assign").performClick();
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idleFor(java.time.Duration.ofMillis(350));
            send(controller.get(),99,true);send(controller.get(),99,false);
            controller.get().onBackPressed(); // An incomplete replacement must preserve the saved pair.
            pair=ControllerProfiles.load(controller.get(),input);
            assertEquals(102,pair.racePauseFirst.code);assertEquals(108,pair.racePauseSecond.code);
            findButton(root,"Disable").performClick();
            pair=ControllerProfiles.load(controller.get(),input);
            assertNull(pair.racePauseFirst);assertNull(pair.racePauseSecond);
            layout(root); // Finish layout after hiding the capture prompt.
            View scrolling=find(root,"Input device report");
            while(!(scrolling instanceof android.widget.ScrollView)) scrolling=(View)scrolling.getParent();
            android.widget.ScrollView scroll=(android.widget.ScrollView)scrolling;
            assertTrue(scroll.getClipToOutline());
            int[] before=new int[2];scroll.getLocationOnScreen(before);
            assertTrue(before[1]>0);assertTrue(scroll.getHeight()<root.getHeight());
            scroll.setSmoothScrollingEnabled(false); // Inspect final geometry, not an unadvanced animation.
            scroll.fullScroll(View.FOCUS_DOWN);
            org.robolectric.Shadows.shadowOf(android.os.Looper.getMainLooper()).idle();
            int[] after=new int[2];scroll.getLocationOnScreen(after);
            assertArrayEquals(before,after);assertTrue(scroll.getScrollY()>0);

            assertNotNull(find(root,"Test gamepad"));
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
