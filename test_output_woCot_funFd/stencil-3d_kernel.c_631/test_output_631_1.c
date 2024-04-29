#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long h;
  long pad_sol;
  long pad_orig;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32L; j <= 32L + 32L; j++) {
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32L; k <= 32L + 32L; k++) {
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32L; i <= 32L + 32L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        pad_sol = i_col + (32L + 1L - 3L) * (j_col + (32L + 1L - 3L) * (k_col));
        pad_orig = i_col + (1L + 3L - 1L) * (j_col + (1L + 3L - 1L) * (k_col));
        sol[pad_sol] = ((2L * orig[pad_orig]) + (orig[pad_orig + 1L] + orig[pad_orig - 1L]) + (orig[pad_orig + (32L + 1L - 1L)] + orig[pad_orig - (32L + 1L - 1L)]) + (orig[pad_orig + 32L * (32L + 1L - 1L)] + orig[pad_orig - 32L * (32L + 1L - 1L)])) / 4L;
      }
    }
  }
}