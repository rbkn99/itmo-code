import expression.CommonExpression;
import expression.parser.ExpressionParser;

public class Main {
    public static void main(String args[]) {
        ExpressionParser parser = new ExpressionParser();
        CommonExpression expression = parser.parse("6 & 1 + 2");
        System.out.println(expression.evaluate(100, 0, 0));
    }
}
