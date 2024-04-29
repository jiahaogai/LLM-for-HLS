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
  long R = 32;
  long Q = 32;
  long P = 32;
  long pad_sz = 1;
  long orig_idx = 0;
  long sol_idx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32;j-- > 1 + 32 - 1;) {
    long j_col_min = j - 1 - 1 + 0 * 32;
    long j_col_max = j - 1 - 1 + 31 * 32;
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32;k-- > 1 + 32 - 1;) {
      long k_col_min = k - 1 - 1 + 0 * 32;
      long k_col_max = k - 1 - 1 + 31 * 32;
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32;i-- > 1 + 32 - 1;) {
        long i_col = i - 1 - 1 + (j - 1 - 1) * 32 + (k - 1 - 1) * 2 * 32;
        idx = i + 1 + 32 * (j + 1 + 32 * (k + 1 - 1));
        idx_col = i_col;
        sol[idx] = ((C0 * orig[idx_col]) + (C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + 32] + orig[idx_col - 32] + orig[idx_col + 32 * 32] + orig[idx_col - 32 * 32]))) / (R * Q * P);
      }
    }
  }
}