package expression;


import com.sun.istack.internal.NotNull;
import exceptions.EvaluateException;

public abstract class AbstractBinaryOperation implements CommonExpression {
    private CommonExpression leftExpression;
    private CommonExpression rightExpression;

    public AbstractBinaryOperation(@NotNull CommonExpression leftExpression, @NotNull CommonExpression rightExpression) {
        this.leftExpression = leftExpression;
        this.rightExpression = rightExpression;
    }

    public abstract int operate(int leftOp, int rightOp) throws EvaluateException;

    @Override
    public int evaluate(int x, int y, int z) throws EvaluateException {
        return operate(leftExpression.evaluate(x, y, z), rightExpression.evaluate(x, y, z));
    }
}
