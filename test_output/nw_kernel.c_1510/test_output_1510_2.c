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
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    b_str_idx = (b_idx * 1) + 1;
    row_up = (b_idx - 1) * 64;
    row = b_idx * 64;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_row:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      a_str_idx = (a_idx * 1) + 1;
      up_left = M[row_up + (a_idx - 1)];
      up = M[row_up + a_idx];
      left = M[row + (a_idx - 1)];
      if (((int )SEQA[a_str_idx - 1]) == ((int )SEQB[b_str_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      max = (up_left + score);
      if (up > max) {
        max = up;
      }
      if (left > max) {
        max = left;
      }
      M[row + a_idx] = max;
      ptr[row + a_idx] = ((char )0);
      if (max == left) {
        ptr[row + a_idx] = 'L';
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = 'U';
        }
         else {
          if (max == (up_left + score)) {
            ptr[row + a_idx] = 'D';
          }
        }
      }
    }
  }
  a_idx = 63;
  b_idx = 63;
  a_str_idx = ((a_idx * 1) + 1);
  b_str_idx = ((b_idx * 1) + 1);
  r = 0;
  row = b_idx * 64;
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace_back:
  while (1) {
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    trace_back_row:
    while (r < a_idx) {
      if (ptr[row + a_idx] == 'D') {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        a_str_idx = ((a_idx * 1) + 1);
        b_str_idx = ((b_idx * 1) + 1);
        row = b_idx * 64;
      }
       else {
        if (ptr[row + a_idx] == 'L') {
          a_idx = a_idx - 1;
          a_str_idx = ((a_idx * 1) + 1);
        }
         else {
          if (ptr[row + a_idx] == 'U') {
            b_idx = b_idx - 1;
            b_str_idx = ((b_idx * 1) + 1);
            row = b_idx * 64;
          }
        }
      }
      r = (a_idx + b_idx);
    }
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
  }
}