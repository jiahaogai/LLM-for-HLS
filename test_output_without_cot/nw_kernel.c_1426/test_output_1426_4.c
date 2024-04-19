#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#pragma ACCEL kernel

void needwun(char SEQA[128],
             char SEQB[128],
             char alignedA[256],
             char alignedB[256],
             int M[16641],
             char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;
  int index;
  int last_row_idx;
  int last_a_idx;
  int last_b_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = '\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_M:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = b_idx * 16;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    init_M:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = a_idx * 16;
      index = a_str_idx + b_str_idx;
      if (a_idx == 0 && b_idx == 0) {
        M[index] = SEQA[0] == SEQB[0] ? 1 : -1;
      }
      else if (a_idx == 0) {
        M[index] = M[index + 16] + (SEQA[0] == SEQB[b_idx] ? 1 : -1);
      }
      else if (b_idx == 0) {
        M[index] = M[a_str_idx] + (SEQA[a_idx] == SEQB[0] ? 1 : -1);
      }
      else {
        up_left = M[a_str_idx + b_str_idx - 1] + (SEQA[a_idx] == SEQB[b_idx] ? 1 : -1);
        up = M[a_str_idx + b_str_idx] + (- 1);
        left = M[a_str_idx + b_str_idx - 1] + (- 1);
        max = (up_left > up? up_left : up);
        max = (left > max? left : max);
        M[index] = max;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace_back:
  for (r = 31; r >= 0; r--) {
    row = r * 16;
    row_up = (r - 1) * 16;
    last_row_idx = row + 15;
    last_a_idx = 5 * 16 - 1;
    last_b_idx = 5 * 16 - 16;
    a_idx = last_a_idx;
    b_idx = last_b_idx;
    a_str_idx = a_idx + row;
    b_str_idx = b_idx + row_up;
    index = a_str_idx + b_str_idx;
    score = M[index];
    while (a_idx > 0 || b_idx > 0) {
      if (a_idx < 0) {
        a_idx = 0;
      }
      if (b_idx < 0) {
        b_idx = 0;
      }
      a_str_idx = a_idx + row;
      b_str_idx = b_idx + row_up;
      if (a_str_idx == last_row_idx && b_str_idx == last_b_idx) {
        break;
      }
      if (M[a_str_idx + b_str_idx] == M[a_str_idx + b_str_idx + 16] + (- 1)) {
        a_idx++;
        b_idx++;
        a_str_idx = a_idx + row;
        b_str_idx = b_idx + row_up;
        index = a_str_idx + b_str_idx;
        score = M[index];
      }
      else {
        if (M[a_str_idx + b_str_idx] == M[a_str_idx + 1 + b_str_idx] + (- 1)) {
          a_idx++;
          a_str_idx = a_idx + row;
          index = a_str_idx + b_str_idx;
          score = M[index];
        }
        else {
          if (M[a_str_idx + b_str_idx] == M[a_str_idx + 1 + b_str_idx + 16] + (- 1)) {
            a_idx++;
            b_idx++;
            a_str_idx = a_idx + row;
            b_str_idx = b_idx + row_up;
            index = a_str_idx + b_str_idx;
            score = M[index];
          }
          else {
            if (M[a_str_idx + b_str_idx] == M[a_str_idx + 1 + b_str_idx + 16] + (- 1)) {
              a_idx++;
              b_idx++;
              a_str_idx = a_idx + row;
              b_str_idx = b_idx + row_up;
              index = a_str_idx + b_str_idx;
              score = M[index];
            }
            else {
              if (M[a_str_idx + b_str_idx] == M[a_str_idx + 1 + b_str_idx] + (- 1)) {
                a_idx++;
                b_str_idx = b_idx + row_up;
                index = a_str_idx + b_str_idx;
                score = M[index];
              }
              else {
                if (M[a_str_idx + b_str_idx] == M[a_str_idx + 1 + b_str_idx + 16] + (- 1)) {
                  a_idx++;
                  b_idx++;
                  a_str_idx = a_idx + row;
                  b_str_idx = b_idx + row_up;
                  index = a_str_idx + b_str_idx;
                  score = M[index];
                }
                else {
                  if (M[a_str_idx + b_str_idx] == M[a_str_idx + b_str_idx - 1] + (- 1)) {
                    a_idx++;
                    b_str_idx = b_idx + row_up;
                    index = a_str_idx + b_str_idx;
                    score =