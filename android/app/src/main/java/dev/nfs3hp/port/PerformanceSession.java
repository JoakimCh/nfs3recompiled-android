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
    // OVERLAY is the legacy boolean, retained only for preference migration.
    public static final String COLLECT="perf_collect", OVERLAY="perf_overlay";
    static final String OVERLAY_MODE="perf_overlay_mode";
    static final String DISABLED="disabled", FPS="fps", VERBOSE="verbose";
    static final int OFF_LEVEL=0, FPS_LEVEL=1, DETAILED_LEVEL=2;

    static String overlayMode(SharedPreferences preferences) {
        String mode=preferences.getString(OVERLAY_MODE,null);
        if(DISABLED.equals(mode)||FPS.equals(mode)||VERBOSE.equals(mode))return mode;
        // Preserve an existing enabled overlay as Verbose until explicitly changed.
        return preferences.getBoolean(OVERLAY,false)?VERBOSE:DISABLED;
    }
    static void setOverlayMode(SharedPreferences preferences,String mode) {
        if(!DISABLED.equals(mode)&&!FPS.equals(mode)&&!VERBOSE.equals(mode))mode=DISABLED;
        preferences.edit().putString(OVERLAY_MODE,mode).remove(OVERLAY).apply();
    }
    static void clearLegacySettings(SharedPreferences preferences) {
        if (preferences.contains("perf_opaque_shader"))
            preferences.edit().remove("perf_opaque_shader").apply();
    }
    static void reset(SharedPreferences preferences) {
        preferences.edit().remove(COLLECT).remove(OVERLAY).remove(OVERLAY_MODE).remove("perf_opaque_shader").apply();
    }
    static int instrumentationLevel(SharedPreferences preferences) {
        String mode=overlayMode(preferences);
        if(preferences.getBoolean(COLLECT,false)||VERBOSE.equals(mode))return DETAILED_LEVEL;
        return FPS.equals(mode)?FPS_LEVEL:OFF_LEVEL;
    }
    private static final String SCHEMA="nfs3-performance-v5";
    private static final String EXTRA_COLUMNS="race_main_calls,race_main_elapsed_ns,race_main_cpu_ns,queue_throttle_calls,queue_throttle_elapsed_ns,queue_throttle_cpu_ns,queue_finish_calls,queue_finish_elapsed_ns,queue_finish_cpu_ns,present_calls,present_elapsed_ns,present_cpu_ns,swap_calls,swap_elapsed_ns,swap_cpu_ns,pace_sleep_calls,pace_sleep_elapsed_ns,pace_sleep_cpu_ns,game_cycle_calls,game_cycle_elapsed_ns,game_cycle_cpu_ns,reserved_adjacent_pairs,reserved_identical_pairs,reserved_break_texture,reserved_break_levels,reserved_break_format,reserved_break_wrap,reserved_break_depth,reserved_break_blend,reserved_break_cull,reserved_break_chroma,reserved_break_clip,reserved_break_fog,reserved_break_gamma,reserved_boundary_analysis_elapsed_ns,reserved_boundary_analysis_cpu_ns,gl_idle_wait_calls,gl_idle_wait_elapsed_ns,gl_idle_wait_cpu_ns,opaque_draws,opaque_vertices,shader_switches,opaque_program_available,depth_steps_active,vertex_compatible_passes,vertex_fast_passes,vertex_retry_passes";
    private final Activity activity;
    private final Handler ui=new Handler(Looper.getMainLooper());
    private final HandlerThread worker;
    private final Handler disk;
    private final boolean collect, show;
    private final String overlayMode;
    private final String gamePrecision;
    private TextView overlay;
    private long[] previous;
    private boolean resumed, closed, storageFailed;
    private int savedSamples;
    private static File directory(Context c) { return new File(c.getFilesDir(),"performance-reports"); }
    private static native long[] nativeSnapshot();
    private static native void nativeActive(boolean active);

    PerformanceSession(Activity a, ViewGroup parent) {
        activity=a;gamePrecision=a.getString(R.string.game_precision);
        SharedPreferences p=GamePreferences.get(a);
        collect=p.getBoolean(COLLECT,false);overlayMode=overlayMode(p);show=!DISABLED.equals(overlayMode);
        if(collect) {
            worker=new HandlerThread("NFS3-performance");worker.start();disk=new Handler(worker.getLooper());
        } else {worker=null;disk=null;}
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
                metadata.put("app_abi",VertexSettings.armv7() ? "armeabi-v7a" : "arm64-v8a").put("package",a.getPackageName());
                metadata.put("overlay",show).put("overlay_mode",overlayMode).put("instrumentation","detailed").put("opaque_shader",true);
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
                String precision=a.getString(R.string.game_precision);
                metadata.put("effective_precision",precision);
                metadata.put("game_precision",precision);
                metadata.put("vertex_arithmetic","DOUBLE".equals(precision) ? "hardware-double" : VertexSettings.armv7() ? "compatible-single" : "checked-float-with-retry");
                metadata.put("full_detail_mirror",p.getBoolean(GamePreferences.FULL_MIRROR,false));
                metadata.put("vertex_counter_notes","Pass counters cover track, object, environment-map and eligible vector dispatches; excludes per-polygon helpers and direct vector/matrix operations. Retry also increments compatible. In DOUBLE builds the compatible column counts direct hardware-double passes. Counters require performance recording or the Verbose overlay.");
                metadata.put("timing_notes","CPU scopes overlap and must not be summed. Game-cycle elapsed excludes explicit frame-cap sleep and includes game-thread queue waits; CPU figures use thread CPU time. Submit CPU is GL-thread work inside drawPending. Swap elapsed is not GPU execution time. FPS uses the full sampling window; frame-time averages and p95 exclude intervals over one second. Legacy batch-boundary fields 285..299 are reserved and zero; the analysis pass has been removed.");
                metadata.put("notes","Cumulative counters sampled once/second. Frame intervals are completed SDL swaps, not GPU times. Intervals over 1 second are counted as excluded gaps. Submission CPU is GL-thread CPU time inside drawPending; submission elapsed includes waits. Overlay overhead is included. Menus and loading are not automatically classified. In-game detail settings are not captured. CSV limited to first 14400 samples (4 hours). Histogram bins: 0..249 milliseconds, bin 250 includes 250..1000 ms.");
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
            long[] v=nativeSnapshot();if(v==null||(v.length!=FIELDS&&v.length!=2))return;
            if(collect&&v.length==FIELDS)disk.post(() -> save(v));
            if(display&&overlay!=null&&previous!=null)
                overlay.setText(FPS.equals(overlayMode)?describeFps(previous,v):describe(previous,v,gamePrecision));
            previous=v;
        } catch(UnsatisfiedLinkError ignored) { if(overlay!=null)overlay.setText("Performance unavailable: game library not loaded"); }
    }
    static String describeFps(long[] a,long[] b) {
        long ns=b[0]-a[0];
        // The FPS-only producer uses a 32-bit atomic counter; account for wrap.
        long frames=b.length==2?(b[1]-a[1])&0xffffffffL:b[1]-a[1];
        if(ns<=0||frames<0)return "Performance: waiting for frames…";
        return String.format(Locale.ROOT,"%.1f FPS",frames*1e9/ns);
    }
    // Native snapshot layout is kept stable for recorded CSV files.
    private static final int FIELDS=311, FRAMES=1, INTERVALS=2, INTERVAL_NS=3,
        DRAWS=5, SUBMIT_CPU_NS=9, WIDTH=11, HEIGHT=12, HISTOGRAM=13,
        QUEUE_NS=268, SWAP_NS=277, GAME_CPU_NS=284,
        OPAQUE_DRAWS=303, OPAQUE_AVAILABLE=306,
        VERTEX_DIRECT=308, VERTEX_FLOAT=309, VERTEX_RETRY=310;

    static String describe(long[] a,long[] b,String precision) {
        if(a.length!=FIELDS||b.length!=FIELDS)return "Performance statistics unavailable";
        long frames=b[FRAMES]-a[FRAMES],sampleNs=b[0]-a[0];
        if(sampleNs<=0||frames<0)return "Performance: waiting for frames…";
        double fps=frames*1e9/sampleNs;
        long intervals=b[INTERVALS]-a[INTERVALS],intervalNs=b[INTERVAL_NS]-a[INTERVAL_NS];
        if(frames==0||intervals<=0||intervalNs<=0)
            return String.format(Locale.ROOT,"%.1f FPS | frame timing unavailable\n%s | %d×%d",
                fps,precision,b[WIDTH],b[HEIGHT]);

        long target=(intervals*95+99)/100,seen=0;
        int p95=250;
        for(int i=0;i<=250;i++) {
            seen+=b[HISTOGRAM+i]-a[HISTOGRAM+i];
            if(seen>=target){p95=i;break;}
        }
        String percentile=p95==250?"≥250":"<"+(p95+1);
        long draws=b[DRAWS]-a[DRAWS];
        String opaque=b[OPAQUE_AVAILABLE]!=0
            ? String.format(Locale.ROOT,"opaque %.0f%%",draws>0?100.0*(b[OPAQUE_DRAWS]-a[OPAQUE_DRAWS])/draws:0)
            : "opaque shader unavailable";
        String text=String.format(Locale.ROOT,
            "%.1f FPS | frame %.1f ms | p95 %s ms\n"+
            "%.0f draws/frame | %s | %d×%d\n"+
            "CPU game %.1f | submit %.1f ms/frame\n"+
            "Queue wait %.1f | swap %.1f ms/frame",
            fps,intervalNs/1e6/intervals,percentile,draws/(double)frames,opaque,b[WIDTH],b[HEIGHT],
            (b[GAME_CPU_NS]-a[GAME_CPU_NS])/1e6/frames,(b[SUBMIT_CPU_NS]-a[SUBMIT_CPU_NS])/1e6/frames,
            (b[QUEUE_NS]-a[QUEUE_NS])/1e6/frames,(b[SWAP_NS]-a[SWAP_NS])/1e6/frames);
        double direct=(b[VERTEX_DIRECT]-a[VERTEX_DIRECT])/(double)frames;
        if("DOUBLE".equals(precision))
            return text+String.format(Locale.ROOT,"\nDOUBLE | vertex double passes %.1f/frame",direct);
        double fast=(b[VERTEX_FLOAT]-a[VERTEX_FLOAT])/(double)frames;
        double retry=(b[VERTEX_RETRY]-a[VERTEX_RETRY])/(double)frames;
        if(fast==0&&retry==0)
            return text+String.format(Locale.ROOT,"\nSINGLE | vertex compatible passes %.1f/frame",direct);
        return text+String.format(Locale.ROOT,"\nSINGLE | vertex passes/frame: float %.1f | fallback %.1f | retry %.1f",
            fast,direct,retry);
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
        if(closed)return;pause();closed=true;
        if(worker!=null) {
            worker.quitSafely();
            try{worker.join(1000);}catch(InterruptedException e){Thread.currentThread().interrupt();}
        }
    }

    public static void showReport(Activity a) {
        new AlertDialog.Builder(a).setTitle("Performance report")
            .setMessage("Share or save the latest collected game session. Includes device/build, experiment settings and per-second counters; no game files. Reports remain available after a crash.")
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
