#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 2; k < 32 - 2; k++) {...} */
  for (k = 2L; k <= 32L - 2L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 32 - 2; j++) {...} */
    for (j = 2L; j <= 32L - 2L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 - 2; i++) {...} */
      for (i = 2L; i <= 32L - 2L; i++) {
        i_col = i - 2L;
        j_col = j - 2L;
        k_col = k - 2L;
        idx_col = k_col * 32L * 32L + j_col * 32L + i_col;
        t = C0 * (orig[idx_col] + orig[idx_col + 1L]) + C1 * (orig[idx_col + 32L] + orig[idx_col + 33L]);
        idx = k_col * 32L * 32L + j_col * 32L + i_col;
        sol[idx] = t;
      }
    }
  }
}