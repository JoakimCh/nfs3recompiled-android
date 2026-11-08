package org.libsdl.app;

import android.view.KeyEvent;
import android.view.View;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import static org.junit.Assert.*;

@RunWith(RobolectricTestRunner.class)
@Config(sdk=34, application=android.app.Application.class)
public class SDLInputConnectionTest {
    private static class Connection extends SDLInputConnection {
        final StringBuilder game = new StringBuilder();
        Connection() {
            super(new View(RuntimeEnvironment.getApplication()), true);
        }
        @Override protected void sendCharacterKey(char character) {
            if (character == '\b' && game.length() > 0) {
                int end = game.length();
                game.delete(game.offsetByCodePoints(end, -1), end);
            }
        }
        @Override protected void sendText(String text) {
            game.append(text);
        }
    }

    @Test public void televisionKeyEventsTypeAndDeleteExactlyOnce() {
        Connection input = new Connection();
        assertTrue(input.sendKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_A)));
        assertTrue(input.sendKeyEvent(new KeyEvent(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_A)));
        assertEquals("a", input.game.toString());
        input.sendKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DEL));
        input.sendKeyEvent(new KeyEvent(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DEL));
        input.commitText("b", 1);
        assertEquals("b", input.game.toString());
        assertEquals("b", input.getEditable().toString());
    }

    @Test public void deletionDoesNotRestoreOldCharactersOnNextCommit() {
        Connection input = new Connection();
        input.commitText("Alex", 1);
        input.deleteSurroundingText(2, 0);
        input.commitText("ice", 1);
        assertEquals("Alice", input.game.toString());
        assertEquals("Alice", input.getEditable().toString());
    }

    @Test public void compositionCanBeReplacedAndDeleted() {
        Connection input = new Connection();
        input.setComposingText("Al", 1);
        input.setComposingText("Alex", 1);
        input.deleteSurroundingText(1, 0);
        input.commitText("c", 1);
        assertEquals("Alec", input.game.toString());
    }

    @Test public void codePointDeletionKeepsSupplementaryCharactersIntact() {
        Connection input = new Connection();
        input.commitText("A\uD83D\uDE00", 1);
        input.deleteSurroundingTextInCodePoints(1, 0);
        input.commitText("b", 1);
        assertEquals("Ab", input.game.toString());
        assertEquals("Ab", input.getEditable().toString());
    }

    @Test public void backspaceCanDeleteAnExistingGameName() {
        Connection input = new Connection();
        input.game.append("Driver");
        input.deleteSurroundingText(2, 0);
        input.commitText("X", 1);
        input.deleteSurroundingTextInCodePoints(2, 0);
        assertEquals("Dri", input.game.toString());
        assertEquals("", input.getEditable().toString());
    }

    @Test public void multipleCharacterKeyEventCommitsTheWholeName() {
        Connection input = new Connection();
        assertTrue(input.sendKeyEvent(new KeyEvent(0, "Player", 0, 0)));
        assertEquals("Player", input.game.toString());
    }
}
