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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      score = ((int )SEQA[a_idx - 1]) - 97 < ((int )SEQB[b_idx - 1]) - 97 ? ((int )SEQA[a_idx - 1]) - 97 : ((int )SEQB[b_idx - 1]) - 97;
      row_up = b_idx * 5;
      up_left = row_up + (a_idx - 1);
      up = row_up + a_idx;
      left = up_left;
      max = M[up_left] + score;
      if (M[up] + 1 > max) {
        max = M[up] + 1;
        ptr[up] = left;
      }
      if (M[left] + 1 > max) {
        max = M[left] + 1;
        ptr[up] = up;
      }
      M[up] = max;
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row_up = b_idx * 5;
    up_left = row_up + a_idx;
    up = row_up + a_idx - 1;
    left = up_left - 1;
*/
  up = 4 * 5 + 4 - 1;
  left = 4 * 5 + 4 - 1;
  r = 0;
/*
    trace_row:
    while(a_idx > 0 || b_idx > 0){
      if (up >= left) {
        b_idx = (up - b_idx);
        a_idx = (b_idx - a_idx);
        up = ptr[up];
      }
      else if (left > up) {
        a_idx = (left - a_idx);
        left = ptr[left];
      }
      else {
        b_idx = (up - b_idx);
        a_idx = (up - a_idx);
        up = ptr[up];
        left = ptr[left];
      }
      r = a_idx * 5 + b_idx;
      alignedA[a_str_idx++] = SEQA[a_idx - 1];
      alignedB[b_str_idx++] = SEQB[b_idx - 1];
    }
*/
  trace_row:
  while(a_idx > 0 || b_idx > 0) {
    if (up >= left) {
      b_idx = (up - b_idx);
      a_idx = (b_idx - a_idx);
      up = ptr[up];
    }
    else if (left > up) {
      a_idx = (left - a_idx);
      left = ptr[left];
    }
    else {
      b_idx = (up - b_idx);
      a_idx = (up - a_idx);
      up = ptr[up];
      left = ptr[left];
    }
    r = a_idx * 5 + b_idx;
    alignedA[a_str_idx++] = SEQA[a_idx - 1];
    alignedB[b_str_idx++] = SEQB[b_idx - 1];
  }
  alignedA[a_str_idx++] = 0;
  alignedB[b_str_idx++] = 0;
}