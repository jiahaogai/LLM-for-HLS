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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_score_a:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[0] = 1;
      }
       else {
        M[0] = 0;
      }
      if (a_idx == 0 && b_idx == 0) {
        ptr[0] = 0;
      }
       else {
        if (a_idx == 0) {
          row_up = 0;
          a_str_idx = 0;
          b_str_idx = 1 * a_idx;
          up = M[a_str_idx * 64 + b_str_idx] + 1;
        }
         else {
          if (b_idx == 0) {
            row_up = 0;
            a_str_idx = 1 * a_idx;
            b_str_idx = 0;
            left = M[(a_str_idx - 1) * 64 + b_str_idx] + 1;
          }
           else {
            row_up = 1 * a_idx;
            a_str_idx = 1 * a_idx;
            b_str_idx = 1 * b_idx;
            up_left = M[(a_str_idx - 1) * 64 + (b_str_idx - 1)] + ((int )SEQA[a_idx] == (int )SEQB[b_idx] ? 1 : 0);
            up = M[a_str_idx * 64 + b_str_idx] + 1;
            left = M[(a_str_idx - 1) * 64 + b_str_idx] + 1;
          }
        }
        score = (up_left < up ? up_left : up);
        score = (score < left ? score : left);
        M[a_str_idx * 64 + b_str_idx] = score;
        if (score == left) {
          ptr[a_str_idx * 64 + b_str_idx] = 2;
        }
         else {
          if (score == up) {
            ptr[a_str_idx * 64 + b_str_idx] = 1;
          }
           else {
            ptr[a_str_idx * 64 + b_str_idx] = 3;
          }
        }
      }
    }
  }
/* TraceBack */
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 5 * a_idx;
  b_str_idx = 5 * b_idx;
  row = 64L + 4;
/*
    r = M[a_str_idx * 64L + b_str_idx];
    while (1) {
      if (a_idx == 0 || b_idx == 0) {
        break;
      }
      if (ptr[a_str_idx * 64L + b_str_idx] == 0) {
        break;
      }
      if (ptr[a_str_idx * 64L + b_str_idx] == 2) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        a_str_idx = 5L * a_idx;
        b_str_idx = 5L * b_idx;
      }
       else {
        if (ptr[a_str_idx * 64L + b_str_idx] == 1) {
          a_idx = a_idx - 1;
          a_str_idx = 5L * a_idx;
        }
         else {
          if (ptr[a_str_idx * 64L + b_str_idx] == 3) {
            b_idx = b_idx - 1;
            b_str_idx = 5L * b_idx;
          }
        }
      }
      r = M[a_str_idx * 64L + b_str_idx];
    }
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace:
  while (1) {
    if (a_idx == 0 || b_idx == 0) {
      break;
    }
    if (ptr[a_str_idx * 64 + b_str_idx] == 0) {
      break;
    }
    if (ptr[a_str_idx * 64 + b_str_idx] == 2) {
      alignedA[row] = '_';
      alignedB[row] = SEQB[b_idx - 1];
      a_idx = a_idx - 1;
      b_idx = b_idx - 1;
      a_str_idx = 5L * a_idx;
      b_str_idx = 5L * b_idx;
      row_up = 64L + a_idx;
    }
     else {
      if (ptr[a_str_idx * 64 + b_str_idx] == 1) {
        alignedA[row] = SEQA[a_idx - 1];
        alignedB[row] = '_';
        a_idx = a_idx - 1;
        a_str_idx = 5L * a_idx;
      }
       else {
        if (ptr[a_str_idx * 64 + b_str_idx] == 3) {
          alignedA[row] = '_';
          alignedB[row] = SEQB[b_idx - 1];
          b_idx = b_idx - 1;
          b_str_idx = 5L * b_idx;
        }
      }
    }
    row = row_up;
  }
}