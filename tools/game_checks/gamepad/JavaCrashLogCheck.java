package dev.nfs3hp.port;
import java.io.File;
import java.nio.file.Files;
import java.util.concurrent.atomic.AtomicInteger;
public final class JavaCrashLogCheck {
    static void check(boolean value){if(!value)throw new AssertionError();}
    public static void main(String[] args) throws Exception {
        File root=new File(args[0],"java-crash-test-"+System.nanoTime());check(root.mkdirs());
        AtomicInteger delegated=new AtomicInteger();
        Throwable failure=new IllegalStateException("launcher failure",new NullPointerException("cause"));
        Thread.UncaughtExceptionHandler handler=JavaCrashLog.handler(root,"Version: test\nProcess: launcher",(t,e)->{check(e==failure);delegated.incrementAndGet();});
        handler.uncaughtException(Thread.currentThread(),failure);check(delegated.get()==1);
        File[] logs=root.listFiles((d,n)->n.endsWith(".pending"));check(logs.length==1);
        String text=Files.readString(logs[0].toPath());check(text.contains("launcher failure") && text.contains("Caused by:") && text.contains("Version: test"));
        handler.uncaughtException(Thread.currentThread(),failure);check(delegated.get()==2 && root.listFiles((d,n)->n.endsWith(".pending")).length==1);
        File blocked=new File(root,"not-a-folder");Files.writeString(blocked.toPath(),"x");
        JavaCrashLog.handler(blocked,"test",(t,e)->delegated.incrementAndGet()).uncaughtException(Thread.currentThread(),failure);
        check(delegated.get()==3);
        File bounded=new File(root,"bounded");
        JavaCrashLog.handler(bounded,"x".repeat(JavaCrashLog.LIMIT*2),(t,e)->delegated.incrementAndGet()).uncaughtException(Thread.currentThread(),failure);
        File log=bounded.listFiles((d,n)->n.endsWith(".pending"))[0];check(log.length()<JavaCrashLog.LIMIT+200);
        check(Files.readString(log.toPath()).contains("truncated"));check(delegated.get()==4);
        System.out.println("PASS Java crash store: stack/cause/version retained, bounded synced pending file, one capture, original crash handler always delegated including write failure.");
    }
}
