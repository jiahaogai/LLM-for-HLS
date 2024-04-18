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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      a_str_idx = 64 * a_idx;
      b_str_idx = 64 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a = (char )SEQA[a_str_idx_p1];
      b = (char )SEQB[b_str_idx_p1];
      up_left = M[b_str_idx * 64 + a_str_idx] + ((int )a == (int )b?1 : - 1);
      up = M[(b_str_idx - 1) * 64 + a_str_idx] + - 1;
      left = M[b_str_idx * 64 + a_str_idx_p1] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx * 64 + a_str_idx] = max;
      row_up = b_str_idx * 64;
      if (max == left) {
        ptr[row_up + a_idx] = 2;
      }
      
      if (max == up) {
        ptr[row_up + a_idx] = 1;
      }
      
      if (max == up_left) {
        ptr[row_up + a_idx] = a_idx + b_idx;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 64 * 64 - 1;
  a_idx = 64 - 1;
  b_idx = 64 - 1;
  a_str_idx = 64 * a_idx;
  b_str_idx = 64 * b_idx;
  score = M[row];
  trace:
  while (1) {
    a_str_idx = 64 * a_idx;
    b_str_idx = 64 * b_idx;
    a_str_idx_p1 = a_str_idx + 1;
    b_str_idx_p1 = b_str_idx + 1;
    a = (char )SEQA[a_str_idx_p1];
    b = (char )SEQB[b_str_idx_p1];
    up_left = M[b_str_idx * 64 + a_str_idx] + ((int )a == (int )b?1 : - 1);
    up = M[(b_str_idx - 1) * 64 + a_str_idx] + - 1;
    left = M[b_str_idx * 64 + a_str_idx_p1] + - 1;
    r = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
    if (r == left) {
      b_idx--;
    }
    
    if (r == up) {
      a_idx--;
    }
    
    if (r == up_left) {
      a_idx--;
      b_idx--;
      score = score + 1;
      alignedA[a_idx] = a;
      alignedB[b_idx] = b;
    }
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
  }
}