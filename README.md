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

## fine-tuning command
sh train.sh

## inference/test command
- python vllm_inference_without_cot.py
- sh inference.sh
- sh inference.sh -syntax_feedback
- sh inference.sh -functionality_feedback

## syntax check
- python syntax_check.py
- sh check.sh -syntax_feedback
- sh check.sh -functionality_feedback
