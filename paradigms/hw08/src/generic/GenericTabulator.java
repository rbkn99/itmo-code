package generic;

import Types.*;
import exceptions.EvaluateException;
import exceptions.ParserException;
import expression.TripleExpression;
import parser.ExpressionParser;
import parser.Parser;

public class GenericTabulator implements Tabulator {
    @Override
    public Object[][][] tabulate(String mode, String expression,
                                 int x1, int x2, int y1, int y2, int z1, int z2) throws ParserException {
        return evaluate(routeMode(mode), expression, x1, x2, y1, y2, z1, z2);
    }

    private Type<?> routeMode(String mode) {
        switch (mode) {
            case "i":
                return new IntegerType();
            case "d":
                return new DoubleType();
            case "bi":
                return new BigIntegerType();
            case "u":
                return new UncheckedIntType();
            case "l":
                return new LongType();
            case "s":
                return new ShortType();
            default:
                throw new IllegalArgumentException();
        }
    }

    private <T> Object[][][] evaluate(Type<T> type, String s,
                                     int x1, int x2, int y1, int y2, int z1, int z2) throws ParserException {
        Object[][][] table = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        Parser<T> parser = new ExpressionParser<>(type);
        TripleExpression<T> expression = parser.parse(s);
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                for (int z = z1; z <= z2; z++) {
                    try {
                        table[x - x1][y - y1][z - z1] = expression.evaluate(
                                type.parseNumber(Integer.toString(x)),
                                type.parseNumber(Integer.toString(y)),
                                type.parseNumber(Integer.toString(z)));
                    }
                    catch (EvaluateException | ParserException e) {
                        table[x - x1][y - y1][z - z1] = null;
                    }
                }
            }
        }
        return table;
    }
}
