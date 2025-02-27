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

# Get the absolute path of the current file
current_file_path = os.path.abspath(__file__)

# Get the directory of the current file
current_dir = os.path.dirname(current_file_path)

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"

if os.path.exists(os.path.join(current_dir,"../../qlora-out/merged")):
    print("find merged model")
else:
    print("not find merged model")
    os.system(
        "python3 -m axolotl.cli.merge_lora ../../axolotl/examples/code-llama/7b/qlora.yml --lora_model_dir='../../axolotl/qlora-out'")

tensor_parallel_size = torch.cuda.device_count()
# model_path = "/root/autodl-tmp/pretrain_models/deepseek-coder-6.7b-instruct"

print(current_file_path)
# Relative path
model_path = "../../qlora-out/merged"

# Combine the current directory with the relative path to get the new absolute path
model_path = os.path.abspath(os.path.join(current_dir, model_path))
device_count = torch.cuda.device_count()
llm = LLM(model_path, tensor_parallel_size=device_count, gpu_memory_utilization=0.5)


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
    Check if C code exists in the text.
    :param text:
    :return: True/False
    """
    return text.find("int main") != -1 or text.find("void main") != -1


def generate_batch(prompts, vll_generate_params):
    outputs = llm.generate(prompts, vll_generate_params, use_tqdm=True)

    processed_outputs = []
    for i in range(len(outputs)):
        sample_outputs = {}
        for j in range(len(outputs[i].outputs)):
            sample_outputs[j] = outputs[i].outputs[j].text.replace('</s>', '').replace('```', '').strip()
        processed_outputs.append(sample_outputs)

    return processed_outputs


def infer_with_syntax_check(args, data):
    batch_size = 1
    use_chain_of_thought = args.get('use_chain_of_thought', False)
    chain_of_thought_prompt = args.get('chain_of_thought_prompt', "")
    predicted_data_dir = args['predicted_data_dir']
    predicted_data_dir += "_woCot_synFd"
    print(f"predicted_data_dir: {predicted_data_dir}")
    # Clear the predicted_data_dir directory.
    os.system(f"rm -rf {predicted_data_dir}")
    os.makedirs(predicted_data_dir, exist_ok=True)

    if use_chain_of_thought:
        prompts = [json.loads(line)['input'] + "\n\n" + chain_of_thought_prompt for line in data]
    else:
        prompts = [json.loads(line)['input'] for line in data]

    source_files = [json.loads(line)['source_file'] for line in data]
    print(f"source_files: {len(source_files)}")
    outputs = [json.loads(line)['output'] for line in data]

    for i in range(0, len(prompts), batch_size):
        batch_prompts = prompts[i:i + batch_size]
        batch_outputs = outputs[i:i + batch_size]
        batch_source_files = source_files[i:i + batch_size]

        generated_batch = generate_batch(batch_prompts, generate_params)

        for k, (input_text, output, predicted_dict, source_file) in enumerate(
                zip(batch_prompts, batch_outputs, generated_batch, batch_source_files)):

            # source_file = line['source_file']
            for _, predicted_text in predicted_dict.items():
                # predicted_text = predicted_text.replace(input_text, '').replace('</s>', '').strip()
                predicted_text = predicted_text[predicted_text.find('#'):]

                with open(f'./tmp.c', 'w') as f:
                    f.write(predicted_text)

                flag, message = check_c_file_syntax(f'./tmp.c')
                if not flag:
                    input_text = "The following code is the result of prompt: " + input_text + "\nCode: " + predicted_text + "\nError: " + message + \
                                         "\nPlease check the code and try again."
                    vll_generate_params = copy.deepcopy(generate_params)
                    vll_generate_params.max_tokens = 1024
                    vll_generate_params.n = 1
                    predicted_dict[_] = generate_batch([input_text], vll_generate_params)[0][0]
                    # predicted_dict[i] = generate_batch([input_text])[0][0]
            line = {
                "input": input_text,
                # "output": output,
                "predicted": predicted_dict,
                "source_file": source_file
            }
            os.makedirs(f'{predicted_data_dir}/{line["source_file"]}_{i+k}', exist_ok=True)
            for j, text in line['predicted'].items():
                with open(os.path.join(predicted_data_dir, f"{source_file}_{i + k}", f"test_output_{i + k}_{j}.c"),
                          'w') as f:
                    f.write(text)
        # destroy_model_parallel()

        # Remove unnecessary variables.
        del generated_batch
        del batch_prompts
        del batch_outputs
        del batch_source_files

        torch.cuda.empty_cache()

if __name__ == "__main__":
    
    with open(os.path.join(current_dir,'../../axolotl/examples/code-llama/7b/qlora.yml'), 'r') as file:
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
        data = f.readlines()

    infer_with_syntax_check(args, data)
