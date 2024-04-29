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
  long idx_out;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1; ) {
        i_row = i + 16 - 1;
        j_row = j + 16 - 1;
        k_row = k + 16 - 1;
        idx_row = i_row * 32 + j_row * 3 + k_row;
        loop_k_col:
        for (k_col = k - 1; k_col > 0; k_col--) {
          idx_col = idx_row + 32 * (k_col - 1);
          loop_j_col:
          for (j_col = j - 1; j_col > 0; j_col--) {
            idx_col += 1;
            idx = idx_col + 1;
            val = orig[idx_col] + orig[idx] + orig[idx + 32] + orig[idx + 32 * 3];
            sol[idx] = val;
          }
        }
      }
    }
  }
}