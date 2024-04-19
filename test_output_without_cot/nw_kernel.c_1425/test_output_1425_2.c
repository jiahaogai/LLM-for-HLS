#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],char ptr[130],int M[130])
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
  int a_str_idx;
  int b_str_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 128L + 1; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '\0';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 128L + 1; b_idx++) {
    M[b_idx * 128L] = b_idx;
    alignedB[b_idx] = '\0';
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  row_init:
  for (a_idx = 0; a_idx < 128L; a_idx++) {
    a_idx_up = a_idx + 1;
    a_str_idx = a_idx * 128L;
    b_str_idx = 0L * 128L;
    init_col:
    for (b_idx = 0; b_idx < 128L; b_idx++) {
      b_idx_up = b_idx + 1;
      score = ((SEQA[a_str_idx]) == ((SEQB[b_str_idx])) ? 1 : (-1)) + M[b_str_idx + a_idx_up];
      up_left = M[b_str_idx + a_idx_up] + ((SEQA[a_str_idx]) == ((SEQB[b_str_idx + b_idx_up])) ? 1 : (-1));
      up = M[b_str_idx + a_idx_up] + 1;
      left = M[b_str_idx + a_idx_up] + 1;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[b_str_idx + a_idx_up] = max;
      if (max == left) {
        b_idx_up = b_idx + 1;
      }
      if (max == up) {
        a_idx_up = a_idx + 1;
        b_str_idx = b_idx_up * 128L;
      }
    }
  }
// Traceback
  row = 128L;
  b_idx = 128L;
  a_idx = 0L;
  a_str_idx = ((long )a_idx) * 128L;
  b_str_idx = ((long )b_idx) * 128L;
  trace:
  while (a_idx < 128L || b_idx < 128L) {
    row_up = a_idx + 1;
    if (a_idx < 128L) {
      a_str_idx = ((long )a_idx) * 128L;
    }
    if (b_idx < 128L) {
      b_str_idx = ((long )b_idx) * 128L;
    }
    if (b_idx < 128L && a_idx < 128L) {
      score = ((SEQA[a_str_idx]) == ((SEQB[b_str_idx])) ? 1 : (-1)) + M[b_str_idx + a_idx];
    }
    up_left = M[b_str_idx + a_idx + 1] + ((SEQA[a_str_idx]) == ((SEQB[b_str_idx + 1L])) ? 1 : (-1));
    up = M[b_str_idx + a_idx + 1] + 1;
    left = M[b_str_idx + a_idx + 1] + 1;
    max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
    if (max == left) {
      b_idx = b_idx + 1L;
      b_str_idx = ((long )b_idx) * 128L;
    }
    if (max == up) {
      a_idx = a_idx + 1L;
      a_str_idx = ((long )a_idx) * 128L;
    }
    if (max == up_left) {
      a_idx = a_idx + 1L;
      b_idx = b_idx + 1L;
      a_str_idx = ((long )a_idx) * 128L;
      b_str_idx = ((long )b_idx) * 128L;
    }
  }
  row = 0L;
  b_idx = 0L;
  a_idx = 128L - 1L;
  a_str_idx = ((long )a_idx) * 128L;
  b_str_idx = ((long )b_idx) * 128L;
  trace2:
  while (a_idx >= 0L || b_idx >= 0L) {
    row_up = a_idx + 1;
    if (a_idx >= 0L) {
      a_str_idx = ((long )a_idx) * 128L;
    }
    if (b_idx >= 0L) {
      b_str_idx = ((long )b_idx) * 128L;
    }
    if (b_idx >= 0L && a_idx >= 0L) {
      score = ((SEQA[a_str_idx]) == ((SEQB[b_str_idx])) ? 1 : (-1)) + M[b_str_idx + a_idx];
    }
    up_left = M[b_str_idx + a_idx - 1L] + ((SEQA[a_str_idx - 1L]) == ((SEQB[b_str_idx])) ? 1 : (-1));
    up = M[b_str_idx + a_idx - 1L] + 1;
    left = M[b_str_idx + a_idx - 1L] + 1;
    max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
    if (max == left) {
      b_idx = b_idx - 1L;
      b_str_idx = ((long )b_idx) * 128L;
    }
    if (max == up) {
      a_idx = a_idx - 1L;
      a_str_idx = ((long )a_idx) * 128L;
    }
    if (max == up_left) {
      a_idx = a_idx - 1L;
      b_idx = b_idx - 1L;
      a_str_idx = ((long )a_idx) * 128L;
      b_str_idx = ((long )b_idx) * 128L;
    }
  }
}