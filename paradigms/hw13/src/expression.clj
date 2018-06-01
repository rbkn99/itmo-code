(defn constant [value] (fn [x] value))
(defn variable [name] (fn [vars] (get vars name)))

(defn operator [func]
  (fn [& operands]
    (fn [args] (apply func (map (fn [f] (f args)) operands)))
    )
  )

(def sinh (operator (fn [x] (Math/sinh x))))
(def cosh (operator (fn [x](Math/cosh x))))

(def negate (operator -))
(def add (operator +))
(def subtract (operator -))
(def multiply (operator *))
(def divide (operator (fn [a b] (/ (double a) (double b)))))

(defn parseFunction [strExpr]
  ((fn parse [expr]
     (cond
       (symbol? expr) (variable (str expr))
       (number? expr) (constant expr)
       (seq? expr) (apply ({'negate negate,
                      '+ add,
                      '- subtract,
                      '* multiply,
                      '/ divide,
                      'sinh sinh,
                      'cosh cosh } (first expr)) (map parse (rest expr))))
     ) (read-string strExpr)))

;(parseFunction "(/ 6 2 3)")
