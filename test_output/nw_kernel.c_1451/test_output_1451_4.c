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
  int score_row;
  int a_str_idx_col;
  int b_str_idx_col;
  int ptr_row;
  int temp;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    alignedB[b_idx] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      score_row = (b_idx) * 64;
      a_str_idx_col = (a_idx) * 1L;
      b_str_idx_col = (b_idx) * 1L;
      up_left = M[a_str_idx_col + b_str_idx_col] + ((int )SEQA[a_idx] == (int )SEQB[b_idx] ? 1L : 0L);
      up = M[a_str_idx_col + b_str_idx_col + 64] + ((int )SEQA[a_idx] == (int )'-' ? 1L : 0L);
      left = M[score_row + a_str_idx_col] + ((int )SEQB[b_idx] == (int )'-' ? 1L : 0L);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_str_idx_col + b_str_idx_col] = max;
      if (max == left) {
        ptr[a_str_idx_col + b_str_idx_col] = ((char )60);
        alignedA[a_idx + 1L] = SEQA[a_idx];
        alignedB[b_idx + 1L] = '-';
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (max == up) {
        ptr[a_str_idx_col + b_str_idx_col] = ((char )94);
        alignedA[a_idx + 1L] = '-';
        alignedB[b_idx + 1L] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == up_left) {
        temp = a_str_idx_col;
        a_str_idx_col = b_str_idx_col;
        b_str_idx_col = temp;
        temp = a_idx;
        a_idx = b_idx;
        b_idx = temp;
        ptr[a_str_idx_col + b_str_idx_col] = ((char )92);
        alignedA[a_idx + 1L] = SEQA[a_idx];
        alignedB[b_idx + 1L] = SEQB[b_idx];
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 63L;
  col = 63L;
  a_str_idx = ((long )64) - 1L;
  b_str_idx = ((long )64) - 1L;
  score = M[a_str_idx + b_str_idx];
  ptr_row = b_str_idx;
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace_out:
  while (1) {
//#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    trace_in:
    while (1) {
      if (ptr[ptr_row + ((long )64) - 1L] == 62) {
        row = row - 1L;
        b_str_idx = b_str_idx - 1L;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L7}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      if (ptr[ptr_row + ((long )64)] == 62) {
        col = col - 1L;
        a_str_idx = a_str_idx - 1L;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      if (ptr[ptr_row + ((long )64) + 1L] == 62) {
        row = row + 1L;
        b_str_idx = b_str_idx + 1L;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L9}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      if (ptr[ptr_row] == 62) {
        col = col + 1L;
        a_str_idx = a_str_idx + 1L;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L10}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      if (ptr[ptr_row - ((long )64)] == 94) {