import expression.*;

public class Main {
    // x*x - 2*x + 1
    public static void main(String args[]) {
        assert args.length > 0;
        BasicExpression var = new Variable("x");
        BasicExpression expression = new Add(
                new Subtract(
                        new Multiply(var, var),
                        new Multiply(new Const(2), var)),
                new Const(1));
        try {
            System.out.println(expression.evaluate(Integer.parseInt(args[0])));
        } catch (NumberFormatException e) {
            System.out.println(expression.evaluate(Double.parseDouble(args[0])));
        }
    }
}
