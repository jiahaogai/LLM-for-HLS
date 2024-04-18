#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
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
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      a_str_idx = (b_idx - 1) * 128;
      b_str_idx = (a_idx - 1) * 128;
      if (((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      a_str_idx_p1 = (b_idx - 0) * 128;
      b_str_idx_p1 = (a_idx - 0) * 128;
      up_left = M[a_str_idx_p1 + (b_str_idx_p1)] + score;
      a_str_idx_p1 = (b_idx - 0) * 128;
      b_str_idx_p1 = (a_idx - 1) * 128;
      up = M[a_str_idx_p1 + b_str_idx_p1] + - 1;
      b_str_idx_p1 = (a_idx - 0) * 128;
      left = M[a_str_idx_p1 + b_str_idx_p1] + - 1;
      u = up_left;
      l = left;
      if (up > u) {
        u = up;
      }
      if (l > u) {
        u = l;
      }
      max = u;
      row = a_idx;
      row_up = a_idx - 1;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      trace_last:
      for (r = b_idx; r > 0; r--) {
        if (row_up == r - 1) {
          b = '_';
        }
         else {
          b_str_idx = (r - 1) * 128;
          b = SEQB[b_str_idx];
        }
        b_str_idx = r * 128;
        a = SEQA[b_str_idx];
        a_str_idx = r * 128;
        M[a_str_idx + b_idx] = max;
        if (max == ((left + score) - 1)) {
          max = left;
          row = row_up;
          b_str_idx_p1 = b_str_idx + 1;
          a_str_idx_p1 = a_str_idx + 1;
          left = M[a_str_idx_p1 + b_str_idx_p1] + - 1;
        }
         else {
          if (max == ((up + score) - 1)) {
            max = up;
            row = row_up;
            b_str_idx_p1 = b_str_idx + 1;
            a_str_idx_p1 = a_str_idx;
            up = M[a_str_idx_p1 + b_str_idx_p1] + - 1;
          }
           else {
            max = up_left;
            row = row_up;
            b_str_idx_p1 = b_str_idx;
            a_str_idx_p1 = a_str_idx;
            up_left = M[a_str_idx_p1 + b_str_idx_p1] + ((int )a == ((int )b)) ? 1 : - 1;
          }
        }
      }
    }
  }
// Traceback
  a_idx = 128;
  b_idx = 128;
  a_str_idx = ((b_idx - 1) * 128);
  b_str_idx = ((a_idx - 1) * 128);
  ptr[0] = - 1;
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    if (a_idx == 0) {
      b_str_idx = b_str_idx + 1;
      b = SEQB[b_str_idx];
      a = '_';
    }
     else {
      if (b_idx == 0) {
        a_str_idx = a_str_idx + 1;
        a = SEQA[a_str_idx];
        b = '_';
      }
       else {
        a_str_idx = a_str_idx + 1;
        b_str_idx = b_str_idx + 1;
        a_str_idx_p1 = a_str_idx + 1;
        b_str_idx_p1 = b_str_idx + 1;
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx];
        if (M[a_str_idx + b_str_idx] == ((M[a_str_idx + b_str_idx_p1] + - 1) - 1)) {
          a_str_idx = a_str_idx_p1;
          b_str_idx = b_str_idx_p1;
        }
         else {
          if (M[a_str_idx + b_str_idx] == ((M[a_str_idx_p1 + b_str_idx] + - 1) - 1)) {
            a_str_idx = a_str_idx_p1;
            b_str_idx = b_str_idx_p1;
          }
           else {
            a_str_idx = a_str_idx_p1;
            b_str_idx = b_str_idx_p1;
          }
        }
      }
    }
    alignedA[a_idx]