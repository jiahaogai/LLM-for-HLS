import os
import subprocess
import tempfile
import json
import re

def find_c_function_names(c_code):
    pattern = r'\bvoid\s+([A-Za-z_][A-Za-z0-9_]*)\b\s*\('
    return re.findall(pattern, c_code)[0]
def compile_and_run(test_case_file_path, output_file_path):
    with tempfile.TemporaryDirectory() as temp_dir:
        result = subprocess.run(["gcc", f"-o test_fdtd", test_case_file_path, output_file_path],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = result.stdout, result.stderr
        if stderr:
            print(f"stderr: {stderr.decode()}")
        return result.returncode == 0, stdout.decode("utf-8")


def run_tests(output_dir):
    output_files = [os.path.join(output_dir, f) for f in os.listdir(output_dir) if not f.endswith(".jsonl")]
    output_files.sort()
    truth_files_path = "../../data/sources"
    total_cases = 0
    total_passed = 0
    n = -1
    for idx, test_dir_path in enumerate(output_files):
        total_cases += 1
        if not os.path.isdir(test_dir_path):
            continue
        n = len(os.listdir(test_dir_path))
        # First, load the correct contents of the C file.
        truth_file = "../../data/sources/" + test_dir_path.split("/")[-1].split('.c')[0] + ".c"
        # Then load the test file.
        test_case_file = "../../functionality_data/" + test_dir_path.split("/")[-1].split('.c')[0] + "_test.c"
        assert os.path.exists(test_case_file), f"Test case file {test_case_file} does not exist"
        # First, obtain the correct file output.
        flag, test_output = compile_and_run(test_case_file, truth_file)
        assert flag, f"Compilation failed for {test_case_file} and {truth_file}, with {test_output}"
        for test_file in os.listdir(test_dir_path):
            test_file_path = os.path.join(test_dir_path, test_file)
            flag, output = compile_and_run(test_case_file, test_file_path)
            if flag:
                if output == test_output:
                    total_passed += 1
                    print(f"{test_file_path} passed")
                    break # break after first pass
                else:
                    print(f"{test_file_path} failed with different output")
            else:
                print(f"{test_file_path} failed to compile")

        print("+++++++++++++++++++++++++++++++++++++++++++")
    print(total_passed)
    pass_at_5 = (total_passed / total_cases) * 100
    print(f"\nTotal pass@{n}: {pass_at_5:.3f}% ({total_passed} out of {total_cases} cases passed)")


if __name__ == "__main__":
    run_tests("../../outputs/test_output_woCot_funFd")
