# LLM-for-HLS

```
██╗     ██╗     ███╗   ███╗██╗  ██╗██╗  ██╗██╗     ███████╗
██║     ██║     ████╗ ████║██║  ██║██║  ██║██║     ██╔════╝
██║     ██║     ██╔████╔██║███████║███████║██║     ███████╗
██║     ██║     ██║╚██╔╝██║╚════██║██╔══██║██║     ╚════██║
███████╗███████╗██║ ╚═╝ ██║     ██║██║  ██║███████╗███████║
╚══════╝╚══════╝╚═╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝
```



LLM-for-HLS is an open-source project focused on leveraging Large Language Models (LLMs) for High-Level Synthesis (HLS). This project aims to construct datasets, fine-tune LLMs, and evaluate their performance in generating HLS code based on natural language instructions. It also involves some techniques like feedback loop and chain of thoughts.

## Project structure
LLM-for-HLS/
├── axolotl                  # Directory for the Axolotl project
├── data                     # Directory containing data files used by the project
├── functionality_data       # Directory storing data specifically for illustrating functionality
├── last_run_prepared        # Directory for prepared data cache
├── qlora-out                # Directory for outputs from qlora model
├── src                      # Source code directory where the main project code is located
├── inference.sh             # Shell script for running inference tasks
├── functionality_check.sh   # Script for executing functional or syntax checks on generated results.
├── README.md                # Markdown file providing an overview and general information about the project
├── requirements.txt         # Text file listing dependencies needed by the project
└── train.sh                 # Shell script for training models or running training processes


## Dataset construction
We have filtered the original labeled design benchmark dataset according to the 'perf' value to construct a dataset optimized for HLS code generation. Later, we extended the orignial dataset by adding tens of new source file after thoroughly inspecting the repository https://github.com/UT-LCA/ML4Accel-Dataset/tree/main/fpga_ml_dataset/HLS_dataset.
- dataset source codes path: ./data/sources 
- dataset design path: ./data/designs
- lately added dataset sources: ./data/new_data 
- dataset prepared path: ./data/gpt35/["processed_sources_train_c.jsonl", "processed_sources_test_c.jsonl"]


### Code to Text(instruction)
used gpt3.5(will probably to gpt4) to generate the corresponding instructions for generating HLS codes

### instruction fine-tuning
used alpaca format .jsonl dataset

{"instruction": "...", "input": "...", "output": "...", "source": "..."}
- adapter: qlora
- trained model path: ./qlora-out/merged
- predicted_data_dir: ./test_output*

## Environment setup

Install vLLM with CUDA 11.8.

```bash
export VLLM_VERSION=0.4.0
export PYTHON_VERSION=38 # Your Python version
```

```bash
pip install https://github.com/vllm-project/vllm/releases/download/v${VLLM_VERSION}/vllm-${VLLM_VERSION}+cu118-cp${PYTHON_VERSION}-cp${PYTHON_VERSION}-manylinux1_x86_64.whl --extra-index-url https://download.pytorch.org/whl/cu118
```

then, run:

```bash
pip install -r requirements.txt
```

then, cd into axlotl dir, and run:
```bash
pip install -e .
```

## Prepare Pre-trained Models
Create a new folder named "models" under the axolotl folder, then download the CodeLlama-7b-hf model and save it in the newly created "models" folder.

## fine-tuning command
Modify the axolotl/examples/code-llama/7b/qlora.yml file, changing the base_model to the absolute path of the model just downloaded.  Before running the script, modify the axolotl/examples/code-llama/7b/qlora.yml file and set the load_4bit parameter to true.
```bash
sh train.sh
```

## inference/test command
**Description:** This script is a wrapper for running various Python scripts related to feedback. Before running the script, modify the axolotl/examples/code-llama/7b/qlora.yml file and set the load_4bit parameter to false. And you must run pip uninstall flash-attn

**Usage:**

The script takes one or two command-line arguments:

* The first argument specifies the type of feedback or inference to run:
	+ `-syntax_feedback`: Run syntax feedback inference
	+ `-functionality_feedback`: Run functionality feedback inference
	+ `-cot`: Run CoT (Contextualized Transformer) inference
* The second argument is optional and only applies to the first two options:
	+ `-cot`: Use CoT for inference (only applicable with `-syntax_feedback` or `-functionality_feedback`)

**Examples:**

* `inference.sh -syntax_feedback`: Run syntax feedback inference without CoT
* `inference.sh -syntax_feedback -cot`: Run syntax feedback inference with CoT
* `inference.sh -functionality_feedback`: Run functionality feedback inference without CoT
* `inference.sh -functionality_feedback -cot`: Run functionality feedback inference with CoT
* `inference.sh -cot`: Run CoT inference
* `inference.sh`: Run inference without CoT (default behavior)

## syntax check
- python syntax_check.py
- sh check.sh -syntax_feedback
- sh check.sh -functionality_feedback
