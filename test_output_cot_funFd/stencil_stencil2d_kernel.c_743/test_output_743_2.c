#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int orig_row_up;
  int orig_row_down;
  int orig_col_up;
  int orig_col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8188; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      k = k_col + 1;
      row = j - 1 + (-1 + k);
      col = k - 1;
      orig_row_up = row + 1;
      orig_row_down = row - 1;
      orig_col_up = col + 1;
      orig_col_down = col - 1;
      sol[j] += filter[k_col] * orig[orig_row_up * 8192 + orig_col_up];
      sol[j] += filter[k_col] * orig[orig_row_up * 8192 + orig_col_down];
      sol[j] += filter[k_col] * orig[orig_row_down * 8192 + orig_col_up];
      sol[j] += filter[k_col] * orig[orig_row_down * 8192 + orig_col_down];
    }
  }
}