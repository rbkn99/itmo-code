package expression;

import com.sun.istack.internal.NotNull;

public class Or extends AbstractBinaryOperation {

    public Or(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }

    @Override
    public int operate(int leftOp, int rightOp) {
        return leftOp | rightOp;
    }

    @Override
    public double operate(double leftOp, double rightOp) {
        System.err.println("Error! Can't apply OR operator to double");
        return -1;
    }
}
