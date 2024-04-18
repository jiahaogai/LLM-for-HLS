c
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
  int a_row_end;
  int a_row_start;
  int b_row_end;
  int b_row_start;
  int a_col;
  int b_col;
  char a_char;
  char b_char;
  int max_row;
  int max_row_idx;
  int max_col;
  int max_col_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    M[b_idx * 128] = b_idx * - 1;
    ptr[b_idx * 128] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  out_row:
  for (a_idx = 1; a_idx < 128 - 1; a_idx++) {
    a_row_start = a_idx * 128;
    a_row_end = (a_idx + 1) * 128;
    row_up = a_idx * 128 - 1;
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    in_row:
    for (b_idx = 1; b_idx < 128 - 1; b_idx++) {
      b_row_start = b_idx * 128;
      b_row_end = (b_idx + 1) * 128;
      up = row_up;
      left = b_row_start;
      max_row = M[a_row_start] + SEQA[a_idx * 128];
      max_row_idx = a_row_start;
      max_col = M[b_row_start] + SEQB[b_idx * 128];
      max_col_idx = b_row_start;
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      inner_col:
      for (b_col = 1; b_col < 128 - 1; b_col++) {
        a_col = a_row_start + b_col * 128;
        score = ((SEQA[a_col] == SEQB[b_col * 128]) ? 1 : 0) + M[a_col];
        up_left = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 - 128]) ? 1 : 0);
        up = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 + 128]) ? 1 : 0);
        left = M[a_col] + ((SEQA[a_col + 128] == SEQB[b_col * 128]) ? 1 : 0);
        if (up_left > max_col) {
          max_col = up_left;
          max_col_idx = left + b_col * 128;
        }
        if (up > max_row) {
          max_row = up;
          max_row_idx = up_left + b_col * 128;
        }
        if (left > max) {
          max = left;
          max_idx = a_col;
        }
        M[a_col] = score;
      }
      b_col = 127 - 1;
      a_col = a_row_end;
      score = ((SEQA[a_col] == SEQB[b_col * 128]) ? 1 : 0) + M[a_col];
      up_left = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 - 1]) ? 1 : 0);
      up = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 + 1]) ? 1 : 0);
      if (up_left > max_col) {
        max_col = up_left;
        max_col_idx = left + b_col * 128;
      }
      if (up > max_row) {
        max_row = up;
        max_row_idx = up_left + b_col * 128;
      }
      if (score > max) {
        max = score;
        max_idx = a_col;
      }
      M[a_col] = score;
      ptr[a_col] = max_col_idx;
    }
    b_idx = 127 - 1;
    a_col = a_row_end;
    score = ((SEQA[a_col] == SEQB[b_col * 128]) ? 1 : 0) + M[a_col];
    up_left = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 - 1]) ? 1 : 0);
    up = M[a_col - 128] + ((SEQA[a_col] == SEQB[b_col * 128 + 1]) ? 1 : 0);
    if (up_left > max_col) {
      max_col = up_left;
      max_col_idx = left + b_col * 128;
    }
    if (up > max_row) {
      max_row = up;
      max_row_idx = up_left + b_col * 128;
    }
    if (score > max) {
      max = score;
      max_idx = a_col;
    }
    M[a_col] = score;
    ptr[a_col] = max_col_idx;
  }
  a_idx = 127 - 1;
  a_row_end = (a_idx + 1) * 128;
  row_up = a_idx * 128 - 1;
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  last_