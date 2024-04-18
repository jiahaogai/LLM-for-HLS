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
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_str_idx = a_idx * 64;
    loop_col:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      b_str_idx = b_idx * 64;
      up_left = ((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx])?1:- 1;
//#pragma ACCEL PARALLEL FACTOR=auto{1}
      
#pragma ACCEL PIPELINE auto{off}
      loop_up:
      for (r = 1; r < 64; r++) {
        row_up = a_str_idx + (r * 64);
        up = ((int )SEQA[row_up]) == ((int )SEQB[b_str_idx])?1:- 1;
        max = (M[row_up * 64] + up) > (M[r * 64 + b_idx] + left)?(M[row_up * 64] + up):(M[r * 64 + b_idx] + left);
        M[r * 64 + b_idx] = max;
        ptr[max + r * 64 + b_idx] = row_up;
      }
//#pragma ACCEL PARALLEL FACTOR=auto{1}
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      loop_left:
      for (r = 1; r < 64; r++) {
        row = r * 64 + b_idx;
        left = M[row] + up_left;
        M[row] = left;
        ptr[left + row] = row + b_idx;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = (64 * 64) - 1;
  a_idx = 0;
  b_idx = 0;
  trace:
  while (row != 0) {
    b_idx = row % 64;
    a_idx = row / 64;
    score = M[row];
    up = ptr[score + a_idx * 64 + b_idx];
    left = ptr[score + b_idx];
    if (up > left) {
      if (up > 0) {
        row = up;
        alignedA[a_idx] = SEQA[row];
        alignedB[a_idx] = SEQB[row - a_idx * 64];
      }
    }
     else {
      if (left > 0) {
        row = left;
        alignedA[a_idx] = SEQA[row];
        alignedB[a_idx] = SEQB[row - a_idx * 64];
      }
    }
  }
  alignedA[a_idx] = SEQA[row];
  alignedB[a_idx] = SEQB[row - a_idx * 64];
}