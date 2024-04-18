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
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      score = ((int )SEQA[a_idx * 64 - 1]) - ((int )SEQB[b_idx * 64 - 1]);
      row_up = (a_idx - 1) * 64;
      up_left = row_up + (b_idx - 1);
      up = row_up + b_idx;
      left = up_left;
      max = M[up_left] + score;
      if (M[up] > max) {
        max = M[up];
        ptr[b_idx] = (char )1;
      }
      else {
        ptr[b_idx] = (char )0;
      }
      if (M[left] > max) {
        max = M[left];
        ptr[b_idx] = (char )2;
      }
      M[b_idx] = max;
    }
  }
// TraceBack
  a_idx = 63;
  b_idx = 63;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row_up = (a_idx - 1) * 64;
    r = row_up + b_idx;
    alignedA[a_str_idx] = '\0';
    alignedB[b_str_idx] = '\0';
*/
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    row_up = (a_idx - 1) * 64;
    r = row_up + b_idx;
    if (((int )ptr[r]) == 0) {
      a_idx = a_idx - 1;
      b_idx = b_idx - 1;
      a_str_idx = a_str_idx + 1;
      b_str_idx = b_str_idx + 1;
      alignedA[a_str_idx] = SEQA[a_idx * 64 - 1];
      alignedB[b_str_idx] = SEQB[b_idx * 64 - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    if (((int )ptr[r]) == 1) {
      a_idx = a_idx - 1;
      alignedA[a_str_idx] = SEQA[a_idx * 64 - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    if (((int )ptr[r]) == 2) {
      b_idx = b_idx - 1;
      alignedB[b_str_idx] = SEQB[b_idx * 64 - 1];
    }
  }
}