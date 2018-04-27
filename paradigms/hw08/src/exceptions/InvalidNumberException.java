package exceptions;

public class InvalidNumberException extends ParserException {
    public InvalidNumberException(String number, int pos, String s) {
        super("invalid number " + number + " at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
