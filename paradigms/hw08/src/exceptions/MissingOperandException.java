package exceptions;

public class MissingOperandException extends ParserException {
    public MissingOperandException(int pos, String s) {
        super("missing operand at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
