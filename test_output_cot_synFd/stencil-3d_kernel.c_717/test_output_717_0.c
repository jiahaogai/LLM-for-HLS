#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long index;
  long result = 0L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2L; k <= ((long )39302L) - 2L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopj:
/* Standardize from: for(j = 2; j < 39302; j++) {...} */
    for (j = 2L; j <= ((long )39302L) - 2L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 39302; i++) {...} */
      for (i = 2L; i <= ((long )39302L) - 2L; i++) {
        i_col = i - 2L;
        j_col = j - 2L;
        k_col = k - 2L;
        index = ((k_col * 39302L) + j_col) * 39302L + i_col;
        result = ((((orig[index + 1L] + orig[index - 1L]) * C0) + ((orig[index + 39302L] + orig[index - 39302L]) * C1)) + orig[index]) / ((C0 * 2L) + C1);
        sol[index] = result;
      }
    }
  }
}