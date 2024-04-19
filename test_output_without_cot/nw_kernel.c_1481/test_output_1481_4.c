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
  int pad_a;
  int pad_b;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 65; a_idx++) {
    M[a_idx] = a_idx * - 1;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 65; b_idx++) {
    M[b_idx * 65] = b_idx * - 1;
    alignedB[b_idx] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  fill_out:
  for (b_idx = 1; b_idx < 65; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    fill_in:
    for (a_idx = 1; a_idx < 65; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * 65;
      row = b_idx * 65;
      up_left = ScoreMatrix[((int )SEQA[a_idx - 1])][((int )SEQB[b_idx - 1])] + M[row_up + (a_idx - 1)];
      up = ScoreMatrix[((int )SEQA[a_idx - 1])][((int )SEQB[b_idx - 1])] + M[row_up + a_idx];
      left = ScoreMatrix[((int )SEQA[a_idx - 1])][((int )SEQB[b_idx - 1])] + M[row + (a_idx - 1)];
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = 1;
        }
         else {
          ptr[row + a_idx] = 0;
        }
      }
      alignedA[a_idx + 64] = ((int )SEQA[a_idx - 1]);
      alignedB[b_idx + 64] = ((int )SEQB[b_idx - 1]);
    }
  }
// TraceBack
  pad_a = 64;
  pad_b = 64;
  a_idx = 64;
  b_idx = 64;
  score_row = 64 * 65;
  a_col = 64;
  b_col = 64;
  r = 0;
  while (1) {
    if (ptr[score_row + a_idx] == 0) {
      a_idx--;
      b_idx--;
      a_col = a_idx;
      b_col = b_idx;
    }
     else {
      if (ptr[score_row + a_idx] == 1) {
        a_idx--;
        score_row += 65;
        r++;
        b_col = b_idx + 1;
      }
       else {
        if (ptr[score_row + a_idx] == 2) {
          score_row += 65;
          a_col = a_idx + 1;
          b_col = b_idx;
        }
      }
    }
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_out:
  for (r = 0; r < 64; r++) {
    alignedA[pad_a + r] = ((char )'-');
    alignedB[pad_b + r] = ((char )'-');
  }
}