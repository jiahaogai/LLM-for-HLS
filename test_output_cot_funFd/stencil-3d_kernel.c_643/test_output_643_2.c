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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3 + 1; i++) {
        i_col = i - 1 - 3 + 0 * (1 - 3) + 1;
        j_col = j - 1 - 3 + 0 * (1 - 3) + 1;
        k_col = k - 1 - 3 + 0 * (1 - 3) + 1;
        idx_col = i_col + 32 * (j_col + 32 * k_col);
        idx = i + 3 * (j + 3 * k);
        t = orig[idx_col] + ((2 * (orig[idx_col + 1] + orig[idx_col - 1])) + (2 * (orig[idx_col + 32] + orig[idx_col - 32])) + (2 * (orig[idx_col + 32 * 32] + orig[idx_col - 32 * 32])));
        sol[idx] = ((1.0 / 12.0) * t) - orig[idx];
      }
    }
  }
}