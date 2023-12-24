# LLM-for-HLS

## Dataset construction

filtered according to the value of 'perf' from the original labeled design benchmark dataset

### code to text(instruction)
used gpt4 to generate the corresponding instructions for generating HLS codes

### instruction fine-tuning
used alpaca format .jsonl dataset

{"instruction": "...", "input": "...", "output": "..."}

## fine-tuning command
accelerate launch scripts/finetune.py examples/code-llama/7b/qlora.yml

## inference/test command
python -m axolotl.cli.inference examples/code-llama/7b/qlora.yml --lora_model_dir="./qlora-out"

## evaluation
Latency, Energy, resource consumption

HLS tools choices? out-of-the-box docker?

SDX? Xilinx Vivado HLS？LegUp Computing？
