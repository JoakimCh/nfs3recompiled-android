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
    private LinearLayout content,devices,players,otherDevices,detailPanel;
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
    private boolean armed,test;
    private long armAt;
    private String descriptor="";
    private Button testButton, pauseAssign;
    private TextView pauseValue;
    private String captureName(){return waiting==6?"race pause extra button":ControllerProfile.NAMES[waiting];}
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
        content.addView(text("Choose a player’s controller above, or select a device below to test and adjust its menu controls. Racing controls are assigned inside the game.",16));
        players=row();content.addView(players);
        heading(content,"Connected controllers");devices=column();content.addView(devices);
        detailPanel=panel();content.addView(detailPanel);selectedTitle=text("",21);detailPanel.addView(selectedTitle);
        heading(detailPanel,"Test input");status=text("",16);detailPanel.addView(status);
        LinearLayout chips=column();
        for(int group=0;group<2;group++) {LinearLayout chipRow=row();for(int col=0;col<3;col++) {
            int i=group*3+col;TextView chip=text(ControllerProfile.NAMES[i],16);chip.setGravity(android.view.Gravity.CENTER);
            chip.setMinHeight(dp(44));chip.setBackgroundResource(R.drawable.ui_input_indicator);indicators[i]=chip;weighted(chipRow,chip);
        }chips.addView(chipRow);}detailPanel.addView(chips);
        functions=text("Active functions: none",16);functions.setVisibility(android.view.View.GONE);detailPanel.addView(functions);
        raw=text("Press a button or move a stick to see its Android input.",15);raw.setMinLines(2);raw.setMaxLines(3);raw.setEllipsize(android.text.TextUtils.TruncateAt.END);detailPanel.addView(raw);
        testButton=button("Start test",()->{cancelCapture();test=!test;testButton.setText(test?"Stop test":"Start test");if(!test){profile.release();down.clear();showFunctions();}updateStatus();});detailPanel.addView(testButton);
        detailPanel.addView(text("During a test, use touch or the TV remote to operate this page. Remote Back stops the test or cancels an assignment.",14));
        heading(detailPanel,"Menu controls");
        for(int i=0;i<6;i++) {
            final int action=i;LinearLayout bindingRow=row(),label=column();
            label.addView(text(ControllerProfile.NAMES[i],17));values[i]=text("",14);label.addView(values[i]);
            bindingRow.addView(label,new LinearLayout.LayoutParams(0,-2,1));
            assignButtons[i]=button("Assign",()->{if(waiting==action){cancelCapture();updateStatus();}else begin(action);});
            LinearLayout.LayoutParams assignLP=new LinearLayout.LayoutParams(dp(100),-2);assignLP.setMargins(dp(4),dp(8),dp(4),dp(8));bindingRow.addView(assignButtons[i],assignLP);
            Button defaults=button("Default",()->{cancelCapture();profile.assign(action,null);save();});
            LinearLayout.LayoutParams defaultLP=new LinearLayout.LayoutParams(dp(100),-2);defaultLP.setMargins(dp(4),dp(8),0,dp(8));bindingRow.addView(defaults,defaultLP);
            detailPanel.addView(bindingRow);
        }
        detailPanel.addView(button("Reset this controller’s menu controls",()->{
            cancelCapture();for(int i=0;i<6;i++)profile.assign(i,null);profile.release();save();showFunctions();
        }));
        heading(detailPanel,"During race");
        detailPanel.addView(text("Pause with Back + an extra button, even when either is assigned to racing. Hold both on this controller; release both before using it again.",14));
        pauseValue=text("",14);detailPanel.addView(pauseValue);
        LinearLayout pauseRow=row();
        pauseAssign=button("Assign extra button",()->{if(waiting==6){cancelCapture();updateStatus();}else begin(6);});
        weighted(pauseRow,pauseAssign);
        weighted(pauseRow,button("Disable",()->{cancelCapture();profile.racePauseModifier=null;save();}));
        detailPanel.addView(pauseRow);
        heading(detailPanel,"Device role");roleLabel=text("",15);detailPanel.addView(roleLabel);
        detailPanel.addView(button("Change device role…",()->showRole(device)));
        detailPanel.addView(text("Use Remote / keyboard for a TV remote. Remotes navigate with keyboard keys and cannot occupy gamepad slots. Choices save for this device.",14));
        otherDevices=column();content.addView(otherDevices);
        Button report=button("Save input device report…",()->InputDeviceReport.show(this));
        LinearLayout.LayoutParams reportLayout=new LinearLayout.LayoutParams(-1,-2);
        reportLayout.topMargin=dp(12);content.addView(report,reportLayout);
        refreshDevices();
    }
    @Override protected void onResume(){super.onResume();((InputManager)getSystemService(INPUT_SERVICE)).registerInputDeviceListener(this,null);refreshDevices();}
    @Override protected void onPause(){((InputManager)getSystemService(INPUT_SERVICE)).unregisterInputDeviceListener(this);handler.removeCallbacks(arm);cancelCapture();test=false;testButton.setText("Start test");if(profile!=null){profile.release();showFunctions();}down.clear();super.onPause();}
    @Override protected void onSaveInstanceState(Bundle out){super.onSaveInstanceState(out);out.putString("controller",descriptor);out.putBoolean("show_others",showOthers);out.putBoolean("expanded",expanded);}
    private void choosePlayer(int slot) {
        List<GamepadSlots.Pad> pads=GamepadSlots.attached();String[] names=new String[pads.size()+1];names[0]="Automatic";
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
            .setItems(new String[]{"Default (detect from capabilities)","Game controller (including button-only)","Remote / keyboard"},(dialog,choice)->{
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
            String player="Available";for(int slot=0;slot<2;slot++)if(assigned[slot]!=null && assigned[slot].id==input.getId())player="Player "+(slot+1);
            boolean active=input.getDescriptor().equals(descriptor);if(active)selected=input;
            Button card=button(input.getName()+"\n"+player+(active?(expanded?" · Hide controls":" · Show controls"):" · Test / configure"),()->{
                if(input.getDescriptor().equals(descriptor)) {
                    expanded=!expanded;if(!expanded){cancelCapture();test=false;profile.release();down.clear();testButton.setText("Start test");}
                    refreshDevices();
                }else select(input);
            });card.setTag("device:"+input.getDescriptor());card.setSelected(active);card.setMinHeight(dp(64));
            LinearLayout.LayoutParams cardLP=new LinearLayout.LayoutParams(-1,-2);cardLP.setMargins(0,dp(5),0,dp(5));devices.addView(card,cardLP);
        }
        if(pads.isEmpty())devices.addView(text("No game controller detected. If a controller is misidentified, expand the inputs below and change its device role.",16));
        final int count=otherCount;Button toggle=button((showOthers?"▾  ":"▸  ")+"Remotes and other inputs ("+count+")",()->{showOthers=!showOthers;refreshDevices();});toggle.setTag("others");otherDevices.addView(toggle);
        if(showOthers)for(InputDevice input:InputDeviceRoles.candidates())if(!InputDeviceRoles.isController(input)) {
            LinearLayout card=panel();card.addView(text(input.getName(),17));card.addView(text(InputDeviceRoles.description(input),14));
            Button role=button("Change role…",()->showRole(input));role.setTag("role:"+input.getDescriptor());card.addView(role);otherDevices.addView(card);
        }
        if(selected==null && !pads.isEmpty()){select(GamepadSlots.device(pads.get(0)));return;}
        if(selected==null){device=null;profile=null;waiting=-1;test=false;testButton.setText("Start test");down.clear();}
        else if(device==null || selected.getId()!=device.getId()){select(selected);return;}
        updateStatus();
        if(focusTag!=null){android.view.View replacement=content.findViewWithTag(focusTag);if(replacement!=null)replacement.requestFocus();}
    }
    private void select(InputDevice selected) {
        if(selected==null)return;
        cancelCapture();device=selected;descriptor=selected.getDescriptor();profile=ControllerProfiles.load(this,selected);expanded=true;
        down.clear();java.util.Arrays.fill(latest,0);
        for(InputDevice.MotionRange r:device.getMotionRanges())if(joystick(r) && r.getAxis()>=0 && r.getAxis()<64)latest[r.getAxis()]=rest(r);
        test=false;testButton.setText("Start test");refreshDevices();refreshRows();showFunctions();
    }
    private void refreshRows(){for(int i=0;i<6;i++) {
        values[i].setText(ControllerProfiles.label(profile,i));
        assignButtons[i].setText(waiting==i?"Cancel":"Assign");
        assignButtons[i].setActivated(waiting==i);
    }
        if(pauseValue!=null)pauseValue.setText(profile==null || profile.racePauseModifier==null?"Disabled":
            "Back + "+ControllerProfiles.keyLabel(profile.racePauseModifier.code));
        if(pauseAssign!=null)pauseAssign.setText(waiting==6?"Cancel":"Assign extra button");
    }
    private void save(){ControllerProfiles.save(this,profile);refreshRows();updateStatus();}
    private void cancelCapture(){waiting=-1;armed=false;handler.removeCallbacks(arm);refreshRows();}
    private void begin(int action) {
        if(profile==null){status.setText("Connect and select a gamepad first.");return;}
        waiting=action;armed=false;armAt=android.os.SystemClock.uptimeMillis()+300;
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
    private void captured(ControllerProfile.Binding binding) {
        int backCode=profile.bindings[5]==null?97:profile.bindings[5].code;
        if(waiting==6) {
            if(binding.axis || ControllerProfile.samePauseButton(binding.code,backCode)) {
                status.setText("Choose a different button from Back.");return;
            }
            profile.racePauseModifier=binding;
            cancelCapture();test=true;testButton.setText("Stop test");save();return;
        }
        if(waiting==5 && profile.racePauseModifier!=null && ControllerProfile.samePauseButton(binding.code,profile.racePauseModifier.code)) {
            status.setText("This is the race pause extra button. Disable or change it first.");return;
        }
        for(int i=0;i<6;i++)if(i!=waiting && binding.sameInput(profile.bindings[i])) {
            status.setText("Already assigned to "+ControllerProfile.NAMES[i]+". Clear that assignment first, or press another control.");return;
        }
        profile.assign(waiting,binding);cancelCapture();test=true;testButton.setText("Stop test");save();
    }
    private void updateStatus() {
        if(status==null)return;
        refreshRows();detailPanel.setVisibility(device!=null && expanded?android.view.View.VISIBLE:android.view.View.GONE);
        if(device!=null){selectedTitle.setText(device.getName());roleLabel.setText(InputDeviceRoles.description(device));}
        if(device==null){status.setText("No selected gamepad connected.");functions.setText("");refreshRows();return;}
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
            boolean reserved=test || waiting>=0;
            if(waiting>=0 && armed && event.getAction()==KeyEvent.ACTION_DOWN && event.getRepeatCount()==0)
                captured(new ControllerProfile.Binding(event.getKeyCode()));
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
            raw.setText(description.toString());boolean reserved=test || waiting>=0;
            if(waiting>=0 && waiting<4 && armed && candidate!=null)captured(candidate);
            showFunctions();if(reserved)return true;
        }
        return super.dispatchGenericMotionEvent(event);
    }
    @Override public void onBackPressed() {
        if(waiting>=0){cancelCapture();updateStatus();return;}
        if(test){test=false;profile.release();down.clear();testButton.setText("Start test");showFunctions();updateStatus();return;}
        super.onBackPressed();
    }
    @Override public void onInputDeviceAdded(int id){InputDeviceRoles.changed(id);refreshDevices();}
    @Override public void onInputDeviceRemoved(int id){InputDeviceRoles.changed(id);refreshDevices();}
    @Override public void onInputDeviceChanged(int id){InputDeviceRoles.changed(id);refreshDevices();}
}
