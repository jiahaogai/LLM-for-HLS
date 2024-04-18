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
  int score_row;
  int a_col;
  int b_col;
  int score_col;
  int ptr_row;
  int ptr_col;
  int temp;
  int i;
  int j;
  int k;
  int m;
  int n;
  int p;
  int q;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 32; a_idx++) {
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 32; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (a_idx = 0; a_idx < 32; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (b_idx = 0; b_idx < 32; b_idx++) {
      score_row = (a_idx) * 32;
      score_col = (b_idx) * 32;
      ptr_row = score_row;
      ptr_col = score_col;
      if (a_idx == 0 || b_idx == 0) {
        if (a_idx == 0 && b_idx == 0) {
          M[0] = 0;
          ptr[0] = 0;
        }
        else if (a_idx == 0) {
          up_left = M[score_col + 31] + 1;
          up = M[score_col] + 1;
          left = M[score_row + 31] + 1;
          max = (up_left > left)?up_left : left;
          M[score_row + score_col] = max;
          if (max == left) {
            temp = 3;
          }
          else {
            temp = 2;
          }
          ptr[score_row + score_col] = temp;
        }
        else {
          up_left = M[score_col + 31] + 1;
          up = M[score_col] + 1;
          left = M[score_row + 31] + 1;
          max = (up_left > up)?up_left : up;
          max = (max > left)?max : left;
          M[score_row + score_col] = max;
          if (max == left) {
            temp = 5;
          }
          else {
            if (max == up_left) {
              temp = 4;
            }
            else {
              temp = 1;
            }
          }
          ptr[score_row + score_col] = temp;
        }
      }
      else {
        row_up = score_row + 31;
        row = score_row;
        up_left = M[row_up + b_idx] + ((int )SEQA[a_idx] != (int )SEQB[b_idx]?1 : 0);
        up = M[row_up] + 1;
        left = M[score_col + 31] + 1;
        max = (up_left > left)?up_left : left;
        max = (max > up)?max : up;
        M[score_row + score_col] = max;
        if (max == left) {
          temp = 8 + ((int )SEQA[a_idx] != (int )SEQB[b_idx]?0 : 1);
        }
        else {
          if (max == up) {
            temp = 4 + ((int )SEQA[a_idx] != (int )SEQB[b_idx]?0 : 1);
          }
          else {
            temp = 1 + ((int )SEQA[a_idx] != (int )SEQB[b_idx]?0 : 1);
          }
        }
        ptr[score_row + score_col] = temp;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace_back:
  for (a_idx = 31; a_idx >= 0; a_idx--) {
    b_idx = 31;
    score_row = (a_idx) * 32;
    score_col = (b_idx) * 32;
    ptr_row = score_row;
    ptr_col = score_col;
    score = M[score_row + score_col];
    alignedA[a_idx] = SEQA[a_idx];
    alignedB[b_idx] = SEQB[b_idx];
    loop_row_up:
    for (r = a_idx + 1; r < 32; r++) {
      row_up = score_row + 31;
      row = score_row;
      up_left = M[row_up + b_idx] + ((int )SEQA[r] != (int )SEQB[b_idx]?1 : 0);
      up = M[row_up] + 1;
      left = M[row + score_col + 31] + 1;
      max = (up_left > left)?up_left : left;
      max = (max > up)?max : up;
      M[row + score_col] = max;
      if (max == left) {
        temp = 8 + ((int )SEQA[r] != (int )SEQB[b_idx]?0 : 1);
      }
      else {
        if (max == up) {
          temp = 4 + ((int )SEQA[r] != (int )SEQB[b_idx]?0 : 1);
        }
        else {
          temp = 1 + ((int )SEQA[r] != (int )SEQB[b_idx]?0 : 1);
        }
      }
      ptr[row + score_col] = temp;
    }
    loop_col_up:
    for (r = b_idx + 1; r < 32; r++) {
      score_col = (r) * 32;
      up_left = M[row_up + r] + ((int )SEQA[a_idx] != (int )SEQB[r]?1 : 0);
      up = M[row_up] + 1;
      left = M[score_row + score_col + 31] + 1;
      max = (up_left > left)?up_left : left;
      max = (max > up)?max : up;
      M[score_row + score_col] = max;
      if (max == left) {
        temp = 8 + ((int )SEQA[a_idx] != (int )SEQB[r]?0 : 1);
      }
      else {
        if (max == up) {
          temp = 4 + ((int )SEQA[a_idx] != (