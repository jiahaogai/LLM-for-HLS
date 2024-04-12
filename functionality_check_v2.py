import os
import subprocess
import tempfile
import json
import re

def find_c_function_names(c_code):
    # Regular expression to match C language function definitions
    pattern = r'\bvoid\s+([A-Za-z_][A-Za-z0-9_]*)\b\s*\('
    return re.findall(pattern, c_code)[0]

def compile_and_run(test_case_file_path, output_file_path):
    with tempfile.TemporaryDirectory() as temp_dir:
        tmp_file_path = os.path.join(temp_dir, "test_fdtd")
        result = subprocess.run(["gcc", "-o", "test_fdtd", test_case_file_path, output_file_path],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = result.stdout, result.stderr
        # Uncomment to print standard output
        # print(f"stdout: {stdout.decode()}")
        if stderr:
            print(f"stderr: {stderr.decode()}")
        return result.returncode == 0, stdout.decode("utf-8")

def run_tests(output_dir):
    output_files = [os.path.join(output_dir, f) for f in os.listdir(output_dir) if not f.endswith(".jsonl")]
    output_files.sort()
    # Uncomment to check number of output files
    # print(len(output_files))
    truth_files_path = "data/sources"
    # Initializing test files and counts
    total_cases = 0
    total_passed = 0
    n = -1
    # Uncomment to debug output files listing
    # print(output_files)
    for idx, test_dir_path in enumerate(output_files):
        # Uncomment to print test directory
        # print(test_dir)
        total_cases += 1
        if not os.path.isdir(test_dir_path):
            continue
        n = len(os.listdir(test_dir_path))
        # First, load the content of the correct C file
        truth_file = "data/sources/" + test_dir_path.split("/")[-1].split('.c')[0] + ".c"
        # Loading the temporary C file to get function names
        # func_name = subprocess.run(["gcc", "-E", "-dM", "-", "-"], input=truth_file.encode(), stdout=subprocess.PIPE).stdout.decode().split("\n")[-2].split()[-1]
        # Uncomment for debugging function names
        # print(func_name)
        test_case_file = "./functionality_data/" + test_dir_path.split("/")[-1].split('.c')[0] + "_test.c"
        assert os.path.exists(test_case_file), f"Test case file {test_case_file} does not exist"
        # Get correct file output first
        flag, test_output = compile_and_run(test_case_file, truth_file)
        assert flag, f"Compilation failed for {test_case_file} and {truth_file}, with {test_output}"
        for test_file in os.listdir(test_dir_path):
            test_file_path = os.path.join(test_dir_path, test_file)
            flag, output = compile_and_run(test_case_file, test_file_path)
            if flag:
                if output == test_output:
                    total_passed += 1
                    print(f"{test_file_path} passed")
                else:
                    print(f"{test_file_path} failed with different output")
            else:
                print(f"{test_file_path} failed to compile")
        print("+++++++++++++++++++++++++++++++++++++++++++")
    print(total_passed)
    pass_at_5 = (total_passed / total_cases) * 100
    print(f"\nTotal pass@{n}: {pass_at_5:.3f}% ({total_passed} out of {total_cases} cases passed)")

if __name__ == "__main__":
    run_tests("./test_output")
