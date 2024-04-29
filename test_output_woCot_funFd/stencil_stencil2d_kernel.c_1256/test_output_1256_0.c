#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 0; j < 32; j++) {...} */
  for (j = 0; j <= 31; j++) {
    int _in_j = 0 + 32L * j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 0; k_col < 9; k_col++) {...} */
    for (k_col = 0; k_col <= 8; k_col++) {
      int _in_k_col = filter[k_col];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_row:
/* Standardize from: for(k_row = 0; k_row < 9; k_row++) {...} */
      for (k_row = 0; k_row <= 8; k_row++) {
        int _in_k_row = filter[k_row];
        row_up = _in_j - 1 + ((k_row - 4) * 32);
        row_down = _in_j + 1 + ((k_row - 4) * 32);
        col_up = _in_j - 1 + ((k_col - 4) * 32);
        col_down = _in_j + 1 + ((k_col - 4) * 32);
        row = _in_j + ((k_row - 4) * 32);
        col = _in_j + ((k_col - 4) * 32);
        if (((row_up >= 0) && (row_up < 8192)) && ((col_up >= 0) && (col_up < 8192))) {
          temp = orig[row_up * 8192 + col_up];
        }
         else {
          temp = 0;
        }
        mul = temp * _in_k_row;
        if (((row_down >= 0) && (row_down < 8192)) && ((col_down >= 0) && (col_down < 8192))) {
          temp = orig[row_down * 8192 + col_down];
        }
         else {
          temp = 0;
        }
        mul += temp * _in_k_col;
        sol[row * 8192 + col] = mul;
      }
    }
  }
}