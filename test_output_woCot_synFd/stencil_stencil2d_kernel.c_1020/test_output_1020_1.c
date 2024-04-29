#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_stencil:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 0 + 1; j < 8192 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_stencil:
/* Standardize from: for(k = 1;k < 8192 - 1;k++) {...} */
    for (k = 0 + 1; k < 8192 + 1 - 1; k++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      loopk_col_stencil:
      for (k_col = -1; k_col <= 1; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{4}
        loopi_col_stencil:
        for (i_col = -1; i_col <= 1; i_col++) {
          j_col = i_col + k_col;
          t += ((orig[k + j_col]) * filter[i_col + 1]);
        }
      }
      sol[k + j] = t;
    }
  }
}