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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = C0 * (orig[i_col + 39072L * j_col + 0L] + orig[i_col + 39072L * (j_col + 1L) + 0L] + orig[i_col + 39072L * (j_col + 2L) + 0L] + orig[i_col + 39072L * (j_col + 3L) + 0L] + orig[i_col + 39072L * (j_col + 4L) + 0L] + orig[i_col + 39072L * (j_col + 5L) + 0L] + orig[i_col + 39072L * (j_col + 6L) + 0L] + orig[i_col + 39072L * (j_col + 7L) + 0L] + orig[i_col + 39072L * (j_col + 8L) + 0L] + orig[i_col + 39072L * (j_col + 9L) + 0L] + orig[i_col + 39072L * (j_col + 10L) + 0L] + orig[i_col + 39072L * (j_col + 11L) + 0L] + orig[i_col + 39072L * (j_col + 12L) + 0L] + orig[i_col + 39072L * (j_col + 13L) + 0L] + orig[i_col + 39072L * (j_col + 14L) + 0L] + orig[i_col + 39072L * (j_col + 15L) + 0L] + orig[i_col + 39072L * (j_col + 16L) + 0L] + orig[i_col + 39072L * (j_col + 17L) + 0L] + orig[i_col + 39072L * (j_col + 18L) + 0L] + orig[i_col + 39072L * (j_col + 19L) + 0L] + orig[i_col + 39072L * (j_col + 20L) + 0L] + orig[i_col + 39072L * (j_col + 21L) + 0L] + orig[i_col + 39072L * (j_col + 22L) + 0L] + orig[i_col + 39072L * (j_col + 23L) + 0L] + orig[i_col + 39072L * (j_col + 24L) + 0L] + orig[i_col + 39072L * (j_col + 25L) + 0L] + orig[i_col + 39072L * (j_col + 26L) + 0L] + orig[i_col + 39072L * (j_col + 27L) + 0L] + orig[i_col + 39072L * (j_col + 28L) + 0L] + orig[i_col + 39072L * (j_col + 29L) + 0L] + orig[i_col + 39072L * (j_col + 30L) + 0L] + orig[i_col + 39072L * (j_col + 31L) + 0L]) + C1 * (orig[i_col + 39072L * j_col + 32L] + orig[i_col + 39072L * (j_col + 1L) + 32L] + orig[i_col + 39072L * (j_col + 2L) + 32L] + orig[i_col + 39072L * (j_col + 3L) + 32L] + orig[i_col + 39072L * (j_col + 4L) + 32L] + orig[i_col + 39072L * (j_col + 5L) + 32L] + orig[i_col + 39072L * (j_col + 6L) + 32L] + orig[i_col + 39072L * (j_col + 7L) + 32L] + orig[i_col + 39072L * (j_col + 8L) + 32L] + orig[i_col + 39072L * (j_col + 9L) + 32L] + orig[i_col + 39072L * (j_col + 10L) + 32L] + orig[i_col + 39072L * (j_col + 11L) + 32L] + orig[i_col + 39072L * (j_col + 12L) + 32L] + orig[i_col + 39072L * (j_col + 13L) + 32L] + orig[i_col + 39072L * (j_col + 14L) + 32L] + orig[i_col + 39072L * (j_col + 15L) + 32L] + orig[i_col + 39072L * (j_col + 16L) + 32L] + orig[i_col + 39072L * (j_col + 17L) + 32L] + orig[i_col + 39072L * (j_col + 18L) + 32L] + orig[i_col + 39072L * (j_col + 19L) + 32L] + orig[i_col + 39072L * (j_col + 20L) + 32L] + orig[i_col + 39072L * (j_col + 21L) + 32L] + orig[i_col + 39072L * (j_col + 22L) + 32L] + orig[i_col + 39072L * (j_col + 23L) + 32L] + orig[i_col + 39072L * (j_col + 24L) + 32L] + orig[i_col + 39072L * (j_col + 25L) + 32L] + orig[i_col + 39072L * (j_col + 26L) + 32L] + orig[i_col + 39072L * (j_col + 27L) + 32L] + orig[i_col + 39072L * (j_col + 28L) + 32L] + orig[i_col + 39072L * (j_col + 29L) + 32L] + orig[i_col + 39072L * (j_col + 30L) + 32L] + orig[i_col + 39072L * (j_col + 31L) + 32L] + orig[i_col + 39072L * (j_col + 32L) + 32L]);
        sol[i + 32L + 39304L * (j + 32L + 32L * k)] = buf;
      }
    }
  }
}