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
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 2; k < 392; k++) {...} */
  for (k = 2L; k <= 392L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 392; j++) {...} */
    for (j = 2L; j <= 392L - 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 392; i++) {...} */
      for (i = 2L; i <= 392L - 1L; i++) {
        i_col = i - 2L;
        j_col = j - 2L;
        k_col = k - 2L;
        idx_in = i_col + 392L * (j_col + 392L * k_col);
        bound_in = k_col + 1L;
        if (bound_in < 392L) {
          bound = bound_in + 1L;
        }
        else {
          bound = 392L;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_t3:
        for (t3 = bound; t3 > 0L; t3--) {
          if (t3 - 1L < bound_in) {
            idx = idx_in + 392L * (t3 - 1L);
            sol[idx] = orig[idx] + 1.5L * (orig[idx + 392L] + orig[idx - 392L] + orig[idx + 1L] + orig[idx - 1L]);
          }
        }
      }
    }
  }
}