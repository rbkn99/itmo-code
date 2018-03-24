package expression;

import com.sun.istack.internal.NotNull;

public class Not extends AbstractUnaryOperation {

    public Not(@NotNull CommonExpression expression) {
        super(expression);
    }

    @Override
    public int operate(int op) {
        return ~op;
    }

    @Override
    public double operate(double op) {
        System.err.println("Error! Can't apply NOT operator to double");
        return -1;
    }
}
