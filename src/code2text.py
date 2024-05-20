import asyncio
import json
import os

import aiofiles
import openai
from tqdm.asyncio import tqdm

api_key = "sk-XudHwpJ8hdJGuxIC3193E4F1B6Ee416982261bF38d5f5b6d"
api_base = "https://chatwithai.icu/v1"

client = openai.AsyncOpenAI(api_key=api_key, base_url=api_base)

base_prompt = "## Task: Create a detailed, yet succinct, natural language instruction for generating the provided HLS (High-Level Synthesis) code snippets written in C. Your instruction should clearly include: the specific function header (the names and types of both the function and parameters), a brief description of the code's overall process, and the appropriate #pragma directives translated into natural language explanations. For instance, translate '#pragma ACCEL PIPELINE \"off\"' as 'Do not automatically pipeline this loop.' Similarly, interpret '#pragma ACCEL TILE FACTOR=1' as 'Keep this loop whole, without dividing it into smaller parts,' '#pragma ACCEL PARALLEL FACTOR=1' as 'Execute loop iterations sequentially, not concurrently,' and '#pragma ACCEL kernel' as 'Designate the following function for hardware acceleration.'"

# base_prompt = "## Task: Give one comprehensive but very concise natural language instruction used to generate the following HLS codes written in C, you must include the specific function header, the general process of codes and which specific #pragma values to use respectively in natural languages.\n " \
#  \
#               "For example, you might use 'Don't automatically pipeline this loop' to describe '#pragma ACCEL PIPELINE \"off\"' , and 'Process this loop in its original, full form without breaking it into smaller chunks' to describe '#pragma ACCEL TILE FACTOR=1', and 'Run the iterations of this loop one after the other, not in parallel' to describe '#pragma ACCEL PARALLEL FACTOR=1', and 'Treat the following function as a hardware kernel for acceleration' to describe '#pragma ACCEL kernel' etc. \n"

# base_prompt = "## Task: Give one comprehensive but very concise natural language instruction used to generate the following HLS codes written in C, you must include:1. the function names with the parameter names, 2. the general process of codes and which specific #pragma values to use respectively in natural languages.\n " \
#  \
#               "For example, you might use 'Don't automatically pipeline this loop' to describe '#pragma ACCEL PIPELINE \"off\"' , and 'Process this loop in its original, full form without breaking it into smaller chunks' to describe '#pragma ACCEL TILE FACTOR=1', and 'Run the iterations of this loop one after the other, not in parallel' to describe '#pragma ACCEL PARALLEL FACTOR=1', and 'Treat the following function as a hardware kernel for acceleration' to describe '#pragma ACCEL kernel'\n"

# base_prompt = "## Task: Give one comprehensive but very concise and not too detailed natural language instruction used to generate the following HLS codes written in C, you need describe the process of codes and which specific #pragma values to use respectively in natural languages.\n " \
#  \
#               "For example, you might use 'Don't automatically pipeline this loop' to describe '#pragma ACCEL PIPELINE \"off\"' , and 'Process this loop in its original, full form without breaking it into smaller chunks' to describe '#pragma ACCEL TILE FACTOR=1', and 'Run the iterations of this loop one after the other, not in parallel' to describe '#pragma ACCEL PARALLEL FACTOR=1', and 'Treat the following function as a hardware kernel for acceleration' to describe '#pragma ACCEL kernel'\n"


async def get_response(prompt):
    try:
        completion = await client.chat.completions.create(
            model="gpt-3.5-turbo-1106",
            # model="gpt-4-0613",
            # model="gpt-4-turbo-2024-04-09",
            messages=[
                {"role": "system", "content": "You are a helpful 'HLS code-to-text' generator"},
                {"role": "user", "content": base_prompt + prompt}
            ]
        )
        return completion.choices[0].message.content
    except Exception as e:
        print(f"Error in get_response: {e}")
        return None


async def process_file(source_path, design, semaphore, only_c=True):
    async with semaphore:
        try:
            async with aiofiles.open(source_path, "r") as f:
                prompt = await f.read()
                if only_c:
                    for k, v in design['point'].items():
                        prompt = prompt.replace(k, str(v))
            response = None
            while not response:
                response = await get_response(prompt)
            if response:
                # print("\n##" + response)
                if not only_c:
                    base_input = prompt + "------------------\n" + "Design point:\n" + "------------------\n"
                    points = "\n".join([f"{k}: {v}" for k, v in design['point'].items()])
                    return {
                        "instruction": "Generate HLS code with the following instructions:",
                        "input": response,
                        "output": base_input + points,
                        "source_file": source_path.split("\\")[-1]
                    }
                else:

                    return {
                        "instruction": "Generate HLS code with the following instructions:",
                        "input": response,
                        "output": prompt,
                        "source_file": source_path.split("\\")[-1]
                    }
        except Exception as e:
            print(f"Error in process_file: {e}")
            return None


async def main():
    sources_dir = "../data/sources"
    designs_dir = "../data/designs/v18"
    only_c = True  # Only generate C code
    semaphore = 60 # Number of processes to run concurrently
    process_num = 1 if semaphore == 1 else 3
    
    # sources_files = os.listdir(sources_dir)[:process_num]
    # designs_files = os.listdir(designs_dir)[:process_num]
    sources_files = os.listdir(sources_dir)[:-1]
    designs_files = os.listdir(designs_dir)[:-1]
    # designs_file_names = [f.split(".")[0] for f in designs_files]
    # 构建design-source 字典
    design_source = {}
    for designs_file in designs_files:
        designs_file_name = designs_file.split(".")[0]
        for source in sources_files:
            # source_name = source.split(".")[0]
            if designs_file_name in source:
                design_source[designs_file] = source
                break

    print(design_source)
    assert len(design_source) == len(designs_files), f"dict size {len(design_source)}, miss match {len(designs_files)}"
    print(f"Sources files: {len(sources_files)}")
    print(f"Designs files: {len(designs_files)}")
    # exit()
    semaphore = asyncio.Semaphore(semaphore)
    tasks = []

    total_tasks = len(
        [1 for design in designs_files for k, v in json.load(open(os.path.join(designs_dir, design), "r")).items() if
         v['perf'] >= 1.0])
    print(f"Total tasks: {total_tasks}")
    # exit(1)

    for idx, design in enumerate(designs_files):
        source = design_source[design]
        source_path = os.path.join(sources_dir, source)
        design_path = os.path.join(designs_dir, design)
        design = json.load(open(design_path, "r"))  # Consider making this async too
        for key, value in design.items():
            if value['perf'] < 1.0:
                continue
            tasks.append(process_file(source_path, value, semaphore, only_c=only_c))

        # if idx > process_num:
        #     break

    processed_sources = []
    for task in tqdm(asyncio.as_completed(tasks), total=len(tasks)):
        result = await task
        if result:
            processed_sources.append(result)

    print(processed_sources[0])
    print("Number of processed sources: ", len(processed_sources))

    # Save the processed sources to a file
    train_size = int(0.8 * len(processed_sources))
    test_size = len(processed_sources) - train_size
    print("Train size: ", train_size)
    print("Test size: ", test_size)
    with open("../data/gpt35/processed_sources_train_c.jsonl", "w") as f:
        for source in processed_sources[:train_size]:
            f.write(json.dumps(source) + "\n")

    with open("../data/gpt35/processed_sources_test_c.jsonl", "w") as f:
        for source in processed_sources[train_size:]:
            f.write(json.dumps(source) + "\n")
    with open("../data/gpt35/processed_sources_c.jsonl", "w") as f:
        for source in processed_sources:
            f.write(json.dumps(source) + "\n")


asyncio.run(main())
