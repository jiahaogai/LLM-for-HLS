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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_zero:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx) * 128;
    init_col_j:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx) * 128;
      M[b_str_idx + a_idx] = 0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx) * 128;
    row_up = (b_idx - 1) * 128;
    init_A:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx) * 128;
      up_left = M[row_up + (a_idx - 1)] + ((a_idx == 1) ? 0 : -1) * 1;
      up = M[row_up + a_idx] + ((a_idx == 1) ? 0 : -1) * 1;
      left = M[b_str_idx + (a_idx - 1)] + ((b_idx == 1) ? 0 : -1) * 1;
      score = (((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx])) ? 1 : -1;
//#Score
      max = (up_left > (up + ((a_idx == 1) ? 0 : -1) * 1)) ? (up_left > (left + ((b_idx == 1) ? 0 : -1) * 1)) ? up_left : (left + ((b_idx == 1) ? 0 : -1) * 1) : (up + ((a_idx == 1) ? 0 : -1) * 1) > (left + ((b_idx == 1) ? 0 : -1) * 1) ? (up + ((a_idx == 1) ? 0 : -1) * 1) : (left + ((b_idx == 1) ? 0 : -1) * 1);
      M[b_str_idx + a_idx] = max;
      ptr[b_str_idx + a_idx] = (char )(((long )max == (long )up_left) ? 2 : ((long )max == (long )up) ? 1 : 0);
    }
  }
}