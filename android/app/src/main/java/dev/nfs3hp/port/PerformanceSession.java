package dev.nfs3hp.port;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.*;
import android.graphics.Color;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.*;
import android.provider.MediaStore;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import androidx.core.content.FileProvider;
import org.json.JSONObject;
import java.io.*;
import java.nio.channels.FileLock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.nio.file.StandardOpenOption;
import java.util.Locale;
import java.util.zip.*;

/** Once/second snapshots. The native counters never alter game math or input.
 * Disk writes and report exports stay off the UI and GL threads. */
public final class PerformanceSession {
    public static final String COLLECT="perf_collect", OVERLAY="perf_overlay", OPAQUE="perf_opaque_shader";
    private static final String SCHEMA="nfs3-performance-v3";
    private static final String EXTRA_COLUMNS="race_main_calls,race_main_elapsed_ns,race_main_cpu_ns,queue_throttle_calls,queue_throttle_elapsed_ns,queue_throttle_cpu_ns,queue_finish_calls,queue_finish_elapsed_ns,queue_finish_cpu_ns,present_calls,present_elapsed_ns,present_cpu_ns,swap_calls,swap_elapsed_ns,swap_cpu_ns,pace_sleep_calls,pace_sleep_elapsed_ns,pace_sleep_cpu_ns,game_cycle_calls,game_cycle_elapsed_ns,game_cycle_cpu_ns,adjacent_pairs,identical_pairs,break_texture,break_levels,break_format,break_wrap,break_depth,break_blend,break_cull,break_chroma,break_clip,break_fog,break_gamma,boundary_analysis_elapsed_ns,boundary_analysis_cpu_ns,gl_idle_wait_calls,gl_idle_wait_elapsed_ns,gl_idle_wait_cpu_ns,opaque_draws,opaque_vertices,shader_switches,opaque_program_available,depth_steps_active";
    private final Activity activity;
    private final Handler ui=new Handler(Looper.getMainLooper());
    private final HandlerThread worker=new HandlerThread("NFS3-performance");
    private final Handler disk;
    private final boolean collect, show;
    private TextView overlay;
    private long[] previous;
    private boolean resumed, closed, storageFailed;
    private int savedSamples;
    private static File directory(Context c) { return new File(c.getFilesDir(),"performance-reports"); }
    private static native long[] nativeSnapshot();
    private static native void nativeActive(boolean active);

    PerformanceSession(Activity a, ViewGroup parent) {
        activity=a;
        SharedPreferences p=GamePreferences.get(a);
        collect=p.getBoolean(COLLECT,false);show=p.getBoolean(OVERLAY,false);
        worker.start();disk=new Handler(worker.getLooper());
        if(show && parent!=null) {
            overlay=new TextView(a);
            overlay.setText("Performance: waiting for frames…");
            overlay.setTextColor(Color.WHITE);overlay.setBackgroundColor(0xb0000000);
            overlay.setTextSize(12);overlay.setTypeface(Typeface.MONOSPACE);
            overlay.setPadding(8,4,8,4);overlay.setFocusable(false);overlay.setClickable(false);
            overlay.setImportantForAccessibility(View.IMPORTANT_FOR_ACCESSIBILITY_NO);
            RelativeLayout.LayoutParams lp=new RelativeLayout.LayoutParams(-2,-2);
            lp.addRule(RelativeLayout.ALIGN_PARENT_TOP);lp.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
            lp.leftMargin=12;lp.topMargin=12;parent.addView(overlay,lp);
        }
        if(collect) {
            final JSONObject metadata=new JSONObject();
            try {
                metadata.put("schema",SCHEMA).put("started_unix_ms",System.currentTimeMillis());
                metadata.put("version",a.getPackageManager().getPackageInfo(a.getPackageName(),0).versionName);
                metadata.put("device",Build.MANUFACTURER+" "+Build.MODEL).put("android",Build.VERSION.RELEASE);
                metadata.put("app_abi","armeabi-v7a").put("package",a.getPackageName());
                metadata.put("overlay",show).put("merge_batches",false).put("opaque_shader",p.getBoolean(OPAQUE,true));
                metadata.put("debug_mode",DebugOptions.enabled(p,a.getIntent()));
                metadata.put("fps_cap",p.getInt(GamePreferences.FPS_CAP,30));
                JSONObject display=new JSONObject();
                for(String key:new String[]{GamePreferences.ORIENTATION,GamePreferences.GAMMA,GamePreferences.BRIGHTNESS,GamePreferences.CONTRAST})
                    if(p.contains(key))display.put(key,p.getAll().get(key));
                metadata.put("launcher_display_settings",display);
                JSONObject debug=new JSONObject();
                for(DebugOptions.Option[] group:DebugOptions.ALL)for(DebugOptions.Option option:group)
                    debug.put(option.name,DebugOptions.value(p,a.getIntent(),option));
                debug.put("depth16",DebugOptions.depth16(p,a.getIntent()));metadata.put("debug_options",debug);
                metadata.put("armv7_default_full_mirror",false);
                metadata.put("timing_notes","v3 appends opaque draw/vertex/program-activation counters, followed by current (noncumulative) opaque-program availability and depth-step flags; batch merging removed. v2 appends phase timings and raw adjacent-batch boundaries. Game cycle excludes explicit FPS-cap sleep but includes queue waits, game logic and work between paceFrame checkpoints; it is not total critical-path time. race_main measures main view calls, not full game frames. present includes swap; swap is not GPU time. Timing categories overlap/across parallel threads and must not be summed. Boundary categories overlap and describe raw neighbors even with merging disabled; analysis overhead is separately measured. Epoch changes discard phase scopes spanning pause/resume. GL idle is condition wait only. CSV first 264 columns retain v1 layout.");
                metadata.put("notes","Cumulative counters sampled once/second. Frame intervals are completed SDL swaps, not GPU times. Intervals over 1 second are counted as excluded gaps. CPU is GL-thread CPU time inside drawPending; elapsed includes waits. Overlay overhead is included. Menus and loading are not automatically classified. In-game detail settings are not captured. CSV limited to first 14400 samples (4 hours). Histogram bins: 0..249 milliseconds, bin 250 includes 250..1000 ms.");
            } catch(Exception ignored) { /* Keep capture useful if metadata is partial. */ }
            disk.post(() -> initialize(metadata));
        }
        resume();
    }

    private interface Locked { void run(File d) throws Exception; }
    private static void locked(Context c,Locked action) throws Exception {
        File d=directory(c);if(!d.isDirectory()&&!d.mkdirs())throw new IOException("Cannot create report directory");
        try(RandomAccessFile file=new RandomAccessFile(new File(d,"session.lock"),"rw"); FileLock lock=file.getChannel().lock()) { action.run(d); }
    }
    private void initialize(JSONObject metadata) {
        try { locked(activity,d -> {
            for(String name:new String[]{"metadata.json","samples.csv"}) {
                File f=new File(d,name);if(f.isFile())Files.move(f.toPath(),new File(d,"previous-"+name).toPath(),StandardCopyOption.REPLACE_EXISTING);
            }
            Files.write(new File(d,"metadata.json").toPath(),metadata.toString(2).getBytes(StandardCharsets.UTF_8));
            StringBuilder header=new StringBuilder("monotonic_ns,frames,intervals,interval_sum_ns,batches,gl_draws,vertices,submissions,submission_elapsed_ns,submission_thread_cpu_ns,excluded_gaps,width,height");
            for(int i=0;i<=250;i++)header.append(",frame_ms_bin_").append(i);
            header.append(',').append(EXTRA_COLUMNS);
            header.append('\n');Files.write(new File(d,"samples.csv").toPath(),header.toString().getBytes(StandardCharsets.UTF_8));
        }); } catch(Exception e) { storageError(); }
    }
    private void save(long[] values) {
        if(storageFailed || savedSamples>=14400)return;
        try { locked(activity,d -> {
            StringBuilder line=new StringBuilder();for(long v:values){if(line.length()>0)line.append(',');line.append(v);}line.append('\n');
            Files.write(new File(d,"samples.csv").toPath(),line.toString().getBytes(StandardCharsets.UTF_8),StandardOpenOption.APPEND);
        });++savedSamples; } catch(Exception e) { storageError(); }
    }
    private void storageError() {
        if(storageFailed)return;storageFailed=true;
        activity.runOnUiThread(()->Toast.makeText(activity,"Performance report could not be saved. The overlay can still run.",Toast.LENGTH_LONG).show());
    }
    private final Runnable tick=new Runnable() { public void run() {
        if(!resumed||closed)return;
        snapshot(true);ui.postDelayed(this,1000);
    }};
    private void snapshot(boolean display) {
        try {
            long[] v=nativeSnapshot();if(v==null||v.length!=308)return;
            if(collect)disk.post(() -> save(v));
            if(display&&overlay!=null&&previous!=null)overlay.setText(describe(previous,v));
            previous=v;
        } catch(UnsatisfiedLinkError ignored) { if(overlay!=null)overlay.setText("Performance unavailable: game library not loaded"); }
    }
    static String describe(long[] a,long[] b) {
        long frames=b[1]-a[1],intervals=b[2]-a[2],ns=b[3]-a[3];
        if(frames<=0||intervals<=0||ns<=0)return "Performance: waiting for frames…";
        long draws=b[5]-a[5];
        long target=(intervals*95+99)/100,seen=0;int p95=250;
        for(int i=0;i<=250;i++){seen+=b[13+i]-a[13+i];if(seen>=target){p95=i;break;}}
        String tail=p95==250?"≥250":"<"+(p95+1);
        String text=String.format(Locale.ROOT,"%.1f FPS | %.1f ms | p95 %s ms\n%.0f draws/frame | submit CPU %.2f ms/frame\n%d×%d",
            intervals*1e9/ns,ns/1e6/intervals,tail,draws/(double)frames,
            (b[9]-a[9])/1e6/frames,b[11],b[12]);
        if(b.length>=303)text+=String.format(Locale.ROOT,"\ngame CPU %.1f | queue %.1f | swap %.1f ms/frame",
            (b[284]-a[284])/1e6/frames,(b[268]-a[268])/1e6/frames,(b[277]-a[277])/1e6/frames);
        if(b.length>=308)text+=String.format(Locale.ROOT," | opaque %.0f%%",draws>0?100.0*(b[303]-a[303])/draws:0);
        return text;
    }
    void resume() {
        if(closed||resumed)return;resumed=true;previous=null;
        try{nativeActive(true);}catch(UnsatisfiedLinkError ignored){}
        if(overlay!=null)overlay.setVisibility(View.VISIBLE);
        if(collect||show)ui.post(tick);
    }
    void pause() {
        if(!resumed)return;ui.removeCallbacks(tick);snapshot(false);
        try{nativeActive(false);}catch(UnsatisfiedLinkError ignored){}
        resumed=false;previous=null;if(overlay!=null)overlay.setVisibility(View.GONE);
    }
    void close() {
        if(closed)return;pause();closed=true;worker.quitSafely();
        try{worker.join(1000);}catch(InterruptedException e){Thread.currentThread().interrupt();}
    }

    public static void showReport(Activity a) {
        new AlertDialog.Builder(a).setTitle("Performance report")
            .setMessage("Share or save the latest collected game session. Includes device/build, experiment settings and per-second counters; no game files. Reports remain available after a crash. Changes to performance switches apply on the next game launch.")
            .setPositiveButton("Share",(d,w)->export(a,false))
            .setNeutralButton("Save to Downloads",(d,w)->export(a,true)).setNegativeButton("Close",null).show();
    }
    private static void export(Activity a,boolean downloads) {
        new Thread(() -> {
            Uri pending=null;
            try {
                final File[] result=new File[1];
                locked(a,d -> {
                    File csv=new File(d,"samples.csv"),meta=new File(d,"metadata.json");
                    if(!csv.isFile()||!meta.isFile())throw new IOException("No report yet. Enable collection and play first.");
                    File zip=new File(d,"nfs3-performance-"+System.currentTimeMillis()+".zip");
                    // Only the last exported snapshot is retained; session data is separate.
                    File[] old=d.listFiles((dir,name)->name.endsWith(".zip"));if(old!=null)for(File f:old)f.delete();
                    try(ZipOutputStream z=new ZipOutputStream(new FileOutputStream(zip))) {
                        for(File f:new File[]{meta,csv}) {z.putNextEntry(new ZipEntry(f.getName()));Files.copy(f.toPath(),z);z.closeEntry();}
                    }
                    result[0]=zip;
                });
                File zip=result[0];
                if(downloads) {
                    if(Build.VERSION.SDK_INT<29)throw new IOException("Use Share on this Android version.");
                    ContentValues v=new ContentValues();v.put(MediaStore.MediaColumns.DISPLAY_NAME,zip.getName());
                    v.put(MediaStore.MediaColumns.MIME_TYPE,"application/zip");v.put(MediaStore.MediaColumns.RELATIVE_PATH,"Download/");v.put(MediaStore.MediaColumns.IS_PENDING,1);
                    pending=a.getContentResolver().insert(MediaStore.Downloads.EXTERNAL_CONTENT_URI,v);
                    if(pending==null)throw new IOException("Downloads unavailable");
                    try(OutputStream out=a.getContentResolver().openOutputStream(pending)){if(out==null)throw new IOException("Cannot save report");Files.copy(zip.toPath(),out);}
                    ContentValues done=new ContentValues();done.put(MediaStore.MediaColumns.IS_PENDING,0);a.getContentResolver().update(pending,done,null,null);pending=null;
                    a.runOnUiThread(()->Toast.makeText(a,"Saved "+zip.getName()+" to Downloads",Toast.LENGTH_LONG).show());
                } else {
                    Uri uri=FileProvider.getUriForFile(a,a.getPackageName()+".crashreports",zip);
                    Intent send=new Intent(Intent.ACTION_SEND).setType("application/zip").putExtra(Intent.EXTRA_STREAM,uri).addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                    send.setClipData(ClipData.newRawUri("Performance report",uri));
                    a.runOnUiThread(()->{try{a.startActivity(Intent.createChooser(send,"Share performance report"));}catch(Exception e){Toast.makeText(a,"Use Save to Downloads instead",Toast.LENGTH_LONG).show();}});
                }
            } catch(Exception e) {
                if(pending!=null)a.getContentResolver().delete(pending,null,null);
                String message=e.getMessage();a.runOnUiThread(()->Toast.makeText(a,"Report unavailable: "+message,Toast.LENGTH_LONG).show());
            }
        },"NFS3-export-performance").start();
    }
}
