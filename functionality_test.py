import ctypes
import json
import logging
import os
import subprocess
import sys
from functools import wraps
from typing import Any
from ctypes import *

def load_data(data_dir):
    return os.listdir(data_dir)


def generate_shared_lib(c_code_dir, c_code_name, lib_name="libfunctionality.so"):
    # 参数校验
    if not c_code_dir or not c_code_name:
        raise ValueError("c_code_dir and c_code_name cannot be empty.")

    c_code_path = os.path.join(c_code_dir, c_code_name)
    if not os.path.isfile(c_code_path):
        raise FileNotFoundError(f"File {c_code_path} not found.")

    lib_output_path = os.path.join(c_code_dir, lib_name)

    try:
        subprocess.run(["gcc", "--version"], check=True, stdout=subprocess.DEVNULL)
    except subprocess.CalledProcessError:
        print("GCC compiler is not available on this system.", file=sys.stderr)
        return

    # 执行编译命令，并处理异常
    try:
        compile_command = ["gcc", "-fPIC", "-shared", "-o", lib_output_path, c_code_path]
        subprocess.run(compile_command, check=True)
        print(f"Shared library {lib_output_path} generated successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error occurred while generating shared library: {e}", file=sys.stderr)


def load_shared_lib(lib_path):
    try:
        return ctypes.CDLL(lib_path)
    except OSError:
        print(f"Unable to load the shared library from {lib_path}", file=sys.stderr)
        return None


# 设置日志记录配置
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')


def safe_getattr(obj: Any, name: str, default=None):
    """安全获取对象属性的装饰器，用于捕获属性不存在的异常。"""

    @wraps(getattr)
    def wrapper(*args, **kwargs):
        try:
            return getattr(*args, **kwargs)
        except AttributeError:
            logging.error(f"Attribute {name} not found in {obj}.")
            return default

    return wrapper


# 假设lib是一个已经安全加载的外部库

def convert_to_ctypes(arg_type, arg_value):
    """
    转换Python数据类型到ctypes类型。
    """
    if arg_type == 'int':
        return ctypes.c_int(arg_value)
    elif arg_type == 'double':
        return ctypes.c_double(arg_value)
    elif arg_type == 'char*':
        return ctypes.c_char_p(arg_value.encode('utf-8'))
    elif arg_type == 'float':
        return ctypes.c_float(arg_value)
    elif arg_type == 'bool':
        return ctypes.c_bool(arg_value)
    elif arg_type == 'double[][]':
        # return convert_to_double_array(arg_value)
        return create_matrix(arg_value)
    elif arg_type == 'int[]':
        return (ctypes.c_int * len(arg_value))(*arg_value)
    elif arg_type == 'double[]':
        return (ctypes.c_double * len(arg_value))(*arg_value)
    elif arg_type == 'char*[]':
        return (ctypes.POINTER(ctypes.c_char_p) * len(arg_value))(
            *[ctypes.create_string_buffer(val.encode('utf-8')) for val in arg_value])
    elif arg_type == 'void':
        return None
    else:
        logging.error(f"Unsupported argument type: {arg_type}")
        raise ValueError(f"Unsupported argument type: {arg_type}")


def convert_to_double_array(arg_value):
    """
    特殊处理二维数组。
    """
    row_count = len(arg_value)
    col_count = len(arg_value[0]) if row_count > 0 else 0

    RowType = ctypes.c_double * col_count
    ArrayType = ctypes.POINTER(RowType) * row_count

    c_arg = ArrayType()

    for i, row in enumerate(arg_value):
        if len(row) != col_count:
            raise ValueError("All rows must have the same number of elements")
        row_instance = RowType(*row)
        c_arg[i] = ctypes.pointer(row_instance)

    return c_arg

class Matrix(Structure):
    _fields_ = [("size", c_int), ("values", POINTER(POINTER(c_double)))]

def create_matrix(data):
    matrix = (POINTER(c_double) * len(data))()
    for i, row in enumerate(data):
        matrix[i] = (c_double * len(row))(*row)
    return Matrix(size=len(data), values=matrix)

def test_functionality(functionality_data_dir, functionality_data_name, lib):
    if not functionality_data_dir or not functionality_data_name:
        logging.error("Data directory or data name is empty.")
        return False

    functionality_data_path = os.path.join(functionality_data_dir, functionality_data_name)
    if not os.path.isfile(functionality_data_path):
        raise FileNotFoundError(f"File {functionality_data_path} not found.")

    try:
        with open(functionality_data_path, "r") as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        logging.error(f"Error decoding JSON from {functionality_data_path}: {e}")
        return False

    if not isinstance(data, dict):
        logging.error(f"Data loaded from {functionality_data_path} is not a dictionary.")
        return False

    for func_name, args in data.items():
        func_ptr = getattr(lib, func_name, None)
        if func_ptr is None:
            logging.error(f"Function pointer for {func_name} is None.")
            continue

        c_args = [convert_to_ctypes(arg_info['type'], arg_info['value']) for arg_name, arg_info in args.items()]
        arg_types = [type(c_arg) for c_arg in c_args]

        func_ptr.argtypes = arg_types
        func_ptr.restype = None
        try:
            func_ptr(*c_args)
            logging.info(f"Function {func_name} executed successfully.")
        except Exception as e:
            logging.error(f"Error calling function {func_name}: {e}")

    return True


def main():
    functionality_data_dir = "functionality_data"
    c_code_dir = "data/sources"
    # functionality_data = [file for file in os.listdir(functionality_data_dir) if file.endswith(".json")]
    c_code_data = [file for file in os.listdir(c_code_dir) if file.endswith(".c")]

    num_passed = 0
    # 生成共享库
    for c_code_name in c_code_data:
        generate_shared_lib(c_code_dir, c_code_name, c_code_name.replace(".c", ".so"))
        lib = load_shared_lib(os.path.join(c_code_dir, c_code_name.replace(".c", ".so")))
        functionality_file_name = c_code_name.replace(".c", "_test_data_and_cases.json")
        flag = test_functionality(functionality_data_dir, functionality_file_name, lib)
        if flag:
            num_passed += 1
    print(f"{num_passed}/{len(c_code_data)} tests passed.")


if __name__ == "__main__":
    main()
