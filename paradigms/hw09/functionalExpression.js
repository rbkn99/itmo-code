var operation = function (op) {
    return function () {
        var ops = arguments;
        return function () {
            var result = [];
            for (var i = 0; i < ops.length; i++) {
                result.push(ops[i].apply(null, arguments));
            }
            return op.apply(null, result);
        }
    }
};

var cnst = function (x) {
    return function () {
        return x;
    }
};

var add = operation(function (a, b) {
    return a + b;
});

var subtract = operation(function (a, b) {
    return a - b;
});

var multiply = operation(function (a, b) {
    return a * b;
});

var divide = operation(function (a, b) {
    return a / b;
});

var negate = operation(function (a) {
    return -a;
});

var cube = operation(function (a) {
    return Math.pow(a, 3);
});

var cuberoot = operation(function (a) {
    return Math.pow(a, 1 / 3.);
});

var min3 = operation(function (a, b, c) {
    return Math.min(a, b, c);
});

var max5 = operation(function (a, b, c, d, e) {
    return Math.max(a, b, c, d, e);
});

var VARIABLES = ['x', 'y', 'z'];

var OPERATORS = {
    '+': [add, 2],
    '-': [subtract, 2],
    '*': [multiply, 2],
    '/': [divide, 2],
    'negate': [negate, 1],
    'cube': [cube, 1],
    'cuberoot': [cuberoot, 1],
    'min3': [min3, 3],
    'max5': [max5, 5]
};

var pi = cnst(Math.PI);
var e = cnst(Math.E);

var CONSTS = {'pi': pi, 'e': e};

var variable = function (x) {
    return function () {
        return arguments[VARIABLES.indexOf(x)];
    }
};

var x = variable('x'), y = variable('y'), z = variable('z');

var parse = function (expr) {
    var stack = [];

    var tokens = expr.split(' ').filter(function (t) {
        return t.length > 0;
    });

    for (var i = 0; i < tokens.length; i++) {
        if (VARIABLES.indexOf(tokens[i]) !== -1) {
            stack.push(variable(tokens[i]));
        }
        else if (tokens[i] in CONSTS) {
            stack.push(CONSTS[tokens[i]]);
        }
        else if (VARIABLES.indexOf('-' + tokens[i]) !== -1) {
            stack.push(negate(variable(tokens[i])));
        }
        else if (!isNaN(tokens[i])) {
            stack.push(cnst(Number(tokens[i])));
        }
        else if (tokens[i] in OPERATORS) {
            var f = OPERATORS[tokens[i]][0];
            var numberOfArgs = OPERATORS[tokens[i]][1];
            var args = [];
            for (var j = 0; j < numberOfArgs; j++) {
                args.push(stack.pop());
            }
            stack.push(f.apply(null, args.reverse()));
        }
    }
    return stack.pop();
};

//var print = console.log;
//print(parse('x 2 +')(0, 0, 0));
//add(pi, variable('x'))(0,0,0);
//multiply(x, y);
//print(parse('x y z pi e max5')(0,0,0));