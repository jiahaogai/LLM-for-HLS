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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_main:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    init_tmp:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = ((int )SEQA[0]) * ((int )SEQB[0]) - 3;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = ((int )SEQA[0]) * ((int )SEQB[b_idx]) - 3;
      }
      else if (b_idx == 0) {
        M[a_idx * 5] = ((int )SEQA[a_idx]) * ((int )SEQB[0]) - 3;
      }
      else {
        M[b_idx * 5 + a_idx] = 0;
      }
      ptr[b_idx * 5 + a_idx] = 0;
    }
  }
/* Row = 1 ... 5 */
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    row = 5L * a_idx;
    row_up = 5L * (a_idx - 1);
/* Column = 1 ... 5 */
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      a_str_idx = a_idx * 5;
      if (a_idx == 0) {
        up_left = ((int )SEQA[b_idx]) * ((int )SEQB[a_idx]);
      }
      else if (b_idx == 0) {
        up_left = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]);
      }
      else {
        up_left = M[b_str_idx + (a_idx - 1)] + ((int )SEQA[b_idx]) * ((int )SEQB[a_idx]);
      }
      up = M[a_str_idx + (b_idx - 1)] + ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]);
      left = M[b_str_idx + a_idx] + ((int )SEQA[b_idx]) * ((int )SEQB[a_idx]);
      max = (up_left > ((int )(3 + 4))) ? ((int )(3 + 4)) : up_left;
      max = (up > max?up : max);
      max = (left > max?left : max);
      M[b_str_idx + a_idx] = max + 4;
      if (max == left) {
        ptr[b_str_idx + a_idx] = 2;
      }
      else {
        if (max == up) {
          ptr[b_str_idx + a_idx] = 1;
        }
        else {
          ptr[b_str_idx + a_idx] = 0;
        }
      }
    }
  }
/* Traceback */
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  r = 4;
  a_idx = 4;
  b_idx = 4;
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx * 5;
  score = M[b_str_idx + a_idx];
  while (a_idx != 0 || b_idx != 0) {
    if (ptr[b_str_idx + a_idx] == 0) {
      up = M[a_str_idx + (b_idx - 1)] + ((int )SEQA[a_idx]);
      left = M[b_str_idx + (a_idx - 1)] + ((int )SEQB[b_idx]);
      if (up == left) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        a_str_idx = a_idx * 5;
        b_str_idx = b_idx * 5;
        score = score - 4;
      }
      else {
        if (up > left) {
          a_idx = a_idx - 1;
          a_str_idx = a_idx * 5;
          score = score - ((int )SEQA[a_idx]);
        }
        else {
          b_idx = b_idx - 1;
          b_str_idx = b_idx * 5;
          score = score - ((int )SEQB[b_idx]);
        }
      }
    }
    else {
      if (ptr[b_str_idx + a_idx] == 1) {
        a_idx = a_idx - 1;
        a_str_idx = a_idx * 5;
        score = score - ((int )SEQA[a_idx]);
      }
      else {
        b_idx = b_idx - 1;
        b_str_idx = b_idx * 5;
        score = score - ((int )SEQB[b_idx]);
      }
    }
    r--;
  }
}