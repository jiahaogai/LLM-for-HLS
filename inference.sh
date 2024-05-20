#!/bin/bash

export TOKENIZERS_PARALLELISM=true

case "$1" in
  -syntax_feedback)
    if [ "$2" = "-cot" ]; then
        python src/fd_loop/inference_cot_synFd.py
    else
        python src/fd_loop/inference_woCot_synFd.py
    fi
    ;;
  -functionality_feedback)
    if [ "$2" = "-cot" ]; then
        python src/fd_loop/inference_cot_funFd.py
    else
        python src/fd_loop/inference_woCot_funFd.py
    fi
    ;;
  -cot)
    python src/fd_loop/vllm_inference_cot.py
    ;;
  *)
    python src/fd_loop/vllm_inference_without_cot.py
    ;;
esac