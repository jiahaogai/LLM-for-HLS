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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1;
     i_col = 32L + 1L - k_col;
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = j - 1;
      k_row = 32L + 1L - j_col;
      i_row = k_row - 1L;
       loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        idx_col = i_col * 32L + j_col;
        idx_row = i_row * 32L + k_row;
        idx = idx_col * 32L + k_col;
        t = orig[idx_row * 39304L + idx_col] + ((C0 * (orig[idx_row * 39304L + idx_col - 1L] + orig[idx_row * 39304L + idx_col + 1L])) + (C1 * (orig[idx_row * 39304L + idx_col - 32L] + orig[idx_row * 39304L + idx_col + 32L])));
        sol[idx] = t;
      }
      i = 1L + (-32L);
    }
    j = 1L + (-32L);
  }
  k = 1L + (-32L);
}