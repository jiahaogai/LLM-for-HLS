#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
  for (i = 1 + 32 - 1; i-- > 32 - 1; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32 - 1; j-- > 32 - 1; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
      for (k = 1 + 32 - 1; k-- > 32 - 1; ) {
        k_col = ((32 + 1) * (32 + 1)) * k + (32 + 1) * j + i;
        i_col = (32 + 1) * k + j;
        j_col = (32 + 1) * j + i;
        t = C0 * orig[k_col] + C1 * (orig[i_col] + orig[j_col]);
        sol[k_col] = t;
      }
    }
  }
}