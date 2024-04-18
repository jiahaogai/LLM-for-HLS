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
    alignedA[a_idx] = SEQA[a_idx];
    alignedA[a_idx + 128] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
    alignedB[b_idx + 128] = SEQB[b_idx];
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = ((int )SEQA[0]) * ((int )SEQB[0]) - 1;
        ptr[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = M[b_idx * 5] + ((int )SEQB[b_idx]) - ((int )SEQB[b_idx - 1]) * ((int )gap_penalty);
        ptr[b_idx * 5] = 3;
      }
      else if (b_idx == 0) {
        M[a_idx * 5] = M[a_idx * 5] + ((int )SEQA[a_idx]) - ((int )SEQA[a_idx - 1]) * ((int )gap_penalty);
        ptr[a_idx * 5] = 1;
      }
      else {
        up_left = M[(b_idx - 1) * 5 + (a_idx - 1)] + ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]) - ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]);
        up = M[(b_idx - 1) * 5 + a_idx] + ((int )gap_penalty) + ((int )SEQA[a_idx]) * ((int )gap_penalty) - ((int )SEQA[a_idx - 1]) * ((int )gap_penalty);
        left = M[b_idx * 5 + (a_idx - 1)] + ((int )gap_penalty) + ((int )SEQB[b_idx]) * ((int )gap_penalty) - ((int )SEQB[b_idx - 1]) * ((int )gap_penalty);
        if (up_left > ((int )0)) {
          max = up_left;
          row = b_idx - 1;
          a_str_idx = a_idx - 1;
          b_str_idx = b_idx - 1;
        }
        else {
          max = (up > left?up : left);
          row = (up > left?b_idx - 1 : b_idx);
          a_str_idx = (up > left?a_idx - 1 : a_idx);
          b_str_idx = (up > left?b_idx - 1 : b_idx - 1);
        }
        M[b_idx * 5 + a_idx] = max;
        if (max == left) {
          ptr[b_idx * 5 + a_idx] = 2;
        }
        else {
          if (max == up) {
            ptr[b_idx * 5 + a_idx] = 1;
          }
          else {
            ptr[b_idx * 5 + a_idx] = 3;
          }
        }
      }
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 4;
  b_str_idx = 4;
/*
    row = 4
    a_str_idx = 4
    b_str_idx = 4
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  trace_row_A:
  while (a_idx > 0) {
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    trace_col_A:
    for (b_idx = 4; b_idx > 0; b_idx--) {
      score = M[b_idx * 5 + a_idx];
      row_up = (b_idx - 1) * 5;
      if (ptr[row_up + a_idx] == 1) {
        b_idx = b_idx;
        a_idx = a_idx - 1;
      }
      else {
        b_idx = b_idx;
        a_idx = a_idx;
      }
    }
    a_idx = a_str_idx;
  }
  b_idx = 4;
  a_str_idx = 4;
  b_str_idx = 4;
/*
    a_str_idx = 4
    b_str_idx = 4
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace_row_B:
  while (b_idx > 0) {
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    trace_col_B:
    for (a_idx = 4; a_idx > 0; a_idx--) {
      score = M[b_idx * 5 + a_idx];
      row_up = (a_idx - 1) * 5;
      if (ptr[row_up + b_idx] == 2) {
        a_idx = a_idx;
        b_idx = b_idx - 1;
      }
      else {
        a_idx = a_idx;
        b_idx = b_idx;
      }
    }
    b_idx = b_str_idx;
  }
  a_idx = 0;
  b_idx = 0;
/*
    a_idx = 0
    b_idx = 0
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}