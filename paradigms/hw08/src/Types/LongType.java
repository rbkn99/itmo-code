package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

public class LongType implements Type<Long> {
    @Override
    public Long parseNumber(String number) throws InvalidTypeException {
        try {
            return Long.parseLong(number);
        }
        catch (NumberFormatException e) {
            throw new InvalidTypeException();
        }
    }

    @Override
    public Long add(Long x, Long y) {
        return x + y;
    }

    @Override
    public Long sub(Long x, Long y) {
        return x - y;
    }

    @Override
    public Long mul(Long x, Long y) {
        return x * y;
    }

    @Override
    public Long div(Long x, Long y) throws OverflowException {
        if (y == 0) {
            throw new OverflowException();
        }
        return x / y;
    }

    @Override
    public Long not(Long x) {
        return -x;
    }

    @Override
    public Long count(Long x) {
        return Long.valueOf(Long.bitCount(x));
    }

    @Override
    public Long max(Long x, Long y) {
        return x > y ? x : y;
    }

    @Override
    public Long min(Long x, Long y) {
        return x < y ? x : y;
    }
}
