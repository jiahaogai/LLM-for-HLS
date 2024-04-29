#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1 - 2; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i-- > 32 + 1 - 3; ) {
        tmp = 0L;
        k_col = -1L + k;
        loopk_col:
        for (; k_col < 32 + 1L; k_col++) {
          j_col = -2L + j;
          loopj_col:
          for (; j_col < 32 + 1L; j_col++) {
            i_col = -3L + i;
            loopi_col:
            for (; i_col < 32 + 1L; i_col++) {
              tmp += orig[i_col + 32L * (j_col + 32L * k_col)] * C0;
            }
          }
        }
        buf[i + 32L * (j + 32L * k)] = tmp;
      }
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      loopi_out:
      for (i = 1 + 3; i-- > 32 + 1 - 3; ) {
        sol[i + 32L * (j + 32L * k)] = buf[i];
      }
    }
  }
}