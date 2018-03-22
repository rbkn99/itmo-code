package expression;

import com.sun.istack.internal.NotNull;

public class Subtract extends AbstractBinaryOperation {

    public Subtract(@NotNull BasicExpression leftExp, @NotNull BasicExpression rightExp) {
        super(leftExp, rightExp);
    }

    @Override
    public int operate(int leftOp, int rightOp) {
        return leftOp - rightOp;
    }

    @Override
    public double operate(double leftOp, double rightOp) {
        return leftOp - rightOp;
    }
}
