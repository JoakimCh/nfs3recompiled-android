package dev.nfs3hp.port;

import java.util.HashSet;

/** Device-independent profile state. No Android calls; shared by setup and play. */
final class ControllerProfile {
    static final String[] NAMES={"Up","Down","Left","Right","Confirm","Back"};
    final String identity;
    final Binding[] bindings=new Binding[6];
    Binding racePauseModifier; // null disables the race-only Back combination.
    private final HashSet<Integer> keys=new HashSet<>();
    private final float[] axes=new float[64];
    private final boolean[] held=new boolean[6];
    private final boolean[] previewHeld=new boolean[4];
    private boolean hatSeen,keysSeen;
    ControllerProfile(String identity) { this.identity=identity; }
    static final class Binding {
        final boolean axis;
        final int code,sign;
        final float rest,span;
        Binding(int code) { this(false,code,0,0,1); }
        Binding(int code,int sign,float rest,float span) { this(true,code,sign,rest,span); }
        private Binding(boolean axis,int code,int sign,float rest,float span) {
            this.axis=axis;this.code=code;this.sign=sign;this.rest=rest;this.span=span;
        }
        String encode() { return axis?"a:"+code+":"+sign+":"+rest+":"+span:"k:"+code; }
        static Binding decode(String value) {
            try {
                String[] p=value.split(":");
                int c=Integer.parseInt(p[1]);
                if(p.length==2 && p[0].equals("k") && c>=0 && c<=1000)return new Binding(c);
                if(p.length==5 && p[0].equals("a") && c>=0 && c<64) {
                    int sign=Integer.parseInt(p[2]);float rest=Float.parseFloat(p[3]),span=Float.parseFloat(p[4]);
                    if(Math.abs(sign)==1 && Float.isFinite(rest) && Float.isFinite(span) && span>0)
                        return new Binding(c,sign,rest,span);
                }
            }catch(RuntimeException ignored){}
            return null;
        }
        boolean active(HashSet<Integer> keys,float[] axes,boolean wasHeld) {
            return axis?(axes[code]-rest)*sign > span*(wasHeld?.125f:.25f):keys.contains(code);
        }
        boolean sameInput(Binding b) { return b!=null && axis==b.axis && code==b.code && (!axis || sign==b.sign); }
    }
    void assign(int action,Binding value) {
        bindings[action]=value;
        if(action==5 && racePauseModifier!=null &&
            samePauseButton(racePauseModifier.code,value==null?97:value.code))racePauseModifier=null;
        release();
    }
    boolean usesKey(int code) {
        for(Binding b:bindings)if(b!=null && !b.axis && b.code==code)return true;
        return racePauseModifier!=null && racePauseModifier.code==code;
    }
    void key(int code,boolean down) { keysSeen=true;if(down)keys.add(code);else keys.remove(code); }
    void axis(int code,float value) {
        if(code>=0 && code<64 && Float.isFinite(value)) {
            axes[code]=value;
            if((code==15 || code==16) && Math.abs(value)>.4883f)hatSeen=true;
        }
    }
    void release() {
        keys.clear();java.util.Arrays.fill(held,false);java.util.Arrays.fill(previewHeld,false);java.util.Arrays.fill(axes,0);
        // Resting triggers may be -1. Avoid a synthetic press after pause.
        for(Binding b:bindings)if(b!=null && b.axis)axes[b.code]=b.rest;
    }
    private boolean defaultKey(int key,int current) {
        if(!keys.contains(key))return false;
        for(int i=0;i<6;i++) {
            Binding b=bindings[i];
            if(i!=current && b!=null && !b.axis && b.code==key)return false;
        }
        return true;
    }
    private boolean defaultAxis(int axis,int sign,int current,boolean wasHeld) {
        for(int i=0;i<6;i++) {
            Binding b=bindings[i];
            if(i!=current && b!=null && b.axis && b.code==axis && b.sign==sign)return false;
        }
        return axes[axis]*sign > (wasHeld?.305f:.4883f);
    }
    boolean preview(int action,long state) {
        boolean active=(state&(1L<<(8+action)))!=0;
        if(action>=4) {
            if((state&(1L<<action))==0)active=defaultKey(action==4?96:97,action);
            return active;
        }
        if(bindings[action]==null) {
            int sign=action==0 || action==2?-1:1;
            active=active || defaultKey(19+action,action) || defaultAxis(action<2?1:0,sign,action,previewHeld[action]);
        }
        previewHeld[action]=active;return active;
    }
    long snapshot() {
        long state=0;
        boolean customFace=keysSeen || bindings[4]!=null || bindings[5]!=null;
        for(int i=0;i<6;i++) {
            Binding b=bindings[i];boolean wasHeld=held[i];
            if(b==null) {
                held[i]=false;
                if(i>=4 && customFace) {
                    // Preserve the other function's conventional defaults.
                    held[i]=defaultKey(i==4?96:97,i);
                    state|=1L<<i;
                } else if(i<4 && hatSeen) {
                    // Android hats are authoritative once actually observed.
                    // SDL may convert them into buttons absent from its mapping.
                    int axis=i<2?16:15,sign=i==0 || i==2?-1:1;
                    held[i]=defaultKey(19+i,i) || defaultAxis(axis,sign,i,wasHeld);
                    state|=(1L<<i)|(1L<<(53+i));
                }
            }else {
                state|=1L<<i;held[i]=b.active(keys,axes,held[i]);
                if(b.axis && i<4) {
                    if(held[i])state|=1L<<48;
                    int source=b.code==0 || b.code==15?(b.sign<0?2:3):
                        b.code==1 || b.code==16?(b.sign<0?0:1):-1;
                    if(b.code==17 || b.code==23)state|=1L<<(16+14);
                    if(b.code==18 || b.code==22)state|=1L<<(16+15);
                    if(source>=0) {
                        state|=1L<<(49+source);
                        if(b.code==15 || b.code==16)state|=1L<<(16+10+source);
                    }
                }
                if(!b.axis) {
                    int source=logicalButton(b.code);
                    if(source>=0)state|=1L<<((i<4?16:32)+source);
                }
            }
            if(held[i])state|=1L<<(8+i);
        }
        return state;
    }
    // Separate from the menu snapshot: physical sources must remain available
    // even when a racing assignment claims their virtual buttons.
    static boolean samePauseButton(int first,int second) {
        int logical=logicalButton(first);
        return first==second || (logical>=0 && logical==logicalButton(second));
    }
    long racePauseSnapshot() {
        if(racePauseModifier==null)return 0;
        Binding back=bindings[5];
        int backCode=back==null?97:back.code;
        if(samePauseButton(backCode,racePauseModifier.code))return 0;
        int b=logicalButton(backCode),m=logicalButton(racePauseModifier.code);
        long sources=(b<0?0:1L<<b)|(m<0?0:1L<<m);
        long menuSources=1L<<1;
        for(int i=0;i<6;i++) {
            Binding input=bindings[i];
            int code=input==null?(i<4?19+i:i==4?96:97):input.axis?-1:input.code;
            if(code==backCode || code==racePauseModifier.code)
                menuSources|=1L<<(i<4?10+i:i==4?0:1);
        }
        return (menuSources<<32)|sources|(1L<<16)|(keys.contains(backCode)?1L<<17:0)
            |(keys.contains(racePauseModifier.code)?1L<<18:0)
            |((long)(b+1)<<20)|((long)(m+1)<<25);
    }
    // Android keycodes -> existing virtual button identity; no vendor IDs.
    static int logicalButton(int code) {
        switch(code) {
        case 23:case 96:return 0;case 97:return 1;case 99:return 2;case 100:return 3;
        case 102:return 4;case 103:return 5;case 106:return 6;case 107:return 7;
        case 4:case 109:return 8;case 108:return 9;
        case 19:return 10;case 20:return 11;case 21:return 12;case 22:return 13;
        case 104:return 14;case 105:return 15;
        default:return code>=188 && code<=203?code-188:-1;
        }
    }
}
