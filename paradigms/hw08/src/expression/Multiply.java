package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class Multiply<T> extends AbstractBinaryOperation<T> {

    public Multiply(@NotNull TripleExpression<T> leftExp, @NotNull TripleExpression<T> rightExp, Type<T> type) {
        super(leftExp, rightExp, type);
    }

    @Override
    public T operate(T x, T y) throws OverflowException {
        return type.mul(x, y);
    }
}
