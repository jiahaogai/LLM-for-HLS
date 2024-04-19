#include "Needwun.h"
 #pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[16641],char ptr[16641])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * (-1);
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * (-1);
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    row_up = (b_idx - 1) * 5;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      row = a_idx * 5;
      up_left = M[row_up + a_idx - 1] + ((SEQA[a_idx - 1] == SEQB[b_idx - 1]) ? 1 : (-1));
      up = M[row_up + a_idx] + (-1);
      left = M[row + a_idx - 1] + (-1);
      max = (up_left > ((up > left) ? (up) : (left)));
      score = ((max == up_left) ? (up_left) : ((max == up) ? (up) : (left)));
      M[row + a_idx] = score;
      a_str_idx = ((score == up_left) ? (a_idx - 1) : ((score == up) ? (a_idx) : (a_idx - 1)));
      b_str_idx = ((score == up_left) ? (b_idx - 1) : ((score == left) ? (b_idx - 1) : (b_idx)));
      ptr[row + a_idx] = ((a_str_idx << 16) | b_str_idx);
    }
  }
// Traceback
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace:
  for (r = 28; r >= 0; r--) {
    a_idx = (ptr[r] >> 16) & 0xffff;
    b_idx = ptr[r] & 0xffff;
    alignedA[a_idx] = SEQA[a_idx];
    alignedB[b_idx] = SEQB[b_idx];
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
  }
}