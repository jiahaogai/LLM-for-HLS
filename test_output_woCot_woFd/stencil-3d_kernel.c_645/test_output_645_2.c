#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
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
        t = C0 * (orig[idx_col + 32 * 32 * 0] + orig[idx_col + 32 * 32 * 1] + orig[idx_col + 32 * 32 * 2] + orig[idx_col + 32 * 32 * 3] + orig[idx_col + 32 * 32 * 4] + orig[idx_col + 32 * 32 * 5] + orig[idx_col + 32 * 32 * 6] + orig[idx_col + 32 * 32 * 7] + orig[idx_col + 32 * 32 * 8] + orig[idx_col + 32 * 32 * 9] + orig[idx_col + 32 * 32 * 10] + orig[idx_col + 32 * 32 * 11] + orig[idx_col + 32 * 32 * 12] + orig[idx_col + 32 * 32 * 13] + orig[idx_col + 32 * 32 * 14] + orig[idx_col + 32 * 32 * 15] + orig[idx_col + 32 * 32 * 16] + orig[idx_col + 32 * 32 * 17] + orig[idx_col + 32 * 32 * 18] + orig[idx_col + 32 * 32 * 19] + orig[idx_col + 32 * 32 * 20] + orig[idx_col + 32 * 32 * 21] + orig[idx_col + 32 * 32 * 22] + orig[idx_col + 32 * 32 * 23] + orig[idx_col + 32 * 32 * 24] + orig[idx_col + 32 * 32 * 25] + orig[idx_col + 32 * 32 * 26] + orig[idx_col + 32 * 32 * 27] + orig[idx_col + 32 * 32 * 28] + orig[idx_col + 32 * 32 * 29] + orig[idx_col + 32 * 32 * 30] + orig[idx_col + 32 * 32 * 31]) + C1 * (orig[idx_row + 32 * 0] + orig[idx_row + 32 * 1] + orig[idx_row + 32 * 2] + orig[idx_row + 32 * 3] + orig[idx_row + 32 * 4] + orig[idx_row + 32 * 5] + orig[idx_row + 32 * 6] + orig[idx_row + 32 * 7] + orig[idx_row + 32 * 8] + orig[idx_row + 32 * 9] + orig[idx_row + 32 * 10] + orig[idx_row + 32 * 11] + orig[idx_row + 32 * 12] + orig[idx_row + 32 * 13] + orig[idx_row + 32 * 14] + orig[idx_row + 32 * 15] + orig[idx_row + 32 * 16] + orig[idx_row + 32 * 17] + orig[idx_row + 32 * 18] + orig[idx_row + 32 * 19] + orig[idx_row + 32 * 20] + orig[idx_row + 32 * 21] + orig[idx_row + 32 * 22] + orig[idx_row + 32 * 23] + orig[idx_row + 32 * 24] + orig[idx_row + 32 * 25] + orig[idx_row + 32 * 26] + orig[idx_row + 32 * 27] + orig[idx_row + 32 * 28] + orig[idx_row + 32 * 29] + orig[idx_row + 32 * 30] + orig[idx_row + 32 * 31] + orig[idx_row + 0] + orig[idx_row + 1] + orig[idx_row + 2] + orig[idx_row + 3] + orig[idx_row + 4] + orig[idx_row + 5] + orig[idx_row + 6] + orig[idx_row + 7] + orig[idx_row + 8] + orig[idx_row + 9] + orig[idx_row + 10] + orig[idx_row + 11] + orig[idx_row + 12] + orig[idx_row + 13] + orig[idx_row + 14] + orig[idx_row + 15] + orig[idx_row + 16] + orig[idx_row + 17] + orig[idx_row + 18] + orig[idx_row + 19] + orig[idx_row + 20] + orig[idx_row + 21] + orig[idx_row + 22] + orig[idx_row + 23] + orig[idx_row + 24] + orig[idx_row + 25] + orig[idx_row + 26] + orig[idx_row + 27] + orig[idx_row + 28] + orig[idx_row + 29] + orig[idx_row + 30] + orig[idx_row + 31]);
        sol[idx] = t;
      }
    }
  }
}