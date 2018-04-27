package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.OverflowException;

public class Count<T> extends AbstractUnaryOperation<T> {

    public Count(@NotNull TripleExpression<T> expression, Type<T> type) {
        super(expression, type);
    }

    public T operate(T op) {
        return type.count(op);
    }
}
