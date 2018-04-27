package exceptions;

public class ParenthesisImbalanceException extends ParserException {
    public ParenthesisImbalanceException(int pos, String s) {
        super("odd parenthesis imbalance at " + (pos + 1) + " position: " + s.substring(pos));
    }
}
