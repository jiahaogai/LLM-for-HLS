#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long delta;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    long k_col_0 = (k - 1) * 30L;
    long k_col_1 = k * 30L;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      long j_col_0 = (j - 1) * 30L;
      long j_col_1 = j * 30L;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        long i_col = (i - 1) * 30L;
        buf = 0L;
        delta = 0L;
        loopk_col:
        for (k_col = k_col_0; k_col <= k_col_1 - 1L; k_col++) {
          long index = k_col + j_col_0 + i_col;
          buf += orig[index] * C0;
          delta += orig[index] * C1;
        }
        sol[i_col + j_col_0 + k_col_0] = buf + delta;
      }
    }
  }
}