#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        idx = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_col = i - 1L + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_row = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L - 32L * 32L;
        t = C0 * (orig[idx_col + 32L * idx_row] - 2L * orig[idx] + orig[idx_col - 32L * idx_row]);
        t += C1 * (orig[idx_col + 1L] - orig[idx_col - 1L] + orig[idx_row + 32L] - orig[idx_row - 32L]);
        sol[idx] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loopk_1:
/* Standardize from: for(k = 32 + 1 - 3; k < 32 + 1; k++) {...} */
  for (k = 32L + 1L - 3L; k < 32L + 1L; k++) {
     loopj_1:
/* Standardize from: for(j = 32 + 1 - 3; j < 32 + 1; j++) {...} */
    for (j = 32L + 1L - 3L; j < 32L + 1L; j++) {
      loopi_1:
/* Standardize from: for(i = 32 + 1 - 3; i < 32 + 1; i++) {...} */
      for (i = 32L + 1L - 3L; i < 32L + 1L; i++) {
        idx = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_col = i - 1L + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_row = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L - 32L * 32L;
        t = C0 * (orig[idx_col + 32L * idx_row] - 2L * orig[idx] + orig[idx_col - 32L * idx_row]);
        t += C1 * (orig[idx_col + 1L] - orig[idx_col - 1L] + orig[idx_row + 32L] - orig[idx_row - 32L]);
        sol[idx] = t;
      }
    }
  }
}