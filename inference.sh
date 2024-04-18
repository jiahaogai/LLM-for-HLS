#!/bin/bash

# 检查参数个数是否为1
#if [ "$#" -ne 1 ]; then
#  echo "Usage: $0 [-syntax_feedback | -functionality_feedback]"
#  exit 1
#fi

# 根据参数调用不同的Python脚本
case "$1" in
  -syntax_feedback)
    python fd_loop/fd_loop.py
    ;;
  -functionality_feedback)
    python fd_loop/fd_loop_fc.py
    ;;
  *)
    python vllm_inference.py
    ;;
esac