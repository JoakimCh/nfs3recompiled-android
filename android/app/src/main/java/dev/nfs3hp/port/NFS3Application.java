package dev.nfs3hp.port;

import android.app.Application;
import android.os.Build;
import java.io.File;

/** Java crash capture for the launcher and game process, installed before activities. */
public final class NFS3Application extends Application {
    @Override public void onCreate() {
        super.onCreate();
        String version="unknown";
        try{version=getPackageManager().getPackageInfo(getPackageName(),0).versionName;}catch(Exception ignored){}
        String process=Build.VERSION.SDK_INT>=28?Application.getProcessName():getPackageName()+" pid="+android.os.Process.myPid();
        String metadata="NFS III Java crash\nVersion: "+version+"\nProcess: "+process+
            "\nDevice: "+Build.MANUFACTURER+" "+Build.MODEL+"\nAndroid: "+Build.VERSION.RELEASE+" SDK "+Build.VERSION.SDK_INT;
        Thread.setDefaultUncaughtExceptionHandler(JavaCrashLog.handler(new File(getFilesDir(),"crash-reports/java"),metadata,
            Thread.getDefaultUncaughtExceptionHandler()));
    }
}
