#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_out;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i > 32 + 1; i--) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_out = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        sum = ((long )0);
        loop_k_col:
/* Standardize from: for(k_col = k - 1; k_col <= k + 1; k_col++) {...} */
        for (k_col = k - 1; k_col <= k + 1; k_col++) {
          loop_j_col:
/* Standardize from: for(j_col = j - 1; j_col <= j + 1; j_col++) {...} */
          for (j_col = j - 1; j_col <= j + 1; j_col++) {
            loop_i_col:
/* Standardize from: for(i_col = i - 1; i_col <= i + 1; i_col++) {...} */
            for (i_col = i - 1; i_col <= i + 1; i_col++) {
              idx_col = i_col + (j_col - 1) * 32 + (k_col - 1) * 32 * 32;
              sum += orig[idx_col] * C0;
            }
          }
        }
        loop_k_row:
/* Standardize from: for(k_row = k + 1; k_row <= 32 + 1 - 1; k_row++) {...} */
        for (k_row = k + 1; k_row <= 32 + 1 - 1; k_row++) {
          loop_j_row:
/* Standardize from: for(j_row = j + 1; j_row <= 32 + 1 - 1; j_row++) {...} */
          for (j_row = j + 1; j_row <= 32 + 1 - 1; j_row++) {
            idx_row = i + (j_row - 1) * 32 + (k_row - 1) * 32 * 32;
            sum += orig[idx_row] * C1;
          }
        }
        sol[idx_out] = sum;
      }
    }
  }
}