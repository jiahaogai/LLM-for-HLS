import asyncio
import json
import os
import openai

api_key = "sk-XudHwpJ8hdJGuxIC3193E4F1B6Ee416982261bF38d5f5b6d"
api_base = "https://chatwithai.icu/v1"

client = openai.AsyncOpenAI(api_key=api_key, base_url=api_base)
base_prompt = "## Task: Give one comprehensive but very concise natural language instruction used to generate the following HLS codes written in C, you need describe the process of codes and which specific #pragma values to use respectively in natural languages.\n " \

"For example, you might use 'Don't automatically pipeline this loop' to describe '#pragma ACCEL PIPELINE \"off\"' , and 'Process this loop in its original, full form without breaking it into smaller chunks' to describe '#pragma ACCEL TILE FACTOR=1', and 'Run the iterations of this loop one after the other, not in parallel' to describe '#pragma ACCEL PARALLEL FACTOR=1', and 'Treat the following function as a hardware kernel for acceleration' to describe '#pragma ACCEL kernel'\n"
              

async def get_response(prompt):
    completion = await client.chat.completions.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": "You are a helpful HLS code generator."},
            {"role": "user", "content": base_prompt + prompt}
        ]
    )
    return completion.choices[0].message.content


async def main():
    Task = "Generate HLS code with the following instructions:"

    sources_dir = "data/sources"
    designs_dir = "data/designs/v18"

    # Get the list of all the files in the sources directory
    sources_files = os.listdir(sources_dir)[:1] # 暂时先取前两条C语言文件

    # Get the list of all the files in the designs directory
    designs_files = os.listdir(designs_dir)[:1] # 暂时先取前两条C语言文件，之后记得改过来，删掉[:2]

    processed_sources = []

    for source, design in zip(sources_files, designs_files):
        source_path = os.path.join(sources_dir, source)
        design_path = os.path.join(designs_dir, design)
        # file_path = os.path.join(base_dir, file)

            # total_responses.append(response)

        # design_name = file.split(".")[0].replace("_kernel", '') + ".json"
        # design_path = os.path.join("data/designs/v18", design_name)
        design = json.load(open(design_path, "r"))
        perf_threshold = 1.0
        for key, value in design.items():
            if value['perf'] < perf_threshold:
                continue
            with open(source_path, "r") as f:
                prompt = f.read()
                response = await get_response(prompt)
                print("\n##" + response)
            base_input = prompt + "------------------\n" + "Design point:\n" + "------------------\n"
            # for k, v in value['point'].items():
            #     base_input = base_input.replace(k, str(v))
            points = "\n".join([f"{k}: {v}" for k, v in value['point'].items()])
            valid_flag = "valid" if value['valid'] else "invalid"
            util = ",".join([f"{k}: {v}" for k, v in value['res_util'].items()])
            # output = (
            #     "The design point is {valid_flag}.\n"
            #     "The resource utilization is {util}.\n"
            # ).format(valid_flag=valid_flag, util=util)
            processed_sources.append(
                {
                    "instruction": Task,
                    "input": response,
                    "output": base_input + points
                }
            )

    print(processed_sources[0])
    print("Number of processed sources: ", len(processed_sources))

    # Save the processed sources to a file
    train_size = int(0.8 * len(processed_sources))
    test_size = len(processed_sources) - train_size
    print("Train size: ", train_size)
    print("Test size: ", test_size)
    with open("data/processed_sources_train.jsonl", "w") as f:
        for source in processed_sources[:train_size]:
            f.write(json.dumps(source) + "\n")

    with open("data/processed_sources_test.jsonl", "w") as f:
        for source in processed_sources[train_size:]:
            f.write(json.dumps(source) + "\n")
    with open("data/processed_sources.jsonl", "w") as f:
        for source in processed_sources:
            f.write(json.dumps(source) + "\n")


asyncio.run(main())
