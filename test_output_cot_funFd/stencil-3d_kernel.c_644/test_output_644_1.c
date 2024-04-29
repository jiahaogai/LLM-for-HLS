#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1; j <= 32; j++) {
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1;k++) {...} */
    for (k = 1; k <= 32; k++) {
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1;i++) {...} */
      for (i = 1; i <= 32; i++) {
        i_col = i - 1;
        k_col = (k - 1) * 32;
        idx = i_col + k_col;
        tmp = C0 * (orig[idx + 32] + orig[idx - 32]) + C1 * (orig[idx + 1] + orig[idx - 1]);
        sol[idx] = tmp;
      }
    }
  }
}