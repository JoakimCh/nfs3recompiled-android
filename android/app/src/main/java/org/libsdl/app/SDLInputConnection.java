package org.libsdl.app;

import android.text.Editable;
import android.text.Selection;
import android.view.*;
import android.view.inputmethod.BaseInputConnection;
import android.widget.EditText;

class SDLInputConnection extends BaseInputConnection
{
    protected EditText mEditText;
    protected String mCommittedText = "";

    SDLInputConnection(View targetView, boolean fullEditor) {
        super(targetView, fullEditor);
        mEditText = new EditText(targetView.getContext());
        Selection.setSelection(getEditable(), 0);
    }

    @Override
    public Editable getEditable() {
        return mEditText.getEditableText();
    }

    @Override
    public boolean sendKeyEvent(KeyEvent event) {
        // TV IMEs can send key events instead of commitText. Handle their text
        // here: redispatching through the Activity can classify them as pad or
        // remote input, and also bypasses the editor's text bookkeeping.
        if (event.getAction() == KeyEvent.ACTION_MULTIPLE && event.getCharacters() != null) {
            return commitText(event.getCharacters(), 1);
        }
        if (event.getKeyCode() == KeyEvent.KEYCODE_DEL) {
            if (event.getAction() == KeyEvent.ACTION_DOWN) {
                deleteSurroundingTextInCodePoints(1, 0);
            }
            return true;
        }
        int character = event.getUnicodeChar();
        if (!event.isCtrlPressed() && character >= 32 && Character.isValidCodePoint(character)) {
            if (event.getAction() == KeyEvent.ACTION_DOWN) {
                commitText(new String(Character.toChars(character)), 1);
            } else if (event.getAction() == KeyEvent.ACTION_MULTIPLE) {
                for (int i = 0; i < Math.max(1, event.getRepeatCount()); ++i) {
                    commitText(new String(Character.toChars(character)), 1);
                }
            }
            return true;
        }

        /*
         * Return DOES still generate a key event, however.  So rather than using it as the 'click a button' key
         * as we do with physical keyboards, let's just use it to hide the keyboard.
         */

        if (event.getKeyCode() == KeyEvent.KEYCODE_ENTER) {
            if (SDLActivity.onNativeSoftReturnKey()) {
                return true;
            }
        }

        return super.sendKeyEvent(event);
    }

    @Override
    public boolean commitText(CharSequence text, int newCursorPosition) {
        if (!super.commitText(text, newCursorPosition)) {
            return false;
        }
        updateText();
        return true;
    }

    @Override
    public boolean setComposingText(CharSequence text, int newCursorPosition) {
        if (!super.setComposingText(text, newCursorPosition)) {
            return false;
        }
        updateText();
        return true;
    }

    @Override
    public boolean deleteSurroundingText(int beforeLength, int afterLength) {
        return deleteText(beforeLength, afterLength, false);
    }

    @Override
    public boolean deleteSurroundingTextInCodePoints(int beforeLength, int afterLength) {
        return deleteText(beforeLength, afterLength, true);
    }

    private boolean deleteText(int beforeLength, int afterLength, boolean codePoints) {
        if (beforeLength < 0 || afterLength < 0) {
            return false;
        }
        Editable text = getEditable();
        int cursor = Math.min(Selection.getSelectionStart(text), Selection.getSelectionEnd(text));
        if (cursor < 0) {
            return false;
        }
        int available = codePoints ? Character.codePointCount(text, 0, cursor) : cursor;
        // The game may already contain a default name, which this invisible
        // editor does not know about. Keep allowing backspace past its start.
        int extraBackspaces = afterLength == 0 ? Math.max(0, beforeLength - available) : 0;
        finishComposingText();
        boolean deleted = codePoints
                ? super.deleteSurroundingTextInCodePoints(beforeLength, afterLength)
                : super.deleteSurroundingText(beforeLength, afterLength);
        if (!deleted) {
            return false;
        }
        updateText();
        while (extraBackspaces-- > 0) {
            sendCharacterKey('\b');
        }
        return true;
    }

    protected void updateText() {
        final Editable content = getEditable();
        if (content == null) {
            return;
        }

        String text = content.toString();
        int compareLength = Math.min(text.length(), mCommittedText.length());
        int matchLength, offset;

        /* Backspace over characters that are no longer in the string */
        for (matchLength = 0; matchLength < compareLength; ) {
            int codePoint = mCommittedText.codePointAt(matchLength);
            if (codePoint != text.codePointAt(matchLength)) {
                break;
            }
            matchLength += Character.charCount(codePoint);
        }
        /* FIXME: This doesn't handle graphemes, like '🌬️' */
        for (offset = matchLength; offset < mCommittedText.length(); ) {
            int codePoint = mCommittedText.codePointAt(offset);
            sendCharacterKey('\b');
            offset += Character.charCount(codePoint);
        }

        if (matchLength < text.length()) {
            String pendingText = text.subSequence(matchLength, text.length()).toString();
            if (!SDLActivity.dispatchingKeyEvent()) {
                for (offset = 0; offset < pendingText.length(); ) {
                    int codePoint = pendingText.codePointAt(offset);
                    if (codePoint == '\n') {
                        if (SDLActivity.onNativeSoftReturnKey()) {
                            return;
                        }
                    }
                    /* Higher code points don't generate simulated scancodes */
                    if (codePoint > 0 && codePoint < 128) {
                        sendCharacterKey((char)codePoint);
                    }
                    offset += Character.charCount(codePoint);
                }
            }
            sendText(pendingText);
        }
        mCommittedText = text;
    }

    protected void sendCharacterKey(char character) {
        nativeGenerateScancodeForUnichar(character);
    }

    protected void sendText(String text) {
        nativeCommitText(text, 0);
    }

    public static native void nativeCommitText(String text, int newCursorPosition);

    public static native void nativeGenerateScancodeForUnichar(char c);
}

