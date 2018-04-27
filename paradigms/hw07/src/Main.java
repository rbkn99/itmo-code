import exceptions.EvaluateException;
import exceptions.ParserException;
import expression.CommonExpression;
import parser.ExpressionParser;

public class Main {
    public static void main(String args[]) throws EvaluateException, ParserException {
        ExpressionParser parser = new ExpressionParser();
        CommonExpression expression = parser.parse("log10 11");
        System.out.println(expression.evaluate(0,0,0));
    }
}
