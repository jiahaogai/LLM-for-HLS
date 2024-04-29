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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
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
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i > 32 + 1; i--) {
        i_row = i - 1;
        j_row = j - 1;
        k_row = k - 1;
        idx_row = i_row * (32 + 1) * (32 + 1) + j_row * (32 + 1) + k_row;
        idx = idx_row;
        loop_k_col:
        for (k_col = k - 32; k_col < k; k_col++) {
          idx_col = idx + (32 + 1) * (32 + 1) * (k_col - k_row);
          loop_j_col:
          for (j_col = j - 32; j_col < j; j_col++) {
            idx_in = idx_col + j_col - j_row;
            t = orig[idx_in];
            sol[idx_in] = ((t << 1) + sol[idx_in - 1]) - sol[idx_in + 1];
          }
        }
      }
    }
  }
}