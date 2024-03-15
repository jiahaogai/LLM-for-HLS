import copy
import json
import os
import subprocess

import torch
import yaml
from tqdm import tqdm
from vllm import LLM
from vllm.sampling_params import SamplingParams

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"

# if os.path.exists("/root/autodl-tmp/LLM-for-HLS/qlora-out/merged"):
#     print("find merged model")
# else:
#     print("not find merged model")
#     os.system(
#         "python3 -m axolotl.cli.merge_lora axolotl/examples/code-llama/7b/qlora.yml --lora_model_dir='/root/autodl-tmp/LLM-for-HLS/axolotl/qlora-out'")

tensor_parallel_size = torch.cuda.device_count()
# model_path = "/root/autodl-tmp/pretrain_models/deepseek-coder-6.7b-instruct"
model_path = "/root/autodl-tmp/LLM-for-HLS/qlora-out/merged"
llm = LLM(model_path, tensor_parallel_size=1, gpu_memory_utilization=1)


def check_c_file_syntax(file_path):
    process = subprocess.Popen(
        ["gcc", "-fsyntax-only", file_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )

    stdout, stderr = process.communicate()

    if process.returncode != 0:
        return False, stderr.decode()
    else:
        return True, "No syntax errors found."
    # return process.returncode == 0  # True if no syntax errors


def find_c_code(text):
    """
    从text中检查是否存在C代码
    :param text:
    :return: True/False
    """
    return text.find("int main") != -1 or text.find("void main") != -1


def generate_batch(prompts, generate_params):
    outputs = llm.generate(prompts, generate_params, use_tqdm=False)

    processed_outputs = []
    for i in range(len(outputs)):
        sample_outputs = []
        for j in range(len(outputs[i].outputs)):
            sample_outputs.append(outputs[i].outputs[j].text)
        processed_outputs.append(sample_outputs)

    return processed_outputs


def infer_with_syntax_check(args, generate_params, data):
    bs = args['inference_batch_size']
    generated = []
    batch_prompts = []

    for line in tqdm(data, total=len(data) // bs, desc="Generating"):
        line = json.loads(line)
        batch_prompts.append(line['input'])
        if len(batch_prompts) == bs:
            batch_predicted_texts = generate_batch(batch_prompts, generate_params)

            for input_text, predicted_texts in zip(batch_prompts, batch_predicted_texts):
                # predicted_text_dict = {i: text.replace(input_text, '').replace('</s>', '').strip() for i, text in
                #                        enumerate(predicted_texts)}
                predicted_text_dict = {}
                # 执行语法检查
                for i, predicted_text in enumerate(predicted_texts):



                    # 去除第一个#之前的内容
                    predicted_text = predicted_text.replace(input_text, '').replace('</s>', '').strip()
                    # index = predicted_text.find('#')
                    predicted_text = predicted_text[predicted_text.find('#'):]

                    # 将预测的文本写入临时文件
                    with open(f'/root/autodl-tmp/LLM-for-HLS/tmp.c', 'w') as f:
                        f.write(predicted_text)

                    flag, message = check_c_file_syntax(f'/root/autodl-tmp/LLM-for-HLS/tmp.c')
                    if not flag:
                        # 在prompt中加入错误信息, 再次进行推理
                        # input_text += f"/* {message} */"
                        if find_c_code(predicted_text):
                            # 如果检测到预测结果中存在C代码，就加入错误信息
                            # 如果没有检测到，那么就重新生成
                            input_text = "The following code is the result of prompt: " + input_text + "\nCode: " + predicted_text + "\nError: " + message + \
                                         "\nPlease check the code and try again."
                        else:
                            print("No C code found in the predicted text, re-generating...")
                        ori_n = generate_params.n
                        generate_params.n = 1
                        re_predicted_texts = generate_batch([input_text], generate_params)
                        generate_params.n = ori_n
                        # 更新predicted_text_dict
                        predicted_text = re_predicted_texts[0][0].replace(input_text, '').replace('</s>', '').strip()
                    predicted_text_dict[i] = predicted_text

                generated.append(
                    {
                        "input": input_text,
                        "output": line['output'],
                        "predicted": predicted_text_dict
                    }
                )
            batch_prompts = []

    predicted_data_dir = args['predicted_data_dir']
    predicted_data_dir += f"_with_feedback_loop"
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


def main():
    # 打开YAML文件
    with open('/root/autodl-tmp/LLM-for-HLS/axolotl/examples/code-llama/7b/qlora.yml', 'r') as file:
        # 加载YAML内容
        args = yaml.safe_load(file)
    args['pass_num'] = 3
    generate_params = SamplingParams(
        n=args['pass_num'],  # number of samples to generate
        temperature=0.7,  # sampling temperature
        use_beam_search=False,  # use beam search instead of top-k sampling
        early_stopping=False,  # stop sampling when all sequences finished
        max_tokens=4096 - 1024,  # maximum number of tokens to generate
        skip_special_tokens=True,  # skip special tokens like <PAD>, <BOS>, etc.
        top_k=20,  # top-k sampling
        top_p=0.9,  # top-p sampling

    )
    args['inference_batch_size'] = 1
    with open(args['test_dataset_path'], 'r') as f:
        data = f.readlines()[:20]

    infer_with_syntax_check(args, generate_params, data)


if __name__ == "__main__":
    main()
