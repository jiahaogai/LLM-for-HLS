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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_a:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[a_idx * 5 + b_idx] = ((int )SEQA[a_idx]) * SCORE_MATCH + b_idx * SCORE_GAP_A + a_idx * SCORE_GAP_B;
      }
       else {
        M[a_idx * 5 + b_idx] = ((int )SEQA[a_idx]) * SCORE_MISMATCH + b_idx * SCORE_GAP_A + a_idx * SCORE_GAP_B;
      }
    }
  }
// Traceback
  a_idx = 0;
  b_idx = 0;
  a_str_idx = 0;
  b_str_idx = 0;
  row = 5;
  row_up = ((5 + 1) * 5);
// Row-major order
/*
    for(a_idx = 0; a_idx < 5; a_idx++) {
      for(b_idx = 0; b_idx < 5; b_idx++) {
        score = M[a_idx * 5 + b_idx];
        up_left = M[(a_idx - 1) * 5 + (b_idx - 1)] + ((int )SEQA[a_idx] == (int )SEQB[b_idx]?SCORE_MATCH:SCORE_MISMATCH);
        up = M[(a_idx - 1) * 5 + b_idx] + SCORE_GAP_B;
        left = M[a_idx * 5 + (b_idx - 1)] + SCORE_GAP_A;
        max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
        ptr[a_idx * 5 + b_idx] = -1;
        if (max == left) {
          b_idx--;
          b_str_idx--;
        }
         else {
          if (max == up) {
            a_idx--;
            a_str_idx--;
          }
           else {
            if (max == up_left) {
              if (((int )SEQA[a_idx] == (int )SEQB[b_idx])) {
                ptr[a_idx * 5 + b_idx] = 4;
              }
               else {
                ptr[a_idx * 5 + b_idx] = 3;
              }
              a_idx--;
              b_idx--;
              a_str_idx--;
              b_str_idx--;
            }
          }
        }
      }
      b_str_idx += 5;
    }
*/
// Column-major order
/*
    for(a_idx = 0; a_idx < 5; a_idx++) {
      for(b_idx = 0; b_idx < 5; b_idx++) {
        score = M[a_idx * 5 + b_idx];
        up_left = M[(a_idx - 1) * 5 + (b_idx - 1)] + ((int )SEQA[a_idx] == (int )SEQB[b_idx]?SCORE_MATCH:SCORE_MISMATCH);
        up = M[(a_idx - 1) * 5 + b_idx] + SCORE_GAP_B;
        left = M[a_idx * 5 + (b_idx - 1)] + SCORE_GAP_A;
        max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
        ptr[a_idx * 5 + b_idx] = -1;
        if (max == left) {
          b_idx--;
        }
         else {
          if (max == up) {
            a_idx--;
          }
           else {
            if (max == up_left) {
              if (((int )SEQA[a_idx] == (int )SEQB[b_idx])) {
                ptr[a_idx * 5 + b_idx] = 4;
              }
               else {
                ptr[a_idx * 5 + b_idx] = 3;
              }
              a_idx--;
              b_idx--;
            }
          }
        }
      }
      b_idx = 5 - 1;
    }
*/
// Row-major order
  r:
  for (a_idx = ((int )0) + 1; a_idx < 5; a_idx++) {
    b_idx = 0;
    b_str_idx = (a_idx) * 5;
    u:
    for (b_idx = ((int )0) + 1; b_idx < 5; b_idx++) {
      score = M[a_idx * 5 + b_idx];
      up_left = M[(a_idx - 1) * 5 + (b_idx - 1)] + ((int )SEQA[a_idx] == (int )SEQB[b_idx]?SCORE_MATCH:SCORE_MISMATCH);
      up = M[(a_idx - 1) * 5 + b_idx] + SCORE_GAP_B;
      left = M[a_idx * 5 + (b_idx - 1)] + SCORE_GAP_A;
      max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
      ptr[a_idx * 5 + b_idx] = -1;
      if (max == left) {
        b_idx--;
        b_str_idx--;
      }
       else {
        if (max == up) {
          a_idx--;
          a_str_idx--;
        }
         else {
          if (max == up_left) {
            if (((int )SEQA[a_idx] == (int )SEQB[b_idx])) {
              ptr[a_idx * 5 + b_idx] = 4;
            }
             else {
              ptr[a_idx * 5 + b_idx] = 3;
            }
            a_idx--;
            b_idx--;
            a_str_idx--;
            b_str_idx--;
          }
        }
      }
    }
    b_idx = 4;