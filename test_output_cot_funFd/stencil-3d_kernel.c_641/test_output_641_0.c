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
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2; k <= 32 - 2; k++) {
     k_col = k;
     loop_j:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2; j <= 32 - 2; j++) {
      j_col = j;
      loop_i:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2; i <= 32 - 2; i++) {
        i_col = i;
        idx_col = i_col + 32L * j_col;
        idx = idx_col + 32L * 32L * k_col;
        i_row = i - 2;
        j_row = j - 2;
        k_row = k - 2;
        idx_row = i_row + 32L * j_row;
        t = orig[idx] + C0 * (orig[idx_row + 32L] + orig[idx_row - 32L] + orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + 32L + 1] + orig[idx_col + 32L - 1] + orig[idx_col - 1 + 32L] + orig[idx_col - 1 - 32L]) + C1 * (orig[idx_row + 32L + 1] + orig[idx_row + 32L - 1] + orig[idx_row - 32L + 1] + orig[idx_row - 32L - 1] + orig[idx_col + 1 + 32L] + orig[idx_col + 1 - 32L] + orig[idx_col - 1 + 32L] + orig[idx_col - 1 - 32L]);
        sol[idx] = t;
      }
    }
  }
}