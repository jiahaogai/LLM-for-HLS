#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row_start;
  int row_end;
  int row_mid;
  int col_start;
  int col_end;
  int col_mid;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 81;j++) {...} */
  for (j = 1; j < 81; j++) {
    int _in_j = 0 + 80L * (j - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    /* Standardize from: for(k_col = 1;k_col < 9;k_col++) {...} */
    for (k_col = 1; k_col < 9; k_col++) {
      int _in_k_col = (0 + 80L * (k_col - 1)) + _in_j;
      mul = filter[k_col - 1];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      /* Standardize from: for(k = j - 1;k <= j + 1;k++) {...} */
      for (k = j - 1; k <= j + 1; k++) {
        int _in_k = 0 + 80L * (k - 1);
        sol[_in_j] += mul * orig[_in_k * 80 + _in_k_col];
      }
    }
  }
}