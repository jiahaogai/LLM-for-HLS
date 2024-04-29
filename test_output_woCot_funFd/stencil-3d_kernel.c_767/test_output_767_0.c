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
  long sum0;
  long sum1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx_col = i_col + 40L * (j_col + 40L * k_col);
        sum0 = C0 * orig[idx_col];
        sum1 = 0L;
        loop_k_col:
/* Standardize from: for(k_col = k - 1; k_col >= 0; k_col--) {...} */
        for (k_col = (40 + 0 - 1) - 1; k_col >= 0 + 0; k_col--) {
          idx_col = i_col + 40L * (j_col + 40L * k_col);
          sum1 += orig[idx_col];
        }
        loop_j_col:
/* Standardize from: for(j_col = j - 1; j_col >= 0; j_col--) {...} */
        for (j_col = (40 + 0 - 1) - 1; j_col >= 0 + 0; j_col--) {
          idx_col = i_col + 40L * (j_col + 40L * ((40 + 0 - 1) - 1));
          sum1 += orig[idx_col];
        }
        idx_col = i_col + 40L * (j_col + 40L * ((40 + 0 - 1) - 2));
        sum1 += orig[idx_col];
        sol[idx_col] = sum0 + sum1;
      }
    }
  }
}