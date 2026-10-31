package dev.nfs3hp.port;
import android.content.SharedPreferences;
import java.lang.reflect.Proxy;
import java.nio.*;
import java.nio.file.*;
import java.util.*;

/** Runs the production preference/profile helpers against obsolete launcher settings. */
public class AutomaticControlsCheck {
    static void require(boolean value,String message){if(!value)throw new AssertionError(message);}
    public static void main(String[] args) throws Exception {
        Map<String,Object> old=new HashMap<>();
        old.put("gamepad1_digital",true);old.put("gamepad2_digital",true);
        old.put("gamepad_slot_1","missing-controller");old.put("gamepad_slot_2","also-missing");
        for(int slot=0;slot<2;slot++)for(String id:GamepadButtons.BUTTON_IDS)
            old.put(GamepadButtons.preferenceKey(slot,id),"confirm");
        for(String action:GamePreferences.ACTION_IDS)old.put(GamePreferences.touchKey(action),54);
        SharedPreferences prefs=(SharedPreferences)Proxy.newProxyInstance(AutomaticControlsCheck.class.getClassLoader(),new Class[]{SharedPreferences.class},(p,m,a)->{
            switch(m.getName()){
            case "getString":case "getBoolean":case "getInt":return old.getOrDefault((String)a[0],a[1]);
            case "getAll":return old;
            default:throw new AssertionError("Unexpected preference mutation: "+m.getName());
            }
        });
        for(int slot=0;slot<2;slot++){
            require(!GamepadButtons.digital(prefs,slot),"old digital mode");
            require(GamepadSlots.assigned(prefs,slot).isEmpty(),"old slot pin");
            for(int i=0;i<GamepadButtons.BUTTON_IDS.length;i++)require(GamepadButtons.action(prefs,slot,i).equals(GamepadButtons.DEFAULT_ACTIONS[i]),"old button override");
            for(int i=0;i<2;i++)require(GamepadButtons.triggerRaceValue(prefs,slot,i).isEmpty(),"trigger keyboard duplication");
        }
        require(GamepadButtons.menuEnvironmentValue(0).equals("Return"),"A confirms");
        require(GamepadButtons.menuEnvironmentValue(1).equals("Escape"),"B goes back");
        require(GamepadButtons.menuEnvironmentValue(8).isEmpty() && GamepadButtons.menuEnvironmentValue(9).isEmpty(),"no Select/Start menu aliases");
        for(int i=0;i<GamePreferences.ACTION_IDS.length;i++)
            require(GamePreferences.getTouchKey(prefs,GamePreferences.ACTION_IDS[i])==GamePreferences.DEFAULT_KEYS[i],"old touch override");
        java.util.Map<String,Object> pins=new java.util.HashMap<>();
        pins.put("input_player_1_descriptor","real-pad");
        SharedPreferences chosen=(SharedPreferences)Proxy.newProxyInstance(AutomaticControlsCheck.class.getClassLoader(),new Class[]{SharedPreferences.class},(p,m,a2)->{
            if(m.getName().equals("getString"))return pins.getOrDefault((String)a2[0],a2[1]);
            throw new AssertionError(m.getName());
        });
        require(GamepadSlots.assigned(chosen,0).equals("real-pad") && GamepadSlots.assigned(chosen,1).isEmpty(),"new player choices respected, independent of obsolete pins");
        GamepadSlots.Pad first=new GamepadSlots.Pad(1,"first","pad"),second=new GamepadSlots.Pad(2,"second","pad");
        GamepadSlots.Pad[] pads=GamepadSlots.resolve(new String[]{GamepadSlots.assigned(prefs,0),GamepadSlots.assigned(prefs,1)},Arrays.asList(first,second));
        require(pads[0]==first&&pads[1]==second,"automatic player order");
        pads=GamepadSlots.resolve(new String[]{"",""},Collections.singletonList(first));
        require(pads[0]==first&&pads[1]==null,"one pad duplication");
        require(ControlProfile.wantedKind(prefs,true)==ControlProfile.Kind.GAMEPADS,"pad default preserves axes");
        require(ControlProfile.wantedKind(prefs,false)==ControlProfile.Kind.TOUCH,"no pad touch default");
        Path root=Path.of(args[0]);Path config=root.resolve("fedata/config/config.dat");Files.createDirectories(config.getParent());
        byte[] custom=new byte[ControlProfile.FILE_SIZE];ByteBuffer b=ByteBuffer.wrap(custom).order(ByteOrder.LITTLE_ENDIAN);b.putInt(0,ControlProfile.FILE_SIZE);
        ControlProfile.apply(custom,ControlProfile.Kind.GAMEPADS);
        b.putInt(ControlProfile.TABLES[0]+16,0x00000302); // custom native button assignment
        Files.write(config,custom);
        ControlProfile.driveWith(root.toFile(),prefs,true);
        require(Arrays.equals(custom,Files.readAllBytes(config)),"custom in-game remap overwritten");
        ControlProfile.driveWith(root.toFile(),prefs,false);
        require(Arrays.equals(custom,Files.readAllBytes(config)),"touch launch overwrote custom remap");
        System.out.println("PASS automatic controls: obsolete preferences ignored, A/B defaults distinct, proportional axes, automatic two-player order, no duplicate pad, custom config preserved with/without pad");
    }
}
