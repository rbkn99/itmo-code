package expression;

import com.sun.istack.internal.NotNull;

public class Divide extends AbstractBinaryOperation {

    public Divide(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    @Override
    public int operate(int leftOp, int rightOp) {
        //assert rightOp != 0;
        return leftOp / rightOp;
    }

    @Override
    public double operate(double leftOp, double rightOp) {
        //assert rightOp != 0;
        return leftOp / rightOp;
    }
}
