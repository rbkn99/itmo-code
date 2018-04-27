package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public class ShortType implements Type<Short> {
    @Override
    public Short parseNumber(String number) throws InvalidTypeException {
        try {
            return (short)Integer.parseInt(number);
        }
        catch (NumberFormatException e) {
            throw new InvalidTypeException();
        }
    }

    @Override
    public Short add(Short x, Short y) {
        return (short)(x + y);
    }

    @Override
    public Short sub(Short x, Short y) {
        return (short)(x - y);
    }

    @Override
    public Short mul(Short x, Short y) {
        return (short)(x * y);
    }

    @Override
    public Short div(Short x, Short y) throws OverflowException {
        if (y == 0) {
            throw new OverflowException();
        }
        return (short)(x / y);
    }

    @Override
    public Short not(Short x) {
        return (short)-x;
    }

    @Override
    public Short count(Short x) {
        return (short)Integer.bitCount(Short.toUnsignedInt(x));
    }

    @Override
    public Short max(Short x, Short y) {
        return x > y ? x : y;
    }

    @Override
    public Short min(Short x, Short y) {
        return x < y ? x : y;
    }
}
