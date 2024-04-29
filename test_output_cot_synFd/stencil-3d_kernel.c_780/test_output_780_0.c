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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 2; k < 392; k++) {...} */
  for (k = 2L; k <= 392L - 1L; k++) {
     k_col = k;
    loop_j:
/* Standardize from: for(j = 2; j < 392; j++) {...} */
    for (j = 2L; j <= 392L - 1L; j++) {
      j_col = j;
      loop_i:
/* Standardize from: for(i = 2; i < 392; i++) {...} */
      for (i = 2L; i <= 392L - 1L; i++) {
        i_col = i;
        idx_col = ((k_col - 2L) * 392L * 392L) + ((j_col - 2L) * 392L) + i_col - 2L;
        idx_row = (k_col * 392L * 392L) + (j_col * 392L) + i_col;
        idx_in = (i_col - 2L) + 392L * ((j_col - 2L) + 392L * (k_col - 2L));
        t = C0 * (orig[idx_in] - ((orig[idx_col - 1L] + orig[idx_col + 1L]) / 2L + (orig[idx_row - 392L] + orig[idx_row + 392L]) / 2L));
        sol[idx_row] = t;
      }
    }
  }
}