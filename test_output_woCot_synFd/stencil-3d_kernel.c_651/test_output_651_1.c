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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        bound = (32L << 2) + 1L;
        t = orig[i_col + ((j_col) << 3) + ((k_col) << 5)] + ((orig[i_col + -1L + ((j_col) << 3) + ((k_col) << 5)] + orig[i_col + (1L + ((j_col) << 3)) + ((k_col) << 5)] + orig[i_col + ((j_col) << 3) + (-1L + (k_col << 3))]) + orig[i_col + ((j_col) << 3) + (1L + (k_col << 3))]);
        t = (t + orig[i_col + ((j_col + 1L) << 3) + ((k_col) << 5)] + orig[i_col + ((j_col - 1L) << 3) + ((k_col) << 5)] + orig[i_col + ((j_col) << 3) + ((k_col + 1L) << 3)] + orig[i_col + ((j_col) << 3) + ((k_col - 1L) << 3)]) >> 3;
        sol[i_col + ((j_col) << 3) + ((k_col) << 5)] = t;
      }
    }
  }
}