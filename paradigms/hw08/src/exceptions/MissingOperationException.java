package exceptions;

public class MissingOperationException extends ParserException {
    public MissingOperationException(int pos, String s) {
        super("missing operator at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
