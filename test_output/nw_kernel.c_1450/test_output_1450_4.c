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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{128}
  init_score:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx + 1] = alignedB[b_idx];
    M[b_idx + 1] = 0;
    ptr[b_idx + 1] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_row:
    for (a_idx = 0; a_idx < 64; a_idx++) {
      if (a_idx == 0) {
        M[((b_idx + 1) * 64) + a_idx] = ((b_idx == 0) ? 0 : (M[((b_idx + 0) * 64) + a_idx] + 1));
        ptr[((b_idx + 1) * 64) + a_idx] = 0;
      }
      else if (b_idx == 0) {
        M[((b_idx + 1) * 64) + a_idx] = ((a_idx == 0) ? 0 : (M[((b_idx + 0) * 64) + a_idx] + 1));
        ptr[((b_idx + 1) * 64) + a_idx] = 3;
      }
      else {
        up_left = M[((b_idx + 0) * 64) + (a_idx + 0)] + ((SEQA[a_idx] == SEQB[b_idx]) ? 0 : 1);
        up = M[((b_idx + 0) * 64) + a_idx] + 1;
        left = M[((b_idx + 1) * 64) + a_idx + 0] + 1;
        M[((b_idx + 1) * 64) + a_idx] = (up_left < up ? (up_left < left ? up_left : left) : (up < left ? up : left));
        if (up_left < up) {
          if (up_left < left) {
            ptr[((b_idx + 1) * 64) + a_idx] = 1;
          }
          else {
            ptr[((b_idx + 1) * 64) + a_idx] = 4;
          }
        }
        else {
          if (up < left) {
            ptr[((b_idx + 1) * 64) + a_idx] = 2;
          }
          else {
            ptr[((b_idx + 1) * 64) + a_idx] = 4;
          }
        }
      }
    }
  }
  row = 63;
  b_idx = 63;
  a_idx = 0;
  a_idx_up = 1;
  b_idx_up = 1;
  a_idx_left = 0;
  b_idx_left = 0;
  score = M[64 * 64 - 1];
  max = score;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace: while (a_idx < 64 && b_idx < 64) {
    a = alignedA[a_idx];
    b = alignedB[b_idx];
    row_up = ((b_idx + 1) * 64);
    if (ptr[row_up + a_idx] == 0) {
      a_idx++;
    }
    else if (ptr[row_up + a_idx] == 1) {
      a_idx_up = a_idx + 1;
      b_idx_up = b_idx + 1;
      a_idx = a_idx_up;
      b_idx = b_idx_up;
    }
    else if (ptr[row_up + a_idx] == 2) {
      a_idx_left = a_idx + 1;
      b_idx_left = b_idx;
      a_idx = a_idx_left;
      b_idx = b_idx_left;
    }
    else {
      a_idx_up = a_idx + 1;
      b_idx_up = b_idx + 1;
      a_idx_left = a_idx;
      b_idx_left = b_idx + 1;
      if (M[row_up + a_idx_left] <= M[row_up + a_idx_up]) {
        a_idx = a_idx_left;
        b_idx = b_idx_left;
      }
      else {
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
    }
    if (a_idx == 63 && b_idx == 63) {
      score = M[64 * 64 - 1];
    }
    else if (a_idx == 63) {
      score = M[b_idx * 64 + 63] + 1;
    }
    else if (b_idx == 63) {
      score = M[(a_idx) * 64 + 63] + 1;
    }
    else {
      score = M[b_idx * 64 + a_idx] + ((a == b) ? 0 : 1);
    }
  }
  r = 0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace_row:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    b = alignedB[b_idx];
    row = ((b_idx) * 64);
    trace_col:
    for (a_idx = 0; a_idx < 64; a_idx++) {
      a = alignedA[a_idx];
      if (a_idx == 0 && b_idx == 0) {
        alignedA[a_idx] = a;
        alignedB[b_idx] = b;
      }
      else if (a_idx == 0) {
        alignedA[a_idx] = a;
        alignedB[b_idx] = b;
      }
      else if (b_idx == 0) {