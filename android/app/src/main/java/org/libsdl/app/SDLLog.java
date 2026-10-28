package org.libsdl.app;

import android.util.Log;

/** SDL's Java log, changed for the NFS III port: android.util.Log in debug
 *  mode, silent otherwise, as the port's own log (dev.nfs3hp.port.AppLog). */
final class SDLLog
{
    private SDLLog()
    {
    }

    static int v(String tag, String message) { return dev.nfs3hp.port.AppLog.enabled() ? Log.v(tag, message) : 0; }
    static int v(String tag, String message, Throwable error) { return dev.nfs3hp.port.AppLog.enabled() ? Log.v(tag, message, error) : 0; }
    static int d(String tag, String message) { return dev.nfs3hp.port.AppLog.enabled() ? Log.d(tag, message) : 0; }
    static int d(String tag, String message, Throwable error) { return dev.nfs3hp.port.AppLog.enabled() ? Log.d(tag, message, error) : 0; }
    static int i(String tag, String message) { return dev.nfs3hp.port.AppLog.enabled() ? Log.i(tag, message) : 0; }
    static int i(String tag, String message, Throwable error) { return dev.nfs3hp.port.AppLog.enabled() ? Log.i(tag, message, error) : 0; }
    static int w(String tag, String message) { return dev.nfs3hp.port.AppLog.enabled() ? Log.w(tag, message) : 0; }
    static int w(String tag, String message, Throwable error) { return dev.nfs3hp.port.AppLog.enabled() ? Log.w(tag, message, error) : 0; }
    static int e(String tag, String message) { return dev.nfs3hp.port.AppLog.enabled() ? Log.e(tag, message) : 0; }
    static int e(String tag, String message, Throwable error) { return dev.nfs3hp.port.AppLog.enabled() ? Log.e(tag, message, error) : 0; }
}
