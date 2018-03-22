package expression;

public class Variable implements CommonExpression {
    private String value;

    public Variable(String value) {
        this.value = value;
    }

    @Override
    public int evaluate(int x) {
        return x;
    }

    @Override
    public double evaluate(double x) {
        return x;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        switch (value) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
        }
        System.err.println("Invalid variable name!");
        return -1;
    }
}
