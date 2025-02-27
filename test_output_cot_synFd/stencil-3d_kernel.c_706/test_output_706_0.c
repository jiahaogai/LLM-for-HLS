#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1 - 1; k++) {
      k_col = k - 1 + (32 - 1) * (1 + 32 - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 1; i++) {
        i_col = i - 1 + (32 - 1) * 0;
        idx = i + 32 * (k + 32 * j);
        idx_col = i_col + 32 * k_col;
        t = ((((0 + 1) * (orig[idx_col - 1] + orig[idx_col + 1])) + ((0 + 1) * (orig[idx_col - 32] + orig[idx_col + 32]))) + ((0 + 1) * (orig[idx_col - 32 * 32] + orig[idx_col + 32 * 32]))) / (4 * (0 + 1));
        sol[idx] = t;
      }
    }
  }
}