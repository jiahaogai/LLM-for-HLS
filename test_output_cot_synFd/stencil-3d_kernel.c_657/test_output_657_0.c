#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        k_col = -1 + 32L * k;
        i_col = -1 + 32L * i;
        idx = i_col + k_col;
        tmp = C0 * (orig[idx] + orig[idx + 1L] + orig[idx + 32L] + orig[idx + 33L]);
        tmp += C1 * (orig[idx + 1L + 32L] + orig[idx + 32L + 32L] + orig[idx + 33L + 32L] + orig[idx + 34L + 32L]);
        sol[idx] = tmp;
      }
    }
  }
}