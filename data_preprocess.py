import os
import json

Task = "Translate the following question into HLS code:"

sources_dir = "data/sources"
designs_dir = "data/designs/v18"

# Get the list of all the files in the sources directory
sources_files = os.listdir(sources_dir)

# Get the list of all the files in the designs directory
designs_files = os.listdir(designs_dir)

processed_sources = []

for source, design in zip(sources_files, designs_files):
    source_path = os.path.join(sources_dir, source)
    design_path = os.path.join(designs_dir, design)

    with open(source_path, "r") as f:
        source_code = f.read()

    with open(design_path, "r") as f:
        design = json.load(f)

    perf_threshold = 1.0
    for key, value in design.items():
        if value['perf'] < perf_threshold:
            continue
        base_input = source_code + "------------------\n" + "Design point:\n" + "------------------\n"
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
                "input": "a nl question",
                "output": base_input + points
            }
        )

print(processed_sources[0])
print("Number of processed sources: ", len(processed_sources))

# Save the processed sources to a file
with open("data/processed_sources.jsonl", "w") as f:
    for source in processed_sources:
        f.write(json.dumps(source) + "\n")