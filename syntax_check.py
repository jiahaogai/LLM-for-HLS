import asyncio
import os


async def check_c_file_syntax_async(file_path):
    process = await asyncio.create_subprocess_exec(
        "gcc", "-fsyntax-only", file_path,
        stdout=asyncio.subprocess.PIPE,
        stderr=asyncio.subprocess.PIPE
    )

    stdout, stderr = await process.communicate()

    # if process.returncode != 0:
    #     return file_path, stderr.decode()
    # else:
    #     return file_path, "No syntax errors found."
    return process.returncode == 0  # True if no syntax errors


async def main():
    folder_path = "/root/autodl-tmp/LLM-for-HLS/test_output"  # './outputs'
    pass_num = len(os.listdir(folder_path + "test_output_0"))
    print(f"Pass num: {pass_num}")
    c_file_dirs = [file_dir for file_dir in os.listdir(folder_path)]

    tasks = [any([check_c_file_syntax_async(os.path.join(folder_path, file)) for file in file_dir] )for file_dir in c_file_dirs]
    results = await asyncio.gather(*tasks)

    # for file, result in results:
    #     print(f"File: {file}\n{result}\n")
    # 计算语法错误的文件数
    print(f"Number of files with no syntax errors: {sum(results)}")
    print(f"Number of files with syntax errors: {len(results) - sum(results)}")
    Accuracy = sum(results) / len(results)
    print(f"Accuracy: {Accuracy:.4f}")


# 运行异步主函数
asyncio.run(main())
