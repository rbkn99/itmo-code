package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedDivide extends AbstractBinaryOperation {

    public CheckedDivide(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    private void check(int x, int y) throws OverflowException {
        if (y == 0) {
            throw new OverflowException();
        }
        if (x == Integer.MIN_VALUE && y == -1) {
            throw new OverflowException();
        }
    }

    @Override
    public int operate(int x, int y) throws OverflowException {
        check(x, y);
        return x / y;
    }
}
