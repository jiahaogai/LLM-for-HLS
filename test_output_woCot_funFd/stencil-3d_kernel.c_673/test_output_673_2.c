#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        idx = ((32L + 2L) * (32L + 2L) * k) + ((32L + 2L) * j) + i;
        idx_col = ((32L + 1L) * (32L + 1L) * k_col) + ((32L + 1L) * i_col) + j;
        t = (C0 * (orig[idx_col - 1 - 32L - 1L] + orig[idx_col - 32L - 1L] +
                   orig[idx_col + 1L - 32L - 1L] + orig[idx_col + 32L - 1L] +
                   orig[idx_col + 32L + 1L] + orig[idx_col + 1L] +
                   orig[idx_col - 1L])) +
             (C1 * orig[idx_col]);
        sol[idx] = t;
      }
    }
    k_col = k;
    loopj_col:
    for (j = 32L + 1L; j < 32 + 1L; j++) {
      i_col = 1L + 32L - k_col;
      idx_col = ((32L + 2L) * (32L + 2L) * k_col) + ((32L + 2L) * j) + i_col;
      orig[idx_col] = sol[idx_col];
    }
  }
}