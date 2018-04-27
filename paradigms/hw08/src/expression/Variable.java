package expression;

public class Variable<T> implements TripleExpression<T> {
    private String value;

    public Variable(String value) {
        this.value = value;
    }

    @Override
    public T evaluate(T x, T y, T z) {
        switch (value) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
        }
        return null;
    }
}
