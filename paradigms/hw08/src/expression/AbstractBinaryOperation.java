package expression;


import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.EvaluateException;

public abstract class AbstractBinaryOperation<T> implements TripleExpression<T> {
    private TripleExpression<T> leftExpression;
    private TripleExpression<T> rightExpression;

    protected Type<T> type;

    public AbstractBinaryOperation(@NotNull TripleExpression<T> leftExpression,
                                   @NotNull TripleExpression<T> rightExpression, Type<T> type) {
        this.leftExpression = leftExpression;
        this.rightExpression = rightExpression;
        this.type = type;
    }

    public abstract T operate(T leftOp, T rightOp) throws EvaluateException;

    @Override
    public T evaluate(T x, T y, T z) throws EvaluateException {
        return operate(leftExpression.evaluate(x, y, z), rightExpression.evaluate(x, y, z));
    }
}
