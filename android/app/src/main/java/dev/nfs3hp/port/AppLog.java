package dev.nfs3hp.port;

import android.content.Context;
import android.util.Log;

/** The app's log: android.util.Log in debug mode (the Advanced screen,
 *  DebugOptions), silent otherwise -- nothing written to the log at all.
 *  Each process says which it is as its first screen starts (configure);
 *  until then it stays silent. */
public final class AppLog
{
    private static volatile boolean on;

    private AppLog()
    {
    }

    static void configure(Context context)
    {
        on = DebugOptions.enabled(context);
    }

    static void setEnabled(boolean enabled)
    {
        on = enabled;
    }

    public static boolean enabled()
    {
        return on;
    }

    static void v(String tag, String message)
    {
        if (on)
            Log.v(tag, message);
    }

    static void d(String tag, String message)
    {
        if (on)
            Log.d(tag, message);
    }

    static void i(String tag, String message)
    {
        if (on)
            Log.i(tag, message);
    }

    static void w(String tag, String message)
    {
        if (on)
            Log.w(tag, message);
    }

    static void w(String tag, String message, Throwable error)
    {
        if (on)
            Log.w(tag, message, error);
    }

    static void e(String tag, String message)
    {
        if (on)
            Log.e(tag, message);
    }

    static void e(String tag, String message, Throwable error)
    {
        if (on)
            Log.e(tag, message, error);
    }
}
