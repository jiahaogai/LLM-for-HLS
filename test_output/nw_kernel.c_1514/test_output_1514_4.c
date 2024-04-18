#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],char ptr[1664])
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
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
  }
// Matrix multiplication: M = A*B
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (a_idx = 1; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (b_idx = 1; b_idx < 5; b_idx++) {
      a_idx_up = a_idx - 1;
      b_idx_up = b_idx - 1;
      a_str_idx = a_idx_up * 5;
      b_str_idx = b_idx_up * 5;
      up_left = M[a_str_idx + b_idx_up] + ((int )SEQA[a_idx_up]) * - 1 * ((int )SEQB[b_idx_up]);
      up = M[a_str_idx + b_idx] + ((int )SEQA[a_idx_up]) * - 1;
      left = M[b_str_idx + a_idx] + ((int )SEQB[b_idx_up]) * - 1;
      max = (up_left > ((int )0 ? up : ((int )0))) ? (up_left > left ? a_idx_up * - 1 : b_idx_up * - 1) : (up > left ? a_idx * - 1 : b_idx * - 1);
      score = M[a_str_idx + b_idx] + ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]);
      M[a_str_idx + b_idx] = score;
      ptr[a_str_idx + b_idx] = max;
    }
  }
// TraceBack
  row = 4;
  b_idx = 4;
  a_idx = 4;
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx * 5;
  alignedA[0] = '\0';
  alignedB[0] = '\0';
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (row != 0 || b_idx != 0) {
    if (b_idx == 0) {
      a_idx = row;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = a_idx * - 1;
    }
    
    if (row == 0) {
      b_idx = b_idx;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = b_idx * - 1;
    }
    
    if (M[a_str_idx + b_idx] > ((int )0 ? M[a_str_idx + b_idx - 1] : ((int )0)) + ((int )SEQA[a_idx - 1]) * - 1) {
      a_idx = a_idx;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = a_idx * - 1;
    }
    
    if (M[a_str_idx + b_idx] > ((int )0 ? M[a_str_idx + b_idx - 5] : ((int )0)) + ((int )SEQA[a_idx - 5]) * - 1) {
      a_idx = a_idx - 5;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = a_idx * - 1;
    }
    
    if (M[a_str_idx + b_idx] > ((int )0 ? M[a_str_idx + b_idx + 1] : ((int )0)) + ((int )SEQA[a_idx + 1]) * - 1) {
      a_idx = a_idx + 1;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = a_idx * - 1;
    }
    
    if (M[a_str_idx + b_idx] > ((int )0 ? M[a_str_idx + b_idx + 5] : ((int )0)) + ((int )SEQA[a_idx + 5]) * - 1) {
      a_idx = a_idx + 5;
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = a_idx * - 1;
    }
    
    if (max >= ((int )0 ? b_idx : ((int )0))) {
      a_idx = a_idx + ((int )ptr[a_str_idx + b_idx]);
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = b_idx * - 1;
    }
    
    if (max < ((int )0 ? b_idx : ((int )0))) {
      b_idx = b_idx + ((int )ptr[a_str_idx + b_idx]);
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = M[a_str_idx + b_idx];
      max = b_idx * - 1;
    }
    row_up = a_idx;
    r = b_idx;
    alignedA[0] = '\0';
    alignedB[0] = '\0';
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    trace_a:
    for (a_idx = row_up; a_idx < 5; a_idx++) {
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx *