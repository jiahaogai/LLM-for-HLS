import os
import subprocess
import tempfile
import json
import re

def find_c_function_names(c_code):
    # 正则表达式匹配C语言函数定义
    pattern = r'\bvoid\s+([A-Za-z_][A-Za-z0-9_]*)\b\s*\('
    return re.findall(pattern, c_code)[0]
def compile_and_run(test_case_file_path, output_file_path):
    with tempfile.TemporaryDirectory() as temp_dir:
        # tmp_file_path = os.path.join(temp_dir, "test_fdtd")
        result = subprocess.run(["gcc", f"-o test_fdtd", test_case_file_path, output_file_path],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = result.stdout, result.stderr
        # print(f"stdout: {stdout.decode()}")
        if stderr:
            print(f"stderr: {stderr.decode()}")
        return result.returncode == 0, stdout.decode("utf-8")


def run_tests(output_dir):
    output_files = [os.path.join(output_dir, f) for f in os.listdir(output_dir) if not f.endswith(".jsonl")]
    # output_files.sort(key=lambda x: int(x.split("_")[-1].split(".")[0]))
    output_files.sort()
    # print(len(output_files))
    truth_files_path = "data/sources"
    # truth_files = [os.path.join(truth_files_path, f) for f in os.listdir(truth_files_path) if f.endswith(".c")]
    # truth_files.sort()
    # truth_files = []
    # with open("./data/processed_sources_test_c.jsonl", "r", encoding="utf-8") as f:
    #     for line in f:
    #         truth_files.append(json.loads(line))
    # truth_files = truth_files[:200]
    # print(len(truth_files))
    # assert len(truth_files) == len(output_files)
    # test_case_files_path = "./functionality_data"
    # test_case_files = [os.path.join(test_case_files_path, f) for f in os.listdir(test_case_files_path)  if f.endswith(".c")]
    # test_case_files.sort()
    total_cases = 0
    total_passed = 0
    n = -1
    # print(output_
    # files)
    for idx, test_dir_path in enumerate(output_files):
        # print(test_dir)
        # test_dir_path = os.path.join(output_dir, test_dir)
        total_cases += 1
        if not os.path.isdir(test_dir_path):
            continue
        n = len(os.listdir(test_dir_path))
        # func_name = find_c_function_names(truth_files[idx]["output"])
        # 首先， 加载正确的c文件的内容
        truth_file = "data/sources/" + test_dir_path.split("/")[-1].split('.c')[0] + ".c"
        # 然后加载测试文件
        test_case_file = "./functionality_data/" + test_dir_path.split("/")[-1].split('.c')[0] + "_test.c"
        assert os.path.exists(test_case_file), f"Test case file {test_case_file} does not exist"
        # print(test_case_file)

        # print(test_dir_path)
        # 先得到正确文件的输出
        flag, test_output = compile_and_run(test_case_file, truth_file)
        # print(test_output)
        assert flag, f"Compilation failed for {test_case_file} and {truth_file}, with {test_output}"

        # exit()
        for test_file in os.listdir(test_dir_path):
            test_file_path = os.path.join(test_dir_path, test_file)
            flag, output = compile_and_run(test_case_file, test_file_path)
            # print(output)
            # print("++++++++++++++++++++++")
            # assert flag, f"Compilation failed for {test_file_path}"
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
        # break
    print(total_passed)
    pass_at_5 = (total_passed / total_cases) * 100
    print(f"\nTotal pass@{n}: {pass_at_5:.3f}% ({total_passed} out of {total_cases} cases passed)")


if __name__ == "__main__":
    run_tests("./test_output_woCot_woFd")
