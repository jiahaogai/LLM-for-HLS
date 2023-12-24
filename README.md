# LLM-for-HLS


### fine tuning
accelerate launch scripts/finetune.py examples/code-llama/7b/qlora.yml

### inference
python -m axolotl.cli.inference examples/code-llama/7b/qlora.yml --lora_model_dir="./qlora-out"
