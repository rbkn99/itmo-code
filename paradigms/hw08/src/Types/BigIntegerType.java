package Types;

import exceptions.InvalidTypeException;
import exceptions.OverflowException;

import java.math.BigInteger;

public class BigIntegerType implements Type<BigInteger> {
    @Override
    public BigInteger parseNumber(String number) throws InvalidTypeException {
        try {
            return new BigInteger(number);
        }
        catch (NumberFormatException e) {
            throw new InvalidTypeException();
        }
    }

    @Override
    public BigInteger add(BigInteger x, BigInteger y) {
        return x.add(y);
    }

    @Override
    public BigInteger sub(BigInteger x, BigInteger y) {
        return x.subtract(y);
    }

    @Override
    public BigInteger mul(BigInteger x, BigInteger y) {
        return x.multiply(y);
    }

    @Override
    public BigInteger div(BigInteger x, BigInteger y) throws OverflowException {
        if (y.compareTo(BigInteger.ZERO) == 0) {
            throw new OverflowException();
        }
        return x.divide(y);
    }

    @Override
    public BigInteger not(BigInteger x) {
        return x.negate();
    }

    @Override
    public BigInteger count(BigInteger x) {
        return BigInteger.valueOf(x.bitCount());
    }

    @Override
    public BigInteger max(BigInteger x, BigInteger y) {
        return x.compareTo(y) == 1 ? x : y;
    }

    @Override
    public BigInteger min(BigInteger x, BigInteger y) {
        return x.compareTo(y) == -1 ? x : y;
    }
}
