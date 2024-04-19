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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = '-';
  }
  alignedA[64] = '\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  alignedB[64] = '\0';
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx + 65] = SEQA[a_idx];
    M[a_idx] = 0;
    ptr[a_idx] = 0;
  }
  M[64] = 0;
  ptr[64] = 0;
  alignedA[129] = '\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score_row:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx + 65] = SEQB[b_idx];
  }
  alignedB[129] = '\0';
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_str_idx = a_idx + 1;
    row_up = (a_idx == 0) ? -1 : a_idx - 1;
    row = a_idx + 65;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    diag:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      b_str_idx = b_idx + 1;
      up_left = M[row_up * 64 + b_idx];
      left = M[row * 64 + b_idx_up];
      if (((int )SEQA[a_str_idx - 1]) == ((int )SEQB[b_str_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      up = M[row_up * 64 + b_idx] + -1;
      left = M[row * 64 + b_idx_up] + -1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row * 64 + b_idx] = max;
      if (max == left) {
        ptr[row * 64 + b_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[row * 64 + b_idx] = 1;
        }
         else {
          ptr[row * 64 + b_idx] = 0;
        }
      }
    }
  }
}