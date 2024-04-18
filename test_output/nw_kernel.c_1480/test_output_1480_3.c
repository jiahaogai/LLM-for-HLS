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
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 5;
    row_up = a_str_idx;
    row = a_str_idx + 5;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      left = M[b_str_idx];
      up = M[row_up];
      score = ((SEQA[a_str_idx] == SEQB[b_str_idx]) ? 1LL : - 1LL);
//#pragma ACCEL PIPELINE auto{__PIPE__L1}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      loop_inner:
      for (r = 0; r < 5; r++) {
        up_left = up + ((SEQA[a_str_idx + r] == SEQB[b_str_idx + r]) ? 1LL : - 1LL);
        max = (up_left);
        max = (left + ((SEQA[a_str_idx + r] == SEQB[b_str_idx + 5]) ? 1LL : - 1LL));
        max = (M[b_str_idx + r] + ((SEQA[a_str_idx + r] == SEQB[b_str_idx]) ? 1LL : - 1LL));
        M[b_str_idx + r + 5] = max;
        ptr[b_str_idx + r + 5] = ((max == up_left) ? b_str_idx + r : ((max == left) ? b_str_idx : a_str_idx + r));
        up = left;
        left = max;
      }
    }
  }
// TraceBack
  a_idx = 21;
  b_idx = 21;
  a_str_idx = (a_idx * 5);
  b_str_idx = (b_idx * 5);
/*
    traceBack: while(a_idx > 0 || b_idx > 0) {
      if (a_idx == 0) {
        alignedA[a_idx + 1] = '_';
        alignedB[b_idx + 1] = SEQB[b_str_idx];
        b_idx--;
        b_str_idx -= 5;
      }
      else if (b_idx == 0) {
        alignedA[a_idx + 1] = SEQA[a_str_idx];
        alignedB[b_idx + 1] = '_';
        a_idx--;
        a_str_idx -= 5;
      }
      else if (M[b_str_idx + 5] > M[b_str_idx] && M[b_str_idx + 5] > M[a_str_idx + 5]) {
        alignedA[a_idx + 1] = SEQA[a_str_idx];
        alignedB[b_idx + 1] = SEQB[b_str_idx];
        a_idx--;
        b_idx--;
        a_str_idx -= 5;
        b_str_idx -= 5;
      }
      else if (M[a_str_idx + 5] > M[b_str_idx] && M[a_str_idx + 5] > M[b_str_idx + 5]) {
        alignedA[a_idx + 1] = SEQA[a_str_idx];
        alignedB[b_idx + 1] = '_';
        a_idx--;
        a_str_idx -= 5;
      }
      else if (M[b_str_idx] > M[a_str_idx + 5] && M[b_str_idx] > M[b_str_idx + 5]) {
        alignedA[a_idx + 1] = '_';
        alignedB[b_idx + 1] = SEQB[b_str_idx];
        b_idx--;
        b_str_idx -= 5;
      }
    }
    alignedA[0] = '_';
    alignedB[0] = '_';
*/
}