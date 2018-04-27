package expression;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.EvaluateException;

public abstract class AbstractUnaryOperation<T> implements TripleExpression<T> {
    private TripleExpression<T> expression;

    protected Type<T> type;

    public AbstractUnaryOperation(@NotNull TripleExpression<T> expression, Type<T> type) {
        this.expression = expression;
        this.type = type;
    }

    public abstract T operate(T op) throws EvaluateException;

    @Override
    public T evaluate(T x, T y, T z) throws EvaluateException {
        return operate(expression.evaluate(x, y, z));
    }
}
