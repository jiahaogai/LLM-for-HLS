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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j <= 32L + 32L - 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i <= 32L + 32L - 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = orig[i_col + ((j_col) + (k_col) * 32L) * 39L];
        delta = buf - ((orig[i_col + -1L + ((j_col) + (k_col) * 32L) * 39L]) + (orig[i_col + 1L + ((j_col) + (k_col) * 32L) * 39L]) + (orig[i_col + ((j_col) + -1L * 32L) * 39L]) + (orig[i_col + ((j_col) + 1L * 32L) * 39L]) + (orig[i_col + ((j_col) + 32L * 32L) * 39L]) + (orig[i_col + ((j_col) + -32L * 32L) * 39L]));
        sol[i_col + ((j_col) + (k_col) * 32L) * 39L] = delta;
      }
    }
  }
}