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
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
    int _in_j = 0 + 1 * 32 + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 0; k < 33 - 1 + 0; k++) {
      int _in_k = _in_j + 1 * 32 + k;
      k_col = _in_k - 1 * 32;
      row_up = _in_k - 32;
      row_down = _in_k + 32;
      col_up = _in_k - 1;
      col_down = _in_k + 1;
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loopk_col:
      for (k_col = col_up; k_col < col_down; k_col++) {
        t += orig[k_col] * filter[k - 1];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      looprow_up:
      for (row = row_up; row < row_down; row++) {
        t += orig[row * 32 + col_down] * filter[k];
        t -= orig[row * 32 + col_up] * filter[k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      looprow_down:
      for (row = row_down; row < row_up; row++) {
        t += orig[row * 32 + col_down] * filter[k];
        t -= orig[row * 32 + col_up] * filter[k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_down:
      for (k_col = col_down; k_col > col_up; k_col--) {
        t -= orig[k_col] * filter[k - 1];
      }
      
      sol[_in_k] = t;
    }
  }
}