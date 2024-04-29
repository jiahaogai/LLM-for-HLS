Code: #pragma ACCEL kernel

void kernel_stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 256 + 1;j++) {...} */
  for (j = 1; j <= 256; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      int k_col_int = k_col;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_row:
      for (k_row = 0; k_row < 8; k_row++) {
        int k_row_int = k_row;
        int k = k_row * 8 + k_col;
        double in = orig[i * 256 + j];
        sum = 0.0;
        loopk:
        for (k = 0; k < 9; k++) {
          sum += in * filter[k];
        }
        sol[i * 256 + j] = sum;
      }
    }
  }
}