#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
     loopk_col:
/* Standardize from: for(k_col = 1;k_col < 32 + 1 - 3;k_col++) {...} */
    for (k_col = 1 + 32 - 3; k_col < 32 + 1 - 1; k_col++) {
      i_col = 1 + 32 - 3 - k_col;
      s = C0 * (orig[i_col + 39073 * (j + 32 * (k_col - 1))]);
       loopki:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
      for (k = 1 + 32 - 1; k < 32 + 1; k++) {
        idx = i_col + 39073 * (j + 32 * (k - 1));
        s += C1 * (orig[idx] + orig[idx + 39073]);
      }
      sol[idx] = s;
    }
  }
}