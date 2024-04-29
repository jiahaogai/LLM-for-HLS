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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1 + 32; i > 1 + 32 - 1; i--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1 + 32; j > 1 + 32 - 1; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1 + 32; k > 1 + 32 - 1; k--) {
        k_col = ((32 + 1) * (32 + 1)) * k;
        j_col = (32 + 1) * j;
        i_col = (32 + 1) * i;
        buf = C0 * (orig[k_col - 1 - 32 * (32 + 1)]) + C0 * (orig[k_col - 32 * (32 + 1)]) + C0 * (orig[k_col + 1 - 32 * (32 + 1)]) + C1 * (orig[k_col - 1]) + C1 * (orig[k_col]) + C1 * (orig[k_col + 1]) + C0 * (orig[k_col + 32 * (32 + 1) - 1]) + C0 * (orig[k_col + 32 * (32 + 1)]) + C0 * (orig[k_col + 32 * (32 + 1) + 1]) + C1 * (orig[k_col + 32 * (32 + 1) - 32]) ;
        delta = buf - sol[k_col];
        sol[k_col] = buf;
      }
    }
  }
}