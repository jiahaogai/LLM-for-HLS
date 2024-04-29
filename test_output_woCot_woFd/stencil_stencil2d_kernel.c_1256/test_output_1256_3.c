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
/* Standardize from: for(k_col = 0; k_col < 32; k_col++) {...} */
    for (k_col = 0; k_col <= 31; k_col++) {
      int _in_k_col = 0 + 32L * k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_row:
/* Standardize from: for(k_row = 0; k_row < 3; k_row++) {...} */
      for (k_row = 0; k_row <= 2; k_row++) {
        int _in_k_row = 0 + 3L * k_row;
        row_up = _in_j - 1 + _in_k_row;
        row_down = _in_j + 1 + _in_k_row;
        col_up = _in_k_col - 1;
        col_down = _in_k_col + 1;
        row = _in_j + _in_k_row;
        col = _in_k_col + _in_k_row;
        temp = 0;
        loopk:
#pragma ACCEL PARALLEL FACTOR=auto{9}
	for (k = 0; k < 9; k++) {
          mul = filter[k] * orig[row_up + ((col_up + k) % 32)];
          temp += mul;
        }
        sol[row + col] = temp;
      }
    }
  }
}