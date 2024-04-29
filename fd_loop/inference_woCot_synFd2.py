import copy
import gc
import json
import os
import subprocess

import torch
import yaml
from tqdm import tqdm
from vllm import LLM
from vllm.sampling_params import SamplingParams

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"
model_path = "/root/autodl-tmp/LLM/LLM-for-HLS/qlora-out/merged"
device_count = torch.cuda.device_count()
llm = LLM(model_path, tensor_parallel_size=device_count, gpu_memory_utilization=0.5)

def check_c_file_syntax(file_path):
    process = subprocess.Popen(
        ["gcc", "-fsyntax-only", file_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    stdout, stderr = process.communicate()
    return process.returncode == 0, stderr.decode()

def generate_batch(prompts, generate_params):
    outputs = llm.generate(prompts, generate_params, use_tqdm=True)
    processed_outputs = []
    for output in outputs:
        processed_output = {}
        for idx, out in enumerate(output.outputs):
            processed_output[idx] = out.text.replace('</s>', '').replace('```', '').strip()
        processed_outputs.append(processed_output)
    return processed_outputs

def infer_with_syntax_check(args, data):
    max_feedback_loops = 2
    batch_size = 1
    predicted_data_dir = args['predicted_data_dir'] + "_woCot_synFd2"
    os.makedirs(predicted_data_dir, exist_ok=True)

    prompts = [json.loads(line)['input'] for line in data]
    source_files = [json.loads(line)['source_file'] for line in data]

    for i in range(0, len(prompts), batch_size):
        feedback_loop_count = 0
        while feedback_loop_count <= max_feedback_loops:
            batch_prompts = prompts[i:i + batch_size]
            generated_batch = generate_batch(batch_prompts, args['generate_params'])

            for idx, (prompt, generated_output) in enumerate(zip(batch_prompts, generated_batch)):
                for j, output_text in generated_output.items():
                    file_path = f'/root/autodl-tmp/LLM/LLM-for-HLS/tmp_{i}_{j}.c'
                    with open(file_path, 'w') as f:
                        f.write(output_text)

                    flag, message = check_c_file_syntax(file_path)
                    if not flag:
                        if feedback_loop_count == max_feedback_loops:
                            print("Max feedback loops reached with syntax errors.")
                        else:
                            prompt = "Prompt with error: " + prompt + "\nError: " + message
                            batch_prompts[idx] = prompt
                    else:
                        with open(os.path.join(predicted_data_dir, f"{source_files[i]}_{i}_{j}.c"), 'w') as f:
                            f.write(output_text)
                if flag:
                    break
            if flag:
                break
            feedback_loop_count += 1

        gc.collect()
        torch.cuda.empty_cache()

if __name__ == "__main__":
    with open('/root/autodl-tmp/LLM/LLM-for-HLS/axolotl/examples/code-llama/7b/qlora.yml', 'r') as file:
        args = yaml.safe_load(file)
    args['generate_params'] = SamplingParams(
        n=1,  # number of samples to generate
        temperature=0.7,
        max_tokens=4096,
        skip_special_tokens=True,
        top_k=20,
        top_p=0.9
    )
    with open(args['test_dataset_path'], 'r') as f:
        data = f.readlines()
    infer_with_syntax_check(args, data)
