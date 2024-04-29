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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i > 32 + 1; i--) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_in = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        t = orig[idx_in] + ((C0 * (orig[idx_col + 1] + orig[idx_col - 1])) + (C1 * (orig[idx_row + 32] + orig[idx_row - 32])));
        sol[idx] = t;
      }
    }
  }
}