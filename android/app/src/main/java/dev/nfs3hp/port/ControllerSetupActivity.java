package dev.nfs3hp.port;

import androidx.activity.ComponentActivity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.hardware.input.InputManager;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import java.util.HashSet;
import java.util.List;

/** Interactive Android input test and per-controller normalization. No game files edited. */
public final class ControllerSetupActivity extends ComponentActivity implements InputManager.InputDeviceListener {
    @Override protected void attachBaseContext(android.content.Context base) {
        super.attachBaseContext(LocaleHelper.wrap(base));
    }
    private LinearLayout content,devices,players,otherDevices,detailPanel,testingPanel;
    private TextView selectedTitle,roleLabel;
    private final TextView[] indicators=new TextView[6];
    private boolean showOthers,expanded=true;
    private TextView status,raw,functions;
    private final TextView[] values=new TextView[6];
    private final Button[] assignButtons=new Button[6];
    private final Handler handler=new Handler(Looper.getMainLooper());
    private final HashSet<Integer> down=new HashSet<>();
    private final float[] latest=new float[64];
    private InputDevice device;
    private ControllerProfile profile;
    private int waiting=-1;
    private boolean armed,test,releaseGate;
    private ControllerProfile.Binding pendingPauseFirst;
    private long armAt;
    private String descriptor="";
    private Button testButton, pauseAssign;
    private TextView pauseValue,pausePrompt;
    private String captureMessage;
    private String captureName(){return ControllerProfile.NAMES[waiting];}
    private int dp(int value){return Math.round(value*getResources().getDisplayMetrics().density);}
    private TextView text(String value,int size) {
        TextView v=new TextView(this);v.setText(value);v.setTextSize(size);v.setTextColor(0xffdce1fa);
        v.setPadding(dp(8),dp(8),dp(8),dp(8));return v;
    }
    private Button button(String value,Runnable action) {
        Button b=new Button(this);b.setText(value);b.setTextSize(15);b.setAllCaps(false);
        b.setBackgroundResource(R.drawable.ui_input_button);b.setMinHeight(dp(48));b.setMinimumWidth(dp(96));
        b.setPadding(dp(12),dp(8),dp(12),dp(8));b.setOnClickListener(v->action.run());return b;
    }
    private LinearLayout column(){LinearLayout v=new LinearLayout(this);v.setOrientation(LinearLayout.VERTICAL);return v;}
    private LinearLayout row(){LinearLayout v=new LinearLayout(this);v.setOrientation(LinearLayout.HORIZONTAL);return v;}
    private android.graphics.drawable.GradientDrawable panelBackground(int color,int border) {
        android.graphics.drawable.GradientDrawable d=new android.graphics.drawable.GradientDrawable();
        d.setColor(color);d.setCornerRadius(dp(14));d.setStroke(dp(1),border);return d;
    }
    private LinearLayout panel() {
        LinearLayout v=column();v.setPadding(dp(14),dp(12),dp(14),dp(12));
        v.setBackground(panelBackground(0xff19204b,0xff46528d));
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.setMargins(0,dp(8),0,dp(8));v.setLayoutParams(lp);return v;
    }
    private void weighted(LinearLayout row,android.view.View view) {
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(0,-2,1);lp.setMargins(dp(4),dp(4),dp(4),dp(4));row.addView(view,lp);
    }
    private void heading(LinearLayout parent,String title) {TextView v=text(title,19);v.setTextColor(0xffead34e);parent.addView(v);}
    @Override public void onCreate(Bundle state) {
        super.onCreate(state);InputDeviceRoles.initialize(this);
        if(state!=null){descriptor=state.getString("controller","");showOthers=state.getBoolean("show_others");expanded=state.getBoolean("expanded",true);}
        ScrollView scroll=new ScrollView(this);scroll.setFillViewport(true);scroll.setBackgroundColor(android.graphics.Color.TRANSPARENT);
        scroll.setOutlineProvider(android.view.ViewOutlineProvider.BOUNDS);scroll.setClipToOutline(true);
        LinearLayout center=column();center.setGravity(android.view.Gravity.CENTER_HORIZONTAL);scroll.addView(center);
        content=column();content.setPadding(0,0,0,dp(12));
        center.addView(content,new LinearLayout.LayoutParams(-1,-2));ControllerSetupScreenKt.showControllerSetup(this,scroll);
        content.addView(text(getString(R.string.controller_setup_intro),16));
        players=row();content.addView(players);
        heading(content,"Connected controllers");devices=column();content.addView(devices);
        detailPanel=panel();content.addView(detailPanel);selectedTitle=text("",21);detailPanel.addView(selectedTitle);
        testButton=button(getString(R.string.controller_test_start),()->{cancelCapture();setTesting(!test);updateStatus();});
        testButton.setTag("gamepad-test-toggle");detailPanel.addView(testButton);
        testingPanel=column();testingPanel.setTag("gamepad-test-panel");testingPanel.setVisibility(android.view.View.GONE);
        detailPanel.addView(testingPanel);
        testingPanel.addView(text(getString(R.string.controller_test_hint),14));
        LinearLayout chips=column();
        for(int group=0;group<2;group++) {LinearLayout chipRow=row();for(int col=0;col<3;col++) {
            int i=group*3+col;TextView chip=text(ControllerProfile.NAMES[i],16);chip.setGravity(android.view.Gravity.CENTER);
            chip.setMinHeight(dp(44));chip.setBackgroundResource(R.drawable.ui_input_indicator);indicators[i]=chip;weighted(chipRow,chip);
        }chips.addView(chipRow);}testingPanel.addView(chips);
        functions=text("Active functions: none",16);testingPanel.addView(functions);
        raw=text(getString(R.string.controller_test_no_input),15);raw.setTag("gamepad-test-raw");
        raw.setMinLines(2);raw.setMaxLines(3);raw.setEllipsize(android.text.TextUtils.TruncateAt.END);testingPanel.addView(raw);
        testingPanel.addView(text(getString(R.string.controller_test_navigation),14));
        // Assignment feedback remains available when the testing panel is closed.
        status=text("",16);status.setTag("controller-assignment-status");status.setVisibility(android.view.View.GONE);detailPanel.addView(status);
        heading(detailPanel,"Menu controls");
        detailPanel.addView(text(getString(R.string.controller_button_actions_hint),14));
        for(int i=0;i<6;i++) {
            final int action=i;LinearLayout bindingRow=row(),label=column();
            label.addView(text(ControllerProfile.NAMES[i],17));values[i]=text("",14);label.addView(values[i]);
            bindingRow.addView(label,new LinearLayout.LayoutParams(0,-2,1));
            assignButtons[i]=button("Assign",()->{if(waiting==action){cancelCapture();updateStatus();}else begin(action);});
            LinearLayout.LayoutParams assignLP=new LinearLayout.LayoutParams(dp(100),-2);assignLP.setMargins(dp(4),dp(8),dp(4),dp(8));bindingRow.addView(assignButtons[i],assignLP);
            Button defaults=button("Reset",()->{cancelCapture();profile.assign(action,null);save();});
            LinearLayout.LayoutParams defaultLP=new LinearLayout.LayoutParams(dp(100),-2);defaultLP.setMargins(dp(4),dp(8),0,dp(8));bindingRow.addView(defaults,defaultLP);
            detailPanel.addView(bindingRow);
        }
        detailPanel.addView(button(getString(R.string.controller_reset_menu),()->{
            cancelCapture();for(int i=0;i<6;i++)profile.assign(i,null);profile.release();save();showFunctions();
        }));
        heading(detailPanel,getString(R.string.controller_pause_title));
        detailPanel.addView(text(getString(R.string.controller_pause_hint),14));
        pauseValue=text("",14);pauseValue.setTag("race-pause-value");detailPanel.addView(pauseValue);
        pausePrompt=text("",14);pausePrompt.setTag("race-pause-prompt");pausePrompt.setTextColor(0xffead34e);
        pausePrompt.setAccessibilityLiveRegion(android.view.View.ACCESSIBILITY_LIVE_REGION_POLITE);
        pausePrompt.setVisibility(android.view.View.GONE);detailPanel.addView(pausePrompt);
        LinearLayout pauseRow=row();
        pauseAssign=button(getString(R.string.controller_assign),()->{if(waiting>=6){cancelCapture();updateStatus();}else begin(6);});
        pauseAssign.setTag("race-pause-assign");weighted(pauseRow,pauseAssign);
        weighted(pauseRow,button(getString(R.string.controller_disable),()->{cancelCapture();profile.setRacePause(null,null);save();}));
        detailPanel.addView(pauseRow);
        heading(detailPanel,getString(R.string.controller_device_type));roleLabel=text("",15);detailPanel.addView(roleLabel);
        detailPanel.addView(button(getString(R.string.controller_change_type),()->showRole(device)));
        detailPanel.addView(text(getString(R.string.controller_role_hint),14));
        otherDevices=column();content.addView(otherDevices);
        Button report=button(getString(R.string.controller_report),()->InputDeviceReport.show(this));
        LinearLayout.LayoutParams reportLayout=new LinearLayout.LayoutParams(-1,-2);
        reportLayout.topMargin=dp(12);content.addView(report,reportLayout);
        refreshDevices();
    }
    @Override protected void onResume(){super.onResume();((InputManager)getSystemService(INPUT_SERVICE)).registerInputDeviceListener(this,null);refreshDevices();}
    @Override protected void onPause(){((InputManager)getSystemService(INPUT_SERVICE)).unregisterInputDeviceListener(this);handler.removeCallbacks(arm);cancelCapture();setTesting(false);if(profile!=null){profile.release();showFunctions();}down.clear();releaseGate=false;super.onPause();}
    @Override protected void onSaveInstanceState(Bundle out){super.onSaveInstanceState(out);out.putString("controller",descriptor);out.putBoolean("show_others",showOthers);out.putBoolean("expanded",expanded);}
    private void choosePlayer(int slot) {
        List<GamepadSlots.Pad> pads=GamepadSlots.attached();String[] names=new String[pads.size()+1];names[0]=getString(R.string.controller_automatic);
        int checked=0;String pin=GamepadSlots.assigned(GamePreferences.get(this),slot);
        for(int i=0;i<pads.size();i++){names[i+1]=pads.get(i).name;if(pads.get(i).descriptor.equals(pin))checked=i+1;}
        new android.app.AlertDialog.Builder(this).setTitle("Player "+(slot+1)+" controller")
            .setSingleChoiceItems(names,checked,(dialog,which)->{
                if(which==0)GamepadSlots.useAutomatic(GamePreferences.get(this),slot);
                else {GamepadSlots.Pad pad=pads.get(which-1);GamepadSlots.assign(GamePreferences.get(this),slot,pad.descriptor,pad.name);}
                dialog.dismiss();refreshDevices();
            }).setNegativeButton("Cancel",null).show();
    }
    private void showRole(InputDevice input) {
        if(input==null)return;
        new android.app.AlertDialog.Builder(this).setTitle(input.getName())
            .setItems(new String[]{getString(R.string.controller_automatic),"Gamepad",getString(R.string.controller_remote)},(dialog,choice)->{
                cancelCapture();InputDeviceRoles.set(input,new String[]{InputDeviceRoles.DEFAULT,InputDeviceRoles.CONTROLLER,InputDeviceRoles.REMOTE}[choice]);
                if(!InputDeviceRoles.isController(input) && descriptor.equals(input.getDescriptor())){device=null;profile=null;descriptor="";}
                refreshDevices();
            }).setNegativeButton("Cancel",null).show();
    }
    private void refreshDevices() {
        android.view.View focused=getCurrentFocus();Object focusTag=focused==null?null:focused.getTag();
        devices.removeAllViews();players.removeAllViews();otherDevices.removeAllViews();
        List<GamepadSlots.Pad> pads=GamepadSlots.attached();InputDevice selected=null;
        android.content.SharedPreferences prefs=GamePreferences.get(this);GamepadSlots.Pad[] assigned=GamepadSlots.resolve(prefs);
        for(int slot=0;slot<2;slot++) {
            final int player=slot;String pin=GamepadSlots.assigned(prefs,slot);
            String who=assigned[slot]!=null?assigned[slot].name:pin.isEmpty()?"No controller":"Disconnected: "+GamepadSlots.assignedName(prefs,slot);
            LinearLayout card=panel();heading(card,"Player "+(slot+1));TextView name=text(who,17);name.setMaxLines(2);name.setEllipsize(android.text.TextUtils.TruncateAt.END);card.addView(name);
            card.addView(text(pin.isEmpty()?"Automatic assignment":"Saved assignment",14));Button change=button("Change…",()->choosePlayer(player));change.setTag("player:"+slot);card.addView(change);weighted(players,card);
        }
        int otherCount=0;for(InputDevice input:InputDeviceRoles.candidates())if(!InputDeviceRoles.isController(input))otherCount++;
        for(InputDevice input:InputDeviceRoles.candidates())if(InputDeviceRoles.isController(input)) {
            String player=getString(R.string.controller_unassigned);for(int slot=0;slot<2;slot++)if(assigned[slot]!=null && assigned[slot].id==input.getId())player="Player "+(slot+1);
            boolean active=input.getDescriptor().equals(descriptor);if(active)selected=input;
            Button card=button(input.getName()+"\n"+player+(active?(expanded?" · Hide controls":" · Show controls"):" · Test / configure"),()->{
                if(input.getDescriptor().equals(descriptor)) {
                    expanded=!expanded;if(!expanded){cancelCapture();setTesting(false);}
                    refreshDevices();
                }else select(input);
            });card.setTag("device:"+input.getDescriptor());card.setSelected(active);card.setMinHeight(dp(64));
            LinearLayout.LayoutParams cardLP=new LinearLayout.LayoutParams(-1,-2);cardLP.setMargins(0,dp(5),0,dp(5));devices.addView(card,cardLP);
        }
        if(pads.isEmpty())devices.addView(text("No game controller detected. If a controller is misidentified, expand the inputs below and change its device type.",16));
        final int count=otherCount;Button toggle=button((showOthers?"▾  ":"▸  ")+"Remotes and other inputs ("+count+")",()->{showOthers=!showOthers;refreshDevices();});toggle.setTag("others");otherDevices.addView(toggle);
        if(showOthers)for(InputDevice input:InputDeviceRoles.candidates())if(!InputDeviceRoles.isController(input)) {
            LinearLayout card=panel();card.addView(text(input.getName(),17));card.addView(text(InputDeviceRoles.description(input),14));
            Button role=button(getString(R.string.controller_change_type),()->showRole(input));role.setTag("role:"+input.getDescriptor());card.addView(role);otherDevices.addView(card);
        }
        if(selected==null && !pads.isEmpty()){select(GamepadSlots.device(pads.get(0)));return;}
        if(selected==null){releaseGate=false;pendingPauseFirst=null;captureMessage=null;device=null;profile=null;waiting=-1;setTesting(false);down.clear();}
        else if(device==null || selected.getId()!=device.getId()){select(selected);return;}
        updateStatus();
        if(focusTag!=null){android.view.View replacement=content.findViewWithTag(focusTag);if(replacement!=null)replacement.requestFocus();}
    }
    private void select(InputDevice selected) {
        if(selected==null)return;
        cancelCapture();releaseGate=false;device=selected;descriptor=selected.getDescriptor();profile=ControllerProfiles.load(this,selected);expanded=true;
        down.clear();java.util.Arrays.fill(latest,0);
        for(InputDevice.MotionRange r:device.getMotionRanges())if(joystick(r) && r.getAxis()>=0 && r.getAxis()<64)latest[r.getAxis()]=rest(r);
        setTesting(false);refreshDevices();refreshRows();showFunctions();
    }
    private void refreshRows(){for(int i=0;i<6;i++) {
        values[i].setText(ControllerProfiles.label(profile,i));
        assignButtons[i].setText(waiting==i?"Cancel":"Assign");
        assignButtons[i].setActivated(waiting==i);
    }
        if(pauseValue!=null) {
            if(waiting>=6)pauseValue.setText(getString(R.string.controller_pause_pair,
                pendingPauseFirst==null?"…":ControllerProfiles.keyLabel(pendingPauseFirst.code),"…"));
            else pauseValue.setText(profile==null || !profile.hasRacePause()?getString(R.string.controller_shortcut_disabled):
                getString(R.string.controller_pause_pair,ControllerProfiles.keyLabel(profile.racePauseFirst.code),
                    ControllerProfiles.keyLabel(profile.racePauseSecond.code)));
        }
        if(pausePrompt!=null) {
            pausePrompt.setVisibility(waiting>=6?android.view.View.VISIBLE:android.view.View.GONE);
            if(waiting>=6)pausePrompt.setText(captureMessage!=null?captureMessage:
                getString(waiting==6?R.string.controller_pause_first:R.string.controller_pause_second));
        }
        if(pauseAssign!=null) {
            pauseAssign.setText(getString(waiting>=6?R.string.controller_cancel:R.string.controller_assign));
            pauseAssign.setActivated(waiting>=6);
        }
    }
    private void setTesting(boolean enabled) {
        if(!enabled && test && device!=null)releaseGate=!neutral();
        test=enabled;
        if(testingPanel!=null)testingPanel.setVisibility(enabled?android.view.View.VISIBLE:android.view.View.GONE);
        if(testButton!=null)testButton.setText(getString(enabled?R.string.controller_test_stop:R.string.controller_test_start));
        if(!enabled && profile!=null){profile.release();showFunctions();}
    }
    private void save(){ControllerProfiles.save(this,profile);refreshRows();updateStatus();}
    private void cancelCapture(){
        if(waiting>=0)releaseGate=device!=null && !neutral();
        waiting=-1;armed=false;pendingPauseFirst=null;captureMessage=null;handler.removeCallbacks(arm);refreshRows();
    }
    private void begin(int action) {
        if(profile==null){status.setText("Connect and select a gamepad first.");return;}
        pendingPauseFirst=null;captureMessage=null;releaseGate=false;waiting=action;armed=false;armAt=android.os.SystemClock.uptimeMillis()+300;
        handler.removeCallbacks(arm);handler.post(arm);updateStatus();
    }
    private float rest(InputDevice.MotionRange r) {
        int a=r.getAxis();
        if(a==MotionEvent.AXIS_LTRIGGER || a==MotionEvent.AXIS_RTRIGGER || a==MotionEvent.AXIS_GAS || a==MotionEvent.AXIS_BRAKE)return r.getMin();
        return r.getMin()<0 && r.getMax()>0?0:r.getMin();
    }
    private boolean neutral() {
        if(!down.isEmpty())return false;
        for(InputDevice.MotionRange r:device.getMotionRanges())if(joystick(r) && r.getAxis()<64 &&
            Math.abs(latest[r.getAxis()]-rest(r))>Math.max(r.getFlat(),r.getRange()*.15f))return false;
        return true;
    }
    private final Runnable arm=new Runnable(){public void run(){
        if(waiting<0 || device==null)return;
        if(android.os.SystemClock.uptimeMillis()>=armAt && neutral()){armed=true;updateStatus();}
        else handler.postDelayed(this,100);
    }};
    // Shared by Confirm, Back and both shortcut steps. Preserve axis support for directions.
    static boolean assignableButton(ControllerProfile.Binding binding) {
        int logical=ControllerProfile.logicalButton(binding.code);
        return !binding.axis && binding.code!=KeyEvent.KEYCODE_DPAD_CENTER && !(logical>=10 && logical<=13);
    }
    private void captureFeedback(String message) {
        captureMessage=message;status.setText(message);
        if(waiting>=6 && pausePrompt!=null)pausePrompt.setText(message);
    }
    private void captured(ControllerProfile.Binding binding) {
        if(waiting>=4 && !assignableButton(binding)) {
            captureFeedback(getString(R.string.controller_buttons_only));return;
        }
        if(!armed)return;
        captureMessage=null;
        if(waiting>=6) {
            if(waiting==6) {
                pendingPauseFirst=binding;waiting=7;armed=false;
                armAt=android.os.SystemClock.uptimeMillis();
                handler.removeCallbacks(arm);handler.post(arm);updateStatus();return;
            }
            if(ControllerProfile.samePauseButton(pendingPauseFirst.code,binding.code)) {
                captureFeedback(getString(R.string.controller_pause_different));return;
            }
            profile.setRacePause(pendingPauseFirst,binding);
            cancelCapture();profile.release();save();return;
        }
        for(int i=0;i<6;i++)if(i!=waiting && binding.sameInput(profile.bindings[i])) {
            captureFeedback("Already assigned to "+ControllerProfile.NAMES[i]+". Reset that assignment first, or press another control.");return;
        }
        profile.assign(waiting,binding);cancelCapture();save();
    }
    private void updateStatus() {
        if(status==null)return;
        status.setVisibility(waiting>=0?android.view.View.VISIBLE:android.view.View.GONE);
        refreshRows();detailPanel.setVisibility(device!=null && expanded?android.view.View.VISIBLE:android.view.View.GONE);
        if(device!=null){selectedTitle.setText(device.getName());roleLabel.setText(InputDeviceRoles.description(device));}
        if(device==null){status.setText("No selected gamepad connected.");functions.setText("");refreshRows();return;}
        if(waiting>=0 && captureMessage!=null){status.setText(captureMessage);return;}
        if(waiting>=6) {
            status.setText(getString(waiting==6?R.string.controller_pause_first:R.string.controller_pause_second));return;
        }
        status.setText(waiting>=0?(armed?(waiting<4?"Press a button or move an axis for ":"Press a button for ")+captureName()+".":"Release all controls to assign "+captureName()+"…"):
            device.getName()+(test?" — test active":" — ready"));
    }
    private void showFunctions() {
        if(profile==null)return;
        long state=profile.snapshot();StringBuilder out=new StringBuilder("Active functions:");boolean any=false;
        for(int i=0;i<6;i++) {
            boolean active=profile.preview(i,state);indicators[i].setSelected(active);
            indicators[i].setTextColor(active?0xff111633:0xffdce1fa);
            indicators[i].setContentDescription(ControllerProfile.NAMES[i]+(active?": pressed":": released"));
            if(active){out.append("  ").append(ControllerProfile.NAMES[i]);any=true;}
        }
        functions.setText(any?out.toString():"Active functions: none");
    }
    @Override public boolean dispatchKeyEvent(KeyEvent event) {
        if(device!=null && event.getDeviceId()==device.getId()) {
            if(event.getAction()==KeyEvent.ACTION_DOWN)down.add(event.getKeyCode());
            else if(event.getAction()==KeyEvent.ACTION_UP)down.remove(event.getKeyCode());
            profile.key(event.getKeyCode(),event.getAction()==KeyEvent.ACTION_DOWN);
            raw.setText("Android button: "+KeyEvent.keyCodeToString(event.getKeyCode())+" ("+event.getKeyCode()+"), scan "+event.getScanCode()+
                (event.getAction()==KeyEvent.ACTION_DOWN?" · pressed":" · released"));
            boolean reserved=test || waiting>=0 || releaseGate;
            if(waiting>=0 && event.getAction()==KeyEvent.ACTION_DOWN && event.getRepeatCount()==0) {
                ControllerProfile.Binding input=new ControllerProfile.Binding(event.getKeyCode());
                if(armed || (waiting>=4 && !assignableButton(input)))captured(input);
            }
            if(waiting>=0 && !armed){handler.removeCallbacks(arm);arm.run();}
            if(releaseGate && neutral()){releaseGate=false;profile.release();}
            showFunctions();if(reserved)return true;
        }
        return super.dispatchKeyEvent(event);
    }
    private static boolean joystick(InputDevice.MotionRange r){return (r.getSource()&InputDevice.SOURCE_JOYSTICK)==InputDevice.SOURCE_JOYSTICK;}
    @Override public boolean dispatchGenericMotionEvent(MotionEvent event) {
        if(device!=null && event.getDeviceId()==device.getId() && event.isFromSource(InputDevice.SOURCE_JOYSTICK)) {
            StringBuilder description=new StringBuilder("Android axes:");ControllerProfile.Binding candidate=null;float strongest=0;
            for(InputDevice.MotionRange r:device.getMotionRanges())if(joystick(r) && r.getAxis()>=0 && r.getAxis()<64 && r.getRange()>0) {
                int a=r.getAxis();float v=event.getAxisValue(a);latest[a]=v;profile.axis(a,v);
                float delta=v-rest(r),amount=Math.abs(delta)/r.getRange();
                if(amount>.05f)description.append(' ').append(MotionEvent.axisToString(a)).append('=').append(String.format(java.util.Locale.ROOT,"%.2f",v));
                if(amount>.25f && amount>strongest){strongest=amount;candidate=new ControllerProfile.Binding(a,delta>0?1:-1,rest(r),r.getRange());}
            }
            raw.setText(description.toString());boolean reserved=test || waiting>=0 || releaseGate;
            if(waiting>=0 && candidate!=null && (armed || waiting>=4))captured(candidate);
            if(waiting>=0 && !armed){handler.removeCallbacks(arm);arm.run();}
            if(releaseGate && neutral()){releaseGate=false;profile.release();}
            showFunctions();if(reserved)return true;
        }
        return super.dispatchGenericMotionEvent(event);
    }
    @Override public void onBackPressed() {
        if(waiting>=0){cancelCapture();updateStatus();return;}
        if(test){setTesting(false);updateStatus();return;}
        super.onBackPressed();
    }
    @Override public void onInputDeviceAdded(int id){InputDeviceRoles.changed(id);refreshDevices();}
    @Override public void onInputDeviceRemoved(int id){InputDeviceRoles.changed(id);refreshDevices();}
    @Override public void onInputDeviceChanged(int id){InputDeviceRoles.changed(id);refreshDevices();}
}
