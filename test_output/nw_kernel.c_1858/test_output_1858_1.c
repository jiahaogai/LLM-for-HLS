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
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    M[a_idx] = ((int )alignedA[a_idx]) * ((int )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    M[b_idx] = ((int )alignedB[b_idx]) * ((int )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    a_str_idx = 0;
    b_str_idx = b_idx;
    a_str_idx_p1 = 1;
    b_str_idx_p1 = b_str_idx + 1;
    a:
    for (a_idx = 1; a_idx < 5 + 1; a_idx++) {
      a_str_idx = a_str_idx + 1;
      b_str_idx = b_str_idx_p1;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx_p1 + 1;
      score = ((int )SEQA[a_str_idx_p1]) * ((int )M[b_str_idx]) + ((int )SEQB[b_str_idx_p1]) * ((int )M[a_str_idx]) - ((int )1) * ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_in:
      for (r = 0; r < 5; r++) {
        row = 5 * b_idx + a_idx;
        row_up = (5 + 1) * b_idx + a_idx;
        up_left = row_up - 5;
        up = row_up;
        left = row - 1;
        max = ((score > ((int )M[left]))) ? score : ((int )M[left]);
        M[row_up] = ((int )SEQA[a_str_idx_p1]) * ((int )M[b_str_idx_p1]) + ((int )SEQB[b_str_idx]) * ((int )M[a_str_idx]) - ((int )1) * ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx_p1]);
        ptr[row_up] = ((char )((int )(((int )b_str_idx_p1) + ((int )48))));
        if (max == ((int )M[left])) {
          ptr[row_up] = ((char )((int )(((int )up_left) + ((int )48))));
        }
        else {
          if (max == ((int )M[up])) {
            ptr[row_up] = ((char )((int )(((int )up) + ((int )48))));
          }
        }
      }
    }
  }
}