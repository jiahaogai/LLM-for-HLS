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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1; k <= 39; k++) {
     k_col = k;
     i_col = 1;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1; j <= 39; j++) {
      j_col = j;
      i_row = i_col;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1; i <= 39; i++) {
        j_row = j_col;
        i_row = i_row + 1;
        idx = i_row - 1 + (j_row - 1) * 40 + (k_row - 1) * 1600;
        idx_col = i_col - 1 + (j_col - 1) * 40 + (k_col - 1) * 160;
        idx_row = i_row - 1 + (j_row - 1) * 40 + (k_row - 1) * 160;
        idx_in = idx_col + 160 * idx_row;
        t = orig[idx_in] + ((40 * (orig[idx + 1] + orig[idx_col + 1])) + (160 * (orig[idx_row + 1] + orig[idx + 40]))) - (2 * (orig[idx] + orig[idx_col] + orig[idx_row] + orig[idx + 40 - 1] + orig[idx_row - 1] + orig[idx_col - 1])));
        sol[idx] = t;
      }
      i_col = i_col + 40;
    }
    k_row = k_col;
  }
}