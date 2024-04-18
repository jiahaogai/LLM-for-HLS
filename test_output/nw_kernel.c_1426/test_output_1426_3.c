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
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    M[a_idx] = ((int )alignedA[a_idx]) * ((int )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    M[b_idx] = ((int )alignedB[b_idx]) * ((int )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 4; b_idx < 128 - 4; b_idx++) {
    alignedB[b_idx + 0] = SEQB[b_idx + 0];
    alignedB[b_idx + 1] = SEQB[b_idx + 1];
    alignedB[b_idx + 2] = SEQB[b_idx + 2];
    alignedB[b_idx + 3] = SEQB[b_idx + 3];
    alignedB[b_idx + 4] = SEQB[b_idx + 4];
    a_idx_up = 0 + 5 * (b_idx + 0);
    b_idx_up = 0 + 5 * (b_idx + 0);
    a_idx_left = 5 * (b_idx + 0);
    b_idx_left = 5 * (b_idx + 0);
    row_up = 0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_row:
    for (a_idx = 4; a_idx < 128 - 4; a_idx++) {
      a_idx_up = a_idx + 5 * (b_idx + 0);
      b_idx_up = b_idx + 5 * (a_idx + 0);
      a_idx_left = 5 * (b_idx + 0) + a_idx;
      b_idx_left = 5 * (a_idx + 0) + b_idx;
      a = alignedA[a_idx + 0];
      b = alignedB[b_idx + 0];
      row = M[a_idx_up] + ((int )b);
      up_left = M[a_idx_left] + ((int )a);
      up = M[a_idx_up + 5] + ((int )a);
      left = M[b_idx_left] + ((int )b);
      max = (row > left? ((row > up? row : up)) : ((left > up? left : up)));
      score = ((int )0);
      if (max == row) {
        a = alignedA[a_idx + 1];
        b = alignedB[b_idx + 1];
        score = row_up + ((int )b);
        ptr[a_idx_left + 1] = 5 + ((int )b_idx);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == left) {
        score = left_up + ((int )a);
        ptr[b_idx_left + 1] = 10 + ((int )a_idx);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      if (max == up) {
        a = alignedA[a_idx + 1];
        b = alignedB[b_idx + 1];
        score = up_left + ((int )(a * b));
        ptr[a_idx_up + 1] = 15 + b_idx_left;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      if (max == up_left) {
        score = up_left;
        ptr[a_idx_up + 1] = 15 + b_idx_left;
      }
      M[a_idx_up + 5] = up;
      row_up = row;
      left_up = left;
    }
    alignedB[b_idx + 5] = SEQB[b_idx + 5];
    alignedB[b_idx + 6] = SEQB[b_idx + 6];
    alignedB[b_idx + 7] = SEQB[b_idx + 7];
  }
  alignedB[b_idx_col + 4] = SEQB[b_idx_col + 4];
  alignedB[b_idx_col + 5] = SEQB[b_idx_col + 5];
  b_idx_col += 5;
  a_idx_col += 5;
}