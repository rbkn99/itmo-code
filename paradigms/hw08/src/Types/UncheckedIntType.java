package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public class UncheckedIntType implements Type<Integer> {
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
    public Integer add(Integer x, Integer y) {
        return x + y;
    }

    @Override
    public Integer sub(Integer x, Integer y) {
        return x - y;
    }

    @Override
    public Integer mul(Integer x, Integer y) {
        return x * y;
    }

    @Override
    public Integer div(Integer x, Integer y) throws OverflowException {
        if (y == 0) {
            throw new OverflowException();
        }
        return x / y;
    }

    @Override
    public Integer not(Integer x) throws OverflowException {
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
