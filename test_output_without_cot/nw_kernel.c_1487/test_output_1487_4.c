#include <stdio.h>
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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      score = ((SEQA[a_idx - 1] == SEQB[b_idx - 1]) ? 1 : (- 1));
      row_up = (a_idx - 1) * (128 + 1);
      up_left = M[row_up + (b_idx - 1)] + score;
      up = M[row_up + b_idx] - 1;
      left = M[a_idx + (b_idx - 1)] - 1;
      max = (up_left > ((up > left) ? up : left))? (up_left) : ((up > left) ? up : left);
      M[a_idx + (b_idx * (128 + 1))] = max;
      row = ((max == left) ? (a_idx - 1) : ((max == up) ? (a_idx - 1 + ((b_idx - 1) * (128 + 1))) : (a_idx + (b_idx * (128 + 1)))));
      ptr[a_idx + (b_idx * (128 + 1))] = row;
    }
  }
// TraceBack
  a_idx = 128;
  b_idx = 128;
  r = 1;
  a_idx_up = a_idx - ((b_idx - 1) * (128 + 1));
  b_idx_up = b_idx - 1;
  a_idx_left = a_idx - 1;
  b_idx_left = b_idx;
/*
    trace: while(a_idx_up != 1 || b_idx_up != 1) {
      if (a_idx_left == a_idx_up || b_idx_left == b_idx_up) {
        up_left = M[a_idx_up * (128 + 1) + b_idx_up];
        left = M[a_idx_left * (128 + 1) + b_idx_left];
        if (up_left < left) {
          if (up_left < 0) {
            up_left = 0;
          }
          a_idx = a_idx_up;
          b_idx = b_idx_up;
          a_idx_up = a_idx - ((b_idx - 1) * (128 + 1));
          b_idx_up = b_idx - 1;
        }
        else {
          if (left < 0) {
            left = 0;
          }
          a_idx = a_idx_left;
          b_idx = b_idx_left;
          a_idx_left = a_idx - 1;
          b_idx_left = b_idx;
        }
      }
      else {
        score = ((SEQA[a_idx_left - 1] == SEQB[b_idx_left - 1]) ? 1 : (- 1));
        up = M[a_idx_left * (128 + 1) + b_idx_left] - 1;
        left = M[a_idx_left * (128 + 1) + b_idx_left - 1] - 1;
        max = (up > left)? (up) : (left);
        if (max == left) {
          if (left < 0) {
            left = 0;
          }
          a_idx = a_idx_left;
          b_idx = b_idx_left;
          a_idx_left = a_idx - 1;
          b_idx_left = b_idx;
        }
        else {
          if (up < 0) {
            up = 0;
          }
          a_idx = a_idx_up;
          b_idx = b_idx_up;
          a_idx_up = a_idx - ((b_idx - 1) * (128 + 1));
          b_idx_up = b_idx - 1;
        }
        if (max == up) {
          if (up_left < ((up > left) ? up : left)) {
            if (up_left < 0) {
              up_left = 0;
            }
            a_idx = a_idx_up;
            b_idx = b_idx_up;
            a_idx_up = a_idx - ((b_idx - 1) * (128 + 1));
            b_idx_up = b_idx - 1;
          }
          else {
            if (up < 0) {
              up = 0;
            }
            a_idx = a_idx_left;
            b_idx = b_idx_left;
            a_idx_left = a_idx - 1;
            b_idx_left = b_idx;
          }
        }
      }
      r++;
    }
    alignedA[r - 1] = '\0';
    alignedB[r - 1] = '\0';
*/
}