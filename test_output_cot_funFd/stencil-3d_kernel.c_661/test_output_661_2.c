#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 2L; j <= 32L + 1L - 2L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 3L; i <= 32L + 1L - 3L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        bound = (32L * (32L * k_col + j_col) + i_col) * 2L;
        t = orig[bound + 0L] + orig[bound + 1L] + orig[bound + 32L] + orig[bound + 33L] + orig[bound + 64L] + orig[bound + 65L] + orig[bound + 96L] + orig[bound + 97L];
        sol[bound + 0L] = (t + orig[bound + 16L]) / 9L;
        sol[bound + 1L] = (t + orig[bound + 17L]) / 9L;
        sol[bound + 32L] = (t + orig[bound + 48L]) / 9L;
        sol[bound + 33L] = (t + orig[bound + 49L]) / 9L;
        sol[bound + 64L] = (t + orig[bound + 80L]) / 9L;
        sol[bound + 65L] = (t + orig[bound + 81L]) / 9L;
        sol[bound + 96L] = (t + orig[bound + 112L]) / 9L;
        sol[bound + 97L] = (t + orig[bound + 113L]) / 9L;
      }
    }
  }
}