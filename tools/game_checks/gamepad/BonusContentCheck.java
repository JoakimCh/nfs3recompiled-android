package dev.nfs3hp.port;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.Random;

/** Standalone host check; compile with BonusContent.java and run with java. */
public final class BonusContentCheck {
    private static void require(boolean ok, String message) {
        if (!ok) throw new AssertionError(message);
    }

    public static void main(String[] args) throws Exception {
        File root = Files.createTempDirectory("nfs3-bonus-check-").toFile();
        File config = new File(root, "config.dat");
        try {
            byte[] original = new byte[0x20f0];
            new Random(3).nextBytes(original);
            ByteBuffer.wrap(original).order(ByteOrder.LITTLE_ENDIAN).putInt(0, original.length)
                .putInt(0x176c, 0);
            original[0x1768] = (byte)0xa5; // Partially earned cars, unknown upper bits.
            Files.write(config.toPath(), original);
            BonusContent.State state = BonusContent.read(config);
            require(!state.cars && state.unlockedCars == 2 && !state.track, "partial unlock display");
            state = BonusContent.update(config, true, null);
            byte[] cars = original.clone();
            cars[0x1768] = (byte)0xbf;
            require(state.cars && !state.track, "cars independent of track");
            require(Arrays.equals(cars, Files.readAllBytes(config.toPath())), "car byte only");
            state = BonusContent.update(config, null, true);
            ByteBuffer.wrap(cars).order(ByteOrder.LITTLE_ENDIAN).putInt(0x176c, 1);
            require(state.cars && state.track, "both unlocked");
            require(Arrays.equals(cars, Files.readAllBytes(config.toPath())), "track field only");
            BonusContent.update(config, true, true);
            require(Arrays.equals(cars, Files.readAllBytes(config.toPath())), "idempotent");
            BonusContent.update(config, false, null);
            cars[0x1768] = (byte)0xa0;
            require(Arrays.equals(cars, Files.readAllBytes(config.toPath())), "relock cars preserves track and unknown bits");
            BonusContent.update(config, null, false);
            ByteBuffer.wrap(cars).order(ByteOrder.LITTLE_ENDIAN).putInt(0x176c, 0);
            require(Arrays.equals(cars, Files.readAllBytes(config.toPath())), "relock track preserves every other byte");
            require(root.list().length == 1, "no backup or temporary file left");
            for (byte[] invalid : new byte[][] {new byte[10], new byte[0x20f0]}) {
                Files.write(config.toPath(), invalid);
                try {
                    BonusContent.update(config, true, true);
                    throw new AssertionError("invalid settings accepted");
                } catch (IOException expected) { }
                require(Arrays.equals(invalid, Files.readAllBytes(config.toPath())), "invalid settings untouched");
                require(root.list().length == 1, "no temporary file for invalid input");
            }
            try {
                BonusContent.update(null, true, true);
                throw new AssertionError("missing settings accepted");
            } catch (IOException expected) { }
            System.out.println("BonusContentCheck passed: independent toggles, preservation, idempotence, invalid/missing files, no leftovers.");
        } finally {
            for (File file : root.listFiles()) Files.deleteIfExists(file.toPath());
            Files.delete(root.toPath());
        }
    }
}
