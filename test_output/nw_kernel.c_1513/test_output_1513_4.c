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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    alignedA[a_idx + 128] = '_';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '_';
    alignedB[b_idx + 128] = SEQB[b_idx];
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_str_idx = a_idx * 16;
      b_str_idx = b_idx * 16;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      score = ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
      up_left = M[a_idx * 5 + b_idx] + score;
      up = M[a_idx * 5 + b_idx + 1] + ((int )'A' - (int )'T');
      left = M[(a_idx + 1) * 5 + b_idx] + ((int )'A' - (int )'G');
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_idx * 5 + b_idx] = max;
      if (max == left) {
        ptr[a_idx * 5 + b_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      diag:
      for (r = 1; r < 16; r++) {
        a_str_idx = a_str_idx_p1 + 1;
        b_str_idx = b_str_idx_p1 + 1;
        a_str_idx_p1 = a_str_idx + 1;
        b_str_idx_p1 = b_str_idx + 1;
        score = M[a_idx * 5 + b_idx] + ((int )SEQA[a_str_idx] - (int )SEQB[b_str_idx]);
        up = M[a_idx * 5 + b_idx + 1] + ((int )'A' - (int )'T');
        left = M[(a_idx + 1) * 5 + b_idx] + ((int )'A' - (int )'G');
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[a_idx * 5 + b_idx] = max;
        if (max == left) {
          ptr[a_idx * 5 + b_idx] = 2;
        }
        else {
          if (max == up) {
            ptr[a_idx * 5 + b_idx] = 1;
          }
          else {
            ptr[a_idx * 5 + b_idx] = 0;
          }
        }
        up_left = up;
      }
    }
  }
// TraceBack
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace:
  for (row = 4; row >= 0; row--) {
    row_up = (row + 1) * 5;
    a_idx = row * 16;
    b_idx = (5 - 1) * 16;
    a_str_idx = a_idx + 15;
    b_str_idx = b_idx + 15;
    a_str_idx_p1 = a_str_idx + 1;
    b_str_idx_p1 = b_str_idx + 1;
    a_char = SEQA[a_str_idx];
    b_char = SEQB[b_str_idx];
    score = ((int )a_char) * ((int )b_char);
    up_left = M[row_up + (5 - 1)] + score;
    up = M[row_up + (5 - 1) + 1] + ((int )'A' - (int )'T');
    left = M[row_up + 15] + ((int )'A' - (int )'G');
    max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
    if (max == left) {
      b_idx--;
      a_char = SEQA[a_str_idx];
      alignedA[a_idx] = a_char;
      alignedB[b_idx] = '_';
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    diag:
    for (r = 15; r > 0; r--) {
      a_str_idx = a_str_idx_p1 - 1;
      b_str_idx = b_str_idx_p1 - 1;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      score = M[row_up + b_idx] + ((int )SEQA[a_str_idx] - (int )SEQB[b_str_idx]);
      up = M[row_up + b_idx + 1] + ((int )'A' - (int )'T');
      left = M[row_up + a_idx] + ((int )'A' - (int )'G');
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row_up + b_idx] = max;
      if (max == left) {
        b_idx--;
        a_char = SEQA[a_str_idx];
        alignedA[a_idx] = a_char