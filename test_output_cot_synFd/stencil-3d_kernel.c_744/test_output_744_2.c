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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k < ((32 + 2) + 2); k++) {
     k_col = k - 2;
     loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j < ((32 + 2) + 2); j++) {
      j_col = j - 2;
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i < ((32 + 2) + 2); i++) {
        i_col = i - 2;
        i_row = i - 2;
        j_row = j - 2;
        k_row = k - 2;
        idx = i_row * (32 + 4) + j_row;
        idx_col = i_col * (32 + 4) + j_col;
        idx_row = i_row * (32 + 2) + j_row;
        t = C0 * (orig[idx_col + idx_row] + orig[idx_col + idx_row + 1] + orig[idx_col + idx_row + (32 + 2)] + orig[idx_col + idx_row + (32 + 2) + 1] ) + C1 * (orig[idx_col + idx_row + (32 + 4)] + orig[idx_col + idx_row + (32 + 4) + 1] + orig[idx_col + idx_row + (32 + 4) + (32 + 2)] + orig[idx_col + idx_row + (32 + 4) + (32 + 2) + 1] );
        sol[idx] = t;
      }
    }
  }
}