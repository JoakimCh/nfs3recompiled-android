package dev.nfs3hp.port;
import java.util.ArrayDeque;
/** Bounded, thread-safe controller-event history; contains no typed text. */
final class InputEventBuffer {
    private final ArrayDeque<String> lines=new ArrayDeque<>();
    private long sequence,dropped;
    synchronized void add(long uptimeMs,String text) {
        String clean=text.replace("\r","\\r").replace("\n","\\n");
        if(clean.length()>2048)clean=clean.substring(0,2048);
        lines.addLast((++sequence)+" uptime_ms="+uptimeMs+" "+clean);
        if(lines.size()>512){lines.removeFirst();++dropped;}
    }
    synchronized long version(){return sequence;}
    synchronized String snapshot(){
        StringBuilder b=new StringBuilder("version="+sequence+"\ndropped="+dropped+"\n");
        for(String line:lines)b.append(line).append('\n');return b.toString();
    }
}
