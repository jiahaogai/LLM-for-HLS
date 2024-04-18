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
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a_char;
  char b_char;
  int idx;
  int ptr_idx;
  int m_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{128}
  fill_out:
  for (b_idx = 5; b_idx < 128 + 5; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out_row:
  for (a_idx = 5; a_idx < 128 + 5; a_idx++) {
    a_str_idx = (a_idx * 5);
    a_str_idx_p1 = (a_str_idx + 5);
    b_str_idx = a_idx;
    b_str_idx_p1 = b_str_idx + 5;
    score = ((int )alignedA[a_str_idx] - (int )alignedB[b_str_idx]);
    up_left = M[b_str_idx * 128 + a_str_idx] + score;
    up = M[(b_str_idx - 1) * 128 + a_str_idx] + ((int )alignedA[a_str_idx_p1] - (int )alignedB[b_str_idx_p1]);
    left = M[b_str_idx * 128 + a_str_idx_p1] + score;
    max = up_left;
    if (up > max) {
      max = up;
    }
    if (left > max) {
      max = left;
    }
    M[b_str_idx * 128 + a_str_idx] = max;
    ptr_idx = b_str_idx * 128 + a_str_idx;
    if (left == max) {
      ptr[ptr_idx] = 2;
      b_idx = b_str_idx_p1;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_out_col:
    for (b_idx = b_str_idx_p1; b_idx < 128 + 5; b_idx++) {
      b_str_idx = b_idx;
      b_str_idx_p1 = b_str_idx + 5;
      a_str_idx = (a_idx * 5);
      a_str_idx_p1 = (a_str_idx + 5);
      score = ((int )alignedA[a_str_idx] - (int )alignedB[b_str_idx]);
      up_left = M[b_str_idx * 128 + a_str_idx] + score;
      up = M[(b_str_idx - 1) * 128 + a_str_idx] + ((int )alignedA[a_str_idx_p1] - (int )alignedB[b_str_idx_p1]);
      left = M[b_str_idx * 128 + a_str_idx_p1] + score;
      max = up_left;
      if (up > max) {
        max = up;
      }
      if (left > max) {
        max = left;
      }
      M[b_str_idx * 128 + a_str_idx] = max;
      ptr_idx = b_str_idx * 128 + a_str_idx;
      if (left == max) {
        ptr[ptr_idx] = 2;
        row = b_str_idx_p1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      trace_row:
      for (row = b_str_idx_p1; row < 128 + 5; row++) {
        row_up = (row - 1);
        a_str_idx = (row * 5);
        a_str_idx_p1 = (a_str_idx + 5);
        b_str_idx = row_up * 5;
        b_str_idx_p1 = b_str_idx + 5;
        score = ((int )alignedA[a_str_idx] - (int )alignedB[b_str_idx]);
        up_left = M[b_str_idx * 128 + a_str_idx] + score;
        up = M[row_up * 128 + a_str_idx] + ((int )alignedA[a_str_idx_p1] - (int )alignedB[b_str_idx_p1]);
        left = M[b_str_idx * 128 + a_str_idx_p1] + score;
        max = up_left;
        if (up > max) {
          max = up;
        }
        if (left > max) {
          max = left;
        }
        m_idx = b_str_idx * 128 + a_str_idx;
        idx = b_str_idx_p1 * 128 + a_str_idx_p1;
        if (max == left) {
          a_char = alignedA[a_str_idx_p1];
          alignedA[a_str_idx_p1] = alignedA[idx];
          alignedA[idx] = a_char;
          b_char = alignedB[idx];
          alignedB[idx] = alignedB[m_idx];
          alignedB[m_idx] = b_char;
          ptr[idx] = 3;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L5}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
        trace_col:
        for (r = 0; r < 5; r++) {
          a_str_idx = (row * 5) + r;
          b_str_idx = (row_up * 5) + r;
          if (ptr[b_str_idx * 128 + a_str_idx] == 2)