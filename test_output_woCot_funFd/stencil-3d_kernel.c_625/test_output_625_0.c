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
/* Standardize from: for(k = 2; k < 392; k++) {...} */
  for (k = 2L; k <= 392L - 1L; k++) {
     k_col = (392L - k);
     k_row = (k + 1L);
    loop_j:
/* Standardize from: for(j = 2; j < 392; j++) {...} */
    for (j = 2L; j <= 392L - 1L; j++) {
      j_col = (392L - j);
      j_row = (j + 1L);
      loop_i:
/* Standardize from: for(i = 2; i < 392; i++) {...} */
      for (i = 2L; i <= 392L - 1L; i++) {
        i_col = (392L - i);
        i_row = (i + 1L);
        idx = (((i + 2L) * 392L) + (j + 2L)) * 392L + (k + 2L);
        idx_col = (((i_col + 2L) * 392L) + (j_col + 2L)) * 392L + (k_col + 2L);
        idx_row = (((i_row + 2L) * 392L) + (j_row + 2L)) * 392L + (k_row + 2L);
        t = (((C0 * (orig[idx_col] + orig[idx_row])) - (C1 * (orig[idx] + orig[idx_col] + orig[idx_row] + orig[idx_col + 1L] + orig[idx_col - 1L] + orig[idx_row + 1L] + orig[idx_row - 1L]))) / (2.0 * 2.0 * 2.0));
        sol[idx] = t;
      }
    }
  }
}