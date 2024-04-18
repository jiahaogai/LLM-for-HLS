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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_score:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx + 6] = SEQB[b_idx];
    M[b_idx] = 0 - b_idx;
  }
  M[0] = 0;
  alignedB[12] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx << 4;
    b_str_idx = 0;
    b_idx = 0;
    row = a_idx << 5;
    up_left = M[b_idx];
    
#pragma ACCEL PIPELINE auto{__PIPE__L0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    col_init:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx << 4;
      score = (a_idx == 0) ? ((b_idx == 0) ? 0 : 0 - b_idx) : (b_idx == 0) ? 0 - a_idx : 0 - a_idx + b_idx;
      M[row + b_idx] = score + ((int )SEQA[a_str_idx + 0] == (int )SEQB[b_str_idx + 0] ? 1 : (((int )SEQA[a_str_idx + 0] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 0] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 0] == (int )'C') ? -5 : -3)));
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx << 4;
    b_str_idx = 0;
    row = (a_idx + 1) << 5;
    up_left = M[b_str_idx + 0] + ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 4] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3));
    up = M[b_str_idx + 1] + ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 3] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3));
    max = (up_left > ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 5] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3))) ? (up_left) : ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 5] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3));
    b_idx = 1;
    row_up = a_idx << 5;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    col:
    for (b_idx = 1; b_idx < 5; b_idx++) {
      b_str_idx = b_idx << 4;
      up_left = M[b_str_idx + 0] + ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 4] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3));
      up = M[b_str_idx + 1] + ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 3] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T') ? -4 : ((int )SEQA[a_str_idx + 4] == (int )'C') ? -5 : -3));
      max = (up_left > up ? up_left : up);
      max = (max > ((int )SEQA[a_str_idx + 4] == (int )SEQB[b_str_idx + 5] ? 1 : (((int )SEQA[a_str_idx + 4] == (int )'A') ? -6 : ((int )SEQA[a_str_idx + 4] == (int )'T