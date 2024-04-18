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
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_init:
  for (b_idx = 0; b_idx < 5; b_idx++) {
//#pragma ACCEL PARALLEL FACTOR=auto{1}
    score_init:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (b_idx == 0) {
        if (a_idx == 0) {
          M[0] = 0;
        }
        else {
          M[a_idx] = M[a_idx - 1] + 1;
        }
      }
      else {
        if (a_idx == 0) {
          M[a_idx + 5 * b_idx] = M[a_idx + 5 * (b_idx - 1)] + 1;
        }
        else {
          up_left = M[a_idx + 5 * (b_idx - 1)] + ((SEQA[a_idx] == SEQB[b_idx]) ? _TP_ : (_FP_ + _FN_));
          up = M[a_idx + 5 * b_idx + 5] + 1;
          left = M[a_idx + 5 * b_idx] + 1;
          M[a_idx + 5 * b_idx] = (up_left < up) ? ((up_left < left) ? up_left : left) : ((up < left) ? up : left);
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  align:
  for (b_idx = 1; b_idx < 5; b_idx++) {
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    trace_row:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = 5 * a_idx;
      b_str_idx = 5 * b_idx;
      row_up = a_str_idx + b_str_idx - 5;
      up = M[a_str_idx + b_str_idx - 5] + ((SEQA[a_idx] == SEQB[b_idx - 1]) ? _TP_ : (_FP_ + _FN_));
      row = M[a_str_idx + b_str_idx] + ((SEQA[a_idx] == SEQB[b_idx]) ? 0 : (_FP_ + _FN_));
      left = M[a_str_idx + b_str_idx - 5] + _CE_;
      max = (up_left > left) ? ((up > row) ? up : row) : ((left > up) ? left : up);
      score = max;
      if (max == left) {
        ptr[a_str_idx + b_str_idx] = 3;
        r = a_str_idx + b_str_idx - 5;
      }
      else {
        if (max == up) {
          ptr[a_str_idx + b_str_idx] = 2;
          r = a_str_idx + b_str_idx - 5 + 5;
        }
        else {
          ptr[a_str_idx + b_str_idx] = 1;
          r = a_str_idx + b_str_idx - 5 + 5 + 1;
        }
      }
      if (a_idx >= b_idx) {
        if (a_idx == b_idx) {
          alignedA[a_idx + 6] = '-';
        }
        else {
          alignedA[a_idx + 6] = alignedA[a_idx - b_idx + 6];
        }
        alignedB[a_idx + 6] = SEQB[b_idx];
      }
      if (a_idx <= b_idx) {
        if (a_idx == b_idx) {
          alignedA[a_idx + 6] = SEQA[a_idx];
        }
        else {
          alignedA[a_idx + 6] = SEQA[a_idx];
        }
        alignedB[a_idx + 6] = '-';
      }
    }
    alignedA[b_idx + 6] = '\0';
    alignedB[b_idx + 6] = '\0';
  }
}