package expression;

import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class CheckedMultiply extends AbstractBinaryOperation {

    public CheckedMultiply(@NotNull CommonExpression leftExp, @NotNull CommonExpression rightExp) {
        super(leftExp, rightExp);
    }



    /*public static boolean baseCheck(int x, int y) {
        return !(x > 0 && Integer.MAX_VALUE / x < y || x < 0 && Integer.MAX_VALUE / x > y);
    }*/

    private void check(int x, int y) throws OverflowException {
        if (x > 0 && y > 0 && Integer.MAX_VALUE / x < y) {
            throw new OverflowException();
        }
        if (x > 0 && y < 0 && Integer.MIN_VALUE / x > y) {
            throw new OverflowException();
        }
        if (x < 0 && y > 0 && Integer.MIN_VALUE / y > x) {
            throw new OverflowException();
        }
        if (x < 0 && y < 0 && Integer.MAX_VALUE / x > y) {
            throw new OverflowException();
        }
    }

    @Override
    public int operate(int x, int y) throws OverflowException {
        check(x, y);
        return x * y;
    }
}
