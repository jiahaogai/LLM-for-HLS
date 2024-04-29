#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        i_row = i - 1L;
        j_row = j - 1L;
        k_row = k - 1L;
        idx_row = i_row * 32L + j_row * 32L * 32L + k_row;
        loop_k_col:
/* Standardize from: for(k_col = k - 1; k_col >= 0; k_col--) {...} */
        for (k_col = k - 1L; k_col >= 0L; k_col--) {
          loop_j_col:
/* Standardize from: for(j_col = j - 1; j_col >= 0; j_col--) {...} */
          for (j_col = j - 1L; j_col >= 0L; j_col--) {
            loop_i_col:
/* Standardize from: for(i_col = i - 1; i_col >= 0; i_col--) {...} */
            for (i_col = i - 1L; i_col >= 0L; i_col--) {
              idx_col = i_col * 32L + j_col * 32L * 32L + k_col;
              t = orig[idx_col];
              idx = idx_row * 36L + idx_col;
              sol[idx] = t;
            }
          }
        }
      }
    }
  }
}