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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    row = a_idx * 6;
    a_str_idx = a_idx * 16;
    b_str_idx = a_idx * 4;
    M[row + 0] = ((int )'A') * ((int )'A') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 0] = 0;
    M[row + 1] = ((int )'A') * ((int )'C') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 1] = 1;
    M[row + 2] = ((int )'A') * ((int )'D') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 2] = 2;
    M[row + 3] = ((int )'A') * ((int )'E') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 3] = 3;
    M[row + 4] = ((int )'A') * ((int )'F') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 4] = 4;
    M[row + 5] = ((int )'A') * ((int )'\0') * 1 + ((int )'B') * 0 * -1 + 1;
    ptr[row + 5] = 5;
  }
}