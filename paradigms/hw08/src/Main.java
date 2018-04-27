import exceptions.EvaluateException;
import exceptions.ParserException;
import expression.TripleExpression;
import generic.GenericTabulator;
import generic.Tabulator;
import parser.ExpressionParser;

public class Main {
    public static void main(String args[]) throws EvaluateException, ParserException {
        Tabulator tabulator = new GenericTabulator();
        System.out.println(
                tabulator.tabulate("d", "1.1-3e+5", -6, 10, -15, 19, -1,7)[0][0][0]);
        //ExpressionParser parser = new ExpressionParser();
        //TripleExpression expression = parser.parse("1234567891239");
        //System.out.println(expression.evaluate(-1,1,1));
    }
}
