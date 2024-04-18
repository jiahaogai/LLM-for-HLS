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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_row:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    a_str_idx = 64 * a_idx;
    a_str_idx_p1 = a_str_idx + 1;
    row_up = a_str_idx_p1 - 1;
    loop_col:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      b_str_idx = 64 * b_idx;
      b_str_idx_p1 = b_str_idx + 1;
      up_left = M[row_up + b_str_idx] + ((int )SEQA[a_str_idx_p1]) * - 1 * ((int )SEQB[b_str_idx_p1]);
      up = M[row_up + b_str_idx_p1] + ((int )SEQA[a_str_idx_p1]) * - 1;
      left = M[a_str_idx + b_str_idx] + ((int )SEQB[b_str_idx_p1]) * - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_str_idx + b_str_idx] = max;
      if (max == left) {
        ptr[a_str_idx + b_str_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[a_str_idx + b_str_idx] = 1;
        }
         else {
          ptr[a_str_idx + b_str_idx] = 0;
        }
      }
    }
  }
// TraceBack
  a_idx = 63;
  b_idx = 63;
  a_str_idx = a_idx * 64;
  b_str_idx = b_idx * 64;
  score = M[a_str_idx + b_str_idx];
  alignedA[0] = '\0';
  alignedB[0] = '\0';
  r = 0;
/*
    row_up = a_idx*64 - 1;
    col_up = b_idx*64 - 1;
    while (a_idx>0||b_idx>0) {
      if (ptr[a_str_idx + b_str_idx] == 0) {
        a_idx--;
        b_idx--;
        a_str_idx = a_idx*64;
        b_str_idx = b_idx*64;
      }
      else if (ptr[a_str_idx + b_str_idx] == 1) {
        a_idx--;
        b_str_idx = b_str_idx_p1;
      }
      else if (ptr[a_str_idx + b_str_idx] == 2) {
        a_str_idx = a_str_idx_p1;
        b_idx--;
        b_str_idx = b_idx*64;
      }
      row = a_idx*64;
      up_left = row_up + b_str_idx;
      up = row_up + b_str_idx_p1;
      left = a_str_idx + b_str_idx;
      score = M[a_str_idx + b_str_idx];
      if (up_left == left) {
        a = SEQA[a_str_idx_p1];
        b = SEQB[b_str_idx_p1];
        r++;
      }
      else if (up_left > up) {
        if (up_left > left) {
          a = SEQA[a_str_idx_p1];
          b = SEQB[b_str_idx];
          r++;
        }
         else {
          a = SEQA[a_str_idx];
          b = SEQB[b_str_idx_p1];
          r++;
        }
      }
      else if (up > left) {
        a = SEQA[a_str_idx_p1];
        b = SEQB[b_str_idx];
        r++;
      }
      else {
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx_p1];
        r++;
      }
      alignedA[r] = a;
      alignedB[r] = b;
      row_up = a_str_idx;
    }
*/
}