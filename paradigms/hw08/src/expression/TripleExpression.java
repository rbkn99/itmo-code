package expression;

import exceptions.EvaluateException;

public interface TripleExpression<T> {
    T evaluate(T x, T y, T z) throws EvaluateException;
}
