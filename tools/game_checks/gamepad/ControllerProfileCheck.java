package dev.nfs3hp.port;
public final class ControllerProfileCheck {
    private static void check(boolean ok){if(!ok)throw new AssertionError();}
    private static boolean held(long state,int action){return (state&(1L<<(8+action)))!=0;}
    public static void main(String[] args) {
        ControllerProfile p=new ControllerProfile("one"),q=new ControllerProfile("two");
        check(p.snapshot()==0);
        ControllerProfile combo=new ControllerProfile("combo");
        check(combo.racePauseSnapshot()==0);
        combo.racePauseModifier=new ControllerProfile.Binding(96);
        long comboState=combo.racePauseSnapshot();
        check((comboState&(1L<<16))!=0 && (comboState&3)==3);
        check((comboState&(3L<<17))==0 && ((comboState>>32)&3)==3);
        combo.key(97,true);check((combo.racePauseSnapshot()&(1L<<17))!=0);
        check((combo.racePauseSnapshot()&(1L<<18))==0);
        combo.key(96,true);check((combo.racePauseSnapshot()&(3L<<17))==(3L<<17));
        check(q.racePauseSnapshot()==0);
        combo.release();check((combo.racePauseSnapshot()&(3L<<17))==0);
        combo.assign(5,new ControllerProfile.Binding(109));
        check((combo.racePauseSnapshot()&(1L<<8))!=0);
        combo.racePauseModifier=new ControllerProfile.Binding(4);
        check(combo.racePauseSnapshot()==0); // Back/Select aliases are one button.
        combo.racePauseModifier=new ControllerProfile.Binding(97);
        combo.assign(5,null);check(combo.racePauseModifier==null);
        combo.racePauseModifier=new ControllerProfile.Binding(250);
        combo.key(250,true);check(combo.usesKey(250));
        check((combo.racePauseSnapshot()&(1L<<18))!=0);
        check(((combo.racePauseSnapshot()>>25)&31)==0); // unmapped Android key

        ControllerProfile hats=new ControllerProfile("generic hats");
        hats.axis(15,0);hats.axis(16,0);check(hats.snapshot()==0);
        hats.axis(16,-1);long automatic=hats.snapshot();
        check(held(automatic,0) && (automatic&15)==15 && (automatic&(1L<<53))!=0);
        hats.axis(15,1);check(held(hats.snapshot(),0)&&held(hats.snapshot(),3));
        hats.axis(16,-.4f);check(held(hats.snapshot(),0));hats.axis(16,-.2f);check(!held(hats.snapshot(),0));
        hats.release();check(!held(hats.snapshot(),3));
        hats.axis(0,1);check(hats.preview(3,hats.snapshot()));hats.axis(0,0);check(!hats.preview(3,hats.snapshot()));
        hats.key(19,true);check(held(hats.snapshot(),0));hats.key(19,false);
        hats.assign(0,new ControllerProfile.Binding(15,-1,0,2));hats.axis(15,-1);
        check(held(hats.snapshot(),0) && !held(hats.snapshot(),2));
        ControllerProfile face=new ControllerProfile("single defaults");
        for(int code:new int[]{108,109,23,4}){face.key(code,true);check(!held(face.snapshot(),4)&&!held(face.snapshot(),5));face.key(code,false);}
        face.key(96,true);check(held(face.snapshot(),4)&&!held(face.snapshot(),5));face.key(96,false);
        face.key(97,true);check(!held(face.snapshot(),4)&&held(face.snapshot(),5));face.release();
        face.assign(4,new ControllerProfile.Binding(108));face.assign(5,new ControllerProfile.Binding(109));
        face.key(96,true);face.key(97,true);check(!held(face.snapshot(),4)&&!held(face.snapshot(),5));face.release();
        face.key(108,true);check(held(face.snapshot(),4)&&!held(face.snapshot(),5));face.release();
        face.key(109,true);check(!held(face.snapshot(),4)&&held(face.snapshot(),5));face.release();
        p.assign(0,new ControllerProfile.Binding(16,-1,0,2));
        p.assign(1,new ControllerProfile.Binding(16,1,0,2));
        p.assign(2,new ControllerProfile.Binding(15,-1,0,2));
        p.assign(3,new ControllerProfile.Binding(15,1,0,2));
        p.axis(16,-1);p.axis(15,-1);long state=p.snapshot();
        check(held(state,0)&&held(state,2)&&!held(state,1)&&!held(state,3));
        check(q.snapshot()==0 && (state&(1L<<48))!=0);
        p.axis(16,-.3f);check(held(p.snapshot(),0));p.axis(16,-.2f);check(!held(p.snapshot(),0));
        p.release();check(!held(p.snapshot(),2));
        p.assign(4,new ControllerProfile.Binding(97));p.key(97,true);state=p.snapshot();
        check(held(state,4)&&!held(state,5)); // B confirm never also back.
        p.assign(5,new ControllerProfile.Binding(96));p.key(96,true);state=p.snapshot();
        check(held(state,5)&&!held(state,4));
        p.release();p.key(99,true);check(!held(p.snapshot(),4)&&!held(p.snapshot(),5));
        p.assign(0,new ControllerProfile.Binding(199));p.key(199,true);check(held(p.snapshot(),0));
        check((p.snapshot()&(1L<<(16+11)))!=0);
        p.release();check(!held(p.snapshot(),0));
        p.assign(0,new ControllerProfile.Binding(17,1,-1,2)); // trigger -1 at rest
        p.release();check(!held(p.snapshot(),0));p.axis(17,1);check(held(p.snapshot(),0));check((p.snapshot()&(1L<<30))!=0);
        ControllerProfile partial=new ControllerProfile("partial");
        partial.assign(0,new ControllerProfile.Binding(96));partial.assign(5,new ControllerProfile.Binding(99));
        partial.key(96,true);check(held(partial.snapshot(),0) && !held(partial.snapshot(),4));
        for(ControllerProfile.Binding b:p.bindings)if(b!=null)check(b.encode().equals(ControllerProfile.Binding.decode(b.encode()).encode()));
        for(String bad:new String[]{"", "k:-1", "a:64:1:0:2", "a:0:0:0:2", "a:0:1:NaN:2", "a:0:1:0:0"})check(ControllerProfile.Binding.decode(bad)==null);
        System.out.println("ControllerProfileCheck PASS: generic default hats with simultaneous X/Y, no face aliases, single custom buttons, defaults, arbitrary buttons, hats/axes, hysteresis, diagonals, A/B swap without duplicates, release, per-pad isolation, trigger rest, serialization.");
    }
}
