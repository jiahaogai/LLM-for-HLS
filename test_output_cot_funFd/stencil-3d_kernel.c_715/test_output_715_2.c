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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2L; j <= 32L + 2L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i <= 32L + 1L; i++) {
        idx = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_col = i_col + (j_col - 1L) * 32L + (k_col - 1L) * 32L * 32L;
        t = orig[idx] + 3L * (orig[idx + 32L] + orig[idx + 32L * 32L] + orig[idx - 1L] + orig[idx - 32L] + orig[idx - 32L * 32L]);
        sol[idx_col] = t;
      }
    }
    k_col = k;
  }
  loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 32 + 1; j_col++) {...} */
  for (j_col = 1L; j_col <= 32L + 1L; j_col++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_i_col:
/* Standardize from: for(i_col = 1; i_col < 32 + 1; i_col++) {...} */
    for (i_col = 1L; i_col <= 32L + 1L; i_col++) {
      idx_col = i_col + (j_col - 1L) * 32L + (k_col - 1L) * 32L * 32L;
      orig[idx_col] = sol[idx_col];
    }
  }
}