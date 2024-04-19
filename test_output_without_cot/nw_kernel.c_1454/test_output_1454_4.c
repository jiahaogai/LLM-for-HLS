# Original (un-optimized) kernel
 
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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_main:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    init_query:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 || b_idx == 0) {
        if (a_idx == 0 && b_idx == 0) {
          M[0] = SEQA[0] == SEQB[0]? 1 : -1;
        }
        else if (a_idx == 0) {
          M[b_idx] = M[b_idx * 5] + 1;
        }
        else {
          M[a_idx] = M[a_idx * 5] + 1;
        }
      }
      else {
        a_idx_up = (a_idx - 1) * 5;
        b_idx_up = (b_idx - 1) * 5;
        a_idx_left = a_idx * 5;
        b_idx_left = b_idx * 5;
        up_left = M[a_idx_up + b_idx] + ((SEQA[a_idx] == SEQB[b_idx])? 1 : -1);
        up = M[a_idx_up + b_idx_left] + 1;
        left = M[a_idx_left + b_idx] + 1;
        max = (up_left > up? up_left : up);
        max = (left > max? left : max);
        score = M[a_idx_left + b_idx_left] + ((SEQA[a_idx] == SEQB[b_idx])? 1 : -1);
        M[a_idx_left + b_idx] = score;
        if (score == max) {
          row = a_idx_left;
          r = b_idx_left;
        }
        else {
          if (score == up) {
            row = a_idx_up;
            r = b_idx;
          }
          else {
            row = a_idx_left;
            r = b_idx_up;
          }
        }
      }
    }
  }
}