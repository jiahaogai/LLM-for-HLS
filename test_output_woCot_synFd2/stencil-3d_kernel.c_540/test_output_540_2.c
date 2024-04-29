#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long bound_in;
  long idx;
  long idx_in;
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    bound_in = k - 1L;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      bound = bound_in - 1L;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        idx_in = i_col + (32L + 2L) * (j_col + (32L + 2L) * k_col);
        sum = ((2L * orig[idx_in]) + (orig[idx_in + 1L] + orig[idx_in - 1L])) + ((2L * orig[idx_in + (32L + 2L)]) + (orig[idx_in - (32L + 2L)] + orig[idx_in + (58L + 2L)])) + (orig[idx_in + (32L + 2L) * 2L] + orig[idx_in - (32L + 2L) * 2L]);
        idx = i_col + (32L * j_col) + (32L * 32L * k_col);
        sol[idx] = sum;
      }
    }
  }
}