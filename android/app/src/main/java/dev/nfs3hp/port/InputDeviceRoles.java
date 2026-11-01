package dev.nfs3hp.port;

import android.content.Context;
import android.content.SharedPreferences;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

/** One eligibility decision for Android input, SDL enumeration, slots and setup.
 * SDK source flags alone are not evidence that a TV device is a game controller.
 */
public final class InputDeviceRoles {
    public static final String DEFAULT="default",CONTROLLER="controller",REMOTE="remote";
    private static volatile SharedPreferences preferences;
    private static final ConcurrentHashMap<Integer,Entry> cache=new ConcurrentHashMap<>();
    private static final SharedPreferences.OnSharedPreferenceChangeListener listener=(p,key)->{if(key==null || key.startsWith("input_role_"))cache.clear();};
    private static final class Entry {
        final String descriptor;final int role;
        Entry(String d,int r){descriptor=d;role=r;}
    }
    public static synchronized void initialize(Context context) {
        if(preferences==null) {
            preferences=context.getApplicationContext().getSharedPreferences(GamePreferences.FILE_NAME,Context.MODE_PRIVATE);
            preferences.registerOnSharedPreferenceChangeListener(listener);
        }
        cache.clear();
    }
    static void changed(int id){cache.remove(id);}
    private static String key(InputDevice d) {
        try {
            String identity=d.getVendorId()+":"+d.getProductId()+":"+d.getDescriptor();
            byte[] bytes=MessageDigest.getInstance("SHA-256").digest(identity.getBytes(StandardCharsets.UTF_8));
            StringBuilder b=new StringBuilder("input_role_");
            for(byte value:bytes)b.append(String.format(java.util.Locale.ROOT,"%02x",value&255));
            return b.toString();
        }catch(java.security.NoSuchAlgorithmException impossible){throw new AssertionError(impossible);}
    }
    static String setting(InputDevice d) {
        SharedPreferences p=preferences;return p==null?DEFAULT:p.getString(key(d),DEFAULT);
    }
    static void set(InputDevice d,String role) {
        if(d==null || preferences==null)return;
        SharedPreferences.Editor e=preferences.edit();
        if(CONTROLLER.equals(role) || REMOTE.equals(role))e.putString(key(d),role);else e.remove(key(d));
        e.apply();cache.remove(d.getId());
    }
    private static int count(InputDevice d,int... keys) {
        int n=0;for(boolean has:d.hasKeys(keys))if(has)n++;return n;
    }
    static boolean declared(InputDevice d) {
        return d.supportsSource(InputDevice.SOURCE_GAMEPAD) || d.supportsSource(InputDevice.SOURCE_JOYSTICK);
    }
    static final class Capabilities {
        final int buttons,axes,hats,navigation,media,controllerAxes,genericAxes;
        final boolean virtual,declared,alphabetic;
        final InputDevicePolicy.Decision decision;
        Capabilities(InputDevice d,int buttons,int axes,int hats,int navigation,int media,int controllerAxes,int genericAxes) {
            this.buttons=buttons;this.axes=axes;this.hats=hats;this.navigation=navigation;this.media=media;
            this.controllerAxes=controllerAxes;this.genericAxes=genericAxes;
            virtual=d.isVirtual();declared=InputDeviceRoles.declared(d);
            alphabetic=d.getKeyboardType()==InputDevice.KEYBOARD_TYPE_ALPHABETIC;
            decision=InputDevicePolicy.decide(virtual,declared,buttons,axes,hats,navigation,media,alphabetic,controllerAxes);
        }
    }
    static Capabilities capabilities(InputDevice d) {
        int buttons=count(d,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,
            188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203);
        int nav=count(d,19,20,21,22,23),media=count(d,KeyEvent.KEYCODE_HOME,KeyEvent.KEYCODE_TV,
            KeyEvent.KEYCODE_GUIDE,KeyEvent.KEYCODE_CHANNEL_UP,KeyEvent.KEYCODE_CHANNEL_DOWN,
            KeyEvent.KEYCODE_VOLUME_UP,KeyEvent.KEYCODE_VOLUME_DOWN,KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE);
        int axes=0,hats=0,controllerAxes=0,genericAxes=0;
        for(InputDevice.MotionRange r:d.getMotionRanges())if((r.getSource()&InputDevice.SOURCE_CLASS_JOYSTICK)!=0 && r.getRange()>0) {
            if(r.getAxis()==MotionEvent.AXIS_HAT_X || r.getAxis()==MotionEvent.AXIS_HAT_Y)hats++;
            else {
                axes++;
                if(InputDevicePolicy.controllerAxis(r.getAxis()))controllerAxes++;
                if(r.getAxis()>=MotionEvent.AXIS_GENERIC_1 && r.getAxis()<=MotionEvent.AXIS_GENERIC_16)genericAxes++;
            }
        }
        return new Capabilities(d,buttons,axes,hats,nav,media,controllerAxes,genericAxes);
    }
    private static int role(InputDevice d) {
        if(d==null || d.getId()<0 || d.getDescriptor()==null || d.getDescriptor().isEmpty())return InputDevicePolicy.OTHER;
        Entry entry=cache.get(d.getId());
        if(entry!=null && entry.descriptor.equals(d.getDescriptor()))return entry.role;
        String selected=setting(d);
        int role=InputDevicePolicy.choose(capabilities(d).decision.role,selected);
        cache.put(d.getId(),new Entry(d.getDescriptor(),role));return role;
    }
    public static boolean isController(InputDevice d){return role(d)==InputDevicePolicy.CONTROLLER;}
    public static boolean isRemote(InputDevice d){return role(d)==InputDevicePolicy.REMOTE;}
    static String description(InputDevice d) {
        String type=isController(d)?"Gamepad":isRemote(d)?"Remote / keyboard":"Keyboard / unclassified";
        return type+(DEFAULT.equals(setting(d))?" (automatic)":" (selected)");
    }
    static List<InputDevice> candidates() {
        List<InputDevice> list=new ArrayList<>();int[] ids=InputDevice.getDeviceIds();java.util.Arrays.sort(ids);
        for(int id:ids) {
            InputDevice d=InputDevice.getDevice(id);if(d==null || id<0 || d.getDescriptor()==null || d.getDescriptor().isEmpty())continue;
            if(declared(d) || d.supportsSource(InputDevice.SOURCE_DPAD) || isController(d) || isRemote(d))list.add(d);
        }
        return list;
    }
}
