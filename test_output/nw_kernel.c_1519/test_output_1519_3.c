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
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_mat:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    init_mat_row:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = ((int )SEQA[0]) * ((int )SEQB[0]) * score_match + ((int )SEQA[0]) * score_gap + ((int )SEQB[0]) * score_gap;
      }
      else if (a_idx == 0) {
        M[a_idx * 5 + b_idx] = ((int )SEQA[0]) * ((int )SEQB[b_idx]) * score_match + M[b_idx] + score_gap;
      }
      else if (b_idx == 0) {
        M[a_idx * 5 + b_idx] = ((int )SEQA[a_idx]) * ((int )SEQB[0]) * score_match + M[a_idx + 5 * 0] + score_gap;
      }
      else {
        M[a_idx * 5 + b_idx] = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]) * score_match + ((int )SEQA[a_idx]) * score_gap + ((int )SEQB[b_idx]) * score_gap + M[a_idx + 5 * (b_idx - 1)] + M[a_idx + 5 * b_idx - 5];
      }
    }
  }
/* TraceBack */
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 5;
  b_str_idx = 5;
  row = 4 * 5;
  score = M[row];
  ptr[row] = -1;
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace:
  while (1) {
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
    row_up = (a_idx - 1) * 5;
    up_left = M[row_up + b_idx];
    up = M[row_up + b_idx + 1];
    left = M[row + b_idx];
    max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
    if (max == left) {
      row = row + 1;
      a_idx = a_idx + 1;
      b_idx = b_idx + 1;
      a_str_idx = a_str_idx + 1;
      b_str_idx = b_str_idx + 1;
      score = score + ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) * score_match;
      alignedA[a_str_idx] = SEQA[a_idx - 1];
      alignedB[b_str_idx] = SEQB[b_idx - 1];
    }
    else {
      if (max == up) {
        a_idx = a_idx + 1;
        b_idx = b_idx + 1;
        a_str_idx = a_str_idx + 1;
        b_str_idx = b_str_idx + 1;
        score = score + ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) * score_match;
        alignedA[a_str_idx] = SEQA[a_idx - 1];
        alignedB[b_str_idx] = SEQB[b_idx - 1];
      }
      else {
        if (max == up_left) {
          if (up != left) {
            b_idx = b_idx + 1;
            b_str_idx = b_str_idx + 1;
            score = score + ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) * score_match;
            alignedA[a_str_idx] = SEQA[a_idx - 1];
            alignedB[b_str_idx] = SEQB[b_idx - 1];
          }
          else {
            a_idx = a_idx + 1;
            a_str_idx = a_str_idx + 1;
            score = score + ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx]) * score_ins;
            alignedA[a_str_idx] = SEQA[a_idx - 1];
            alignedB[b_str_idx] = '-';
          }
        }
      }
    }
  }
}