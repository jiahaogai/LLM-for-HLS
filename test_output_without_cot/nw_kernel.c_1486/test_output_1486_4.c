#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
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
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = '-';
  }
  alignedA[64] = '\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  alignedB[64] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_score:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx + 64] = SEQA[a_idx];
    M[a_idx] = 0;
    ptr[a_idx] = 0;
  }
  M[64] = 0;
  ptr[64] = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  init_score_row:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx + 64] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_str_idx = a_idx * 64;
    row_up = a_idx * 64;
    row = a_idx + 64;
    last_row_idx = ((a_idx + 1) * 64) - 1;
    last_a_idx = a_idx + 64 - 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7_0}
    up:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      b_str_idx = b_idx * 64;
      up_left = M[row_up + b_idx];
      up = M[row_up + b_idx + 1] + 1;
      left = M[row_up + b_idx] + 1;
      if (SEQA[last_a_idx] == SEQB[b_idx]) {
        score = 1;
      }
       else {
        score = 0;
      }
      max = (up_left > ((up > left)?up:left))?up_left:((up > left)?up:left);
      M[row + b_idx] = max;
      if (max == left) {
        ptr[row + b_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[row + b_idx] = 1;
        }
         else {
          ptr[row + b_idx] = 0;
        }
      }
    }
  }
}