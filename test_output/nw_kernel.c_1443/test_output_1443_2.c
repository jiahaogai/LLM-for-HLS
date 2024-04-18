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
  int a_str_idx;
  int b_str_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    init_score_a:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 || b_idx == 0) {
        if (a_idx == 0 && b_idx == 0) {
          M[0] = 0;
          ptr[0] = -1;
        }
        else if (a_idx == 0) {
          M[b_idx] = 4 * b_idx;
          ptr[b_idx] = -1;
        }
        else {
          M[b_idx] = 4 * a_idx;
          ptr[b_idx] = -1;
        }
      }
      else {
        score = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]) - ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) + M[b_idx - 1] - 1;
        row_up = b_idx - 1;
        up_left = M[row_up] + ((int )SEQA[a_idx] - (int )SEQB[b_idx - 1]);
        up = M[b_idx] - ((int )SEQA[a_idx - 1]) + 1;
        left = up_left + 1;
        if (left < up) {
          if (left < up_left) {
            max = left;
            a_str_idx = a_idx;
            b_str_idx = b_idx;
          }
          else {
            max = up_left;
            a_str_idx = a_idx;
            b_str_idx = row_up;
          }
        }
        else {
          if (up < up_left) {
            max = up;
            a_str_idx = a_idx - 1;
            b_str_idx = b_idx;
          }
          else {
            max = up_left;
            a_str_idx = a_idx;
            b_str_idx = row_up;
          }
        }
        M[b_idx] = max;
        if (max == left) {
          ptr[b_idx] = a_idx;
        }
        else {
          if (max == up) {
            ptr[b_idx] = a_idx - 1;
          }
          else {
            ptr[b_idx] = row_up;
          }
        }
      }
    }
  }
  row = 5;
  b_idx = 5;
  a_idx = ptr[b_idx] + 1;
  a_str_idx = a_idx;
  b_str_idx = b_idx;
/* TraceBack */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    if (a_idx == 0) {
      alignedA[row] = '-';
      alignedB[row] = SEQB[b_idx - 1];
      b_idx --;
    }
    else if (b_idx == 0) {
      alignedA[row] = SEQA[a_idx - 1];
      alignedB[row] = '-';
      a_idx --;
    }
    else if (M[b_idx] - M[b_idx - 1] == M[a_idx - 1 - b_idx] + ((int )SEQA[a_idx - 1]) - ((int )SEQB[b_idx - 1])) {
      alignedA[row] = SEQA[a_idx - 1];
      alignedB[row] = SEQB[b_idx - 1];
      a_idx --;
      b_idx --;
    }
    else if (M[b_idx] - M[b_idx - 1] > M[a_idx - 1 - b_idx] + ((int )SEQA[a_idx - 1]) - ((int )SEQB[b_idx - 1])) {
      alignedA[row] = SEQA[a_idx - 1];
      alignedB[row] = '-';
      a_idx --;
    }
    else {
      alignedA[row] = '-';
      alignedB[row] = SEQB[b_idx - 1];
      b_idx --;
    }
    row_up = b_idx - 1;
    up_left = M[row_up] + ((int )SEQA[a_idx] - (int )SEQB[b_idx - 1]);
    up = M[b_idx] - ((int )SEQA[a_idx - 1]) + 1;
    left = up_left + 1;
    if (left < up) {
      if (left < up_left) {
        max = left;
        a_str_idx = a_idx;
        b_str_idx = b_idx;
      }
      else {
        max = up_left;
        a_str_idx = a_idx;
        b_str_idx = row_up;
      }
    }
    else {
      if (up < up_left) {
        max = up;
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx;
      }
      else {
        max = up_left;
        a_str_idx = a_idx;
        b_str_idx = row_up;
      }
    }
    row = b_idx;
    b_idx = b_str_idx;
    a_idx = a_str_idx + 1;
  }
}