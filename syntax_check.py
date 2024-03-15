import asyncio
import os


async def check_c_file_syntax_async(file_path):
    process = await asyncio.create_subprocess_exec(
        "gcc", "-fsyntax-only", file_path,
        stdout=asyncio.subprocess.PIPE,
        stderr=asyncio.subprocess.PIPE
    )

    stdout, stderr = await process.communicate()

    # Return True if no syntax errors, False otherwise
    return process.returncode == 0


async def main():
    folder_path = "/root/autodl-tmp/LLM-for-HLS/test_output"  # './outputs'
    pass_num = len([1 for file in os.listdir(folder_path) if os.path.isdir(os.path.join(folder_path, file))])
    print(f"Pass num: {pass_num}")
    c_file_dirs = [file_dir for file_dir in os.listdir(folder_path) if os.path.isdir(os.path.join(folder_path, file_dir)) and
                   file_dir.startswith("test")]
    print(f"C file dirs: {c_file_dirs}")
    
    results = []
    for file_dir in c_file_dirs:
        dir_results = await asyncio.gather(*[check_c_file_syntax_async(os.path.join(folder_path, file_dir, file))
                                             for file in os.listdir(os.path.join(folder_path, file_dir))])
        print(f"Dir results: {dir_results}")
        results.append(1 if any(dir_results) else 0)

    # Calculate the number of files with syntax errors
    print(f"Total test instances: {len(results)}")
    print(f"Total pass instances: {sum(results)}")
    print(f"Total fail instances: {len(results) - sum(results)}")
    print(f"Pass rate: {sum(results) / len(results) * 100}%")

# Run the asynchronous main function
asyncio.run(main())
