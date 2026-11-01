package dev.nfs3hp.port;

import android.content.Context;
import android.content.SharedPreferences;
import android.view.InputDevice;
import android.view.MotionEvent;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

/** Private per-physical-controller assignments. Never tied to transient device IDs. */
final class ControllerProfiles {
    static String identity(InputDevice device) {
        if(device==null)return "";
        return device.getVendorId()+":"+device.getProductId()+":"+device.getDescriptor();
    }
    private static String prefix(String identity) {
        try {
            byte[] hash=MessageDigest.getInstance("SHA-256").digest(identity.getBytes(StandardCharsets.UTF_8));
            StringBuilder out=new StringBuilder("controller_profile_");
            for(byte b:hash)out.append(String.format(java.util.Locale.ROOT,"%02x",b&255));
            return out.append('_').toString();
        }catch(java.security.NoSuchAlgorithmException impossible){throw new AssertionError(impossible);}
    }
    static ControllerProfile load(Context context,InputDevice device) {
        ControllerProfile p=new ControllerProfile(identity(device));
        SharedPreferences prefs=GamePreferences.get(context);String prefix=prefix(p.identity);
        for(int i=0;i<6;i++)p.bindings[i]=ControllerProfile.Binding.decode(prefs.getString(prefix+i,""));
        for(int i=4;i<6;i++)if(p.bindings[i]!=null && p.bindings[i].axis)p.bindings[i]=null;
        p.racePauseModifier=ControllerProfile.Binding.decode(prefs.getString(prefix+"race_pause_modifier",""));
        if(p.racePauseModifier!=null && (p.racePauseModifier.axis ||
            ControllerProfile.samePauseButton(p.racePauseModifier.code,p.bindings[5]==null?97:p.bindings[5].code)))
            p.racePauseModifier=null;
        p.release();return p;
    }
    static void save(Context context,ControllerProfile p) {
        SharedPreferences.Editor e=GamePreferences.get(context).edit();String prefix=prefix(p.identity);
        for(int i=0;i<6;i++)if(p.bindings[i]==null)e.remove(prefix+i);else e.putString(prefix+i,p.bindings[i].encode());
        if(p.racePauseModifier==null)e.remove(prefix+"race_pause_modifier");
        else e.putString(prefix+"race_pause_modifier",p.racePauseModifier.encode());
        e.apply();
    }
    static void motion(ControllerProfile p,MotionEvent event) {
        for(InputDevice.MotionRange r:event.getDevice().getMotionRanges())
            if((r.getSource()&InputDevice.SOURCE_JOYSTICK)==InputDevice.SOURCE_JOYSTICK)
                p.axis(r.getAxis(),event.getAxisValue(r.getAxis()));
    }
    static String label(ControllerProfile profile,int action) {
        ControllerProfile.Binding b=profile==null?null:profile.bindings[action];
        if(b==null) {
            if(action<4)return "Default: D-pad / hat / X–Y";
            int code=action==4?96:97;
            String label="Default: "+keyLabel(code);
            if(profile!=null)for(int i=0;i<6;i++) {
                ControllerProfile.Binding other=profile.bindings[i];
                if(i!=action && other!=null && !other.axis && other.code==code)
                    return label+" · assigned to "+ControllerProfile.NAMES[i];
            }
            return label;
        }
        return b.axis?MotionEvent.axisToString(b.code)+(b.sign>0?" +":" −"):keyLabel(b.code);
    }
    static String keyLabel(int code) {
        return android.view.KeyEvent.keyCodeToString(code).replace("KEYCODE_","")+" ("+code+")";
    }
}
