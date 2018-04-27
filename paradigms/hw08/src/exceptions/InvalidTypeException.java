package exceptions;

public class InvalidTypeException extends ParserException {
    public InvalidTypeException() {
        super("can't parse the number");
    }
}
