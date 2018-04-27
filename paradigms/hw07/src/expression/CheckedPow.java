package expression;

import com.sun.istack.internal.NotNull;
import exceptions.LogArgumentException;
import exceptions.LogBaseException;
import exceptions.OverflowException;

public class CheckedPow extends AbstractBinaryOperation {
    public CheckedPow(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    private void check(int x, int y) throws OverflowException {
        if (y < 0) {
            throw new OverflowException();
        }
        if (y == 0 && x == 0) {
            throw new OverflowException();
        }
    }

    private int pow(int x, int y) throws OverflowException {
        int result = 1;
        if (x == 1 || x == 0) {
            return x;
        }
        if (x == -1) {
            return x * (y % 2 == 0 ? -1 : 1);
        }
        for (int i = 1; i <= y; i++) {
            if (x > 0 && Integer.MAX_VALUE / x < result) {
                throw new OverflowException();
            }
            else if (x < 0) {
                if (i % 2 == 1 && -Integer.MAX_VALUE / x < result) {
                    throw new OverflowException();
                }
                if (i % 2 == 0 && Integer.MAX_VALUE / x > result) {
                    throw new OverflowException();
                }
            }
            result *= x;
        }
        return result;
    }

    @Override
    public int operate(int x, int y) throws OverflowException {
        check(x, y);
        return pow(x, y);
    }
}
