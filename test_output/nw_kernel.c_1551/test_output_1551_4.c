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
  char a_char;
  char b_char;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = -1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_idx_up = a_idx * 5;
      b_idx_up = b_idx * 5;
      a_char = SEQA[a_idx];
      b_char = SEQB[b_idx];
      score = ((int )a_char) * ((int )b_char);
      up_left = M[a_idx_up + b_idx] + ((int )b_char);
      up = M[a_idx_up + b_idx_up] + ((int )a_char);
      left = M[a_idx + b_idx_up] + ((int )b_char);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_idx_up + b_idx_up] = max;
      if (max == left) {
        ptr[a_idx_up + b_idx_up] = 2;
      }
      
      if (max == up) {
        ptr[a_idx_up + b_idx_up] = 1;
      }
      
      if (max == up_left) {
        ptr[a_idx_up + b_idx_up] = 0;
      }
    }
  }
// TraceBack
  row = 26;
  b_idx = 4;
  a_idx = 4;
  a_idx_left = a_idx + 1;
  b_idx_left = b_idx + 1;
  a_idx_up = a_idx;
  b_idx_up = b_idx;
/*
    traceBack: while(a_idx > 0 || b_idx > 0) {
      if (b_idx == 0) {
        a_idx_left = a_idx + 1;
        b_idx_left = b_idx + 1;
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
      else if (a_idx == 0) {
        a_idx_left = a_idx + 1;
        b_idx_left = b_idx + 1;
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
      else if (M[a_idx_left * 5 + b_idx_left] > max(M[a_idx_left * 5 + b_idx],M[a_idx * 5 + b_idx_left])) {
        a_idx_left = a_idx_up + 1;
        b_idx_left = b_idx_up;
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
      else if (M[a_idx_left * 5 + b_idx_left] > max(M[a_idx * 5 + b_idx_left],M[a_idx_left * 5 + b_idx])) {
        a_idx_left = a_idx_up;
        b_idx_left = b_idx_up + 1;
        a_idx = a_idx_up;
        b_idx = b_idx_up;
      }
      else if (M[a_idx_left * 5 + b_idx_left] == M[a_idx * 5 + b_idx]) {
        a_idx_left = a_idx_up;
        b_idx_left = b_idx_up;
        a_idx = a_idx_up - 1;
        b_idx = b_idx_up - 1;
      }
      else if (M[a_idx_left * 5 + b_idx_left] == M[a_idx * 5 + b_idx_left]) {
        a_idx_left = a_idx_up;
        b_idx_left = b_idx_up;
        a_idx = a_idx_up - 1;
        b_idx = b_idx_up;
      }
      else if (M[a_idx_left * 5 + b_idx_left] == M[a_idx_left * 5 + b_idx]) {
        a_idx_left = a_idx_up - 1;
        b_idx_left = b_idx_up;
        a_idx = a_idx_up;
        b_idx = b_idx_up - 1;
      }
      else {
        a_idx_left = a_idx_up;
        b_idx_left = b_idx_up;
        a_idx = a_idx_up - 1;
        b_idx = b_idx_up - 1;
      }
      a_idx_up = a_idx;
      b_idx_up = b_idx;
      row = ((a_idx * 5) + b_idx) + 1;
    }
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace: while(a_idx_up != 0 || b_idx_up != 0) {
    row_up = (a_idx_up * 5) + b_idx_up;
    if (ptr[row_up] == 0) {
      alignedA[row] = SEQA[a_idx_up];
      alignedB[row] = SEQB[b_idx_up];
      a_idx = a_idx_up;
      b_idx = b_idx_up;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    if (ptr[