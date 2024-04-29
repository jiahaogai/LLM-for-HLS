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
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1; k < 40 + 1; k++) {
     k_col = 40L * k;
     k_row = (40L * (k - 1)) + 1;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1; j < 40 + 1; j++) {
      j_col = 1L + (40L * j);
      j_row = (40L * (j - 1)) + 1;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1; i < 40 + 1; i++) {
        i_col = 1L + i;
        i_row = (40L * (i - 1)) + 1;
        idx_col = ((k_col - 1L) * 40L) + j_col;
        idx_row = ((k_row - 1L) * 40L) + i_row;
        idx_in = ((k_col - 1L) * 40L) + j_row;
        idx_out = (k_row * 40L) + i_col;
        idx = idx_out;
        sol[idx] = ((2L * orig[idx_in]) + (-1L * (orig[idx_col] + orig[idx_row])));
      }
    }
  }
}