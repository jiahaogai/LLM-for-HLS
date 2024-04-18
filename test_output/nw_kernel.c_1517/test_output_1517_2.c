#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char ptr[128],int M[128])
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
  int idx_row;
  int idx_row_up;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    ptr[a_idx] = a_idx;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    ptr[b_idx + 5] = b_idx;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  trace_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    trace_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      row_up = a_idx * 5;
      idx_row_up = a_idx * 6;
      up_left = ((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx])?1:-1;
      up = M[row_up + 5] + ((int )SEQA[a_str_idx + 5]) == ((int )SEQB[b_str_idx + 5])?1:-1;
      left = M[b_str_idx + 5] + ((int )SEQA[a_str_idx + 5]) == ((int )SEQB[b_str_idx])?1:-1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      score = M[b_str_idx + 5] + max;
//#pragma ACCEL PARALLEL FACTOR=auto{1}
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      trace_max:
      for (r = 1; r < 5; r++) {
        row = r + a_idx * 5;
        idx_row = r + idx_row_up;
        up_left = M[row_up + r + 1] + ((int )SEQA[a_str_idx + r + 1]) == ((int )SEQB[b_str_idx + r + 1])?1:-1;
        up = M[row + 5] + ((int )SEQA[a_str_idx + r + 1 + 5]) == ((int )SEQB[b_str_idx + r + 1 + 5])?1:-1;
        left = M[b_str_idx + r + 1] + ((int )SEQA[a_str_idx + r + 1 + 5]) == ((int )SEQB[b_str_idx + r + 1])?1:-1;
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[idx_row] = score;
        if (max == left) {
          b_idx = b_idx + 1;
          b_str_idx = b_idx * 5;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        if (max == up) {
          a_idx = a_idx + 1;
          a_str_idx = a_idx * 5;
          row_up = a_idx * 5;
          idx_row_up = a_idx * 6;
        }
        score = M[b_str_idx + r + 1] + max;
      }
      M[idx_row] = score;
    }
  }
//#pragma endscop
}