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
  int a_col_idx;
  int b_idx;
  int b_col_idx;
  int a_row_idx;
  int a_row_col_idx;
  int b_row_idx;
  int b_row_col_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      up_left = M[(b_idx - 1) * (128 + 1) + (a_idx - 1)] + score;
      up = M[(b_idx - 1) * (128 + 1) + a_idx] - 1;
      left = M[b_idx * (128 + 1) + (a_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = 1;
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = 0;
        }
      }
    }
  }
// Traceback
  row = 128;
  col = 128;
  a_row_idx = 0;
  b_row_idx = 0;
  alignedA[(((128 + 1) + 1) - 1)] = '_';
  alignedB[(((128 + 1) + 1) - 1)] = '_';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace:
  while (1) {
    a_col_idx = 0;
    b_col_idx = 0;
    a_row_col_idx = ((128 + 1) * a_row_idx) + a_col_idx;
    b_row_col_idx = ((128 + 1) * b_row_idx) + b_col_idx;
    if (((int )SEQA[a_row_idx]) == ((int )SEQB[b_row_idx])) {
      alignedA[(((128 + 1) + 1) * a_row_idx) - 1] = SEQA[a_row_idx];
      alignedB[(((128 + 1) + 1) * b_row_idx) - 1] = SEQB[b_row_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    trace_row:
    while (a_row_col_idx < a_row_idx) {
      a_col_idx = a_row_col_idx;
      b_col_idx = b_row_col_idx;
      a_row_col_idx = ((128 + 1) * a_row_idx) + a_col_idx;
      b_row_col_idx = ((128 + 1) * b_row_idx) + b_col_idx;
      alignedA[(((128 + 1) + 1) * a_row_idx) + a_col_idx] = alignedA[(((128 + 1) + 1) * a_row_idx) - 1];
      alignedB[(((128 + 1) + 1) * b_row_idx) + b_col_idx] = alignedB[(((128 + 1) + 1) * b_row_idx) - 1];
    }
    trace_col:
    while (b_row_col_idx < b_row_idx) {
      a_col_idx = a_row_col_idx;
      b_col_idx = b_row_col_idx;
      a_row_col_idx = ((128 + 1) * a_row_idx) + a_col_idx;
      b_row_col_idx = ((128 + 1) * b_row_idx) + b_col_idx;
      alignedA[(((128 + 1) + 1) * a_row_idx) + a_col_idx] = alignedA[(((128 + 1) + 1) * a_row_idx) - 1];
      alignedB[(((128 + 1) + 1) * b_row_idx) + b_col_idx] = alignedB[(((128 + 1) + 1) * b_row_idx) - 1];
    }
    if (ptr[b_row_col_idx * (128 + 1) + a_row_col_idx] == 0) {
      a_row_idx--;
      b_row_idx--;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    if (ptr[b_row_col_idx * (128 + 1) + a_row_col_idx] == 1) {
      a_row_idx--;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    if (ptr[b_row_col_idx * (128 + 1) + a_row_col_idx] == 2) {