#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long tmp;
  
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
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        tmp = C0 * (orig[i_col + 32L * (j_col + 32L * k_col)]);
        sol[i_col + 32L * (j_col + 32L * k_col)] = tmp;
        loopk_col:
        for (long tmp_k = 0L; tmp_k < 1L; tmp_k++) {
          k_col = k_col + 1L;
          tmp = C1 * (orig[i_col + 32L * (j_col + 32L * k_col)]);
          sol[i_col + 32L * (j_col + 32L * k_col)] += tmp;
        }
      }
    }
  }
}