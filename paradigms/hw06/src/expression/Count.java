package expression;

import com.sun.istack.internal.NotNull;

public class Count extends AbstractUnaryOperation {

    public Count(@NotNull CommonExpression expression) {
        super(expression);
    }

    @Override
    public int operate(int op) {
        return Integer.bitCount(op);
    }

    @Override
    public double operate(double op) {
        System.err.println("Error! Can't apply COUNT operator to double");
        return -1;
    }
}
