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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    score_row:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = ((int )SEQA[0]) * ((int )SEQB[0]) - 1;
        ptr[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx] = M[b_idx * 1] + ((int )SEQB[b_idx]) - ((int )SEQA[0]) * ((int )SEQB[b_idx]);
        ptr[b_idx] = 0;
      }
      else if (b_idx == 0) {
        M[a_idx * 1] = M[a_idx * 1 * 1] + ((int )SEQA[a_idx]) - ((int )SEQB[0]) * ((int )SEQA[a_idx]);
        ptr[a_idx * 1] = 1;
      }
      else {
        up_left = M[(b_idx - 1) * 1] + ((int )SEQA[a_idx]) - ((int )SEQB[b_idx]);
        up = M[a_idx * 1] + ((int )SEQB[b_idx]) - ((int )SEQA[a_idx]);
        left = M[a_idx * 1 * 1] + ((int )SEQA[a_idx]) - ((int )SEQB[b_idx]);
        max = (up_left > ((int )0)) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
        M[a_idx * 1 * 1] = max;
        if (max == left) {
          ptr[a_idx * 1 * 1] = 3;
        }
        else {
          if (max == up) {
            ptr[a_idx * 1 * 1] = 2;
          }
          else {
            ptr[a_idx * 1 * 1] = 1;
          }
        }
      }
    }
  }
}