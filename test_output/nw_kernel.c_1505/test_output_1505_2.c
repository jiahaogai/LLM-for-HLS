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
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_main:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    init_tmp:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = 0;
        ptr[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = - 1 * b_idx;
        ptr[b_idx * 5] = 3;
      }
      else if (b_idx == 0) {
        M[a_idx * 5] = - 1 * a_idx;
        ptr[a_idx * 5] = 1;
      }
      else {
        score = ((int )SEQA[a_idx]) == ((int )SEQB[b_idx])?1:- 1;
        up_left = M[(b_idx - 1) * 5] + - 1 * a_idx;
        up = M[b_idx * 5] + - 1 * a_idx;
        left = M[a_idx * 5] + - 1 * b_idx;
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[b_idx * 5 + a_idx] = max;
        row_up = b_idx * 5;
        if (max == left) {
          ptr[b_idx * 5 + a_idx] = row_up + a_idx + 1;
        }
        else {
          if (max == up) {
            ptr[b_idx * 5 + a_idx] = row_up + a_idx;
          }
          else {
            ptr[b_idx * 5 + a_idx] = row_up + a_idx - 1;
          }
        }
      }
    }
  }
  row = 4 * 5;
  a_str_idx = 4 * 5 - 1;
  b_str_idx = 5 - 1;
  a_idx = 4;
  b_idx = 4;
  while (a_idx != 0 || b_idx != 0) {
    if (b_idx == 0) {
      alignedA[a_str_idx] = alignedA[a_idx + a_str_idx];
      a_str_idx = a_str_idx - 1;
      a_idx = a_idx + 1;
    }
    else if (a_idx == 0) {
      alignedB[b_str_idx] = alignedB[b_idx + b_str_idx];
      b_str_idx = b_str_idx - 1;
      b_idx = b_idx + 1;
    }
    else if (M[b_idx * 5 + a_idx] > M[(b_idx - 1) * 5 + a_idx - 1] + 1) {
      if (M[b_idx * 5 + a_idx] > M[b_idx * 5 + a_idx - 1] + 1) {
        alignedA[a_str_idx] = alignedA[a_idx + a_str_idx];
        a_str_idx = a_str_idx - 1;
        a_idx = a_idx + 1;
      }
      else {
        alignedA[a_str_idx] = alignedA[a_idx + a_str_idx];
        a_str_idx = a_str_idx - 1;
        a_idx = a_idx + 1;
      }
      alignedB[b_str_idx] = SEQB[b_idx];
      b_str_idx = b_str_idx - 1;
      b_idx = b_idx + 1;
    }
    else if (M[b_idx * 5 + a_idx] > M[(b_idx - 1) * 5 + a_idx] + 1) {
      alignedA[a_str_idx] = SEQA[a_idx];
      a_str_idx = a_str_idx - 1;
      a_idx = a_idx + 1;
      alignedB[b_str_idx] = alignedB[b_idx + b_str_idx];
      b_str_idx = b_str_idx - 1;
      b_idx = b_idx + 1;
    }
    else {
      alignedA[a_str_idx] = SEQA[a_idx];
      a_str_idx = a_str_idx - 1;
      a_idx = a_idx + 1;
      alignedB[b_str_idx] = SEQB[b_idx];
      b_str_idx = b_str_idx - 1;
      b_idx = b_idx + 1;
    }
  }
}