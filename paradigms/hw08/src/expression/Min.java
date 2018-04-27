package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class Min<T> extends AbstractBinaryOperation<T> {

    public Min(@NotNull TripleExpression<T> leftExp, @NotNull TripleExpression<T> rightExp, Type<T> type) {
        super(leftExp, rightExp, type);
    }

    @Override
    public T operate(T x, T y) {
        return type.min(x, y);
    }
}
