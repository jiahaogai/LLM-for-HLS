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
  long sum0;
  long sum1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        idx_col = i_col + 32L * (j_col + 32L * k_col);
        sum0 = ((orig[idx_col - 1L - 32L * 32L] + orig[idx_col + 1L - 32L * 32L]) + (orig[idx_col - 32L - 32L * 32L] + orig[idx_col + 32L - 32L * 32L])) + (orig[idx_col - 32L * 32L] + orig[idx_col + 32L * 32L]);
        sum1 = ((orig[idx_col - 1L] + orig[idx_col + 1L]) + (orig[idx_col - 32L] + orig[idx_col + 32L])) + orig[idx_col];
        idx = i_col + 32L * (j_col + 32L * k_col);
        sol[idx] = C0 * sum0 + C1 * sum1;
      }
    }
  }
}