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
  long idx_out;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k <= 39L - 1L; k++) {
     k_col = k;
    loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j <= 39L - 1L; j++) {
      j_col = j;
      k_row = k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i <= 39L - 1L; i++) {
        i_col = i;
        i_row = i;
        idx_col = i_col + ((j_col) + ((k_col) * 40L));
        idx_row = i_row + ((j_row) + ((k_row) * 40L));
        idx = idx_col + 40L * idx_row;
        idx_in = idx_row * 40L + idx_col;
        idx_out = idx;
        sol[idx_out] = ((2L * orig[idx_in]) + (C0 * (orig[idx_in + 1L] + orig[idx_in - 1L])) + (C1 * (orig[idx_in + 40L] + orig[idx_in - 40L]))) / (C0 + C1);
      }
    }
  }
}