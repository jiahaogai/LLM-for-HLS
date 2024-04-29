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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i < 32 + 1; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        bound = (32L * 32L) * (k - 1L);
        t = orig[bound + j_col * 32L + i_col] + ((long )0) + orig[bound + j_col * 32L + i_col + 1L] + ((long )0) + orig[bound + (j_col + 1L) * 32L + i_col + 1L] + ((long )0) + orig[bound + (j_col + 1L) * 32L + i_col] + ((long )0) + orig[bound + (j_col + 1L) * 32L + i_col + 1L] + ((long )0);
        sol[bound + j_col * 32L + i_col] = t;
      }
    }
  }
}