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
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_M:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx * 5) + 1;
    row = 1;
    row_up = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_M_row:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx * 5) + 1;
      if (a_idx == 0) {
        M[b_str_idx] = ((int )SEQB[b_idx]) * score_match + ((int )SEQA[a_idx]) * score_mismatch;
      }
      else if (b_idx == 0) {
        M[a_str_idx] = ((int )SEQA[a_idx]) * score_match + ((int )SEQB[b_idx]) * score_mismatch;
      }
      else {
        up_left = M[a_str_idx_prev] + ((int )SEQA[a_idx]) * score_match + ((int )SEQB[b_idx]) * score_mismatch;
        up = M[a_str_idx] + ((int )SEQA[a_idx]) * score_mismatch;
        left = M[b_str_idx_prev] + ((int )SEQB[b_idx]) * score_match + ((int )SEQA[a_idx]) * score_mismatch;
        M[a_str_idx] = (up_left > ((int )0 ? up : ((int )0)));
        if (up_left > ((int )0 ? up : ((int )0))) {
          max = up_left;
          ptr[a_str_idx] = 3;
        }
        else {
          max = up;
          ptr[a_str_idx] = 2;
        }
        if (left > max) {
          max = left;
          ptr[a_str_idx] = 1;
        }
      }
    }
  }
}