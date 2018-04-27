package exceptions;

public class LogArgumentException extends EvaluateException {
    public LogArgumentException() {
        super("log argument <= 0");
    }
}
