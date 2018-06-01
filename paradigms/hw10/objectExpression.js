"use strict";

function Const(value) {
    this.value = value;
}

Const.prototype.evaluate = function () {
    return this.value;
};

Const.prototype.toString = function () {
    return this.value.toString();
};

Const.prototype.diff = function () {
    return CONSTANTS[0];
};

Const.prototype.simplify = function () {
    return this;
};

function Variable(name) {
    this.name = name;
}

Variable.prototype.evaluate = function () {
    return arguments[VARIABLES[this.name]];
};

Variable.prototype.toString = function () {
    return this.name;
};

Variable.prototype.diff = function (x) {
    return x === this.name ? CONSTANTS[1] : CONSTANTS[0];
};

Variable.prototype.simplify = function () {
    return this;
};

function Operation() {
    this.operands = [].slice.call(arguments);
}

Operation.prototype.evaluate = function () {
    var args = arguments;
    return this.func.apply(this, this.operands.map(function (x) {
        return x.evaluate.apply(x, args);
    }));
};

Operation.prototype.toString = function () {
    return this.operands.join(' ') + ' ' + this.operator;
};

Operation.prototype.diff = function (v) {
    return this._diff.apply(this, this.operands.concat(
        this.operands.map(function (x) {
            return x.diff(v);

    })));
};

Operation.prototype.simplify = function () {
    var copy = Object.create(this);
    copy.operands = this.operands.map(function (val) {
        return val.simplify();
    });
    if (copy.operands.every(function (item) {
        return item instanceof Const;
    }))
        return new Const(copy.evaluate());
    if (copy._simplify !== undefined) {
        return copy._simplify.apply(copy.constructor, copy.operands);
    }
    return copy;
};

function OperationFactory(operands, func, operator, diff, simplify) {
    this.func = func;
    this.operator = operator;
    this._diff = diff;
    this._simplify = simplify;
    Operation.apply(this, operands);
}

function Add() {
    OperationFactory.apply(this, [arguments, function (a, b) {
        return a + b;
    }, '+', function (a, b, da, db) {
        return new Add(da, db);
    }, function (a, b) {
        if (isEqual(a, 0))
            return b;
        if (isEqual(b, 0))
            return a;
        return new Add(a, b);
    }]);
}

function Subtract() {
    OperationFactory.apply(this, [arguments, function (a, b) {
        return a - b;
    }, '-', function (a, b, da, db) {
        return new Subtract(da, db);
    }, function (a, b) {
        if (isEqual(b, 0))
            return a;
        if (isEqual(a, 0) && b instanceof Const)
            return new Const(-b.value);
        return new Subtract(a, b);
    }]);
}

function Multiply() {
    OperationFactory.apply(this, [arguments, function (a, b) {
        return a * b;
    }, '*', function (a, b, da, db) {
        return new Add(new Multiply(da, b), new Multiply(a, db));
    }, function (a, b) {
        if (isEqual(a, 0) || isEqual(b, 0))
            return CONSTANTS[0];
        if (isEqual(b, 1))
            return a;
        if (isEqual(a, 1))
            return b;
        return new Multiply(a, b);
    }]);
}

function Divide() {
    OperationFactory.apply(this, [arguments, function (a, b) {
        return a / b;
    }, '/', function (a, b, da, db) {
        return new Divide(
            new Subtract(
                new Multiply(da, b),
                new Multiply(a, db)),
            new Multiply(b, b));
    }, function (a, b) {
        if (isEqual(a, 0))
            return CONSTANTS[0];
        if (isEqual(b, 1))
            return a;
        return new Divide(a, b);
    }]);
}

function Negate() {
    OperationFactory.apply(this, [arguments, function (a) {
        return -a;
    }, 'negate', function (a, da) {
        return new Negate(da);
    }, function (a) {
        if (isEqual(a, 0))
            return CONSTANTS[0];
        if (a instanceof Const)
            return new Const(-a.value);
        return new Negate(a);
    }]);
}

function Abs() {
    OperationFactory.apply(this, [arguments, function (a) {
        return Math.abs(a);
    }, 'abs', function (a, da) {
        return new Divide(new Multiply(a, da), new Abs(a));
    }, function (a) {
        if (isEqual(a, 0))
            return CONSTANTS[0];
        if (a instanceof Const) {
            if (a > 0)
                return new Const(a.value);
            return new Const(-a.value);
        }
        return new Abs(a);
    }]);
}

function Square() {
    OperationFactory.apply(this, [arguments, function (a) {
        return a * a;
    }, 'square', function (a, da) {
        return new Multiply(new Multiply(new Const(2), a), da);
    }
    /*, function (a) {
        if (isEqual(a, 0))
            return CONSTANTS[0];
        if (isEqual(a, 1))
            return CONSTANTS[1];
        return new Square(a);
    }*/]);
}

function Sqrt() {
    OperationFactory.apply(this, [arguments, function (a) {
        return Math.sqrt(Math.abs(a));
    }, 'sqrt', function (a, da) {
        return new Divide(
            new Multiply(da, a),
            new Multiply(
                CONSTANTS[2],
                new Abs(
                    new Multiply(
                        new Sqrt(a),
                        a))));
    }, function (a) {
        if (isEqual(a, 0))
            return CONSTANTS[0];
        if (isEqual(a, 1))
            return CONSTANTS[1];
        return new Sqrt(a);
    }]);
}

var OPERATORS = {
    '+': [Add, 2],
    '-': [Subtract, 2],
    '*': [Multiply, 2],
    '/': [Divide, 2],
    'negate': [Negate, 1],
    'abs': [Abs, 1],
    'square': [Square, 1],
    'sqrt': [Sqrt, 1]
};

for (var op in OPERATORS) {
    OPERATORS[op][0].prototype = Object.create(Operation.prototype);
}

var CONSTANTS = [new Const(0), new Const(1), new Const(2)];

var VARIABLES = {
    'x': 0,
    'y': 1,
    'z': 2
};

function isEqual(x, val) {
    return (x instanceof Const) && (x.evaluate() === val);
}

var parse = function (expr) {
    var stack = [];
    var newLikeApply = function(obj, args) {
        var tmp = Object.create(obj.prototype);
        obj.apply(tmp, args);
        return tmp;
    };

    var tokens = expr.split(' ').filter(function (t) {
        return t.length > 0;
    });

    for (var i = 0; i < tokens.length; i++) {
        if (tokens[i] in VARIABLES) {
            stack.push(new Variable(tokens[i]));
        }
        else if (tokens[i] in CONSTANTS) {
            stack.push(CONSTANTS[tokens[i]]);
        }
        else if (!isNaN(tokens[i])) {
            stack.push(new Const(Number(tokens[i])));
        }
        else if (tokens[i] in OPERATORS) {
            var f = OPERATORS[tokens[i]][0];
            var numberOfArgs = OPERATORS[tokens[i]][1];
            var args = [];
            for (var j = 0; j < numberOfArgs; j++) {
                args.push(stack.pop());
            }
            stack.push(newLikeApply(f, args.reverse()));
        }
    }
    return stack.pop();
};

var expr = parse('x y - square').diff('x').simplify();
console.log(expr.toString());