#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_in:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx * 16) - 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in_row:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx * 16) - 1;
      score_row = ((b_str_idx + 1) * 5) + a_idx;
      score_row_up = score_row - 5;
      up_left = M[score_row_up];
      up = M[score_row_up + 1] + 1;
      left = M[score_row] + 1;
      max = (up_left > ((left > up) ? left : up)) ? up_left : ((left > up) ? left : up);
      M[score_row] = max;
      if (max == left) {
        row = a_idx;
      }
      else {
        if (max == up) {
          row = a_idx - 1;
        }
        else {
          row = up_row;
        }
      }
      row_up = a_idx - 1;
      if ((int )alignedA[row_up] != (int )SEQA[a_str_idx]) {
        alignedA[row] = '-';
      } else {
        alignedA[row] = SEQA[a_str_idx];
      }
      if ((int )alignedB[a_idx] != (int )SEQB[b_str_idx]) {
        alignedB[a_idx] = '^';
      } else {
        alignedB[a_idx] = SEQB[b_str_idx];
      }
    }
  }
  b_str_idx = (56) - 1;
  a_str_idx = (56) - 1;
  score = M[((b_str_idx + 1) * 5) + a_str_idx];
  r = a_idx;
  a_idx = 5 - 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for ( ; a_idx >= 0; a_idx--) {
    a_str_idx = (a_idx * 16) - 1;
    score_row = ((b_str_idx + 1) * 5) + a_idx;
    score_row_up = score_row - 5;
    up_left = M[score_row_up];
    up = M[score_row_up + 1] + 1;
    left = M[score_row] + 1;
    max = (up_left > ((left > up) ? left : up)) ? up_left : ((left > up) ? left : up);
    M[score_row] = max;
    if (max == left) {
      row = a_idx;
    }
    else {
      if (max == up) {
        row = a_idx - 1;
      }
      else {
        row = up_row;
      }
    }
    row_up = a_idx - 1;
    if ((int )alignedA[row_up] != (int )SEQA[a_str_idx]) {
      alignedA[row] = '-';
    } else {
      alignedA[row] = SEQA[a_str_idx];
    }
    if ((int )alignedB[a_idx] != (int )SEQB[b_str_idx]) {
      alignedB[a_idx] = '^';
    } else {
      alignedB[a_idx] = SEQB[b_str_idx];
    }
  }
}