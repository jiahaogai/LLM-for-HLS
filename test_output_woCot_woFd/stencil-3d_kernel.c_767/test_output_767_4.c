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
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx_col = i_col + 32 * (j_col + 32 * k_col);
        sum0 = ((long )0);
        sum1 = ((long )0);
        loop_k_col:
/* Standardize from: for(idx = k_col - 1; idx <= k_col + 1; idx++) {...} */
        for (idx = k_col - 1; idx <= k_col + 1; idx++) {
          if (2 <= idx && idx <= 30) {
            loop_j_col:
/* Standardize from: for(idx = j_col - 1; idx <= j_col + 1; idx++) {...} */
            for (idx = j_col - 1; idx <= j_col + 1; idx++) {
              if (2 <= idx && idx <= 30) {
                loop_i_col:
/* Standardize from: for(idx = i_col - 1; idx <= i_col + 1; idx++) {...} */
                for (idx = i_col - 1; idx <= i_col + 1; idx++) {
                  if (orig[idx + 32 * (idx_col + 32 * idx_col)] == 1) {
                    sum0++;
                  }
                }
              }
            }
          }
        }
        loop_k_col:
/* Standardize from: for(idx = k_col - 1; idx <= k_col + 1; idx++) {...} */
        for (idx = k_col - 1; idx <= k_col + 1; idx++) {
          if (2 <= idx && idx <= 30) {
            loop_j_col:
/* Standardize from: for(idx = j_col - 1; idx <= j_col + 1; idx++) {...} */
            for (idx = j_col - 1; idx <= j_col + 1; idx++) {
              if (2 <= idx && idx <= 30) {
                loop_i_col:
/* Standardize from: for(idx = i_col - 1; idx <= i_col + 1; idx++) {...} */
                for (idx = i_col - 1; idx <= i_col + 1; idx++) {
                  if (orig[idx + 32 * (idx_col + 32 * idx_col)] == 1) {
                    sum1++;
                  }
                }
              }
            }
          }
        }
        sol[i_col + 32 * (j_col + 32 * k_col)] = (((C0 * sum0 + C1) * sum1) + 32768) / 65536;
      }
    }
  }
}