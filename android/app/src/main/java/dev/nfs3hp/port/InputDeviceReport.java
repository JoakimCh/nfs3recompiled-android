package dev.nfs3hp.port;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ClipData;
import android.content.ContentValues;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.provider.MediaStore;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.Toast;
import androidx.core.content.FileProvider;
import org.json.JSONArray;
import org.json.JSONObject;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

/** On-demand capabilities snapshot. No game launch, event recording or SDL initialization. */
public final class InputDeviceReport {
    private static final AtomicBoolean exporting=new AtomicBoolean();
    public static void show(Activity a) {
        new AlertDialog.Builder(a).setTitle("Input device report")
            .setMessage("Share or save connected input details and controller setup for troubleshooting. Includes app and device information.")
            .setPositiveButton("Share",(d,w)->export(a,false))
            .setNeutralButton("Save to Downloads",(d,w)->export(a,true)).setNegativeButton("Close",null).show();
    }
    private static JSONArray sources(int sources) {
        JSONArray list=new JSONArray();int[] values={InputDevice.SOURCE_KEYBOARD,InputDevice.SOURCE_DPAD,InputDevice.SOURCE_GAMEPAD,
            InputDevice.SOURCE_JOYSTICK,InputDevice.SOURCE_MOUSE,InputDevice.SOURCE_TOUCHSCREEN,InputDevice.SOURCE_TOUCHPAD,
            InputDevice.SOURCE_STYLUS,InputDevice.SOURCE_TRACKBALL,InputDevice.SOURCE_ROTARY_ENCODER};
        String[] names={"KEYBOARD","DPAD","GAMEPAD","JOYSTICK","MOUSE","TOUCHSCREEN","TOUCHPAD","STYLUS","TRACKBALL","ROTARY_ENCODER"};
        for(int i=0;i<values.length;i++)if((sources&values[i])==values[i])list.put(names[i]);return list;
    }
    private static JSONObject snapshot(Activity a) throws Exception {
        InputDeviceRoles.initialize(a);
        android.content.pm.PackageInfo info=a.getPackageManager().getPackageInfo(a.getPackageName(),0);
        JSONObject root=new JSONObject().put("schema",1).put("report_type","input_device_capabilities")
            .put("created_at_unix_ms",System.currentTimeMillis()).put("package",a.getPackageName())
            .put("app_version",info.versionName)
            .put("version_code",Build.VERSION.SDK_INT>=28?info.getLongVersionCode():info.versionCode)
            .put("android_sdk",Build.VERSION.SDK_INT).put("android_release",Build.VERSION.RELEASE)
            .put("manufacturer",Build.MANUFACTURER).put("model",Build.MODEL).put("brand",Build.BRAND)
            .put("device",Build.DEVICE).put("product",Build.PRODUCT).put("board",Build.BOARD).put("hardware",Build.HARDWARE)
            .put("build_fingerprint",Build.FINGERPRINT).put("supported_abis",new JSONArray(java.util.Arrays.asList(Build.SUPPORTED_ABIS)))
            .put("inventory_source","Android InputDevice capabilities; classifier is shared with SDL Android enumeration")
            .put("contains_recorded_events",false);
        android.content.SharedPreferences prefs=GamePreferences.get(a);
        GamepadSlots.Pad[] resolved=GamepadSlots.resolve(prefs);JSONArray players=new JSONArray();
        for(int slot=0;slot<2;slot++)players.put(new JSONObject().put("player",slot+1)
            .put("mode",GamepadSlots.assigned(prefs,slot).isEmpty()?"automatic":"assigned")
            .put("saved_descriptor",GamepadSlots.assigned(prefs,slot)).put("saved_name",GamepadSlots.assignedName(prefs,slot))
            .put("resolved_device_id",resolved[slot]==null?JSONObject.NULL:resolved[slot].id));
        root.put("players",players);JSONArray devices=new JSONArray();
        int[] ids=InputDevice.getDeviceIds();java.util.Arrays.sort(ids);
        for(int id:ids) {
            InputDevice d=InputDevice.getDevice(id);JSONObject item=new JSONObject().put("id",id);devices.put(item);
            if(d==null){item.put("error","Device disconnected while collecting inventory");continue;}
            try {
                item.put("name",d.getName()).put("descriptor",d.getDescriptor()).put("vendor_id",d.getVendorId()).put("product_id",d.getProductId())
                    .put("vendor_hex",String.format(java.util.Locale.ROOT,"%04x",d.getVendorId()))
                    .put("product_hex",String.format(java.util.Locale.ROOT,"%04x",d.getProductId()))
                    .put("virtual",d.isVirtual()).put("external",Build.VERSION.SDK_INT>=29?d.isExternal():JSONObject.NULL).put("keyboard_type",d.getKeyboardType())
                    .put("controller_number",d.getControllerNumber()).put("sources",d.getSources())
                    .put("sources_hex",String.format(java.util.Locale.ROOT,"0x%08x",d.getSources())).put("source_names",sources(d.getSources()))
                    .put("has_vibrator",d.getVibrator().hasVibrator()).put("has_microphone",d.hasMicrophone());
                InputDeviceRoles.Capabilities c=InputDeviceRoles.capabilities(d);
                item.put("classifier",new JSONObject().put("automatic_role",role(c.decision.role)).put("reason_code",c.decision.name())
                    .put("reason",c.decision.explanation).put("game_buttons",c.buttons).put("joystick_axes",c.axes).put("hat_axes",c.hats).put("controller_axes",c.controllerAxes).put("generic_axes",c.genericAxes)
                    .put("navigation_keys",c.navigation).put("media_keys",c.media).put("declares_controller_source",c.declared)
                    .put("saved_role",InputDeviceRoles.setting(d)).put("effective_role",InputDeviceRoles.description(d))
                    .put("eligible_for_player_slot",InputDeviceRoles.isController(d)));
                JSONArray assigned=new JSONArray();for(int slot=0;slot<2;slot++)if(resolved[slot]!=null && resolved[slot].id==id)assigned.put(slot+1);
                item.put("players",assigned);
                int[] codes=new int[KeyEvent.getMaxKeyCode()+1];for(int code=0;code<codes.length;code++)codes[code]=code;
                boolean[] has=d.hasKeys(codes);JSONArray keys=new JSONArray();
                for(int code=0;code<codes.length;code++)if(has[code])keys.put(new JSONObject().put("code",code).put("name",KeyEvent.keyCodeToString(code)));
                item.put("supported_keys",keys);JSONArray axes=new JSONArray();
                for(InputDevice.MotionRange r:d.getMotionRanges())axes.put(new JSONObject().put("axis",r.getAxis()).put("name",MotionEvent.axisToString(r.getAxis()))
                    .put("source",r.getSource()).put("source_names",sources(r.getSource())).put("min",r.getMin()).put("max",r.getMax())
                    .put("range",r.getRange()).put("flat",r.getFlat()).put("fuzz",r.getFuzz()).put("resolution",r.getResolution()));
                item.put("motion_ranges",axes);ControllerProfile profile=ControllerProfiles.load(a,d);JSONArray mappings=new JSONArray();
                for(int i=0;i<6;i++)mappings.put(new JSONObject().put("function",ControllerProfile.NAMES[i])
                    .put("binding",profile.bindings[i]==null?JSONObject.NULL:profile.bindings[i].encode())
                    .put("display",ControllerProfiles.label(profile,i)));
                item.put("menu_controls",mappings);
            }catch(Exception e){item.put("collection_error",e.toString());}
        }
        return root.put("devices",devices);
    }
    private static String role(int role){return role==InputDevicePolicy.CONTROLLER?"controller":role==InputDevicePolicy.REMOTE?"remote_keyboard":"other";}
    private static void export(Activity a,boolean downloads) {
        if(!exporting.compareAndSet(false,true)){Toast.makeText(a,"A report is already being prepared",Toast.LENGTH_SHORT).show();return;}
        new Thread(()->{
            Uri pending=null;File partial=null;
            try {
                JSONObject report=snapshot(a);File folder=new File(a.getFilesDir(),"device-reports");
                if(!folder.isDirectory() && !folder.mkdirs())throw new IOException("Cannot create report folder");
                String name="nfs3-input-devices-"+System.currentTimeMillis()+".zip";File zip=new File(folder,name);partial=new File(folder,name+".partial");
                try(ZipOutputStream out=new ZipOutputStream(new FileOutputStream(partial))) {
                    out.putNextEntry(new ZipEntry("report.json"));out.write(report.toString(2).getBytes(StandardCharsets.UTF_8));out.closeEntry();
                    out.putNextEntry(new ZipEntry("README.txt"));out.write(("NFS III input device capabilities snapshot\n\nGenerated from the launcher without game execution or input recording.\nIncludes every Android device returned by InputDevice.getDeviceIds, supported keycodes, motion ranges, classification reasons, role overrides and player resolution. Device capabilities are reported by Android firmware and may be inaccurate.\n\nThis report contains Android inventory, not a native SDL live-state capture. The role policy is the same one used by the SDL Android bridge and player assignment.\n").getBytes(StandardCharsets.UTF_8));out.closeEntry();
                }
                if(!partial.renameTo(zip))throw new IOException("Cannot finish report file");partial=null;
                if(downloads) {
                    if(Build.VERSION.SDK_INT<29)throw new IOException("Use Share on this Android version");
                    ContentValues values=new ContentValues();values.put(MediaStore.MediaColumns.DISPLAY_NAME,name);values.put(MediaStore.MediaColumns.MIME_TYPE,"application/zip");
                    values.put(MediaStore.MediaColumns.RELATIVE_PATH,"Download/");values.put(MediaStore.MediaColumns.IS_PENDING,1);
                    pending=a.getContentResolver().insert(MediaStore.Downloads.EXTERNAL_CONTENT_URI,values);if(pending==null)throw new IOException("Downloads unavailable");
                    try(OutputStream out=a.getContentResolver().openOutputStream(pending)){if(out==null)throw new IOException("Cannot write report");Files.copy(zip.toPath(),out);}
                    ContentValues done=new ContentValues();done.put(MediaStore.MediaColumns.IS_PENDING,0);a.getContentResolver().update(pending,done,null,null);pending=null;
                    a.runOnUiThread(()->Toast.makeText(a,"Saved "+name+" to Downloads",Toast.LENGTH_LONG).show());
                }else {
                    Uri uri=FileProvider.getUriForFile(a,a.getPackageName()+".crashreports",zip);
                    Intent send=new Intent(Intent.ACTION_SEND).setType("application/zip").putExtra(Intent.EXTRA_STREAM,uri)
                        .addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                    send.setClipData(ClipData.newRawUri("Input device report",uri));
                    a.runOnUiThread(()->{try{a.startActivity(Intent.createChooser(send,"Share input device report"));}catch(Exception e){Toast.makeText(a,"Use Save to Downloads instead",Toast.LENGTH_LONG).show();}});
                }
            }catch(Exception e) {
                if(pending!=null)a.getContentResolver().delete(pending,null,null);if(partial!=null)partial.delete();
                String message=e.getMessage();a.runOnUiThread(()->Toast.makeText(a,"Could not save device report: "+message,Toast.LENGTH_LONG).show());
            }finally{exporting.set(false);}
        },"NFS3-device-report").start();
    }
}
