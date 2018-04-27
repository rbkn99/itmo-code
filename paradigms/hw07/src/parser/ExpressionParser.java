package parser;

import com.sun.istack.internal.NotNull;
import exceptions.*;
import exceptions.Parser;
import expression.*;

public class ExpressionParser implements Parser {
    private Tokenizer tokenizer;

    @Override
    public CommonExpression parse(@NotNull String expression) throws ParserException {
        tokenizer = new Tokenizer(expression);
        return addSubOp();
    }

    private CommonExpression addSubOp() throws ParserException {
        CommonExpression expression = mulDivOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case ADD:
                    expression = new CheckedAdd(expression, mulDivOp());
                    break;
                case SUB:
                    expression = new CheckedSubtract(expression, mulDivOp());
                    break;
                default:
                    return expression;
            }
        }
    }

    private CommonExpression mulDivOp() throws ParserException {
        CommonExpression expression = powLogOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case MUL:
                    expression = new CheckedMultiply(expression, powLogOp());
                    break;
                case DIV:
                    expression = new CheckedDivide(expression, powLogOp());
                    break;
                default:
                    return expression;
            }
        }
    }

    private CommonExpression powLogOp() throws ParserException {
        CommonExpression expression = baseOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case LOG:
                    expression = new CheckedLog(expression, baseOp());
                    break;
                case POW:
                    expression = new CheckedPow(expression, baseOp());
                    break;
                default:
                    return expression;
            }
        }
    }

    private CommonExpression baseOp() throws ParserException {
        tokenizer.getToken();
        CommonExpression expression;
        switch (tokenizer.getCurrentToken()) {
            case CONST:
                Const value = new Const(tokenizer.getValue());
                tokenizer.getToken();
                return value;
            case VAR:
                Variable variable = new Variable(tokenizer.getVarName());
                tokenizer.getToken();
                return variable;
            case LOG10:
                expression = new CheckedLog10(baseOp());
                return expression;
            case POW10:
                expression = new CheckedPow10(baseOp());
                return expression;
            case MINUS:
                expression = new CheckedNegate(baseOp());
                return expression;
            case LP:
                expression = addSubOp();
                if (tokenizer.getCurrentToken() != TokenType.RP) {
                    throw new MissingClosingParenthesisException(tokenizer.getIterator(),
                            tokenizer.getRestExpression());
                }
                tokenizer.getToken();
                return expression;
            default:
                throw new UnknownSymbolException(tokenizer.getIterator(), tokenizer.getRestExpression());
        }
    }
}
