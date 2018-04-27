package parser;

import Types.Type;
import com.sun.istack.internal.NotNull;
import exceptions.*;
import expression.*;

public class ExpressionParser<T> implements Parser<T> {
    private Tokenizer<T> tokenizer;
    private Type<T> type;
    private boolean containsVariables;

    public ExpressionParser(Type<T> type) {
        this.type = type;
        containsVariables = false;
    }

    @Override
    public TripleExpression<T> parse(@NotNull String expression) throws ParserException {
        tokenizer = new Tokenizer<>(expression, type);
        return minMaxOp();
    }

    public boolean containsVariables() {
        return containsVariables;
    }

    private TripleExpression<T> minMaxOp() throws ParserException {
        TripleExpression<T> expression = addSubOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case MIN:
                    expression = new Min<>(expression, addSubOp(), type);
                    break;
                case MAX:
                    expression = new Max<>(expression, addSubOp(), type);
                    break;
                default:
                    return expression;
            }
        }
    }

    private TripleExpression<T> addSubOp() throws ParserException {
        TripleExpression<T> expression = mulDivOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case ADD:
                    expression = new Add<>(expression, mulDivOp(), type);
                    break;
                case SUB:
                    expression = new Subtract<>(expression, mulDivOp(), type);
                    break;
                default:
                    return expression;
            }
        }
    }

    private TripleExpression<T> mulDivOp() throws ParserException {
        TripleExpression<T> expression = baseOp();
        while (true) {
            switch (tokenizer.getCurrentToken()) {
                case MUL:
                    expression = new Multiply<>(expression, baseOp(), type);
                    break;
                case DIV:
                    expression = new Divide<>(expression, baseOp(), type);
                    break;
                default:
                    return expression;
            }
        }
    }

    private TripleExpression<T> baseOp() throws ParserException {
        tokenizer.getToken();
        TripleExpression<T> expression;
        switch (tokenizer.getCurrentToken()) {
            case CONST:
                expression = new Const<>(tokenizer.getValue());
                tokenizer.getToken();
                return expression;
            case VAR:
                containsVariables = true;
                expression = new Variable<>(tokenizer.getVarName());
                tokenizer.getToken();
                return expression;
            case MINUS:
                expression = new Negate<>(baseOp(), type);
                return expression;
            case COUNT:
                expression = new Count<>(baseOp(), type);
                return expression;
            case LP:
                expression = minMaxOp();
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
