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
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32 - 1; j-- > 0 + 1 - 1; ) {
    long j_col;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1; k-- > 0 + 1 - 1; ) {
      long k_col_idx_col;
      long i_col_idx;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32 - 1; i-- > 0 + 1 - 1; ) {
        i_col = i - 1 + ((j - 1) * (32L + -1L)) + ((k - 1) * ((32L + -1L) * (32L + -1L)));
        idx = i + ((j * (32L + -1L)) + (k * ((32L + -1L) * (32L + -1L)))) - 1;
        t = ((C0 * (orig[idx - 1 - 1 - 1] + orig[idx - 1 + 0 - 1] + orig[idx - 1 + 1 - 1] + orig[idx + 0 - 1] + orig[idx + 0 + 0] + orig[idx + 0 + 1] + orig[idx + 1 - 1] + orig[idx + 1 + 0] + orig[idx + 1 + 1])) / (C1 + 1L)) + orig[idx];
        sol[idx] = t;
      }
    }
    k_col = 32L + -1L;
    loopk_col:
/* Standardize from: for(k_col = 32 - 1;k_col >= 0 + 1 - 1;k_col--) {...} */
    for (k_col = 32 - 1; k_col >= 0 + 1 - 1; k_col--) {
      i_col = 32L + -1L;
      loopi_col:
/* Standardize from: for(i_col = 32 - 1;i_col >= 0 + 1 - 1;i_col--) {...} */
      for (i_col = 32 - 1; i_col >= 0 + 1 - 1; i_col--) {
        idx_col = i_col + (j * 32L) + (k_col * (32L * 32L));
        idx = i_col + 1 + ((j * (32L + -1L)) + (k_col * ((32L + -1L) * (32L + -1L)))) - 1;
        t = sol[idx_col];
        sol[idx_col] = t;
      }
    }
  }
}