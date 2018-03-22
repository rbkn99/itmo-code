package expression;


import com.sun.istack.internal.NotNull;

public abstract class AbstractBinaryOperation implements CommonExpression {
    private CommonExpression leftExpression;
    private CommonExpression rightExpression;

    public AbstractBinaryOperation(@NotNull CommonExpression leftExpression, @NotNull CommonExpression rightExpression) {
        this.leftExpression = leftExpression;
        this.rightExpression = rightExpression;
    }

    public abstract int operate(int leftOp, int rightOp);

    public abstract double operate(double leftOp, double rightOp);

    @Override
    public int evaluate(int x) {
        return operate(leftExpression.evaluate(x), rightExpression.evaluate(x));
    }

    @Override
    public double evaluate(double x) {
        return operate(leftExpression.evaluate(x), rightExpression.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return operate(leftExpression.evaluate(x, y, z), rightExpression.evaluate(x, y, z));
    }
}
