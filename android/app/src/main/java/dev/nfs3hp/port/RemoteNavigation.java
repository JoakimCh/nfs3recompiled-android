package dev.nfs3hp.port;

import java.util.HashMap;
import java.util.ArrayList;
import java.util.Map;

/** Turns remote buttons/axes into ordinary keyboard edges, once per key.
 * Independent of Android so overlapping devices, repeats and cleanup are tested.
 */
final class RemoteNavigation {
    interface Sink { void key(int key,boolean down); }
    private final Sink sink;
    private final Map<Long,Integer> sources=new HashMap<>();
    private final Map<Integer,Integer> counts=new HashMap<>();
    private final Map<Integer,Long> repeats=new HashMap<>();
    RemoteNavigation(Sink sink){this.sink=sink;}
    private void set(int device,int source,int key,boolean down,long now) {
        long token=((long)device<<32)|(source&0xffffffffL);
        Integer old=sources.get(token);
        if(down) {
            if(old!=null)return;
            sources.put(token,key);int count=counts.getOrDefault(key,0);counts.put(key,count+1);
            if(count==0){sink.key(key,true);if(key>=19 && key<=22)repeats.put(key,now+400);}
        }else if(old!=null) {
            sources.remove(token);int count=counts.get(old)-1;
            if(count==0){counts.remove(old);repeats.remove(old);sink.key(old,false);}else counts.put(old,count);
        }
    }
    boolean key(int device,int code,boolean down,long now) {
        int key=InputDevicePolicy.remoteKey(code);if(key<0)return false;
        set(device,code,key,down,now);return true;
    }
    void motion(int device,float x,float y,long now) {
        for(int i=0;i<4;i++) {
            int key=19+i,source=-1-i;float value=(i<2?y:x)*(i==0 || i==2?-1:1);
            long token=((long)device<<32)|(source&0xffffffffL);
            set(device,source,key,value>(sources.containsKey(token)?.30f:.49f),now);
        }
    }
    boolean repeating(){return !repeats.isEmpty();}
    void tick(long now) {
        for(int key:new ArrayList<>(repeats.keySet()))if(now>=repeats.get(key)){
            sink.key(key,true);repeats.put(key,now+120);
        }
    }
    void remove(int device) {
        for(Map.Entry<Long,Integer> entry:new ArrayList<>(sources.entrySet()))if((int)(entry.getKey()>>32)==device)
            set(device,(int)(long)entry.getKey(),entry.getValue(),false,0);
    }
    void release() {
        for(int key:new ArrayList<>(counts.keySet()))sink.key(key,false);
        sources.clear();counts.clear();repeats.clear();
    }
}
