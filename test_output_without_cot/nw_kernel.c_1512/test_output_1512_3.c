#include <math.h>
#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[160],char alignedB[160],int M[160][160],char ptr[160])
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
  int a_str_idx;
  int b_str_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = '-';
    M[a_idx][0] = ((int )a_idx) * -1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
    M[0][b_idx] = ((int )b_idx) * -1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = a_idx - 1;
      row = a_idx;
      up_left = M[row_up][b_idx - 1] + score;
      up = M[row_up][b_idx] - 1;
      left = M[row][b_idx - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row][b_idx] = max;
      if (max == left) {
        a_idx_up = row_up;
        b_idx_up = b_idx - 1;
      }
       else {
        if (max == up) {
          a_idx_up = row_up;
          b_idx_up = b_idx;
        }
         else {
          a_idx_up = row;
          b_idx_up = b_idx;
        }
      }
    }
    a_str_idx = ((int )SEQA[a_idx - 1]);
    b_str_idx = ((int )SEQB[b_idx - 1]);
    alignedA[(((a_idx + 1) - 1) * 5)] = a_str_idx;
    alignedB[(((b_idx + 1) - 1) * 5)] = b_str_idx;
    ptr[(((b_idx + 1) - 1) * 5)] = ((char )((int )' '));
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    trace_out:
    for (r = 0; r < 5; r++) {
      a_idx = a_idx_up + r;
      b_idx = b_idx_up + r;
      if (a_idx > 5) {
        a_idx = a_idx - 5;
      }
      if (b_idx > 5) {
        b_idx = b_idx - 5;
      }
      a_str_idx = ((int )SEQA[a_idx]);
      b_str_idx = ((int )SEQB[b_idx]);
      if (a_str_idx == b_str_idx) {
        alignedA[(((a_idx + 1) - 1) * 5)] = a_str_idx;
        alignedB[(((b_idx + 1) - 1) * 5)] = b_str_idx;
        ptr[(((b_idx + 1) - 1) * 5)] = ((char )((int )'|'));
      }
       else {
        alignedA[(((a_idx + 1) - 1) * 5)] = a_str_idx;
        alignedB[(((b_idx + 1) - 1) * 5)] = b_str_idx;
        ptr[(((b_idx + 1) - 1) * 5)] = ((char )((int )' '));
      }
    }
  }
}