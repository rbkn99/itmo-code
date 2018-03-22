package expression.parser;

import com.sun.istack.internal.NotNull;
import expression.*;
import expression.token.TokenType;

public class ExpressionParser implements Parser {
    private int iterator;
    private String restExpression;
    private TokenType currentToken;
    private int numberValue;
    private String varName;

    @Override
    public CommonExpression parse(@NotNull String expression) {
        iterator = 0;
        restExpression = expression;
        CommonExpression result = addSubOp();
        if (iterator != restExpression.length()) {
            System.err.println("Error! Unreadable expression");
        }
        return result;
    }

    private CommonExpression addSubOp() {
        CommonExpression expression = mulDivOp();
        while (true) {
            switch (currentToken) {
                case ADD:
                    expression = new Add(expression, mulDivOp());
                    break;
                case SUB:
                    expression = new Subtract(expression, mulDivOp());
                    break;
                default:
                    return expression;
            }
        }
    }

    private CommonExpression mulDivOp() {
        CommonExpression expression = baseOp();
        while (true) {
            switch (currentToken) {
                case MUL:
                    expression = new Multiply(expression, baseOp());
                    break;
                case DIV:
                    expression = new Divide(expression, baseOp());
                    break;
                default:
                    return expression;
            }
        }
    }

    private CommonExpression baseOp() {
        getToken();
        switch (currentToken) {
            case CONST:
                Const value = new Const(numberValue);
                getToken();
                return value;
            case VAR:
                Variable variable = new Variable(varName);
                getToken();
                return variable;
            case SUB:
                return new UnaryMinus(baseOp());
            case LP:
                CommonExpression expression = addSubOp();
                if (currentToken != TokenType.RP) {
                    System.err.println("Error! ')' expected");
                }
                getToken();
                return expression;
            default:
                System.err.println("Error! Unknown symbol");
                return null;
        }
    }

    private TokenType getTokenType(char c) {
        if (c >= '0' && c <= '9')
            return TokenType.CONST;
        switch (c) {
            case '+':
                return TokenType.ADD;
            case '-':
                return TokenType.SUB;
            case '*':
                return TokenType.MUL;
            case '/':
                return TokenType.DIV;
            case '(':
                return TokenType.LP;
            case ')':
                return TokenType.RP;
            case 'x':
            case 'y':
            case 'z':
                varName = String.valueOf(c);
                return TokenType.VAR;
            default:
                return TokenType.UNKNOWN_TOKEN;
        }
    }

    private void skipSpaces() {
        while (iterator != restExpression.length() &&
                (restExpression.charAt(iterator) == ' ' || restExpression.charAt(iterator) == '\t')
                ) {
            iterator++;
        }
    }

    private int getConst(char firstC) {
        final StringBuilder sb = new StringBuilder();
        sb.append(firstC);
        while (iterator != restExpression.length() &&
                getTokenType(restExpression.charAt(iterator)) == TokenType.CONST) {
            sb.append(restExpression.charAt(iterator));
            iterator++;
        }
        return Integer.parseUnsignedInt(sb.toString());
    }

    private void getToken() {
        skipSpaces();
        if (iterator == restExpression.length()) {
            currentToken = TokenType.END;
            return;
        }
        char c = restExpression.charAt(iterator);
        iterator++;
        TokenType type = getTokenType(c);
        if (type == TokenType.CONST) {
            numberValue = getConst(c);
        }
        currentToken = type;
    }
}
