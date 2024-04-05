import os

import torch
from tqdm import tqdm

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"

# if os.path.exists("/root/autodl-tmp/LLM-for-HLS/qlora-out/merged"):
#     print("find merged model")
# else:
#     print("not find merged model")
#     os.system(
#         "python3 -m axolotl.cli.merge_lora axolotl/examples/code-llama/7b/qlora.yml --lora_model_dir='/root/autodl-tmp/LLM-for-HLS/axolotl/qlora-out'")

from vllm import LLM
from vllm.sampling_params import SamplingParams
import yaml
import json

# 打开YAML文件
with open('/root/autodl-tmp/LLM-for-HLS/axolotl/examples/code-llama/7b/qlora.yml', 'r') as file:
    # 加载YAML内容
    args = yaml.safe_load(file)

# 打印读取的数据
# print(args)
# exit(0)
generate_params = SamplingParams(
    n=args['pass_num'],  # number of samples to generate
    temperature=0.7,  # sampling temperature
    use_beam_search=False,  # use beam search instead of top-k sampling
    early_stopping=False,  # stop sampling when all sequences finished
    max_tokens=2048,  # maximum number of tokens to generate
    skip_special_tokens=True,  # skip special tokens like <PAD>, <BOS>, etc.
    top_k=20,  # top-k sampling
    top_p=0.9,  # top-p sampling

)

bs = args['inference_batch_size']

tensor_parallel_size = torch.cuda.device_count()
# model_path = "/root/autodl-tmp/pretrain_models/deepseek-coder-6.7b-instruct"
model_path = "/root/autodl-tmp/LLM-for-HLS/qlora-out/merged"
llm = LLM(model_path, tensor_parallel_size=1, gpu_memory_utilization=1)
use_chain_of_thought = True
chain_of_thought_prompt = """
Let's think step by step.

First, Consider the characteristics of FPGA.
Second, Determine the program structure.
Third, Write code logic.
Fourth, Consider data types and interfaces.

Finally, Generate code: 
"""


def generate_batch(prompts):
    outputs = llm.generate(prompts, generate_params, use_tqdm=False)

    processed_outputs = []
    for i in range(len(outputs)):
        sample_outputs = []
        for j in range(len(outputs[i].outputs)):
            sample_outputs.append(outputs[i].outputs[j].text)
        processed_outputs.append(sample_outputs)

    return processed_outputs


generated = []
batch_prompts = []

with open(args['test_dataset_path'], 'r') as f:
    f = f.readlines()[:20]
    if use_chain_of_thought:
        prompts = [line['input'] + "\n\n" + chain_of_thought_prompt]
    for line in tqdm(f, total=len(f) // bs, desc="Generating"):
        line = json.loads(line)
        prompt = line['input']
        if use_chain_of_thought:
            prompt = prompt + "\n\n" + chain_of_thought_prompt
        batch_prompts.append(prompt)
        if len(batch_prompts) == bs:
            predicted_texts = generate_batch(batch_prompts)

            for input_text, predicted_text in zip(batch_prompts, predicted_texts):
                predicted_text_dict = {i: text.replace(input_text, '').replace('</s>', '') for i, text in
                                       enumerate(predicted_text)}
                generated.append(
                    {
                        "input": input_text,
                        "output": line['output'],
                        "predicted": predicted_text_dict
                    }
                )
            batch_prompts = []
    # predicted_texts = generate_batch(batch_prompts)
    #
    # for input_text, predicted_text in zip(batch_prompts, predicted_texts):
    #     predicted_text_dict = {i: text.replace(input_text, '').replace('</s>', '') for i, text in
    #                            enumerate(predicted_text)}
    #     generated.append(
    #         {
    #             "input": input_text,
    #             "output": line['output'],
    #             "predicted": predicted_text_dict
    #         }
    #     )
predicted_data_dir = args['predicted_data_dir']

# 清空predicted_data_dir目录
os.system(f"rm -rf {predicted_data_dir}")
os.makedirs(predicted_data_dir, exist_ok=True)

with open(f'{predicted_data_dir}/test_output.jsonl', 'w') as f:
    for line in generated:
        f.write(json.dumps(line) + '\n')

# 将每一个输出的predicted保存为一个个单独的.c文件
for i, line in enumerate(generated):
    os.makedirs(f'{predicted_data_dir}/test_output_{i}', exist_ok=True)
    for j, text in line['predicted'].items():
        with open(f'{predicted_data_dir}/test_output_{i}/test_output_{i}_{j}.c', 'w') as f:
            f.write(text)
