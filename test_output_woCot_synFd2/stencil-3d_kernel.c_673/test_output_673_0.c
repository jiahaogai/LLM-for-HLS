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
  for (j = 1 + 32 - 1; j-- > 1; ) {
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1; k-- > 1; ) {
      k_col = (32 + 1) * k;
       i_col = (32 + 1) * i;
      idx_col = k_col + i_col;
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
       loopi:
      for (idx = idx_col + 1; idx < idx_col + (32 + 1) - 1; idx++) {
        t = orig[idx] + C0 * (orig[idx - 1] + orig[idx + 1]) + C1 * (orig[idx_col + 32 - 1] + orig[idx_col + 32]);
        sol[idx] = t;
      }
    }
  }
}