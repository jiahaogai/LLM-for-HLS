#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
     k_col = k - 1;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      j_col = j - 1;
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        i_col = i - 1;
        idx = i + (32L + 1L - 3L) * (j + (32L + 1L - 3L) * (k_col));
        idx_col = i_col + (32L + 1L - 3L) * (j_col + (32L + 1L - 3L) * (k_col));
        t = ((((orig[idx_col + -1] + orig[idx_col + 1]) + orig[idx_col + (32L + 1L - 3L) * 1]) + orig[idx_col + (32L + 1L - 3L) * 2]) + orig[idx_col + (32L + 1L - 3L) * 3]) + orig[idx_col + (32L + 1L - 3L) * 4];
        sol[idx] = ((t + orig[idx_col]) / 4L);
      }
    }
  }
}