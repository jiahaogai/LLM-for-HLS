Code: ### Generated Code:
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
  long idx_out;
  long val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1; i <= 32; i++) {
     i_row = i - 1;
     idx_row = i_row * 32;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1; j <= 32; j++) {
      j_row = j - 1;
      idx_row_j = idx_row + j_row;
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1; k <= 32; k++) {
        k_row = k - 1;
        idx_k = k_row * 256;
        idx = idx_k + idx_row_j;
        val = ((C0 * orig[idx]) + (C1 * (orig[idx_k + idx_row + 1] + orig[idx_k + idx_row - 1] + orig[idx_k + 1 + idx_row] + orig[idx_k + 1 - idx_row] + orig[idx_k - 1 + idx_row] + orig[idx_k - 1 - idx_row] + orig[idx_k + idx_row]))) / 66;
        sol[idx] = val;
      }
    }
  }
}