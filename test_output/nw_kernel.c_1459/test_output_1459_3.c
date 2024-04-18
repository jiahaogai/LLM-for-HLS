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
  int a_row_end;
  int b_row_end;
  int a_col_end;
  int b_col_end;
  int a_row;
  int b_row;
  int a_col;
  int b_col;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_row = 0; a_row < 64; a_row++) {
    alignedA[a_row * 64] = SEQA[a_row];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (a_col = 0; a_col < 64; a_col++) {
    alignedA[a_col] = SEQA[a_col];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_row:
  for (b_row = 0; b_row < 64; b_row++) {
    alignedB[b_row * 64] = SEQB[b_row];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_col:
  for (b_col = 0; b_col < 64; b_col++) {
    alignedB[b_col] = SEQB[b_col];
  }
  a_row_end = 0;
  b_row_end = 0;
  a_col_end = 1;
  b_col_end = 1;
  a_row = 0;
  b_row = 0;
  a_col = 0;
  b_col = 0;
  a_idx = 128;
  b_idx = 128;
  loop_row:
  while (a_row_end < 64) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    loop_col:
    while (b_col_end < 64) {
      a_idx_up = a_idx - 64;
      b_idx_up = b_idx - 64;
      a_idx_left = a_idx - 1;
      b_idx_left = b_idx - 1;
      up_left = ((int )alignedA[a_idx_up]) - ((int )alignedB[b_idx_up]);
      up = ((int )alignedA[a_idx_up]) - ((int )alignedB[b_idx]);
      left = ((int )alignedA[a_idx]) - ((int )alignedB[b_idx_left]);
      max = ((int )0);
      row_up = up_left + left;
      row = up + left;
      if (row_up > row) {
        if (row_up > max) {
          max = row_up;
          row = row_up;
          flg = 0;
        }
        else {
          flg = 1;
        }
      }
      else {
        if (row > max) {
          max = row;
        }
        else {
          flg = 1;
        }
      }
      col = up + left;
      if (col > max) {
        max = col;
      }
      else {
        flg = 1;
      }
      if (flg == 0) {
        a_idx = a_idx_left;
        b_idx = b_idx_left;
      }
      else {
        flg = 2;
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
    }
    b_col_end += 1;
    b_col = ((int )64) - 1 - b_col_end;
  }
  a_row_end += 1;
  a_row = ((int )64) - 1 - a_row_end;
}