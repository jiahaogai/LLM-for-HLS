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
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = - 1;
  }
// Matrix multiplication
// Note that the code below sums up elements of the matrix M
// rather than multiplies two matrices
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 5;
    row_up = a_str_idx;
    row = a_str_idx + 5;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      left = M[b_str_idx];
      up = M[row_up + b_idx];
      score = ((SEQA[a_str_idx] == SEQB[b_str_idx]) ? 1LL : - 1LL);
      max = (up_left + score);
      up = (up + score);
      left = (left + score);
      max = (left > up ? (left > max ? left : max) : (up > max ? up : max));
      M[b_str_idx + a_idx] = max;
      if (max == left) {
        ptr[b_str_idx + a_idx] = row_up + b_idx;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_f_1:
      for (r = 0; r < 1; r++) {
      }
    }
    row_up = row;
  }
// Traceback
    b_idx = 4;
    a_idx = 4;
    score = M[b_idx * 5 + a_idx];
    b_str_idx = ((int )b_idx) * 5;
    a_str_idx = ((int )a_idx) * 5;
    alignedA[((int )(5 + 2)) + 0] = '_';
    alignedB[((int )(5 + 2)) + 0] = '_';
    alignedA[((int )(5 + 2)) + 1] = '_';
    alignedB[((int )(5 + 2)) + 1] = '_';
    alignedA[((int )(5 + 2)) + 2] = '_';
    alignedB[((int )(5 + 2)) + 2] = '_';
    alignedA[((int )(5 + 2)) + 3] = '_';
    alignedB[((int )(5 + 2)) + 3] = '_';
    alignedA[((int )(5 + 2)) + 4] = '_';
    alignedB[((int )(5 + 2)) + 4] = '_';
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_tb1:
  while (a_idx > 0 || b_idx > 0) {
    if (b_idx == 0) {
      a_idx = ptr[a_str_idx];
      score = M[a_str_idx + a_idx];
      b_str_idx = ((int )b_idx) * 5;
      a_str_idx = ((int )a_idx) * 5;
      alignedA[((int )(5 + 2)) + 0] = '_';
      alignedB[((int )(5 + 2)) + 0] = '_';
      alignedA[((int )(5 + 2)) + 1] = '_';
      alignedB[((int )(5 + 2)) + 1] = '_';
      alignedA[((int )(5 + 2)) + 2] = '_';
      alignedB[((int )(5 + 2)) + 2] = '_';
      alignedA[((int )(5 + 2)) + 3] = '_';
      alignedB[((int )(5 + 2)) + 3] = '_';
      alignedA[((int )(5 + 2)) + 4] = '_';
      alignedB[((int )(5 + 2)) + 4] = '_';
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    loop_tb2:
    while (b_str_idx != a_str_idx) {
      if (a_str_idx == ((int )(5 + 2)) * 5) {
        b_idx = ptr[b_str_idx];
        score = M[b_str_idx + b_idx];
        b_str_idx = ((int )b_idx) * 5;
        a_str_idx = ((int )a_idx) * 5;
        alignedA[((int )(5 + 2)) + 0] = '_';
        alignedB[((int )(5 + 2)) + 0] = '_';
        alignedA[((int )(5 + 2)) + 1] = '_';
        alignedB[((int )(5 + 2)) + 1] = '_';
        alignedA[((int )(5 + 2)) + 2] = '_';
        alignedB[((int )(5 + 2)) + 2] = '_';
        alignedA[((int )(5 + 2)) + 3] = '_';
        alignedB[((int )(5 + 2)) + 3] = '_';
        alignedA[((int )(5 + 2)) + 4] = '_';
        alignedB[((int )(5 + 2)) + 4] = '_';
      }
      else {
        if (b_str_idx == ((int )(5 + 2)) * 5) {
          a_idx = ptr[a_str_idx];
          score = M[a_str_idx + a_idx];
          b_str_idx = ((int )b_idx) * 5;
          a_str_idx = ((int )a_idx)