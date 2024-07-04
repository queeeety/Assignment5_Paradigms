import subprocess


def run_program(input_data):
    process = subprocess.Popen(
        ['./main'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()


def test_program():
    tests = [
        {"input": "max(min(2+3,5+6), 7*(8-2)) + 5\n",
         "expected_output": "Echo: Hello, world!"},
        {"input": "12345\n", "expected_output": "Echo: 12345"}
    ]

    for test in tests:
        output, _ = run_program(test["input"])
        if output == test["expected_output"]:
            print(f"Test with input {test['input'].strip()} passed.")
        else:
            print(f"Test with input {test['input'].strip()} failed. Expected '{test['expected_output']}', got '{output}'")

# Run the tests
test_program()