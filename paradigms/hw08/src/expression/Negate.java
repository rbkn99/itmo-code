package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class Negate<T> extends AbstractUnaryOperation<T> {

    public Negate(@NotNull TripleExpression<T> expression, Type<T> type) {
        super(expression, type);
    }

    @Override
    public T operate(T op) throws OverflowException {
        return type.not(op);
    }
}
