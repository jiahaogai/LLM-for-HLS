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
  int index;
  int last_row_idx;
  int last_a_idx;
  char a_char;
  char b_char;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 1; a_idx < 64 - 1; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 1; b_idx < 64 - 1; b_idx++) {
      score = ((int )SEQA[a_idx * 64 - 1]) * ((int )SEQB[b_idx * 64 - 1]) + ((int )SEQA[a_idx * 64]) * ((int )SEQB[b_idx * 64]) + ((int )SEQA[a_idx * 64 + 1]) * ((int )SEQB[b_idx * 64 + 1]) - Q1 * (((int )SEQA[a_idx * 64 - 1]) + ((int )SEQA[a_idx * 64]) + ((int )SEQA[a_idx * 64 + 1]) + ((int )SEQB[b_idx * 64 - 1]) + ((int )SEQB[b_idx * 64]) + ((int )SEQB[b_idx * 64 + 1]));
      up_left = M[(b_idx - 1) * 64 + (a_idx - 1)] + score;
      up = M[(b_idx - 1) * 64 + a_idx] - Q2;
      left = M[b_idx * 64 + (a_idx - 1)] - Q3;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * 64 + a_idx] = max;
      if (max == left) {
        ptr[b_idx * 64 + a_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_row_up:
      for (r = 1; r < 3; r++) {
        row_up = b_idx + (r - 1) * 1;
        index = b_idx * 64 + a_idx;
        row = b_idx * 64 + a_idx + r * 1;
        a_str_idx = (row_up + 1) * 64;
        b_str_idx = (index + 1) * 64;
        a_char = ((char )SEQA[a_str_idx - 1]);
        b_char = ((char )SEQB[b_str_idx - 1]);
        score = ((int )a_char) * ((int )b_char) - Q1 * (((int )a_char) + ((int )b_char));
        up = M[b_str_idx] - Q2 * (((int )a_char) + ((int )b_char));
        left = M[a_str_idx] - Q3 * (((int )a_char) + ((int )b_char));
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[b_str_idx] = max;
        if (max == left) {
          ptr[b_str_idx] = 2;
        }
        
#pragma ACCEL PIPELINE auto{off}
      }
    }
    last_row_idx = (a_idx + 1) * 64 - 1;
    last_a_idx = (a_idx + 1) * 64 - 1;
    a_char = ((char )SEQA[last_row_idx]);
    b_char = ((char )SEQB[last_a_idx]);
    score = ((int )a_char) * ((int )b_char) - Q1 * (((int )a_char) + ((int )b_char));
    up = M[last_a_idx] - Q2 * (((int )a_char) + ((int )b_char));
    left = M[last_row_idx] - Q3 * (((int )a_char) + ((int )b_char));
    max = (up > left?up : left);
    M[last_a_idx] = max;
    if (max == left) {
      ptr[last_a_idx] = 1;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    loop_col_up:
    for (b_idx = 64 - 2; b_idx > 1; b_idx--) {
      index = b_idx * 64;
      a_str_idx = (b_idx + 1) * 64;
      b_str_idx = (index + 1) * 64;
      a_char = ((char )SEQA[a_str_idx - 1]);
      b_char = ((char )SEQB[b_str_idx - 1]);
      score = ((int )a_char) * ((int )b_char) - Q1 * (((int )a_char) + ((int )b_char));
      up = M[b_str_idx] - Q2 * (((int )a_char) + ((int )b_char));
      left = M[a_str_idx] - Q3 * (((int )a_char) + ((int )b_char));
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx] = max;
      if (max == left) {
        ptr[b_str_idx] = 2;
      }
    }
  }
  last_row_idx = 64 * 64 - 1;
  last_a_idx = 64 * 64 - 1;
  a_char = ((char )SEQA[last_row_idx]);
  b_char = ((char