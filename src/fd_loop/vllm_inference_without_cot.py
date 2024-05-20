import os

import torch

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"


from vllm import LLM
from vllm.sampling_params import SamplingParams
import yaml
import json

# Get the absolute path of the current file
current_file_path = os.path.abspath(__file__)

# Get the directory of the current file
current_dir = os.path.dirname(current_file_path)
# 打开YAML文件
with open(os.path.join(current_dir,'../../axolotl/examples/code-llama/7b/qlora.yml'), 'r') as file:
    # 加载YAML内容
    args = yaml.safe_load(file)

# 打印读取的数据
# print(args)
# exit(0)
generate_params = SamplingParams(
    n=args['pass_num'],  # number of samples to generate
    temperature=0,  # sampling temperature 0.7
    use_beam_search=True,  # use beam search instead of top-k sampling
    early_stopping=False,  # stop sampling when all sequences finished
    max_tokens=2048,  # maximum number of tokens to generate
    skip_special_tokens=True,  # skip special tokens like <PAD>, <BOS>, etc.
    top_k=-1,  # top-k sampling 20
    top_p=1,  # top-p sampling 0.9

)

# bs = args['inference_batch_size']
bs = 4
tensor_parallel_size = torch.cuda.device_count()
# model_path = "/root/autodl-tmp/pretrain_models/deepseek-coder-6.7b-instruct"
model_path = "../../qlora-out/merged"
# Combine the current directory with the relative path to get the new absolute path
model_path = os.path.abspath(os.path.join(current_dir, model_path))
llm = LLM(model_path, tensor_parallel_size=1, gpu_memory_utilization=1, dtype="float16")
use_chain_of_thought = False
chain_of_thought_prompt = """
Let's think step by step.

First, Consider the characteristics of FPGA.
Second, Determine the program structure.
Third, Write code logic.
Fourth, Consider data types and interfaces.

Finally, Generate code: 
"""


def generate_batch(prompts):
    outputs = llm.generate(prompts, generate_params, use_tqdm=True)

    processed_outputs = []
    for i in range(len(outputs)):
        sample_outputs = {}
        for j in range(len(outputs[i].outputs)):
            sample_outputs[j] = outputs[i].outputs[j].text.replace('</s>', '').replace('```', '').strip()
        processed_outputs.append(sample_outputs)

    return processed_outputs


# generated = []
# batch_prompts = []
predicted_data_dir = args['predicted_data_dir']
predicted_data_dir += f"_without_cot"


print(f"predicted_data_dir: {predicted_data_dir}")
# 清空predicted_data_dir目录
os.system(f"rm -rf {predicted_data_dir}")
os.makedirs(predicted_data_dir, exist_ok=True)
with open(args['test_dataset_path'], 'r') as f:
    data = f.readlines()

if use_chain_of_thought:
    prompts = [json.loads(line)['input'] + "\n\n" + chain_of_thought_prompt for line in data]
else:
    prompts = [json.loads(line)['input'] for line in data]

source_files = [json.loads(line)['source_file'] for line in data]
print(f"source_files: {len(source_files)}")
scale_factor = 1 / 2
outputs = [json.loads(line)['output'] for line in data]
current_idx = 0
next_idx = bs

for i in range(0, len(prompts), bs):
    batch_prompts = prompts[i:i + bs]
    batch_outputs = outputs[i:i + bs]
    batch_source_files = source_files[i:i + bs]

    generated_batch = generate_batch(batch_prompts)
    # print(f"batch {i} generated")
    # print(generated_batch)
    # print(len(batch_prompts), len(generated_batch), len(batch_source_files))
    for k, (input_text, predicted_dict, source_file) in enumerate(
            zip(batch_prompts, generated_batch, batch_source_files)):
        line = {
            "input": input_text,
            # "output": output,
            "predicted": predicted_dict,
            "source_file": source_file
        }

        os.makedirs(f'{predicted_data_dir}/{line["source_file"]}_{i+k}', exist_ok=True)
        for j, text in line['predicted'].items():
            with open(f'{predicted_data_dir}/{line["source_file"]}_{i+k}/test_output_{i+k}_{j}.c', 'w') as w:
                w.write(text)
    # exit()
