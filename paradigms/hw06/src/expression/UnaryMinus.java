package expression;

import com.sun.istack.internal.NotNull;

public class UnaryMinus extends AbstractUnaryOperation {

    public UnaryMinus(@NotNull CommonExpression expression) {
        super(expression);
    }

    @Override
    public int operate(int op) {
        return -op;
    }

    @Override
    public double operate(double op) {
        return -op;
    }
}
