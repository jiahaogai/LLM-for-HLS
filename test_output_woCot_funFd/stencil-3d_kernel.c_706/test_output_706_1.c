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
    for (k = 1 + 32 - 1; k < 32 + 1 - 3; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 3; i++) {
        k_col = (32 + 1) * (k - 1) + 1;
        i_col = (32 + 1) * (i - 1) + 1;
        idx = i_col + k_col;
        idx_col = i_col + 1 + k_col;
        t = orig[idx_col + 1] + orig[idx_col + 32 + 1] + orig[idx_col + 32 + 32 + 1] + orig[idx_col + 32] + orig[idx] + orig[idx + 32] + orig[idx + 32 + 32] + orig[idx_col - 1] + orig[idx_col - 32 - 1] + orig[idx_col - 32] + orig[idx_col - 1 + 32] + orig[idx_col + 32 - 1];
        sol[idx] = t;
      }
    }
  }
}