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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    int _in_init_row = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    init_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0) {
        if (b_idx == 0) {
          score = 0;
        }
        else {
          score = 0 - 1 * B[b_idx];
        }
      }
      else {
        if (b_idx == 0) {
          score = 0 - 1 * A[a_idx];
        }
        else {
          score = 0 - 1 * B[b_idx] - 1 * A[a_idx];
        }
      }
      M[b_idx * 5 + a_idx] = score;
      ptr[b_idx * 5 + a_idx] = 0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 16;
    alignedA[a_str_idx + 0] = '-';
    alignedA[a_str_idx + 1] = '-';
    alignedA[a_str_idx + 2] = '-';
    alignedA[a_str_idx + 3] = '-';
    alignedA[a_str_idx + 4] = '-';
    alignedA[a_str_idx + 5] = '_';
    alignedA[a_str_idx + 6] = '_';
    alignedA[a_str_idx + 7] = '_';
    alignedA[a_str_idx + 8] = '_';
    alignedA[a_str_idx + 9] = '_';
    alignedA[a_str_idx + 10] = '_';
    alignedA[a_str_idx + 11] = '_';
    alignedA[a_str_idx + 12] = '_';
    alignedA[a_str_idx + 13] = '_';
    alignedA[a_str_idx + 14] = '_';
    alignedA[a_str_idx + 15] = '_';
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  col_init:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = b_idx * 16;
    alignedB[b_str_idx + 0] = '_';
    alignedB[b_str_idx + 1] = '_';
    alignedB[b_str_idx + 2] = '_';
    alignedB[b_str_idx + 3] = '_';
    alignedB[b_str_idx + 4] = '_';
    alignedB[b_str_idx + 5] = A[0];
    alignedB[b_str_idx + 6] = '-';
    alignedB[b_str_idx + 7] = '-';
    alignedB[b_str_idx + 8] = '-';
    alignedB[b_str_idx + 9] = '-';
    alignedB[b_str_idx + 10] = '-';
    alignedB[b_str_idx + 11] = '-';
    alignedB[b_str_idx + 12] = '-';
    alignedB[b_str_idx + 13] = '-';
    alignedB[b_str_idx + 14] = '-';
    alignedB[b_str_idx + 15] = '-';
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 16;
    row_up = (5 + 1) * 5;
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 16;
      up_left = M[b_idx * 5 + (a_idx + 0)];
      up = M[b_idx * 5 + (a_idx + 1)];
      left = M[(a_idx + 0) * 5 + a_idx + 0];
      if (a_idx == 0 && b_idx == 0) {
        max = up_left;
        row = 0;
        col = 0;
      }
      else if (a_idx == 0) {
        max = up_left + left;
        row = 0;
        col = 1;
      }
      else if (b_idx == 0) {
        max = up_left + up;
        row = 1;
        col = 0;
      }
      else {
        up_old = M[b_idx * 5 + (a_idx + 0)];
        left_old = M[(a_idx + 0) * 5 + a_idx + 0];
        max = (up_left + left) > ((up_old + up) > (left_old + left) ? (up_left + left) : ((up_old + up) > (left_old + left) ? (up_old + up) : (left_old + left)));
        row_up = (5 + 1) * b_idx;
        row = row_up + a_idx + 1;
        col = a_idx + 1;
      }
      M[b_idx * 5 + a_idx + 0] = max;
      if (max == left) {
        ptr[b_idx * 5 + a_idx + 0] = 2;
        alignedA[a_str_idx + 16] = '-';
      }
      else {
        if (max == up) {
          ptr[b_idx * 5 + a_idx + 0] = 1;
          alignedA[a_str_idx + 16] = A[b_idx * 16];
        }
        else {
          ptr[b_idx * 5 + a_idx + 0] = 0;
          alignedA[a_str_idx + 16] = A[b_idx * 16];
        }
      }
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR