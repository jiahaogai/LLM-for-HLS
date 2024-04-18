#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char M[128][128],char ptr[128][128])
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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_row:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    alignedA[a_idx] = ((char )0);
    SEQA[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    alignedB[b_idx] = ((char )0);
    SEQB[b_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_M:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    init_M_a_idx:
    for (b_idx = 0; b_idx < 128; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[a_idx][b_idx] = 0;
      }
      else {
        if (a_idx == 0) {
          M[a_idx][b_idx] = M[a_idx][b_idx + 1] + 1;
        }
        else {
          if (b_idx == 0) {
            M[a_idx][b_idx] = M[a_idx + 1][b_idx] + 1;
          }
          else {
            up_left = M[a_idx][b_idx + 1] + 1;
            up = M[a_idx][b_idx] + 1;
            left = M[a_idx + 1][b_idx] + 1;
            score = ((int )SEQA[a_idx]) - ((int )SEQB[b_idx]);
            max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
            if (score == 0) {
              max = (left > max?left : max);
            }
            else {
              if (score < 0) {
                max = (up > max?up : max);
              }
              else {
                max = (left > max?left : max);
              }
            }
            M[a_idx][b_idx] = max;
          }
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  traceback:
  a_idx = 0;
  b_idx = 0;
  a_row_end = 128;
  b_row_end = 128;
  a_col_end = 128;
  b_col_end = 128;
  a_row_pos = a_row_end - 1;
  b_row_pos = b_row_end - 1;
  a_col_pos = a_col_end - 1;
  b_col_pos = b_col_end - 1;
  loop_row:
  while (a_row_pos >= 0) {
    loop_col:
    while (b_col_pos >= 0) {
      if (a_col_pos < a_row_pos) {
        a_idx = a_row_pos;
        b_idx = b_col_pos;
      }
      else {
        if (b_col_pos < b_row_pos) {
          a_idx = a_col_pos;
          b_idx = b_row_pos;
        }
        else {
          a_idx = a_col_pos;
          b_idx = b_col_pos;
        }
      }
      up_left = M[a_idx][b_idx + 1] + 1;
      up = M[a_idx][b_idx] + 1;
      left = M[a_idx + 1][b_idx] + 1;
      score = ((int )SEQA[a_idx]) - ((int )SEQB[b_idx]);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      if (score == 0) {
        max = (left > max?left : max);
      }
      else {
        if (score < 0) {
          max = (up > max?up : max);
        }
        else {
          max = (left > max?left : max);
        }
      }
      if (max == left) {
        b_col_pos--;
        alignedA[a_col_pos] = ((char )'-');
        alignedB[a_col_pos] = SEQB[b_idx];
        ptr[a_col_pos][b_col_pos] = 3;
      }
      else {
        if (max == up) {
          a_col_pos--;
          alignedA[a_col_pos] = SEQA[a_idx];
          alignedB[a_col_pos] = ((char )'-');
          ptr[a_col_pos][b_col_pos] = 1;
        }
        else {
          a_col_pos--;
          b_col_pos--;
          alignedA[a_col_pos] = SEQA[a_idx];
          alignedB[a_col_pos] = SEQB[b_idx];
          ptr[a_col_pos][b_col_pos] = 2;
        }
      }
    }
    b_col_pos = b_col_end - 1;
    a_col_pos = a_col_end - 1;
    b_row_pos--;
  }
  a_row_pos = a_row_end - 1;
  b_row_pos = b_row_end - 1;
  a_col_pos = a_col_end - 1;
  b_col_pos = b_col_end - 1;
}