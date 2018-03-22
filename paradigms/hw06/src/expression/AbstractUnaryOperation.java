package expression;

import com.sun.istack.internal.NotNull;

public abstract class AbstractUnaryOperation  implements CommonExpression {
    private CommonExpression expression;

    public AbstractUnaryOperation(@NotNull CommonExpression expression) {
        this.expression = expression;
    }

    public abstract int operate(int op);

    public abstract double operate(double op);

    @Override
    public int evaluate(int x) {
        return operate(expression.evaluate(x));
    }

    @Override
    public double evaluate(double x) {
        return operate(expression.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return operate(expression.evaluate(x, y, z));
    }
}
