package expression;

import com.sun.istack.internal.NotNull;
import exceptions.LogArgumentException;

public class CheckedLog10 extends AbstractUnaryOperation {
    public CheckedLog10(@NotNull CommonExpression expression) {
        super(expression);
    }

    private void check(int x) throws LogArgumentException {
        if (x <= 0) {
            throw new LogArgumentException();
        }
    }

    private int log(int x) {
        int result = 0;
        while (10 <= x) {
            result++;
            x /= 10;
        }
        return result;
    }

    @Override
    public int operate(int op) throws LogArgumentException {
        check(op);
        return log(op);
    }
}
