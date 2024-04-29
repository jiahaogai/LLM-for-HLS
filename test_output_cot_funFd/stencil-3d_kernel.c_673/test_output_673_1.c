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
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        idx = (((32L + 1L) * (32L + 1L)) * k) + (((32L + 1L) * j) + i);
        idx_col = (((32L + 1L) * (32L + 1L)) * (k - 1)) + (((32L + 1L) * (j - 1)) + (i - 1));
        t = C0 * (orig[idx_col] + orig[idx_col + 1]) + C1 * orig[idx_col + 32L + 1L];
        sol[idx] = t;
      }
    }
    k_col = (32L + 1L) * (1L + 2L);
/* Standardize from: for(j = 0L; j < 32L; j++) {...} */
    loopj_col:
    for (j = 0L; j < 32L; j++) {
      i_col = (32L + 1L) * (1L + ((j - 1L) / (32L + 1L)));
/* Standardize from: for(i = 0L; i < 32L; i++) {...} */
      loopi_col:
      for (i = 0L; i < 32L; i++) {
        idx_col = i_col + i;
        orig[idx_col] = sol[idx_col + k_col];
      }
    }
  }
}