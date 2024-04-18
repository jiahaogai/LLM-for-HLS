c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (a_idx = 64; a_idx < 128; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    a_str_idx = (a_idx << 4);
    b_str_idx = (64 << 4);
    a_str_idx_p1 = a_str_idx + 1;
    b_str_idx_p1 = b_str_idx + 1;
    up_left = M[b_str_idx + a_idx - 1];
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_out_a:
    for (b_idx = 64; b_idx < 48; b_idx++) {
      b_str_idx = (b_idx << 4);
      b = SEQB[b_str_idx + a_idx - 1];
      up = M[b_str_idx + a_idx] + 1;
      left = M[b_str_idx + a_idx - 1] + 1;
      score = (up_left > up) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
      M[b_str_idx + a_idx] = score;
      ptr[b_str_idx + a_idx] = ((score == up_left) ? 2 : ((score == up) ? 1 : 0));
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_out_b:
    for (b_idx = 48; b_idx < 64; b_idx++) {
      b_str_idx = (b_idx << 4);
      b = SEQB[b_str_idx + a_idx - 1];
      up = M[b_str_idx + a_idx] + 1;
      left = M[b_str_idx + a_idx - 1] + 1;
      score = (up_left > up) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
      M[b_str_idx + a_idx] = score;
      ptr[b_str_idx + a_idx] = ((score == up_left) ? 2 : ((score == up) ? 1 : 0));
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  fill_in:
  for (a_idx = 63; a_idx >= 1; a_idx--) {
    a_str_idx = (a_idx << 4);
    b_str_idx = (64 << 4);
    a_str_idx_p1 = a_str_idx + 1;
    b_str_idx_p1 = b_str_idx + 1;
    up_left = M[b_str_idx + a_idx - 1];
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    fill_in_a:
    for (b_idx = 64; b_idx < 48; b_idx++) {
      b_str_idx = (b_idx << 4);
      b = SEQB[b_str_idx + a_idx - 1];
      up = M[b_str_idx + a_idx] + 1;
      left = M[b_str_idx + a_idx - 1] + 1;
      score = (up_left > up) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
      M[b_str_idx + a_idx] = score;
      ptr[b_str_idx + a_idx] = ((score == up_left) ? 2 : ((score == up) ? 1 : 0));
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    fill_in_b:
    for (b_idx = 48; b_idx >= 1; b_idx--) {
      b_str_idx = (b_idx << 4);
      b = SEQB[b_str_idx + a_idx - 1];
      up = M[b_str_idx + a_idx] + 1;
      left = M[b_str_idx + a_idx - 1] + 1;
      score = (up_left > up) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
      M[b_str_idx + a_idx] = score;
      ptr[b_str_idx + a_idx] = ((score == up_left) ? 2 : ((score == up) ? 1 : 0));
    }
    b_str_idx = 0;
    b = SEQB[b_str_idx + a_idx - 1];
    up = M[b_str_idx + a_idx] + 1;
    left = M[b_str_idx + a_idx - 1] + 1;
    score = (up_left > up) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
    M[b_str_idx + a_idx] = score;
    ptr[b_str_idx + a_idx] = ((score == up_left) ? 2 : ((score == up) ? 1 : 0));
  }
  b_idx = 0;
  a_idx = 0;
  r = 0;
  row = 0;
  row_up = 1;
  a_str_idx = 0;
  b_str_idx = 0;
  a = SEQA[a_idx];
  b = SEQB[b_idx];
  while (