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
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32;j >= 32 + 1;j--) {
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32;k >= 32 + 1;k--) {
      k_col = ((32 + 1) * (k - 1)) + 1;
       i_col = ((32 + 1) * (j - 1)) + 1;
       idx = k_col - 1 + 32 * i_col;
      tmp = C0 * (orig[idx] + orig[idx + 1] + orig[idx + 32] + orig[idx + 32 + 1]) + C1 * (orig[idx + 1 + 32] + orig[idx + 32 + 1]);
      sol[idx] = tmp;
    }
  }
}