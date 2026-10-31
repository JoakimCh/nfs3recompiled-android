package dev.nfs3hp.port;

/** Stable game action identities, in the original 13-entry Controls table order. */
final class TouchAction {
    static int function(String action) {
        switch(action) {
            case "steer_right": return 0;
            case "steer_left": return 1;
            case "accelerate": return 2;
            case "brake": return 3;
            case "handbrake": return 4;
            case "gear_up": return 5;
            case "gear_down": return 6;
            case "camera": return 7;
            case "horn": return 8;
            case "look_behind": return 9;
            case "recover": return 10;
            case "spike_strip": return 11;
            case "headlights": return 12;
            default: return -1; // Pause/back/keyboard retain their menu route.
        }
    }
}
