package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public interface Type<T> {
    T parseNumber(final String number) throws InvalidTypeException;

    T add(T x, T y) throws OverflowException;

    T sub(T x, T y) throws OverflowException;

    T mul(T x, T y) throws OverflowException;

    T div(T x, T y) throws OverflowException;

    T not(T x) throws OverflowException;

    T count(T x);

    T max(T x, T y);

    T min(T x, T y);
}
