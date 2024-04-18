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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedB[a_idx + 5] = '_';
    a_str_idx = a_idx * 16;
    b_str_idx = a_idx * 4;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_score:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[b_idx] = B[b_idx];
      }
      else if (a_idx == 0) {
        M[b_idx] = M[b_idx + 1] + B[b_idx];
        ptr[b_idx] = 2;
      }
      else if (b_idx == 0) {
        M[b_idx] = M[a_idx + 1] + A[a_idx];
        ptr[b_idx] = 1;
      }
      else {
        up_left = M[b_idx + 1] + A[a_idx];
        up = M[b_idx] + A[a_idx];
        left = M[b_idx + 1] + B[b_idx];
        if (up_left > left) {
          if (up_left > up) {
            M[b_idx] = up_left;
            ptr[b_idx] = 3;
          }
          else {
            M[b_idx] = up;
            ptr[b_idx] = 1;
          }
        }
        else {
          if (left > up) {
            M[b_idx] = left;
            ptr[b_idx] = 4;
          }
          else {
            M[b_idx] = up;
            ptr[b_idx] = 1;
          }
        }
      }
    }
  }
/* Traceback */
  row = 4;
  b_idx = 4;
  a_idx = 4;
  a_str_idx = a_idx * 16;
  b_str_idx = b_idx * 4;
  trace_row:
  while (row != 0) {
    trace_col:
    while (b_idx != 0) {
      if (ptr[b_idx] == 2) {
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = '_';
        a_str_idx --;
        b_str_idx --;
        a_idx --;
        b_idx --;
      }
      else {
        if (ptr[b_idx] == 1) {
          alignedA[a_str_idx] = SEQA[a_idx];
          alignedB[b_str_idx] = SEQB[b_idx];
          a_str_idx --;
          b_str_idx --;
          a_idx --;
          b_idx --;
        }
        else {
          if (ptr[b_idx] == 4) {
            alignedA[a_str_idx] = SEQA[a_idx];
            alignedB[b_str_idx] = '_';
            a_str_idx --;
            b_str_idx --;
            a_idx --;
          }
          else {
            if (ptr[b_idx] == 3) {
              alignedA[a_str_idx] = '_';
              alignedB[b_str_idx] = SEQB[b_idx];
              a_str_idx --;
              b_str_idx --;
              b_idx --;
            }
          }
        }
      }
    }
    b_idx = 4;
    trace_move:
    while (a_idx != row) {
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedB[b_str_idx] = '_';
      a_str_idx --;
      b_str_idx --;
      a_idx --;
    }
    row = a_idx;
  }
}