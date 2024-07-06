# Expression Evaluator

The Expression Evaluator is a versatile program designed to parse and evaluate mathematical expressions. It supports a wide range of operations, including basic arithmetic, variable evaluation, and function handling. The program is capable of interpreting expressions with nested functions and variables, providing accurate results for complex calculations.

## Features

- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Function Evaluation**: Can evaluate custom functions, including `min`, `max`, `abs`, and more.
- **Variable Handling**: Allows for the definition and use of variables within expressions.
- **Complex Expressions**: Capable of evaluating expressions with nested functions and operations.
- **Error Handling**: Provides meaningful error messages for undefined variables or syntax errors.

## Technologies

- **Language**: C++
- **External Libraries**: Uses `exprtk` for expression parsing and evaluation.

## Usage

The program reads expressions from the standard input and outputs the evaluation result. It continues to read and evaluate expressions until an empty line is entered.

## Tests

- Test: `max(min(2+3,5+6), 7*(8-2)) + 5` passed.
- Test: `12345` passed.
- Test: `10 * 5 - 3` passed.
- Test: `pow(2,  8) / 4` passed.
- Test: `(100 - 50) * 3` passed.
- Test: `pow(12,2) + 12` passed.
- Test: `99 / 3 * 4` passed.
- Test: `max(10, 20.2) + min(5, 3.3)` passed.
- Test: `min(max(2, 3), max(5, 6))` passed.
- Test: `max(1+2, 3+4) - min(2*2, 3*3)` passed.
- Test: `min(100, max(50, 25))` passed.
- Test: `max(abs(-16), 10)` passed.
- Test: `var x = 10 var y = 20 max(x, y)` passed.
- Test: `var a = 5 var b = 15 max(a+5, b-5)` passed.
- Test: `var va1 = 100 var va2 = 200 min(va1, va2)` passed.
- Test: `var num1 = 9 var num2 = 3 max(num1 / num2, 5)` passed.
- Test: `var first = 12 var second = 24 max(first * 2, second / 2)` passed.
- Test: `def add(a, b) { a + b} add(5, 7)` passed.
- Test: `def subtract(a, b) {a - b} subtract(10, 3)` passed.
- Test: `def multiply(a, b, c) { a * b * c  } multiply(6, 7, 10)` passed.
- Test: `def min_of_two(a, b){ min(a, b)} min_of_two(10, 20)` passed.
- Test: `def calc_diff_max_min(a, b, c) { max(a, b, c) - min(a, b, c)} calc_diff_max_min(10, 20, 15)` passed.
- Test: `def add(a, b) { a + b} var x = 10 var y = 20 add(x, y)` passed.
- Test: `def subtract(a, b) {a - b} var x = 10 var y = 20 subtract(x, y)` passed.