package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedAdd extends AbstractBinaryOperation {

    public CheckedAdd(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    private void check(int x, int y) throws OverflowException {
        if (x > 0 && Integer.MAX_VALUE - x < y || x < 0 && Integer.MIN_VALUE - x > y) {
            throw new OverflowException();
        }
    }

    @Override
    public int operate(int x, int y) throws OverflowException {
        check(x, y);
        return x + y;
    }
}
