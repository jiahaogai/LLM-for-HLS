#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],int E[1664],int P[1664],char ptr[1664])
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
  int max_idx;
  
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
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_score:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    fill_score:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (b_idx == 0) {
        if (a_idx == 0) {
          M[0] = 0;
        }
        else {
          M[a_idx] = M[a_idx - 1] + 1;
        }
      }
      else {
        if (a_idx == 0) {
          M[a_idx * 5] = M[(a_idx * 5) - 5] + 1;
        }
        else {
          score = ((int )SEQA[a_idx]) == ((int )SEQB[b_idx])?1 : -1;
          up_left = M[(b_idx - 1) * 5 + (a_idx - 1)] + score;
          up = M[(b_idx - 1) * 5 + a_idx] + 1;
          left = M[b_idx * 5 + (a_idx - 1)] + 1;
          M[b_idx * 5 + a_idx] = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        }
      }
    }
  }
}