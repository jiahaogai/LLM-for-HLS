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
  up = 24;
  left = 23;
  r = 0;
/*
    trace_row:
    while(1) {
      if (up >= left) {
        break;
      }
      if (M[up] == M[left]) {
        up = ptr[up];
        left = ptr[left];
        a_str_idx++;
        b_str_idx++;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      trace_col:
      for (r = 0; r < 5; r++) {
        if (up + r == left) {
          break;
        }
      }
    }
*/
  trace_row:
  while(a_idx > 0 || b_idx > 0){
    if (up >= left) {
      a_str_idx++;
      b_str_idx++;
      alignedA[a_str_idx] = SEQA[a_idx - 1];
      alignedB[b_str_idx] = SEQB[b_idx - 1];
      a_idx--;
      b_idx--;
      up = ptr[up];
      left = ptr[left];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    trace_col:
    for (r = 0; r < 5; r++) {
      if (up + r == left) {
        a_str_idx++;
        b_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx - 1];
        alignedB[b_str_idx] = SEQB[b_idx - 1];
        a_idx--;
        b_idx--;
        up = ptr[up];
        left = ptr[left];
      }
    }
  }
}