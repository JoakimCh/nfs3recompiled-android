package dev.nfs3hp.port;
import java.nio.*;
import java.util.*;
public class ControlProfileUpgradeCheck {
    public static void main(String[] args) {
        byte[] fresh = new byte[ControlProfile.FILE_SIZE];
        ByteBuffer b = ByteBuffer.wrap(fresh).order(ByteOrder.LITTLE_ENDIAN);
        b.putInt(0, fresh.length);
        ControlProfile.apply(fresh, ControlProfile.Kind.GAMEPADS);
        if (b.getInt(0xe30+0x38) != 0xffff || b.getInt(0xe30+0x88+0x38) != 0xffff) throw new AssertionError("new device shape");
        b.putInt(0xe30+0x38,0); b.putInt(0xe30+0x88+0x38,0);
        // A custom in-game binding, force feedback and axis response must survive.
        b.putInt(ControlProfile.TABLES[0]+16,0x00000302);
        b.putInt(0xe30+0x44,61); b.putInt(0xe30+0x48,13);
        byte[] before=fresh.clone();
        if (!ControlProfile.upgradeButtonRecords(fresh)) throw new AssertionError("old shape not upgraded");
        for (int i=0;i<fresh.length;i++) {
            boolean allowed=(i>=0xe30+0x38 && i<0xe30+0x3c)||(i>=0xe30+0x88+0x38 && i<0xe30+0x88+0x3c);
            if (!allowed && before[i]!=fresh[i]) throw new AssertionError("changed unrelated byte "+i);
        }
        if (ControlProfile.upgradeButtonRecords(fresh)) throw new AssertionError("not idempotent");
        if (ControlProfile.upgradeButtonRecords(new byte[9])) throw new AssertionError("invalid file");
        b.putInt(0xe30+0x38,0); b.put(0xe30+4,(byte)'X');
        before=fresh.clone();
        if (ControlProfile.upgradeButtonRecords(fresh)||!Arrays.equals(before,fresh)) throw new AssertionError("modified unknown device");
        System.out.println("PASS: config migration preserves all bindings/settings, new device shape, idempotence and invalid/unknown inputs");
    }
}
