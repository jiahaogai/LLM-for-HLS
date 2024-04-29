#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 2; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 1; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        bound = (32L * 32L) * (k - 1L);
        sum0 = orig[bound + j_col * 32L + i_col] + orig[bound + j_col * 32L + i_col + 1L] + orig[bound + (j_col + 1L) * 32L + i_col] + orig[bound + (j_col + 1L) * 32L + i_col + 1L];
        sum1 = orig[bound + (j_col + 2L) * 32L + i_col] + orig[bound + (j_col + 2L) * 32L + i_col + 1L];
        mul0 = sum0 * 32L;
        mul1 = sum1 * 1L;
        sol[bound + j_col * 32L + i_col] = mul0 + mul1;
      }
    }
  }
}