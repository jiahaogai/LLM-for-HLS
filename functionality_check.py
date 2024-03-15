import os
import subprocess
import importlib

def compile_and_run(c_file_path, test_dir):
    # Compile the C file
    compile_cmd = f"gcc -o {test_dir}/test {c_file_path}"
    subprocess.run(compile_cmd, shell=True, check=True)

    # Run the compiled program
    run_cmd = f"{test_dir}/test"
    result = subprocess.run(run_cmd, shell=True, check=True, capture_output=True, text=True)
    
    passed_cases = 0
    for line in result.stdout.split("\n"):
        if "Pass" in line:
            passed_cases += 1
    
    return passed_cases

def run_tests(test_cases_dir):
    total_cases = 0
    total_passed = 0

    for test_dir in os.listdir(test_cases_dir):
        test_dir_path = os.path.join(test_cases_dir, test_dir)
        if not os.path.isdir(test_dir_path):
            continue

        # Find the C file
        c_file = None
        for file in os.listdir(test_dir_path):
            if file.endswith(".c"):
                c_file = file
                break
        if c_file is None:
            print(f"No .c file found in {test_dir_path}, skipping...")
            continue
        
        c_file_path = os.path.join(test_dir_path, c_file)

        # Add input_data.py and expected_output.py to the module search path
        import sys
        sys.path.insert(0, test_dir_path)
        
        # Dynamically import input_data and expected_output modules
        input_data = importlib.import_module("input_data") 
        expected_output = importlib.import_module("expected_output")

        # Inject input data and expected output into the C file
        with open(c_file_path, "r") as f:
            c_code = f.read()
        c_code = f"#include <stdbool.h>\n{c_code}"  # Add stdbool.h header
        c_code = c_code.replace("//INPUT_DATA_PLACEHOLDER", f"const int NUM_TESTS = {len(input_data.data)};\n" + input_data.to_c_code())
        c_code = c_code.replace("//EXPECTED_OUTPUT_PLACEHOLDER", expected_output.to_c_code())

        injected_c_file = os.path.join(test_dir_path, "injected_" + c_file)
        with open(injected_c_file, "w") as f:
            f.write(c_code)

        # Compile and run the test
        passed_cases = compile_and_run(injected_c_file, test_dir_path)
        print(f"{test_dir}: passed {passed_cases} out of {len(input_data.data)} cases.")

        total_cases += len(input_data.data)
        total_passed += passed_cases

    pass_at_5 = total_passed / total_cases
    print(f"\nTotal pass@5: {pass_at_5:.3f} ({total_passed} out of {total_cases} cases passed)")

if __name__ == "__main__":
    run_tests("test_cases")
