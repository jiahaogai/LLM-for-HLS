#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256])
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
  int i;
  int j;
  int a_str_idx_col;
  int b_str_idx_col;
  int label;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    init_score_a:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[0] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      init_score_b:
      for (i = 1; i < 6; i++) {
        a_str_idx_col = (a_idx + (i * 5));
        b_str_idx_col = (b_idx + (i * 5));
        up_left = M[(i - 1) * 5 + (b_idx + (0 * 5))];
        up = M[(i - 1) * 5 + (b_idx + (1 * 5))] - 1;
        left = M[i * 5 + (b_idx + (0 * 5))] - 1;
        if (((int )SEQA[a_str_idx_col]) == ((int )SEQB[b_str_idx_col])) {
          score = 1;
        }
         else {
          score = 0;
        }
        max = (up_left > ((up > left)?up : left))?up_left : ((up > left)?up : left);
        M[i * 5 + b_idx] = ((long )((up_left + score) > ((up + left)?(up + left) : (up_left + score))?up_left : ((up + left)?(up + left) : (up_left + score))));
        ptr[i * 5 + b_idx] = ((long )max);
      }
    }
  }
/* TraceBack */
  a_idx = 4;
  b_idx = 4;
  label = M[a_idx * 5 + b_idx] + 1;
  a_str_idx = a_idx;
  b_str_idx = b_idx;
  trace: while(1) {
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_row:
    for (i = 4; i >= 0; i--) {
      row = i;
      row_up = row + 5;
      a_str_idx = a_idx;
      b_str_idx = b_idx;
      loop_col:
      for (j = 4; j >= 0; j--) {
        if (row == 4 && j == 4) {
          goto loop_col_end;
        }
        if (ptr[row_up * 5 + b_idx] == label) {
          a_str_idx = a_str_idx + 5;
          b_str_idx = b_str_idx;
        }
         else {
          if (ptr[row * 5 + b_idx + 5] == label) {
            a_str_idx = a_str_idx;
            b_str_idx = b_str_idx + 5;
          }
           else {
            if (ptr[row_up * 5 + b_idx + 5] == label) {
              a_str_idx = a_str_idx + 5;
              b_str_idx = b_str_idx + 5;
            }
             else {
              a_str_idx = a_str_idx + 1;
              b_str_idx = b_str_idx + 1;
            }
          }
        }
        label = M[a_str_idx * 5 + b_str_idx];
      }
      loop_col_end:;
    }
  }
  trace_end:;
  alignedA[a_idx] = ((void *)0);
  alignedB[b_idx] = ((void *)0);
}