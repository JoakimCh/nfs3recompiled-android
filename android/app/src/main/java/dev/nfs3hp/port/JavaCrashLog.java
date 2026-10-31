package dev.nfs3hp.port;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Writer;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicBoolean;

/** Best-effort Java exception snapshot; always delegates to Android's handler. */
final class JavaCrashLog {
    static final int LIMIT=65536;
    static Thread.UncaughtExceptionHandler handler(File folder,String metadata,Thread.UncaughtExceptionHandler previous) {
        AtomicBoolean writing=new AtomicBoolean();
        return (thread,error)->{
            if(writing.compareAndSet(false,true))try{write(folder,metadata,thread,error);}catch(Throwable ignored){}
            // Preserve normal Android crash logging, process termination and exit records.
            if(previous!=null)previous.uncaughtException(thread,error);else error.printStackTrace();
        };
    }
    private static void write(File folder,String metadata,Thread thread,Throwable error) throws IOException {
        if(!folder.isDirectory() && !folder.mkdirs())throw new IOException("Cannot create crash folder");
        File partial=File.createTempFile("java-crash-",".partial",folder);
        try(FileOutputStream file=new FileOutputStream(partial);
            OutputStreamWriter utf8=new OutputStreamWriter(file,StandardCharsets.UTF_8)) {
            LimitedWriter bounded=new LimitedWriter(utf8,LIMIT);PrintWriter out=new PrintWriter(bounded);
            out.println(metadata);out.println("Time: "+System.currentTimeMillis());out.println("Thread: "+thread.getName());
            error.printStackTrace(out);out.flush();if(out.checkError())throw new IOException("Cannot write crash trace");
            if(bounded.truncated)utf8.write("\n[Java crash trace truncated after "+LIMIT+" characters]\n");
            utf8.flush();file.getFD().sync();
        }
        File complete=new File(folder,partial.getName().replace(".partial",".pending"));
        if(!partial.renameTo(complete))throw new IOException("Cannot commit crash log");
    }
    private static final class LimitedWriter extends Writer {
        final Writer target;int remaining;boolean truncated;
        LimitedWriter(Writer target,int limit){this.target=target;remaining=limit;}
        @Override public void write(char[] chars,int offset,int length) throws IOException {
            int count=Math.min(remaining,length);if(count>0)target.write(chars,offset,count);
            remaining-=count;if(count<length)truncated=true;
        }
        @Override public void flush() throws IOException{target.flush();}
        @Override public void close() throws IOException{target.close();}
    }
}
