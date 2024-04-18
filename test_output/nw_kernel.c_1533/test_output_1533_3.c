c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    int _in_init_row = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    init_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0) {
        if (b_idx == 0) {
          M[0] = 0;
          ptr[0] = 0;
        }
        else {
          M[b_idx * 5] = ((int )SEQA[0]) * ((int )SEQB[b_idx * 5]) + M[(b_idx - 1) * 5];
          ptr[b_idx * 5] = 2;
        }
      }
      else {
        if (b_idx == 0) {
          M[a_idx * 5] = ((int )SEQA[a_idx * 5]) * ((int )SEQB[0]) + M[(a_idx - 1) * 5];
          ptr[a_idx * 5] = 1;
        }
        else {
          up_left = M[(a_idx - 1) * 5] + ((int )SEQA[a_idx * 5]) * ((int )SEQB[b_idx * 5]);
          up = M[a_idx * 5] + ((int )SEQA[a_idx * 5]) * ((int )SEQB[b_idx]);
          left = M[b_idx * 5] + ((int )SEQA[a_idx * 5]) * ((int )SEQB[b_idx * 5]);
          M[a_idx * 5 + b_idx] = (up_left > ((int )0) ? ((up > left ? up : left)) : ((left > ((int )0) ? left : up_left)));
          if (M[a_idx * 5 + b_idx] == up_left) {
            ptr[a_idx * 5 + b_idx] = 3;
          }
          else {
            if (M[a_idx * 5 + b_idx] == up) {
              ptr[a_idx * 5 + b_idx] = 1;
            }
            else {
              ptr[a_idx * 5 + b_idx] = 2;
            }
          }
        }
      }
    }
  }
// Matrix strides
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    int _in_fill_out = 0;
    a_str_idx = a_idx * 5;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_out_row:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_out_col:
      for (r = 0; r < 5; r++) {
        if (a_idx == r) {
          alignedA[((b_idx + 1) * 5) - 1] = '-';
        }
        else {
          if (b_idx == r) {
            alignedA[((a_idx + 1) * 5) - 1] = '-';
          }
          else {
            alignedA[((b_idx + 1) * 5) - 1] = SEQA[a_str_idx + r];
          }
        }
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      fill_in_col:
      for (r = 0; r < 5; r++) {
        if (a_idx == r) {
          alignedB[((b_idx + 1) * 5) - 1] = '-';
        }
        else {
          if (b_idx == r) {
            alignedB[((a_idx + 1) * 5) - 1] = '-';
          }
          else {
            alignedB[((b_idx + 1) * 5) - 1] = SEQB[b_str_idx + r];
          }
        }
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      trace_row:
      for (row = 5 - 1; row >= 0; row--) {
        row_up = (row + 1) * 5;
        if (ptr[a_str_idx + b_str_idx + row] == 0) {
          max = M[a_str_idx + b_str_idx + row] + M[a_str_idx + b_str_idx + row + 1];
          if (M[a_str_idx + b_str_idx + row + 1] == max) {
            ptr[a_str_idx + b_str_idx + row] = 6;
          }
          else {
            ptr[a_str_idx + b_str_idx + row] = 5;
          }
        }
        else {
          if (ptr[a_str_idx + b_str_idx + row] == 1) {
            max = M[a_str_idx + b_str_idx + row] + M[a_str_idx + b_str_idx + row + 1];
            if (M[a_str_idx + b_str_idx + row + 1] == max) {
              ptr[a_str_idx + b_str_idx + row] = 6;
            }
            else {
              ptr[a_str_idx + b_str_idx + row] = 1;
            }
          }
          else {
            if (ptr[a_str_idx + b_str_idx + row] == 2) {
              max = M[a_str_idx + b_str_idx + row] + M[a_str_idx + b_str_idx + row - 1];
              if (M[a_str_idx + b_str_idx + row - 1] == max) {
                ptr[a_str_idx + b_str_idx + row] = 7;
              }
              else {
                ptr[a_str_idx + b_str_idx + row] = 2;
              }
            }
            else {
              if (ptr[a_str_idx + b_str_idx + row] == 3) {
                max = M[a_str_idx + b_str_idx + row] + M[a_str_idx + b_str_idx + row - 1] + M[a_str_idx + b_str_idx + row