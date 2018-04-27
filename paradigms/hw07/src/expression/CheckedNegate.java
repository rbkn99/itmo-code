package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedNegate extends AbstractUnaryOperation {

    public CheckedNegate(@NotNull CommonExpression expression) {
        super(expression);
    }

    private void check(int x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException();
        }
    }

    @Override
    public int operate(int op) throws OverflowException {
        check(op);
        return -op;
    }
}
