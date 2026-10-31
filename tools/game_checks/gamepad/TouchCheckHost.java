package dev.nfs3hp.port;
import java.util.*;
class TouchCheckHost {
 public static void main(String[] args){
 String[] actions={"steer_right","steer_left","accelerate","brake","handbrake","gear_up","gear_down","camera","horn","look_behind","recover","spike_strip","headlights"};
 for(int i=0;i<actions.length;i++)if(TouchAction.function(actions[i])!=i)throw new AssertionError(actions[i]);
 for(String s:new String[]{"pause","back","keyboard","confirm","unknown"})if(TouchAction.function(s)!=-1)throw new AssertionError(s);
 List<String> events=new ArrayList<>();TouchKeyState state=new TouchKeyState((key,down)->events.add(key+":"+down));
 state.press(-3);state.press(-3);state.release(-3);
 if(!events.equals(Arrays.asList("-3:true")))throw new AssertionError(events);
 state.release(-3);if(!events.equals(Arrays.asList("-3:true","-3:false")))throw new AssertionError(events);
 state.press(-1);state.press(-2);state.press(66);state.releaseAll();
 if(!events.contains("-1:false")||!events.contains("-2:false")||!events.contains("66:false"))throw new AssertionError(events);
 int count=events.size();state.releaseAll();state.release(-3);if(events.size()!=count)throw new AssertionError(events);
 System.out.println("PASS actual Java action IDs and TouchKeyState: 13 actions, legacy menu exclusions, negative tokens, two-finger hold counts and cancel/release-all");
 }
}
