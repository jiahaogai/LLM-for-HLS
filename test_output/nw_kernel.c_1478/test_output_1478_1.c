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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    score_init:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[b_idx]) == ((int )SEQB[a_idx])) {
        M[a_idx * 5 + b_idx] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      score_loop:
      for (b_str_idx = (b_idx + 1); b_str_idx < 5; b_str_idx++) {
        up_left = M[(b_idx) * 5 + (b_str_idx - 1)] + ((SEQA[b_str_idx] == SEQB[a_idx]) ? 1 : -1);
        up = M[(b_idx) * 5 + b_str_idx] + (-1);
        left = M[(b_str_idx) * 5 + a_idx] + (-1);
        max = (up_left > ((up > left) ? up : left));
        row_up = ((b_str_idx - 1) * 5) + a_idx;
        M[row_up] = max;
        ptr[row_up] = ((left == max) ? 3 : ((up == max) ? 2 : 1));
      }
    }
  }
}