#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx * 16) + 1;
    row = 0;
    row_up = 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx * 16) + 1;
      if (a_idx == 0) {
        score = ((int )SEQB[b_str_idx]) * match;
        M[0] = score;
      }
      else {
        up_left = M[row_up * 16 + a_idx_up] + ((int )SEQA[a_str_idx_up]) * ((int )SEQB[b_str_idx]) * mismatch;
        up = M[row_up * 16 + a_idx] + gap;
        left = M[row * 16 + a_idx_left] + ((int )SEQA[a_str_idx_left]) * gap;
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[row * 16 + a_idx] = max;
        if (max == left) {
          row = a_idx_left;
        }
        else {
          if (max == up) {
            row = a_idx_up;
          }
          else {
            row = a_idx_up_left;
          }
        }
      }
    }
    alignedB[b_idx * 16 + 14] = '_';
    alignedB[b_idx * 16 + 13] = '_';
    alignedB[b_idx * 16 + 12] = '_';
    alignedB[b_idx * 16 + 11] = '_';
    alignedB[b_idx * 16 + 10] = '_';
    alignedB[b_idx * 16 + 9] = '_';
    alignedB[b_idx * 16 + 8] = '_';
    alignedB[b_idx * 16 + 7] = '_';
    alignedB[b_idx * 16 + 6] = '_';
    alignedB[b_idx * 16 + 5] = '_';
    alignedB[b_idx * 16 + 4] = '_';
    alignedB[b_idx * 16 + 3] = '_';
    alignedB[b_idx * 16 + 2] = '_';
    alignedB[b_idx * 16 + 1] = '_';
    alignedB[b_idx * 16] = SEQB[b_str_idx];
  }
  alignedB[b_idx * 16 + 14] = '_';
  alignedB[b_idx * 16 + 13] = '_';
  alignedB[b_idx * 16 + 12] = '_';
  alignedB[b_idx * 16 + 11] = '_';
  alignedB[b_idx * 16 + 10] = '_';
  alignedB[b_idx * 16 + 9] = '_';
  alignedB[b_idx * 16 + 8] = '_';
  alignedB[b_idx * 16 + 7] = '_';
  alignedB[b_idx * 16 + 6] = '_';
  alignedB[b_idx * 16 + 5] = '_';
  alignedB[b_idx * 16 + 4] = '_';
  alignedB[b_idx * 16 + 3] = '_';
  alignedB[b_idx * 16 + 2] = '_';
  alignedB[b_idx * 16 + 1] = '_';
  alignedB[b_idx * 16] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace_back:
  a_idx = 4;
  b_idx = 4;
  a_str_idx = (a_idx * 16) + 1;
  b_str_idx = (b_idx * 16) + 1;
/*
    trace_out: while(a_idx != 0 || b_idx != 0) {
      if (M[b_idx * 16 + a_idx] == M[(b_idx + 1) * 16 + a_idx] + gap) {
        b_idx = b_idx + 1;
        alignedB[b_idx * 16 + 14] = '_';
        alignedB[b_idx * 16 + 13] = '_';
        alignedB[b_idx * 16 + 12] = '_';
        alignedB[b_idx * 16 + 11] = '_';
        alignedB[b_idx * 16 + 10] = '_';
        alignedB[b_idx * 16 + 9] = '_';
        alignedB[b_idx * 16 + 8] = '_';
        alignedB[b_idx * 16 + 7] = '_';
        alignedB[b_idx * 16 + 6] = '_';
        alignedB[b_idx * 16 + 5] = '_';
        alignedB[b_idx * 16 + 4] = '_';
        alignedB[b_idx * 16 + 3] = '_';
        alignedB[b_idx * 16 + 2] = '_';
        alignedB[b_idx * 16 + 1] = '_';
        alignedB[b_idx * 16] = SEQB[b_str_idx];
        b_str_idx = b_str_idx + 1;
      }
      else
      if (M[b_idx * 16 + a_idx] == M[b_idx * 16 + a_idx_left] + ((int )SEQA[a_str_idx_left]) * gap) {
        a_idx = a_idx_left;
        a_str_idx = a_str_idx_left;
        alignedA[a_idx * 16 + 14] = '_';
        alignedA[a_idx * 16 + 13] = '_';
        alignedA[a_idx * 16 + 12] = '_';
        alignedA[a_idx * 16 + 11] = '_';
        alignedA[a_idx * 16 + 10] = '_';
        alignedA