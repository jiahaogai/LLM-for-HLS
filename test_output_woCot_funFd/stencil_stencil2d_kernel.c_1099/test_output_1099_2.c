#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  loopj:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 0 + 1; j < 33 + 1 - 1; j++) {
    int _in_j = 0 + 1 + j;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 33;k_col++) {...} */
    for (k_col = 0 + 1; k_col < 33 + 1 - 1; k_col++) {
      int _in_k_col = 0 + 1 + k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 33;i_col++) {...} */
      for (i_col = 0 + 1; i_col < 33 + 1 - 1; i_col++) {
        int _in_i_col = 0 + 1 + i_col;
        sum = 0.0;
        loopk:
/* Standardize from: for(k = 0;k < 3;k++) {...} */
        for (k = 0; k < 3; k++) {
          int _in_k = 0 + k;
          sum += filter[k] * orig[(_in_k_col - 1 + (30 + 1 - 1) * (_in_k - 1))];
        }
        sol[(_in_j - 1 + (30 + 1 - 1) * (_in_i_col - 1))] = sum;
      }
    }
    loopk_col_end:
    k_col = 0 + 33 + 1 - 1;
  }
  loopj_end:
  j = 0 + 33 + 1 - 1;
}