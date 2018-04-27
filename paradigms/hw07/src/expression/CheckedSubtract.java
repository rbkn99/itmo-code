package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedSubtract extends AbstractBinaryOperation {

    public CheckedSubtract(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    private void check(int x, int y) throws OverflowException {
        if (y < 0 && Integer.MAX_VALUE + y < x || y > 0 && Integer.MIN_VALUE + y > x) {
            throw new OverflowException();
        }
    }

    @Override
    public int operate(int x, int y) throws OverflowException {
        check(x, y);
        return x - y;
    }
}
