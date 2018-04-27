package expression;

import com.sun.istack.internal.NotNull;
import exceptions.LogArgumentException;
import exceptions.LogBaseException;
import exceptions.OverflowException;

public class CheckedLog extends AbstractBinaryOperation {
    public CheckedLog(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    private void check(int x, int y) throws LogArgumentException, LogBaseException {
        if (x <= 0) {
            throw new LogArgumentException();
        }
        if (y <= 0 || y == 1) {
            throw new LogBaseException();
        }
    }

    private int log(int x, int y) {
        int result = 0;
        while (y <= x) {
            result++;
            x /= y;
        }
        return result;
    }

    @Override
    public int operate(int x, int y) throws LogArgumentException, LogBaseException {
        check(x, y);
        return log(x, y);
    }
}
