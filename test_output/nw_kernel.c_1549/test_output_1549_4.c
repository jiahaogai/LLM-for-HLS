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
  int a_row_end;
  int a_row_start;
  int b_row_end;
  int b_row_start;
  int a_col_end;
  int a_col_start;
  int b_col_end;
  int b_col_start;
  int ptr_row_end;
  int ptr_row_start;
  int m_row_end;
  int m_row_start;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_zero:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  row_up:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_row_end = ((a_idx == 63) ? 64 : a_idx + 1);
    a_row_start = a_idx + 1;
    b_row_end = 64;
    b_row_start = 0;
    ptr_row_end = a_idx;
    ptr_row_start = ((a_idx == 0) ? 0 : ptr_row_end - 1);
    m_row_end = a_idx + 1;
    m_row_start = ((a_idx == 0) ? 0 : a_idx);
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    row_left:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      a_col_end = ((b_idx == 63) ? 64 : b_idx + 1);
      a_col_start = b_idx + 1;
      b_col_end = b_idx + 1;
      b_col_start = ((b_idx == 0) ? 0 : b_col_end - 1);
      score = ((a_idx == 0) ? 0 : ((b_idx == 0) ? 0 : M[m_row_start * 64 + b_col_start]));
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      d_up:
      for (r = a_row_start; r < a_row_end; r++) {
        row = r * 64;
        row_up = (r - 1) * 64;
        up_left = M[row_up * 64 + b_col_start];
        up = M[row_up * 64 + b_idx];
        left = M[row * 64 + b_col_start];
        max = (up_left > up ? up_left : up);
        max = (left > max ? left : max);
        if (a_idx == 0 && b_idx == 0) {
          M[row * 64 + b_idx] = max;
        }
        else {
          M[row * 64 + b_idx] = max + score;
        }
      }
    }
  }
}