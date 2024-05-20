#!/bin/bash

# 检查参数个数是否为2
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 [-woCot | -cot] [-woFd | -synFd | -funFd]"
  exit 1
fi

# 将参数组合成一个字符串
args="$1_$2"

# 根据参数调用不同的Python脚本
case "$args" in
  -woCot_-woFd)
    python ./src/syntax_check/syntax_check_woCot_woFd.py
    ;;
  -woCot_-synFd)
    python ./src/syntax_check/syntax_check_woCot_synFd.py
    ;;
  -woCot_-funFd)
    python ./src/syntax_check/syntax_check_woCot_funFd.py
    ;;
  -cot_-woFd)
    python ./src/syntax_check/syntax_check_cot_woFd.py
    ;;
  -cot_-synFd)
    python ./src/syntax_check/syntax_check_cot_synFd.py
    ;;
  -cot_-funFd)
    python ./src/syntax_check/syntax_check_cot_funFd.py
    ;;
  *)
    echo "Invalid argument combination: $1 $2"
    echo "Usage: $0 [-woCot | -cot] [-woFd | -synFd | -funFd]"
    exit 1
    ;;
esac
