package expression;

import com.sun.istack.internal.NotNull;
import exceptions.EvaluateException;

public abstract class AbstractUnaryOperation implements CommonExpression {
    private CommonExpression expression;

    public AbstractUnaryOperation(@NotNull CommonExpression expression) {
        this.expression = expression;
    }

    public abstract int operate(int op) throws EvaluateException;

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        return operate(expression.evaluate(x, y, z));
    }
}
