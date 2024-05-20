#!/bin/bash

# Check if the number of parameters is 2
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 [-woCot | -cot] [-woFd | -synFd | -funFd]"
  exit 1
fi

# Combine parameters into a single string
args="$1_$2"

# Call different Python scripts based on the parameters
case "$args" in
  -woCot_-woFd)
    python ./src/func_checkfunctionality_check_woCot_woFd.py
    ;;
  -woCot_-synFd)
    python ./src/func_checkfunctionality_check_woCot_synFd.py
    ;;
  -woCot_-funFd)
    python ./src/func_checkfunctionality_check_woCot_funFd.py
    ;;
  -cot_-woFd)
    python ./src/func_checkfunctionality_check_cot_woFd.py
    ;;
  -cot_-synFd)
    python ./src/func_checkfunctionality_check_cot_synFd.py
    ;;
  -cot_-funFd)
    python ./src/func_checkfunctionality_check_cot_funFd.py
    ;;
  *)
    echo "Invalid argument combination: $1 $2"
    echo "Usage: $0 [-woCot | -cot] [-woFd | -synFd | -funFd]"
    exit 1
    ;;
esac
