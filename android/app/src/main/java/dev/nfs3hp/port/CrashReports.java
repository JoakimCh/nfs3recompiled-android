package dev.nfs3hp.port;

import android.app.*;
import android.content.*;
import android.net.Uri;
import android.os.Build;
import android.provider.MediaStore;
import android.widget.Toast;
import androidx.core.content.FileProvider;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.zip.*;

/** Collects Android's retained exit trace after the game process has died.
 * No signal handlers, debug mode, logging permission, or automatic uploads. */
public final class CrashReports {
    private static final AtomicBoolean busy = new AtomicBoolean();
    private static File report(Context c) { return new File(c.getFilesDir(), "crash-reports/nfs3-crash-report.zip"); }
    private static boolean alive(Activity a) { return !a.isFinishing() && !a.isDestroyed(); }
    public static void check(Activity a) {
        if (!busy.compareAndSet(false, true)) return;
        new Thread(() -> {
            try {
                if(collectJava(a))return;
                if(Build.VERSION.SDK_INT<30)return;
                long updated = a.getPackageManager().getPackageInfo(a.getPackageName(), 0).lastUpdateTime;
                android.content.SharedPreferences prefs = a.getSharedPreferences("crash-reports", 0);
                long seen = prefs.getLong("seen", 0);
                ActivityManager am = (ActivityManager)a.getSystemService(Context.ACTIVITY_SERVICE);
                for (ApplicationExitInfo exit : am.getHistoricalProcessExitReasons(null, 0, 16)) {
                    int reason = exit.getReason();
                    if (!(exit.getProcessName().equals(a.getPackageName()) || exit.getProcessName().startsWith(a.getPackageName()+":"))
                            || exit.getTimestamp() <= Math.max(seen,prefs.getLong("java_seen",0)) || (reason != ApplicationExitInfo.REASON_CRASH_NATIVE
                            && reason != ApplicationExitInfo.REASON_CRASH && reason != ApplicationExitInfo.REASON_ANR)) continue;
                    long javaTime=prefs.getLong("java_seen",0);
                    if(reason==ApplicationExitInfo.REASON_CRASH && Math.abs(exit.getTimestamp()-javaTime)<3000)continue;
                    File target = report(a); target.getParentFile().mkdirs();
                    File temp = new File(target.getParentFile(), "report.tmp");
                    try (ZipOutputStream zip = new ZipOutputStream(new FileOutputStream(temp))) {
                        String metadata = "NFS III ARMv7 TV app crash report tv21-profile\n"
                            + "Version: " + a.getPackageManager().getPackageInfo(a.getPackageName(), 0).versionName
                            + "\nDevice: " + Build.MANUFACTURER + " " + Build.MODEL
                            + "\nAndroid: " + Build.VERSION.RELEASE + " SDK " + Build.VERSION.SDK_INT
                            + "\nBuild: " + Build.FINGERPRINT + "\nABIs: " + String.join(",", Build.SUPPORTED_ABIS)
                            + "\nProcess: " + exit.getProcessName() + "\nTime: " + exit.getTimestamp()
                            + "\nReason: " + reason + "\nStatus: " + exit.getStatus()
                            + "\nDescription: " + exit.getDescription() + "\n"
                            + (exit.getTimestamp()<updated?"Exit occurred before the current app update; installed version above may differ from crashed version.\n":"");
                        entry(zip, "summary.txt", metadata);
                        // Native traces are tombstone protobufs on Android 12+;
                        // preserve their bytes for offline decoding/symbolication.
                        try (InputStream trace = exit.getTraceInputStream()) {
                            if (trace == null) entry(zip, "trace-unavailable.txt", "Android did not retain a trace for this exit.\n");
                            else {
                                zip.putNextEntry(new ZipEntry(reason == ApplicationExitInfo.REASON_CRASH_NATIVE ? "tombstone.pb" : "trace.txt"));
                                byte[] bytes = new byte[16384]; int n;
                                while ((n = trace.read(bytes)) != -1) zip.write(bytes, 0, n);
                                zip.closeEntry();
                            }
                        } catch (IOException e) { entry(zip, "trace-error.txt", e.toString()); }
                    }
                    java.nio.file.Files.move(temp.toPath(), target.toPath(), java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                    final long timestamp = exit.getTimestamp();
                    a.runOnUiThread(() -> {
                        if (!alive(a)) return;
                        prefs.edit().putLong("seen", timestamp).apply();
                        showLast(a);
                    });
                    break;
                }
            } catch (Exception e) {
                // Report collection must never prevent the launcher opening.
                android.util.Log.w("NFS3CrashReport", "Could not collect exit trace", e);
            } finally { busy.set(false); }
        }, "NFS3-crash-report").start();
    }
    // Package saved Java traces even on Android versions without exit history.
    static boolean collectJava(Activity a) throws Exception {
        android.content.SharedPreferences prefs=a.getSharedPreferences("crash-reports",0);
        long seen=prefs.getLong("java_seen",0);
        File dir=new File(a.getFilesDir(),"crash-reports/java");
        File[] traces=dir.listFiles((folder,name)->name.startsWith("java-crash-") && name.endsWith(".pending"));
        if(traces==null || traces.length==0)return false;
        long newest=0;for(File trace:traces)newest=Math.max(newest,trace.lastModified());
        if(newest<=seen)return false;
        File target=report(a);target.getParentFile().mkdirs();File temp=new File(target.getParentFile(),"java-report.tmp");
        try(ZipOutputStream zip=new ZipOutputStream(new FileOutputStream(temp))) {
            entry(zip,"summary.txt","NFS III saved Java exception report\nJava traces contain the version/process at the time of the crash. Android's original crash handler was retained.\n");
            int index=0;for(File trace:traces)if(trace.lastModified()>seen) {
                zip.putNextEntry(new ZipEntry("java-stack-"+(++index)+".txt"));java.nio.file.Files.copy(trace.toPath(),zip);zip.closeEntry();
            }
        }
        java.nio.file.Files.move(temp.toPath(),target.toPath(),java.nio.file.StandardCopyOption.REPLACE_EXISTING);
        prefs.edit().putLong("java_seen",newest).apply();
        for(File trace:traces)if(trace.lastModified()<=newest)trace.delete();
        a.runOnUiThread(()->{if(alive(a))showLast(a);});return true;
    }
    private static void entry(ZipOutputStream zip, String name, String text) throws IOException {
        zip.putNextEntry(new ZipEntry(name)); zip.write(text.getBytes(StandardCharsets.UTF_8)); zip.closeEntry();
    }
    public static void showLast(Activity a) {
        if (!report(a).isFile()) {
            Toast.makeText(a, "No crash report yet. After a crash, reopen the launcher.", Toast.LENGTH_LONG).show(); return;
        }
        new AlertDialog.Builder(a).setTitle("App crash report")
            .setMessage("A report is ready. Share it, or save it to Downloads and attach it to our chat. It includes device information and the crash trace; no game files.")
            .setPositiveButton("Share report", (d,w) -> share(a))
            .setNeutralButton("Save to Downloads", (d,w) -> save(a))
            .setNegativeButton("Close", null).show();
    }
    private static void share(Activity a) {
        try {
            Uri uri = FileProvider.getUriForFile(a, a.getPackageName()+".crashreports", report(a));
            Intent send = new Intent(Intent.ACTION_SEND).setType("application/zip")
                .putExtra(Intent.EXTRA_STREAM, uri).addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
            send.setClipData(ClipData.newRawUri("Crash report", uri));
            a.startActivity(Intent.createChooser(send, "Share crash report"));
        } catch (Exception e) { Toast.makeText(a, "Sharing unavailable. Use Save to Downloads.", Toast.LENGTH_LONG).show(); }
    }
    private static void save(Activity a) {
        if (Build.VERSION.SDK_INT < 29) { Toast.makeText(a, "Use Share report on this Android version.", Toast.LENGTH_LONG).show(); return; }
        new Thread(() -> {
            Uri uri = null;
            try {
                ContentValues values = new ContentValues();
                String name = "nfs3-crash-"+System.currentTimeMillis()+".zip";
                values.put(MediaStore.MediaColumns.DISPLAY_NAME, name);
                values.put(MediaStore.MediaColumns.MIME_TYPE, "application/zip");
                values.put(MediaStore.MediaColumns.RELATIVE_PATH, "Download/");
                values.put(MediaStore.MediaColumns.IS_PENDING, 1);
                uri = a.getContentResolver().insert(MediaStore.Downloads.EXTERNAL_CONTENT_URI, values);
                if (uri == null) throw new IOException("Downloads unavailable");
                try (InputStream in = new FileInputStream(report(a)); OutputStream out = a.getContentResolver().openOutputStream(uri)) {
                    if (out == null) throw new IOException("Cannot open Downloads file");
                    byte[] b = new byte[16384]; int n;
                    while ((n = in.read(b)) != -1) out.write(b,0,n);
                }
                values.clear(); values.put(MediaStore.MediaColumns.IS_PENDING, 0);
                a.getContentResolver().update(uri, values, null, null);
                a.runOnUiThread(() -> Toast.makeText(a, "Saved to Downloads: "+name, Toast.LENGTH_LONG).show());
            } catch (Exception e) {
                if (uri != null) try { a.getContentResolver().delete(uri,null,null); } catch(Exception ignored) {}
                a.runOnUiThread(() -> Toast.makeText(a, "Could not save report. Try Share report.", Toast.LENGTH_LONG).show());
            }
        }, "NFS3-save-report").start();
    }
}
