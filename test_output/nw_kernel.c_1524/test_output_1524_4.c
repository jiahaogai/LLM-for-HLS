#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char ptr[128],int M[128])
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
  int i;
  int j;
  int a_str_idx_col;
  int b_str_idx_col;
  int label;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = '-';
    M[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
  }
// Matrix initialization
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_in:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    b_str_idx_col = (b_idx * 16);
    init_col_j:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx_col = (a_idx * 16);
      up_left = ((int )SEQA[a_str_idx_col - 1]) * ((int )SEQB[b_str_idx_col - 1]);
      up = M[a_idx - 1] + ((int )' '- (int )SEQB[b_str_idx_col - 1]);
      left = M[a_idx * 16] + ((int )' '- (int )SEQA[a_str_idx_col - 1]);
      if (up_left > left) {
        if (up_left > up) {
          score = up_left;
          label = 1;
        } else {
          score = up;
          label = 2;
        }
      } else {
        if (left > up) {
          score = left;
          label = 3;
        } else {
          score = up;
          label = 2;
        }
      }
      M[a_idx * 16] = score;
      ptr[a_idx * 16] = label * 16 + b_idx - 1;
    }
  }
// TraceBack
  row = 4;
  a_str_idx = 4 * 16;
  b_str_idx = 4 * 16;
  alignedA[a_str_idx] = '_';
  alignedB[b_str_idx] = '_';
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  last_row:
  while (row != 0) {
    b_str_idx_row = b_str_idx;
    last_col:
    for (a_idx = row; a_idx > 0; a_idx--) {
      a_str_idx_row = a_str_idx;
      if (label == 1) {
        alignedA[a_str_idx_row] = SEQA[a_str_idx - 1];
        alignedB[b_str_idx_row] = SEQB[b_str_idx - 1];
        a_str_idx = a_str_idx - 1;
        b_str_idx = b_str_idx - 1;
      }
      if (label == 2) {
        alignedA[a_str_idx_row] = SEQA[a_str_idx - 1];
        alignedB[b_str_idx_row] = '_';
        a_str_idx = a_str_idx - 1;
      }
      if (label == 3) {
        alignedA[a_str_idx_row] = '_';
        alignedB[b_str_idx_row] = SEQB[b_str_idx - 1];
        b_str_idx = b_str_idx - 1;
      }
      b_str_idx = b_str_idx_row;
      a_str_idx = a_str_idx_row;
      label = ptr[a_idx * 16 + b_idx];
    }
    row_up = row - 1;
    row = row_up;
    a_str_idx = a_str_idx_row;
    b_str_idx = b_str_idx_row;
  }
  a_str_idx = 0;
  b_str_idx = 0;
}