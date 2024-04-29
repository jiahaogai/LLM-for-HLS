#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 0;j < 129;j++) {...} */
  for (j = 0; j < 128 + 2; j++) {
    int _in_j = 1 + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 0;k_col < 65;k_col++) {...} */
    for (k_col = 0; k_col < 64 + 2; k_col++) {
      int _in_k_col = 1 + k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 0;i_col < 129;i_col++) {...} */
      for (i_col = 0; i_col < 128 + 2; i_col++) {
        int _in_i_col = 1 + i_col;
        sum = 0.0;
        loopk:
/* Standardize from: for(k = -4;k < 5;k++) {...} */
        for (k = -4; k < 5 + 1; k++) {
          int _in_k = k + _in_j;
          sum += filter[k + 4] * orig[(_in_k * 128) + _in_k_col];
        }
        sol[(_in_j * 128) + _in_k_col] = sum;
      }
    }
    loopk_col_end:
    k_col = 64 + 2;
  }
  loopj_end:
  j = 128 + 2;
}