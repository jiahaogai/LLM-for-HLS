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
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j <= 32L + 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i <= 32L + 1; i++) {
        idx = i + (j - 1) * 32L + (k - 1) * 32L * 32L;
        idx_col = i - 1 + (j - 1) * 32L + (k - 1) * 32L * 32L;
        idx_row = i + (j - 1) * 32L - 1 + (k - 1) * 32L * 32L;
        idx_in = idx_col + 32L * 32L * (idx_row - 1);
        idx_out = idx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig[idx_in - 1] + orig[idx_in + 1] + orig[idx_in - 32L] + orig[idx_in + 32L] + orig[idx_in - 32L * 32L] + orig[idx_in + 32L * 32L]))) / 64L;
      }
    }
  }
}