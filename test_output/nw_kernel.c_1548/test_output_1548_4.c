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
  int a_row_end;
  int b_row_end;
  int a_col_end;
  int b_col_end;
  int a_row;
  int b_row;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_row = 0; a_row < 64; a_row++) {
    alignedA[a_row * 64] = SEQA[a_row];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_col:
  for (b_row = 0; b_row < 64; b_row++) {
    alignedB[b_row * 64] = SEQB[b_row];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  row_init:
  for (a_row = 0; a_row < 64 - 1; a_row++) {
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    row_init_a:
    for (a_col = 0; a_col < 64 - 1; a_col++) {
      a_idx = a_row * 64 + a_col;
      b_idx = a_idx + 1;
      a_idx_up = a_idx + 64;
      b_idx_up = a_idx_up + 1;
      a = alignedA[a_idx];
      b = alignedB[b_idx];
      up_left = M[a_idx_up * 64 + b_idx_up] + ((int )a == (int )b?1 : 0);
      up = M[a_idx_up * 64 + b_idx] + 1;
      left = M[a_idx * 64 + b_idx_up] + 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_idx * 64 + b_idx] = max;
      if (max == left) {
        ptr[a_idx * 64 + b_idx] = 3;
      }
      
      else
      if (max == up) {
        ptr[a_idx * 64 + b_idx] = 2;
      }
      
      else
      if (max == up_left) {
        ptr[a_idx * 64 + b_idx] = 1;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  row:
  for (a_row = 0; a_row < 64 - 1; a_row++) {
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    row_a:
    for (a_col = 0; a_col < 64 - 1; a_col++) {
      a_idx = (a_row + 1) * 64 + a_col + 1;
      b_idx = a_idx + 1;
      a_idx_up = a_idx - 64;
      b_idx_up = a_idx_up + 1;
      a_idx_left = a_idx - 1;
      b_idx_left = a_idx_left + 1;
      a_row_end = ((int )alignedA[a_idx] == 4?1 : 0);
      b_row_end = ((int )alignedB[b_idx] == 4?1 : 0);
      a_col_end = ((int )alignedA[a_idx] == 4?1 : 0);
      b_col_end = ((int )alignedB[b_idx] == 4?1 : 0);
      a = alignedA[a_idx_left];
      b = alignedB[b_idx_left];
      up_left = M[a_idx_up * 64 + b_idx_up] + a_row_end + b_row_end;
      up = M[a_idx_up * 64 + b_idx] + a_row_end + b_col_end;
      left = M[a_idx * 64 + b_idx_up] + a_col_end + b_row_end;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      score = ((int )alignedA[a_idx] == (int )alignedB[b_idx]?1 : 0);
      M[a_idx * 64 + b_idx] = max;
      if (max == left) {
        ptr[a_idx * 64 + b_idx] = 3;
      }
      
      else
      if (max == up) {
        ptr[a_idx * 64 + b_idx] = 2;
      }
      
      else
      if (max == up_left) {
        ptr[a_idx * 64 + b_idx] = 1;
      }
    }
  }
}