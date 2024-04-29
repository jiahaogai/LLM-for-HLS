#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2; k <= ((long )39302) - 2; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 2; j < 39300; j++) {...} */
    for (j = 2; j <= ((long )39300) - 2; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 39304; i++) {...} */
      for (i = 2; i <= ((long )39304) - 2; i++) {
        idx = ((((k - 2) * 39300) + (j - 2)) * 39304) + (i - 2);
        idx_col = ((((k - 1) * 39300) + (j - 1)) * 39304) + (i - 1);
        t = (((C0 * (orig[idx_col] - orig[idx_col + 1])) + (C1 * (orig[idx_col + 39304] - orig[idx_col + 39304 + 1]))) + orig[idx_col + 39304 * 2]) / ((long )8);
        sol[idx] = t;
      }
    }
  }
}