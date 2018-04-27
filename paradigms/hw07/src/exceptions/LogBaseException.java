package exceptions;

public class LogBaseException extends EvaluateException {
    public LogBaseException() {
        super("log base <= 0 or == 1");
    }
}
