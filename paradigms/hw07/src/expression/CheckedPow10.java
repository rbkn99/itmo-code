package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedPow10 extends AbstractUnaryOperation {
    public CheckedPow10(@NotNull CommonExpression expression) {
        super(expression);
    }

    private void check(int y) throws OverflowException {
        if (y < 0) {
            throw new OverflowException();
        }
    }

    private int pow(int y) throws OverflowException {
        int result = 1;
        for (int i = 1; i <= y; i++) {
            if (Integer.MAX_VALUE / 10 < result) {
                throw new OverflowException();
            }
            result *= 10;
        }
        return result;
    }

    @Override
    public int operate(int op) throws OverflowException {
        check(op);
        return pow(op);
    }
}
