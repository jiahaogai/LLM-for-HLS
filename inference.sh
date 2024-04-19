#!/bin/bash

# check if the number of arguments is 1
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 [-syntax_feedback | -functionality_feedback]"
  exit 1
fi

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