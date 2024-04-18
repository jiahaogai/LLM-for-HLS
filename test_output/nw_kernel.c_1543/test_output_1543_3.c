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
  int a_col_end;
  int b_row_end;
  int b_col_end;
  int a_row;
  int a_col;
  int b_row;
  int b_col;
  char a_char;
  char b_char;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_row = 0; a_row < 15; a_row++) {
    M[a_row] = a_row * - 1;
    ptr[a_row] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (a_col = 0; a_col < 5; a_col++) {
    M[a_col * 15] = a_col * - 1;
    ptr[a_col * 15] = - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (a_row = 1; a_row < 15 - 1; a_row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in_a:
    for (a_col = 1; a_col < 5 - 1; a_col++) {
      a_row_up = a_row - 1;
      a_row_up = a_row_up * 15;
      a_col_up = a_col - 1;
      a_col_up = a_col_up * 15;
      a_row_down = a_row + 1;
      a_row_down = a_row_down * 15;
      a_col_down = a_col + 1;
      a_col_down = a_col_down * 15;
      row_up = M[a_row_up + a_col];
      left = M[a_row_up + a_col_down];
      row = M[a_row_up + a_col];
      up_left = M[a_row_up + a_col_up];
      up = M[a_row_up + a_col];
      left_down = M[a_row_down + a_col_down];
      down = M[a_row_down + a_col];
      up_right = M[a_row_up + a_col_down];
      max = (row > left) ? row : left;
      max = (up > max) ? up : max;
      max = (up_left > max) ? up_left : max;
      score = ((int )SEQA[a_row * 128]) - ((int )SEQB[a_col * 128]);
      if (score < 0) {
        score = 0 - score;
      }
      score = ((int )score) * weight_match;
      max = max + score;
      score = ((int )SEQA[a_row * 128]) - ((int )SEQB[a_col_down * 128]);
      if (score < 0) {
        score = 0 - score;
      }
      score = ((int )score) * weight_mismatch;
      left_down = left_down + score;
      score = ((int )SEQA[a_row_down * 128]) - ((int )SEQB[a_col * 128]);
      if (score < 0) {
        score = 0 - score;
      }
      score = ((int )score) * weight_mismatch;
      down = down + score;
      max = (max > left_down) ? max : left_down;
      max = (max > down) ? max : down;
      max = (max > up_right) ? max : up_right;
      M[a_row_up + a_col_up] = max;
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (max == row) {
        ptr[a_row_up + a_col_up] = 5;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (max == left) {
        ptr[a_row_up + a_col_up] = 4;
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == up_left) {
        ptr[a_row_up + a_col_up] = 3;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      if (max == up) {
        ptr[a_row_up + a_col_up] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      if (max == left_down) {
        ptr[a_row_up + a_col_up] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      if (max == down) {
        ptr[a_row_up + a_col_up] = 8;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L7}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      if (max == up_right) {
        ptr[a_row_up + a_col_up] = 7;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 127;
  b_idx = 127;
  r = 15;
  a_row_end = 15 * 128 - 1;
  b_row_end = 15 * 128 - 1;
  a_col_end = 5 * 128 - 1;
  b_col_end = 5 * 128 - 1;
/*
    traceBack:
    while (a_row != 0 || b_row != 0) {
      a_char = SEQA[a_idx];
      b_char = SEQB[b_idx];
      if (ptr[r * 15