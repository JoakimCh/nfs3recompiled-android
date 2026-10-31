package dev.nfs3hp.port;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
public final class InputDevicePolicyCheck {
    static void check(boolean ok){if(!ok)throw new AssertionError();}
    public static void main(String[] args) {
        int controller=InputDevicePolicy.CONTROLLER,remote=InputDevicePolicy.REMOTE;
        // Exact RC600U TV report: seven generic buttons, GENERIC_1 only,
        // navigation/media keys. Mouse X/Y ranges do not enter joystick counts.
        check(InputDevicePolicy.decide(false,true,7,1,0,5,6,false,0).role==remote);
        check(InputDevicePolicy.decide(false,true,7,1,0,5,6,false,0)==InputDevicePolicy.Decision.NAVIGATION_MEDIA);
        check(InputDevicePolicy.decide(false,true,15,4,2,0,0,false,4).role==controller); // reported Zero2
        check(InputDevicePolicy.decide(false,true,2,0,0,4,0,false,0).role==controller); // button-only
        check(InputDevicePolicy.decide(false,true,1,1,0,4,6,false,1).role==controller); // actual wheel axis
        check(InputDevicePolicy.decide(false,true,2,0,2,4,6,false,0).role==controller); // real hat
        check(InputDevicePolicy.decide(false,true,0,2,0,0,0,false,0).role==controller); // generic-axis joystick without remote evidence
        check(InputDevicePolicy.choose(remote,"controller")==controller); // explicit exception
        for(int axis:new int[]{0,1,11,12,13,14,17,18,19,20,21,22,23})check(InputDevicePolicy.controllerAxis(axis));
        for(int axis=32;axis<=47;axis++)check(!InputDevicePolicy.controllerAxis(axis));
        for(int axis:new int[]{2,3,4,9,10})check(!InputDevicePolicy.controllerAxis(axis));
        check(InputDevicePolicy.automatic(false,true,0,0,0,5,3,false)==remote);
        check(InputDevicePolicy.automatic(false,true,4,0,0,5,3,false)==remote); // bogus gamepad source/buttons on TV remote
        check(InputDevicePolicy.automatic(false,true,0,2,0,5,0,false)==remote); // navigation-only air remote
        check(InputDevicePolicy.automatic(false,true,10,4,2,0,0,false)==controller);
        check(InputDevicePolicy.automatic(false,true,2,0,0,4,0,false)==controller); // real button-only pad
        check(InputDevicePolicy.automatic(false,false,4,0,0,0,0,false)==controller); // named buttons, bad source flags
        check(InputDevicePolicy.automatic(false,true,1,1,0,0,0,false)==controller); // wheel
        check(InputDevicePolicy.automatic(false,true,0,3,0,0,0,false)==controller); // axis-only joystick
        check(InputDevicePolicy.automatic(false,false,0,0,0,4,2,true)==InputDevicePolicy.OTHER); // keyboard
        check(InputDevicePolicy.automatic(true,true,16,4,2,4,0,false)==InputDevicePolicy.OTHER);
        check(InputDevicePolicy.choose(remote,"controller")==controller && InputDevicePolicy.choose(controller,"remote")==remote);
        check(InputDevicePolicy.choose(remote,"default")==remote);
        check(InputDevicePolicy.decide(false,true,10,0,0,4,0,false)==InputDevicePolicy.Decision.GAME_BUTTONS);
        check(InputDevicePolicy.decide(false,true,0,0,0,5,3,false)==InputDevicePolicy.Decision.NAVIGATION_MEDIA);
        for(InputDevicePolicy.Decision decision:InputDevicePolicy.Decision.values())check(!decision.explanation.isEmpty());
        List<String> events=new ArrayList<>();
        RemoteNavigation n=new RemoteNavigation((key,down)->events.add(key+":"+down));
        check(!n.repeating());
        check(n.key(1,23,true,0));check(n.key(1,23,true,10));check(events.equals(Arrays.asList("66:true")));
        n.key(1,23,false,20);check(events.equals(Arrays.asList("66:true","66:false")));events.clear();
        n.key(1,19,true,0);check(n.repeating());n.key(2,19,true,5);n.motion(1,0,-1,6);
        check(events.equals(Arrays.asList("19:true")));n.tick(399);check(events.size()==1);
        n.tick(400);check(events.equals(Arrays.asList("19:true","19:true")));n.tick(401);check(events.size()==2);
        n.key(1,19,false,410);n.key(2,19,false,420);check(events.size()==2);
        n.motion(1,0,0,430);check(events.get(2).equals("19:false"));events.clear();
        n.motion(1,-1,1,0);check(events.equals(Arrays.asList("20:true","21:true")));
        n.motion(1,-.4f,.4f,20);check(events.size()==2);n.motion(1,-.2f,.2f,30);check(events.size()==4);
        n.key(1,4,true,40);n.key(1,97,true,41);check(events.get(4).equals("111:true"));
        n.remove(1);check(events.get(5).equals("111:false"));check(events.size()==6);
        check(!n.key(1,24,true,50)); // volume stays an OS key
        n.key(4,22,true,0);n.release();check(!n.repeating());int end=events.size();n.tick(999);check(events.size()==end);
        System.out.println("PASS RC600U generic-axis remote regression; Zero2, button-only, wheel/hat and generic-only joystick preservation. PASS shared device roles: TV remotes/phantom devices excluded; button-only pads, wheels and joysticks retained; explicit roles. PASS remote keyboard: codes, duplicates, two devices, key/axis overlap, repeats, hysteresis, unplug/pause cleanup.");
    }
}
