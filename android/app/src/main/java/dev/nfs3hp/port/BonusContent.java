package dev.nfs3hp.port;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.util.Arrays;

/** The PC game's own bonus flags, not tournament results or controller presets. */
public final class BonusContent {
    static final int SIZE = 0x20f0, CARS = 0x1768, TRACK = 0x176c, CAR_MASK = 0x1f;

    public static final class State {
        public final boolean cars, track;
        public final int unlockedCars;
        private final int carFlags;

        private State(byte[] bytes) {
            int flags = bytes[CARS] & CAR_MASK;
            carFlags = flags;
            cars = flags == CAR_MASK;
            unlockedCars = Integer.bitCount(flags);
            track = buffer(bytes).getInt(TRACK) != 0;
        }

        /** Index order: El Niño, CLK-GTR, XJR-15, Pursuit Diablo SV, Pursuit El Niño. */
        public boolean car(int index) {
            return (carFlags & carBit(index)) != 0;
        }
    }

    private static int carBit(int index) {
        if (index < 0 || index >= 5) throw new IllegalArgumentException("Unknown bonus car");
        return 1 << index;
    }

    private static ByteBuffer buffer(byte[] bytes) {
        return ByteBuffer.wrap(bytes).order(ByteOrder.LITTLE_ENDIAN);
    }

    private static byte[] load(File file) throws IOException {
        if (file == null || !file.isFile())
            throw new IOException("Start the game once to create its settings, then close it.");
        if (file.length() != SIZE)
            throw new IOException("Unrecognized game settings; no changes made.");
        byte[] bytes = Files.readAllBytes(file.toPath());
        if (bytes.length != SIZE || buffer(bytes).getInt(0) != SIZE)
            throw new IOException("Unrecognized game settings; no changes made.");
        return bytes;
    }

    public static State read(File file) throws IOException {
        return new State(load(file));
    }

    /** Null leaves that group alone. Caller must ensure the game is stopped. */
    public static State update(File file, Boolean cars, Boolean track) throws IOException {
        return updateFlags(file, cars == null ? 0 : CAR_MASK, Boolean.TRUE.equals(cars) ? CAR_MASK : 0, track);
    }

    public static State updateCar(File file, int index, boolean unlocked) throws IOException {
        int mask = carBit(index);
        return updateFlags(file, mask, unlocked ? mask : 0, null);
    }

    private static State updateFlags(File file, int mask, int flags, Boolean track) throws IOException {
        byte[] original = load(file);
        byte[] changed = original.clone();
        changed[CARS] = (byte)((changed[CARS] & ~mask) | flags);
        if (track != null)
            buffer(changed).putInt(TRACK, track ? 1 : 0);
        if (Arrays.equals(original, changed))
            return new State(original);

        File temporary = File.createTempFile("config-unlocks-", ".part", file.getParentFile());
        try {
            try (FileOutputStream out = new FileOutputStream(temporary)) {
                out.write(changed);
                out.getFD().sync();
            }
            byte[] verified = load(temporary);
            if (!Arrays.equals(changed, verified))
                throw new IOException("Could not verify updated settings; no changes made.");
            for (int i = 0; i < SIZE; ++i) {
                boolean allowed = (mask != 0 && i == CARS)
                    || (track != null && i >= TRACK && i < TRACK + 4);
                if (!allowed && verified[i] != original[i])
                    throw new IOException("Unexpected settings change; no changes made.");
            }
            if ((verified[CARS] & ~mask) != (original[CARS] & ~mask)
                    || !Arrays.equals(original, load(file)))
                throw new IOException("Game settings changed; reopen this page and try again.");
            // No non-atomic fallback: a failed move must leave the original intact.
            Files.move(temporary.toPath(), file.toPath(),
                StandardCopyOption.ATOMIC_MOVE, StandardCopyOption.REPLACE_EXISTING);
            return new State(verified);
        } finally {
            Files.deleteIfExists(temporary.toPath());
        }
    }
}
