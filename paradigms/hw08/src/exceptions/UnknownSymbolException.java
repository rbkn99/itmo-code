package exceptions;

public class UnknownSymbolException extends ParserException {
    public UnknownSymbolException(int pos, String s) {
        super("unknown symbol at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
