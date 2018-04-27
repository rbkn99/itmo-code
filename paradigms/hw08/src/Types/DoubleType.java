package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public class DoubleType implements Type<Double> {
    @Override
    public Double parseNumber(String number) throws InvalidTypeException {
        try {
            return Double.parseDouble(number);
        }
        catch (NumberFormatException e) {
            throw new InvalidTypeException();
        }
    }

    @Override
    public Double add(Double x, Double y) {
        return x + y;
    }

    @Override
    public Double sub(Double x, Double y) {
        return x - y;
    }

    @Override
    public Double mul(Double x, Double y) {
        return x * y;
    }

    @Override
    public Double div(Double x, Double y) {
        return x / y;
    }

    @Override
    public Double not(Double x) {
        return -x;
    }

    @Override
    public Double count(Double x) {
        return Double.valueOf(Long.bitCount(Double.doubleToLongBits(x)));
    }

    @Override
    public Double max(Double x, Double y) {
        return x > y ? x : y;
    }

    @Override
    public Double min(Double x, Double y) {
        return x < y ? x : y;
    }
}
