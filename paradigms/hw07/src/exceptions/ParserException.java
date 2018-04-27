package exceptions;

public class ParserException extends Exception {
    public ParserException(String message) {
        super(message);
    }

    protected int shiftPos(int pos, int stringLength) {
        return pos < stringLength - 1 ? pos + 1 : pos;
    }
}
