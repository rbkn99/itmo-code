package exceptions;

public class MissingClosingParenthesisException extends ParserException {
    public MissingClosingParenthesisException(int pos, String s) {
        super("missing ')' at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
