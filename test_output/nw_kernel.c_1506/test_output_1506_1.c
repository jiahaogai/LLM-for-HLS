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
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * (-1);
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * (-1);
    ptr[b_idx * 5] = 0;
  }
/* Row = 0 */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_row0:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    a_str_idx = 0;
    b_str_idx = b_idx * 5;
    a_str_idx_p1 = 1;
    b_str_idx_p1 = (b_idx * 5) + 1;
    a = SEQA[0];
    b = SEQB[b_str_idx];
    score = 0;
    up_left = M[b_str_idx] + (-1);
    up = M[b_str_idx_p1] + (-1);
    left = M[b_str_idx] + a;
    max = (up_left > up) ? up_left : up;
    max = (left > max) ? left : max;
    M[b_str_idx] = max;
    ptr[b_str_idx] = 0;
    if (max == up_left) {
      if (up_left > left) {
        row = b_idx;
        col = b_idx - 1;
      }
      else {
        row = b_idx;
        col = b_idx + 1;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_col0:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx += 1;
      b_str_idx_p1 += 1;
      a = SEQA[a_str_idx];
      up_left = M[b_str_idx] + (-1);
      up = M[b_str_idx_p1] + (-1);
      left = M[b_str_idx] + a;
      max = (up_left > up) ? up_left : up;
      max = (left > max) ? left : max;
      M[b_str_idx] = max;
      ptr[b_str_idx] = (max == left) ? 3 : ((max == up_left) ? 2 : ((max == up) ? 1 : 0));
    }
  }
/* Row = 1 */
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_row1:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    a_str_idx = 0;
    b_str_idx = b_idx * 5;
    a_str_idx_p1 = 1;
    b_str_idx_p1 = (b_idx * 5) + 1;
    row_up = (b_idx - 1) * 5;
    a = SEQA[0];
    b = SEQB[b_str_idx];
    score = 0;
    up_left = M[b_str_idx] + (-1);
    up = M[b_str_idx_p1] + (-1);
    left = M[b_str_idx] + a;
    max = (up_left > up) ? up_left : up;
    max = (left > max) ? left : max;
    M[b_str_idx] = max;
    ptr[b_str_idx] = 0;
    if (max == up_left) {
      if (up_left > left) {
        row = b_idx - 1;
        col = b_idx;
      }
      else {
        row = b_idx + 1;
        col = b_idx;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_col1:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx += 1;
      b_str_idx_p1 += 1;
      row_up += 1;
      a = SEQA[a_str_idx];
      up_left = M[b_str_idx] + (-1);
      up = M[b_str_idx_p1] + (-1);
      left = M[b_str_idx] + a;
      max = (up_left > up) ? up_left : up;
      max = (left > max) ? left : max;
      M[b_str_idx] = max;
      ptr[b_str_idx] = (max == left) ? 3 : ((max == up_left) ? 2 : ((max == up) ? 1 : 0));
    }
  }
/* Row = 2 */
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  fill_row2:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    a_str_idx = 0;
    b_str_idx = b_idx * 5;
    a_str_idx_p1 = 1;
    b_str_idx_p1 = (b_idx * 5) + 1;
    row_up = (b_idx - 1) * 5;
    a = SEQA[0];
    b = SEQB[b_str_idx];
    score = 0;
    up_left = M[b_str_idx] + (-1);
    up = M[b_str_idx_p1] + (-1);
    left = M[b_str_idx] + a;
    max = (up_left > up) ? up_left : up;
    max = (left > max) ? left : max;
    M[b_str_idx] = max;
    ptr[b_str_idx] = 0;
    if (max == up_left) {
      if