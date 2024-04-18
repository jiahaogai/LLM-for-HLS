#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],char ptr[1664])
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
  int a_row_pos;
  int b_row_pos;
  int a_col_pos;
  int b_col_pos;
  int a_row_start;
  int b_row_start;
  int a_col_start;
  int b_col_start;
  char a_char;
  char b_char;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 128L; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128L; b_idx++) {
    M[b_idx * 128L] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128L; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128L; a_idx++) {
      a_row_end = ((int )b_idx * - 1) + 128L;
      b_row_end = ((int )a_idx * - 1) + 128L;
      a_col_end = ((int )b_idx) + 128L;
      b_col_end = ((int )a_idx) + 128L;
      a_row_start = a_row_end - ((int )SEQA_LEN);
      b_row_start = b_row_end - ((int )SEQB_LEN);
      a_col_start = a_col_end - ((int )SEQA_LEN);
      b_col_start = b_col_end - ((int )SEQB_LEN);
      if (a_row_start < 0) {
        a_row_start = 0;
      }
      if (b_row_start < 0) {
        b_row_start = 0;
      }
      if (a_col_start < 0) {
        a_col_start = 0;
      }
      if (b_col_start < 0) {
        b_col_start = 0;
      }
      a_row_pos = a_row_start;
      b_row_pos = b_row_start;
      a_col_pos = a_col_start;
      b_col_pos = b_col_start;
      a_char = ((char )0);
      b_char = ((char )0);
      row = a_row_start * 128L;
      row_up = (a_row_start - 1L) * 128L;
/* Standardize from: for(a_idx = a_col_start; a_idx < a_col_end; a_idx++) */
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      standardize_A:
      while (a_col_pos < a_col_end) {
        a_idx_up = (a_idx_left + 1L) * 1L;
        a_idx_left = a_idx_up;
        a_idx = a_idx_left;
        a_char = SEQA[a_idx];
        b_col_pos = b_col_start;
        standardize_B:
        for (b_idx_left = b_col_start; b_idx_left < b_col_end; b_idx_left++) {
          b_idx_up = (b_idx_left + 1L) * 1L;
          b_idx_left = b_idx_up;
          b_idx = b_idx_left;
          b_char = SEQB[b_idx];
          score = ((int )a_char) * ((int )b_char);
          up_left = M[row_up + b_idx_left] + (1L - ((int )a_char)) * (1L - ((int )b_char));
          up = M[row + b_idx_left] + (1L - ((int )a_char));
          left = M[row_up + b_idx_left] + (1L - ((int )b_char));
          max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
          M[row + b_idx_left] = max;
          if (max == left) {
            b_idx = b_idx_left;
          }
          if (max == up) {
            a_idx = a_idx_left;
            b_idx = b_idx_up;
          }
          if (max == up_left) {
            a_idx = a_idx_up;
            b_idx = b_idx_up;
          }
        }
        b_col_pos = b_col_end;
        a_col_pos ++;
        row = a_row_pos * 128L;
        row_up = a_row_pos * 128L - 1L;
        a_col_pos = a_col_pos + 1L;
        a_row_pos = a_row_pos + 1L;
      }
      a_row_pos = a_row_end;
      b_row_pos = b_row_end;
      a_col_pos = a_col_end;
      b_col_pos = b_col_end;
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = ((int )SEQA_LEN) - 1L;
  b_idx = ((int )SEQB_LEN) - 1L;
  a_row = ((int )SEQA_LEN) - 1L;
  b_row = ((int )SEQB_LEN) - 1L;
  ptr[0L] = - 1L;
/* Standardize from: while(a_idx != 0 || b_idx != 0) */
  
#pragma ACCEL PIPELINE auto{off}
  while (a_idx != 0 || b_idx != 0) {
    a_char = ((char )0);
    b_char = ((char )0);
    if (a_idx != 0) {
      a_char = SEQA[a_idx];
    }
    if (b_idx != 0) {
      b_char = SEQB[b_idx];
    }
    score = ((int )a_char) * ((int )b_char);
    up_left = M[b_row * 128L + a_idx] + (1L - ((int )a_char)) * (1L - ((int )b_char));
    up = M