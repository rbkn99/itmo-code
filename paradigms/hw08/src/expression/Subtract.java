package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class Subtract<T> extends AbstractBinaryOperation<T> {

    public Subtract(@NotNull TripleExpression<T> leftExp, @NotNull TripleExpression<T> rightExp, Type<T> type) {
        super(leftExp, rightExp, type);
    }

    @Override
    public T operate(T x, T y) throws OverflowException {
        return type.sub(x, y);
    }
}
