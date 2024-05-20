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
    folder_path = "../../outputs/test_output"  # './outputs'
    # folder_path = "/root/autodl-tmp/LLM/LLM-for-HLS/test_output_with_feedback_loop"  # './outputs'
    pass_num = len(os.listdir(os.path.join(folder_path, os.listdir(folder_path)[0])))
    print(f"Pass num: {pass_num}")
    c_file_dirs = [file_dir for file_dir in os.listdir(folder_path) if os.path.isdir(os.path.join(folder_path, file_dir)) and
                   ".c" in file_dir]
    print(f"C file dirs: {c_file_dirs}")
    # tasks = [any([check_c_file_syntax_async(os.path.join(folder_path, file)) for file in file_dir]) for file_dir in
    #          c_file_dirs]
    # tasks = [check_c_file_syntax_async(os.path.join(folder_path, file))
    #          for file_dir in c_file_dirs
    #          for file in os.listdir(os.path.join(folder_path, file_dir))]
    # results = await asyncio.gather(*tasks)
    results = []
    for file_dir in c_file_dirs:
        dir_results = await asyncio.gather(*[check_c_file_syntax_async(os.path.join(folder_path, file_dir, file))
                                             for file in os.listdir(os.path.join(folder_path, file_dir))])
        print(f"Dir results: {dir_results}")
        results.append(1 if any(dir_results) else 0)

    # for file, result in results:
    #     print(f"File: {file}\n{result}\n")
    # Count the number of files with syntax errors
    print(f"Total test instances: {len(results)}")
    print(f"Total pass instances: {sum(results)}")
    print(f"Total fail instances: {len(results) - sum(results)}")
    print(f"Pass rate: {sum(results) / len(results) * 100}%")

# Run the asynchronous main function
asyncio.run(main())
