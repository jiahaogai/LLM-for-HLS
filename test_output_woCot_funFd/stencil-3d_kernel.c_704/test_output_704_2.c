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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3; k++) {
     k_col = k;
     i_col = k_col * 32 + 1;
     j_col = ((k_col - 1) * 32) + 1;
     k_row = 32 + 1 - k;
     i_row = k_row;
     j_row = ((k_row - 1) * 32) + 1;
    loop_j:
    for (j = 1; j < 32 + 1 - 2; j++) {
      loop_i:
      for (i = 1; i < 32 + 1 - 2; i++) {
        idx = i + ((j * 32) + k);
        idx_col = i_col + j;
        idx_row = i_row + j;
        t = ((((C0 * (orig[idx] + orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_row + 32] + orig[idx_row - 32] + orig[idx_row * 32 + 32] + orig[idx_row * 32 - 32]) + 
          C1 * (orig[idx_col + 32] + orig[idx_col - 32] + orig[idx_row + 1] + orig[idx_row - 1])) / 4) - 
          sol[idx]) / C0);
        sol[idx] = t;
      }
    }
  }
}