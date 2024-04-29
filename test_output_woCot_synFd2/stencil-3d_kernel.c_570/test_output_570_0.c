#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
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
        k_col = -(32L << 1) + k;
        i_col = -(32L << 1) + i;
        idx_col = i_col * 32L + k_col;
        t = orig[idx_col];
        idx = i * 32L * 32L + j * 32L + k;
        sol[idx] = t + ((+1L) * (orig[idx_col + 32L] + orig[idx_col + 1L])) + ((+2L) * (orig[idx_col + 33L] + orig[idx_col + 2L])) + ((+1L) * (orig[idx_col - 32L] + orig[idx_col - 1L])) + ((+2L) * (orig[idx_col - 31L] + orig[idx_col - 2L]));
      }
    }
  }
}