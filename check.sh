#!/bin/bash

# 检查参数个数是否为1
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 [-syntax_feedback | -functionality_feedback]"
  exit 1
fi

# 根据参数调用不同的Python脚本
case "$1" in
  -syntax_feedback)
    python syntax_check.py
    ;;
  -functionality_feedback)
    python functionality_check_v2.py
    ;;
  *)
    echo "Invalid argument: $1"
    echo "Usage: $0 [-syntax_feedback | -functionality_feedback]"
    exit 1
    ;;
esac

