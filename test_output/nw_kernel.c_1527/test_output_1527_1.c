#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    alignedB[b_idx] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = ((5 * a_idx) - 1);
      b_str_idx = ((5 * b_idx) - 1);
      a_str_idx_p1 = ((5 * a_idx) - 1) + 1;
      b_str_idx_p1 = ((5 * b_idx) - 1) + 1;
      a = (SEQA[a_str_idx]);
      b = (SEQB[b_str_idx]);
      up_left = M[(b_str_idx_p1 - 1)] + ((a == b) ? 1 : (-1));
      up = M[(b_str_idx_p1)] + (-1);
      left = M[(a_str_idx_p1)] + (-1);
      u = up_left;
      l = left;
      if (u < up) {
        u = up;
      }
      if (u < left) {
        u = left;
      }
      if (l < up) {
        l = up;
      }
      if (l < up_left) {
        l = up_left;
      }
      score = u;
      row_up = (b_str_idx_p1 - 1);
      row = b_str_idx_p1;
      max = M[row_up * 5 + a_idx];
      if (score > max) {
        max = score;
        ptr[row_up * 5 + a_idx] = 2;
      }
      else {
        ptr[row_up * 5 + a_idx] = 0;
      }
      M[row * 5 + a_idx] = score;
      score = l;
      row_up = (a_str_idx_p1 - 1);
      row = a_str_idx_p1;
      max = M[row_up * 5 + b_idx];
      if (score > max) {
        max = score;
        ptr[row_up * 5 + b_idx] = 1;
      }
      else {
        ptr[row_up * 5 + b_idx] = 0;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 4;
  b_idx = 4;
  a_str_idx = ((5 * a_idx) - 1);
  b_str_idx = ((5 * b_idx) - 1);
  a = (SEQA[a_str_idx]);
  b = (SEQB[b_str_idx]);
  alignedA[a_idx] = a;
  alignedB[b_idx] = b;
  trace: while(a_idx > 0 || b_idx > 0){
//#pragma ACCEL PIPELINE auto{off}
    if (ptr[b_idx * 5 + a_idx] == 0) {
      a_idx--;
      b_idx--;
      a_str_idx = ((5 * a_idx) - 1);
      b_str_idx = ((5 * b_idx) - 1);
      a = (SEQA[a_str_idx]);
      b = (SEQB[b_str_idx]);
      alignedA[a_idx] = a;
      alignedB[b_idx] = b;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    else if (ptr[b_idx * 5 + a_idx] == 1) {
      a_idx--;
      b_str_idx = ((5 * b_idx) - 1);
      b = (SEQB[b_str_idx]);
      alignedA[a_idx] = '-';
      alignedB[b_idx] = b;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    else if (ptr[b_idx * 5 + a_idx] == 2) {
      b_idx--;
      a_str_idx = ((5 * a_idx) - 1);
      a = (SEQA[a_str_idx]);
      alignedA[a_idx] = a;
      alignedB[b_idx] = '-';
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    else if (ptr[b_idx * 5 + a_idx] == 3) {
      a_idx--;
      b_idx--;
      a_str_idx = ((5 * a_idx) - 1);
      b_str_idx = ((5 * b_idx) - 1);
      a = (SEQA[a_str_idx]);
      b = (SEQB[b_str_idx]);
      alignedA[a_idx] = a;
      alignedB[b_idx] = b;
    }
  }
}