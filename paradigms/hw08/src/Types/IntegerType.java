package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public class IntegerType implements Type<Integer> {
    @Override
    public Integer parseNumber(String number) throws InvalidTypeException {
        try {
            return Integer.parseInt(number);
        }
        catch (NumberFormatException e) {
            throw new InvalidTypeException();
        }
    }

    @Override
    public Integer add(Integer x, Integer y) throws OverflowException {
        if (x > 0 && Integer.MAX_VALUE - x < y || x < 0 && Integer.MIN_VALUE - x > y) {
            throw new OverflowException();
        }
        return x + y;
    }

    @Override
    public Integer sub(Integer x, Integer y) throws OverflowException {
        if (y < 0 && Integer.MAX_VALUE + y < x || y > 0 && Integer.MIN_VALUE + y > x) {
            throw new OverflowException();
        }
        return x - y;
    }

    @Override
    public Integer mul(Integer x, Integer y) throws OverflowException {
        if (x > 0 && y > 0 && Integer.MAX_VALUE / x < y) {
            throw new OverflowException();
        }
        if (x > 0 && y < 0 && Integer.MIN_VALUE / x > y) {
            throw new OverflowException();
        }
        if (x < 0 && y > 0 && Integer.MIN_VALUE / y > x) {
            throw new OverflowException();
        }
        if (x < 0 && y < 0 && Integer.MAX_VALUE / x > y) {
            throw new OverflowException();
        }
        return x * y;
    }

    @Override
    public Integer div(Integer x, Integer y) throws OverflowException {
        if (y == 0) {
            throw new OverflowException();
        }
        if (x == Integer.MIN_VALUE && y == -1) {
            throw new OverflowException();
        }
        return x / y;
    }

    @Override
    public Integer not(Integer x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException();
        }
        return -x;
    }

    @Override
    public Integer count(Integer x) {
        return Integer.bitCount(x);
    }

    @Override
    public Integer max(Integer x, Integer y) {
        return x > y ? x : y;
    }

    @Override
    public Integer min(Integer x, Integer y) {
        return x < y ? x : y;
    }
}
