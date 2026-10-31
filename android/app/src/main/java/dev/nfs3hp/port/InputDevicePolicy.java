package dev.nfs3hp.port;

/** Capability policy shared by the SDL bridge, game slots and setup page. */
final class InputDevicePolicy {
    static final int OTHER=0,CONTROLLER=1,REMOTE=2;
    enum Decision {
        VIRTUAL(OTHER,"Virtual input device"),
        KEYBOARD(OTHER,"Alphabetic keyboard without controller source flags"),
        NAVIGATION_MEDIA(REMOTE,"Navigation and media keys without standard controller axes or hats"),
        GAME_BUTTONS(CONTROLLER,"At least two reported game buttons; axes are not required"),
        BUTTONS_AND_AXES(CONTROLLER,"A reported game button together with joystick axes or hats"),
        JOYSTICK_AXES(CONTROLLER,"Declared joystick with axes/hats and no navigation keys"),
        NAVIGATION(REMOTE,"Navigation or media keys without stronger controller evidence"),
        UNCLASSIFIED(OTHER,"No sufficient controller or remote capabilities reported");
        final int role;final String explanation;
        Decision(int role,String explanation){this.role=role;this.explanation=explanation;}
    }
    static Decision decide(boolean virtual,boolean declared,int buttons,int axes,int hats,int navigation,int media,boolean alphabetic) {
        return decide(virtual,declared,buttons,axes,hats,navigation,media,alphabetic,axes);
    }
    static Decision decide(boolean virtual,boolean declared,int buttons,int axes,int hats,int navigation,int media,boolean alphabetic,int controllerAxes) {
        if(virtual)return Decision.VIRTUAL;
        if(alphabetic && !declared)return Decision.KEYBOARD;
        if(media>0 && navigation>=2 && controllerAxes==0 && hats==0)return Decision.NAVIGATION_MEDIA;
        if(buttons>=2)return Decision.GAME_BUTTONS;
        if(buttons>=1 && (axes>=1 || hats>=1))return Decision.BUTTONS_AND_AXES;
        if(declared && navigation==0 && (axes>=2 || hats>=1))return Decision.JOYSTICK_AXES;
        if(navigation>0 || media>0)return Decision.NAVIGATION;
        return Decision.UNCLASSIFIED;
    }
    // Standard Android stick/rotation/trigger/wheel axes. Generic axes and
    // pressure/scroll signals are insufficient controller evidence on a remote.
    static boolean controllerAxis(int axis) {
        return axis==0 || axis==1 || (axis>=11 && axis<=14) || (axis>=17 && axis<=23);
    }
    static int automatic(boolean virtual,boolean declared,int buttons,int axes,int hats,int navigation,int media,boolean alphabetic) {
        return decide(virtual,declared,buttons,axes,hats,navigation,media,alphabetic).role;
    }
    static int choose(int automatic,String setting) {
        return "controller".equals(setting)?CONTROLLER:"remote".equals(setting)?REMOTE:automatic;
    }
    static int remoteKey(int code) {
        switch(code) {
        case 19:case 20:case 21:case 22:case 66:case 111:return code;
        case 23:case 96:case 160:return 66; // OK / A / numpad Enter
        case 4:case 97:return 111; // Back / B
        default:return -1;
        }
    }
}
