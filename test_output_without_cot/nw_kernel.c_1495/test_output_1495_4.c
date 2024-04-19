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
  int a_col_idx;
  int b_col_idx;
  int a_row_idx;
  int b_row_idx;
  int a_row_idx_p1;
  int b_row_idx_p1;
  int a_col_idx_p1;
  int b_col_idx_p1;
  char a_char;
  char b_char;
  int A_idx;
  int B_idx;
  int C_idx;
  int D_idx;
  int E_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 1; a_idx <= 128; a_idx++) {
    M[a_idx] = a_idx - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 1; b_idx <= 128; b_idx++) {
    M[b_idx * 128] = b_idx - 1;
    ptr[b_idx * 128] = 0;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 1; b_idx < 128 - 1; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 128 - 1; a_idx++) {
      a_col_idx = 128 * a_idx;
      b_col_idx = 128 * b_idx;
      a_row_idx = a_col_idx + a_idx;
      b_row_idx = b_col_idx + b_idx;
      a_row_idx_p1 = a_row_idx + 1;
      b_row_idx_p1 = b_row_idx + 1;
      a_col_idx_p1 = a_col_idx + 1;
      b_col_idx_p1 = b_col_idx + 1;
      A_idx = a_row_idx_p1;
      B_idx = b_row_idx_p1;
      C_idx = b_row_idx;
      D_idx = a_row_idx;
      E_idx = a_col_idx;
      up_left = M[A_idx] + ((int )SEQA[a_idx] == (int )SEQB[b_idx]?1:-1);
      up = M[B_idx] + ((int )SEQA[a_idx] == (int )SEQB[b_col_idx_p1]?1:-1);
      left = M[D_idx] + ((int )SEQA[b_idx] == (int )SEQB[a_idx]?1:-1);
      max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
      score = ((int )SEQA[a_idx] == (int )SEQB[b_idx]?1:-1);
      M[A_idx] = max;
      if (max == left) {
        ptr[A_idx] = (char )6;
      }
      
      if (max == up) {
        ptr[A_idx] = (char )5;
      }
      
      if (max == up_left + score) {
        ptr[A_idx] = (char )4;
      }
      
      if (max == left + score) {
        ptr[A_idx] = (char )2;
      }
      
      if (max == up + score) {
        ptr[A_idx] = (char )1;
      }
      
      if (max == 0) {
        ptr[A_idx] = (char )0;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 128;
  b_idx = 128;
  a_col_idx = 128 * a_idx;
  b_col_idx = 128 * b_idx;
  a_row_idx = a_col_idx + a_idx;
  b_row_idx = b_col_idx + b_idx;
  a_row_idx_p1 = a_row_idx + 1;
  b_row_idx_p1 = b_row_idx + 1;
  a_col_idx_p1 = a_col_idx + 1;
  b_col_idx_p1 = b_col_idx + 1;
  A_idx = a_row_idx_p1;
  B_idx = b_row_idx_p1;
  C_idx = b_row_idx;
  D_idx = a_row_idx;
  E_idx = a_col_idx;
  r = 0;
  trace:
  while (1) {
    a_char = SEQA[a_idx];
    b_char = SEQB[b_idx];
    if (a_char == b_char) {
      score = 1;
    }
    
    if (a_char != b_char) {
      score = - 1;
    }
    switch (ptr[A_idx]) {
      case 0:
        a_idx = E_idx;
        b_idx = D_idx;
        a_col_idx = 128 * a_idx;
        b_col_idx = 128 * b_idx;
        a_row_idx = a_col_idx + a_idx;
        b_row_idx = b_col_idx + b_idx;
        a_row_idx_p1 = a_row_idx + 1;
        b_row_idx_p1 = b_row_idx + 1;
        a_col_idx_p1 = a_col_idx + 1;
        b_col_idx_p1 = b_col_idx + 1;
        A_idx = a_row_idx_p1;
        B_idx = b_row_idx_p1;
        C_idx = b_row_idx;
        D_idx = a_row_idx;
        E_idx = a_col_idx;
        break;
      case 1:
        alignedA[r++] = a_char;
        alignedB[r++] = b_char;
        a_idx = E_idx;
        b_idx = D_idx;
        a_col_idx = 128 * a_idx;
        b_col_idx = 128 * b_idx;
        a_row_idx = a_col_idx + a_idx;
        b_row_idx = b_col_idx + b_idx;
        a_row_idx_p1 = a_row_idx + 1;
        b_row_idx_p1 = b_row_