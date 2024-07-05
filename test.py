import subprocess

def run_program(input_data):
    print("Running program with input:")
    result = subprocess.run(
        ['./main', input_data],  # Path to your executable
        capture_output=True,  # Захоплюємо stdout та stderr
        text=True,            # Повертаємо рядкові дані, а не байти
    )
    # Communicate input_data to the subprocess and close stdin
    output = result.stdout
    error = result.stderr
    print("Output:", output)
    print("Error:", error)



if __name__ == "__main__":

    tests = [
        {"input": "max(min(2+3,5+6), 7*(8-2)) + 5", "expected_output": "32"},
        # {"input": "12345\n", "expected_output": "12345"},
        # {"input": "10 * 5 - 3\n", "expected_output": "47"},
        # {"input": "pow(2,  8) / 4\n", "expected_output": "64"},
        # {"input": "(100 - 50) * 3\n", "expected_output": "150"},
        # {"input": "pow(12,2) + 12 \n", "expected_output": "156"},
        # {"input": "99 / 3 * 4\n", "expected_output": "132"},
        # {"input": "max(10, 20.2) + min(5, 3.3)\n", "expected_output": "23.5"},
        # {"input": "min(max(2, 3), max(5, 6))\n", "expected_output": "5"},
        # {"input": "max(1+2, 3+4) - min(2*2, 3*3)\n", "expected_output": "4"},
        # {"input": "min(100, max(50, 25))\n", "expected_output": "50"},
        # {"input": "max(abs(-16), 10)\n", "expected_output": "16"},
        # {"input": "var x = 10\n var   y = 20\nmax(x  , y)\n", "expected_output": "20"},
        # {"input": "var a = 5\n var b = 15\nmax(a+5, b-5)\n", "expected_output": "15"},
        # {"input": "var va1 = 100\nvar var va2 = 200\nmin(va1, va2)\n", "expected_output": "100"},
        # {"input": "var num1 = 9\nvar num2 = 3\nmax(num1 % num2, 5)\n", "expected_output": "5"},
        # {"input": "var first = 12\nvar  second = 24\nmax(first * 2, second / 2)\n", "expected_output": "24"},
        # {"input": "def add(a, b) { a + b} \n add(5, 7)\n", "expected_output": "12"},
        # {"input": "def subtract(a, b) {a - b}\nsubtract(10, 3)\n", "expected_output": "7"},
        # {"input": "def multiply(a, b, c) { a * b * c  }\nmultiply(6, 7, 10)\n", "expected_output": "420"},
        # {"input": "def max_of_three(a, b, c){ max(a, max(b, c))}\nmax_of_three(1, 5, 3)\n", "expected_output": "5"},
        # {"input": "def min_of_two(a, b){ min(a, b)} \nmin_of_two(10, 20)\n", "expected_output": "10"},
        # {"input": "def calc_diff_max_min(a, b, c) { max(a, b, c) - min(a, b, c)}\ncalc_diff_max_min(10, 20, 15)\n", "expected_output": "10"},
        # {"input": "def add(a, b) { a + b}\nvar x = 10\nvar y = 20\nadd(x, y)\n", "expected_output": "30"},
        # {"input": "def subtract(a, b) {a - b}\nvar x = 10\nvar y = 20\nsubtract(x, y)\n", "expected_output": "-10"},
    ]

    for test in tests:
        output, error = run_program(test["input"])
        if error:
            print(f"Error for input {test['input'].strip()}: {error}")
        elif output == test["expected_output"]:
            print(f"Test with input {test['input'].strip()} passed.")
        else:
            print(f"Test with input {test['input'].strip()} failed. Expected '{test['expected_output']}', got '{output}'")



