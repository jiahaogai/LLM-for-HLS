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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1 - 3; k--) {
     k_col = vmap[k];
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32 - 1; j > 32 + 1 - 2; j--) {
      j_col = vmap[j];
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32 - 2; i > 32 + 1 - 3; i--) {
        i_col = vmap[i];
        idx_col = i_col * 32 + j_col;
        idx = idx_col * 32 + k_col;
        i_row = i + 1;
        loop_j_row:
/* Standardize from: for(j_row = 24; j_row < 32 + 1; j_row++) {...} */
        for (j_row = 24; j_row < 32 + 1; j_row++) {
          j_row_col = vmap[j_row];
          idx_row = j_row_col * 32 + j_col;
          loop_k_row:
/* Standardize from: for(k_row = 24; k_row < 32 + 1; k_row++) {...} */
          for (k_row = 24; k_row < 32 + 1; k_row++) {
            k_row_col = vmap[k_row];
            idx_in = k_row_col * 32 + i_row;
            t = + orig[idx] + C0 * ( + orig[idx_row + 1] + orig[idx_row - 1] + orig[idx_col + 32] + orig[idx_col - 32] );
            t = + t + C1 * ( + orig[idx_in + 1] + orig[idx_in - 1] + orig[idx_in + 32] + orig[idx_in - 32] );
            sol[idx] = t;
          }
        }
      }
    }
  }
}