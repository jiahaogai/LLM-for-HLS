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
  for (j = 1 + 32 - 1;j-- > 0 + 1;) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1;k-- > 0 + 1;) {
      k_col = k * 32;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32 - 1;i-- > 0 + 1;) {
        i_col = i * 32;
        idx = i_col + k_col;
        idx_col = k_col + i_col;
        t = C0 * (orig[idx] + orig[idx + 1] + orig[idx + 32] + orig[idx + 33]);
        t += C1 * (orig[idx_col] + orig[idx_col + 1] + orig[idx_col + 32] + orig[idx_col + 33]);
        sol[idx] = t;
      }
    }
  }
}