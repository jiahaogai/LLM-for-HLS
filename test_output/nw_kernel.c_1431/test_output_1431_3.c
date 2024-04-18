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
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : (- 1));
      row_up = a_idx * 5;
      up_left = score + M[row_up + b_idx];
      up = M[row_up + b_idx + 1] + 1;
      left = M[row_up + b_idx + 1] + 1;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[a_idx * 5 + b_idx] = max;
      row = a_idx * 5 + b_idx;
      if (max == left) {
        ptr[row] = ((b_idx == 0) ? (- 1) : (row - 1));
      }
      
#pragma ACCEL PIPELINE auto{off}
      if (max == up) {
        ptr[row] = row_up;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      if (max == up_left) {
        ptr[row] = (b_idx == 0) ? (- 1) : (ptr[row - 1] + 1);
      }
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row_up = a_idx * 5;
    r = M[row_up + b_idx];
    while (a_idx > 0 || b_idx > 0) {
      row_up = a_idx * 5;
      if (r == M[row_up + b_idx]) {
        a_idx--;
        b_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
        r = M[row_up + b_idx];
      }
      else {
        if (r == M[row_up + b_idx + 1]) {
          b_idx++;
          alignedA[a_str_idx++] = SEQA[a_idx];
          alignedB[b_str_idx++] = '_';
          r = M[row_up + b_idx];
        }
        else {
          a_idx++;
          alignedA[a_str_idx++] = '_';
          alignedB[b_str_idx++] = SEQB[b_idx];
          r = M[row_up + b_idx + 1];
        }
      }
    }
    alignedA[a_str_idx] = 0;
    alignedB[b_str_idx] = 0;
    */
}