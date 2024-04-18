#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],char ptr[16642])
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
  int score_row;
  int score_row_up;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  alignedB[b_idx + 1] = '_';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedB[((int )alignedA[a_idx])] = a_idx;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  fill_zero:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedA[((int )alignedB[b_idx])] = b_idx;
    score_row = b_idx * 5;
    score_row_up = (b_idx - 1) * 5;
    row = 0;
    row_up = 0;
    str_idx_row:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (a_idx == 0) {
        up_left = 0;
      }
      else {
        up_left = ((int )alignedA[a_idx]) * 5 + ((int )alignedB[0]);
      }
      if (b_idx == 0) {
        left = 0;
      }
      else {
        left = score_row_up + ((int )alignedB[a_idx]);
      }
      if (a_idx == 0 && b_idx == 0) {
        M[score_row + ((int )alignedA[a_idx])] = left * match + up_left * match;
      }
      else if (a_idx == 0) {
        M[score_row + ((int )alignedA[a_idx])] = left * match + up_left * mismatch;
      }
      else if (b_idx == 0) {
        M[score_row + ((int )alignedA[a_idx])] = left * mismatch + up_left * match;
      }
      else {
        up = score_row_up + ((int )alignedA[a_idx]);
        M[score_row + ((int )alignedA[a_idx])] = (left * match + up_left * mismatch) > (up * mismatch + left * match) ? (left * match + up_left * mismatch) : (up * mismatch + left * match);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  trace_back:
  for (b_idx = 4; b_idx >= 0; b_idx--) {
    b_str_idx = ((int )alignedB[b_idx]) * 5;
    a_idx = 4;
    a_str_idx = b_str_idx + ((int )alignedA[a_idx]);
    ptr[b_idx] = a_idx;
    trace_row:
    while (a_idx > 0) {
      up_left = b_str_idx + ((int )alignedA[a_idx]) + ((int )alignedB[a_idx]);
      up = b_str_idx + ((int )alignedA[a_idx]) + ((int )alignedB[a_idx - 1]);
      left = a_str_idx;
      if (M[up_left] == (M[up] + mismatch)) {
        a_idx--;
        a_str_idx = left;
      }
      else if (M[up_left] == (M[left] + match)) {
        a_str_idx = up_left;
      }
      else {
        ptr[a_idx] = ((int )alignedA[a_idx]) + 1;
        a_idx--;
        a_str_idx = up;
      }
    }
    ptr[a_idx] = -1;
  }
  a_idx = 0;
  b_idx = 0;
  a_str_idx = 0;
  b_str_idx = 0;
  trace: while (a_idx < 5 || b_idx < 5) {
    r = ((int )ptr[a_idx]) - a_idx;
    if (r == 0) {
      alignedA[a_idx] = SEQA[b_idx];
      alignedB[b_idx] = SEQB[a_idx];
      a_idx++;
      b_idx++;
      a_str_idx += 5;
      b_str_idx += 1;
    }
    else {
      if (r > 0) {
        b_idx++;
        b_str_idx += 1;
      }
      else {
        a_idx++;
        a_str_idx += 5;
      }
    }
  }
}