package expression;

public class Const implements CommonExpression {
    private Number value;

    public Const(Number value) {
        this.value = value;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return value.intValue();
    }
}
