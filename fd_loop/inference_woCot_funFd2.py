import copy
import json
import os
import subprocess
import tempfile

import torch
import yaml
from tqdm import tqdm
from vllm import LLM
from vllm.sampling_params import SamplingParams

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"

model_path = "/root/autodl-tmp/LLM/LLM-for-HLS/qlora-out/merged"
device_count = torch.cuda.device_count()
llm = LLM(model_path, tensor_parallel_size=device_count, gpu_memory_utilization=0.5)

def compile_and_run(test_case_file_path, output_file_path):
    with tempfile.TemporaryDirectory() as temp_dir:
        executable_path = os.path.join(temp_dir, "test_fdtd")
        result = subprocess.run(["gcc", "-o", executable_path, test_case_file_path, output_file_path],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = result.stdout, result.stderr
        return result.returncode == 0, stdout.decode("utf-8"), stderr.decode("utf-8")

def generate_batch(prompts, vll_generate_params):
    outputs = llm.generate(prompts, vll_generate_params, use_tqdm=True)
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
    predicted_data_dir = args['predicted_data_dir'] + "_woCot_funFd2"
    os.makedirs(predicted_data_dir, exist_ok=True)

    prompts = [json.loads(line)['input'] for line in data]
    source_files = [json.loads(line)['source_file'] for line in data]

    for i in range(0, len(prompts), batch_size):
        batch_prompts = prompts[i:i + batch_size]
        batch_source_files = source_files[i:i + batch_size]
        feedback_loop_count = 0
        correct_generation = False

        while feedback_loop_count <= max_feedback_loops and not correct_generation:
            generated_batch = generate_batch(batch_prompts, args['generate_params'])

            for k, (input_text, predicted_dict, source_file) in enumerate(zip(batch_prompts, generated_batch, batch_source_files)):
                for j, predicted_text in predicted_dict.items():
                    with tempfile.NamedTemporaryFile(suffix='.c', delete=False) as tmp:
                        tmp.write(predicted_text.encode())
                        tmp.flush()
                        test_case_file = f"/root/autodl-tmp/LLM/LLM-for-HLS/functionality_data/{source_file.split('.c')[0]}_test.c"
                        flag, stdout, stderr = compile_and_run(test_case_file, tmp.name)
                        if not flag or stderr:
                            if feedback_loop_count == max_feedback_loops:
                                print("Max feedback loops reached with errors.")
                            else:
                                prompt = "Prompt with error: " + input_text + "\nError: " + stderr + \
                                         "\nPlease check the code and try again."
                                batch_prompts[k] = prompt
                        else:
                            correct_generation = True
                            with open(f'{predicted_data_dir}/{source_file}_{i+k}_test_output_{j}.c', 'w') as w:
                                w.write(predicted_text)

            feedback_loop_count += 1

if __name__ == "__main__":
    with open('/root/autodl-tmp/LLM/LLM-for-HLS/axolotl/examples/code-llama/7b/qlora.yml', 'r') as file:
        args = yaml.safe_load(file)
    args['generate_params'] = SamplingParams(
        n=1, 
        temperature=0.7, 
        max_tokens=4096 - 1024, 
        skip_special_tokens=True, 
        top_k=20, 
        top_p=0.9
    )
    with open(args['test_dataset_path'], 'r') as f:
        data = f.readlines()
    infer_with_syntax_check(args, data)
