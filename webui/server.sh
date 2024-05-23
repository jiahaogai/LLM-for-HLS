# start server
python -m vllm.entrypoints.openai.api_server --model /root/autodl-tmp/LLM-for-HLS/qlora-out/merged --dtype auto --host 127.0.0.1 --port 8080 --served-model-name llm --max-model-len 8192
# start UI
# streamlit run app.py --server.port 8501